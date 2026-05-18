#pragma once

#include "hippomodel/loss/EvaluationResult.h"
#include "hippomodel/network/DGNetworkContext.h"
#include "hippomodel/optimizer/OptimizationLogger.h"

#include <memory>
#include <vector>

namespace hippomodel::DG {

class DGEvaluator {
public:
    DGEvaluator(std::unique_ptr<DGNetworkContext> context, OptimizationLogger* logger = nullptr);

    double objective(const std::vector<double>& params, bool output = true);
    EvaluationResult lastResult() const { return last_result_; }

private:
    void measureFiringRates(const std::vector<double>& params, bool publish_ei);
    double targetFor(const std::string& group) const;
    std::pair<double, double> boundsFor(const std::string& group) const;

    std::unique_ptr<DGNetworkContext> ctx_;
    OptimizationLogger* logger_ = nullptr;
    EvaluationResult last_result_;

    std::map<std::string, std::vector<float>> firing_rates_;
    std::map<std::string, double> mean_rates_;
};

}  // namespace hippomodel::DG
