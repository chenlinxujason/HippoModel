//#include <vector>
#include <algorithm>
//#include <functional>
//#include <iostream>
//#include <cmath> 
#include <numeric>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <omp.h> // OpenMP header for parallelization
//#include <iomanip> // setPrecision for 'saveData'
#include "ProgressiveEI.h" // Progressive EI

//#####################
// UPDATEs
//#####################
// This algorithm aims to optimize the difference between function_value and targeted_value, the difference is denoted by 
//'tolerance'. User must define the tolerance in objective function, normally tolerance = abs(function_value -targeted_value)
// and tolerance = 0 is the best case.

//* Each iteration now will involve multiple possible NM operations, including reflection, expansion, contraction, shrinks
//* Take the best value (lowest value) across all operation within one iteration, and use it to plot loss function
//* Use reparameterization method with logistic function to map NM-proposed-unconstraint z-space into constraint x-space. This is standard method for constrained NM optimization (i.e, MATLAB 'fminsearchcon', except MATLAB use sine instead of logistic. Sine is just simple to code and only works for small problem) 
//* It can handle whatever parameter has finite lower and upper bound, one-sided bound, or infinite bounds

//extern bool gIsNMIteration;// = false;  // Set true only when we want to log once per NM iter
//extern bool gIsInitBaseline;// = false;  // Set true only for the single baseline line
//extern int  gNMIterForLog;// = 0;      // which NM-iteration index to stamp into the FR log

extern void logNMBestSoFarFromCpp(
    int iteration,
    const std::vector<double>& params,
    double bestTotal
);

extern void logNMInitialVertexFromCpp(
    int iteration,
    const std::vector<double>& params,
    double total
);

// Default
static const int kEILocalIters_Default = 7;          // EI balancing iteration per NM iter
static const int kMaxEIAttemptsPerLabel_Default = 4; // attempts per lineage (label)

// **Optional: Gradient operation for the 1st vertex
static const int kEILocalIters_FirstNM = 30;         // first NM iter: operate on the first index
static const int kEI_Attempts_FirstNM  = 1;          // first NM iter: 1 attempt only
static const int kEI_FirstLabel        = 0;          // target the original first vertex (label 0)

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

/*
// Function to save data
void saveData(const std::vector<int>& iterations, const std::vector<double>& objectiveValues, const std::vector<std::vector<double>>& parameterTrajectory, const std::string& filename) {
    std::ofstream file(filename);
    //file << std::setprecision(17) << std::scientific; //modify
    for (size_t i = 0; i < iterations.size(); i++) {
        file << iterations[i] << ", " << objectiveValues[i];
        for (double param : parameterTrajectory[i]) {
            file << ", " << param;
        }
        file << "\n";
    }
    file.close();
}
*/

// Function to update best value *per iteration
inline void upd(double f, const std::vector<double>& x,
                double& bestF, std::vector<double>& bestX) {
    if (f < bestF) { bestF = f; bestX = x; }
}

// --- Minimal helpers to fix missing symbols ---

// Find the first index i where labels[i] == targetLabel; return -1 if not found.
static int indexOfLabel(const std::vector<int>& labels, int targetLabel) {
    for (int i = 0; i < static_cast<int>(labels.size()); ++i) {
        if (labels[i] == targetLabel) return i;
    }
    return -1;
}

// Return the index of the worst (largest objective) vertex, skipping skipIdx.
// If everything is skipped (corner case), fall back to the last element.
static int worstRemainingIndex(
    const std::vector<std::pair<std::vector<double>, double>>& simplex_pairs,
    int skipIdx)
{
    int worst = -1;
    double worstVal = -std::numeric_limits<double>::infinity();

    for (int i = 0; i < static_cast<int>(simplex_pairs.size()); ++i) {
        if (i == skipIdx) continue;
        const double v = simplex_pairs[i].second;
        if (worst < 0 || v > worstVal) { worst = i; worstVal = v; }
    }

    if (worst < 0) worst = static_cast<int>(simplex_pairs.size()) - 1; // safe fallback
    return worst;
}


