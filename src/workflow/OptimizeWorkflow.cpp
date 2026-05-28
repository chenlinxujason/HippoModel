#include "hippomodel/workflow/OptimizeWorkflow.h"

#include "hippomodel/config/RuntimeConfig.h"
#include "hippomodel/loss/DGEvaluator.h"
#include "hippomodel/loss/CA3Evaluator.h"
#include "hippomodel/loss/CA1Evaluator.h"
#include "hippomodel/network/DGNetworkBuilder.h"
#include "hippomodel/network/CA3NetworkBuilder.h"
#include "hippomodel/network/CA1NetworkBuilder.h"
#include "hippomodel/optimizer/NelderMeadLegacyGD.h"
#include "hippomodel/optimizer/OptimizationLogger.h"
#include "hippomodel/optimizer/ProgressiveEI.h"
#include "hippomodel/optimizer/SimplexGenerator.h"
#include "hippomodel/region/DG/DGOptimizationBounds.h"
#include "hippomodel/region/CA3/CA3OptimizationBounds.h"
#include "hippomodel/region/CA1/CA1OptimizationBounds.h"
#include "hippomodel/user/ProjectSelection.h"
#include "hippomodel/workflow/WorkflowArgs.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace hippomodel {
namespace {


bool startsWith(const std::string& s, const std::string& prefix) {
    return s.size() >= prefix.size() &&
           std::equal(prefix.begin(), prefix.end(), s.begin());
}

int findConnectionIndex(
    const std::vector<std::string>& order,
    const std::string& name)
{
    const auto it = std::find(order.begin(), order.end(), name);
    if (it == order.end()) return -1;
    return static_cast<int>(std::distance(order.begin(), it));
}

std::vector<std::pair<int, int>> makeEcLecMecPairs(
    const std::vector<std::string>& optimizedConnectionOrder)
{
    std::vector<std::pair<int, int>> pairs;

    for (int i = 0; i < static_cast<int>(optimizedConnectionOrder.size()); ++i) {
        const std::string& lecName = optimizedConnectionOrder[i];
        std::string mecName;

        if (startsWith(lecName, "LEC_")) {
            mecName = "MEC_" + lecName.substr(4);
        } else if (startsWith(lecName, "LEC3_")) {
            mecName = "MEC3_" + lecName.substr(5);
        } else {
            continue;
        }

        const int mecIdx = findConnectionIndex(optimizedConnectionOrder, mecName);
        if (mecIdx >= 0) {
            pairs.push_back({i, mecIdx});  // first = LEC/LEC3 index, second = MEC/MEC3 index
        }
    }

    return pairs;
}

template <typename RegionSpecT>
void registerEI(const RegionSpecT& spec, const RuntimeConfig& cfg) {
    for (const auto& reg : spec.ei_registrations) {
        auto bounds = spec.default_fr_bounds.at(reg.neuron_type);
        const auto cfg_it = cfg.firing_rate_bounds.find(reg.neuron_type);
        if (cfg_it != cfg.firing_rate_bounds.end()) {
            bounds = cfg_it->second;
        }
        ::opt::ProgressiveEI::RegisterNeuronType(reg.neuron_type, bounds.first, bounds.second, reg.exc_indices, reg.inh_indices);
    }
}

void saveVerticesToCSV(const std::vector<std::vector<double>>& vertices, const std::string& filename) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Unable to open file " << filename << " for writing." << std::endl;
        return;
    }
    for (const auto& vertex : vertices) {
        for (size_t i = 0; i < vertex.size(); ++i) {
            out << vertex[i];
            if (i + 1 != vertex.size()) out << ",";
        }
        out << "\n";
    }
}

