#include "hippomodel/analysis/PSD.h"

#include <algorithm>
#include <cmath>
#include <complex>
#include <numeric>

namespace hippomodel {

void buildGlobalPopulationTimeSeries(
    SpikeMonitor* mon,
    int bin_ms,
    int T0_ms,
    int T1_ms,
    std::vector<double>& x_global,
    double& fs_hz) {

    fs_hz = 1000.0 / static_cast<double>(bin_ms);
    const int nbins = std::max(1, static_cast<int>(std::ceil((T1_ms - T0_ms) / static_cast<double>(bin_ms))));
    x_global.assign(nbins, 0.0);

    if (!mon || T1_ms <= T0_ms || bin_ms <= 0) return;
    const auto spikes2D = mon->getSpikeVector2D();
    for (const auto& times : spikes2D) {
        for (int t_ms : times) {
            if (t_ms < T0_ms || t_ms >= T1_ms) continue;
            const int b = (t_ms - T0_ms) / bin_ms;
            if (b >= 0 && b < nbins) x_global[b] += 1.0;
        }
    }
}

void computeNormalizedPSD(const std::vector<double>& x, double fs_hz, std::vector<double>& psd, int nfft) {
    const int kmax = nfft / 2;
    psd.assign(kmax + 1, 0.0);
    if (x.empty() || nfft <= 0) return;

    std::vector<double> xpad(nfft, 0.0);
    const int n = std::min(static_cast<int>(x.size()), nfft);
    double mean = 0.0;
    for (int i = 0; i < n; ++i) mean += x[i];
    mean /= std::max(1, n);
    for (int i = 0; i < n; ++i) xpad[i] = x[i] - mean;

    constexpr double pi = 3.14159265358979323846;
    for (int k = 0; k <= kmax; ++k) {
        std::complex<double> acc(0.0, 0.0);
        for (int t = 0; t < nfft; ++t) {
            const double phase = -2.0 * pi * static_cast<double>(k) * static_cast<double>(t) / static_cast<double>(nfft);
            acc += xpad[t] * std::complex<double>(std::cos(phase), std::sin(phase));
        }
        psd[k] = std::norm(acc) / static_cast<double>(nfft);
    }

    const double df = fs_hz / static_cast<double>(nfft);
    double area = 0.0;
    for (double v : psd) area += v * df;
    if (area > 0.0 && std::isfinite(area)) {
        for (double& v : psd) v /= area;
    }
}

double rhythmRatio(
    const std::vector<double>& x,
    double fs_hz,
    double band_f1_hz,
    double band_f2_hz,
    double ref_f1_hz,
    double ref_f2_hz) {

    const int nfft = 1024;
    std::vector<double> psd;
    computeNormalizedPSD(x, fs_hz, psd, nfft);
    if (psd.empty()) return 0.0;

    const double df = fs_hz / static_cast<double>(nfft);
    auto bandPower = [&](double f1, double f2) {
        double p = 0.0;
        for (int k = 0; k < static_cast<int>(psd.size()); ++k) {
            const double f = k * df;
            if (f >= f1 && f <= f2) p += psd[k] * df;
        }
        return p;
    };

    const double ref = bandPower(ref_f1_hz, ref_f2_hz);
    if (ref <= 0.0 || !std::isfinite(ref)) return 0.0;
    return bandPower(band_f1_hz, band_f2_hz) / ref;
}

}  // namespace hippomodel
