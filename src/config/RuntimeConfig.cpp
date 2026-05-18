#include "hippomodel/config/RuntimeConfig.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace hippomodel {
namespace {

std::string trim(std::string s) {
    auto notSpace = [](unsigned char ch) { return !std::isspace(ch); };
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), notSpace));
    s.erase(std::find_if(s.rbegin(), s.rend(), notSpace).base(), s.end());
    return s;
}

std::string stripInlineComment(const std::string& line) {
    bool inString = false;
    std::string out;
    for (size_t i = 0; i < line.size(); ++i) {
        const char c = line[i];
        if (c == '"') inString = !inString;
        if (!inString && c == '#') break;
        out.push_back(c);
    }
    return out;
}

std::string unquote(std::string value) {
    value = trim(value);
    if (value.size() >= 2 && value.front() == '"' && value.back() == '"') {
        return value.substr(1, value.size() - 2);
    }
    return value;
}

bool parseBool(const std::string& value) {
    const std::string v = trim(value);
    if (v == "true") return true;
    if (v == "false") return false;
    throw std::runtime_error("Invalid boolean value: " + value);
}

double parseDouble(const std::string& value) {
    try {
        size_t pos = 0;
        const std::string v = trim(value);
        const double out = std::stod(v, &pos);
        if (pos != v.size()) throw std::runtime_error("");
        return out;
    } catch (...) {
        throw std::runtime_error("Invalid numeric value: " + value);
    }
}

int parseInt(const std::string& value) {
    try {
        size_t pos = 0;
        const std::string v = trim(value);
        const int out = std::stoi(v, &pos);
        if (pos != v.size()) throw std::runtime_error("");
        return out;
    } catch (...) {
        throw std::runtime_error("Invalid integer value: " + value);
    }
}

std::vector<std::string> splitDot(const std::string& value) {
    std::vector<std::string> parts;
    std::string part;
    std::istringstream in(value);
    while (std::getline(in, part, '.')) {
        parts.push_back(part);
    }
    return parts;
}

void assignPathValue(RuntimePaths& paths, const std::string& key, const std::string& value) {
    if (key == "connectivity_h5") paths.connectivity_h5 = unquote(value);
    else if (key == "output_dir") paths.output_dir = unquote(value);
    else if (key == "target_psd_file") paths.target_psd_file = unquote(value);
}

void overlayPaths(RuntimePaths& base, const RuntimePaths& region) {
    if (!region.connectivity_h5.empty()) base.connectivity_h5 = region.connectivity_h5;
    if (!region.output_dir.empty()) base.output_dir = region.output_dir;
    if (!region.target_psd_file.empty()) base.target_psd_file = region.target_psd_file;
}

void assignInputSourceValue(RuntimeInputSource& source, const std::string& key, const std::string& value) {
    if (key == "mode") source.mode = unquote(value);
    else if (key == "file") source.file = unquote(value);
    else if (key == "rate_hz") source.rate_hz = parseDouble(value);
}

}  // namespace

