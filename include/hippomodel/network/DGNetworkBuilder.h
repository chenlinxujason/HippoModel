#pragma once

#include "hippomodel/config/RuntimeConfig.h"
#include "hippomodel/network/DGNetworkContext.h"

#include <memory>
#include <vector>

namespace hippomodel::DG {

std::unique_ptr<DGNetworkContext> buildDGNetwork(const RuntimeConfig& cfg, const std::vector<double>& scaling_factors);
void scaleDGWeights(DGNetworkContext& ctx, const std::vector<double>& scaling_factors);

}  // namespace hippomodel::DG
