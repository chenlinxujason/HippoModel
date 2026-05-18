#include "hippomodel/optimizer/OptimizationLogger.h"

#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <stdexcept>

namespace hippomodel {
OptimizationLogger* g_logger = nullptr;
namespace {

double maxAbsParamDiff(const std::vector<double>& a, const std::vector<double>& b) {
    if (a.size() != b.size()) return std::numeric_limits<double>::infinity();
    double maxDiff = 0.0;
    for (size_t i = 0; i < a.size(); ++i) maxDiff = std::max(maxDiff, std::abs(a[i] - b[i]));
    return maxDiff;
}

void truncateFile(const std::string& filename) {
    std::ofstream out(filename, std::ios::trunc);
}

}  // namespace

OptimizationLogger::OptimizationLogger(std::string output_dir, std::string region, int scale, std::string tag)
    : output_dir_(std::move(output_dir)), region_(std::move(region)), scale_(scale), tag_(std::move(tag)) {
    std::filesystem::create_directories(output_dir_);
}

void OptimizationLogger::reset() {
    cache_.clear();
    truncateFile(path("nelder_mead_output(" + region_ + "," + scaleLabel() + ")" + suffix() + ".txt"));
    truncateFile(path(region_ + "_FR_and_Error(" + scaleLabel() + ")" + suffix() + ".txt"));
    truncateFile(path(region_ + "_Corr_and_Error(" + scaleLabel() + ")" + suffix() + ".txt"));
    truncateFile(path(region_ + "_betaR_and_Error(" + scaleLabel() + ")" + suffix() + ".txt"));
    truncateFile(path(region_ + "_gammaR_and_Error(" + scaleLabel() + ")" + suffix() + ".txt"));
    truncateFile(path("loss_trajectory.csv"));
}

void OptimizationLogger::cache(const EvaluationResult& result) {
    cache_.push_back(result);
    std::ofstream out(path("loss_trajectory.csv"), std::ios::app);
    out << cache_.size() << "," << result.total_loss << ","
        << result.corr_error << "," << result.beta_error << "," << result.gamma_error << "\n";
}

const EvaluationResult* OptimizationLogger::findCached(const std::vector<double>& params, double total) const {
    constexpr double kParamTol = 1e-8;
    constexpr double kTotalAbsTol = 1e-7;
    const EvaluationResult* best = nullptr;
    double bestTotalDiff = std::numeric_limits<double>::infinity();
    for (const auto& rec : cache_) {
        if (maxAbsParamDiff(rec.params, params) > kParamTol) continue;
        const double diff = std::abs(rec.total_loss - total);
        if (diff < bestTotalDiff) {
            best = &rec;
            bestTotalDiff = diff;
        }
    }
    if (best != nullptr) {
        const double totalTol = std::max(kTotalAbsTol, 1e-9 * std::max(1.0, std::abs(total)));
        if (bestTotalDiff > totalTol) {
            std::cerr << "[WARN] Found matching NM params, but cached total differs from NM runningBest: "
                      << "cached=" << best->total_loss << ", runningBest=" << total
                      << ", diff=" << bestTotalDiff << std::endl;
        }
    }
    return best;
}

void OptimizationLogger::logInitialVertex(int iteration, const std::vector<double>& params, double total) {
    const EvaluationResult* rec = findCached(params, total);
    if (rec == nullptr) {
        std::cerr << "[ERROR] Cannot log NM initial vertex at iteration " << iteration
                  << ": no cached evaluation matches this initial vertex." << std::endl;
        return;
    }
    appendTrajectory(iteration, params, total, path("nelder_mead_output(" + region_ + "," + scaleLabel() + ")" + suffix() + ".txt"));
    logVectorPair(iteration, rec->ordered_mean_firing_rates, rec->ordered_firing_rate_errors, path(region_ + "_FR_and_Error(" + scaleLabel() + ")" + suffix() + ".txt"));
    logVectorPair(iteration, {rec->corr_mean_abs}, {rec->corr_error}, path(region_ + "_Corr_and_Error(" + scaleLabel() + ")" + suffix() + ".txt"));
    logVectorPair(iteration, {rec->beta_ratio}, {rec->beta_error}, path(region_ + "_betaR_and_Error(" + scaleLabel() + ")" + suffix() + ".txt"));
    logVectorPair(iteration, {rec->gamma_ratio}, {rec->gamma_error}, path(region_ + "_gammaR_and_Error(" + scaleLabel() + ")" + suffix() + ".txt"));
    std::cout << "\n[NM INIT LOG] Iteration " << iteration
              << " initial vertex total error = " << total
              << " = FRmean + Corr(" << rec->corr_error << ")"
              << " + Osc [Beta(" << rec->beta_error << ") + Gamma(" << rec->gamma_error << ")]"
              << std::endl;
}

void OptimizationLogger::logBestSoFar(int iteration, const std::vector<double>& params, double total) {
    const EvaluationResult* rec = findCached(params, total);
    if (rec == nullptr) {
        std::cerr << "[ERROR] Cannot log NM best-so-far at iteration " << iteration
                  << ": no cached evaluation matches the selected NM best point." << std::endl;
        return;
    }
    appendTrajectory(iteration, params, total, path("nelder_mead_output(" + region_ + "," + scaleLabel() + ")" + suffix() + ".txt"));
    logVectorPair(iteration, rec->ordered_mean_firing_rates, rec->ordered_firing_rate_errors, path(region_ + "_FR_and_Error(" + scaleLabel() + ")" + suffix() + ".txt"));
    logVectorPair(iteration, {rec->corr_mean_abs}, {rec->corr_error}, path(region_ + "_Corr_and_Error(" + scaleLabel() + ")" + suffix() + ".txt"));
    logVectorPair(iteration, {rec->beta_ratio}, {rec->beta_error}, path(region_ + "_betaR_and_Error(" + scaleLabel() + ")" + suffix() + ".txt"));
    logVectorPair(iteration, {rec->gamma_ratio}, {rec->gamma_error}, path(region_ + "_gammaR_and_Error(" + scaleLabel() + ")" + suffix() + ".txt"));
    std::cout << "\n[NM BEST LOG] Iteration " << iteration
              << " Current Best total error = " << total
              << " = FRmean + Corr(" << rec->corr_error << ")"
              << " + Osc [Beta(" << rec->beta_error << ") + Gamma(" << rec->gamma_error << ")]"
              << std::endl;
}

void OptimizationLogger::writeEffectiveConfig(const RuntimeConfig& cfg) const {
    std::ofstream out(path("effective_config.toml"), std::ios::trunc);
    out << effectiveConfigText(cfg);
}

void OptimizationLogger::appendTrajectory(int iteration, const std::vector<double>& params, double total, const std::string& filename) const {
    std::ofstream out(filename, std::ios::app);
    if (!out.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }
    out << iteration << ", " << total;
    for (double p : params) out << ", " << p;
    out << "\n";
}

void OptimizationLogger::logVectorPair(int iteration, const std::vector<double>& values, const std::vector<double>& errors, const std::string& filename) const {
    std::ofstream out(filename, std::ios::app);
    if (!out.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }
    out << iteration;
    for (double v : values) out << " " << v;
    for (double e : errors) out << " " << e;
    out << "\n";
}

std::string OptimizationLogger::path(const std::string& filename) const {
    return (std::filesystem::path(output_dir_) / filename).string();
}

std::string OptimizationLogger::suffix() const {
    return tag_.empty() ? "" : "_" + tag_;
}

std::string OptimizationLogger::scaleLabel() const {
    return "scale" + std::to_string(scale_);
}

void setGlobalOptimizationLogger(OptimizationLogger* logger) {
    g_logger = logger;
}

}  // namespace hippomodel

void logNMBestSoFarFromCpp(int iteration, const std::vector<double>& params, double bestTotal) {
    if (hippomodel::g_logger == nullptr) {
        std::cerr << "[ERROR] Global OptimizationLogger is not set." << std::endl;
        return;
    }
    hippomodel::g_logger->logBestSoFar(iteration, params, bestTotal);
}

void logNMInitialVertexFromCpp(int iteration, const std::vector<double>& params, double total) {
    if (hippomodel::g_logger == nullptr) {
        std::cerr << "[ERROR] Global OptimizationLogger is not set." << std::endl;
        return;
    }
    hippomodel::g_logger->logInitialVertex(iteration, params, total);
}
