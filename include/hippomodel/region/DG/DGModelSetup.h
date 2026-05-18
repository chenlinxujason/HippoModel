#pragma once

#include <map>
#include <string>

class CARLsim;

namespace hippomodel::DG {

void configureDGCellModels(CARLsim& sim, const std::map<std::string, int>& group_ids);

}  // namespace hippomodel::DG
