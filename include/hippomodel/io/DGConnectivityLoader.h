#pragma once

#include "hippomodel/config/RuntimeConfig.h"
#include "hippomodel/io/ConnectivityData.h"
#include "hippomodel/region/DG/DGRegionSpec.h"

namespace hippomodel::DG {

ConnectivityData loadDGConnectivity(const RuntimeConfig& cfg, const DGRegionSpec& spec);

}  // namespace hippomodel::DG
