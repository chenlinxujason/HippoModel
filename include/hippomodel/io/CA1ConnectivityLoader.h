#pragma once

#include "hippomodel/config/RuntimeConfig.h"
#include "hippomodel/io/ConnectivityData.h"
#include "hippomodel/region/CA1/CA1RegionSpec.h"

namespace hippomodel::CA1 {

ConnectivityData loadCA1Connectivity(const RuntimeConfig& cfg, const CA1RegionSpec& spec);

}  // namespace hippomodel::CA1