RuntimeConfig loadRuntimeConfigFromFile(const std::string& config_path) {
    RuntimeConfig cfg;

    std::ifstream in(config_path);
    if (!in.is_open()) {
        throw std::runtime_error("Cannot open config file: " + config_path);
    }

    std::string section;
    std::string line;
    int lineNo = 0;
    while (std::getline(in, line)) {
        ++lineNo;
        line = trim(stripInlineComment(line));
        if (line.empty()) continue;

        if (line.front() == '[' && line.back() == ']') {
            section = trim(line.substr(1, line.size() - 2));
            continue;
        }

        const size_t eq = line.find('=');
        if (eq == std::string::npos) {
            throw std::runtime_error("Invalid config line " + std::to_string(lineNo) + ": " + line);
        }

        const std::string key = trim(line.substr(0, eq));
        const std::string value = trim(line.substr(eq + 1));

        if (section == "paths") {
            assignPathValue(cfg.paths, key, value);
        } else if (section.rfind("paths.", 0) == 0) {
            const std::string region_name = section.substr(std::string("paths.").size());
            assignPathValue(cfg.region_paths[region_name], key, value);
        } else if (section.rfind("inputs.", 0) == 0) {
            const auto parts = splitDot(section);
            if (parts.size() == 2) {
                // Backward-compatible compact style:
                // [inputs.DG]
                // EC_LEC = "results/spk_EC_LEC.dat"
                const std::string& region_name = parts[1];
                RuntimeInputSource source;
                source.mode = "file";
                source.file = unquote(value);
                cfg.region_inputs[region_name].sources[key] = source;
            } else if (parts.size() == 3) {
                // Preferred explicit style:
                // [inputs.DG.EC_LEC]
                // mode = "file" or "poisson"
                // file = "..." or rate_hz = 2.1
                const std::string& region_name = parts[1];
                const std::string& group_name = parts[2];
                assignInputSourceValue(cfg.region_inputs[region_name].sources[group_name], key, value);
            }
        } else if (section == "simulation") {
            if (key == "seed") cfg.simulation.seed = parseInt(value);
            else if (key == "num_gpus") cfg.simulation.num_gpus = parseInt(value);
            else if (key == "integration_step") cfg.simulation.integration_step = parseInt(value);
            else if (key == "transient_sec") cfg.simulation.transient_sec = parseInt(value);
            else if (key == "measurement_sec") cfg.simulation.measurement_sec = parseInt(value);
            else if (key == "write_spikes") cfg.simulation.write_spikes = parseBool(value);
        } else if (section == "optimizer") {
            if (key == "nm_mode") cfg.optimizer.nm_mode = unquote(value);
            else if (key == "max_iterations") cfg.optimizer.max_iterations = parseInt(value);
            else if (key == "tolerance_percent") cfg.optimizer.tolerance_percent = parseDouble(value);
            else if (key == "lower_scale") cfg.optimizer.lower_scale = parseDouble(value);
            else if (key == "upper_scale") cfg.optimizer.upper_scale = parseDouble(value);
        } else if (section == "loss.weights") {
            if (key == "firing_rate") cfg.loss_weights.firing_rate = parseDouble(value);
            else if (key == "correlation") cfg.loss_weights.correlation = parseDouble(value);
            else if (key == "oscillation") cfg.loss_weights.oscillation = parseDouble(value);
        } else if (section == "loss.correlation") {
            if (key == "n_slices") cfg.correlation.n_slices = parseInt(value);
            else if (key == "bin_ms") cfg.correlation.bin_ms = parseInt(value);
            else if (key == "n_shuffle") cfg.correlation.n_shuffle = parseInt(value);
            else if (key == "target_mean_abs_corr") cfg.correlation.target_mean_abs_corr = parseDouble(value);
            else if (key == "dv_ymin_mm") cfg.correlation.dv_ymin_mm = parseDouble(value);
            else if (key == "dv_ymax_mm") cfg.correlation.dv_ymax_mm = parseDouble(value);
        } else if (section == "loss.oscillation") {
            if (key == "bin_ms") cfg.oscillation.bin_ms = parseInt(value);
            else if (key == "ref_f1_hz") cfg.oscillation.ref_f1_hz = parseDouble(value);
            else if (key == "ref_f2_hz") cfg.oscillation.ref_f2_hz = parseDouble(value);
            else if (key == "theta_f1_hz") cfg.oscillation.theta_f1_hz = parseDouble(value);
            else if (key == "theta_f2_hz") cfg.oscillation.theta_f2_hz = parseDouble(value);
            else if (key == "beta_f1_hz") cfg.oscillation.beta_f1_hz = parseDouble(value);
            else if (key == "beta_f2_hz") cfg.oscillation.beta_f2_hz = parseDouble(value);
            else if (key == "gamma_f1_hz") cfg.oscillation.gamma_f1_hz = parseDouble(value);
            else if (key == "gamma_f2_hz") cfg.oscillation.gamma_f2_hz = parseDouble(value);
            else if (key == "low_f1_hz") cfg.oscillation.low_f1_hz = parseDouble(value);
            else if (key == "low_f2_hz") cfg.oscillation.low_f2_hz = parseDouble(value);
            else if (key == "target_theta") cfg.oscillation.target_theta = parseDouble(value);
            else if (key == "target_beta") cfg.oscillation.target_beta = parseDouble(value);
            else if (key == "target_gamma") cfg.oscillation.target_gamma = parseDouble(value);
            else if (key == "target_two_hz") cfg.oscillation.target_two_hz = parseDouble(value);
        } else if (section == "loss.firing_rate.targets") {
            cfg.firing_rate_targets[key] = parseDouble(value);
        } else if (section.rfind("loss.firing_rate.bounds.", 0) == 0) {
            const std::string group = section.substr(std::string("loss.firing_rate.bounds.").size());
            auto& bounds = cfg.firing_rate_bounds[group];
            if (key == "lower") bounds.first = parseDouble(value);
            else if (key == "upper") bounds.second = parseDouble(value);
        } else if (section == "run.scaling_factors") {
            cfg.run_scaling_factors[key] = parseDouble(value);
        }
    }

    validateRuntimeConfig(cfg);
    return cfg;
}

RuntimeConfig runtimeConfigForRegion(RuntimeConfig cfg, const std::string& region_name) {
    cfg.selected_region = region_name;

    const auto path_it = cfg.region_paths.find(region_name);
    if (path_it != cfg.region_paths.end()) {
        overlayPaths(cfg.paths, path_it->second);
    }

    const auto input_it = cfg.region_inputs.find(region_name);
    if (input_it != cfg.region_inputs.end()) {
        cfg.inputs = input_it->second;
    }

    validateRuntimeConfig(cfg);
    return cfg;
}