template <typename EvaluatorT>
int runNMForRegion(
    const std::string& regionName,
    RuntimeConfig& cfg,
    EvaluatorT& evaluator,
    const std::vector<double>& initGuess,
    const std::vector<double>& lowerBounds,
    const std::vector<double>& upperBounds,
    const std::vector<std::string>& optimizedConnectionOrder) {

    const auto ecPairs = makeEcLecMecPairs(optimizedConnectionOrder);
    const double EC_PAIR_MAX_RATIO = 1.5;

    ::opt::ProgressiveEI::SelectReferenceVertex(initGuess);

    std::cout << "Running baseline objective at x0 (with FR log as NM iter 1)..." << std::endl;
    const double baselineErr = evaluator.objective(initGuess, false);
    logNMInitialVertexFromCpp(1, initGuess, baselineErr);
    std::cout << "Baseline complete. Error = " << baselineErr << std::endl;

    std::cout << "Generating initial simplex (EI-shift, progressive)..." << std::endl;
    std::vector<std::vector<double>> progressiveSimplex;
    progressiveSimplex.reserve(initGuess.size() + 1);
    progressiveSimplex.push_back(initGuess);

    std::vector<double> initObjValues;
    initObjValues.reserve(initGuess.size() + 1);
    initObjValues.push_back(baselineErr);

    auto initEvaluator = [&evaluator](const std::vector<double>& p, bool) -> double {
        return evaluator.objective(p, false);
    };

    const int numVertices = static_cast<int>(initGuess.size()) + 1;
    for (int v = 1; v < numVertices; ++v) {
        std::vector<std::vector<double>> stepVerts;
        std::vector<double> stepVals;
        opt::generateVerticesGDShift(
            initEvaluator,
            progressiveSimplex,
            static_cast<int>(progressiveSimplex.size()) + 1,
            cfg.simulation.seed + v,
            lowerBounds,
            upperBounds,
            stepVerts,
            stepVals,
            ecPairs,
            EC_PAIR_MAX_RATIO);

        progressiveSimplex.push_back(stepVerts.back());
        initObjValues.push_back(stepVals.back());
        logNMInitialVertexFromCpp(1, progressiveSimplex.back(), initObjValues.back());
    }

    saveVerticesToCSV(progressiveSimplex, cfg.paths.output_dir + "/initialSimplex" + regionName + "_Gradient_Shift.csv");
    std::cout << "Initial simplex generated successfully (Gradient-Shift)." << std::endl;
    std::cout << "Starting SINGLE-thread Nelder-Mead optimization..." << std::endl;

    auto objective = [&evaluator](const std::vector<double>& params, bool output) {
        return evaluator.objective(params, output);
    };

    auto optimizedParams = nelderMead(
        objective,
        progressiveSimplex,
        lowerBounds,
        upperBounds,
        cfg.optimizer.tolerance_percent,
        cfg.optimizer.max_iterations,
        &initObjValues);

    const double bestObjective = objective(optimizedParams, false);
    std::cout << "Optimization finished. Best objective = " << bestObjective << std::endl;
    return 0;
}

}  // namespace

int optimizeWorkflow(int argc, char** argv) {
    try {
        const std::string configPath = parseConfigPath(argc, argv);
        RuntimeConfig cfg = loadRuntimeConfigFromFile(configPath);
        cfg = runtimeConfigForRegion(cfg, toString(user::kSelectedRegion));
        std::filesystem::create_directories(cfg.paths.output_dir);

        std::cout << "Selected region: " << toString(user::kSelectedRegion) << std::endl;
        if constexpr (user::kSelectedRegion == Region::DG) {
            auto spec = DG::makeDGRegionSpec();
            OptimizationLogger logger(cfg.paths.output_dir, "DG", 10);
            logger.reset();
            logger.writeEffectiveConfig(cfg);
            setGlobalOptimizationLogger(&logger);
            registerEI(spec, cfg);

            std::vector<double> initGuess(spec.optimized_connection_order.size(), 1.0);
            const auto bounds = DG::makeDGOptimizationBounds(initGuess, cfg.optimizer.lower_scale, cfg.optimizer.upper_scale);
            auto ctx = DG::buildDGNetwork(cfg, initGuess);
            DG::DGEvaluator evaluator(std::move(ctx), &logger);
            return runNMForRegion("DG", cfg, evaluator, initGuess, bounds.lower, bounds.upper, spec.optimized_connection_order);
        } else if constexpr (user::kSelectedRegion == Region::CA3) {
            auto spec = CA3::makeCA3RegionSpec();
            OptimizationLogger logger(cfg.paths.output_dir, "CA3", 10);
            logger.reset();
            logger.writeEffectiveConfig(cfg);
            setGlobalOptimizationLogger(&logger);
            registerEI(spec, cfg);

            std::vector<double> initGuess(spec.optimized_connection_order.size(), 1.0);
            const auto bounds = CA3::makeCA3OptimizationBounds(initGuess, cfg.optimizer.lower_scale, cfg.optimizer.upper_scale);
            auto ctx = CA3::buildCA3Network(cfg, initGuess);
            CA3::CA3Evaluator evaluator(std::move(ctx), &logger);
            return runNMForRegion("CA3", cfg, evaluator, initGuess, bounds.lower, bounds.upper, spec.optimized_connection_order);
        } else if constexpr (user::kSelectedRegion == Region::CA1) {
            auto spec = CA1::makeCA1RegionSpec();
            OptimizationLogger logger(cfg.paths.output_dir, "CA1", 10);
            logger.reset();
            logger.writeEffectiveConfig(cfg);
            setGlobalOptimizationLogger(&logger);
            registerEI(spec, cfg);

            std::vector<double> initGuess(spec.optimized_connection_order.size(), 1.0);
            const auto bounds = CA1::makeCA1OptimizationBounds(initGuess, cfg.optimizer.lower_scale, cfg.optimizer.upper_scale);
            auto ctx = CA1::buildCA1Network(cfg, initGuess);
            CA1::CA1Evaluator evaluator(std::move(ctx), &logger);
            return runNMForRegion("CA1", cfg, evaluator, initGuess, bounds.lower, bounds.upper, spec.optimized_connection_order);
        }
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "[OPTIMIZE ERROR] " << e.what() << std::endl;
        return 1;
    }
}

}  // namespace hippomodel
