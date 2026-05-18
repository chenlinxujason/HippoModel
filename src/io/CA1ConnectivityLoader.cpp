#include "hippomodel/io/CA1ConnectivityLoader.h"

#include <highfive/H5File.hpp>

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

namespace hippomodel::CA1 {
namespace {

std::vector<int> tryReadVector(HighFive::File& file, const std::string& datasetName) {
    std::vector<int> con_data;
    try {
        file.getDataSet(datasetName).read(con_data);
    } catch (HighFive::Exception&) {
        con_data.clear();
    }
    return con_data;
}

std::map<std::string, GroupSpec> groupSpecByName(const CA1RegionSpec& spec) {
    std::map<std::string, GroupSpec> out;
    for (const auto& g : spec.groups) out[g.name] = g;
    return out;
}

}  // namespace

ConnectivityData loadCA1Connectivity(const RuntimeConfig& cfg, const CA1RegionSpec& spec) {
    ConnectivityData data;
    auto groups = groupSpecByName(spec);

    HighFive::File file(cfg.paths.connectivity_h5, HighFive::File::ReadOnly);

    std::map<std::string, std::vector<int>> idRanges;
    for (const auto& group : spec.groups) {
        std::vector<int> range;
        file.getDataSet(group.id_range_path).read(range);
        idRanges[group.name] = range;
        data.id_offset[group.name] = range[0];
    }

    std::vector<std::vector<float>> locs_hc;
    file.getDataSet("Locs/HC").read(locs_hc);

    for (const auto& group : spec.groups) {
        const auto& range = idRanges.at(group.name);
        for (int id = range[0]; id <= range[1]; ++id) {
            data.loc_x[group.name].push_back(locs_hc[id][0]);
            data.loc_y[group.name].push_back(locs_hc[id][1]);
        }
    }

    for (const auto& conn : spec.connections) {
        const auto& preSpec = groups.at(conn.pre_group);
        const auto& postSpec = groups.at(conn.post_group);
        const auto& preRange = idRanges.at(conn.pre_group);
        const auto& postRange = idRanges.at(conn.post_group);

        std::cout << "Loading " << conn.pre_group << " to " << conn.post_group << std::endl;
        auto& fanoutByPre = data.divergence[conn.pre_group][conn.post_group];
        for (int globalPreId = preRange[0]; globalPreId <= preRange[1]; ++globalPreId) {
            const std::string dataset = "Div/" + preSpec.h5_div_name + "/" + postSpec.h5_div_name + "/" + std::to_string(globalPreId);
            std::vector<int> div_data = tryReadVector(file, dataset);
            for (int& postId : div_data) {
                postId -= postRange[0];
            }
            fanoutByPre.emplace(globalPreId - preRange[0], std::move(div_data));
        }
    }

    return data;
}

}  // namespace hippomodel::CA1
