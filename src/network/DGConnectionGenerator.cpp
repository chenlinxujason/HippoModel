#include "hippomodel/network/DGConnectionGenerator.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>

namespace hippomodel::DG {

DGConnectionGenerator::DGConnectionGenerator(
    const DGRegionSpec& spec,
    const ConnectivityData& connectivity,
    const std::map<std::string, std::map<std::string, float>>& weights)
    : spec_(spec), connectivity_(connectivity), weights_(weights) {}

std::pair<float, float> DGConnectionGenerator::getCoords(const std::string& group, int global_id) const {
    static int nan_dbg = 0;
    const auto offsetIt = connectivity_.id_offset.find(group);
    if (offsetIt == connectivity_.id_offset.end()) {
        if (nan_dbg < 20) {
            std::cout << "[COORDS] MISSING OFFSET for group=" << group << " (gid=" << global_id << ")" << std::endl;
            ++nan_dbg;
        }
        return {NAN, NAN};
    }

    const int local_id = global_id - offsetIt->second;
    const auto xIt = connectivity_.loc_x.find(group);
    const auto yIt = connectivity_.loc_y.find(group);
    if (xIt == connectivity_.loc_x.end() || yIt == connectivity_.loc_y.end()) {
        if (nan_dbg < 20) {
            std::cout << "[COORDS] UNKNOWN GROUP=" << group << " (gid=" << global_id << ")" << std::endl;
            ++nan_dbg;
        }
        return {NAN, NAN};
    }

    const auto& xs = xIt->second;
    const auto& ys = yIt->second;
    if (local_id >= 0 && local_id < static_cast<int>(xs.size()) && local_id < static_cast<int>(ys.size())) {
        return {xs[local_id], ys[local_id]};
    }

    if (nan_dbg < 20) {
        std::cout << "[COORDS] OOB for group=" << group
                  << " gid=" << global_id
                  << " offset=" << offsetIt->second
                  << " local_id=" << local_id
                  << " xs.size()=" << xs.size()
                  << " ys.size()=" << ys.size() << std::endl;
        ++nan_dbg;
    }
    return {NAN, NAN};
}

void DGConnectionGenerator::connect(CARLsim* sim, int srcGrp, int i, int destGrp, int j,
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

    const float x_post_mm = postXY.first;
    if (name_dest == "DG_GC" &&
        (name_src == "EC_MEC" || name_src == "EC_LEC") &&
        std::isfinite(x_post_mm) && x_post_mm <= 0.0f) {
        weight *= static_cast<float>(spec_.ec_to_gc_infra_weight_scale);
    }

    float velocity = static_cast<float>(spec_.default_velocity);
    const auto vit = spec_.velocity_by_pre_group.find(name_src);
    if (vit != spec_.velocity_by_pre_group.end()) {
        velocity = static_cast<float>(vit->second);
    }

    float dist_mm = 0.0f;
    if (std::isfinite(preXY.first) && std::isfinite(preXY.second) &&
        std::isfinite(postXY.first) && std::isfinite(postXY.second)) {
        const float dx = preXY.first - postXY.first;
        const float dy = preXY.second - postXY.second;
        dist_mm = std::sqrt(dx * dx + dy * dy);
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

    static int conn_count = 0;
    if (conn_count < 10) {
        std::cout << "Conn " << (conn_count + 1)
                  << " | src=" << name_src << " GID_pre=" << ID_pre
                  << " | dst=" << name_dest << " GID_post=" << ID_post
                  << " | pre=(" << preXY.first << "," << preXY.second << ")"
                  << " post=(" << postXY.first << "," << postXY.second << ")"
                  << " | dist_mm=" << dist_mm
                  << " | velocity=" << velocity
                  << " | delay_ms=" << delay
                  << std::endl;
        ++conn_count;
    }
}

}  // namespace hippomodel::DG
