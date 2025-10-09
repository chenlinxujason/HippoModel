#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <cmath> 
#include <numeric>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <omp.h> // OpenMP header for parallelization

#include "ProgressiveEI.h" // Progressive EI

static bool gIsNMIteration = false;  // Set true only when we want to log once per NM iter
static bool gIsInitBaseline = false;  // Set true only for the single baseline line
static int  gNMIterForLog = 0; 

// This algorithm aims to optimize the difference between function_value and targeted_value, the difference is denoted by 
//'tolerance'. User must define the tolerance in objective function, normally tolerance = abs(function_value -targeted_value)
// and tolerance = 0 is the best case.

//#####################
// UPDATEs
//#####################

//* Each iteration now will involve multiple possible NM operations, including reflection, expansion, contraction, shrinks
//* Take the best value (lowest value) across all operation within one iteration, and use it to plot loss function
//* Use reparameterization method with logistic function to map NM-proposed-unconstraint z-space into constraint x-space. This is standard method for constrained NM optimization (i.e, MATLAB 'fminsearchcon', except MATLAB use sine instead of logistic. Sine is just simple to code and only works for small problem) 
//* It can handle whatever parameter has finite lower and upper bound, one-sided bound, or infinite bounds

//##########################
// Helper functions
//##########################

// Function to print results
void printVector(const std::vector<double>& vec, double value) {
    for (const auto& v : vec) {
        std::cout << v << " ";
    }
    std::cout << " with Objective: " << value << std::endl;
}

// Function to clip parameters within lower and upper bound
void clip(std::vector<double>& parameters, const std::vector<double>& lowerBounds, const std::vector<double>& upperBounds) {
    for (size_t i = 0; i < parameters.size(); ++i) {
        parameters[i] = std::max(lowerBounds[i], std::min(parameters[i], upperBounds[i]));
    }
}

// Function to save data
void saveData(const std::vector<int>& iterations, const std::vector<double>& objectiveValues, const std::vector<std::vector<double>>& parameterTrajectory, const std::string& filename) {
    std::ofstream file(filename);
    for (size_t i = 0; i < iterations.size(); i++) {
        file << iterations[i] << ", " << objectiveValues[i];
        for (double param : parameterTrajectory[i]) {
            file << ", " << param;
        }
        file << "\n";
    }
    file.close();
}

// Function to sort simplex and calculate centroid
void updateSimplexAndCentroid(
    std::vector<std::pair<std::vector<double>, double>>& simplex_pairs,
    std::vector<double>& centroid)
{
    //std::cout << "Start sorting simplex" << std::endl;
    std::sort(simplex_pairs.begin(), simplex_pairs.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;  // Sort based on the second element of the pairs
        });
    //std::cout << "Finish sorting simplex" << std::endl;

    // Calculate the centroid of all but the worst point
    std::fill(centroid.begin(), centroid.end(), 0.0);
    for (size_t i = 0; i < simplex_pairs.size() - 1; ++i) {
        for (size_t j = 0; j < simplex_pairs[i].first.size(); ++j) {
            centroid[j] += simplex_pairs[i].first[j];
        }
    }
    for (size_t j = 0; j < centroid.size(); ++j) {
        centroid[j] /= (simplex_pairs.size() - 1);
    }
}


// Function to adjuast alpha,gamma,rho,and sigma dynamically based on the proximity to targeted value
double adjustCoefficient(double currentCoefficient, double bestObjectiveValue, double tolerance, bool isImproving) {
    double adjustmentFactor = 1.0;
    double distanceToTolerance = fabs(bestObjectiveValue - tolerance);

    if (!isImproving) {
        if (distanceToTolerance > tolerance * 150) {
            currentCoefficient = currentCoefficient + 0.6;//0.6
            adjustmentFactor = 1.15;
        }

        else if (distanceToTolerance > tolerance * 90 && distanceToTolerance <= tolerance * 150) {
            currentCoefficient = currentCoefficient + 0.3;//0.3
            adjustmentFactor = 1.05;
        }

        else if (distanceToTolerance > tolerance * 30 && distanceToTolerance <= tolerance * 90) {
            currentCoefficient = currentCoefficient + 0.2;//0.2
            adjustmentFactor = 1.0;
        }

        else {  // Close to tolerance, be more conservative
            currentCoefficient = currentCoefficient + 0.1;//0.1
            adjustmentFactor = 0.95;//0.95
        }
    }


    else {
        currentCoefficient = currentCoefficient - 0.3;
        adjustmentFactor = 0.98; // Slow down adjustments if improving,0.98
    }
    return currentCoefficient * adjustmentFactor;
}

