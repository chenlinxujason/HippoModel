#pragma once

#include <carlsim.h>

#include <vector>

namespace hippomodel {

void buildGlobalPopulationTimeSeries(
    SpikeMonitor* mon,
    int bin_ms,
    int t0_ms,
    int t1_ms,
    std::vector<double>& x_global,
    double& fs_hz);

double rhythmRatio(
    const std::vector<double>& x,
    double fs_hz,
    double band_f1_hz,
    double band_f2_hz,
    double ref_f1_hz,
    double ref_f2_hz);

void computeNormalizedPSD(
    const std::vector<double>& x,
    double fs_hz,
    std::vector<double>& psd,
    int nfft);

}  // namespace hippomodel
