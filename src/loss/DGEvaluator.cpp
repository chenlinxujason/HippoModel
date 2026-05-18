#include "hippomodel/loss/DGEvaluator.h"

#include "hippomodel/analysis/Correlation.h"
#include "hippomodel/analysis/FiringRate.h"
#include "hippomodel/analysis/PSD.h"
#include "hippomodel/network/DGNetworkBuilder.h"
#include "hippomodel/optimizer/ProgressiveEI.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>

namespace hippomodel::DG {
namespace {

std::vector<std::string> orderedOutputGroups() {
    return {"DG_GC", "DG_MC", "DG_BC", "DG_AAC", "DG_BCCCK", "DG_HICAP", "DG_HIPP", "DG_MOPP", "DG_TML"};
}

SpikeMonitor* monitorFor(DGNetworkContext& ctx, const std::string& group) {
    if (group == "DG_GC") return ctx.mon_dg_gc;
    if (group == "DG_MC") return ctx.mon_dg_mc;
    if (group == "DG_AAC") return ctx.mon_dg_aac;
    if (group == "DG_BC") return ctx.mon_dg_bc;
    if (group == "DG_BCCCK") return ctx.mon_dg_bccck;
    if (group == "DG_HICAP") return ctx.mon_dg_hicap;
    if (group == "DG_HIPP") return ctx.mon_dg_hipp;
    if (group == "DG_MOPP") return ctx.mon_dg_mopp;
    if (group == "DG_TML") return ctx.mon_dg_tml;
    return nullptr;
}

}  // namespace

DGEvaluator::DGEvaluator(std::unique_ptr<DGNetworkContext> context, OptimizationLogger* logger)
    : ctx_(std::move(context)), logger_(logger) {}

double DGEvaluator::targetFor(const std::string& group) const {
    const auto it = ctx_->config.firing_rate_targets.find(group);
    if (it != ctx_->config.firing_rate_targets.end()) return it->second;
    return ctx_->spec.default_fr_targets.at(group);
}

std::pair<double, double> DGEvaluator::boundsFor(const std::string& group) const {
    const auto it = ctx_->config.firing_rate_bounds.find(group);
    if (it != ctx_->config.firing_rate_bounds.end()) return it->second;
    return ctx_->spec.default_fr_bounds.at(group);
}

void DGEvaluator::measureFiringRates(const std::vector<double>& params, bool publish_ei) {
    scaleDGWeights(*ctx_, params);

    ctx_->sim->runNetwork(ctx_->config.simulation.transient_sec, 0);

    for (const auto& group : orderedOutputGroups()) {
        if (auto* mon = monitorFor(*ctx_, group)) mon->startRecording();
    }

    ctx_->sim->runNetwork(ctx_->config.simulation.measurement_sec, 0);

    for (const auto& group : orderedOutputGroups()) {
        if (auto* mon = monitorFor(*ctx_, group)) mon->stopRecording();
    }

    firing_rates_.clear();
    mean_rates_.clear();
    for (const auto& group : orderedOutputGroups()) {
        if (auto* mon = monitorFor(*ctx_, group)) {
            firing_rates_[group] = mon->getAllFiringRates();
            mean_rates_[group] = meanFiringRate(firing_rates_[group]);
        }
    }

    const bool lowActivity = mean_rates_["DG_GC"] <= 0.03f;
    if (publish_ei) {
        if (lowActivity) {
            opt::ProgressiveEI::UpdateFiringRate("DG_GC", mean_rates_["DG_GC"]);
            std::cout << "[EI Logic] Low GC activity detected (" << mean_rates_["DG_GC"]
                      << "Hz). Modifying ONLY DG_GC connections." << std::endl;
        } else {
            for (const auto& group : orderedOutputGroups()) {
                opt::ProgressiveEI::UpdateFiringRate(group, mean_rates_[group]);
            }
        }
    }

    std::cout << "[measureFRs] DGGC=" << mean_rates_["DG_GC"]
              << " DGMC=" << mean_rates_["DG_MC"]
              << " DGBC=" << mean_rates_["DG_BC"]
              << " DGAAC=" << mean_rates_["DG_AAC"]
              << " DGBCCCK=" << mean_rates_["DG_BCCCK"]
              << " DGHICAP=" << mean_rates_["DG_HICAP"]
              << " DGHIPP=" << mean_rates_["DG_HIPP"]
              << " DGMOPP=" << mean_rates_["DG_MOPP"]
              << " DGTML=" << mean_rates_["DG_TML"]
              << std::endl;
}

double DGEvaluator::objective(const std::vector<double>& params, bool output) {
    measureFiringRates(params, true);

    EvaluationResult result;
    result.params = params;

    std::vector<double> frErrors;
    std::vector<double> means;
    for (const auto& group : orderedOutputGroups()) {
        const double target = targetFor(group);
        const auto bounds = boundsFor(group);
        const double per = perNeuronPercentError(firing_rates_[group], target);
        const double penalty = firingRatePenalty(mean_rates_[group], bounds.first, bounds.second, per);
        result.mean_firing_rates[group] = mean_rates_[group];
        result.firing_rate_errors[group] = penalty;
        means.push_back(mean_rates_[group]);
        frErrors.push_back(penalty);
    }
    result.ordered_mean_firing_rates = means;
    result.ordered_firing_rate_errors = frErrors;

    const int recLen = ctx_->mon_dg_gc->getRecordingTotalTime();
    const int T1_MS = recLen;
    const int T0_MS = std::max(0, recLen - ctx_->config.simulation.measurement_sec * 1000);
    const int T0_sec = T0_MS / 1000;
    const int T1_sec = T1_MS / 1000;

    result.corr_mean_abs = dvSliceCorrMeanAbsZeroLagRandom(
        ctx_->mon_dg_gc,
        ctx_->connectivity.loc_y.at("DG_GC"),
        ctx_->config.correlation.n_slices,
        ctx_->config.correlation.bin_ms,
        T0_MS,
        T1_MS,
        ctx_->config.correlation.n_shuffle,
        ctx_->config.correlation.dv_ymin_mm,
        ctx_->config.correlation.dv_ymax_mm);
    if (!std::isfinite(result.corr_mean_abs)) result.corr_mean_abs = 1.0;
    result.corr_mean_abs = std::max(0.0, std::min(1.0, result.corr_mean_abs));
    result.corr_error = 100.0 * std::abs(result.corr_mean_abs - ctx_->config.correlation.target_mean_abs_corr) /
                        ctx_->config.correlation.target_mean_abs_corr;

    std::vector<double> x_global;
    double fs = 0.0;
    buildGlobalPopulationTimeSeries(ctx_->mon_dg_gc, ctx_->config.oscillation.bin_ms, T0_MS, T1_MS, x_global, fs);

    const auto& osc = ctx_->config.oscillation;
    result.theta_ratio = rhythmRatio(x_global, fs, osc.theta_f1_hz, osc.theta_f2_hz, osc.ref_f1_hz, osc.ref_f2_hz);
    result.beta_ratio = rhythmRatio(x_global, fs, osc.beta_f1_hz, osc.beta_f2_hz, osc.ref_f1_hz, osc.ref_f2_hz);
    result.gamma_ratio = rhythmRatio(x_global, fs, osc.gamma_f1_hz, osc.gamma_f2_hz, osc.ref_f1_hz, osc.ref_f2_hz);
    result.two_hz_ratio = rhythmRatio(x_global, fs, osc.low_f1_hz, osc.low_f2_hz, osc.ref_f1_hz, osc.ref_f2_hz);

    auto ratioError = [](double ratio, double target) {
        if (!std::isfinite(ratio)) return 100.0;
        ratio = std::max(0.0, std::min(1.0, ratio));
        return 100.0 * std::abs(ratio - target) / target;
    };
    result.theta_error = ratioError(result.theta_ratio, osc.target_theta);
    result.beta_error = ratioError(result.beta_ratio, osc.target_beta);
    result.gamma_error = ratioError(result.gamma_ratio, osc.target_gamma);
    result.two_hz_error = ratioError(result.two_hz_ratio, osc.target_two_hz);

    if (output) {
        std::cout << "DGGC corr=" << result.corr_mean_abs
                  << " window=[" << T0_sec << "," << T1_sec << ")s, "
                  << ", betaRatio=" << result.beta_ratio
                  << ", gammaRatio=" << result.gamma_ratio
                  << std::endl;
    }

    const double frMeanError = std::accumulate(frErrors.begin(), frErrors.end(), 0.0) / static_cast<double>(frErrors.size());
    const double oscError = result.beta_error + result.gamma_error;
    result.total_loss = ctx_->config.loss_weights.firing_rate * frMeanError +
                        ctx_->config.loss_weights.correlation * result.corr_error +
                        ctx_->config.loss_weights.oscillation * oscError;

    for (const auto& kv : ctx_->file_generators) {
        kv.second->rewind(static_cast<int>(ctx_->sim->getSimTime()));
    }

    last_result_ = result;
    if (logger_ != nullptr) logger_->cache(result);
    return result.total_loss;
}

}  // namespace hippomodel::DG
