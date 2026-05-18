#include "hippomodel/region/DG/DGModelSetup.h"

#include <carlsim.h>

#include <map>
#include <string>

namespace hippomodel::DG {

void configureDGCellModels(CARLsim& sim, const std::map<std::string, int>& group_ids) {
    const int DG_GC    = group_ids.at("DG_GC");
    const int DG_MC    = group_ids.at("DG_MC");
    const int DG_AAC   = group_ids.at("DG_AAC");
    const int DG_BC    = group_ids.at("DG_BC");
    const int DG_BCCCK = group_ids.at("DG_BCCCK");
    const int DG_HICAP = group_ids.at("DG_HICAP");
    const int DG_HIPP  = group_ids.at("DG_HIPP");
    const int DG_MOPP  = group_ids.at("DG_MOPP");
    const int DG_TML   = group_ids.at("DG_TML");

    //sim.setConductances(true);// COBA
    
    sim.setConductances(DG_GC, 37.72, 0, 97.818, 26.936, 0, 239.606);// type1,ok(Gene)(modify a,b)
    //sim.setConductances(DG_GC, 8.0, 0, 30.654, 26.936, 0, 239.606);// type1,ok(modify a,b)
    //sim.setConductances(DG_GC, 4.603, 0, 22.973, 43.572, 0, 316.13);// type1,(DGMC-DGGC)
    //sim.setConductances(DG_GC, 53.47, 0, 133.41, 43.572, 0, 316.13);// type1,(NMDA)

    sim.setConductances(DG_MC, 1.0, 0, 14.83, 18.58, 0, 201.177);// ok(GC-MC Exc)
    
    //sim.setConductances(DG_AAC, 3.962, 0, 21.525, 14.075, 0, 180.443);// modify,ok(EC-AAC)
    sim.setConductances(DG_AAC, 1.0, 0, 14.83, 14.075, 0, 180.443);// ok(EC/GC-AAC,Gene's simulation)
    //sim.setConductances(DG_AAC, 3.22, 0, 19.85, 14.075, 0, 180.443);// modify,ok(DGGC-AAC)
    //sim.setConductances(DG_AAC, 3.293, 0, 20.011, 14.075, 0, 180.443);// modify,ok(DGMC-AAC)
    
    //sim.setConductances(DG_BC, 9.32, 0, 53.03, 9.644, 0, 160.062);// ok(EC-BC)
    sim.setConductances(DG_BC, 1.0, 0, 14.83, 9.644, 0, 160.062);// ok(EC/GC-BC,Gene's simulation)
    //sim.setConductances(DG_BC, 7.13, 0, 53.03, 9.644, 0, 160.062);// ok(DGGC-BC)
    //sim.setConductances(DG_BC, 1.066, 0, 53.03, 9.644, 0, 160.062);// ok(DGMC-BC)

    //sim.setConductances(DG_BCCCK, 2.751, 0, 18.788, 13.11, 0, 176.02);// ok(EC-BCCCK)
    sim.setConductances(DG_BCCCK, 1.0, 0, 14.83, 13.11, 0, 176.02);// ok(EC-BCCCK,Gene's simulation)
    

    sim.setConductances(DG_HICAP, 1.593, 0, 16.168, 21.278, 0, 213.578);// ok(EC-HICAP,Gene's simulation)
    //sim.setConductances(DG_HICAP, 1.52, 0, 16.01, 21.278, 0, 213.578);// ok(DGGC-HICAP,Gene's simulation)
    //sim.setConductances(DG_HICAP, 5.3, 0, 24.54, 21.278, 0, 213.578);// ok(DGMC-HICAP,Gene's simulation)
    
    //sim.setConductances(DG_HIPP, 3.04, 0, 19.43, 6.411, 0, 145.191);// modify,ok(DGGC-HIPP)
    sim.setConductances(DG_HIPP, 1.0, 0, 14.83, 6.411, 0, 145.191);// modify,ok(DGGC-HIPP,Gene's simulation)
    //sim.setConductances(DG_HIPP, 1.0, 0, 14.83, 6.411, 0, 145.191);// modify,ok(DGMC-HIPP)
    
    //sim.setConductances(DG_MOPP, 2.055, 0, 17.214, 30.165, 0, 254.46);// modify,ok(EC-MOPP)
    sim.setConductances(DG_MOPP, 4.84, 0, 23.51, 30.165, 0, 254.46);// modify,ok(EC-MOPP,Gene's simulation)
    
    //sim.setConductances(DG_TML, 2.237, 0, 17.626, 10.586, 0, 164.396);//ok(EC-TML)
    sim.setConductances(DG_TML, 1.0, 0, 14.83, 10.576, 0, 164.352);//ok(EC-TML,Gene's simulation)
    

    // set-up network parameters(C,k,Vr,Vt,a,b,Vpeak,Vmin,d)
    
    //sim.setNeuronParameters(DG_GC, 38.0, 0.0, 0.45, 0.0, -77.4, 0.0, -44.9, 0.0, 0.003, 0.0, 24.48, 0.0, 15.49, 0.0, -66.47, 0.0, 50.0, 0.0);//type1, vr=-77.4, vt=-44.9; hold vr=-57.8 for IPSP 
    sim.setNeuronParameters(DG_GC, 38.0, 0.0, 0.45, 0.0, -77.4, 0.0, -44.9, 0.0, 0.001, 0.0, 10.0, 0.0, 15.49, 0.0, -66.47, 0.0, 50.0, 0.0);//type1, modify a=0.001,b=10, to decrease AHP
    
    sim.setNeuronParameters(DG_MC, 258.0, 0.0, 1.5, 0.0, -63.67, 0.0, -37.11, 0.0, 0.004, 0.0, -20.84, 0.0, 28.29, 0.0, -47.98, 0.0, 117.0, 0.0);//ok
    
    sim.setNeuronParameters(DG_AAC, 109.0, 0.0, 1.52, 0.0, -65.25, 0.0, -54.35, 0.0, 0.049, 0.0, 3.0, 0.0, 5.07, 0.0, -64.47, 0.0, -1.0, 0.0);// modify, eliminate after-hyperpolarization
    
    sim.setNeuronParameters(DG_BC, 208.0, 0.0, 0.81, 0.0, -61.02, 0.0, -45.87, 0.0, 0.097, 0.0, 1.89, 0.0, 14.08, 0.0, -36.23, 0.0, 553.0, 0.0);//DG BC (type1), modified vth match with literature
    //sim.setNeuronParameters(DG_BC, 208.0, 0.0, 0.81, 0.0, -61.02, 0.0, -37.84, 0.0, 0.097, 0.0, 1.89, 0.0, 14.08, 0.0, -36.23, 0.0, 553.0, 0.0);//works
    
    sim.setNeuronParameters(DG_BCCCK, 135.0, 0.0, 0.58, 0.0, -59.0, 0.0, -39.4, 0.0, 0.006, 0.0, -1.24, 0.0, 18.27, 0.0, -42.77, 0.0, 54.0, 0.0);// use CA3 BCCCK for DG BCCCK since there is no DG BCCCK Izhi parameter in Hippo.org
    
    sim.setNeuronParameters(DG_HICAP, 61.0, 0.0, 0.5, 0.0, -61.28, 0.0, -35.36, 0.0, 0.039, 0.0, -1.62, 0.0, 38.79, 0.0, -60.77, 0.0, 49.0, 0.0);
    
    
    sim.setNeuronParameters(DG_HIPP, 132.0, 0.0, 0.55, 0.0, -62.16, 0.0, -43.16, 0.0, 0.043, 0.0, -3.15, 0.0, 13.2, 0.0, -37.71, 0.0, 231.0, 0.0);// modified from DG BC (type2), also make Vth match
    //sim.setNeuronParameters(DG_HIPP, 208.0, 0.0, 0.81, 0.0, -61.02, 0.0, -42.02, 0.0, 0.097, 0.0, 1.89, 0.0, 14.08, 0.0, -36.23, 0.0, 553.0, 0.0);//DG BC (type1), modified vth match with literature
    
    sim.setNeuronParameters(DG_MOPP, 100.0, 0.0, 1.39, 0.0, -74.67, 0.0, -29.07, 0.0, 0.0018, 0.0, -37.42, 0.0, 17.03, 0.0, -47.0, 0.0, 110.0, 0.0);// modified, okay; vth=-74.67mV, dep to -57.8 works
    
    sim.setNeuronParameters(DG_TML, 236.0, 0.0, 0.92, 0.0, -54.91, 0.0, -41.69, 0.0, 0.001, 0.0, -3.12, 0.0, -11.61, 0.0, -48.73, 0.0, 8.0, 0.0);
    //sim.setNeuronParameters(DG_TML, 208.0, 0.0, 0.81, 0.0, -61.02, 0.0, -37.84, 0.0, 0.097, 0.0, 1.89, 0.0, 14.08, 0.0, -36.23, 0.0, 553.0, 0.0);//replace TML as BC
}

}  // namespace hippomodel::DG