//---------------------------------------------------------
// UPDATE: Function to sort simplex and calculate centroid
//---------------------------------------------------------
void updateSimplexAndCentroid(
    std::vector<std::pair<std::vector<double>, double>>& simplex_pairs,
    std::vector<int>& labels,
    std::vector<double>& centroid)
{

    // --- keep labels in lockstep with simplex size (minimal, robust) ---
    if (labels.size() != simplex_pairs.size()) {
        const size_t old = labels.size();
        labels.resize(simplex_pairs.size());
        // fill/repair labels so we never index out-of-bounds during permutation
        std::iota(labels.begin(), labels.end(), 0);
        std::cout << "[DEBUG] labels resized from " << old
                  << " to " << labels.size() << " to match simplex.\n";
    }
    
    
    // sort ascending by objective while permuting labels in lockstep
    std::vector<size_t> idx(simplex_pairs.size());
    std::iota(idx.begin(), idx.end(), 0);

    std::sort(idx.begin(), idx.end(), [&](size_t a, size_t b){
        return simplex_pairs[a].second < simplex_pairs[b].second;
    });

    std::vector<std::pair<std::vector<double>, double>> sorted(simplex_pairs.size());

    // *** key change: size labels_sorted by simplex_pairs.size(), not labels.size()
    std::vector<int> labels_sorted(simplex_pairs.size());

    for (size_t i = 0; i < idx.size(); ++i) {
        sorted[i]        = std::move(simplex_pairs[idx[i]]);
        labels_sorted[i] = labels[idx[i]];
    }
    simplex_pairs.swap(sorted);
    labels.swap(labels_sorted);

    // centroid of all but worst
    std::fill(centroid.begin(), centroid.end(), 0.0);
    for (size_t i = 0; i + 1 < simplex_pairs.size(); ++i) {
        const auto& z = simplex_pairs[i].first;
        for (size_t j = 0; j < z.size(); ++j) centroid[j] += z[j];
    }
    const double denom = std::max<size_t>(1, simplex_pairs.size() - 1);
    for (size_t j = 0; j < centroid.size(); ++j) centroid[j] /= denom;
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

// ------------------------------------------------------------------
//  Per-coordinate z->x and x->z for sine
// ------------------------------------------------------------------
// z is now constrained logically to [-pi/2, +pi/2]. We clamp softly to avoid
// hitting exact endpoints due to FP noise.

inline double map_z_to_x(double z, double L, double U, BoundType t) {
    switch (t) {
        case BoundType::Boxed: {
            const double eps = 1e-12;
            const double zc  = std::max(-M_PI_2 + eps, std::min(M_PI_2 - eps, z));//when NM go to pi/2, zc stop change - x stop change - f stop change - flat
            // s in [0,1]
            const double s   = (std::sin(zc) + 1.0) * 0.5;// this clamp whenever NM pass pi/2
            //const double s = 1.0 / (1.0 + std::exp(-z));
            return L + (U - L) * s;              // x in [L,U]
        }
        case BoundType::LowerOnly: {
            return L + softplus(z);              // unchanged
        }
        case BoundType::UpperOnly: {
            return U - softplus(z);              // unchanged
        }
        case BoundType::Unbounded: {
            return z;                            // unchanged
        }
        case BoundType::Fixed: {
            return L;                            // unchanged
        }
    }
    return z; // unreachable
}

inline double map_x_to_z(double x, double L, double U, BoundType t) {
    switch (t) {
        case BoundType::Boxed: {
            // w in [0,1], guard FP drift
            const double eps = 1e-12;
            double w = (x - L) / (U - L);
            w = std::max(eps, std::min(1.0 - eps, w));
            // invert: s = 2w-1 in (-1,1) then z = asin(s) in (-pi/2, pi/2)
            const double s = 2.0 * w - 1.0; // (-1,1)
            return std::asin(s);//(-p1/2, p1/2)
        }
        case BoundType::LowerOnly: {
            return inv_softplus(x - L);          // unchanged
        }
        case BoundType::UpperOnly: {
            return inv_softplus(U - x);          // unchanged
        }
        case BoundType::Unbounded: {
            return x;                            // unchanged
        }
        case BoundType::Fixed: {
            return 0.0;                          // unchanged
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
// ------------------------------------------------------------------
//  Per-coordinate z->x and x->z for sine END
// ------------------------------------------------------------------


/*
// ------------------------------------------------------------------
//  Plain clamp mapping (no reparameterization) works
// ------------------------------------------------------------------

inline double map_z_to_x(double z, double L, double U, BoundType t) {
    (void)t; // unused
    // Treat z as x directly and clamp to [L, U] if boxed. 
    // For other bound types, clamp as appropriate.
    if (std::isfinite(L) && std::isfinite(U))
        return std::max(L, std::min(U, z));
    if (std::isfinite(L) && !std::isfinite(U))
        return std::max(L, z);
    if (!std::isfinite(L) && std::isfinite(U))
        return std::min(U, z);
    // Fixed or unbounded
    return (std::isfinite(L) && L == U) ? L : z;
}

inline double map_x_to_z(double x, double, double, BoundType) {
    return x; // identity (no transform)
}

// Vector overloads for clamp mapping
inline std::vector<double> z_to_x_vec(
    const std::vector<double>& z,
    const std::vector<double>& L,
    const std::vector<double>& U,
    const std::vector<BoundType>&)
{
    std::vector<double> x(z.size());
    for (size_t j = 0; j < z.size(); ++j) {
        if (std::isfinite(L[j]) && std::isfinite(U[j]))
            x[j] = std::max(L[j], std::min(U[j], z[j]));
        else if (std::isfinite(L[j]) && !std::isfinite(U[j]))
            x[j] = std::max(L[j], z[j]);
        else if (!std::isfinite(L[j]) && std::isfinite(U[j]))
            x[j] = std::min(U[j], z[j]);
        else
            x[j] = z[j];
    }
    return x;
}

inline std::vector<double> x_to_z_vec(
    const std::vector<double>& x,
    const std::vector<double>&,
    const std::vector<double>&,
    const std::vector<BoundType>&)
{
    return x; // identity (NM runs in x-space directly)
}

// ------------------------------------------------------------------
//  Plain clamp mapping (no reparameterization) END
// ------------------------------------------------------------------

*/


//################################################
// Nelder Mead evaluation
//################################################

std::vector<double> nelderMead(
    const std::function<double(const std::vector<double>&, bool)>& func,
    std::vector<std::vector<double>> simplex,                 // initial vertices in x-space
    const std::vector<double>& lowerBounds,
    const std::vector<double>& upperBounds,
    double tolerance, int maxIterations,
    const std::vector<double>* initObj = nullptr // add
    )
{
    // default parameters
    double alpha = 1.0;
    double gamma = 2.0;
    double rho   = 0.5;
    double sigma = 0.5;
    
    //====================== Add EI target config/state ===========================
    enum class EITargetMode { Best, Fixed };
    
    const EITargetMode eiMode = EITargetMode::Best;   // Choose best vertex for EI operation
    //const EITargetMode eiMode = EITargetMode::Fixed;   // Choose a specific vertex for EI operation
    
    const int eiFixedLabel = 0; // 0 to n+1, we choose 0 (or 1), for EPSP/IPSP Wt

    struct EIState {
        int   targetLabel   = -1;    // label of the currently targeted vertex
        bool  continueSame  = false; // whether to keep targeting same label next NM iter
        bool  acceptedOnce  = false; // whether any EI candidate was ever accepted for this target
        double bestAcceptedF = std::numeric_limits<double>::infinity(); // record for regression logic
    } eiState;
    

    // attempts per original label (lineage)
    std::unordered_map<int,int> eiAttempts;         // label -> {0,1,2}
    // labels that have EI-converged (lock; never re-EI them)
    std::unordered_set<int> eiLocked;               // label set
    // labels that have exhausted attempts without convergence
    std::unordered_set<int> eiExhausted;            // label set

    // Add this for EI-convergence check 

    auto EIWithinBounds = [&](const std::vector<double>& x)->bool {
        return false; // placeholder fallback; treat as "not converged" unless you wire your check
    };
    //=================================================================================

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
    
    // UPDATE: add labels, such that we can target vertices across iterations 
    std::vector<int> labels(simplex_pairs.size());
    std::iota(labels.begin(), labels.end(), 0); // 0..n

    // logs parameters
    /*
    std::vector<int> iterations;
    std::vector<double> objectiveValues;
    std::vector<std::vector<double>> parameterTrajectory;
    */
    
    
    int iteration = 0;
    //int stallCounter = 0; 
    int fevals = 0;
    bool foundOptimal = false;

    // z-space centroid (same dimensionality as x)
    std::vector<double> centroid(simplex[0].size(), 0.0);

    // report best solution in x-space (within the bound)
    double bestObjectiveValue = std::numeric_limits<double>::infinity();
    std::vector<double> bestSolution;
    
    // Add these lines to record 'best-so-far' value and solution
    double runningBest = std::numeric_limits<double>::infinity();
    std::vector<double> runningBestSolution;
    
    // ---------------------------------------------------------------------
    // initial evaluation
    // ---------------------------------------------------------------------
    
    if (iteration == 0) iteration = 1;// only count 1 iteration for initial vertices generation stage
    
    const bool haveInit = (initObj && initObj->size() == simplex_z.size());// Use provided initObj values if present & aligned; otherwise evaluate once.

    for (size_t i = 0; i < simplex_z.size(); ++i) {
        
        std::vector<double> xi = z_to_x_vec(simplex_z[i], lowerBounds, upperBounds, btypes);// Map z -> x and evaluate at bounded x
 
        double fi = 0.0;
        if (haveInit) {
            fi = (*initObj)[i];             // NO evaluation 
        } else {
            fi = func(xi, /*output=*/false);// 1 evaluation 
            fevals++;
        }

        simplex_pairs[i].first = simplex_z[i];  // store z-vertex
        simplex_pairs[i].second = fi;            // store f(x(z))

        std::cout << "Iteration " << iteration << " Evaluate vertex " << (i + 1) << " -> ";
        printVector(xi, fi);
        
        // Initial vertices are logged immediately in the region-specific .cpp during progressive simplex generation.
        //logNMInitialVertexFromCpp(iteration, xi, fi);
        
        //--------------------------------------------------------------------------
        // Log all n+1 vertices as iteration 1
        //--------------------------------------------------------------------------
        
        //if (i == 0) { // i==0 if: if we only want to log vertex[0] instead of every vertices
        
        //saveData(iterations, objectiveValues, parameterTrajectory, "nelder_mead_output(DG,scale10).txt");
        //saveData(iterations, objectiveValues, parameterTrajectory, "nelder_mead_output(DG,scale500)_lowCorr_lowBeta.txt");// Record objective value
        //saveData(iterations, objectiveValues, parameterTrajectory, "nelder_mead_output(CA1,scale10).txt");
        
        //Add code to log firing rate and error per NM iteration using 'gIsNMIteration' sign that defined at the very top of this code
       
       // }//i=0 end

        if (fi < bestObjectiveValue) {
            bestObjectiveValue = fi;
            bestSolution = xi; // store best value *still in x-space
        }
    }

    // Sort & centroid after initialization (in z-space)
    //updateSimplexAndCentroid(simplex_pairs, centroid);//old
    updateSimplexAndCentroid(simplex_pairs, labels, centroid);// update
    bestSolution = z_to_x_vec(simplex_pairs.front().first, lowerBounds, upperBounds, btypes);
    bestObjectiveValue = simplex_pairs.front().second;
    
    // Add this such that 'runningBest' also consider initial simplex
    runningBest = bestObjectiveValue;
    runningBestSolution = bestSolution;
    
    std::cout << "Current Best: ";
    printVector(runningBestSolution, runningBest);

    if (runningBest <= tolerance) {
        std::cout << "Optimal solution found during initial evaluation: " << runningBest << ".\n";
        return runningBestSolution;
    }
    
   
    // =========================== Main NM iteration loop (z-space) ==========================
    while (iteration < maxIterations) {
        // Keep simplex sorted and centroid fresh (z-space)
        //updateSimplexAndCentroid(simplex_pairs, centroid);//old
        updateSimplexAndCentroid(simplex_pairs, labels, centroid);//new


        // Count exactly one NM step per loop
        iteration++;
        std::cout << "---- NM Iteration " << iteration << " ----\n";
       
        // ####################################################################################################
        //**Add GD Operation (EI balancing) based on "ProgressiveEI.h"
        // ####################################################################################################
        
        // Map current simplex vertices (z) into x so EI can work in x-space
        std::vector<std::vector<double>> simplex_x(simplex_pairs.size());
        for (size_t i = 0; i < simplex_pairs.size(); ++i) {
            simplex_x[i] = z_to_x_vec(simplex_pairs[i].first, lowerBounds, upperBounds, btypes);
        }

        
        // --- choose GD Operation target index ---
        int eiIdx = -1;

        // In this codebase:
        // - After init, you set iteration=1
        // - At the top of while-loop you do iteration++
        // So the FIRST NM step after init corresponds to iteration==2.
        const bool isFirstNMStep = (iteration == 2);

        // Per-step EI hyperparameters
        const int localItersThis  = isFirstNMStep ? kEILocalIters_FirstNM : kEILocalIters_Default;
        const int maxAttemptsThis = isFirstNMStep ? kEI_Attempts_FirstNM  : kMaxEIAttemptsPerLabel_Default;

        // -----------------------------
        // First NM step: target the original first vertex (label 0), 1 attempt
        // -----------------------------
        if (isFirstNMStep) {
            eiIdx = indexOfLabel(labels, kEI_FirstLabel);
            if (eiIdx < 0) {
                std::cout << "GD Operation (first NM): label " << kEI_FirstLabel
                          << " not found. Skipping GD Operation this iteration.\n";
            } else {
                eiState.targetLabel   = labels[eiIdx];
                eiState.continueSame  = false;  // no retry on first NM step
                eiState.acceptedOnce  = false;
                eiState.bestAcceptedF = std::numeric_limits<double>::infinity();
            }
        }

        // -----------------------------
        // Normal NM steps: your usual "best eligible + attempts" behavior
        // -----------------------------
        if (!isFirstNMStep) {
            // Pick best eligible (simplex is sorted ascending by objective)
            auto pickBestEligible = [&]()->int {
                for (int i = 0; i < static_cast<int>(labels.size()); ++i) {
                    const int lbl = labels[i];
                    if (eiLocked.count(lbl))    continue;
                    if (eiExhausted.count(lbl)) continue;
                    const int a = (eiAttempts.count(lbl) ? eiAttempts[lbl] : 0);
                    if (a < maxAttemptsThis) return i;
                }
                return -1;
            };

            if (eiState.continueSame && eiState.targetLabel >= 0) {
                int idx = indexOfLabel(labels, eiState.targetLabel);
                if (idx >= 0) {
                    const int a = (eiAttempts.count(eiState.targetLabel) ? eiAttempts[eiState.targetLabel] : 0);
                    if (!eiLocked.count(eiState.targetLabel) &&
                        !eiExhausted.count(eiState.targetLabel) &&
                        a < maxAttemptsThis)
                    {
                        eiIdx = idx; // keep focusing same label
                    }
                }
                if (eiIdx < 0) {
                    // switch lineage
                    eiState.continueSame  = false;
                    eiState.acceptedOnce  = false;
                    eiState.bestAcceptedF = std::numeric_limits<double>::infinity();
                    eiIdx = pickBestEligible();
                }
            } else {
                eiIdx = pickBestEligible();
            }

            if (eiIdx < 0) {
                std::cout << "GD Operation: no eligible vertex (all Locked/Exhausted). Skipping GD Operation this iteration.\n";
            } else {
                eiState.targetLabel = labels[eiIdx];
                if (!eiState.continueSame) {
                    eiState.acceptedOnce  = false;
                    eiState.bestAcceptedF = std::numeric_limits<double>::infinity();
                }
            }
        }

        // -----------------------------
        // Run GD Operation (EI) on chosen vertex
        // -----------------------------
        opt::EIResult ei;
        bool ranEI = false;

        if (eiIdx >= 0) {
            // EI should NOT log FRs
            auto func_quiet = [&](const std::vector<double>& xAbs, bool /*out*/) {
                return func(xAbs, /*output=*/false);
            };

            ei = opt::ProgressiveEI::Run(func_quiet, simplex_x[eiIdx], /*localIters=*/localItersThis);

            std::cout << "GD Operation final candidate (x) -> ";
            printVector(ei.x, ei.f);

            ranEI = true;
        }

        // -----------------------------
        // Acceptance rule:
        // - First NM step: compare to WORST overall (replace if better)
        // - Normal steps: compare to worst-of-remaining (exclude target)
        // -----------------------------
        if (ranEI) {
            int wIdx = -1;

            if (isFirstNMStep) {
                wIdx = static_cast<int>(simplex_pairs.size()) - 1; // worst overall (simplex sorted)
                if (wIdx == eiIdx) {
                    wIdx = worstRemainingIndex(simplex_pairs, eiIdx);
                }
            } else {
                wIdx = worstRemainingIndex(simplex_pairs, eiIdx);
            }

            const double fWorst = simplex_pairs[wIdx].second;

            // attempts++ for this lineage
            int &att = eiAttempts[eiState.targetLabel];
            att = att + 1;

            const bool converged = EIWithinBounds(ei.x);
            if (converged) eiLocked.insert(eiState.targetLabel);

            const bool eiAccepted = (ei.f < fWorst);

            if (eiAccepted) {
                simplex_pairs[wIdx].first  = x_to_z_vec(ei.x, lowerBounds, upperBounds, btypes);
                simplex_pairs[wIdx].second = ei.f;

                updateSimplexAndCentroid(simplex_pairs, labels, centroid);

                eiState.acceptedOnce  = true;
                eiState.bestAcceptedF = std::min(eiState.bestAcceptedF, ei.f);

                if (isFirstNMStep) {
                    eiState.continueSame = false;
                } else {
                    if (converged) {
                        eiState.continueSame = false;
                    } else if (att < maxAttemptsThis) {
                        eiState.continueSame = true;
                    } else {
                        eiExhausted.insert(eiState.targetLabel);
                        eiState.continueSame = false;
                    }
                }

                std::cout << (isFirstNMStep ? "GD Operation (first NM): " : "GD Operation: ")
                          << "accepted vs worst (replaced idx " << wIdx
                          << "), f=" << ei.f << ", attempts=" << att
                          << (converged ? " [CONVERGED]\n" : "\n");
            } else {
                std::cout << (isFirstNMStep ? "GD Operation (first NM): " : "GD Operation: ")
                          << "discarded (f_ei=" << ei.f << " >= worst=" << fWorst
                          << "), attempts=" << att
                          << (converged ? " [CONVERGED]\n" : "\n");

                if (isFirstNMStep) {
                    eiState.continueSame = false;
                } else {
                    if (converged) {
                        eiState.continueSame = false;
                    } else if (att < maxAttemptsThis) {
                        eiState.continueSame = true;
                    } else {
                        eiExhausted.insert(eiState.targetLabel);
                        eiState.continueSame = false;
                    }
                }
            }

            // Enforce "1 attempt only" on first NM step
            if (isFirstNMStep) {
                eiState.continueSame = false;
                if (eiAttempts[eiState.targetLabel] >= kEI_Attempts_FirstNM) {
                    eiExhausted.insert(eiState.targetLabel);
                }
            }
        } else {
            eiState.continueSame = false;
        }

        // ####################################################################################################
        // EI END
        // ####################################################################################################
        
        std::vector<double> z_best  = simplex_pairs.front().first;   
        std::vector<double> z_worst = simplex_pairs.back().first;    
        double f_best  = simplex_pairs.front().second;
        double f_worst = simplex_pairs.back().second;
        double f_2nd   = simplex_pairs[simplex_pairs.size() - 2].second;
 
        // current best before NM
        //std::cout << "Current Best: ";
        //printVector(z_to_x_vec(z_best, lowerBounds, upperBounds, btypes), f_best);

        //logging the best value so far (global min so far) for plot, but not the best value among the operations performed in that iteration.
        //double iterBestValue = f_best; 
        //std::vector<double> iterBestParams = z_to_x_vec(z_best, lowerBounds, upperBounds, btypes);
        
        //logging in the best value per iteration for plot
        double iterBestValue = std::numeric_limits<double>::infinity();
        std::vector<double> iterBestParams;

        //  Reflection 
        std::vector<double> z_ref(centroid.size());
        for (size_t j = 0; j < centroid.size(); ++j)
            z_ref[j] = centroid[j] + alpha * (centroid[j] - z_worst[j]);

        std::vector<double> x_ref = z_to_x_vec(z_ref, lowerBounds, upperBounds, btypes);
        double f_ref = func(x_ref, false);//true
        fevals++;
        upd(f_ref, x_ref, iterBestValue, iterBestParams);//Save reflection value if f_ref is the best value for this NM iteration
        
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
            double f_exp = func(x_exp, false);//true
            fevals++;
            upd(f_exp, x_exp, iterBestValue, iterBestParams);//Save expansion value if f_ref is the best value for this NM iteration
           
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
            //updateSimplexAndCentroid(simplex_pairs, centroid);
            updateSimplexAndCentroid(simplex_pairs, labels, centroid);//update

        } else if (f_ref < f_2nd) {
            // Accept reflection
            simplex_pairs.back() = { z_ref, f_ref };
            //updateSimplexAndCentroid(simplex_pairs, centroid);
            updateSimplexAndCentroid(simplex_pairs, labels, centroid);//update

        } else if (f_ref < f_worst) {
            // Outside Contraction 
            alpha = adjustCoefficient(alpha, f_best, tolerance, /*isImproving*/ (f_ref < f_best));

            std::vector<double> z_con(centroid.size());
            for (size_t j = 0; j < centroid.size(); ++j)
                z_con[j] = centroid[j] + rho * (z_ref[j] - centroid[j]);

            std::vector<double> x_con = z_to_x_vec(z_con, lowerBounds, upperBounds, btypes);
            double f_con = func(x_con, false);//true 
            fevals++;
            upd(f_con, x_con, iterBestValue, iterBestParams);//Save outside contraction value if f_ref is the best value for this NM iteration
            
            if (f_con < iterBestValue) { iterBestValue = f_con; iterBestParams = x_con; }

            std::cout << "Contract(out) -> ";
            printVector(x_con, f_con);

            if (f_con < f_ref) {
                rho = adjustCoefficient(rho, f_best, tolerance, /*isImproving*/ true);
                simplex_pairs.back() = { z_con, f_con };
                //updateSimplexAndCentroid(simplex_pairs, centroid);
                updateSimplexAndCentroid(simplex_pairs, labels, centroid);//update
            } else {
                // Shrink
                rho = adjustCoefficient(rho, f_best, tolerance, /*isImproving*/ false);

                const std::vector<double>& z0 = simplex_pairs[0].first; // best z
                for (size_t i = 1; i < simplex_pairs.size(); ++i) {
                    for (size_t j = 0; j < z0.size(); ++j)
                        simplex_pairs[i].first[j] = z0[j] + sigma * (simplex_pairs[i].first[j] - z0[j]);

                    std::vector<double> xi = z_to_x_vec(simplex_pairs[i].first, lowerBounds, upperBounds, btypes);
                    double fi = func(xi, false); //true 
                    fevals++;
                    simplex_pairs[i].second = fi;
                    upd(fi, xi, iterBestValue, iterBestParams);//Save shrink value if f_ref is the best value for this NM iteration

                    if (simplex_pairs[i].second < iterBestValue) {
                        iterBestValue  = simplex_pairs[i].second;
                        iterBestParams = xi;
                    }
                    std::cout << "Shrink -> ";
                    printVector(xi, simplex_pairs[i].second);
                }
                //updateSimplexAndCentroid(simplex_pairs, centroid);
                updateSimplexAndCentroid(simplex_pairs, labels, centroid);//update
            }

        } else {
            // Inside Contraction
            alpha = adjustCoefficient(alpha, f_best, tolerance, /*isImproving*/ (f_ref < f_best));

            std::vector<double> z_con(centroid.size());
            for (size_t j = 0; j < centroid.size(); ++j)
                z_con[j] = centroid[j] + rho * (z_worst[j] - centroid[j]);

            std::vector<double> x_con = z_to_x_vec(z_con, lowerBounds, upperBounds, btypes);
            double f_con = func(x_con, false);//true 
            fevals++;
            upd(f_con, x_con, iterBestValue, iterBestParams);//Save inside contraction value if f_ref is the best value for this NM iteration
            
            if (f_con < iterBestValue) { iterBestValue = f_con; iterBestParams = x_con; }

            std::cout << "Contract(in)  -> ";
            printVector(x_con, f_con);

            if (f_con < f_worst) {
                rho = adjustCoefficient(rho, f_best, tolerance, /*isImproving*/ true);
                simplex_pairs.back() = { z_con, f_con };
                //updateSimplexAndCentroid(simplex_pairs, centroid);
                updateSimplexAndCentroid(simplex_pairs, labels, centroid);//update
            } else {
                // Shrink
                rho = adjustCoefficient(rho, f_best, tolerance, /*isImproving*/ false);

                const std::vector<double>& z0 = simplex_pairs[0].first; // best z
                for (size_t i = 1; i < simplex_pairs.size(); ++i) {
                    for (size_t j = 0; j < z0.size(); ++j)
                        simplex_pairs[i].first[j] = z0[j] + sigma * (simplex_pairs[i].first[j] - z0[j]);

                    std::vector<double> xi = z_to_x_vec(simplex_pairs[i].first, lowerBounds, upperBounds, btypes);
                    double fi = func(xi, false); //true 
                    fevals++;
                    simplex_pairs[i].second = fi;
                    upd(fi, xi, iterBestValue, iterBestParams);//Save shrink value if f_ref is the best value for this NM iteration

                    if (simplex_pairs[i].second < iterBestValue) {
                        iterBestValue  = simplex_pairs[i].second;
                        iterBestParams = xi;
                    }
                    std::cout << "Shrink -> ";
                    printVector(xi, simplex_pairs[i].second);
                }
                //updateSimplexAndCentroid(simplex_pairs, centroid);
                updateSimplexAndCentroid(simplex_pairs, labels, centroid);//update
            }
        }
              

        // Overall best from the accepted simplex. This is the true NM best-so-far, not a rejected or hidden trial.
        bestSolution = z_to_x_vec(simplex_pairs.front().first, lowerBounds, upperBounds, btypes);
        bestObjectiveValue = simplex_pairs.front().second;

        if (bestObjectiveValue < runningBest) {
            runningBest = bestObjectiveValue;
            runningBestSolution = bestSolution;
        }

        logNMBestSoFarFromCpp(iteration, runningBestSolution, runningBest);

        // Re-evaluate exactly the same candidate that nelder_mead_output records.
        // This makes FR/Corr/Theta/Gamma logs correspond to the same best-so-far solution.
        
        /*
        if (std::isfinite(loggedObjective) &&
            std::fabs(loggedObjective - runningBest) > reevalTol) {
            std::cerr << "[WARN] Re-evaluated objective differs from stored NM best: "
                      << "stored=" << runningBest
                      << ", logged=" << loggedObjective
                      << ". Check simulator determinism/reset behavior." << std::endl;
        }
        */
        //objectiveValues.push_back(loggedObjective);

        //saveData(iterations, objectiveValues, parameterTrajectory, "nelder_mead_output(DG,scale10).txt");
        //saveData(iterations, objectiveValues, parameterTrajectory, "nelder_mead_output(DG,scale500)_lowCorr_lowBeta.txt");// Record objective value
        //saveData(iterations, objectiveValues, parameterTrajectory, "nelder_mead_output(CA1,scale10).txt");

        std::cout << "Current Best: ";
        printVector(runningBestSolution, runningBest);
        //printVector(runningBestSolution, loggedObjective);

        /*
        if (loggedObjective <= tolerance) {
            std::cout << "Reached tolerance after iteration " << iteration
                      << " with objective " << loggedObjective << ".\n";
            return runningBestSolution;
        }
        */
        
        if (runningBest <= tolerance) {
            std::cout << "Reached tolerance after iteration " << iteration
                      << " with objective " << runningBest << ".\n";
            return runningBestSolution;
        }
        
    } // while end

    // Final best solution
    //updateSimplexAndCentroid(simplex_pairs, centroid);
    updateSimplexAndCentroid(simplex_pairs, labels, centroid);//update
    bestSolution = z_to_x_vec(simplex_pairs.front().first, lowerBounds, upperBounds, btypes);
    bestObjectiveValue = simplex_pairs.front().second;

    if (bestObjectiveValue < runningBest) {
        runningBest = bestObjectiveValue;
        runningBestSolution = bestSolution;
    }

    std::cout << "Best Solution Found: ";
    printVector(runningBestSolution, runningBest);
    return runningBestSolution;
}
