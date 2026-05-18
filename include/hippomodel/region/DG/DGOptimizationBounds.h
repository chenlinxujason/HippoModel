#pragma once

#include <vector>

namespace hippomodel::DG {

struct OptimizationBounds {
    std::vector<double> lower;
    std::vector<double> upper;
};

OptimizationBounds makeDGOptimizationBounds(const std::vector<double>& initGuess,
                                            double lowerScale,
                                            double upperScale);

}  // namespace hippomodel::DG
