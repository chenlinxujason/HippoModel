#pragma once

#include "hippomodel/config/RuntimeConfig.h"
#include "hippomodel/io/ConnectivityData.h"
#include "hippomodel/network/CA3ConnectionGenerator.h"
#include "hippomodel/region/CA3/CA3RegionSpec.h"

#include <carlsim.h>
#include <spikegen_from_file.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace hippomodel::CA3 {

struct CA3NetworkContext {
    RuntimeConfig config;
    CA3RegionSpec spec;
    ConnectivityData connectivity;

    std::unique_ptr<CARLsim> sim;
    std::map<std::string, std::unique_ptr<SpikeGeneratorFromFile>> file_generators;
    std::map<std::string, std::unique_ptr<PoissonRate>> poisson_generators;
    std::unique_ptr<CA3ConnectionGenerator> connection_generator;

    std::map<std::string, int> group_ids;
    std::map<std::string, int> connection_ids;
    std::map<std::string, std::map<std::string, float>> connection_weights;
    std::map<std::string, double> current_abs_weights;

    SpikeMonitor* mon_ca3_pc = nullptr;
    SpikeMonitor* mon_ca3_aac = nullptr;
    SpikeMonitor* mon_ca3_bc = nullptr;
    SpikeMonitor* mon_ca3_bccck = nullptr;
    SpikeMonitor* mon_ca3_bisc = nullptr;
    SpikeMonitor* mon_ca3_mfa = nullptr;
    SpikeMonitor* mon_ca3_olm = nullptr;
    SpikeMonitor* mon_ca3_tl = nullptr;
};

}  // namespace hippomodel::CA3
