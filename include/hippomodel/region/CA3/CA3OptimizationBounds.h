#pragma once

#include <vector>

namespace hippomodel::CA3 {

struct CA3OptimizationBounds {
    std::vector<double> lower;
    std::vector<double> upper;
};

CA3OptimizationBounds makeCA3OptimizationBounds(
    const std::vector<double>& initGuess,
    double lowerScale,
    double upperScale);

}  // namespace hippomodel::CA3
