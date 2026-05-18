#include "hippomodel/network/CA1ConnectionGenerator.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <random>

namespace hippomodel::CA1 {

CA1ConnectionGenerator::CA1ConnectionGenerator(
    const CA1RegionSpec& spec,
    const ConnectivityData& connectivity,
    const std::map<std::string, std::map<std::string, float>>& weights)
    : spec_(spec), connectivity_(connectivity), weights_(weights) {}

std::pair<float, float> CA1ConnectionGenerator::getCoords(const std::string& group, int global_id) const {
    const int local_id = global_id - connectivity_.id_offset.at(group);
    const auto& xs = connectivity_.loc_x.at(group);
    const auto& ys = connectivity_.loc_y.at(group);
    if (local_id >= 0 && local_id < static_cast<int>(xs.size()) && local_id < static_cast<int>(ys.size())) {
        return {xs[local_id], ys[local_id]};
    }
    return {NAN, NAN};
}

void CA1ConnectionGenerator::connect(CARLsim* sim, int srcGrp, int i, int destGrp, int j,
                                    float& weight, float& maxWt, float& delay, bool& connected) {
    const std::string name_src  = sim->getGroupName(srcGrp);
    const std::string name_dest = sim->getGroupName(destGrp);

    const int ID_pre  = i + connectivity_.id_offset.at(name_src);
    const int ID_post = j + connectivity_.id_offset.at(name_dest);

    auto& fanout = connectivity_.divergence.at(name_src).at(name_dest).at(i);
    connected = true;
    weight = weights_.at(name_src).at(name_dest);

    const auto preXY  = getCoords(name_src, ID_pre);
    const auto postXY = getCoords(name_dest, ID_post);

    float velocity = static_cast<float>(spec_.default_velocity);
    const auto vit = spec_.velocity_by_pre_group.find(name_src);
    if (vit != spec_.velocity_by_pre_group.end()) {
        velocity = static_cast<float>(vit->second);
    }

    if (std::isfinite(preXY.first) && std::isfinite(preXY.second) &&
        std::isfinite(postXY.first) && std::isfinite(postXY.second)) {
        const float dx = preXY.first - postXY.first;
        const float dy = preXY.second - postXY.second;
        const float dist_mm = std::sqrt(dx * dx + dy * dy);
        delay = dist_mm / velocity;
    } else {
        delay = 1.0f;
    }

    const int repeats = std::count(fanout.begin(), fanout.end(), ID_post);
    if (repeats > 1) {
        static thread_local std::mt19937 rng(std::random_device{}());
        std::uniform_real_distribution<float> U01(0.0f, 1.0f);
        delay += 1.0f - U01(rng);
    }
}

}  // namespace hippomodel::CA1
