#pragma once

#include "hippomodel/config/RuntimeConfig.h"
#include "hippomodel/network/CA3NetworkContext.h"

#include <memory>
#include <vector>

namespace hippomodel::CA3 {

std::unique_ptr<CA3NetworkContext> buildCA3Network(
    const RuntimeConfig& cfg,
    const std::vector<double>& scaling_factors);

void scaleCA3Weights(CA3NetworkContext& ctx, const std::vector<double>& scaling_factors);

}  // namespace hippomodel::CA3
