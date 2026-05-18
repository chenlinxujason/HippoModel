#include "hippomodel/analysis/Correlation.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <numeric>
#include <random>
#include <unordered_map>

namespace hippomodel {
namespace {

double pearsonCorrZeroLag(const std::vector<float>& a, const std::vector<float>& b) {
    const int L = static_cast<int>(a.size());
    if (static_cast<int>(b.size()) != L || L <= 2) return std::numeric_limits<double>::quiet_NaN();

    double ma = 0.0, mb = 0.0;
    for (int i = 0; i < L; ++i) { ma += a[i]; mb += b[i]; }
    ma /= static_cast<double>(L);
    mb /= static_cast<double>(L);

    double num = 0.0, da = 0.0, db = 0.0;
    for (int i = 0; i < L; ++i) {
        const double xa = static_cast<double>(a[i]) - ma;
        const double xb = static_cast<double>(b[i]) - mb;
        num += xa * xb;
        da += xa * xa;
        db += xb * xb;
    }
    const double den = std::sqrt(da * db);
    if (den <= 0.0) return std::numeric_limits<double>::quiet_NaN();
    return num / den;
}

}  // namespace

double dvSliceCorrMeanAbsZeroLagRandom(
    SpikeMonitor* mon,
    const std::vector<float>& dv_mm,
    int K,
    int bin_ms,
    int T0_ms,
    int T1_ms,
    int n_shuffle,
    double dv_ymin_mm,
    double dv_ymax_mm) {

    if (!mon || dv_mm.empty() || T1_ms <= T0_ms || bin_ms <= 0 || n_shuffle <= 0) return 1.0;
    const int nbins = static_cast<int>(std::ceil((T1_ms - T0_ms) / static_cast<double>(bin_ms)));
    if (nbins <= 2) return 1.0;

    const auto spikes2D = mon->getSpikeVector2D();
    std::vector<int> activeNids;
    activeNids.reserve(spikes2D.size());
    std::unordered_map<int, std::vector<int>> binsByNid;
    binsByNid.reserve(spikes2D.size());

    for (int nid = 0; nid < static_cast<int>(spikes2D.size()); ++nid) {
        if (nid >= static_cast<int>(dv_mm.size())) break;
        const double y = static_cast<double>(dv_mm[nid]);
        if (y < dv_ymin_mm || y >= dv_ymax_mm) continue;

        std::vector<int> bins;
        for (int t_ms : spikes2D[nid]) {
            if (t_ms < T0_ms || t_ms >= T1_ms) continue;
            const int b = (t_ms - T0_ms) / bin_ms;
            if (b >= 0 && b < nbins) bins.push_back(b);
        }
        if (!bins.empty()) {
            activeNids.push_back(nid);
            binsByNid.emplace(nid, std::move(bins));
        }
    }

    if (static_cast<int>(activeNids.size()) < K || K < 2) return 1.0;

    auto computeOneShuffle = [&](int seed) -> double {
        std::vector<int> shuffled = activeNids;
        std::mt19937 rng(static_cast<uint32_t>(seed));
        std::shuffle(shuffled.begin(), shuffled.end(), rng);

        std::vector<std::vector<float>> X(K, std::vector<float>(nbins, 0.0f));
        for (int idx = 0; idx < static_cast<int>(shuffled.size()); ++idx) {
            const int s = std::min(K - 1, idx * K / static_cast<int>(shuffled.size()));
            const int nid = shuffled[idx];
            for (int b : binsByNid.at(nid)) X[s][b] += 1.0f;
        }

        double sum = 0.0;
        int cnt = 0;
        for (int i = 0; i < K; ++i) {
            for (int j = i + 1; j < K; ++j) {
                const double r = pearsonCorrZeroLag(X[i], X[j]);
                if (!std::isnan(r)) { sum += std::abs(r); ++cnt; }
            }
        }
        return cnt == 0 ? 1.0 : sum / static_cast<double>(cnt);
    };

    double sum = 0.0;
    for (int s = 1; s <= n_shuffle; ++s) sum += computeOneShuffle(s);
    return sum / static_cast<double>(n_shuffle);
}

}  // namespace hippomodel
