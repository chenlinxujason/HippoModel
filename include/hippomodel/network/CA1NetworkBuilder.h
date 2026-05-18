#pragma once

#include "hippomodel/config/RuntimeConfig.h"
#include "hippomodel/network/CA1NetworkContext.h"

#include <memory>
#include <vector>

namespace hippomodel::CA1 {

std::unique_ptr<CA1NetworkContext> buildCA1Network(
    const RuntimeConfig& cfg,
    const std::vector<double>& scaling_factors);

void scaleCA1Weights(CA1NetworkContext& ctx, const std::vector<double>& scaling_factors);

}  // namespace hippomodel::CA1
