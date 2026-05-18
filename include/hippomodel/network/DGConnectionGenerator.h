#pragma once

#include "hippomodel/io/ConnectivityData.h"
#include "hippomodel/region/DG/DGRegionSpec.h"

#include <carlsim.h>

#include <map>
#include <random>
#include <string>

namespace hippomodel::DG {

class DGConnectionGenerator : public ConnectionGenerator {
public:
    DGConnectionGenerator(
        const DGRegionSpec& spec,
        const ConnectivityData& connectivity,
        const std::map<std::string, std::map<std::string, float>>& weights);

    void connect(CARLsim* sim, int srcGrp, int i, int destGrp, int j,
                 float& weight, float& maxWt, float& delay, bool& connected);

private:
    std::pair<float, float> getCoords(const std::string& group, int global_id) const;

    const DGRegionSpec& spec_;
    const ConnectivityData& connectivity_;
    const std::map<std::string, std::map<std::string, float>>& weights_;
};

}  // namespace hippomodel::DG