void validateRuntimeConfig(const RuntimeConfig& cfg) {
    auto require = [](bool ok, const std::string& msg) {
        if (!ok) throw std::runtime_error("Invalid config: " + msg);
    };

    require(!cfg.paths.connectivity_h5.empty(), "paths.connectivity_h5 is empty");
    require(!cfg.paths.output_dir.empty(), "paths.output_dir is empty");
    require(cfg.simulation.num_gpus > 0, "simulation.num_gpus must be > 0");
    require(cfg.simulation.integration_step > 0, "simulation.integration_step must be > 0");
    require(cfg.simulation.transient_sec >= 0, "simulation.transient_sec must be >= 0");
    require(cfg.simulation.measurement_sec > 0, "simulation.measurement_sec must be > 0");
    require(cfg.optimizer.max_iterations > 0, "optimizer.max_iterations must be > 0");
    require(cfg.optimizer.tolerance_percent > 0.0, "optimizer.tolerance_percent must be > 0");
    require(cfg.optimizer.lower_scale >= 0.0, "optimizer.lower_scale must be >= 0");
    require(cfg.optimizer.upper_scale > cfg.optimizer.lower_scale, "optimizer.upper_scale must be > optimizer.lower_scale");
    require(cfg.correlation.n_slices > 1, "loss.correlation.n_slices must be > 1");
    require(cfg.correlation.bin_ms > 0, "loss.correlation.bin_ms must be > 0");
    require(cfg.correlation.n_shuffle > 0, "loss.correlation.n_shuffle must be > 0");
    require(cfg.correlation.target_mean_abs_corr > 0.0, "loss.correlation.target_mean_abs_corr must be > 0");
    require(cfg.oscillation.bin_ms > 0, "loss.oscillation.bin_ms must be > 0");
    require(cfg.oscillation.ref_f2_hz > cfg.oscillation.ref_f1_hz, "loss.oscillation reference band is invalid");
    require(cfg.loss_weights.firing_rate >= 0.0, "loss.weights.firing_rate must be >= 0");
    require(cfg.loss_weights.correlation >= 0.0, "loss.weights.correlation must be >= 0");
    require(cfg.loss_weights.oscillation >= 0.0, "loss.weights.oscillation must be >= 0");

    auto requireInput = [&](const std::string& region, const std::string& group) {
        const auto it = cfg.inputs.sources.find(group);
        require(it != cfg.inputs.sources.end(), "inputs." + region + "." + group + " is missing");
        require(it->second.mode == "file" || it->second.mode == "poisson",
                "inputs." + region + "." + group + ".mode must be file or poisson");
        if (it->second.mode == "file") {
            require(!it->second.file.empty(), "inputs." + region + "." + group + ".file is empty");
        } else if (it->second.mode == "poisson") {
            require(it->second.rate_hz >= 0.0, "inputs." + region + "." + group + ".rate_hz must be >= 0");
        }
    };

    if (cfg.selected_region == "DG") {
        requireInput("DG", "EC_LEC");
        requireInput("DG", "EC_MEC");
    } else if (cfg.selected_region == "CA3") {
        requireInput("CA3", "EC_LEC");
        requireInput("CA3", "EC_MEC");
        requireInput("CA3", "DG_GC");
    } else if (cfg.selected_region == "CA1") {
        requireInput("CA1", "EC_LEC3");
        requireInput("CA1", "EC_MEC3");
        requireInput("CA1", "CA3_PC");
    }
}

std::string effectiveConfigText(const RuntimeConfig& cfg) {
    std::ostringstream out;
    out << "selected_region = \"" << cfg.selected_region << "\"\n\n";
    out << "[paths]\n";
    out << "connectivity_h5 = \"" << cfg.paths.connectivity_h5 << "\"\n";
    out << "output_dir = \"" << cfg.paths.output_dir << "\"\n";
    out << "target_psd_file = \"" << cfg.paths.target_psd_file << "\"\n\n";
    out << "[inputs]\n";
    for (const auto& kv : cfg.inputs.sources) {
        out << kv.first << ".mode = \"" << kv.second.mode << "\"\n";
        if (kv.second.mode == "file") out << kv.first << ".file = \"" << kv.second.file << "\"\n";
        if (kv.second.mode == "poisson") out << kv.first << ".rate_hz = " << kv.second.rate_hz << "\n";
    }
    out << "\n[simulation]\n";
    out << "seed = " << cfg.simulation.seed << "\n";
    out << "num_gpus = " << cfg.simulation.num_gpus << "\n";
    out << "integration_step = " << cfg.simulation.integration_step << "\n";
    out << "transient_sec = " << cfg.simulation.transient_sec << "\n";
    out << "measurement_sec = " << cfg.simulation.measurement_sec << "\n";
    out << "write_spikes = " << (cfg.simulation.write_spikes ? "true" : "false") << "\n\n";
    out << "[optimizer]\n";
    out << "nm_mode = \"" << cfg.optimizer.nm_mode << "\"\n";
    out << "max_iterations = " << cfg.optimizer.max_iterations << "\n";
    out << "tolerance_percent = " << cfg.optimizer.tolerance_percent << "\n";
    out << "lower_scale = " << cfg.optimizer.lower_scale << "\n";
    out << "upper_scale = " << cfg.optimizer.upper_scale << "\n";
    return out.str();
}

}  // namespace hippomodel
