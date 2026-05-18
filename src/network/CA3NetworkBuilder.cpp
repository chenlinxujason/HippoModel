#include "hippomodel/network/CA3NetworkBuilder.h"

#include "hippomodel/io/CA3ConnectivityLoader.h"
#include "hippomodel/region/CA3/CA3ModelSetup.h"
#include "hippomodel/region/CA3/CA3ConnectionSetup.h"

#include <algorithm>
#include <stdexcept>

namespace hippomodel::CA3 {
namespace {

int carlsimNeuronType(NeuronSign sign) {
    return sign == NeuronSign::Excitatory ? EXCITATORY_NEURON : INHIBITORY_NEURON;
}

std::map<std::string, double> scaleMapFromVector(const CA3RegionSpec& spec, const std::vector<double>& scaling_factors) {
    std::map<std::string, double> out;
    for (size_t i = 0; i < spec.optimized_connection_order.size(); ++i) {
        const double scale = (i < scaling_factors.size()) ? scaling_factors[i] : 1.0;
        out[spec.optimized_connection_order[i]] = scale;
    }
    return out;
}

void updateConnectionWeights(CA3NetworkContext& ctx, const std::map<std::string, double>& scale_by_name) {
    ctx.connection_weights.clear();
    for (const auto& conn : ctx.spec.connections) {
        const auto scale_it = scale_by_name.find(conn.name);
        const double scale = (scale_it == scale_by_name.end()) ? 1.0 : scale_it->second;
        const float abs_weight = static_cast<float>(conn.baseline_weight * scale);
        ctx.connection_weights[conn.pre_group][conn.post_group] = abs_weight;
    }
}

void configureCA3ExternalInput(CA3NetworkContext& ctx, const std::string& group_name) {
    const auto src_it = ctx.config.inputs.sources.find(group_name);
    if (src_it == ctx.config.inputs.sources.end()) {
        throw std::runtime_error("Missing CA3 input source for group: " + group_name);
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
        throw std::runtime_error("Unsupported CA3 input mode for " + group_name + ": " + input.mode);
    }
}

}  // namespace

std::unique_ptr<CA3NetworkContext> buildCA3Network(const RuntimeConfig& cfg, const std::vector<double>& scaling_factors) {
    auto ctx = std::make_unique<CA3NetworkContext>();
    ctx->config = cfg;
    ctx->spec = makeCA3RegionSpec();
    ctx->connectivity = loadCA3Connectivity(cfg, ctx->spec);

    updateConnectionWeights(*ctx, scaleMapFromVector(ctx->spec, scaling_factors));

    ctx->sim = std::make_unique<CARLsim>("CA3_refactor", GPU_MODE, USER, cfg.simulation.num_gpus, cfg.simulation.seed);

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

    configureCA3ExternalInput(*ctx, "EC_LEC");
    configureCA3ExternalInput(*ctx, "EC_MEC");
    configureCA3ExternalInput(*ctx, "DG_GC");

    configureCA3CellModels(*ctx->sim, ctx->group_ids);

    ctx->connection_generator = std::make_unique<CA3ConnectionGenerator>(ctx->spec, ctx->connectivity, ctx->connection_weights);
    ctx->sim->setUserConnectivity(ctx->connectivity.divergence);
    connectCA3Network(*ctx->sim, ctx->connection_generator.get(), ctx->group_ids, ctx->connection_ids);
    for (const auto& conn : ctx->spec.connections) {
        ctx->current_abs_weights[conn.name] = ctx->connection_weights.at(conn.pre_group).at(conn.post_group);
    }

    ctx->sim->setIntegrationMethod(RUNGE_KUTTA4, cfg.simulation.integration_step);
    ctx->sim->setupNetwork();

    for (const auto& kv : ctx->poisson_generators) {
        ctx->sim->setSpikeRate(ctx->group_ids.at(kv.first), kv.second.get());
    }

    const char* spikeOut = cfg.simulation.write_spikes ? "DEFAULT" : "NULL";
    ctx->mon_ca3_pc = ctx->sim->setSpikeMonitor(ctx->group_ids.at("CA3_PC"), spikeOut);
    ctx->mon_ca3_aac = ctx->sim->setSpikeMonitor(ctx->group_ids.at("CA3_AAC"), spikeOut);
    ctx->mon_ca3_bc = ctx->sim->setSpikeMonitor(ctx->group_ids.at("CA3_BC"), spikeOut);
    ctx->mon_ca3_bccck = ctx->sim->setSpikeMonitor(ctx->group_ids.at("CA3_BCCCK"), spikeOut);
    ctx->mon_ca3_bisc = ctx->sim->setSpikeMonitor(ctx->group_ids.at("CA3_BisC"), spikeOut);
    ctx->mon_ca3_mfa = ctx->sim->setSpikeMonitor(ctx->group_ids.at("CA3_MFA"), spikeOut);
    ctx->mon_ca3_olm = ctx->sim->setSpikeMonitor(ctx->group_ids.at("CA3_OLM"), spikeOut);
    ctx->mon_ca3_tl = ctx->sim->setSpikeMonitor(ctx->group_ids.at("CA3_TL"), spikeOut);

    return ctx;
}

void scaleCA3Weights(CA3NetworkContext& ctx, const std::vector<double>& scaling_factors) {
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

}  // namespace hippomodel::CA3
