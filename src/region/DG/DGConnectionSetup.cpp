#include "hippomodel/region/DG/DGConnectionSetup.h"

#include <carlsim.h>

#include <map>
#include <string>

namespace hippomodel::DG {

void connectDGNetwork(CARLsim& sim,
                      ConnectionGenerator* myConn,
                      const std::map<std::string, int>& group_ids,
                      std::map<std::string, int>& connectionIDs) {
    const int EC_LEC     = group_ids.at("EC_LEC");
    const int EC_MEC     = group_ids.at("EC_MEC");
    const int DG_GC      = group_ids.at("DG_GC");
    const int DG_MC      = group_ids.at("DG_MC");
    const int DG_AAC     = group_ids.at("DG_AAC");
    const int DG_BC      = group_ids.at("DG_BC");
    const int DG_BCCCK   = group_ids.at("DG_BCCCK");
    const int DG_HICAP   = group_ids.at("DG_HICAP");
    const int DG_HIPP    = group_ids.at("DG_HIPP");
    const int DG_MOPP    = group_ids.at("DG_MOPP");
    const int DG_TML     = group_ids.at("DG_TML");

connectionIDs["LEC_DGGC"] = sim.connect(EC_LEC, DG_GC, myConn, 1.0, 0.11, SYN_FIXED);//0.38(young) or 0.11(mature)
connectionIDs["MEC_DGGC"] = sim.connect(EC_MEC, DG_GC, myConn, 1.0, 0.11, SYN_FIXED);//0.38(young) or 0.11(mature)
connectionIDs["DGMC_DGGC"] = sim.connect(DG_MC, DG_GC, myConn, 1.0, 0.11, SYN_FIXED);//0.38(young) or 0.11(mature)
connectionIDs["DGAAC_DGGC"] = sim.connect(DG_AAC, DG_GC, myConn, 1.0, 0.0, SYN_FIXED);
connectionIDs["DGBC_DGGC"] = sim.connect(DG_BC, DG_GC, myConn, 1.0, 0.0, SYN_FIXED);
connectionIDs["DGBCCCK_DGGC"] = sim.connect(DG_BCCCK, DG_GC, myConn, 1.0, 0.07, SYN_FIXED);
connectionIDs["DGHICAP_DGGC"] = sim.connect(DG_HICAP, DG_GC, myConn, 1.0, 0.07, SYN_FIXED);
connectionIDs["DGHIPP_DGGC"] = sim.connect(DG_HIPP, DG_GC, myConn, 1.0, 0.0, SYN_FIXED);
connectionIDs["DGMOPP_DGGC"] = sim.connect(DG_MOPP, DG_GC, myConn, 1.0, 0.0, SYN_FIXED);
connectionIDs["DGTML_DGGC"] = sim.connect(DG_TML, DG_GC, myConn, 1.0, 0.0, SYN_FIXED);

connectionIDs["DGGC_DGMC"] = sim.connect(DG_GC, DG_MC, myConn, 1.0, 0.11, SYN_FIXED);//0.38(young) or 0.11(mature)
connectionIDs["DGMC_DGMC"] = sim.connect(DG_MC, DG_MC, myConn, 1.0, 0.11, SYN_FIXED);
connectionIDs["DGAAC_DGMC"] = sim.connect(DG_AAC, DG_MC, myConn, 1.0, 0.0, SYN_FIXED);
connectionIDs["DGTML_DGMC"] = sim.connect(DG_TML, DG_MC, myConn, 1.0, 0.0, SYN_FIXED);

connectionIDs["LEC_DGAAC"] = sim.connect(EC_LEC, DG_AAC, myConn, 1.0, 0.39, SYN_FIXED);
connectionIDs["MEC_DGAAC"] = sim.connect(EC_MEC, DG_AAC, myConn, 1.0, 0.39, SYN_FIXED);
connectionIDs["DGGC_DGAAC"] = sim.connect(DG_GC, DG_AAC, myConn, 1.0, 0.39, SYN_FIXED);
connectionIDs["DGMC_DGAAC"] = sim.connect(DG_MC, DG_AAC, myConn, 1.0, 0.39, SYN_FIXED);
connectionIDs["DGBC_DGAAC"] = sim.connect(DG_BC, DG_AAC, myConn, 1.0, 0.0, SYN_FIXED);
connectionIDs["DGBCCCK_DGAAC"] = sim.connect(DG_BCCCK, DG_AAC, myConn, 1.0, 0.07, SYN_FIXED);
connectionIDs["DGHICAP_DGAAC"] = sim.connect(DG_HICAP, DG_AAC, myConn, 1.0, 0.07, SYN_FIXED);
connectionIDs["DGHIPP_DGAAC"] = sim.connect(DG_HIPP, DG_AAC, myConn, 1.0, 0.0, SYN_FIXED);
connectionIDs["DGMOPP_DGAAC"] = sim.connect(DG_MOPP, DG_AAC, myConn, 1.0, 0.0, SYN_FIXED);
connectionIDs["DGTML_DGAAC"] = sim.connect(DG_TML, DG_AAC, myConn, 1.0, 0.0, SYN_FIXED);

connectionIDs["LEC_DGBC"] = sim.connect(EC_LEC, DG_BC, myConn, 1.0, 0.39, SYN_FIXED);
connectionIDs["MEC_DGBC"] = sim.connect(EC_MEC, DG_BC, myConn, 1.0, 0.39, SYN_FIXED);
connectionIDs["DGGC_DGBC"] = sim.connect(DG_GC, DG_BC, myConn, 1.0, 0.39, SYN_FIXED);
connectionIDs["DGMC_DGBC"] = sim.connect(DG_MC, DG_BC, myConn, 1.0, 0.39, SYN_FIXED);
connectionIDs["DGBC_DGBC"] = sim.connect(DG_BC, DG_BC, myConn, 1.0, 0.0, SYN_FIXED);
connectionIDs["DGBCCCK_DGBC"] = sim.connect(DG_BCCCK, DG_BC, myConn, 1.0, 0.07, SYN_FIXED);
connectionIDs["DGHICAP_DGBC"] = sim.connect(DG_HICAP, DG_BC, myConn, 1.0, 0.07, SYN_FIXED);
connectionIDs["DGHIPP_DGBC"] = sim.connect(DG_HIPP, DG_BC, myConn, 1.0, 0.0, SYN_FIXED);
connectionIDs["DGMOPP_DGBC"] = sim.connect(DG_MOPP, DG_BC, myConn, 1.0, 0.0, SYN_FIXED);
connectionIDs["DGTML_DGBC"] = sim.connect(DG_TML, DG_BC, myConn, 1.0, 0.0, SYN_FIXED);

connectionIDs["LEC_DGBCCCK"] = sim.connect(EC_LEC, DG_BCCCK, myConn, 1.0, 0.39, SYN_FIXED);
connectionIDs["MEC_DGBCCCK"] = sim.connect(EC_MEC, DG_BCCCK, myConn, 1.0, 0.39, SYN_FIXED);
connectionIDs["DGAAC_DGBCCCK"] = sim.connect(DG_AAC, DG_BCCCK, myConn, 1.0, 0.0, SYN_FIXED);
connectionIDs["DGBC_DGBCCCK"] = sim.connect(DG_BC, DG_BCCCK, myConn, 1.0, 0.0, SYN_FIXED);
connectionIDs["DGBCCCK_DGBCCCK"] = sim.connect(DG_BCCCK, DG_BCCCK, myConn, 1.0, 0.07, SYN_FIXED);
connectionIDs["DGHICAP_DGBCCCK"] = sim.connect(DG_HICAP, DG_BCCCK, myConn, 1.0, 0.07, SYN_FIXED);
connectionIDs["DGHIPP_DGBCCCK"] = sim.connect(DG_HIPP, DG_BCCCK, myConn, 1.0, 0.0, SYN_FIXED);
connectionIDs["DGMOPP_DGBCCCK"] = sim.connect(DG_MOPP, DG_BCCCK, myConn, 1.0, 0.0, SYN_FIXED);
connectionIDs["DGTML_DGBCCCK"] = sim.connect(DG_TML, DG_BCCCK, myConn, 1.0, 0.0, SYN_FIXED);

connectionIDs["LEC_DGHICAP"] = sim.connect(EC_LEC, DG_HICAP, myConn, 1.0, 0.39, SYN_FIXED);
connectionIDs["MEC_DGHICAP"] = sim.connect(EC_MEC, DG_HICAP, myConn, 1.0, 0.39, SYN_FIXED);
connectionIDs["DGGC_DGHICAP"] = sim.connect(DG_GC, DG_HICAP, myConn, 1.0, 0.39, SYN_FIXED);
connectionIDs["DGMC_DGHICAP"] = sim.connect(DG_MC, DG_HICAP, myConn, 1.0, 0.39, SYN_FIXED);
connectionIDs["DGBC_DGHICAP"] = sim.connect(DG_BC, DG_HICAP, myConn, 1.0, 0.0, SYN_FIXED);
connectionIDs["DGBCCCK_DGHICAP"] = sim.connect(DG_BCCCK, DG_HICAP, myConn, 1.0, 0.07, SYN_FIXED);
connectionIDs["DGHICAP_DGHICAP"] = sim.connect(DG_HICAP, DG_HICAP, myConn, 1.0, 0.07, SYN_FIXED);
connectionIDs["DGHIPP_DGHICAP"] = sim.connect(DG_HIPP, DG_HICAP, myConn, 1.0, 0.0, SYN_FIXED);
connectionIDs["DGMOPP_DGHICAP"] = sim.connect(DG_MOPP, DG_HICAP, myConn, 1.0, 0.0, SYN_FIXED);
connectionIDs["DGTML_DGHICAP"] = sim.connect(DG_TML, DG_HICAP, myConn, 1.0, 0.0, SYN_FIXED);

connectionIDs["DGGC_DGHIPP"] = sim.connect(DG_GC, DG_HIPP, myConn, 1.0, 0.39, SYN_FIXED);
connectionIDs["DGMC_DGHIPP"] = sim.connect(DG_MC, DG_HIPP, myConn, 1.0, 0.39, SYN_FIXED);
connectionIDs["DGTML_DGHIPP"] = sim.connect(DG_TML, DG_HIPP, myConn, 1.0, 0.0, SYN_FIXED);

connectionIDs["LEC_DGMOPP"] = sim.connect(EC_LEC, DG_MOPP, myConn, 1.0, 0.39, SYN_FIXED);
connectionIDs["MEC_DGMOPP"] = sim.connect(EC_MEC, DG_MOPP, myConn, 1.0, 0.39, SYN_FIXED);
connectionIDs["DGHIPP_DGMOPP"] = sim.connect(DG_HIPP, DG_MOPP, myConn, 1.0, 0.0, SYN_FIXED);
connectionIDs["DGMOPP_DGMOPP"] = sim.connect(DG_MOPP, DG_MOPP, myConn, 1.0, 0.0, SYN_FIXED);
connectionIDs["DGTML_DGMOPP"] = sim.connect(DG_TML, DG_MOPP, myConn, 1.0, 0.0, SYN_FIXED);

connectionIDs["LEC_DGTML"] = sim.connect(EC_LEC, DG_TML, myConn, 1.0, 0.39, SYN_FIXED);
connectionIDs["MEC_DGTML"] = sim.connect(EC_MEC, DG_TML, myConn, 1.0, 0.39, SYN_FIXED);
connectionIDs["DGHICAP_DGTML"] = sim.connect(DG_HICAP, DG_TML, myConn, 1.0, 0.07, SYN_FIXED);
connectionIDs["DGHIPP_DGTML"] = sim.connect(DG_HIPP, DG_TML, myConn, 1.0, 0.0, SYN_FIXED);
connectionIDs["DGMOPP_DGTML"] = sim.connect(DG_MOPP, DG_TML, myConn, 1.0, 0.0, SYN_FIXED);
connectionIDs["DGTML_DGTML"] = sim.connect(DG_TML, DG_TML, myConn, 1.0, 0.0, SYN_FIXED);

}

}  // namespace hippomodel::DG
