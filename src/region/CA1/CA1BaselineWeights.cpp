#include "hippomodel/region/CA1/CA1BaselineWeights.h"

namespace hippomodel::CA1 {

std::vector<ConnectionEndpoint> makeCA1ConnectionEndpoints() {
    return {
        // EC_LEC3 (PRE) -> {CA1_PC, CA1_AAC, CA1_BC, CA1_BCCCK, CA1_NG}
        {"LEC3_CA1PC", "EC_LEC3", "CA1_PC"},
        {"LEC3_CA1AAC", "EC_LEC3", "CA1_AAC"},
        {"LEC3_CA1BC", "EC_LEC3", "CA1_BC"},
        {"LEC3_CA1BCCCK", "EC_LEC3", "CA1_BCCCK"},
        {"LEC3_CA1NG", "EC_LEC3", "CA1_NG"},
        // EC_MEC3 (PRE) -> same 5
        {"MEC3_CA1PC", "EC_MEC3", "CA1_PC"},
        {"MEC3_CA1AAC", "EC_MEC3", "CA1_AAC"},
        {"MEC3_CA1BC", "EC_MEC3", "CA1_BC"},
        {"MEC3_CA1BCCCK", "EC_MEC3", "CA1_BCCCK"},
        {"MEC3_CA1NG", "EC_MEC3", "CA1_NG"},
        // CA3_PC (PRE) -> {PC, AAC, BC, BCCCK, BisC, OLM, TL}
        {"CA3PC_CA1PC", "CA3_PC", "CA1_PC"},
        {"CA3PC_CA1AAC", "CA3_PC", "CA1_AAC"},
        {"CA3PC_CA1BC", "CA3_PC", "CA1_BC"},
        {"CA3PC_CA1BCCCK", "CA3_PC", "CA1_BCCCK"},
        {"CA3PC_CA1BisC", "CA3_PC", "CA1_BisC"},
        {"CA3PC_CA1OLM", "CA3_PC", "CA1_OLM"},
        {"CA3PC_CA1TL", "CA3_PC", "CA1_TL"},
        // CA1_PC (PRE) -> same 7
        {"CA1PC_CA1PC", "CA1_PC", "CA1_PC"},
        {"CA1PC_CA1AAC", "CA1_PC", "CA1_AAC"},
        {"CA1PC_CA1BC", "CA1_PC", "CA1_BC"},
        {"CA1PC_CA1BCCCK", "CA1_PC", "CA1_BCCCK"},
        {"CA1PC_CA1BisC", "CA1_PC", "CA1_BisC"},
        {"CA1PC_CA1OLM", "CA1_PC", "CA1_OLM"},
        {"CA1PC_CA1TL", "CA1_PC", "CA1_TL"},
        // CA1_AAC (PRE) -> {CA1_PC}
        {"CA1AAC_CA1PC", "CA1_AAC", "CA1_PC"},
        // CA1_BC (PRE) -> {PC, AAC, BC, BCCCK, BisC}
        {"CA1BC_CA1PC", "CA1_BC", "CA1_PC"},
        {"CA1BC_CA1AAC", "CA1_BC", "CA1_AAC"},
        {"CA1BC_CA1BC", "CA1_BC", "CA1_BC"},
        {"CA1BC_CA1BCCCK", "CA1_BC", "CA1_BCCCK"},
        {"CA1BC_CA1BisC", "CA1_BC", "CA1_BisC"},
        // CA1_BCCCK (PRE) -> same 5
        {"CA1BCCCK_CA1PC", "CA1_BCCCK", "CA1_PC"},
        {"CA1BCCCK_CA1AAC", "CA1_BCCCK", "CA1_AAC"},
        {"CA1BCCCK_CA1BC", "CA1_BCCCK", "CA1_BC"},
        {"CA1BCCCK_CA1BCCCK", "CA1_BCCCK", "CA1_BCCCK"},
        {"CA1BCCCK_CA1BisC", "CA1_BCCCK", "CA1_BisC"},
        // CA1_BisC (PRE) -> {PC, AAC, BC, BCCCK, BisC, OLM, TL}
        {"CA1BisC_CA1PC", "CA1_BisC", "CA1_PC"},
        {"CA1BisC_CA1AAC", "CA1_BisC", "CA1_AAC"},
        {"CA1BisC_CA1BC", "CA1_BisC", "CA1_BC"},
        {"CA1BisC_CA1BCCCK", "CA1_BisC", "CA1_BCCCK"},
        {"CA1BisC_CA1BisC", "CA1_BisC", "CA1_BisC"},
        {"CA1BisC_CA1OLM", "CA1_BisC", "CA1_OLM"},
        {"CA1BisC_CA1TL", "CA1_BisC", "CA1_TL"},
        // CA1_NG (PRE) -> {PC, AAC, BC, BCCCK, NG}
        {"CA1NG_CA1PC", "CA1_NG", "CA1_PC"},
        {"CA1NG_CA1AAC", "CA1_NG", "CA1_AAC"},
        {"CA1NG_CA1BC", "CA1_NG", "CA1_BC"},
        {"CA1NG_CA1BCCCK", "CA1_NG", "CA1_BCCCK"},
        {"CA1NG_CA1NG", "CA1_NG", "CA1_NG"},
        // CA1_OLM (PRE) -> {PC, AAC, BC, BCCCK, NG}
        {"CA1OLM_CA1PC", "CA1_OLM", "CA1_PC"},
        {"CA1OLM_CA1AAC", "CA1_OLM", "CA1_AAC"},
        {"CA1OLM_CA1BC", "CA1_OLM", "CA1_BC"},
        {"CA1OLM_CA1BCCCK", "CA1_OLM", "CA1_BCCCK"},
        {"CA1OLM_CA1NG", "CA1_OLM", "CA1_NG"},
        // CA1_TL (PRE) -> {PC, AAC, BC, BCCCK, BisC, OLM, TL}
        {"CA1TL_CA1PC", "CA1_TL", "CA1_PC"},
        {"CA1TL_CA1AAC", "CA1_TL", "CA1_AAC"},
        {"CA1TL_CA1BC", "CA1_TL", "CA1_BC"},
        {"CA1TL_CA1BCCCK", "CA1_TL", "CA1_BCCCK"},
        {"CA1TL_CA1BisC", "CA1_TL", "CA1_BisC"},
        {"CA1TL_CA1OLM", "CA1_TL", "CA1_OLM"},
        {"CA1TL_CA1TL", "CA1_TL", "CA1_TL"},
    };
}

std::map<std::string, float> makeCA1BaselineWeights() {
    std::map<std::string, float> baselineWts = {
        // EC_LEC3 (PRE) -> {CA1_PC, CA1_AAC, CA1_BC, CA1_BCCCK, CA1_NG}
        {"LEC3_CA1PC",    0.9f}, // 0.104 borrow PSP, at least 0.85 EC-CA3PC can generate spike; try 0.9
        {"LEC3_CA1AAC",   0.8f},
        {"LEC3_CA1BC",    0.37f},
        {"LEC3_CA1BCCCK", 0.9f},
        {"LEC3_CA1NG",    0.55f},
        // EC_MEC3 (PRE) -> same 5
        {"MEC3_CA1PC",    0.9f}, // 0.104 borrow PSP, at least 0.85 EC-CA3PC can generate spike; try 0.9
        {"MEC3_CA1AAC",   0.8f},
        {"MEC3_CA1BC",    0.37f},
        {"MEC3_CA1BCCCK", 0.9f},
        {"MEC3_CA1NG",    0.55f},
        // CA3_PC (PRE) -> {PC, AAC, BC, BCCCK, BisC, OLM, TL}
        {"CA3PC_CA1PC",    0.255f}, // 0.255 PSP
        {"CA3PC_CA1AAC",   2.72f},
        {"CA3PC_CA1BC",    1.42f},
        {"CA3PC_CA1BCCCK", 4.52f},
        {"CA3PC_CA1BisC",  3.89f},
        {"CA3PC_CA1OLM",   1.27f},
        {"CA3PC_CA1TL",    0.647f},
        // CA1_PC (PRE) -> same 7
        {"CA1PC_CA1PC",    1.63f}, // 1.63 PSP
        {"CA1PC_CA1AAC",   7.75f},
        {"CA1PC_CA1BC",    2.84f},
        {"CA1PC_CA1BCCCK", 12.7f},
        {"CA1PC_CA1BisC",  5.23f},
        {"CA1PC_CA1OLM",   1.27f},
        {"CA1PC_CA1TL",    0.49f},
        // CA1_AAC (PRE) -> {CA1_PC}
        {"CA1AAC_CA1PC",   3.17f}, // 3.17
        // CA1_BC (PRE) -> {PC, AAC, BC, BCCCK, BisC}
        {"CA1BC_CA1PC",    10.72f}, // 10.72
        {"CA1BC_CA1AAC",   1.8f},
        {"CA1BC_CA1BC",    0.947f},
        {"CA1BC_CA1BCCCK", 1.88f},
        {"CA1BC_CA1BisC",  3.47f},
        // CA1_BCCCK (PRE) -> same 5
        {"CA1BCCCK_CA1PC",    10.72f},
        {"CA1BCCCK_CA1AAC",   1.8f},
        {"CA1BCCCK_CA1BC",    0.947f},
        {"CA1BCCCK_CA1BCCCK", 1.88f},
        {"CA1BCCCK_CA1BisC",  3.47f},
        // CA1_BisC (PRE) -> {PC, AAC, BC, BCCCK, BisC, OLM, TL}
        {"CA1BisC_CA1PC",    1.367f},
        {"CA1BisC_CA1AAC",   1.8f},
        {"CA1BisC_CA1BC",    1.29f},
        {"CA1BisC_CA1BCCCK", 1.88f},
        {"CA1BisC_CA1BisC",  0.62f},
        {"CA1BisC_CA1OLM",   1.0f},
        {"CA1BisC_CA1TL",    0.104f},
        // CA1_NG (PRE) -> {PC, AAC, BC, BCCCK, NG}
        {"CA1NG_CA1PC",    4.215f},
        {"CA1NG_CA1AAC",   1.8f},
        {"CA1NG_CA1BC",    0.947f},
        {"CA1NG_CA1BCCCK", 1.88f},
        {"CA1NG_CA1NG",    3.7f},
        // CA1_OLM (PRE) -> {PC, AAC, BC, BCCCK, NG}
        {"CA1OLM_CA1PC",    10.72f},
        {"CA1OLM_CA1AAC",   1.8f},
        {"CA1OLM_CA1BC",    0.947f},
        {"CA1OLM_CA1BCCCK", 1.88f},
        {"CA1OLM_CA1NG",    3.7f},
        // CA1_TL (PRE) -> {PC, AAC, BC, BCCCK, BisC, OLM, TL}
        {"CA1TL_CA1PC",    0.365f},
        {"CA1TL_CA1AAC",   1.8f},
        {"CA1TL_CA1BC",    1.29f},
        {"CA1TL_CA1BCCCK", 1.88f},
        {"CA1TL_CA1BisC",  0.62f},
        {"CA1TL_CA1OLM",   0.69f},
        {"CA1TL_CA1TL",    0.86f},
    };
    return baselineWts;
}

}  // namespace hippomodel::CA1
