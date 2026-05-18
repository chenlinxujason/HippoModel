// ProgressiveEI.h - excitatory-inhibitory balancing
#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <iostream>
#include <cmath>

namespace opt {

struct EIResult {
    std::vector<double> x;
    double f;
};

struct NeuronType {
    std::string name;
    double FiringRateLow = 0.0;
    double FiringRateHigh = 0.0;
    std::vector<int> ExcIndices; // indices in x[]
    std::vector<int> InhIndices; // indices in x[]
};

class ProgressiveEI {
public:
static void SetEIVertexIndex(int idx) { EIVertexIndex() = idx; }
static int  GetEIVertexIndex()        { return EIVertexIndex(); }

// These two for Gradient-based Operation shifted kernel
static const std::unordered_map<std::string, NeuronType>& GetTypes()       { return Types(); }
static const std::unordered_map<std::string, double>&     GetFiringRates() { return LastFR(); }


    static void RegisterNeuronType(
        const std::string& name,
        double firingRateLow,
        double firingRateHigh,
        const std::vector<int>& excIdx,
        const std::vector<int>& inhIdx = {}  // default empty, so that we can handle Exc only or Inh only connections
        )
    {
        NeuronType nt;
        nt.name = name;
        nt.FiringRateLow  = firingRateLow;
        nt.FiringRateHigh = firingRateHigh;
        nt.ExcIndices = excIdx;
        nt.InhIndices = inhIdx;
        Types()[name] = nt;
    }

    // Publish mean FR per-pop from your objective()
    static void UpdateFiringRate(const std::string& name, double meanHz) {
        LastFR()[name] = meanHz;
    }

    // Select which original x-vertex Gradient Operation will “stick to”
    static void SelectReferenceVertex(const std::vector<double>& xref) { RefX() = xref; }
    static const std::vector<double>& GetReferenceX() { return RefX(); }

    // Gradient Operation loop in x-space (no reparameterization here)
    static EIResult Run(
    const std::function<double(const std::vector<double>&, bool)>& obj,
    const std::vector<double>& x0,
    int localIters,
    double up = 1.1,
    double dn = 1 / 1.1
    )
{
    // Evaluate starting point. In the NM wrapper, obj(...) is usually func_quiet,
    // so this still runs with output=false even though the second argument here is true.
    EIResult best{ x0, obj(x0, /*count*/true) };

    if (localIters <= 0) {
        return best;
    }

    std::vector<double> x = x0;
    double f = best.f;

    for (int it = 0; it < localIters; ++it) {
        bool allWithin = true;

        for (const auto& kv : Types()) {
            const NeuronType& T = kv.second;

            auto itFR = LastFR().find(T.name);
            if (itFR == LastFR().end()) {
                continue;
            }

            const double fr = itFR->second;

            if (fr > T.FiringRateHigh) {
                scale(x, T.InhIndices, up);
                scale(x, T.ExcIndices, dn);
                allWithin = false;
            } else if (fr < T.FiringRateLow) {
                scale(x, T.ExcIndices, up);
                scale(x, T.InhIndices, dn);
                allWithin = false;
            }
        }

        // If the current candidate already satisfies the FR bounds, return the best objective candidate instead of the final one.
        if (allWithin) {
            return best;
        }

        f = obj(x, /*count*/true);

        if ((std::isfinite(f) && !std::isfinite(best.f)) ||
            (std::isfinite(f) && f < best.f)) {
            best.x = x;
            best.f = f;
        }
    }

    return best;
}

private:
    static int& EIVertexIndex() { static int g = 0; return g; }
    static void scale(std::vector<double>& x, const std::vector<int>& idx, double factor) {
        for (int k : idx) if (k >= 0 && (size_t)k < x.size()) {
            x[k] *= factor;
            if (x[k] < 0.0) x[k] = 0.0;
        }
    }
    static std::unordered_map<std::string, NeuronType>& Types() { static std::unordered_map<std::string, NeuronType> g; return g; }
    static std::unordered_map<std::string, double>& LastFR()    { static std::unordered_map<std::string, double> g; return g; }
    static std::vector<double>& RefX()                          { static std::vector<double> g; return g; }
};

} // namespace opt

