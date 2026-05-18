#pragma once

#include <map>
#include <string>

class CARLsim;

namespace hippomodel::CA3 {

void configureCA3CellModels(CARLsim& sim, const std::map<std::string, int>& group_ids);

}  // namespace hippomodel::CA3
