#pragma once

#include "hippomodel/loss/EvaluationResult.h"
#include "hippomodel/network/CA3NetworkContext.h"
#include "hippomodel/optimizer/OptimizationLogger.h"

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace hippomodel::CA3 {

class CA3Evaluator {
public:
    explicit CA3Evaluator(std::unique_ptr<CA3NetworkContext> context, OptimizationLogger* logger = nullptr);

    double objective(const std::vector<double>& params, bool output);
    const EvaluationResult& lastResult() const { return last_result_; }

private:
    double targetFor(const std::string& group) const;
    std::pair<double, double> boundsFor(const std::string& group) const;
    void measureFiringRates(const std::vector<double>& params, bool publish_ei);

    std::unique_ptr<CA3NetworkContext> ctx_;
    OptimizationLogger* logger_ = nullptr;
    std::map<std::string, std::vector<float>> firing_rates_;
    std::map<std::string, double> mean_rates_;
    EvaluationResult last_result_;
};

}  // namespace hippomodel::CA3
