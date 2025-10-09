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

#include "ProgressiveEI.h" // Progressive EI


static bool gIsNMIteration = false;  // Set true only when we want to log once per NM iter
static bool gIsInitBaseline = false;  // Set true only for the single baseline line
static int  gNMIterForLog = 0;      // which NM-iteration index to stamp into the FR log

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

//----------------------------------------------------------
// Add helper function 
//----------------------------------------------------------
inline int indexOfLabel(const std::vector<int>& labels, int lbl) {
    for (size_t i = 0; i < labels.size(); ++i) if (labels[i] == lbl) return static_cast<int>(i);
    return -1;
}

inline int worstRemainingIndex(const std::vector<std::pair<std::vector<double>,double>>& sp,
                               int excludeIdx)
{
    int w = -1; double bestW = -std::numeric_limits<double>::infinity();
    for (int i = 0; i < static_cast<int>(sp.size()); ++i) {
        if (i == excludeIdx) continue;
        if (sp[i].second > bestW) { bestW = sp[i].second; w = i; }
    }
    return (w >= 0) ? w : static_cast<int>(sp.size()) - 1;
}


//################################################
// Nelder Mead evaluation
//################################################

static const int kEILocalIters = 30;// EI balancing iteration, 30; I can change to 20

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
    
    
    static const int kMaxEIAttemptsPerLabel = 2;// Maximal EI attempt per NM iteration

    // attempts per original label (lineage)
    std::unordered_map<int,int> eiAttempts;         // label -> {0,1,2}
    // labels that have EI-converged (lock; never re-EI them)
    std::unordered_set<int> eiLocked;               // label set
    // labels that have exhausted attempts without convergence
    std::unordered_set<int> eiExhausted;            // label set

    // --- NEW: tiny shim for EI-convergence check (replace with your real check) ---
    // If your ProgressiveEI already exposes a convergence predicate, call it here instead.
    auto EIWithinBounds = [&](const std::vector<double>& x)->bool {
        // TODO: replace with your real convergence/within-bounds check
        // e.g., return opt::ProgressiveEI::WithinBounds(x);
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

    // ---------------------------------------------------------------------
    // initial evaluation, only count 1 iteration
    // ---------------------------------------------------------------------
    
    if (iteration == 0) iteration = 1;

    for (size_t i = 0; i < simplex_z.size(); ++i) {
        
        std::vector<double> xi = z_to_x_vec(simplex_z[i], lowerBounds, upperBounds, btypes);// Map z -> x and evaluate at bounded x
        
        //double fi = func(xi, /*count*/ false);
        
        double fi;
        if (initObj && initObj->size() == simplex_z.size()) {
            fi = (*initObj)[i];
       } else {
            fi = func(xi, /*count*/false);// NO Firing rate log
       }
        
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
    //updateSimplexAndCentroid(simplex_pairs, centroid);//old
    updateSimplexAndCentroid(simplex_pairs, labels, centroid);// update
    bestSolution = z_to_x_vec(simplex_pairs.front().first, lowerBounds, upperBounds, btypes);
    bestObjectiveValue = simplex_pairs.front().second;
    
    

    // =========================== Main NM iteration loop (z-space) ==========================
    while (iteration < maxIterations) {
        // Keep simplex sorted and centroid fresh (z-space)
        //updateSimplexAndCentroid(simplex_pairs, centroid);//old
        updateSimplexAndCentroid(simplex_pairs, labels, centroid);//new


       // const std::vector<double>& z_best  = simplex_pairs.front().first;
       // const std::vector<double>& z_worst = simplex_pairs.back().first;
       // double f_best  = simplex_pairs.front().second;
       // double f_worst = simplex_pairs.back().second;
       // double f_2nd   = simplex_pairs[simplex_pairs.size() - 2].second;

        // Count exactly one NM step per loop
        iteration++;
        std::cout << "---- NM Iteration " << iteration << " ----\n";
       
        // ###################################
        //**Add EI balancing
        // ###################################
        
        // Map current simplex vertices (z) into x so EI can work in x-space
        std::vector<std::vector<double>> simplex_x(simplex_pairs.size());
        for (size_t i = 0; i < simplex_pairs.size(); ++i) {
            simplex_x[i] = z_to_x_vec(simplex_pairs[i].first, lowerBounds, upperBounds, btypes);
        }

        
        // --- choose EI target index ---
        int eiIdx = -1;
        /*
        if (eiState.continueSame && eiState.targetLabel >= 0) {
            // keep targeting the same label across iterations
            eiIdx = indexOfLabel(labels, eiState.targetLabel);
            if (eiIdx < 0) { // label vanished for any reason → fall back to best
                eiIdx = 0; eiState.continueSame = false; eiState.acceptedOnce = false;
            }
        } else {
            if (eiMode == EITargetMode::Best) {
                eiIdx = 0; // best is always at index 0 after our labeled sort
            } else { // EITargetMode::Fixed
                eiIdx = indexOfLabel(labels, eiFixedLabel);
                if (eiIdx < 0) eiIdx = 0; // fallback to best
            }
            eiState.targetLabel  = labels[eiIdx];
            eiState.acceptedOnce = false;
            eiState.bestAcceptedF = std::numeric_limits<double>::infinity();
        }
        */
        
        // Helper: pick best eligible index by label, skipping Locked/Exhausted
        auto pickBestEligible = [&]()->int {
            for (int i = 0; i < static_cast<int>(labels.size()); ++i) {
                int lbl = labels[i];
                if (eiLocked.count(lbl))    continue; // converged → skip forever
                if (eiExhausted.count(lbl)) continue; // 2 attempts used → skip
                // attempts default 0 if unseen
                int a = (eiAttempts.count(lbl) ? eiAttempts[lbl] : 0);
                if (a < kMaxEIAttemptsPerLabel) return i; // eligible
            }
            return -1; // none eligible
        };

        if (eiState.continueSame && eiState.targetLabel >= 0) {
            // retry same lineage if still eligible
            int idx = indexOfLabel(labels, eiState.targetLabel);
            if (idx >= 0) {
                int a = (eiAttempts.count(eiState.targetLabel) ? eiAttempts[eiState.targetLabel] : 0);
                if (!eiLocked.count(eiState.targetLabel) && !eiExhausted.count(eiState.targetLabel) && a < kMaxEIAttemptsPerLabel) {
                    eiIdx = idx; // keep focusing the same label
                }
            }
            if (eiIdx < 0) {
                // same lineage no longer eligible → switch to best eligible
                eiState.continueSame = false;
                eiState.acceptedOnce = false;
                eiState.bestAcceptedF = std::numeric_limits<double>::infinity();
                eiIdx = pickBestEligible();
            }
        } else {
            // fresh selection each iteration: best eligible
            eiIdx = pickBestEligible();
        }

        if (eiIdx < 0) {
            std::cout << "EI: no eligible vertex (all Locked/Exhausted). Skipping EI this iteration.\n";
        } else {
            eiState.targetLabel  = labels[eiIdx];
            // reset acceptance memory for the new lineage
            if (!eiState.continueSame) {
                eiState.acceptedOnce  = false;
                eiState.bestAcceptedF = std::numeric_limits<double>::infinity();
            }
        }
        
        

        // --- run EI for exactly N local steps on the chosen vertex ---
        //opt::EIResult ei = opt::ProgressiveEI::Run(func, simplex_x[eiIdx], /*localIters=*/kEILocalIters);
        opt::EIResult ei;
        bool ranEI = false;
        if (eiIdx >= 0) {
            ei = opt::ProgressiveEI::Run(func, simplex_x[eiIdx], /*localIters=*/kEILocalIters);
            ranEI = true;
        }

        // **Do not overwrite the chosen vertex; we compare only against the worst of the remaining n.
        /*
        const int wRem = worstRemainingIndex(simplex_pairs, eiIdx);
        const double fWorstRem = simplex_pairs[wRem].second;

        bool eiAccepted = (ei.f < fWorstRem);
        if (eiAccepted) {
            // replace the worst-of-remaining with EI candidate; keep the chosen vertex untouched
            simplex_pairs[wRem].first  = x_to_z_vec(ei.x, lowerBounds, upperBounds, btypes);
            simplex_pairs[wRem].second = ei.f;

            // label bookkeeping: the replaced slot keeps its label (candidate takes that slot)
            updateSimplexAndCentroid(simplex_pairs, labels, centroid);

            // record acceptance & keep targeting the same label next time (unless you later add FR-converged logic)
            eiState.acceptedOnce  = true;
            eiState.bestAcceptedF = std::min(eiState.bestAcceptedF, ei.f);
            eiState.continueSame  = true;

            std::cout << "EI: accepted candidate vs worst-of-remaining (replaced idx " << wRem
                      << "), f=" << ei.f << "\n";
        } else {
            // discard EI candidate
            std::cout << "EI: discarded (f_ei=" << ei.f << " >= worstRemaining=" << fWorstRem << ")\n";

            // if we had accepted earlier for this label and now regressed, stop focusing on this label
            if (eiState.acceptedOnce) {
                eiState.continueSame = false; // switch to best-of-(n+1) next iteration
            } else {
                // never accepted → also switch to best next time
                eiState.continueSame = false;
            }
        }
        */
        
        if (ranEI) {
            const int wRem = worstRemainingIndex(simplex_pairs, eiIdx);
            const double fWorstRem = simplex_pairs[wRem].second;

            // attempts++ for this lineage
            int &att = eiAttempts[eiState.targetLabel];
            att = att + 1;

            const bool converged = EIWithinBounds(ei.x);
            if (converged) {
                eiLocked.insert(eiState.targetLabel);   // no more EI on this lineage
            }

            const bool eiAccepted = (ei.f < fWorstRem);
            if (eiAccepted) {
                // replace the worst-of-remaining with EI candidate; keep the targeted vertex as-is
                simplex_pairs[wRem].first  = x_to_z_vec(ei.x, lowerBounds, upperBounds, btypes);
                simplex_pairs[wRem].second = ei.f;

                updateSimplexAndCentroid(simplex_pairs, labels, centroid);

                eiState.acceptedOnce  = true;
                eiState.bestAcceptedF = std::min(eiState.bestAcceptedF, ei.f);

                // NEXT-TARGET POLICY:
                // - If converged: do NOT continue on this lineage; pick best-eligible (excluding Locked) next time.
                // - Else if attempts < 2: continueSame = true (retry same lineage).
                // - Else (attempts==2): mark exhausted; move on next time.
                if (converged) {
                    eiState.continueSame = false;
                } else if (att < kMaxEIAttemptsPerLabel) {
                    eiState.continueSame = true;   // retry same lineage next iteration
                } else {
                    eiExhausted.insert(eiState.targetLabel);
                    eiState.continueSame = false;  // move on
                }

                std::cout << "EI: accepted vs worst-of-remaining (replaced idx " << wRem
                          << "), f=" << ei.f << ", attempts=" << att
                          << (converged ? " [CONVERGED]\n" : "\n");

            } else {
                // discard EI candidate
                std::cout << "EI: discarded (f_ei=" << ei.f << " >= worstRemaining=" << fWorstRem
                          << "), attempts=" << att << (converged ? " [CONVERGED]\n" : "\n");

                // same next-target policy as above
                if (converged) {
                    eiState.continueSame = false;
                } else if (att < kMaxEIAttemptsPerLabel) {
                    eiState.continueSame = true;   // retry same lineage next iteration
                } else {
                    eiExhausted.insert(eiState.targetLabel);
                    eiState.continueSame = false;  // move on
                }
            }
        } else {
            // No eligible EI target this iteration
            eiState.continueSame = false;
        }

        // ###################################
        // EI END
        // ###################################
        
        std::vector<double> z_best  = simplex_pairs.front().first;   
        std::vector<double> z_worst = simplex_pairs.back().first;    
        double f_best  = simplex_pairs.front().second;
        double f_worst = simplex_pairs.back().second;
        double f_2nd   = simplex_pairs[simplex_pairs.size() - 2].second;

        std::cout << "Current Best: ";
        printVector(z_to_x_vec(z_best, lowerBounds, upperBounds, btypes), f_best);

        // Per-iteration best for the loss plot (one row per NM step)
        double iterBestValue = f_best;
        std::vector<double> iterBestParams = z_to_x_vec(z_best, lowerBounds, upperBounds, btypes);

        //  Reflection 
        std::vector<double> z_ref(centroid.size());
        for (size_t j = 0; j < centroid.size(); ++j)
            z_ref[j] = centroid[j] + alpha * (centroid[j] - z_worst[j]);

        std::vector<double> x_ref = z_to_x_vec(z_ref, lowerBounds, upperBounds, btypes);
        double f_ref = func(x_ref, false);//true
        fevals++;
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
                    simplex_pairs[i].second = func(xi, false);//true
                    fevals++;

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
                    simplex_pairs[i].second = func(xi, false);//true 
                    fevals++;

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
        saveData(iterations, objectiveValues, parameterTrajectory, "nelder_mead_output.txt");// Record objective value

        if (bestObjectiveValue <= tolerance) {
            std::cout << "Reached tolerance after iteration " << iteration << " with objective " << bestObjectiveValue << ".\n";
            return bestSolution;
        }
    } // while end

    // Final best solution
    //updateSimplexAndCentroid(simplex_pairs, centroid);
    updateSimplexAndCentroid(simplex_pairs, labels, centroid);//update
    bestSolution = z_to_x_vec(simplex_pairs.front().first, lowerBounds, upperBounds, btypes);
    bestObjectiveValue = simplex_pairs.front().second;

    std::cout << "Best Solution Found: ";
    printVector(bestSolution, bestObjectiveValue);
    return bestSolution;
}
