#include "hippomodel/network/DGNetworkBuilder.h"

#include "hippomodel/io/DGConnectivityLoader.h"
#include "hippomodel/region/DG/DGModelSetup.h"
#include "hippomodel/region/DG/DGConnectionSetup.h"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <stdexcept>

namespace hippomodel::DG {
namespace {

int carlsimNeuronType(NeuronSign sign) {
    return sign == NeuronSign::Excitatory ? EXCITATORY_NEURON : INHIBITORY_NEURON;
}

std::map<std::string, double> scaleMapFromVector(const DGRegionSpec& spec, const std::vector<double>& scaling_factors) {
    std::map<std::string, double> out;
    for (size_t i = 0; i < spec.optimized_connection_order.size(); ++i) {
        const double scale = (i < scaling_factors.size()) ? scaling_factors[i] : 1.0;
        out[spec.optimized_connection_order[i]] = scale;
    }
    return out;
}

void updateConnectionWeights(DGNetworkContext& ctx, const std::map<std::string, double>& scale_by_name) {
    ctx.connection_weights.clear();
    for (const auto& conn : ctx.spec.connections) {
        const auto scale_it = scale_by_name.find(conn.name);
        const double scale = (scale_it == scale_by_name.end()) ? 1.0 : scale_it->second;
        const float abs_weight = static_cast<float>(conn.baseline_weight * scale);
        ctx.connection_weights[conn.pre_group][conn.post_group] = abs_weight;
    }
}

void configureDGExternalInput(DGNetworkContext& ctx, const std::string& group_name) {
    const auto src_it = ctx.config.inputs.sources.find(group_name);
    if (src_it == ctx.config.inputs.sources.end()) {
        throw std::runtime_error("Missing DG input source for group: " + group_name);
    }

    const int group_id = ctx.group_ids.at(group_name);
    const int n = static_cast<int>(ctx.connectivity.loc_x.at(group_name).size());
    const auto& input = src_it->second;

    if (input.mode == "file") {
        auto generator = std::make_unique<SpikeGeneratorFromFile>(input.file);
        ctx.sim->setSpikeGenerator(group_id, generator.get());
        ctx.file_generators[group_name] = std::move(generator);
    } else if (input.mode == "poisson") {
        auto generator = std::make_unique<PoissonRate>(n);
        generator->setRates(static_cast<float>(input.rate_hz));
        ctx.poisson_generators[group_name] = std::move(generator);
    } else {
        throw std::runtime_error("Unsupported DG input mode for " + group_name + ": " + input.mode);
    }
}

}  // namespace

std::unique_ptr<DGNetworkContext> buildDGNetwork(const RuntimeConfig& cfg, const std::vector<double>& scaling_factors) {
    auto ctx = std::make_unique<DGNetworkContext>();
    ctx->config = cfg;
    ctx->spec = makeDGRegionSpec();
    ctx->connectivity = loadDGConnectivity(cfg, ctx->spec);

    updateConnectionWeights(*ctx, scaleMapFromVector(ctx->spec, scaling_factors));

    ctx->sim = std::make_unique<CARLsim>("DG_refactor", GPU_MODE, USER, cfg.simulation.num_gpus, cfg.simulation.seed);

    for (const auto& group : ctx->spec.groups) {
        int gid = -1;
        const int n = static_cast<int>(ctx->connectivity.loc_x.at(group.name).size());
        if (group.spike_generator) {
            gid = ctx->sim->createSpikeGeneratorGroup(group.name, n, carlsimNeuronType(group.sign));
        } else {
            gid = ctx->sim->createGroup(group.name, n, carlsimNeuronType(group.sign));
        }
        ctx->group_ids[group.name] = gid;
    }

    configureDGExternalInput(*ctx, "EC_LEC");
    configureDGExternalInput(*ctx, "EC_MEC");

    // Keep DG cell-model setup in the same explicit CARLsim style as the original code:
    // direct sim.setConductances(...) and sim.setNeuronParameters(...) calls.
    configureDGCellModels(*ctx->sim, ctx->group_ids);

    ctx->connection_generator = std::make_unique<DGConnectionGenerator>(ctx->spec, ctx->connectivity, ctx->connection_weights);
    ctx->sim->setUserConnectivity(ctx->connectivity.divergence);

    // Keep DG connection setup in the same explicit CARLsim style as the original loadConnectivityDG_opt_div.h:
    // named connectionIDs[...] = sim.connect(...).
    connectDGNetwork(*ctx->sim, ctx->connection_generator.get(), ctx->group_ids, ctx->connection_ids);
    for (const auto& conn : ctx->spec.connections) {
        ctx->current_abs_weights[conn.name] = ctx->connection_weights.at(conn.pre_group).at(conn.post_group);
    }

    ctx->sim->setIntegrationMethod(RUNGE_KUTTA4, cfg.simulation.integration_step);
    ctx->sim->setupNetwork();

    for (const auto& kv : ctx->poisson_generators) {
        ctx->sim->setSpikeRate(ctx->group_ids.at(kv.first), kv.second.get());
    }

    const char* spikeOut = cfg.simulation.write_spikes ? "DEFAULT" : "NULL";
    ctx->mon_mec = ctx->sim->setSpikeMonitor(ctx->group_ids.at("EC_MEC"), spikeOut);
    ctx->mon_lec = ctx->sim->setSpikeMonitor(ctx->group_ids.at("EC_LEC"), spikeOut);
    ctx->mon_dg_gc = ctx->sim->setSpikeMonitor(ctx->group_ids.at("DG_GC"), spikeOut);
    ctx->mon_dg_mc = ctx->sim->setSpikeMonitor(ctx->group_ids.at("DG_MC"), spikeOut);
    ctx->mon_dg_aac = ctx->sim->setSpikeMonitor(ctx->group_ids.at("DG_AAC"), spikeOut);
    ctx->mon_dg_bc = ctx->sim->setSpikeMonitor(ctx->group_ids.at("DG_BC"), spikeOut);
    ctx->mon_dg_bccck = ctx->sim->setSpikeMonitor(ctx->group_ids.at("DG_BCCCK"), spikeOut);
    ctx->mon_dg_hicap = ctx->sim->setSpikeMonitor(ctx->group_ids.at("DG_HICAP"), spikeOut);
    ctx->mon_dg_hipp = ctx->sim->setSpikeMonitor(ctx->group_ids.at("DG_HIPP"), spikeOut);
    ctx->mon_dg_mopp = ctx->sim->setSpikeMonitor(ctx->group_ids.at("DG_MOPP"), spikeOut);
    ctx->mon_dg_tml = ctx->sim->setSpikeMonitor(ctx->group_ids.at("DG_TML"), spikeOut);

    return ctx;
}

void scaleDGWeights(DGNetworkContext& ctx, const std::vector<double>& scaling_factors) {
    for (size_t i = 0; i < ctx.spec.optimized_connection_order.size(); ++i) {
        const std::string& name = ctx.spec.optimized_connection_order[i];
        const double scale = (i < scaling_factors.size()) ? scaling_factors[i] : 1.0;

        const auto conn_it = std::find_if(ctx.spec.connections.begin(), ctx.spec.connections.end(),
            [&](const ConnectionSpec& c) { return c.name == name; });
        if (conn_it == ctx.spec.connections.end()) continue;

        const double target_abs = conn_it->baseline_weight * scale;
        const double current_abs = ctx.current_abs_weights[name];
        const double ratio = (current_abs == 0.0) ? 0.0 : target_abs / current_abs;
        ctx.sim->scaleWeights(ctx.connection_ids.at(name), ratio, true);
        ctx.current_abs_weights[name] = target_abs;
    }
}

}  // namespace hippomodel::DG
