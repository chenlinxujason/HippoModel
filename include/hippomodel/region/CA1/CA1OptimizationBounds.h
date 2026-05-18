#pragma once

#include <vector>

namespace hippomodel::CA1 {

struct CA1OptimizationBounds {
    std::vector<double> lower;
    std::vector<double> upper;
};

CA1OptimizationBounds makeCA1OptimizationBounds(
    const std::vector<double>& initGuess,
    double lowerScale,
    double upperScale);

}  // namespace hippomodel::CA1
