#pragma once

#include "hippomodel/io/ConnectivityData.h"
#include "hippomodel/region/CA3/CA3RegionSpec.h"

#include <carlsim.h>

#include <map>
#include <string>
#include <utility>

namespace hippomodel::CA3 {

class CA3ConnectionGenerator final : public ConnectionGenerator {
public:
    CA3ConnectionGenerator(
        const CA3RegionSpec& spec,
        const ConnectivityData& connectivity,
        const std::map<std::string, std::map<std::string, float>>& weights);

    void connect(CARLsim* sim, int srcGrp, int i, int destGrp, int j,
                 float& weight, float& maxWt, float& delay, bool& connected) override;

private:
    std::pair<float, float> getCoords(const std::string& group, int global_id) const;

    const CA3RegionSpec& spec_;
    const ConnectivityData& connectivity_;
    const std::map<std::string, std::map<std::string, float>>& weights_;
};

}  // namespace hippomodel::CA3
