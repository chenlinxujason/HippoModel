#pragma once

#include "hippomodel/config/RuntimeConfig.h"
#include "hippomodel/io/ConnectivityData.h"
#include "hippomodel/region/CA3/CA3RegionSpec.h"

namespace hippomodel::CA3 {

ConnectivityData loadCA3Connectivity(const RuntimeConfig& cfg, const CA3RegionSpec& spec);

}  // namespace hippomodel::CA3
