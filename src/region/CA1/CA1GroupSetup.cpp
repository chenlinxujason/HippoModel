#include "hippomodel/region/CA1/CA1GroupSetup.h"

namespace hippomodel::CA1 {

void createCA1Groups(CARLsim& sim, const ConnectivityData& connectivity, std::map<std::string, int>& groupIDs) {
    const int num_EC_LEC3 = static_cast<int>(connectivity.loc_x.at("EC_LEC3").size());
    const int num_EC_MEC3 = static_cast<int>(connectivity.loc_x.at("EC_MEC3").size());
    const int num_CA3_PC = static_cast<int>(connectivity.loc_x.at("CA3_PC").size());
    const int num_CA1_PC = static_cast<int>(connectivity.loc_x.at("CA1_PC").size());
    const int num_CA1_AAC = static_cast<int>(connectivity.loc_x.at("CA1_AAC").size());
    const int num_CA1_BC = static_cast<int>(connectivity.loc_x.at("CA1_BC").size());
    const int num_CA1_BCCCK = static_cast<int>(connectivity.loc_x.at("CA1_BCCCK").size());
    const int num_CA1_BisC = static_cast<int>(connectivity.loc_x.at("CA1_BisC").size());
    const int num_CA1_NG = static_cast<int>(connectivity.loc_x.at("CA1_NG").size());
    const int num_CA1_OLM = static_cast<int>(connectivity.loc_x.at("CA1_OLM").size());
    const int num_CA1_TL = static_cast<int>(connectivity.loc_x.at("CA1_TL").size());

    int EC_LEC3 = sim.createSpikeGeneratorGroup("EC_LEC3", num_EC_LEC3, EXCITATORY_NEURON);
    int EC_MEC3 = sim.createSpikeGeneratorGroup("EC_MEC3", num_EC_MEC3, EXCITATORY_NEURON);
    int CA3_PC = sim.createSpikeGeneratorGroup("CA3_PC", num_CA3_PC, EXCITATORY_NEURON);
    int CA1_PC = sim.createGroup("CA1_PC", num_CA1_PC, EXCITATORY_NEURON);
    int CA1_AAC = sim.createGroup("CA1_AAC", num_CA1_AAC, INHIBITORY_NEURON);
    int CA1_BC = sim.createGroup("CA1_BC", num_CA1_BC, INHIBITORY_NEURON);
    int CA1_BCCCK = sim.createGroup("CA1_BCCCK", num_CA1_BCCCK, INHIBITORY_NEURON);
    int CA1_BisC = sim.createGroup("CA1_BisC", num_CA1_BisC, INHIBITORY_NEURON);
    int CA1_NG = sim.createGroup("CA1_NG", num_CA1_NG, INHIBITORY_NEURON);
    int CA1_OLM = sim.createGroup("CA1_OLM", num_CA1_OLM, INHIBITORY_NEURON);
    int CA1_TL = sim.createGroup("CA1_TL", num_CA1_TL, INHIBITORY_NEURON);

    groupIDs["EC_LEC3"] = EC_LEC3;
    groupIDs["EC_MEC3"] = EC_MEC3;
    groupIDs["CA3_PC"] = CA3_PC;
    groupIDs["CA1_PC"] = CA1_PC;
    groupIDs["CA1_AAC"] = CA1_AAC;
    groupIDs["CA1_BC"] = CA1_BC;
    groupIDs["CA1_BCCCK"] = CA1_BCCCK;
    groupIDs["CA1_BisC"] = CA1_BisC;
    groupIDs["CA1_NG"] = CA1_NG;
    groupIDs["CA1_OLM"] = CA1_OLM;
    groupIDs["CA1_TL"] = CA1_TL;
}

}  // namespace hippomodel::CA1
