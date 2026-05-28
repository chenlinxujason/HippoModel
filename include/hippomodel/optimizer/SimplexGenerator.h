#pragma once

#include "hippomodel/optimizer/ProgressiveEI.h"

#include <algorithm>
#include <cmath>
#include <functional>
#include <random>
#include <stdexcept>
#include <utility>
#include <vector>

namespace hippomodel::opt {


inline void enforceEcPairGeometricLimit(
    std::vector<double>& x,
    const std::vector<double>& lowerBounds,
    const std::vector<double>& upperBounds,
    const std::vector<std::pair<int, int>>& ecPairs,
    double EC_PAIR_MAX_RATIO)
{
    if (EC_PAIR_MAX_RATIO <= 1.0) return;

    const double sqrtRatioMax = std::sqrt(EC_PAIR_MAX_RATIO);

    for (const auto& pair : ecPairs) {
        const int lecIdx = pair.first;
        const int mecIdx = pair.second;

        if (lecIdx < 0 || mecIdx < 0) continue;
        if (static_cast<size_t>(lecIdx) >= x.size()) continue;
        if (static_cast<size_t>(mecIdx) >= x.size()) continue;

        double lec = x[lecIdx];
        double mec = x[mecIdx];

        if (lec <= 0.0 || mec <= 0.0) continue;

        const double ratio = lec / mec;
        if (ratio > EC_PAIR_MAX_RATIO) {
            const double g = std::sqrt(lec * mec);  // preserve accumulated common-mode increase/decrease
            lec = g * sqrtRatioMax;
            mec = g / sqrtRatioMax;
        } else if (ratio < 1.0 / EC_PAIR_MAX_RATIO) {
            const double g = std::sqrt(lec * mec);  // preserve accumulated common-mode increase/decrease
            lec = g / sqrtRatioMax;
            mec = g * sqrtRatioMax;
        } else {
            continue;
        }

        lec = std::max(lowerBounds[lecIdx], std::min(lec, upperBounds[lecIdx]));
        mec = std::max(lowerBounds[mecIdx], std::min(mec, upperBounds[mecIdx]));

        x[lecIdx] = lec;
        x[mecIdx] = mec;
    }
}

inline std::vector<std::vector<double>> generateVerticesGDShift(
    const std::function<double(const std::vector<double>&, bool)>& func, // add
    const std::vector<std::vector<double>>& inputVertices, //base
    int numVertices,
    int seed, // include random seed for vertex generation and debug
    const std::vector<double>& lowerBounds,
    const std::vector<double>& upperBounds,
    std::vector<std::vector<double>>& outVertices,
    std::vector<double>& outObjValues,
    const std::vector<std::pair<int, int>>& ecPairs = {},
    double EC_PAIR_MAX_RATIO = 1.5
    //double shiftDelta // = 0.3 //shift amount, fix as 0.3
    )
{
    if (inputVertices.empty())
        throw std::runtime_error("Error: inputVertices is empty.");

    const size_t n = inputVertices[0].size();
    std::mt19937 rng(seed);
    std::normal_distribution<double> N01(0.0, 1.0);
    
    // Retrieve EI balancing info from ProgressiveEI
    const auto& types = ::opt::ProgressiveEI::GetTypes();   // use ProgressiveEI
    const auto& frmap = ::opt::ProgressiveEI::GetFiringRates(); // use ProgressiveEI
    
    if (lowerBounds.size() != n || upperBounds.size() != n)
        throw std::runtime_error("Error: lowerBounds and upperBounds must have the same size as the initial vertex.");

    for (size_t i = 1; i < inputVertices.size(); ++i)
        if (inputVertices[i].size() != n)
            throw std::runtime_error("Error: Not all input vertices have the same number of parameters as the first vertex.");

    std::vector<std::vector<double>> allVertices = inputVertices;

    const int alreadyProvided = static_cast<int>(inputVertices.size());
    if (numVertices <= alreadyProvided) {
        allVertices.resize(std::max(0, numVertices));
        return allVertices;
    }

    auto sgn = [](double v)->int { return (v > 0.0) - (v < 0.0); };

    // -------------------------------------------------------------------------
    // Precompute firing rate band info for each parameter index
    // -------------------------------------------------------------------------
    std::vector<double> F_low(n, 0.0), F_high(n, 0.0);
    for (const auto& kv : types) {
        const ::opt::NeuronType& T = kv.second;
        for (int k : T.ExcIndices)
            if (k >= 0 && static_cast<size_t>(k) < n) {
                F_low[k] = T.FiringRateLow;
                F_high[k] = T.FiringRateHigh;
            }
        for (int k : T.InhIndices)
            if (k >= 0 && static_cast<size_t>(k) < n) {
                F_low[k] = T.FiringRateLow;
                F_high[k] = T.FiringRateHigh;
            }
    }

    const std::vector<double>& x0 = inputVertices[0];
    outVertices.clear();
    outObjValues.clear();

    // -------------------------------------------------------------------------
    // Generate new vertices
    // -------------------------------------------------------------------------
    while (static_cast<int>(allVertices.size()) < numVertices) {
        
        //std::vector<double> x = x0;// start with the first vertex
        std::vector<double> x = allVertices.back(); // start with the latest vertex

        // -------------------------------------------------------------------------
        // Compute direction score for each parameter based on CURRENT FR position.
        // - Inside band: 80% chance to move (random direction), 20% chance hold.
        // - Outside band: same direction logic as before (push back toward band).
        // -------------------------------------------------------------------------
        std::vector<double> dirScore(n, 0.0);
        std::vector<double> f(n, 0.0); // current firing rate per parameter index (copied from frmap by type)

        std::uniform_real_distribution<double> U01(0.0, 1.0);
        
        double p_move = 0.9; // 90% chance to move, 10% chance hold ; 

        for (const auto& kv : types) {
            const ::opt::NeuronType& T = kv.second; // use ProgressiveEI
            auto itFR = frmap.find(T.name);
            if (itFR == frmap.end()) continue;

            const double fr = itFR->second;

            // store FR for indices belonging to this type (used later for normalized distance)
            for (int k : T.ExcIndices) if (k >= 0 && static_cast<size_t>(k) < n) f[k] = fr;
            for (int k : T.InhIndices) if (k >= 0 && static_cast<size_t>(k) < n) f[k] = fr;

            if (fr < T.FiringRateLow) {
                // FR below lower bound: increase Exc, decrease Inh
                for (int k : T.ExcIndices) if (k >= 0 && static_cast<size_t>(k) < n) dirScore[k] += 1.0;
                for (int k : T.InhIndices) if (k >= 0 && static_cast<size_t>(k) < n) dirScore[k] -= 1.0;
            } 
            else if (fr > T.FiringRateHigh) {
                // FR above upper bound: decrease Exc, increase Inh
                for (int k : T.ExcIndices) if (k >= 0 && static_cast<size_t>(k) < n) dirScore[k] -= 1.0;
                for (int k : T.InhIndices) if (k >= 0 && static_cast<size_t>(k) < n) dirScore[k] += 1.0;
            }
            else {
                // FR within band
                if (U01(rng) < p_move) {
                    // random direction: +1 means "increase FR" (Exc up, Inh down; -1 means "decrease FR" (Exc down, Inh up)
                    // p_move*50% move up, p_move*50% move down
                    const double s = (U01(rng) < 0.5) ? +1.0 : -1.0;

                    for (int k : T.ExcIndices) if (k >= 0 && static_cast<size_t>(k) < n) dirScore[k] += s;
                    for (int k : T.InhIndices) if (k >= 0 && static_cast<size_t>(k) < n) dirScore[k] -= s;
                }
            }
        }

        for (size_t j = 0; j < n; ++j) {
            const double L = lowerBounds[j];
            const double U = upperBounds[j];
            if (!(L < U)) { x[j] = L; continue; }

            const int dir = sgn(dirScore[j]);

            //----------------------------------------------------------------
            // Shift Gaussian Kernel mean based on firing rate (sgn sign)
            //----------------------------------------------------------------

            // shift amount based on how far FR is from the nearest violated bound
            //* Use normalized distance thresholds: d = |fr - bound| / (high - low); 
            // i.e, if a type’s band is narrow (0.4–0.9, width=0.5), being 0.5 Hz away is huge, d=1; if a type’s band is wide (15–30, width=15), being 0.5 Hz away is tiny, d=0.033
            // small: d<0.25; medium: 0.25-0.75; large, d>0.75
            const double dMed   = 0.4;  // normalized distance thresholds
            const double dLarge = 0.95;

            double scale = 1.1; // default (will be overridden below if needed)

            if (dir != 0) {
                double d = 0.0;
                double span = F_high[j] - F_low[j];
                if (span < 1e-9) span = 1e-9;

                const bool inBand = (f[j] >= F_low[j] && f[j] <= F_high[j]);

                if (!inBand) {// outside the bound
                    if (f[j] < F_low[j])       d = (F_low[j] - f[j]) / span;
                    else if (f[j] > F_high[j]) d = (f[j] - F_high[j]) / span;

                    if (d >= dLarge)      scale = 1.25;//1.25
                    else if (d >= dMed)   scale = 1.15;//1.15
                    else                  scale = 1.1;//1.1
                } else {
                    // within bound: fixed shift amount = 1.2
                    scale = 1.12;
                }
            }

            double mu = x[j];//x[j] start from last vertex 1
            
            // Direction from GD: +1 => increase (EXC up, INH down), -1 => decrease (EXC down, INH up), 0 => hold
            if (dir > 0)      mu = x[j] * scale;// right shift
            else if (dir < 0) mu = x[j] / scale;// left shift
            else              mu = x[j];// no shift
                     
            mu = std::min(std::max(mu, L), U);// clamp to valid bounds
            
            //----------------------------------------------------
            // Gaussian kernel width: 15% Gaussian sampling band
            //----------------------------------------------------
            const double delta = 0.15; // 15% band (15% around mu)
            const double sigma = 0.5 * delta * mu; // Gaussian width = μ*δ/2 such that μ±2σ ≈ [μ(1±δ)]
            double bandLo = std::max(L, mu * (1.0 - delta));
            double bandHi = std::min(U, mu * (1.0 + delta));
            if (bandLo > bandHi) std::swap(bandLo, bandHi);

            // sample within band
            // Each draw has 95% sample within the Gaussian kernel (mu with delta width, 15%)
            // We try multiple times to make sure the sample will drop within this Gaussian kernel.
            // The probability that 8 times will all fall outside the kernel is: (1-95%)^8, near 0 
            double v = mu;
            bool accepted = false;
            for (int tries = 0; tries < 8; ++tries) { // tries 8 times
                double cand = mu + sigma * N01(rng);
                if (cand >= bandLo && cand <= bandHi) {
                    v = cand;
                    accepted = true;
                    break;
                }
            }

            // If we didn’t hit the band in a few tries, project into it
            if (!accepted) {
                v = std::min(std::max(mu, bandLo), bandHi);
            }

            x[j] = v;
        }

        enforceEcPairGeometricLimit(
            x,
            lowerBounds,
            upperBounds,
            ecPairs,
            EC_PAIR_MAX_RATIO);

        // evaluate objective
        double fval = func(x, /*count*/false);

        allVertices.push_back(x);
        
        outVertices.push_back(x);
        
        outObjValues.push_back(fval);
    }

    return allVertices;
}




}  // namespace hippomodel::opt
