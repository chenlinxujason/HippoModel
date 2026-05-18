#pragma once

#include <map>
#include <string>

class CARLsim;
class ConnectionGenerator;

namespace hippomodel::CA3 {

void connectCA3Network(CARLsim& sim,
                       ConnectionGenerator* myConn,
                       const std::map<std::string, int>& group_ids,
                       std::map<std::string, int>& connectionIDs);

}  // namespace hippomodel::CA3
