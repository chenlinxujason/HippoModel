#pragma once

#include "hippomodel/io/ConnectivityData.h"
#include "hippomodel/region/CA1/CA1RegionSpec.h"

#include <carlsim.h>

#include <map>
#include <string>
#include <utility>

namespace hippomodel::CA1 {

class CA1ConnectionGenerator final : public ConnectionGenerator {
public:
    CA1ConnectionGenerator(
        const CA1RegionSpec& spec,
        const ConnectivityData& connectivity,
        const std::map<std::string, std::map<std::string, float>>& weights);

    void connect(CARLsim* sim, int srcGrp, int i, int destGrp, int j,
                 float& weight, float& maxWt, float& delay, bool& connected) override;

private:
    std::pair<float, float> getCoords(const std::string& group, int global_id) const;

    const CA1RegionSpec& spec_;
    const ConnectivityData& connectivity_;
    const std::map<std::string, std::map<std::string, float>>& weights_;
};

}  // namespace hippomodel::CA1
