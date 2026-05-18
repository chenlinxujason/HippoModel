#pragma once

#include <map>
#include <string>
#include <vector>

namespace hippomodel {

struct EvaluationResult {
    std::vector<double> params;
    double total_loss = 0.0;

    std::map<std::string, double> mean_firing_rates;
    std::map<std::string, double> firing_rate_errors;
    std::vector<double> ordered_mean_firing_rates;
    std::vector<double> ordered_firing_rate_errors;

    double corr_mean_abs = 0.0;
    double corr_error = 0.0;

    double theta_ratio = 0.0;
    double theta_error = 0.0;
    double beta_ratio = 0.0;
    double beta_error = 0.0;
    double gamma_ratio = 0.0;
    double gamma_error = 0.0;
    double two_hz_ratio = 0.0;
    double two_hz_error = 0.0;
};

}  // namespace hippomodel
