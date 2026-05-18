#include "hippomodel/region/CA1/CA1ConnectionSetup.h"

#include <carlsim.h>

#include <map>
#include <string>

namespace hippomodel::CA1 {

void connectCA1Network(CARLsim& sim,
                       ConnectionGenerator* myConn,
                       const std::map<std::string, int>& group_ids,
                       std::map<std::string, int>& connectionIDs) {
    const int EC_LEC3   = group_ids.at("EC_LEC3");
    const int EC_MEC3   = group_ids.at("EC_MEC3");
    const int CA3_PC    = group_ids.at("CA3_PC");
    const int CA1_PC    = group_ids.at("CA1_PC");
    const int CA1_AAC   = group_ids.at("CA1_AAC");
    const int CA1_BC    = group_ids.at("CA1_BC");
    const int CA1_BCCCK = group_ids.at("CA1_BCCCK");
    const int CA1_BisC  = group_ids.at("CA1_BisC");
    const int CA1_NG    = group_ids.at("CA1_NG");
    const int CA1_OLM   = group_ids.at("CA1_OLM");
    const int CA1_TL    = group_ids.at("CA1_TL");

    connectionIDs["LEC3_CA1PC"] = sim.connect(EC_LEC3, CA1_PC, myConn, 1.0, 0.268, SYN_FIXED);//0.268
    connectionIDs["MEC3_CA1PC"] = sim.connect(EC_MEC3, CA1_PC, myConn, 1.0, 0.268, SYN_FIXED);//0.268
    connectionIDs["CA3PC_CA1PC"] = sim.connect(CA3_PC, CA1_PC, myConn, 1.0, 0.608, SYN_FIXED);//0.608
    connectionIDs["CA1PC_CA1PC"] = sim.connect(CA1_PC, CA1_PC, myConn, 1.0, 0.97, SYN_FIXED);
    connectionIDs["CA1AAC_CA1PC"] = sim.connect(CA1_AAC, CA1_PC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA1BC_CA1PC"] = sim.connect(CA1_BC, CA1_PC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA1BCCCK_CA1PC"] = sim.connect(CA1_BCCCK, CA1_PC, myConn, 1.0, 0.07, SYN_FIXED);
    connectionIDs["CA1BisC_CA1PC"] = sim.connect(CA1_BisC, CA1_PC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA1NG_CA1PC"] = sim.connect(CA1_NG, CA1_PC, myConn, 1.0, 0.07, SYN_FIXED);
    connectionIDs["CA1OLM_CA1PC"] = sim.connect(CA1_OLM, CA1_PC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA1TL_CA1PC"] = sim.connect(CA1_TL, CA1_PC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["LEC3_CA1AAC"] = sim.connect(EC_LEC3, CA1_AAC, myConn, 1.0, 0.769, SYN_FIXED);
    connectionIDs["MEC3_CA1AAC"] = sim.connect(EC_MEC3, CA1_AAC, myConn, 1.0, 0.769, SYN_FIXED);
    connectionIDs["CA3PC_CA1AAC"] = sim.connect(CA3_PC, CA1_AAC, myConn, 1.0, 0.769, SYN_FIXED);
    connectionIDs["CA1PC_CA1AAC"] = sim.connect(CA1_PC, CA1_AAC, myConn, 1.0, 0.769, SYN_FIXED);
    connectionIDs["CA1BC_CA1AAC"] = sim.connect(CA1_BC, CA1_AAC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA1BCCCK_CA1AAC"] = sim.connect(CA1_BCCCK, CA1_AAC, myConn, 1.0, 0.07, SYN_FIXED);
    connectionIDs["CA1BisC_CA1AAC"] = sim.connect(CA1_BisC, CA1_AAC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA1NG_CA1AAC"] = sim.connect(CA1_NG, CA1_AAC, myConn, 1.0, 0.07, SYN_FIXED);
    connectionIDs["CA1OLM_CA1AAC"] = sim.connect(CA1_OLM, CA1_AAC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA1TL_CA1AAC"] = sim.connect(CA1_TL, CA1_AAC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["LEC3_CA1BC"] = sim.connect(EC_LEC3, CA1_BC, myConn, 1.0, 0.769, SYN_FIXED);
    connectionIDs["MEC3_CA1BC"] = sim.connect(EC_MEC3, CA1_BC, myConn, 1.0, 0.769, SYN_FIXED);
    connectionIDs["CA3PC_CA1BC"] = sim.connect(CA3_PC, CA1_BC, myConn, 1.0, 0.769, SYN_FIXED);
    connectionIDs["CA1PC_CA1BC"] = sim.connect(CA1_PC, CA1_BC, myConn, 1.0, 0.769, SYN_FIXED);
    connectionIDs["CA1BC_CA1BC"] = sim.connect(CA1_BC, CA1_BC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA1BCCCK_CA1BC"] = sim.connect(CA1_BCCCK, CA1_BC, myConn, 1.0, 0.07, SYN_FIXED);
    connectionIDs["CA1BisC_CA1BC"] = sim.connect(CA1_BisC, CA1_BC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA1NG_CA1BC"] = sim.connect(CA1_NG, CA1_BC, myConn, 1.0, 0.07, SYN_FIXED);
    connectionIDs["CA1OLM_CA1BC"] = sim.connect(CA1_OLM, CA1_BC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA1TL_CA1BC"] = sim.connect(CA1_TL, CA1_BC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["LEC3_CA1BCCCK"] = sim.connect(EC_LEC3, CA1_BCCCK, myConn, 1.0, 1.045, SYN_FIXED);
    connectionIDs["MEC3_CA1BCCCK"] = sim.connect(EC_MEC3, CA1_BCCCK, myConn, 1.0, 1.045, SYN_FIXED);
    connectionIDs["CA3PC_CA1BCCCK"] = sim.connect(CA3_PC, CA1_BCCCK, myConn, 1.0, 1.045, SYN_FIXED);
    connectionIDs["CA1PC_CA1BCCCK"] = sim.connect(CA1_PC, CA1_BCCCK, myConn, 1.0, 1.045, SYN_FIXED);
    connectionIDs["CA1BC_CA1BCCCK"] = sim.connect(CA1_BC, CA1_BCCCK, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA1BCCCK_CA1BCCCK"] = sim.connect(CA1_BCCCK, CA1_BCCCK, myConn, 1.0, 0.07, SYN_FIXED);
    connectionIDs["CA1BisC_CA1BCCCK"] = sim.connect(CA1_BisC, CA1_BCCCK, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA1NG_CA1BCCCK"] = sim.connect(CA1_NG, CA1_BCCCK, myConn, 1.0, 0.07, SYN_FIXED);
    connectionIDs["CA1OLM_CA1BCCCK"] = sim.connect(CA1_OLM, CA1_BCCCK, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA1TL_CA1BCCCK"] = sim.connect(CA1_TL, CA1_BCCCK, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA3PC_CA1BisC"] = sim.connect(CA3_PC, CA1_BisC, myConn, 1.0, 0.81, SYN_FIXED);
    connectionIDs["CA1PC_CA1BisC"] = sim.connect(CA1_PC, CA1_BisC, myConn, 1.0, 0.81, SYN_FIXED);
    connectionIDs["CA1BC_CA1BisC"] = sim.connect(CA1_BC, CA1_BisC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA1BCCCK_CA1BisC"] = sim.connect(CA1_BCCCK, CA1_BisC, myConn, 1.0, 0.07, SYN_FIXED);
    connectionIDs["CA1BisC_CA1BisC"] = sim.connect(CA1_BisC, CA1_BisC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA1TL_CA1BisC"] = sim.connect(CA1_TL, CA1_BisC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["LEC3_CA1NG"] = sim.connect(EC_LEC3, CA1_NG, myConn, 1.0, 0.9, SYN_FIXED);
    connectionIDs["MEC3_CA1NG"] = sim.connect(EC_MEC3, CA1_NG, myConn, 1.0, 0.9, SYN_FIXED);
    connectionIDs["CA1NG_CA1NG"] = sim.connect(CA1_NG, CA1_NG, myConn, 1.0, 0.07, SYN_FIXED);
    connectionIDs["CA1OLM_CA1NG"] = sim.connect(CA1_OLM, CA1_NG, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA3PC_CA1OLM"] = sim.connect(CA3_PC, CA1_OLM, myConn, 1.0, 0.9, SYN_FIXED);
    connectionIDs["CA1PC_CA1OLM"] = sim.connect(CA1_PC, CA1_OLM, myConn, 1.0, 0.9, SYN_FIXED);
    connectionIDs["CA1BisC_CA1OLM"] = sim.connect(CA1_BisC, CA1_OLM, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA1TL_CA1OLM"] = sim.connect(CA1_TL, CA1_OLM, myConn, 1.0, 0.0, SYN_FIXED);// for OLM, pre-OLM and OLM-post all has GABAb
    connectionIDs["CA3PC_CA1TL"] = sim.connect(CA3_PC, CA1_TL, myConn, 1.0, 0.9, SYN_FIXED);//0.9 - 0.69 - (0,1)
    connectionIDs["CA1PC_CA1TL"] = sim.connect(CA1_PC, CA1_TL, myConn, 1.0, 0.9, SYN_FIXED);//0.9 - 0.69 - (0,1)
    connectionIDs["CA1BisC_CA1TL"] = sim.connect(CA1_BisC, CA1_TL, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA1TL_CA1TL"] = sim.connect(CA1_TL, CA1_TL, myConn, 1.0, 0.0, SYN_FIXED);
}

}  // namespace hippomodel::CA1
