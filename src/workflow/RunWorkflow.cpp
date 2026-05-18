#include "hippomodel/workflow/RunWorkflow.h"

#include "hippomodel/config/RuntimeConfig.h"
#include "hippomodel/network/DGNetworkBuilder.h"
#include "hippomodel/network/CA3NetworkBuilder.h"
#include "hippomodel/network/CA1NetworkBuilder.h"
#include "hippomodel/user/ProjectSelection.h"
#include "hippomodel/workflow/WorkflowArgs.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace hippomodel {
namespace {

std::vector<double> makeRunScales(const std::vector<std::string>& order, const RuntimeConfig& cfg) {
    std::vector<double> scales(order.size(), 1.0);
    for (size_t i = 0; i < order.size(); ++i) {
        const auto it = cfg.run_scaling_factors.find(order[i]);
        if (it != cfg.run_scaling_factors.end()) scales[i] = it->second;
    }
    return scales;
}

void recordAndPrintDG(DG::DGNetworkContext& ctx, const RuntimeConfig& cfg) {
    ctx.sim->runNetwork(cfg.simulation.transient_sec, 0);
    ctx.mon_dg_gc->startRecording(); ctx.mon_dg_mc->startRecording(); ctx.mon_dg_bc->startRecording(); ctx.mon_dg_aac->startRecording();
    ctx.mon_dg_bccck->startRecording(); ctx.mon_dg_hicap->startRecording(); ctx.mon_dg_hipp->startRecording(); ctx.mon_dg_mopp->startRecording(); ctx.mon_dg_tml->startRecording();
    ctx.sim->runNetwork(cfg.simulation.measurement_sec, 0);
    ctx.mon_dg_gc->stopRecording(); ctx.mon_dg_mc->stopRecording(); ctx.mon_dg_bc->stopRecording(); ctx.mon_dg_aac->stopRecording();
    ctx.mon_dg_bccck->stopRecording(); ctx.mon_dg_hicap->stopRecording(); ctx.mon_dg_hipp->stopRecording(); ctx.mon_dg_mopp->stopRecording(); ctx.mon_dg_tml->stopRecording();
    ctx.mon_dg_gc->print(false); ctx.mon_dg_mc->print(false); ctx.mon_dg_bc->print(false); ctx.mon_dg_aac->print(false);
    ctx.mon_dg_bccck->print(false); ctx.mon_dg_hicap->print(false); ctx.mon_dg_hipp->print(false); ctx.mon_dg_mopp->print(false); ctx.mon_dg_tml->print(false);
}

void recordAndPrintCA3(CA3::CA3NetworkContext& ctx, const RuntimeConfig& cfg) {
    ctx.sim->runNetwork(cfg.simulation.transient_sec, 0);
    ctx.mon_ca3_pc->startRecording(); ctx.mon_ca3_aac->startRecording(); ctx.mon_ca3_bc->startRecording(); ctx.mon_ca3_bccck->startRecording();
    ctx.mon_ca3_bisc->startRecording(); ctx.mon_ca3_mfa->startRecording(); ctx.mon_ca3_olm->startRecording(); ctx.mon_ca3_tl->startRecording();
    ctx.sim->runNetwork(cfg.simulation.measurement_sec, 0);
    ctx.mon_ca3_pc->stopRecording(); ctx.mon_ca3_aac->stopRecording(); ctx.mon_ca3_bc->stopRecording(); ctx.mon_ca3_bccck->stopRecording();
    ctx.mon_ca3_bisc->stopRecording(); ctx.mon_ca3_mfa->stopRecording(); ctx.mon_ca3_olm->stopRecording(); ctx.mon_ca3_tl->stopRecording();
    ctx.mon_ca3_pc->print(false); ctx.mon_ca3_aac->print(false); ctx.mon_ca3_bc->print(false); ctx.mon_ca3_bccck->print(false);
    ctx.mon_ca3_bisc->print(false); ctx.mon_ca3_mfa->print(false); ctx.mon_ca3_olm->print(false); ctx.mon_ca3_tl->print(false);
}

void recordAndPrintCA1(CA1::CA1NetworkContext& ctx, const RuntimeConfig& cfg) {
    ctx.sim->runNetwork(cfg.simulation.transient_sec, 0);
    ctx.mon_ca1_pc->startRecording(); ctx.mon_ca1_aac->startRecording(); ctx.mon_ca1_bc->startRecording(); ctx.mon_ca1_bccck->startRecording();
    ctx.mon_ca1_bisc->startRecording(); ctx.mon_ca1_ng->startRecording(); ctx.mon_ca1_olm->startRecording(); ctx.mon_ca1_tl->startRecording();
    ctx.sim->runNetwork(cfg.simulation.measurement_sec, 0);
    ctx.mon_ca1_pc->stopRecording(); ctx.mon_ca1_aac->stopRecording(); ctx.mon_ca1_bc->stopRecording(); ctx.mon_ca1_bccck->stopRecording();
    ctx.mon_ca1_bisc->stopRecording(); ctx.mon_ca1_ng->stopRecording(); ctx.mon_ca1_olm->stopRecording(); ctx.mon_ca1_tl->stopRecording();
    ctx.mon_ca1_pc->print(false); ctx.mon_ca1_aac->print(false); ctx.mon_ca1_bc->print(false); ctx.mon_ca1_bccck->print(false);
    ctx.mon_ca1_bisc->print(false); ctx.mon_ca1_ng->print(false); ctx.mon_ca1_olm->print(false); ctx.mon_ca1_tl->print(false);
}

}  // namespace

int runWorkflow(int argc, char** argv) {
    try {
        const std::string configPath = parseConfigPath(argc, argv);
        RuntimeConfig cfg = loadRuntimeConfigFromFile(configPath);
        cfg = runtimeConfigForRegion(cfg, toString(user::kSelectedRegion));
        std::filesystem::create_directories(cfg.paths.output_dir);
        std::ofstream(cfg.paths.output_dir + "/effective_config.toml") << effectiveConfigText(cfg);

        std::cout << "Selected region: " << toString(user::kSelectedRegion) << std::endl;
        if constexpr (user::kSelectedRegion == Region::DG) {
            auto spec = DG::makeDGRegionSpec();
            auto ctx = DG::buildDGNetwork(cfg, makeRunScales(spec.optimized_connection_order, cfg));
            recordAndPrintDG(*ctx, cfg);
            return 0;
        } else if constexpr (user::kSelectedRegion == Region::CA3) {
            auto spec = CA3::makeCA3RegionSpec();
            auto ctx = CA3::buildCA3Network(cfg, makeRunScales(spec.optimized_connection_order, cfg));
            recordAndPrintCA3(*ctx, cfg);
            return 0;
        } else if constexpr (user::kSelectedRegion == Region::CA1) {
            auto spec = CA1::makeCA1RegionSpec();
            auto ctx = CA1::buildCA1Network(cfg, makeRunScales(spec.optimized_connection_order, cfg));
            recordAndPrintCA1(*ctx, cfg);
            return 0;
        }
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "[RUN ERROR] " << e.what() << std::endl;
        return 1;
    }
}

}  // namespace hippomodel
