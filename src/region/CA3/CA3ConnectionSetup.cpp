#include "hippomodel/region/CA3/CA3ConnectionSetup.h"

#include <carlsim.h>

#include <map>
#include <string>

namespace hippomodel::CA3 {

void connectCA3Network(CARLsim& sim,
                       ConnectionGenerator* myConn,
                       const std::map<std::string, int>& group_ids,
                       std::map<std::string, int>& connectionIDs) {
    const int EC_LEC     = group_ids.at("EC_LEC");
    const int EC_MEC     = group_ids.at("EC_MEC");
    const int DG_GC      = group_ids.at("DG_GC");
    const int CA3_PC     = group_ids.at("CA3_PC");
    const int CA3_AAC    = group_ids.at("CA3_AAC");
    const int CA3_BC     = group_ids.at("CA3_BC");
    const int CA3_BCCCK  = group_ids.at("CA3_BCCCK");
    const int CA3_BisC   = group_ids.at("CA3_BisC");
    const int CA3_MFA    = group_ids.at("CA3_MFA");
    const int CA3_OLM    = group_ids.at("CA3_OLM");
    const int CA3_TL     = group_ids.at("CA3_TL");

    connectionIDs["LEC_CA3PC"] = sim.connect(EC_LEC, CA3_PC, myConn, 1.0, 0.268, SYN_FIXED);//0.268
    connectionIDs["MEC_CA3PC"] = sim.connect(EC_MEC, CA3_PC, myConn, 1.0, 0.268, SYN_FIXED);//0.268
    connectionIDs["DGGC_CA3PC"] = sim.connect(DG_GC, CA3_PC, myConn, 1.0, 1.633, SYN_FIXED);//EPSC ratio = 0.88
    connectionIDs["CA3PC_CA3PC"] = sim.connect(CA3_PC, CA3_PC, myConn, 1.0, 0.97, SYN_FIXED);
    connectionIDs["CA3AAC_CA3PC"] = sim.connect(CA3_AAC, CA3_PC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA3BC_CA3PC"] = sim.connect(CA3_BC, CA3_PC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA3BCCCK_CA3PC"] = sim.connect(CA3_BCCCK, CA3_PC, myConn, 1.0, 0.07, SYN_FIXED);
    connectionIDs["CA3BisC_CA3PC"] = sim.connect(CA3_BisC, CA3_PC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA3MFA_CA3PC"] = sim.connect(CA3_MFA, CA3_PC, myConn, 1.0, 0.07, SYN_FIXED);
    connectionIDs["CA3OLM_CA3PC"] = sim.connect(CA3_OLM, CA3_PC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA3TL_CA3PC"] = sim.connect(CA3_TL, CA3_PC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["LEC_CA3AAC"] = sim.connect(EC_LEC, CA3_AAC, myConn, 1.0, 0.769, SYN_FIXED);
    connectionIDs["MEC_CA3AAC"] = sim.connect(EC_MEC, CA3_AAC, myConn, 1.0, 0.769, SYN_FIXED);
    connectionIDs["DGGC_CA3AAC"] = sim.connect(DG_GC, CA3_AAC, myConn, 1.0, 0.769, SYN_FIXED);
    connectionIDs["CA3PC_CA3AAC"] = sim.connect(CA3_PC, CA3_AAC, myConn, 1.0, 0.769, SYN_FIXED);
    connectionIDs["CA3BCCCK_CA3AAC"] = sim.connect(CA3_BCCCK, CA3_AAC, myConn, 1.0, 0.07, SYN_FIXED);
    connectionIDs["CA3BisC_CA3AAC"] = sim.connect(CA3_BisC, CA3_AAC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA3OLM_CA3AAC"] = sim.connect(CA3_OLM, CA3_AAC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA3TL_CA3AAC"] = sim.connect(CA3_TL, CA3_AAC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["LEC_CA3BC"] = sim.connect(EC_LEC, CA3_BC, myConn, 1.0, 0.769, SYN_FIXED);
    connectionIDs["MEC_CA3BC"] = sim.connect(EC_MEC, CA3_BC, myConn, 1.0, 0.769, SYN_FIXED);
    connectionIDs["DGGC_CA3BC"] = sim.connect(DG_GC, CA3_BC, myConn, 1.0, 0.769, SYN_FIXED);
    connectionIDs["CA3PC_CA3BC"] = sim.connect(CA3_PC, CA3_BC, myConn, 1.0, 0.769, SYN_FIXED);
    connectionIDs["CA3BC_CA3BC"] = sim.connect(CA3_BC, CA3_BC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA3BCCCK_CA3BC"] = sim.connect(CA3_BCCCK, CA3_BC, myConn, 1.0, 0.07, SYN_FIXED);
    connectionIDs["CA3BisC_CA3BC"] = sim.connect(CA3_BisC, CA3_BC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA3MFA_CA3BC"] = sim.connect(CA3_MFA, CA3_BC, myConn, 1.0, 0.07, SYN_FIXED);
    connectionIDs["CA3OLM_CA3BC"] = sim.connect(CA3_OLM, CA3_BC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA3TL_CA3BC"] = sim.connect(CA3_TL, CA3_BC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["DGGC_CA3BCCCK"] = sim.connect(DG_GC, CA3_BCCCK, myConn, 1.0, 1.045, SYN_FIXED);
    connectionIDs["CA3PC_CA3BCCCK"] = sim.connect(CA3_PC, CA3_BCCCK, myConn, 1.0, 1.045, SYN_FIXED);
    connectionIDs["CA3BC_CA3BCCCK"] = sim.connect(CA3_BC, CA3_BCCCK, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA3BCCCK_CA3BCCCK"] = sim.connect(CA3_BCCCK, CA3_BCCCK, myConn, 1.0, 0.07, SYN_FIXED);
    connectionIDs["CA3BisC_CA3BCCCK"] = sim.connect(CA3_BisC, CA3_BCCCK, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA3MFA_CA3BCCCK"] = sim.connect(CA3_MFA, CA3_BCCCK, myConn, 1.0, 0.07, SYN_FIXED);
    connectionIDs["CA3OLM_CA3BCCCK"] = sim.connect(CA3_OLM, CA3_BCCCK, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA3TL_CA3BCCCK"] = sim.connect(CA3_TL, CA3_BCCCK, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["DGGC_CA3BisC"] = sim.connect(DG_GC, CA3_BisC, myConn, 1.0, 0.81, SYN_FIXED);
    connectionIDs["CA3PC_CA3BisC"] = sim.connect(CA3_PC, CA3_BisC, myConn, 1.0, 0.81, SYN_FIXED);
    connectionIDs["CA3BC_CA3BisC"] = sim.connect(CA3_BC, CA3_BisC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA3BCCCK_CA3BisC"] = sim.connect(CA3_BCCCK, CA3_BisC, myConn, 1.0, 0.07, SYN_FIXED); // Add CCK-BisC
    connectionIDs["CA3BisC_CA3BisC"] = sim.connect(CA3_BisC, CA3_BisC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA3MFA_CA3BisC"] = sim.connect(CA3_MFA, CA3_BisC, myConn, 1.0, 0.07, SYN_FIXED);
    connectionIDs["CA3OLM_CA3BisC"] = sim.connect(CA3_OLM, CA3_BisC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA3TL_CA3BisC"] = sim.connect(CA3_TL, CA3_BisC, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["DGGC_CA3MFA"] = sim.connect(DG_GC, CA3_MFA, myConn, 1.0, 1.045, SYN_FIXED);
    connectionIDs["CA3PC_CA3MFA"] = sim.connect(CA3_PC, CA3_MFA, myConn, 1.0, 1.045, SYN_FIXED);
    connectionIDs["CA3BC_CA3MFA"] = sim.connect(CA3_BC, CA3_MFA, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA3BCCCK_CA3MFA"] = sim.connect(CA3_BCCCK, CA3_MFA, myConn, 1.0, 0.07, SYN_FIXED);
    connectionIDs["CA3BisC_CA3MFA"] = sim.connect(CA3_BisC, CA3_MFA, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA3MFA_CA3MFA"] = sim.connect(CA3_MFA, CA3_MFA, myConn, 1.0, 0.07, SYN_FIXED);
    connectionIDs["CA3OLM_CA3MFA"] = sim.connect(CA3_OLM, CA3_MFA, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA3TL_CA3MFA"] = sim.connect(CA3_TL, CA3_MFA, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA3PC_CA3OLM"] = sim.connect(CA3_PC, CA3_OLM, myConn, 1.0, 0.9, SYN_FIXED);
    connectionIDs["CA3BisC_CA3OLM"] = sim.connect(CA3_BisC, CA3_OLM, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA3OLM_CA3OLM"] = sim.connect(CA3_OLM, CA3_OLM, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA3TL_CA3OLM"] = sim.connect(CA3_TL, CA3_OLM, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA3PC_CA3TL"] = sim.connect(CA3_PC, CA3_TL, myConn, 1.0, 0.9, SYN_FIXED);
    connectionIDs["CA3BisC_CA3TL"] = sim.connect(CA3_BisC, CA3_TL, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA3OLM_CA3TL"] = sim.connect(CA3_OLM, CA3_TL, myConn, 1.0, 0.0, SYN_FIXED);
    connectionIDs["CA3TL_CA3TL"] = sim.connect(CA3_TL, CA3_TL, myConn, 1.0, 0.0, SYN_FIXED);
}

}  // namespace hippomodel::CA3