//#############################
// Reparameterization
//#############################
// --------------------- Bounds classification ---------------------
enum class BoundType : uint8_t { Unbounded, LowerOnly, UpperOnly, Boxed, Fixed };

inline BoundType classify(double L, double U) {
    const bool hasL = std::isfinite(L);
    const bool hasU = std::isfinite(U);
    if (hasL && hasU) return (L == U) ? BoundType::Fixed : BoundType::Boxed;
    if (hasL && !hasU) return BoundType::LowerOnly;
    if (!hasL && hasU) return BoundType::UpperOnly;
    return BoundType::Unbounded;
}

// --------------------- Stable logistic & softplus ---------------------
inline double sigmoid(double z) {                // logistic in (0,1)
    if (z >= 0) { double ez = std::exp(-z); return 1.0 / (1.0 + ez); }
    double ez = std::exp(z); return ez / (1.0 + ez);
}
inline double logit(double y) {                  // inverse logistic
    const double eps = 1e-12;
    double yc = std::min(1.0 - eps, std::max(eps, y));
    return std::log(yc / (1.0 - yc));
}
inline double softplus(double z) {               // smooth, ≥0
    if (z > 40) return z;                        // avoid exp overflow
    if (z < -40) return std::exp(z);             // ~0 in the far negative
    return std::log1p(std::exp(z));              // log(1+e^z)
}
inline double inv_softplus(double y) {           // inverse of softplus on y>0
    // Solve y = log(1+e^z) → e^y = 1 + e^z → e^z = e^y - 1 → z = log(e^y - 1)
    const double eps = 1e-12;
    double yy = std::max(y, eps);
    if (yy > 40) return yy;                      // ~linear tail
    return std::log(std::exp(yy) - 1.0);
}

// --------------------- Per-coordinate z->x and x->z ---------------------
inline double map_z_to_x(double z, double L, double U, BoundType t) {
    switch (t) {
        case BoundType::Boxed: {
            double s = sigmoid(z);               // (0,1)
            return L + (U - L) * s;              // [L,U]
        }
        case BoundType::LowerOnly: {
            return L + softplus(z);              // [L, +inf)
        }
        case BoundType::UpperOnly: {
            return U - softplus(z);              // (-inf, U]
        }
        case BoundType::Unbounded: {
            return z;                            // (-inf, +inf)
        }
        case BoundType::Fixed: {
            return L;                            // L==U
        }
    }
    return z; // unreachable
}

inline double map_x_to_z(double x, double L, double U, BoundType t) {
    switch (t) {
        case BoundType::Boxed: {
            double w = (x - L) / (U - L);        // expect in [0,1]
            return logit(w);
        }
        case BoundType::LowerOnly: {
            return inv_softplus(x - L);          // x-L >= 0
        }
        case BoundType::UpperOnly: {
            return inv_softplus(U - x);          // U-x >= 0
        }
        case BoundType::Unbounded: {
            return x;
        }
        case BoundType::Fixed: {
            return 0.0;                          // any constant; will be dropped logically
        }
    }
    return x; // unreachable
}

// Vector overloads
inline std::vector<double> z_to_x_vec(
    const std::vector<double>& z,
    const std::vector<double>& L,
    const std::vector<double>& U,
    const std::vector<BoundType>& bt)
{
    std::vector<double> x(z.size());
    for (size_t j = 0; j < z.size(); ++j) x[j] = map_z_to_x(z[j], L[j], U[j], bt[j]);
    return x;
}

inline std::vector<double> x_to_z_vec(
    const std::vector<double>& x,
    const std::vector<double>& L,
    const std::vector<double>& U,
    const std::vector<BoundType>& bt)
{
    std::vector<double> z(x.size());
    for (size_t j = 0; j < x.size(); ++j) z[j] = map_x_to_z(x[j], L[j], U[j], bt[j]);
    return z;
}


