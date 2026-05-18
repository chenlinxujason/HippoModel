#pragma once

#include "hippomodel/config/RuntimeConfig.h"
#include "hippomodel/io/ConnectivityData.h"
#include "hippomodel/network/CA1ConnectionGenerator.h"
#include "hippomodel/region/CA1/CA1RegionSpec.h"

#include <carlsim.h>
#include <spikegen_from_file.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace hippomodel::CA1 {

struct CA1NetworkContext {
    RuntimeConfig config;
    CA1RegionSpec spec;
    ConnectivityData connectivity;

    std::unique_ptr<CARLsim> sim;
    std::map<std::string, std::unique_ptr<SpikeGeneratorFromFile>> file_generators;
    std::map<std::string, std::unique_ptr<PoissonRate>> poisson_generators;
    std::unique_ptr<CA1ConnectionGenerator> connection_generator;

    std::map<std::string, int> group_ids;
    std::map<std::string, int> connection_ids;
    std::map<std::string, std::map<std::string, float>> connection_weights;
    std::map<std::string, double> current_abs_weights;

    SpikeMonitor* mon_ca1_pc = nullptr;
    SpikeMonitor* mon_ca1_aac = nullptr;
    SpikeMonitor* mon_ca1_bc = nullptr;
    SpikeMonitor* mon_ca1_bccck = nullptr;
    SpikeMonitor* mon_ca1_bisc = nullptr;
    SpikeMonitor* mon_ca1_ng = nullptr;
    SpikeMonitor* mon_ca1_olm = nullptr;
    SpikeMonitor* mon_ca1_tl = nullptr;
};

}  // namespace hippomodel::CA1
