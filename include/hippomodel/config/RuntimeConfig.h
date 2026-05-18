#pragma once

#include <map>
#include <string>
#include <utility>

namespace hippomodel {

struct RuntimePaths {
    std::string connectivity_h5;
    std::string output_dir;
    std::string target_psd_file;
};

struct RuntimeInputSource {
    // mode = "file" uses SpikeGeneratorFromFile.
    // mode = "poisson" uses PoissonRate with rate_hz.
    std::string mode = "file";
    std::string file;
    double rate_hz = 0.0;
};

struct RuntimeInputs {
    std::map<std::string, RuntimeInputSource> sources;
};

struct SimulationConfig {
    int seed = 42;
    int num_gpus = 1;
    int integration_step = 10;
    int transient_sec = 10;
    int measurement_sec = 10;
    bool write_spikes = false;
};

struct OptimizerConfig {
    std::string nm_mode = "GD_full";
    int max_iterations = 400;
    double tolerance_percent = 1.0;
    double lower_scale = 0.009;
    double upper_scale = 15.0;
};

struct CorrelationConfig {
    int n_slices = 500;
    int bin_ms = 5;
    int n_shuffle = 3;
    double target_mean_abs_corr = 0.2;
    double dv_ymin_mm = 0.0;
    double dv_ymax_mm = 10.0;
};

struct OscillationConfig {
    int bin_ms = 5;
    double ref_f1_hz = 1.0;
    double ref_f2_hz = 60.0;
    double theta_f1_hz = 4.0;
    double theta_f2_hz = 9.0;
    double beta_f1_hz = 10.0;
    double beta_f2_hz = 20.0;
    double gamma_f1_hz = 21.0;
    double gamma_f2_hz = 55.0;
    double low_f1_hz = 0.0;
    double low_f2_hz = 2.0;
    double target_theta = 0.3;
    double target_beta = 0.3;
    double target_gamma = 0.3;
    double target_two_hz = 0.3;
};

struct LossWeightConfig {
    double firing_rate = 4.0;
    double correlation = 1.0;
    double oscillation = 1.0;
};

struct RuntimeConfig {
    std::string selected_region;
    RuntimePaths paths;
    RuntimeInputs inputs;
    std::map<std::string, RuntimePaths> region_paths;
    std::map<std::string, RuntimeInputs> region_inputs;
    SimulationConfig simulation;
    OptimizerConfig optimizer;
    CorrelationConfig correlation;
    OscillationConfig oscillation;
    LossWeightConfig loss_weights;
    std::map<std::string, double> firing_rate_targets;
    std::map<std::string, std::pair<double, double>> firing_rate_bounds;
    std::map<std::string, double> run_scaling_factors;
};

RuntimeConfig loadRuntimeConfigFromFile(const std::string& config_path);
RuntimeConfig runtimeConfigForRegion(RuntimeConfig cfg, const std::string& region_name);
void validateRuntimeConfig(const RuntimeConfig& cfg);
std::string effectiveConfigText(const RuntimeConfig& cfg);

}  // namespace hippomodel
