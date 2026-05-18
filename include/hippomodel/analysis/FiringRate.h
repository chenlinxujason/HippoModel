#pragma once

#include <vector>

namespace hippomodel {

double meanFiringRate(const std::vector<float>& firing_rates);
double perNeuronPercentError(const std::vector<float>& rates, double target_hz);
double firingRatePenalty(double mean, double lower_bound, double upper_bound, double percent_error);

}  // namespace hippomodel
