#include "hippomodel/region/CA1/CA1ModelSetup.h"

#include <carlsim.h>

#include <map>
#include <string>

namespace hippomodel::CA1 {

void configureCA1CellModels(CARLsim& sim, const std::map<std::string, int>& group_ids) {
    const int CA1_PC    = group_ids.at("CA1_PC");
    const int CA1_AAC   = group_ids.at("CA1_AAC");
    const int CA1_BC    = group_ids.at("CA1_BC");
    const int CA1_BCCCK = group_ids.at("CA1_BCCCK");
    const int CA1_BisC  = group_ids.at("CA1_BisC");
    const int CA1_NG    = group_ids.at("CA1_NG");
    const int CA1_OLM   = group_ids.at("CA1_OLM");
    const int CA1_TL    = group_ids.at("CA1_TL");

    //sim.setConductances(true);// COBA
    //sim.setConductances(CA1_PC, 36.68, 0, 95.47, 1.6, 0, 123.08); //ok(CA3PC-CA1PC,CA1BC-CA1PC,type1)
    sim.setConductances(CA1_PC, 3.978, 0, 21.56, 1.6, 0, 123.08); //ok(CA3PC-CA1PC,CA1BC-CA1PC,type1)
    //sim.setConductances(CA1_PC, 3.978, 0, 21.56, 40.317, 0, 301.158); //ok(CA3PC-CA1PC,CA1BC-CA1PC,type1)
    sim.setConductances(CA1_AAC, 1.36, 0, 15.65, 15.55, 0, 187.23); //ok(CA3PC-CA1AAC, CA1BC-CA1AAC)
    sim.setConductances(CA1_BC, 1.0, 0, 14.83, 29.4, 0, 250.92);//ok(CA3PC-CA1BC, CA1BisC-CA1BC)
    sim.setConductances(CA1_BCCCK, 1.0, 0, 14.83, 16.6, 0, 192.04);//ok(CA3PC-CA1BCCCK, CA1BC-CA1BCCCK),type2 (modify,correct EPSP shape)
    //sim.setConductances(CA1_BisC, 1.1, 0, 15.06, 33.69, 0, 270.67); //modify,ok(CA1PC-CA3BisC)type1
    sim.setConductances(CA1_BisC, 2.26, 0, 17.67, 32.65, 0, 265.9); //ok(CA3PC-CA1BisC,CA1BisC-CA1BisC)type2
    sim.setConductances(CA1_NG, 25.61, 0, 70.44, 3.0, 0, 129.5); //ok(EC-CA1NG,-CA1NG)
    sim.setConductances(CA1_OLM, 4.45, 0, 22.64, 31.6, 0, 261.06); //ok(CA3/CA1PC-CA1OLM, CA1BisC-CA1OLM),modify CA1 OLM
    sim.setConductances(CA1_TL, 1.0, 0, 14.83, 17.566, 0, 196.5); //ok(CA3/CA1PC-CA1TL,CA1BC-CA1TL),type1 modify

    // set-up network parameters(C,k,Vr,Vt,a,b,Vpeak,Vmin,d)
    sim.setNeuronParameters(CA1_PC, 334.0, 0.0, 1.56, 0.0, -65.77, 0.0, -53.22, 0.0, 0.001, 0.0, 4.0, 0.0, 25.46, 0.0, -60.22, 0.0, 15.0, 0.0);//modified type1, a=0.001,b=4,d=15,vr=-65.77
    //sim.setNeuronParameters(CA1_PC, 334.0, 0.0, 1.56, 0.0, -69.36, 0.0, -53.22, 0.0, 0.001, 0.0, -17.25, 0.0, 25.46, 0.0, -60.22, 0.0, 16.0, 0.0);//modified type1, a=0.001,b=-17.25,d=16
    sim.setNeuronParameters(CA1_AAC, 287.0, 0.0, 4.0, 0.0, -65.16, 0.0, -49.04, 0.0, 0.013, 0.0, -4.02, 0.0, 15.13, 0.0, -55.48, 0.0, 38.0, 0.0);// CA1 AAC, type2 ASP, modify vpeak from -0.61 to 15.13 to fix its action potential as its original vpeak<0
    sim.setNeuronParameters(CA1_BC, 114.0, 0.0, 1.19, 0.0, -57.63, 0.0, -35.53, 0.0, 0.005, 0.0, 0.22, 0.0, 21.72, 0.0, -48.7, 0.0, 2.0, 0.0);
    sim.setNeuronParameters(CA1_BCCCK, 477.0, 0.0, 2.0, 0.0, -63.1, 0.0, -40.6, 0.0, 0.04, 0.0, -12.2, 0.0, 27.12, 0.0, -56.15, 0.0, 460.0, 0.0);// CA1 BCCCK, type2, modify k,a,Vr so that IPSP shape correct and pattern also correct
    //sim.setNeuronParameters(CA1_BCCCK, 477.0, 0.0, 2.48, 0.0, -63.1, 0.0, -51.93, 0.0, 0.016, 0.0, -12.2, 0.0, 27.12, 0.0, -56.15, 0.0, 460.0, 0.0);// CA1 BCCCK, type2, incorrect IPSP shape
    //sim.setNeuronParameters(CA1_BCCCK, 59.0, 0.0, 1.06, 0.0, -63.18, 0.0, -38.18, 0.0, 0.023, 0.0, -26.87, 0.0, 27.44, 0.0, -53.32, 0.0, 294.0, 0.0);// CA1 BCCCK, type1 incorrect EPSP shape
    sim.setNeuronParameters(CA1_BisC, 208.0, 0.0, 3.06, 0.0, -64.94, 0.0, -44.58, 0.0, 0.026, 0.0, 7.36, 0.0, 6.92, 0.0, -51.09, 0.0, 4, 0.0); //CA1 Bistratified type2 modift AP amplitude (avg 51.5)
    //sim.setNeuronParameters(CA1_BisC, 112.0, 0.0, 1.2, 0.0, -64.67, 0.0, -47.67, 0.0, 0.008,0.0, 16.4, 0.0, 3.83, 0.0, -50.2, 0.0, 19.0, 0.0);// modified CA1 BisC(type1),Vth,Vpeak and patterns correct
    sim.setNeuronParameters(CA1_NG, 254.0, 0.0, 2.36, 0.0, -63.33, 0.0, -47.62, 0.0, 0.0075, 0.0, 9.2, 0.0, 10.7, 0.0, -50.78, 0.0, 80, 0.0); //modified CA1 Neurogliaform to avoid undershoot: decrease b to 9.2, then decrease a = 0.0075, increase d = 80
    //sim.setNeuronParameters(CA1_OLM, 65.0, 0.0, 0.51, 0.0, -60.04, 0.0, -30.87, 0.0, 0.01, 0.0, 2.39, 0.0, 19.77, 0.0, -52.81, 0.0, 6.0, 0.0);//use CA3 OLM parameters
    //sim.setNeuronParameters(CA1_OLM, 73.0, 0.0, 4.47, 0.0, -60, 0.0, -56.41, 0.0, 0.069, 0.0, 74.3, 0.0, 7.99, 0.0, -58.16, 0.0, 299, 0.0); //CA1 OLM,wrong
    sim.setNeuronParameters(CA1_OLM, 103.0, 0.0, 2.1, 0.0, -60, 0.0, -46.0, 0.0, 0.001, 0.0, 42.0, 0.0, 7.99, 0.0, -58.16, 0.0, 14, 0.0); //modify CA1 OLM
    //sim.setNeuronParameters(CA1_TL, 38.0, 0.0, 0.16, 0.0, -60.94, 0.0, -46.19, 0.0, 0.004, 0.0, 2.72, 0.0, -0.92, 0.0, -55.34, 0.0, -3, 0.0);//CA1 Trilaminar, subtype1
    sim.setNeuronParameters(CA1_TL, 45.0, 0.0, 0.16, 0.0, -60.94, 0.0, -46.19, 0.0, 0.001, 0.0, 1, 0.0, -0.92, 0.0, -55.34, 0.0, 3, 0.0);//CA1 Trilaminar, subtype1 modify: decrease a to 0.001 to avoid rebound, and increase C to 45, increase d to 1 to avoid cell become too excitable
}

}  // namespace hippomodel::CA1