//################################################
// Nelder Mead evaluation
//################################################

static const int kEILocalIters = 30;// EI balancing iteration

std::vector<double> nelderMead(
    const std::function<double(const std::vector<double>&, bool)>& func,
    std::vector<std::vector<double>> simplex,                 // initial vertices in x-space
    const std::vector<double>& lowerBounds,
    const std::vector<double>& upperBounds,
    double tolerance, int maxIterations)
{
    // default parameters
    double alpha = 1.0;
    double gamma = 2.0;
    double rho   = 0.5;
    double sigma = 0.5;

    // classify bounds
    std::vector<BoundType> btypes(lowerBounds.size());
    for (size_t j = 0; j < btypes.size(); ++j) {
        btypes[j] = classify(lowerBounds[j], upperBounds[j]);
    }

    // x live within the bound; z live outside the bound (NM operation)
    // build z-simplex from the provided x-simplex ----
    for (auto& v : simplex) clip(v, lowerBounds, upperBounds);//clamp user input once so z_from_x is well-defined
    
    std::vector<std::vector<double>> simplex_z(simplex.size());
    for (size_t i = 0; i < simplex.size(); ++i) {
        simplex_z[i] = x_to_z_vec(simplex[i], lowerBounds, upperBounds, btypes);
    }

    // storage: simplex pairs hold (z-vertex, f(x(z)))
    std::vector<std::pair<std::vector<double>, double>> simplex_pairs(simplex_z.size());

    // logs parameters
    std::vector<int> iterations;
    std::vector<double> objectiveValues;
    std::vector<std::vector<double>> parameterTrajectory;

    int iteration = 0;
    //int stallCounter = 0; 
    int fevals = 0;
    bool foundOptimal = false;

    // z-space centroid (same dimensionality as x)
    std::vector<double> centroid(simplex[0].size(), 0.0);

    // report best solution in x-space (within the bound)
    double bestObjectiveValue = std::numeric_limits<double>::infinity();
    std::vector<double> bestSolution;

    // initial evaluation, only count 1 iteration
    if (iteration == 0) iteration = 1;

    for (size_t i = 0; i < simplex_z.size(); ++i) {
        // Map z -> x and evaluate at bounded x
        std::vector<double> xi = z_to_x_vec(simplex_z[i], lowerBounds, upperBounds, btypes);
        double fi = func(xi, /*count*/ false);
        fevals++;

        simplex_pairs[i].first = simplex_z[i];  // store z-vertex
        simplex_pairs[i].second = fi;            // store f(x(z))

        std::cout << "Iteration " << iteration << " Evaluate vertex " << (i + 1) << " -> ";
        printVector(xi, fi);

        //--------------------------------------------------------------------------
        // Log all n+1 vertices as iteration 1
        //--------------------------------------------------------------------------
        
        //if (i == 0) { // i==0: only record vertice[0] as initial point
        
        iterations.push_back(iteration);
        objectiveValues.push_back(fi);
        parameterTrajectory.push_back(xi);
        saveData(iterations, objectiveValues, parameterTrajectory, "nelder_mead_output.txt");//log objective value
        
        //Add code to log firing rate and error per NM iteration using 'gIsNMIteration' sign that defined at the very top of this code
        gIsNMIteration = true;
        gNMIterForLog  = 1; // ** IMPORTANT: start log firing rate and error and count it as iteration 1
        (void)func(xi, /*output=*/true);
        gIsNMIteration = false;
       
       // }//i=0 end

        if (fi < bestObjectiveValue) {
            bestObjectiveValue = fi;
            bestSolution = xi; // store best value *still in x-space
        }

        if (bestObjectiveValue <= tolerance) {
            std::cout << "Optimal solution found during initial evaluation: " << bestObjectiveValue << ".\n";
            return bestSolution;
        }
    }

    // Sort & centroid after initialization (in z-space)
    updateSimplexAndCentroid(simplex_pairs, centroid);
    bestSolution = z_to_x_vec(simplex_pairs.front().first, lowerBounds, upperBounds, btypes);
    bestObjectiveValue = simplex_pairs.front().second;

    // =========================== Main NM iteration loop (z-space) ==========================
    while (iteration < maxIterations) {
        // Keep simplex sorted and centroid fresh (z-space)
        updateSimplexAndCentroid(simplex_pairs, centroid);

        const std::vector<double>& z_best  = simplex_pairs.front().first;
        const std::vector<double>& z_worst = simplex_pairs.back().first;
        double f_best  = simplex_pairs.front().second;
        double f_worst = simplex_pairs.back().second;
        double f_2nd   = simplex_pairs[simplex_pairs.size() - 2].second;

        // Count exactly one NM step per loop
        iteration++;
        std::cout << "---- NM Iteration " << iteration << " ----\n";
        std::cout << "Current Best: ";
        printVector(z_to_x_vec(z_best, lowerBounds, upperBounds, btypes), f_best);
        
        // ###################################
        //**NO EI balancing
        // ###################################

        // Per-iteration best for the loss plot (one row per NM step)
        double iterBestValue = f_best;
        std::vector<double> iterBestParams = z_to_x_vec(z_best, lowerBounds, upperBounds, btypes);

        //  Reflection 
        std::vector<double> z_ref(centroid.size());
        for (size_t j = 0; j < centroid.size(); ++j)
            z_ref[j] = centroid[j] + alpha * (centroid[j] - z_worst[j]);

        std::vector<double> x_ref = z_to_x_vec(z_ref, lowerBounds, upperBounds, btypes);
        double f_ref = func(x_ref, true); fevals++;
        if (f_ref < iterBestValue) { iterBestValue = f_ref; iterBestParams = x_ref; }

        std::cout << "Reflect -> ";
        printVector(x_ref, f_ref);

        if (f_ref < f_best) {
            //  Expansion
            alpha = adjustCoefficient(alpha, f_best, tolerance, /*isImproving*/ true);

            std::vector<double> z_exp(centroid.size());
            for (size_t j = 0; j < centroid.size(); ++j)
                z_exp[j] = centroid[j] + gamma * (z_ref[j] - centroid[j]);

            std::vector<double> x_exp = z_to_x_vec(z_exp, lowerBounds, upperBounds, btypes);
            double f_exp = func(x_exp, true); fevals++;
            if (f_exp < iterBestValue) { iterBestValue = f_exp; iterBestParams = x_exp; }

            std::cout << "Expand  -> ";
            printVector(x_exp, f_exp);

            if (f_exp < f_ref) {
                gamma = adjustCoefficient(gamma, f_best, tolerance, /*isImproving*/ true);
                simplex_pairs.back() = { z_exp, f_exp };
            } else {
                gamma = adjustCoefficient(gamma, f_best, tolerance, /*isImproving*/ (f_ref < f_best) );
                simplex_pairs.back() = { z_ref, f_ref };
            }
            updateSimplexAndCentroid(simplex_pairs, centroid);

        } else if (f_ref < f_2nd) {
            // Accept reflection
            simplex_pairs.back() = { z_ref, f_ref };
            updateSimplexAndCentroid(simplex_pairs, centroid);

        } else if (f_ref < f_worst) {
            // Outside Contraction 
            alpha = adjustCoefficient(alpha, f_best, tolerance, /*isImproving*/ (f_ref < f_best));

            std::vector<double> z_con(centroid.size());
            for (size_t j = 0; j < centroid.size(); ++j)
                z_con[j] = centroid[j] + rho * (z_ref[j] - centroid[j]);

            std::vector<double> x_con = z_to_x_vec(z_con, lowerBounds, upperBounds, btypes);
            double f_con = func(x_con, true); fevals++;
            if (f_con < iterBestValue) { iterBestValue = f_con; iterBestParams = x_con; }

            std::cout << "Contract(out) -> ";
            printVector(x_con, f_con);

            if (f_con < f_ref) {
                rho = adjustCoefficient(rho, f_best, tolerance, /*isImproving*/ true);
                simplex_pairs.back() = { z_con, f_con };
                updateSimplexAndCentroid(simplex_pairs, centroid);
            } else {
                // Shrink
                rho = adjustCoefficient(rho, f_best, tolerance, /*isImproving*/ false);

                const std::vector<double>& z0 = simplex_pairs[0].first; // best z
                for (size_t i = 1; i < simplex_pairs.size(); ++i) {
                    for (size_t j = 0; j < z0.size(); ++j)
                        simplex_pairs[i].first[j] = z0[j] + sigma * (simplex_pairs[i].first[j] - z0[j]);

                    std::vector<double> xi = z_to_x_vec(simplex_pairs[i].first, lowerBounds, upperBounds, btypes);
                    simplex_pairs[i].second = func(xi, true); fevals++;

                    if (simplex_pairs[i].second < iterBestValue) {
                        iterBestValue  = simplex_pairs[i].second;
                        iterBestParams = xi;
                    }
                    std::cout << "Shrink -> ";
                    printVector(xi, simplex_pairs[i].second);
                }
                updateSimplexAndCentroid(simplex_pairs, centroid);
            }

        } else {
            // Inside Contraction
            alpha = adjustCoefficient(alpha, f_best, tolerance, /*isImproving*/ (f_ref < f_best));

            std::vector<double> z_con(centroid.size());
            for (size_t j = 0; j < centroid.size(); ++j)
                z_con[j] = centroid[j] + rho * (z_worst[j] - centroid[j]);

            std::vector<double> x_con = z_to_x_vec(z_con, lowerBounds, upperBounds, btypes);
            double f_con = func(x_con, true); fevals++;
            if (f_con < iterBestValue) { iterBestValue = f_con; iterBestParams = x_con; }

            std::cout << "Contract(in)  -> ";
            printVector(x_con, f_con);

            if (f_con < f_worst) {
                rho = adjustCoefficient(rho, f_best, tolerance, /*isImproving*/ true);
                simplex_pairs.back() = { z_con, f_con };
                updateSimplexAndCentroid(simplex_pairs, centroid);
            } else {
                // Shrink
                rho = adjustCoefficient(rho, f_best, tolerance, /*isImproving*/ false);

                const std::vector<double>& z0 = simplex_pairs[0].first; // best z
                for (size_t i = 1; i < simplex_pairs.size(); ++i) {
                    for (size_t j = 0; j < z0.size(); ++j)
                        simplex_pairs[i].first[j] = z0[j] + sigma * (simplex_pairs[i].first[j] - z0[j]);

                    std::vector<double> xi = z_to_x_vec(simplex_pairs[i].first, lowerBounds, upperBounds, btypes);
                    simplex_pairs[i].second = func(xi, true); fevals++;

                    if (simplex_pairs[i].second < iterBestValue) {
                        iterBestValue  = simplex_pairs[i].second;
                        iterBestParams = xi;
                    }
                    std::cout << "Shrink -> ";
                    printVector(xi, simplex_pairs[i].second);
                }
                updateSimplexAndCentroid(simplex_pairs, centroid);
            }
        }

        // Overall best from sorted simplex (map z->x for reporting/return)
        bestSolution = z_to_x_vec(simplex_pairs.front().first, lowerBounds, upperBounds, btypes);
        bestObjectiveValue = simplex_pairs.front().second;
        
        //Add code to log firing rate and error per NM iteration using 'gIsNMIteration' sign that defined at the very top of this code
        gIsNMIteration = true;
        gNMIterForLog  = iteration;     // current NM step index
        (void)func(iterBestParams, /*output*/ true);  // logs FR+Error only one time per NM iter, only record the **best value across all operations within each NM iteration
        gIsNMIteration = false;
        
        // iteration END
        iterations.push_back(iteration);
        objectiveValues.push_back(iterBestValue);
        parameterTrajectory.push_back(iterBestParams);
        saveData(iterations, objectiveValues, parameterTrajectory, "nelder_mead_output.txt");

        if (bestObjectiveValue <= tolerance) {
            std::cout << "Reached tolerance after iteration " << iteration << " with objective " << bestObjectiveValue << ".\n";
            return bestSolution;
        }
    } // while end

    // Final best solution
    updateSimplexAndCentroid(simplex_pairs, centroid);
    bestSolution = z_to_x_vec(simplex_pairs.front().first, lowerBounds, upperBounds, btypes);
    bestObjectiveValue = simplex_pairs.front().second;

    std::cout << "Best Solution Found: ";
    printVector(bestSolution, bestObjectiveValue);
    return bestSolution;
}
