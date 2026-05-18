#pragma once

#include <map>
#include <string>

class CARLsim;
class ConnectionGenerator;

namespace hippomodel::CA1 {

void connectCA1Network(CARLsim& sim,
                       ConnectionGenerator* myConn,
                       const std::map<std::string, int>& group_ids,
                       std::map<std::string, int>& connectionIDs);

}  // namespace hippomodel::CA1
