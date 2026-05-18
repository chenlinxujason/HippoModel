#pragma once

#include <carlsim.h>

#include <vector>

namespace hippomodel {

double dvSliceCorrMeanAbsZeroLagRandom(
    SpikeMonitor* mon,
    const std::vector<float>& dv_mm,
    int n_slices,
    int bin_ms,
    int t0_ms,
    int t1_ms,
    int n_shuffle,
    double dv_ymin_mm,
    double dv_ymax_mm);

}  // namespace hippomodel
