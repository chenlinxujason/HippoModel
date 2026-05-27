#include "hippomodel/region/DG/DGGroupSetup.h"

namespace hippomodel::DG {

void createDGGroups(CARLsim& sim, const ConnectivityData& connectivity, std::map<std::string, int>& groupIDs) {
    const int num_EC_LEC = static_cast<int>(connectivity.loc_x.at("EC_LEC").size());
    const int num_EC_MEC = static_cast<int>(connectivity.loc_x.at("EC_MEC").size());
    const int num_DG_GC = static_cast<int>(connectivity.loc_x.at("DG_GC").size());
    const int num_DG_MC = static_cast<int>(connectivity.loc_x.at("DG_MC").size());
    const int num_DG_AAC = static_cast<int>(connectivity.loc_x.at("DG_AAC").size());
    const int num_DG_BC = static_cast<int>(connectivity.loc_x.at("DG_BC").size());
    const int num_DG_BCCCK = static_cast<int>(connectivity.loc_x.at("DG_BCCCK").size());
    const int num_DG_HICAP = static_cast<int>(connectivity.loc_x.at("DG_HICAP").size());
    const int num_DG_HIPP = static_cast<int>(connectivity.loc_x.at("DG_HIPP").size());
    const int num_DG_MOPP = static_cast<int>(connectivity.loc_x.at("DG_MOPP").size());
    const int num_DG_TML = static_cast<int>(connectivity.loc_x.at("DG_TML").size());

    int EC_LEC = sim.createSpikeGeneratorGroup("EC_LEC", num_EC_LEC, EXCITATORY_NEURON);
    int EC_MEC = sim.createSpikeGeneratorGroup("EC_MEC", num_EC_MEC, EXCITATORY_NEURON);
    int DG_GC = sim.createGroup("DG_GC", num_DG_GC, EXCITATORY_NEURON);
    int DG_MC = sim.createGroup("DG_MC", num_DG_MC, EXCITATORY_NEURON);
    int DG_AAC = sim.createGroup("DG_AAC", num_DG_AAC, INHIBITORY_NEURON);
    int DG_BC = sim.createGroup("DG_BC", num_DG_BC, INHIBITORY_NEURON);
    int DG_BCCCK = sim.createGroup("DG_BCCCK", num_DG_BCCCK, INHIBITORY_NEURON);
    int DG_HICAP = sim.createGroup("DG_HICAP", num_DG_HICAP, INHIBITORY_NEURON);
    int DG_HIPP = sim.createGroup("DG_HIPP", num_DG_HIPP, INHIBITORY_NEURON);
    int DG_MOPP = sim.createGroup("DG_MOPP", num_DG_MOPP, INHIBITORY_NEURON);
    int DG_TML = sim.createGroup("DG_TML", num_DG_TML, INHIBITORY_NEURON);

    groupIDs["EC_LEC"] = EC_LEC;
    groupIDs["EC_MEC"] = EC_MEC;
    groupIDs["DG_GC"] = DG_GC;
    groupIDs["DG_MC"] = DG_MC;
    groupIDs["DG_AAC"] = DG_AAC;
    groupIDs["DG_BC"] = DG_BC;
    groupIDs["DG_BCCCK"] = DG_BCCCK;
    groupIDs["DG_HICAP"] = DG_HICAP;
    groupIDs["DG_HIPP"] = DG_HIPP;
    groupIDs["DG_MOPP"] = DG_MOPP;
    groupIDs["DG_TML"] = DG_TML;
}

}  // namespace hippomodel::DG
