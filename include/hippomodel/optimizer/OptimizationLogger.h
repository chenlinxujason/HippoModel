#pragma once

#include "hippomodel/config/RuntimeConfig.h"
#include "hippomodel/loss/EvaluationResult.h"

#include <string>
#include <vector>

namespace hippomodel {

class OptimizationLogger {
public:
    OptimizationLogger(std::string output_dir, std::string region, int scale, std::string tag = "");

    void reset();
    void cache(const EvaluationResult& result);
    void logInitialVertex(int iteration, const std::vector<double>& params, double total);
    void logBestSoFar(int iteration, const std::vector<double>& params, double total);
    void writeEffectiveConfig(const RuntimeConfig& cfg) const;

private:
    const EvaluationResult* findCached(const std::vector<double>& params, double total) const;
    void appendTrajectory(int iteration, const std::vector<double>& params, double total, const std::string& filename) const;
    void logVectorPair(int iteration, const std::vector<double>& values, const std::vector<double>& errors, const std::string& filename) const;
    std::string path(const std::string& filename) const;
    std::string suffix() const;
    std::string scaleLabel() const;

    std::string output_dir_;
    std::string region_;
    int scale_ = 10;
    std::string tag_;
    std::vector<EvaluationResult> cache_;
};

void setGlobalOptimizationLogger(OptimizationLogger* logger);

}  // namespace hippomodel

// Required by the legacy Nelder-Mead header.
void logNMBestSoFarFromCpp(int iteration, const std::vector<double>& params, double bestTotal);
void logNMInitialVertexFromCpp(int iteration, const std::vector<double>& params, double total);
