#pragma once

#include <map>
#include <string>
#include <utility>
#include <vector>

namespace hippomodel {

struct ConnectivityData {
    // pre_group -> post_group -> pre_local_id -> vector<post_local_id>
    std::map<std::string, std::map<std::string, std::map<int, std::vector<int>>>> divergence;
    std::map<std::string, int> id_offset;
    std::map<std::string, std::vector<float>> loc_x;
    std::map<std::string, std::vector<float>> loc_y;
    std::vector<int> dg_gc_supra_global_ids;
    std::vector<int> dg_gc_infra_global_ids;
};

}  // namespace hippomodel
