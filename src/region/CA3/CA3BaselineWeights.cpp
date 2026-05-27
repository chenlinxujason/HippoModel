#include "hippomodel/region/CA3/CA3BaselineWeights.h"

namespace hippomodel::CA3 {

std::vector<ConnectionEndpoint> makeCA3ConnectionEndpoints() {
    return {
        // EC_LEC (3)
        {"LEC_CA3PC", "EC_LEC", "CA3_PC"},
        {"LEC_CA3AAC", "EC_LEC", "CA3_AAC"},
        {"LEC_CA3BC", "EC_LEC", "CA3_BC"},
        // EC_MEC (3)
        {"MEC_CA3PC", "EC_MEC", "CA3_PC"},
        {"MEC_CA3AAC", "EC_MEC", "CA3_AAC"},
        {"MEC_CA3BC", "EC_MEC", "CA3_BC"},
        // DG_GC (6)
        {"DGGC_CA3PC", "DG_GC", "CA3_PC"},
        {"DGGC_CA3AAC", "DG_GC", "CA3_AAC"},
        {"DGGC_CA3BC", "DG_GC", "CA3_BC"},
        {"DGGC_CA3BCCCK", "DG_GC", "CA3_BCCCK"},
        {"DGGC_CA3BisC", "DG_GC", "CA3_BisC"},
        {"DGGC_CA3MFA", "DG_GC", "CA3_MFA"},
        // CA3_PC (8)
        {"CA3PC_CA3PC", "CA3_PC", "CA3_PC"},
        {"CA3PC_CA3AAC", "CA3_PC", "CA3_AAC"},
        {"CA3PC_CA3BC", "CA3_PC", "CA3_BC"},
        {"CA3PC_CA3BCCCK", "CA3_PC", "CA3_BCCCK"},
        {"CA3PC_CA3BisC", "CA3_PC", "CA3_BisC"},
        {"CA3PC_CA3MFA", "CA3_PC", "CA3_MFA"},
        {"CA3PC_CA3OLM", "CA3_PC", "CA3_OLM"},
        {"CA3PC_CA3TL", "CA3_PC", "CA3_TL"},
        // CA3_AAC (1)
        {"CA3AAC_CA3PC", "CA3_AAC", "CA3_PC"},
        // CA3_BC (5)
        {"CA3BC_CA3PC", "CA3_BC", "CA3_PC"},
        {"CA3BC_CA3BC", "CA3_BC", "CA3_BC"},
        {"CA3BC_CA3BCCCK", "CA3_BC", "CA3_BCCCK"},
        {"CA3BC_CA3BisC", "CA3_BC", "CA3_BisC"},
        {"CA3BC_CA3MFA", "CA3_BC", "CA3_MFA"},
        // CA3_BCCCK (6)
        {"CA3BCCCK_CA3PC", "CA3_BCCCK", "CA3_PC"},
        {"CA3BCCCK_CA3AAC", "CA3_BCCCK", "CA3_AAC"},
        {"CA3BCCCK_CA3BC", "CA3_BCCCK", "CA3_BC"},
        {"CA3BCCCK_CA3BCCCK", "CA3_BCCCK", "CA3_BCCCK"},
        {"CA3BCCCK_CA3BisC", "CA3_BCCCK", "CA3_BisC"},
        {"CA3BCCCK_CA3MFA", "CA3_BCCCK", "CA3_MFA"},
        // CA3_BisC (8)
        {"CA3BisC_CA3PC", "CA3_BisC", "CA3_PC"},
        {"CA3BisC_CA3AAC", "CA3_BisC", "CA3_AAC"},
        {"CA3BisC_CA3BC", "CA3_BisC", "CA3_BC"},
        {"CA3BisC_CA3BCCCK", "CA3_BisC", "CA3_BCCCK"},
        {"CA3BisC_CA3BisC", "CA3_BisC", "CA3_BisC"},
        {"CA3BisC_CA3MFA", "CA3_BisC", "CA3_MFA"},
        {"CA3BisC_CA3OLM", "CA3_BisC", "CA3_OLM"},
        {"CA3BisC_CA3TL", "CA3_BisC", "CA3_TL"},
        // CA3_MFA (5)
        {"CA3MFA_CA3PC", "CA3_MFA", "CA3_PC"},
        {"CA3MFA_CA3BC", "CA3_MFA", "CA3_BC"},
        {"CA3MFA_CA3BCCCK", "CA3_MFA", "CA3_BCCCK"},
        {"CA3MFA_CA3BisC", "CA3_MFA", "CA3_BisC"},
        {"CA3MFA_CA3MFA", "CA3_MFA", "CA3_MFA"},
        // CA3_OLM (8)
        {"CA3OLM_CA3PC", "CA3_OLM", "CA3_PC"},
        {"CA3OLM_CA3AAC", "CA3_OLM", "CA3_AAC"},
        {"CA3OLM_CA3BC", "CA3_OLM", "CA3_BC"},
        {"CA3OLM_CA3BCCCK", "CA3_OLM", "CA3_BCCCK"},
        {"CA3OLM_CA3BisC", "CA3_OLM", "CA3_BisC"},
        {"CA3OLM_CA3MFA", "CA3_OLM", "CA3_MFA"},
        {"CA3OLM_CA3OLM", "CA3_OLM", "CA3_OLM"},
        {"CA3OLM_CA3TL", "CA3_OLM", "CA3_TL"},
        // CA3_TL (8)
        {"CA3TL_CA3PC", "CA3_TL", "CA3_PC"},
        {"CA3TL_CA3AAC", "CA3_TL", "CA3_AAC"},
        {"CA3TL_CA3BC", "CA3_TL", "CA3_BC"},
        {"CA3TL_CA3BCCCK", "CA3_TL", "CA3_BCCCK"},
        {"CA3TL_CA3BisC", "CA3_TL", "CA3_BisC"},
        {"CA3TL_CA3MFA", "CA3_TL", "CA3_MFA"},
        {"CA3TL_CA3OLM", "CA3_TL", "CA3_OLM"},
        {"CA3TL_CA3TL", "CA3_TL", "CA3_TL"},
    };
}

std::map<std::string, float> makeCA3BaselineWeights() {
    std::map<std::string, float> baselineWts = {
        // EC_LEC (3), borrow: divided by 8
        {"LEC_CA3PC",  0.23f},   // 0.1; 0.23 PSP
        {"LEC_CA3AAC", 0.264f},  // 0.1; 2.11 borrow PSP
        {"LEC_CA3BC",  0.1275f}, // 0.05; 1.02 borrow PSP
        // EC_MEC (3), borrow: divided by 8
        {"MEC_CA3PC",  0.23f},   // 0.1; 0.23 PSP
        {"MEC_CA3AAC", 0.264f},  // 0.1; 2.11 borrow PSP
        {"MEC_CA3BC",  0.1275f}, // 0.05; 1.02 borrow PSP
        // DG_GC (6), borrow: divided by 5
        {"DGGC_CA3PC",    1.05f},   // 0.2; 1.05 borrow PSP
        {"DGGC_CA3AAC",   0.82f},   // 0.2; 4.1 borrow PSP
        {"DGGC_CA3BC",    0.281f},  // 0.07; 1.405 borrow PSP
        {"DGGC_CA3BCCCK", 0.263f},  // 0.13; 1.315 borrow PSP
        {"DGGC_CA3BisC",  0.206f},  // 0.1; 1.03 borrow PSP
        {"DGGC_CA3MFA",   0.3754f}, // 0.18; 1.877 borrow PSP
        // CA3_PC (8), borrow: divided by 8
        {"CA3PC_CA3PC",    0.00246f}, // 0.0005 correct; 0.246 PSP
        {"CA3PC_CA3AAC",   0.35f},    // 0.14; 2.8 borrow PSP
        {"CA3PC_CA3BC",    0.1475f},  // 0.051; 1.18 borrow PSP
        {"CA3PC_CA3BCCCK", 0.455f},   // 0.36; 3.64 borrow PSP
        {"CA3PC_CA3BisC",  0.1813f},  // 0.14; 1.45 borrow PSP
        {"CA3PC_CA3MFA",   0.6613f},  // 0.53; 5.29 borrow PSP
        {"CA3PC_CA3OLM",   0.112f},   // 0.01; 0.112 (CA3PC-SO)
        {"CA3PC_CA3TL",    0.0168f},  // 0.01; 0.134 borrow PSP, divided by 5
        // CA3_AAC (1); borrow: divided by 5
        {"CA3AAC_CA3PC", 0.848f}, // 0.63; 4.24 borrow PSP, divided by 5 = 0.848
        // CA3_BC (5); borrow: divided by 5
        {"CA3BC_CA3PC",    0.848f},
        {"CA3BC_CA3BC",    0.1894f},
        {"CA3BC_CA3BCCCK", 0.0938f},
        {"CA3BC_CA3BisC",  0.668f},
        {"CA3BC_CA3MFA",   0.1164f},
        // CA3_BCCCK (6); borrow: divided by 5
        {"CA3BCCCK_CA3PC",    0.848f},
        {"CA3BCCCK_CA3AAC",   0.3134f},
        {"CA3BCCCK_CA3BC",    0.1894f},
        {"CA3BCCCK_CA3BCCCK", 0.0938f},
        {"CA3BCCCK_CA3BisC",  0.668f},
        {"CA3BCCCK_CA3MFA",   0.1164f},
        // CA3_BisC (8); borrow: divided by 8
        {"CA3BisC_CA3PC",    0.53f},
        {"CA3BisC_CA3AAC",   0.1959f},
        {"CA3BisC_CA3BC",    0.1184f},
        {"CA3BisC_CA3BCCCK", 0.0586f},
        {"CA3BisC_CA3BisC",  0.4175f},
        {"CA3BisC_CA3MFA",   0.073f},
        {"CA3BisC_CA3OLM",   0.051f},
        {"CA3BisC_CA3TL",    0.675f},
        // CA3_MFA (5); borrow: divided by 5
        {"CA3MFA_CA3PC",    0.848f},
        {"CA3MFA_CA3BC",    0.1894f},
        {"CA3MFA_CA3BCCCK", 0.0938f},
        {"CA3MFA_CA3BisC",  0.668f},
        {"CA3MFA_CA3MFA",   0.1164f},
        // CA3_OLM (8); borrow: divided by 5
        {"CA3OLM_CA3PC",    0.848f},
        {"CA3OLM_CA3AAC",   0.3134f},
        {"CA3OLM_CA3BC",    0.1894f},
        {"CA3OLM_CA3BCCCK", 0.0938f},
        {"CA3OLM_CA3BisC",  0.668f},
        {"CA3OLM_CA3MFA",   0.1164f},
        {"CA3OLM_CA3OLM",   0.081f},
        {"CA3OLM_CA3TL",    1.08f},
        // CA3_TL (8); borrow: divided by 8
        {"CA3TL_CA3PC",    0.53f},
        {"CA3TL_CA3AAC",   0.1959f},
        {"CA3TL_CA3BC",    0.1184f},
        {"CA3TL_CA3BCCCK", 0.0586f},
        {"CA3TL_CA3BisC",  0.4175f},
        {"CA3TL_CA3MFA",   0.073f},
        {"CA3TL_CA3OLM",   0.051f},
        {"CA3TL_CA3TL",    0.675f},
    };
    return baselineWts;
}

}  // namespace hippomodel::CA3
