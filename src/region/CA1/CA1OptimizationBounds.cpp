#include "hippomodel/region/CA1/CA1OptimizationBounds.h"
#include "hippomodel/region/CA1/CA1BaselineWeights.h"

#include <stdexcept>
#include <string>

namespace hippomodel::CA1 {

CA1OptimizationBounds makeCA1OptimizationBounds(const std::vector<double>& initGuess,
                                                double lowerScale,
                                                double upperScale) {
    const auto baselineWts = makeCA1BaselineWeights();
    const auto wt = [&](const std::string& name) -> double {
        const auto it = baselineWts.find(name);
        if (it == baselineWts.end()) {
            throw std::runtime_error("Missing CA1 baseline weight for " + name);
        }
        return static_cast<double>(it->second);
    };

    CA1OptimizationBounds bounds;

    // EC_LEC3 as PRE  (indices 0..4)
        double lowerLEC3PC   = lowerScale * initGuess[0];  double upperLEC3PC   = 22 / wt("LEC3_CA1PC"); // 22/0.832, 24 reach AP (type1 modifieda), use 22/ as upper bound
        double lowerLEC3AAC  = lowerScale * initGuess[1];  double upperLEC3AAC  = 43 / wt("LEC3_CA1AAC"); // 43/0.8, 45 reach AP, use 43/ as upper bound
        double lowerLEC3BC   = lowerScale * initGuess[2];  double upperLEC3BC   = 26 / wt("LEC3_CA1BC"); // 26/0.37, 28 reach AP, use 26/ as upper bound
        double lowerLEC3CCK  = lowerScale * initGuess[3];  double upperLEC3CCK  = 66 / wt("LEC3_CA1BCCCK"); // 66/0.9, 68 reach AP, use 66/ as upper bound
        double lowerLEC3NG   = lowerScale * initGuess[4];  double upperLEC3NG   = 5 / wt("LEC3_CA1NG"); // 5/0.55, 7 reach AP, use 5/ as upper bound

        // EC_MEC3 as PRE  (indices 5..9)
        double lowerMEC3PC   = lowerScale * initGuess[5];  double upperMEC3PC   = 22 / wt("MEC3_CA1PC"); // 22/0.832, 24 reach AP (type1 modifieda), use 22/ as upper bound
        double lowerMEC3AAC  = lowerScale * initGuess[6];  double upperMEC3AAC  = 43 / wt("MEC3_CA1AAC"); // 43/0.8, 45 reach AP, use 43/ as upper bound
        double lowerMEC3BC   = lowerScale * initGuess[7];  double upperMEC3BC   = 26 / wt("MEC3_CA1BC"); // 26/0.37, 28 reach AP, use 26/ as upper bound
        double lowerMEC3CCK  = lowerScale * initGuess[8];  double upperMEC3CCK  = 66 / wt("MEC3_CA1BCCCK"); // 66/0.9, 68 reach AP, use 66/ as upper bound
        double lowerMEC3NG   = lowerScale * initGuess[9];  double upperMEC3NG   = 5 / wt("MEC3_CA1NG"); // 5/0.55, 7 reach AP, use 5/ as upper bound
       
       // CA3_PC as PRE  (indices 10..16)
        double lowerCA3PC_PC  = lowerScale * initGuess[10]; double upperCA3PC_PC  = 19 / wt("CA3PC_CA1PC"); // 19/0.255, 21 reach AP (type1 modifieda), use 19/ as upper bound
        double lowerCA3PC_AAC = lowerScale * initGuess[11]; double upperCA3PC_AAC = 43 / wt("CA3PC_CA1AAC"); // 43/2.72, 45 reach AP, use 43/ as upper bound
        double lowerCA3PC_BC  = lowerScale * initGuess[12]; double upperCA3PC_BC  = 26 / wt("CA3PC_CA1BC"); // 26/1.42, 28 reach AP, use 26/ as upper bound
        double lowerCA3PC_CCK = lowerScale * initGuess[13]; double upperCA3PC_CCK = 66 / wt("CA3PC_CA1BCCCK"); // 66/4.52, 68 reach AP, use 66/ as upper bound
        double lowerCA3PC_BisC= lowerScale * initGuess[14]; double upperCA3PC_BisC= 31 / wt("CA3PC_CA1BisC"); // 31/3.89, 33 reach AP, use 31/ as upper bound
        double lowerCA3PC_OLM = lowerScale * initGuess[15]; double upperCA3PC_OLM = 6 / wt("CA3PC_CA1OLM"); // 6/1.27, 8 reach AP, use 6/ as upper bound
        double lowerCA3PC_TL  = lowerScale * initGuess[16]; double upperCA3PC_TL  = 3 / wt("CA3PC_CA1TL"); // 3/0.647, 5 reach AP, use 3/ as upper bound

        // CA1_PC as PRE  (indices 17..23)
        double lowerCA1PC_PC  = lowerScale * initGuess[17]; double upperCA1PC_PC  = 17 / wt("CA1PC_CA1PC"); // 17/1.63, 19 reach AP (type1 modifieda), use 17/ as upper bound
        double lowerCA1PC_AAC = lowerScale * initGuess[18]; double upperCA1PC_AAC = 43 / wt("CA1PC_CA1AAC"); // 43/7.75, 45 reach AP, use 43/ as upper bound
        double lowerCA1PC_BC  = lowerScale * initGuess[19]; double upperCA1PC_BC  = 26 / wt("CA1PC_CA1BC"); // 26/2.84, 28 reach AP, use 26/ as upper bound
        double lowerCA1PC_CCK = lowerScale * initGuess[20]; double upperCA1PC_CCK = 66 / wt("CA1PC_CA1BCCCK"); // 66/12.7, 68 reach AP, use 66/ as upper bound
        double lowerCA1PC_BisC= lowerScale * initGuess[21]; double upperCA1PC_BisC= 31 / wt("CA1PC_CA1BisC"); // 31/5.23, 33 reach AP, use 31/ as upper bound
        double lowerCA1PC_OLM = lowerScale * initGuess[22]; double upperCA1PC_OLM = 6 / wt("CA1PC_CA1OLM"); // 6/1.27, 8 reach AP, use 6/ as upper bound
        double lowerCA1PC_TL  = lowerScale * initGuess[23]; double upperCA1PC_TL  = 3 / wt("CA1PC_CA1TL"); // 3/0.49, 5 reach AP, use 3/ as upper bound

        // CA1_AAC as PRE  (index 24)
        double lowerCA1AAC_PC = lowerScale * initGuess[24]; double upperCA1AAC_PC = upperScale * initGuess[24];

        // CA1_BC as PRE  (indices 25..29)
        double lowerCA1BC_PC  = lowerScale * initGuess[25]; double upperCA1BC_PC  = upperScale * initGuess[25];
        double lowerCA1BC_AAC = lowerScale * initGuess[26]; double upperCA1BC_AAC = upperScale * initGuess[26];
        double lowerCA1BC_BC  = lowerScale * initGuess[27]; double upperCA1BC_BC  = upperScale * initGuess[27];
        double lowerCA1BC_CCK = lowerScale * initGuess[28]; double upperCA1BC_CCK = upperScale * initGuess[28]; // BCCCK
        double lowerCA1BC_BisC= lowerScale * initGuess[29]; double upperCA1BC_BisC= upperScale * initGuess[29];

        // CA1_BCCCK as PRE  (indices 30..34)
        double lowerCA1CCK_PC  = lowerScale * initGuess[30]; double upperCA1CCK_PC  = upperScale * initGuess[30];
        double lowerCA1CCK_AAC = lowerScale * initGuess[31]; double upperCA1CCK_AAC = upperScale * initGuess[31];
        double lowerCA1CCK_BC  = lowerScale * initGuess[32]; double upperCA1CCK_BC  = upperScale * initGuess[32];
        double lowerCA1CCK_CCK = lowerScale * initGuess[33]; double upperCA1CCK_CCK = upperScale * initGuess[33]; // BCCCK
        double lowerCA1CCK_BisC= lowerScale * initGuess[34]; double upperCA1CCK_BisC= upperScale * initGuess[34];

        // CA1_BisC as PRE  (indices 35..41) // use upper = 3.0
        double lowerCA1BisC_PC   = lowerScale * initGuess[35]; double upperCA1BisC_PC   = 1.2 * initGuess[35];
        double lowerCA1BisC_AAC  = lowerScale * initGuess[36]; double upperCA1BisC_AAC  = 3.0 * initGuess[36];
        double lowerCA1BisC_BC   = lowerScale * initGuess[37]; double upperCA1BisC_BC   = 3.0 * initGuess[37];
        double lowerCA1BisC_CCK  = lowerScale * initGuess[38]; double upperCA1BisC_CCK  = 3.0 * initGuess[38]; // BCCCK
        double lowerCA1BisC_BisC = lowerScale * initGuess[39]; double upperCA1BisC_BisC = 1.2 * initGuess[39];// CA1 BisC
        double lowerCA1BisC_OLM  = lowerScale * initGuess[40]; double upperCA1BisC_OLM  = 3.0 * initGuess[40];
        double lowerCA1BisC_TL   = lowerScale * initGuess[41]; double upperCA1BisC_TL   = 1.2 * initGuess[41];

        // CA1_NG as PRE  (indices 42..46)
        double lowerCA1NG_PC  = lowerScale * initGuess[42]; double upperCA1NG_PC  = upperScale * initGuess[42];
        double lowerCA1NG_AAC = lowerScale * initGuess[43]; double upperCA1NG_AAC = upperScale * initGuess[43];
        double lowerCA1NG_BC  = lowerScale * initGuess[44]; double upperCA1NG_BC  = upperScale * initGuess[44];
        double lowerCA1NG_CCK = lowerScale * initGuess[45]; double upperCA1NG_CCK = upperScale * initGuess[45]; // BCCCK
        double lowerCA1NG_NG  = lowerScale * initGuess[46]; double upperCA1NG_NG  = upperScale * initGuess[46];

        // CA1_OLM as PRE  (indices 47..51)
        double lowerCA1OLM_PC  = lowerScale * initGuess[47]; double upperCA1OLM_PC  = upperScale * initGuess[47];
        double lowerCA1OLM_AAC = lowerScale * initGuess[48]; double upperCA1OLM_AAC = upperScale * initGuess[48];
        double lowerCA1OLM_BC  = lowerScale * initGuess[49]; double upperCA1OLM_BC  = upperScale * initGuess[49];
        double lowerCA1OLM_CCK = lowerScale * initGuess[50]; double upperCA1OLM_CCK = upperScale * initGuess[50]; // BCCCK
        double lowerCA1OLM_NG  = lowerScale * initGuess[51]; double upperCA1OLM_NG  = upperScale * initGuess[51];

        // CA1_TL as PRE  (indices 52..58) // use upper = 3.0
        double lowerCA1TL_PC   = lowerScale * initGuess[52]; double upperCA1TL_PC   = 1.2 * initGuess[52];
        double lowerCA1TL_AAC  = lowerScale * initGuess[53]; double upperCA1TL_AAC  = 3.0 * initGuess[53];
        double lowerCA1TL_BC   = lowerScale * initGuess[54]; double upperCA1TL_BC   = 3.0 * initGuess[54];
        double lowerCA1TL_CCK  = lowerScale * initGuess[55]; double upperCA1TL_CCK  = 3.0 * initGuess[55]; // BCCCK
        double lowerCA1TL_BisC = lowerScale * initGuess[56]; double upperCA1TL_BisC = 1.2 * initGuess[56];
        double lowerCA1TL_OLM  = lowerScale * initGuess[57]; double upperCA1TL_OLM  = 3.0 * initGuess[57];
        double lowerCA1TL_TL   = lowerScale * initGuess[58]; double upperCA1TL_TL   = 1.2 * initGuess[58];

        // ----------------------------------------------------------
        // Pack all bounds in CA1ConnectionNames order
        // ----------------------------------------------------------
       
        std::vector<double> lowerBounds = {
            // CA1PC targets (0..10)
            lowerLEC3PC, lowerMEC3PC, lowerCA3PC_PC, lowerCA1PC_PC, 
            lowerCA1AAC_PC, lowerCA1BC_PC, lowerCA1CCK_PC, lowerCA1BisC_PC, lowerCA1NG_PC, lowerCA1OLM_PC, lowerCA1TL_PC,

            // CA1AAC targets (11..20)
            lowerLEC3AAC, lowerMEC3AAC, lowerCA3PC_AAC, lowerCA1PC_AAC, 
            lowerCA1BC_AAC, lowerCA1CCK_AAC, lowerCA1BisC_AAC, lowerCA1NG_AAC, lowerCA1OLM_AAC, lowerCA1TL_AAC,

            // CA1BC targets (21..30)
            lowerLEC3BC, lowerMEC3BC, lowerCA3PC_BC, lowerCA1PC_BC, 
            lowerCA1BC_BC, lowerCA1CCK_BC, lowerCA1BisC_BC, lowerCA1NG_BC, lowerCA1OLM_BC, lowerCA1TL_BC,

            // CA1BCCCK targets (31..40)
            lowerLEC3CCK, lowerMEC3CCK, lowerCA3PC_CCK, lowerCA1PC_CCK, 
            lowerCA1BC_CCK, lowerCA1CCK_CCK, lowerCA1BisC_CCK, lowerCA1NG_CCK, lowerCA1OLM_CCK, lowerCA1TL_CCK,

            // CA1BisC targets (41..46)
            lowerCA3PC_BisC, lowerCA1PC_BisC, 
            lowerCA1BC_BisC, lowerCA1CCK_BisC, lowerCA1BisC_BisC, lowerCA1TL_BisC,

            // CA1NG targets (47..50)
            lowerLEC3NG, lowerMEC3NG, 
            lowerCA1NG_NG, lowerCA1OLM_NG,

            // CA1OLM targets (51..54)
            lowerCA3PC_OLM, lowerCA1PC_OLM, 
            lowerCA1BisC_OLM, lowerCA1TL_OLM,

            // CA1TL targets (55..58)
            lowerCA3PC_TL, lowerCA1PC_TL, 
            lowerCA1BisC_TL, lowerCA1TL_TL
        };

        std::vector<double> upperBounds = {
            // CA1PC targets (0..10)
            upperLEC3PC, upperMEC3PC, upperCA3PC_PC, upperCA1PC_PC, 
            upperCA1AAC_PC, upperCA1BC_PC, upperCA1CCK_PC, upperCA1BisC_PC, upperCA1NG_PC, upperCA1OLM_PC, upperCA1TL_PC,

            // CA1AAC targets (11..20)
            upperLEC3AAC, upperMEC3AAC, upperCA3PC_AAC, upperCA1PC_AAC, 
            upperCA1BC_AAC, upperCA1CCK_AAC, upperCA1BisC_AAC, upperCA1NG_AAC, upperCA1OLM_AAC, upperCA1TL_AAC,

            // CA1BC targets (21..30)
            upperLEC3BC, upperMEC3BC, upperCA3PC_BC, upperCA1PC_BC, 
            upperCA1BC_BC, upperCA1CCK_BC, upperCA1BisC_BC, upperCA1NG_BC, upperCA1OLM_BC, upperCA1TL_BC,

            // CA1BCCCK targets (31..40)
            upperLEC3CCK, upperMEC3CCK, upperCA3PC_CCK, upperCA1PC_CCK, 
            upperCA1BC_CCK, upperCA1CCK_CCK, upperCA1BisC_CCK, upperCA1NG_CCK, upperCA1OLM_CCK, upperCA1TL_CCK,

            // CA1BisC targets (41..46)
            upperCA3PC_BisC, upperCA1PC_BisC, 
            upperCA1BC_BisC, upperCA1CCK_BisC, upperCA1BisC_BisC, upperCA1TL_BisC,

            // CA1NG targets (47..50)
            upperLEC3NG, upperMEC3NG, 
            upperCA1NG_NG, upperCA1OLM_NG,

            // CA1OLM targets (51..54)
            upperCA3PC_OLM, upperCA1PC_OLM, 
            upperCA1BisC_OLM, upperCA1TL_OLM,

            // CA1TL targets (55..58)
            upperCA3PC_TL, upperCA1PC_TL, 
            upperCA1BisC_TL, upperCA1TL_TL
        };

        bounds.lower = lowerBounds;
        bounds.upper = upperBounds;
        return bounds;
}

}  // namespace hippomodel::CA1
