#pragma once

#include <map>
#include <string>
#include <vector>

namespace hippomodel::CA1 {

enum class NeuronSign { Excitatory, Inhibitory };

struct GroupSpec {
    std::string name;
    std::string id_range_path;
    std::string h5_div_name;
    bool spike_generator = false;
    NeuronSign sign = NeuronSign::Excitatory;
};

struct ConnectionSpec {
    std::string name;
    std::string pre_group;
    std::string post_group;
    double connection_prob = 1.0;
    double max_weight = 0.0;
    double baseline_weight = 1.0;
};

struct EIRegistrationSpec {
    std::string neuron_type;
    std::vector<int> exc_indices;
    std::vector<int> inh_indices;
};

struct CA1RegionSpec {
    std::vector<GroupSpec> groups;
    std::vector<ConnectionSpec> connections;
    std::vector<std::string> optimized_connection_order;
    std::map<std::string, double> default_fr_targets;
    std::map<std::string, std::pair<double, double>> default_fr_bounds;
    std::vector<EIRegistrationSpec> ei_registrations;
    std::map<std::string, double> velocity_by_pre_group;
    double default_velocity = 0.13;
};

CA1RegionSpec makeCA1RegionSpec();

}  // namespace hippomodel::CA1
