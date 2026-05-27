#include "hippomodel/region/CA3/CA3OptimizationBounds.h"
#include "hippomodel/region/CA3/CA3BaselineWeights.h"

#include <stdexcept>
#include <string>

namespace hippomodel::CA3 {

CA3OptimizationBounds makeCA3OptimizationBounds(
    const std::vector<double>& initGuess,
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

    CA3OptimizationBounds bounds;
    bounds.lower = {
        lowerScale * initGuess[0],
        lowerScale * initGuess[1],
        lowerScale * initGuess[2],
        lowerScale * initGuess[3],
        lowerScale * initGuess[4],
        lowerScale * initGuess[5],
        lowerScale * initGuess[6],
        lowerScale * initGuess[7],
        lowerScale * initGuess[8],
        lowerScale * initGuess[9],
        lowerScale * initGuess[10],
        lowerScale * initGuess[11],
        0.0,
        lowerScale * initGuess[13],
        lowerScale * initGuess[14],
        lowerScale * initGuess[15],
        lowerScale * initGuess[16],
        lowerScale * initGuess[17],
        lowerScale * initGuess[18],
        lowerScale * initGuess[19],
        lowerScale * initGuess[20],
        lowerScale * initGuess[21],
        lowerScale * initGuess[22],
        lowerScale * initGuess[23],
        lowerScale * initGuess[24],
        lowerScale * initGuess[25],
        lowerScale * initGuess[26],
        lowerScale * initGuess[27],
        lowerScale * initGuess[28],
        lowerScale * initGuess[29],
        lowerScale * initGuess[30],
        lowerScale * initGuess[31],
        lowerScale * initGuess[32],
        lowerScale * initGuess[33],
        lowerScale * initGuess[34],
        lowerScale * initGuess[35],
        lowerScale * initGuess[36],
        lowerScale * initGuess[37],
        lowerScale * initGuess[38],
        lowerScale * initGuess[39],
        lowerScale * initGuess[40],
        lowerScale * initGuess[41],
        lowerScale * initGuess[42],
        lowerScale * initGuess[43],
        lowerScale * initGuess[44],
        lowerScale * initGuess[45],
        lowerScale * initGuess[46],
        lowerScale * initGuess[47],
        lowerScale * initGuess[48],
        lowerScale * initGuess[49],
        lowerScale * initGuess[50],
        lowerScale * initGuess[51],
        lowerScale * initGuess[52],
        lowerScale * initGuess[53],
        lowerScale * initGuess[54],
        lowerScale * initGuess[55],
        lowerScale * initGuess[56],
        lowerScale * initGuess[57],
        lowerScale * initGuess[58],
        lowerScale * initGuess[59],
        lowerScale * initGuess[60]
    };
    bounds.upper = {
        7.0 / wt("LEC_CA3PC"), // 7.0/0.23, maxWt to generate AP is 7.0,
        3.3 / wt("MEC_CA3PC"), // 3.3/0.23? keep original AP numerator 3.3; denominator now from MEC_CA3PC,
        3.0 / wt("DGGC_CA3PC"), // 3.0/1.05? denominator from DGGC_CA3PC,
        7.0 / wt("CA3PC_CA3PC"), // 7.0/0.00246, denominator from CA3PC_CA3PC,
        3.3 / wt("CA3AAC_CA3PC"), // 3.3/0.848, denominator from CA3AAC_CA3PC,
        3.0 / wt("CA3BC_CA3PC"), // 3.0/0.848, denominator from CA3BC_CA3PC,
        5.0 / wt("CA3BCCCK_CA3PC"), // 5.0/0.848, denominator from CA3BCCCK_CA3PC,
        3.3 / wt("CA3BisC_CA3PC"), // 3.3/0.53, denominator from CA3BisC_CA3PC,
        3.0 / wt("CA3MFA_CA3PC"), // 3.0/0.848, denominator from CA3MFA_CA3PC,
        4.7 / wt("CA3OLM_CA3PC"), // 4.7/0.848, denominator from CA3OLM_CA3PC,
        3.9 / wt("CA3TL_CA3PC"), // 3.9/0.53, denominator from CA3TL_CA3PC,
        5.9 / wt("LEC_CA3AAC"), // 5.9/0.264, denominator from LEC_CA3AAC,
        0.246 / wt("MEC_CA3AAC"), // 0.246/0.264, denominator from MEC_CA3AAC,
        3.3 / wt("DGGC_CA3AAC"), // 3.3/0.82, denominator from DGGC_CA3AAC,
        3.0 / wt("CA3PC_CA3AAC"), // 3.0/0.35, denominator from CA3PC_CA3AAC,
        4.7 / wt("CA3BCCCK_CA3AAC"), // 4.7/0.3134, denominator from CA3BCCCK_CA3AAC,
        3.9 / wt("CA3BisC_CA3AAC"), // 3.9/0.1959, denominator from CA3BisC_CA3AAC,
        5.9 / wt("CA3OLM_CA3AAC"), // 5.9/0.3134, denominator from CA3OLM_CA3AAC,
        1.7 / wt("CA3TL_CA3AAC"), // 1.7/0.1959, denominator from CA3TL_CA3AAC,
        1.5 / wt("LEC_CA3BC"), // 1.5/0.1275, denominator from LEC_CA3BC,
        upperScale * initGuess[20],
        upperScale * initGuess[21],
        upperScale * initGuess[22],
        upperScale * initGuess[23],
        upperScale * initGuess[24],
        upperScale * initGuess[25],
        upperScale * initGuess[26],
        upperScale * initGuess[27],
        upperScale * initGuess[28],
        upperScale * initGuess[29],
        upperScale * initGuess[30],
        upperScale * initGuess[31],
        upperScale * initGuess[32],
        upperScale * initGuess[33],
        upperScale * initGuess[34],
        upperScale * initGuess[35],
        upperScale * initGuess[36],
        upperScale * initGuess[37],
        upperScale * initGuess[38],
        upperScale * initGuess[39],
        upperScale * initGuess[40],
        upperScale * initGuess[41],
        upperScale * initGuess[42],
        upperScale * initGuess[43],
        upperScale * initGuess[44],
        upperScale * initGuess[45],
        upperScale * initGuess[46],
        upperScale * initGuess[47],
        upperScale * initGuess[48],
        upperScale * initGuess[49],
        upperScale * initGuess[50],
        upperScale * initGuess[51],
        upperScale * initGuess[52],
        upperScale * initGuess[53],
        upperScale * initGuess[54],
        upperScale * initGuess[55],
        upperScale * initGuess[56],
        upperScale * initGuess[57],
        upperScale * initGuess[58],
        upperScale * initGuess[59],
        upperScale * initGuess[60]
    };
    return bounds;
}

}  // namespace hippomodel::CA3
