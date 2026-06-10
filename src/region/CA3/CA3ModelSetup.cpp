#include "hippomodel/region/CA3/CA3ModelSetup.h"

#include <carlsim.h>

#include <map>
#include <string>

namespace hippomodel::CA3 {

void configureCA3CellModels(CARLsim& sim, const std::map<std::string, int>& group_ids) {
    const int CA3_PC    = group_ids.at("CA3_PC");
    const int CA3_AAC   = group_ids.at("CA3_AAC");
    const int CA3_BC    = group_ids.at("CA3_BC");
    const int CA3_BCCCK = group_ids.at("CA3_BCCCK");
    const int CA3_BisC  = group_ids.at("CA3_BisC");
    const int CA3_MFA   = group_ids.at("CA3_MFA");
    const int CA3_OLM   = group_ids.at("CA3_OLM");
    const int CA3_TL    = group_ids.at("CA3_TL");

    //sim.setConductances(true);// COBA, CARLsim default tao must be greater than 1, and tao_slow > tao_fast
    sim.setConductances(CA3_PC, 21.543, 0, 29.122, 4.6, 0, 136.84); //wfa,type2, ok(CA3PC-CA3PC)

    sim.setConductances(CA3_AAC, 7.62, 0, 29.78, 25.57, 0, 233.33); //modify,ok(CA3PC-CA3AAC) 

    sim.setConductances(CA3_BC, 10.06, 0, 35.3, 33.3, 0, 268.89); //ok(CA3PC-CA3BC)
    
    sim.setConductances(CA3_BCCCK, 1.0, 0, 14.83, 28.49, 0, 246.76); //ok(CA3PC-CA3BCCCK,but can't constraint CA3PC-CA3BCCCK)

    sim.setConductances(CA3_BisC, 3.85, 0, 21.28, 1.0, 0, 120.3); //modify,ok(CA3PC-CA3BisC)
    
    sim.setConductances(CA3_MFA, 1.0, 0, 14.83, 26.516, 0, 237.675); //ok(CA3PC-CA3MFA, but can't constraint CA3PC-CA3MFA)

    sim.setConductances(CA3_OLM, 44.62, 0, 113.4, 55.42, 0, 370.65); //ok(CA3PC-CA3OLM)
   
    sim.setConductances(CA3_TL, 16.879, 0, 50.717, 1.0, 0, 120.3); //modified CA1TL(type2),ok(CA3PC-CA3TL)\
    
    
    //sim.setConductances(CA3_PC, 29.3, 0, 34.082, 7.347, 0, 149.498); //wfa:type1, ok(EC-CA3PC)
	//sim.setConductances(CA3_PC, 94.97, 0, 227.21, 7.347, 0, 149.498); //wfa:type1, ok(DGGC-CA3PC)
	//sim.setConductances(CA3_PC, 24.058, 0, 31.065, 7.347, 0, 149.498); //wfa:type1, ok(CA3PC-CA3PC)
	
	
	//sim.setConductances(CA3_PC, 71.677, 0, 116.18, 42.718, 0, 312.203); //burst:type4, ok(EC-CA3PC)
    //sim.setConductances(CA3_PC, 3900.0, 0, 7922.0, 42.718, 0, 312.203);  //burst:type4, ok(DGGC-CA3PC)
	//sim.setConductances(CA3_PC, 61.585, 0, 107.46, 42.718, 0, 312.203);  //burst:type4, ok(CA3PC-CA3PC)

	
	//-----------------------------------------------------------------------------------------------------
    // set-up network parameters(C,k,Vr,Vt,a,b,Vpeak,Vmin,d)
    //-----------------------------------------------------------------------------------------------------
  
    sim.setNeuronParameters(CA3_PC, 297.0, 0.0, 0.54, 0.0, -60.53, 0.0, -39.23, 0.0, 0.004, 0.0, 5.21, 0.0, 38.02, 0.0, -36.52, 0.0, 48.0, 0.0);//wfa: type2,ASP, modify vth=-39.23
        
	sim.setNeuronParameters(CA3_BC, 45.0, 0.0, 1.0, 0.0, -57.51, 0.0, -23.38, 0.0, 0.004, 0.0, 9.26, 0.0, 18.45, 0.0, -47.56, 0.0, -6.0, 0.0);
	
	sim.setNeuronParameters(CA3_AAC, 165.0, 0.0, 3.96, 0.0, -57.1, 0.0, -44.5, 0.0, 0.005, 0.0, 8.68, 0.0, 27.8, 0.0, -73.97, 0.0, 15.0, 0.0);// modify Vt from -51.72 to -44.5
	
	sim.setNeuronParameters(CA3_BCCCK, 135.0, 0.0, 0.58, 0.0, -59.0, 0.0, -39.4, 0.0, 0.006, 0.0, -1.24, 0.0, 18.27, 0.0, -42.77, 0.0, 54.0, 0.0);// CA3 BCCCK
	
	sim.setNeuronParameters(CA3_BisC, 112.0, 0.0, 1.2, 0.0, -64.67, 0.0, -47.67, 0.0, 0.008,0.0, 16.4, 0.0, 3.83, 0.0, -50.2, 0.0, 19.0, 0.0);// CA3 BisC, use modified CA1 BisC(type1),Vth,Vpeak and patterns correct
	
	sim.setNeuronParameters(CA3_MFA, 185.0, 0.0, 0.55, 0.0, -59.41, 0.0, -36.59, 0.0, 0.003, 0.0, 3.69, 0.0, 9.99, 0.0, -43.55, 0.0, 5.0, 0.0);
	//sim.setNeuronParameters(CA3_MFA, 209.0, 0.0, 1.38, 0.0, -57.08, 0.0, -39.1, 0.0, 0.008, 0.0, 12.93, 0.0, 16.31, 0.0, -40.68, 0.0, 0.0, 0.0);//MFA_ORDEN
	
	sim.setNeuronParameters(CA3_OLM, 65.0, 0.0, 0.51, 0.0, -60.04, 0.0, -30.87, 0.0, 0.01, 0.0, 2.39, 0.0, 19.77, 0.0, -52.81, 0.0, 6.0, 0.0);
	
	sim.setNeuronParameters(CA3_TL, 205.0, 0.0, 0.52, 0.0, -64.64, 0.0, -52.64, 0.0, 0.002, 0.0, 1.24, 0.0, 0.17, 0.0, -60.62, 0.0, -19.0, 0.0);//modfified CA1 TL(type2) vth=-52.64, b=1.24
	//CA3 TL parameters are wrong
}

}  // namespace hippomodel::CA3
