#include "hippomodel/region/CA3/CA3OptimizationBounds.h"
#include "hippomodel/region/CA3/CA3BaselineWeights.h"

#include <stdexcept>
#include <string>

namespace hippomodel::CA3 {
CA3OptimizationBounds makeCA3OptimizationBounds(const std::vector<double>& initGuess,
                                            double lowerScale,
                                            double upperScale) {
    const auto baselineWts = makeCA3BaselineWeights();
    const auto wt = [&](const std::string& name) -> double {
        const auto it = baselineWts.find(name);
        if (it == baselineWts.end()) {
            throw std::runtime_error("Missing CA3 baseline weight for " + name);
        }
        return static_cast<double>(it->second);
    };

        // Upper EC/GC/PC - PC is calculated based on seperated AMPA:NMDA gain (1:0.268; 1:0.97; 1:1.633) and 21.543ms, 29.122ms decay time
        
        // --------------------------- EC_LEC as PRE --------------------------- (indices 0..2)
        double lowerLEC_CA3PC  = lowerScale * initGuess[0];  double upperLEC_CA3PC  = 4.5 / wt("LEC_CA3PC");   // 8.2 reach AP, use 4.5 for lower undershoot
        double lowerLEC_CA3AAC = lowerScale * initGuess[1];  double upperLEC_CA3AAC = 2.4 / wt("LEC_CA3AAC");  // 3.4 reach AP
        double lowerLEC_CA3BC  = lowerScale * initGuess[2];  double upperLEC_CA3BC  = 2.1 / wt("LEC_CA3BC");   // 3.1 reach AP

        // --------------------------- EC_MEC as PRE --------------------------- (indices 3..5)
        double lowerMEC_CA3PC  = lowerScale * initGuess[3];  double upperMEC_CA3PC  = 4.5 / wt("MEC_CA3PC");   // 8.2 reach AP, use 4.5 for lower undershoot
        double lowerMEC_CA3AAC = lowerScale * initGuess[4];  double upperMEC_CA3AAC = 2.4 / wt("MEC_CA3AAC");  // 3.4 reach AP
        double lowerMEC_CA3BC  = lowerScale * initGuess[5];  double upperMEC_CA3BC  = 2.1 / wt("MEC_CA3BC");   // 3.1 reach AP

        // --------------------------- DG_GC as PRE ---------------------------- (indices 6..11)
        double lowerDGGC_CA3PC    = lowerScale * initGuess[6];   double upperDGGC_CA3PC    = 4.0 / wt("DGGC_CA3PC");     // 6.2 reach AP, use 4.0 for lower undershoot
        double lowerDGGC_CA3AAC   = lowerScale * initGuess[7];   double upperDGGC_CA3AAC   = 2.7 / wt("DGGC_CA3AAC");    // 3.4 reach AP
        double lowerDGGC_CA3BC    = lowerScale * initGuess[8];   double upperDGGC_CA3BC    = 2.4 / wt("DGGC_CA3BC");     // 3.1 reach AP
        double lowerDGGC_CA3BCCCK = lowerScale * initGuess[9];   double upperDGGC_CA3BCCCK = 3.7 / wt("DGGC_CA3BCCCK");  // 4.8 reach AP
        double lowerDGGC_CA3BisC  = lowerScale * initGuess[10];  double upperDGGC_CA3BisC  = 3.0 / wt("DGGC_CA3BisC");   // 4.0 reach AP
        double lowerDGGC_CA3MFA   = lowerScale * initGuess[11];  double upperDGGC_CA3MFA   = 4.8 / wt("DGGC_CA3MFA");    // 6.0 reach AP

        // --------------------------- CA3_PC as PRE --------------------------- (indices 12..19)
        double lowerCA3PC_CA3PC    = 1.0 / 10.0;                   double upperCA3PC_CA3PC    = 20;  // CA3PC-CA3PC; 
        double lowerCA3PC_CA3AAC   = lowerScale * initGuess[13];   double upperCA3PC_CA3AAC   = 2.4 / wt("CA3PC_CA3AAC");   // 3.4 reach AP
        double lowerCA3PC_CA3BC    = lowerScale * initGuess[14];   double upperCA3PC_CA3BC    = 2.1 / wt("CA3PC_CA3BC");    // 3.1 reach AP
        double lowerCA3PC_CA3BCCCK = lowerScale * initGuess[15];   double upperCA3PC_CA3BCCCK = 3.2 / wt("CA3PC_CA3BCCCK"); // 4.8 reach AP
        double lowerCA3PC_CA3BisC  = lowerScale * initGuess[16];   double upperCA3PC_CA3BisC  = 2.5 / wt("CA3PC_CA3BisC");  // 4.0 reach AP
        double lowerCA3PC_CA3MFA   = lowerScale * initGuess[17];   double upperCA3PC_CA3MFA   = 4.0 / wt("CA3PC_CA3MFA");   // 6.0 reach AP
        double lowerCA3PC_CA3OLM   = lowerScale * initGuess[18];   double upperCA3PC_CA3OLM   = 1.1 / wt("CA3PC_CA3OLM");   // 1.8 reach AP
        double lowerCA3PC_CA3TL    = lowerScale * initGuess[19];   double upperCA3PC_CA3TL    = 1.0 / wt("CA3PC_CA3TL");    // 1.6 reach AP

        // --------------------------- CA3_AAC as PRE -------------------------- (index 19)
        double lowerCA3AAC_CA3PC = lowerScale * initGuess[20];  double upperCA3AAC_CA3PC = upperScale * initGuess[20];


        // --------------------------- CA3_BC as PRE --------------------------- (indices 20..24)
        double lowerCA3BC_CA3PC    = lowerScale * initGuess[21]; double upperCA3BC_CA3PC    = upperScale * initGuess[21];
        double lowerCA3BC_CA3BC    = lowerScale * initGuess[22]; double upperCA3BC_CA3BC    = upperScale * initGuess[22];
        double lowerCA3BC_CA3BCCCK = lowerScale * initGuess[23]; double upperCA3BC_CA3BCCCK = upperScale * initGuess[23];
        double lowerCA3BC_CA3BisC  = lowerScale * initGuess[24]; double upperCA3BC_CA3BisC  = upperScale * initGuess[24];
        double lowerCA3BC_CA3MFA   = lowerScale * initGuess[25]; double upperCA3BC_CA3MFA   = upperScale * initGuess[25];


        // --------------------------- CA3_BCCCK as PRE ------------------------ (indices 25..30)
        double lowerCA3BCCCK_CA3PC    = lowerScale * initGuess[26]; double upperCA3BCCCK_CA3PC    = upperScale * initGuess[26];
        double lowerCA3BCCCK_CA3AAC   = lowerScale * initGuess[27]; double upperCA3BCCCK_CA3AAC   = upperScale * initGuess[27];
        double lowerCA3BCCCK_CA3BC    = lowerScale * initGuess[28]; double upperCA3BCCCK_CA3BC    = upperScale * initGuess[28];
        double lowerCA3BCCCK_CA3BCCCK = lowerScale * initGuess[29]; double upperCA3BCCCK_CA3BCCCK = upperScale * initGuess[29];
        double lowerCA3BCCCK_CA3BisC  = lowerScale * initGuess[30]; double upperCA3BCCCK_CA3BisC  = upperScale * initGuess[30];
        double lowerCA3BCCCK_CA3MFA   = lowerScale * initGuess[31]; double upperCA3BCCCK_CA3MFA   = upperScale * initGuess[31];

        // --------------------------- CA3_BisC as PRE ------------------------- (indices 31..38)
        double lowerCA3BisC_CA3PC    = lowerScale * initGuess[32]; double upperCA3BisC_CA3PC    = 5 * initGuess[32];// 5.0*init
        double lowerCA3BisC_CA3AAC   = lowerScale * initGuess[33]; double upperCA3BisC_CA3AAC   = 5 * initGuess[33];
        double lowerCA3BisC_CA3BC    = lowerScale * initGuess[34]; double upperCA3BisC_CA3BC    = 5 * initGuess[34];
        double lowerCA3BisC_CA3BCCCK = lowerScale * initGuess[35]; double upperCA3BisC_CA3BCCCK = 5 * initGuess[35];
        double lowerCA3BisC_CA3BisC  = lowerScale * initGuess[36]; double upperCA3BisC_CA3BisC  = 5 * initGuess[36];
        double lowerCA3BisC_CA3MFA   = lowerScale * initGuess[37]; double upperCA3BisC_CA3MFA   = 5 * initGuess[37];
        double lowerCA3BisC_CA3OLM   = lowerScale * initGuess[38]; double upperCA3BisC_CA3OLM   = 5 * initGuess[38];
        double lowerCA3BisC_CA3TL    = lowerScale * initGuess[39]; double upperCA3BisC_CA3TL    = 5 * initGuess[39];


        // --------------------------- CA3_MFA as PRE -------------------------- (indices 39..43)
        double lowerCA3MFA_CA3PC    = lowerScale * initGuess[40]; double upperCA3MFA_CA3PC    = upperScale * initGuess[40];
        double lowerCA3MFA_CA3BC    = lowerScale * initGuess[41]; double upperCA3MFA_CA3BC    = upperScale * initGuess[41];
        double lowerCA3MFA_CA3BCCCK = lowerScale * initGuess[42]; double upperCA3MFA_CA3BCCCK = upperScale * initGuess[42];
        double lowerCA3MFA_CA3BisC  = lowerScale * initGuess[43]; double upperCA3MFA_CA3BisC  = upperScale * initGuess[43];
        double lowerCA3MFA_CA3MFA   = lowerScale * initGuess[44]; double upperCA3MFA_CA3MFA   = upperScale * initGuess[44];


        // --------------------------- CA3_OLM as PRE -------------------------- (indices 44..51)
        double lowerCA3OLM_CA3PC    = lowerScale * initGuess[45]; double upperCA3OLM_CA3PC    = upperScale * initGuess[45];
        double lowerCA3OLM_CA3AAC   = lowerScale * initGuess[46]; double upperCA3OLM_CA3AAC   = upperScale * initGuess[46];
        double lowerCA3OLM_CA3BC    = lowerScale * initGuess[47]; double upperCA3OLM_CA3BC    = upperScale * initGuess[47];
        double lowerCA3OLM_CA3BCCCK = lowerScale * initGuess[48]; double upperCA3OLM_CA3BCCCK = upperScale * initGuess[48];
        double lowerCA3OLM_CA3BisC  = lowerScale * initGuess[49]; double upperCA3OLM_CA3BisC  = upperScale * initGuess[49];
        double lowerCA3OLM_CA3MFA   = lowerScale * initGuess[50]; double upperCA3OLM_CA3MFA   = upperScale * initGuess[50];
        double lowerCA3OLM_CA3OLM   = lowerScale * initGuess[51]; double upperCA3OLM_CA3OLM   = upperScale * initGuess[51];
        double lowerCA3OLM_CA3TL    = lowerScale * initGuess[52]; double upperCA3OLM_CA3TL    = upperScale * initGuess[52];


        // --------------------------- CA3_TL as PRE --------------------------- (indices 52..59)
        double lowerCA3TL_CA3PC    = lowerScale * initGuess[53]; double upperCA3TL_CA3PC    = 5 * initGuess[53];// 5.0*init
        double lowerCA3TL_CA3AAC   = lowerScale * initGuess[54]; double upperCA3TL_CA3AAC   = 5 * initGuess[54];
        double lowerCA3TL_CA3BC    = lowerScale * initGuess[55]; double upperCA3TL_CA3BC    = 5 * initGuess[55];
        double lowerCA3TL_CA3BCCCK = lowerScale * initGuess[56]; double upperCA3TL_CA3BCCCK = 5 * initGuess[56];
        double lowerCA3TL_CA3BisC  = lowerScale * initGuess[57]; double upperCA3TL_CA3BisC  = 5 * initGuess[57];
        double lowerCA3TL_CA3MFA   = lowerScale * initGuess[58]; double upperCA3TL_CA3MFA   = 5 * initGuess[58];
        double lowerCA3TL_CA3OLM   = lowerScale * initGuess[59]; double upperCA3TL_CA3OLM   = 5 * initGuess[59];
        double lowerCA3TL_CA3TL    = lowerScale * initGuess[60]; double upperCA3TL_CA3TL    = 5 * initGuess[60];

    CA3OptimizationBounds bounds;
    bounds.lower = {
           // CA3PC targets (0..10)
            lowerLEC_CA3PC, lowerMEC_CA3PC, lowerDGGC_CA3PC, lowerCA3PC_CA3PC, 
            lowerCA3AAC_CA3PC, lowerCA3BC_CA3PC, lowerCA3BCCCK_CA3PC, lowerCA3BisC_CA3PC, lowerCA3MFA_CA3PC, lowerCA3OLM_CA3PC, lowerCA3TL_CA3PC,

            // CA3AAC targets (11..18)
            lowerLEC_CA3AAC, lowerMEC_CA3AAC, lowerDGGC_CA3AAC, 
            lowerCA3PC_CA3AAC, lowerCA3BCCCK_CA3AAC, lowerCA3BisC_CA3AAC, lowerCA3OLM_CA3AAC, lowerCA3TL_CA3AAC,

            // CA3BC targets (19..28)
            lowerLEC_CA3BC, lowerMEC_CA3BC, lowerDGGC_CA3BC, lowerCA3PC_CA3BC, 
            lowerCA3BC_CA3BC, lowerCA3BCCCK_CA3BC, lowerCA3BisC_CA3BC, lowerCA3MFA_CA3BC, lowerCA3OLM_CA3BC, lowerCA3TL_CA3BC,

            // CA3BCCCK targets (29..36)
            lowerDGGC_CA3BCCCK, lowerCA3PC_CA3BCCCK, 
            lowerCA3BC_CA3BCCCK, lowerCA3BCCCK_CA3BCCCK, lowerCA3BisC_CA3BCCCK, lowerCA3MFA_CA3BCCCK, lowerCA3OLM_CA3BCCCK, lowerCA3TL_CA3BCCCK,

            // CA3BisC targets (37..44)
            lowerDGGC_CA3BisC, lowerCA3PC_CA3BisC, 
            lowerCA3BC_CA3BisC, lowerCA3BCCCK_CA3BisC, lowerCA3BisC_CA3BisC, lowerCA3MFA_CA3BisC, lowerCA3OLM_CA3BisC, lowerCA3TL_CA3BisC,

            // CA3MFA targets (45..52)
            lowerDGGC_CA3MFA, lowerCA3PC_CA3MFA, 
            lowerCA3BC_CA3MFA, lowerCA3BCCCK_CA3MFA, lowerCA3BisC_CA3MFA, lowerCA3MFA_CA3MFA, lowerCA3OLM_CA3MFA, lowerCA3TL_CA3MFA,

            // CA3OLM targets (53..56)
            lowerCA3PC_CA3OLM, 
            lowerCA3BisC_CA3OLM, lowerCA3OLM_CA3OLM, lowerCA3TL_CA3OLM,

            // CA3TL targets (57..60)
            lowerCA3PC_CA3TL, 
            lowerCA3BisC_CA3TL, lowerCA3OLM_CA3TL, lowerCA3TL_CA3TL
    };

    bounds.upper = {
         // CA3PC targets (0..10)
            upperLEC_CA3PC, upperMEC_CA3PC, upperDGGC_CA3PC, upperCA3PC_CA3PC, 
            upperCA3AAC_CA3PC, upperCA3BC_CA3PC, upperCA3BCCCK_CA3PC, upperCA3BisC_CA3PC, upperCA3MFA_CA3PC, upperCA3OLM_CA3PC, upperCA3TL_CA3PC,

            // CA3AAC targets (11..18)
            upperLEC_CA3AAC, upperMEC_CA3AAC, upperDGGC_CA3AAC, upperCA3PC_CA3AAC, 
            upperCA3BCCCK_CA3AAC, upperCA3BisC_CA3AAC, upperCA3OLM_CA3AAC, upperCA3TL_CA3AAC,

            // CA3BC targets (19..28)
            upperLEC_CA3BC, upperMEC_CA3BC, upperDGGC_CA3BC, upperCA3PC_CA3BC, 
            upperCA3BC_CA3BC, upperCA3BCCCK_CA3BC, upperCA3BisC_CA3BC, upperCA3MFA_CA3BC, upperCA3OLM_CA3BC, upperCA3TL_CA3BC,

            // CA3BCCCK targets (29..36)
            upperDGGC_CA3BCCCK, upperCA3PC_CA3BCCCK, 
            upperCA3BC_CA3BCCCK, upperCA3BCCCK_CA3BCCCK, upperCA3BisC_CA3BCCCK, upperCA3MFA_CA3BCCCK, upperCA3OLM_CA3BCCCK, upperCA3TL_CA3BCCCK,

            // CA3BisC targets (37..44)
            upperDGGC_CA3BisC, upperCA3PC_CA3BisC, 
            upperCA3BC_CA3BisC, upperCA3BCCCK_CA3BisC, upperCA3BisC_CA3BisC, upperCA3MFA_CA3BisC, upperCA3OLM_CA3BisC, upperCA3TL_CA3BisC,

            // CA3MFA targets (45..52)
            upperDGGC_CA3MFA, upperCA3PC_CA3MFA, 
            upperCA3BC_CA3MFA, upperCA3BCCCK_CA3MFA, upperCA3BisC_CA3MFA, upperCA3MFA_CA3MFA, upperCA3OLM_CA3MFA, upperCA3TL_CA3MFA,

            // CA3OLM targets (53..56)
            upperCA3PC_CA3OLM, 
            upperCA3BisC_CA3OLM, upperCA3OLM_CA3OLM, upperCA3TL_CA3OLM,

            // CA3TL targets (57..60)
            upperCA3PC_CA3TL, 
            upperCA3BisC_CA3TL, upperCA3OLM_CA3TL, upperCA3TL_CA3TL
    };

    return bounds;
}

}  // namespace hippomodel::CA3
