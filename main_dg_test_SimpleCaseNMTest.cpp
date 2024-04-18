
#include <carlsim.h> // include CARLsim user interface
#include <boost/iterator/counting_iterator.hpp>
#include <ctime>
#include <cstdlib>
#include <spikegen_from_file.h>
#include <stopwatch.h>
#include <map>
#include "../Nelder_Mead_Opt.h"// 

#include <spikegen_from_file.h>
#include <carlsim.h>
#include <stopwatch.h>

double tolerance = 0.01; // Tolerance for stopping criterion
int maxIterations = 200; // Maximum number of iterations

double clip(double value, double lowerBound, double upperBound) {
    double clipped = std::max(lowerBound, std::min(value, upperBound));
    return (clipped <= lowerBound) ? lowerBound + std::numeric_limits<double>::epsilon() : clipped;
}

double objectiveFunction(const std::vector<double>& params, bool output = true) {
     static std::random_device rd;
     static std::mt19937 gen(rd());
     static std::normal_distribution<> noise(0, 1); // Mean 0, standard deviation 1

     if (params.size() < 2) {
        std::cerr << "Error: Booth function requires two parameters." << std::endl;
        return std::numeric_limits<double>::max();
    }

    double x = params[0];
    double y = params[1];
    double result = std::pow(x + 2*y - 7, 2) + std::pow(2*x + y - 5, 2);
    result += noise(gen);

    if (output) {
        std::cout << "Evaluating at (x, y) = (" << x << ", " << y << ") yields function value = " << result << std::endl;
    }
    return result;
}

// Outputs both scaled factors and their effective weights given the baseline
void printOptimizedParameters(const std::vector<double>& optimizedParams, const float baselineWts[]) {
    std::cout << "Optimized Scaling Factors: ";
    for (auto& scale : optimizedParams) {
        std::cout << scale << " ";
    }
    std::cout << std::endl;

    std::cout << "Optimized Weights: ";
    for (int i = 0; i < optimizedParams.size(); ++i) {
        std::cout << (baselineWts[i] * optimizedParams[i]) << " ";
    }
    std::cout << std::endl;
}

int main() {

     std::vector<std::vector<double>> initialSimplex = {
        {100.0, 200.0},   // Near the known minimum (1,3)
        {0.0, 0.0},   // Another guess
        {0.1, 7.0}    // And another guess
    };

    std::vector<double> optimizedParams = nelderMead(objectiveFunction, initialSimplex, tolerance, maxIterations);

    std::cout << "Optimized x: " << optimizedParams[0] << std::endl;
    std::cout << "Optimized y: " << optimizedParams[1] << std::endl; // Should be close to 4
    //std::cout << "Calculated y: " << 2 * optimizedParams[0] << std::endl; // Should be close to 4

    return 0;
}
