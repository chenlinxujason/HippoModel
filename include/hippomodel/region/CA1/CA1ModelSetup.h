#pragma once

#include <map>
#include <string>

class CARLsim;

namespace hippomodel::CA1 {

void configureCA1CellModels(CARLsim& sim, const std::map<std::string, int>& group_ids);

}  // namespace hippomodel::CA1
