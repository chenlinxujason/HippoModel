#include "hippomodel/analysis/FiringRate.h"

#include <cmath>
#include <numeric>

namespace hippomodel {

double meanFiringRate(const std::vector<float>& firing_rates) {
    if (firing_rates.empty()) return 0.0;
    return std::accumulate(firing_rates.begin(), firing_rates.end(), 0.0) / static_cast<double>(firing_rates.size());
}

double perNeuronPercentError(const std::vector<float>& rates, double target_hz) {
    if (rates.empty() || target_hz <= 0.0) return 0.0;
    double acc = 0.0;
    for (float x : rates) {
        acc += std::abs(static_cast<double>(x) - target_hz) / target_hz * 100.0;
    }
    return acc / static_cast<double>(rates.size());
}

double firingRatePenalty(double mean, double lower_bound, double upper_bound, double percent_error) {
    if (mean >= lower_bound && mean <= upper_bound) {
        return 0.0;
    }
    return percent_error;
}

}  // namespace hippomodel
