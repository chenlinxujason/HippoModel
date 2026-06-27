#pragma once

#include <cmath>

namespace opt {
namespace DGCorrelationGuidance {

inline double& CurrentCorrMeanAbs() {
    static double value = 0.0;
    return value;
}

inline double& TargetCorrMeanAbs() {
    static double value = 0.0;
    return value;
}

inline bool& Available() {
    static bool value = false;
    return value;
}

inline void Update(double current_corr_mean_abs, double target_corr_mean_abs) {
    if (std::isfinite(current_corr_mean_abs) &&
        std::isfinite(target_corr_mean_abs) &&
        target_corr_mean_abs > 0.0) {
        CurrentCorrMeanAbs() = current_corr_mean_abs;
        TargetCorrMeanAbs() = target_corr_mean_abs;
        Available() = true;
    }
}

inline void Clear() {
    CurrentCorrMeanAbs() = 0.0;
    TargetCorrMeanAbs() = 0.0;
    Available() = false;
}

inline bool Get(double& current_corr_mean_abs, double& target_corr_mean_abs) {
    if (!Available()) {
        return false;
    }

    current_corr_mean_abs = CurrentCorrMeanAbs();
    target_corr_mean_abs = TargetCorrMeanAbs();
    return true;
}

}  // namespace DGCorrelationGuidance
}  // namespace opt
