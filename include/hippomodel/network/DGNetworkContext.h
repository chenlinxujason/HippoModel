#pragma once

#include "hippomodel/config/RuntimeConfig.h"
#include "hippomodel/io/ConnectivityData.h"
#include "hippomodel/network/DGConnectionGenerator.h"
#include "hippomodel/region/DG/DGRegionSpec.h"

#include <carlsim.h>
#include <spikegen_from_file.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace hippomodel::DG {

struct DGNetworkContext {
    RuntimeConfig config;
    DGRegionSpec spec;
    ConnectivityData connectivity;

    std::unique_ptr<CARLsim> sim;
    std::map<std::string, std::unique_ptr<SpikeGeneratorFromFile>> file_generators;
    std::map<std::string, std::unique_ptr<PoissonRate>> poisson_generators;
    std::unique_ptr<DGConnectionGenerator> connection_generator;

    std::map<std::string, int> group_ids;
    std::map<std::string, int> connection_ids;
    std::map<std::string, std::map<std::string, float>> connection_weights;
    std::map<std::string, double> current_abs_weights;

    SpikeMonitor* mon_mec = nullptr;
    SpikeMonitor* mon_lec = nullptr;
    SpikeMonitor* mon_dg_gc = nullptr;
    SpikeMonitor* mon_dg_mc = nullptr;
    SpikeMonitor* mon_dg_aac = nullptr;
    SpikeMonitor* mon_dg_bc = nullptr;
    SpikeMonitor* mon_dg_bccck = nullptr;
    SpikeMonitor* mon_dg_hicap = nullptr;
    SpikeMonitor* mon_dg_hipp = nullptr;
    SpikeMonitor* mon_dg_mopp = nullptr;
    SpikeMonitor* mon_dg_tml = nullptr;
};

}  // namespace hippomodel::DG
