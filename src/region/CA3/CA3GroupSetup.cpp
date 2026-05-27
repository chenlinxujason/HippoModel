#include "hippomodel/region/CA3/CA3GroupSetup.h"

namespace hippomodel::CA3 {

void createCA3Groups(CARLsim& sim, const ConnectivityData& connectivity, std::map<std::string, int>& groupIDs) {
    const int num_EC_LEC = static_cast<int>(connectivity.loc_x.at("EC_LEC").size());
    const int num_EC_MEC = static_cast<int>(connectivity.loc_x.at("EC_MEC").size());
    const int num_DG_GC = static_cast<int>(connectivity.loc_x.at("DG_GC").size());
    const int num_CA3_PC = static_cast<int>(connectivity.loc_x.at("CA3_PC").size());
    const int num_CA3_AAC = static_cast<int>(connectivity.loc_x.at("CA3_AAC").size());
    const int num_CA3_BC = static_cast<int>(connectivity.loc_x.at("CA3_BC").size());
    const int num_CA3_BCCCK = static_cast<int>(connectivity.loc_x.at("CA3_BCCCK").size());
    const int num_CA3_BisC = static_cast<int>(connectivity.loc_x.at("CA3_BisC").size());
    const int num_CA3_MFA = static_cast<int>(connectivity.loc_x.at("CA3_MFA").size());
    const int num_CA3_OLM = static_cast<int>(connectivity.loc_x.at("CA3_OLM").size());
    const int num_CA3_TL = static_cast<int>(connectivity.loc_x.at("CA3_TL").size());

    int EC_LEC = sim.createSpikeGeneratorGroup("EC_LEC", num_EC_LEC, EXCITATORY_NEURON);
    int EC_MEC = sim.createSpikeGeneratorGroup("EC_MEC", num_EC_MEC, EXCITATORY_NEURON);
    int DG_GC = sim.createSpikeGeneratorGroup("DG_GC", num_DG_GC, EXCITATORY_NEURON);
    int CA3_PC = sim.createGroup("CA3_PC", num_CA3_PC, EXCITATORY_NEURON);
    int CA3_AAC = sim.createGroup("CA3_AAC", num_CA3_AAC, INHIBITORY_NEURON);
    int CA3_BC = sim.createGroup("CA3_BC", num_CA3_BC, INHIBITORY_NEURON);
    int CA3_BCCCK = sim.createGroup("CA3_BCCCK", num_CA3_BCCCK, INHIBITORY_NEURON);
    int CA3_BisC = sim.createGroup("CA3_BisC", num_CA3_BisC, INHIBITORY_NEURON);
    int CA3_MFA = sim.createGroup("CA3_MFA", num_CA3_MFA, INHIBITORY_NEURON);
    int CA3_OLM = sim.createGroup("CA3_OLM", num_CA3_OLM, INHIBITORY_NEURON);
    int CA3_TL = sim.createGroup("CA3_TL", num_CA3_TL, INHIBITORY_NEURON);

    groupIDs["EC_LEC"] = EC_LEC;
    groupIDs["EC_MEC"] = EC_MEC;
    groupIDs["DG_GC"] = DG_GC;
    groupIDs["CA3_PC"] = CA3_PC;
    groupIDs["CA3_AAC"] = CA3_AAC;
    groupIDs["CA3_BC"] = CA3_BC;
    groupIDs["CA3_BCCCK"] = CA3_BCCCK;
    groupIDs["CA3_BisC"] = CA3_BisC;
    groupIDs["CA3_MFA"] = CA3_MFA;
    groupIDs["CA3_OLM"] = CA3_OLM;
    groupIDs["CA3_TL"] = CA3_TL;
}

}  // namespace hippomodel::CA3
