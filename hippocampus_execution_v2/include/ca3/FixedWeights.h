// Set the original fixed baseline weights and optimized scaling factors.
// This header contains statements included inside main, sharing its local variables.
// ======================================
// Add values to weight map from optimization
// ======================================

// 1. Optimization Output

std::vector<float> scalingFactors = { 4.59497, 4.59497, 4.59497, 4.59497, 0.217629, 0.217629, 0.217629, 0.217629, 0.217629, 0.217629, 0.217629, 0.239392, 0.239392, 0.239392, 0.239392, 4.17725, 4.17725, 4.17725, 4.17725, 0.564474, 0.564474, 0.564474, 0.564474, 1.77156, 1.77156, 1.77156, 1.77156, 1.77156, 1.77156, 0.424098, 0.424098, 2.35795, 2.35795, 2.35795, 2.35795, 2.35795, 2.35795, 0.826446, 0.826446, 1.21, 1.21, 1.21, 1.21, 1.21, 1.21, 0.350494, 0.350494, 2.85312, 2.85312, 2.85312, 2.85312, 2.85312, 2.85312, 0.424098, 2.35795, 2.35795, 2.35795, 1.21, 0.826446, 0.826446, 0.826446 };//1/10 model type2 - 246.991% - good

//std::vector<float> scalingFactors = { 4.59497, 4.59497, 4.59497, 4.59497, 0.217629, 0.217629, 0.217629, 0.217629, 0.217629, 0.217629, 0.217629, 0.217629, 0.217629, 0.217629, 0.217629, 4.59497, 4.59497, 4.59497, 4.59497, 0.513158, 0.513158, 0.513158, 0.513158, 1.94872, 1.94872, 1.94872, 1.94872, 1.94872, 1.94872, 0.385543, 0.385543, 2.59374, 2.59374, 2.59374, 2.59374, 2.59374, 2.59374, 0.826446, 0.826446, 1.21, 1.21, 1.21, 1.21, 1.21, 1.21, 0.318631, 0.318631, 3.13843, 3.13843, 3.13843, 3.13843, 3.13843, 3.13843, 0.424098, 2.35795, 2.35795, 2.35795, 1.331, 0.751315, 0.751315, 0.751315 };//1/10 model type2 - 195% - increase GC-INs, not working




// 2. Baseline Weights - CA3PC(type3)
float baselineWts[] = {
    // EC_LEC (3)
    0.165f, 0.264f, 0.1275f,
    // EC_MEC (3)
    0.165f, 0.264f, 0.1275f,
    // DG_GC (6)
    0.415f, 0.82f, 0.281f, 0.263f, 0.206f, 0.3754f, //(good)0.415f, 0.82f, 0.281f, 0.263f, 0.206f, 0.3754f ; (increase GC-INs)0.277f, 1.33f, 0.468f, 0.438f, 0.343f, 0.626f
    // CA3_PC (8)
    0.00181f, 0.35f, 0.1475f, 0.455f, 0.1813f, 0.6613f, 0.112f, 0.0168f,
    // CA3_AAC (1)
    0.879f,
    // CA3_BC (5)
    0.879f, 0.1894f, 0.0938f, 0.668f, 0.1164f,
    // CA3_BCCCK (6)
    0.879f, 0.3134f, 0.1894f, 0.0938f, 0.668f, 0.1164f,
    // CA3_BisC (8)
    0.549f, 0.1959f, 0.1184f, 0.0586f, 0.4175f, 0.073f, 0.051f, 0.675f,
    // CA3_MFA (5)
    0.879f, 0.1894f, 0.0938f, 0.668f, 0.1164f,
    // CA3_OLM (8)
    0.879f, 0.3134f, 0.1894f, 0.0938f, 0.668f, 0.1164f, 0.081f, 1.08f,
    // CA3_TL (8)
    0.549f, 0.1959f, 0.1184f, 0.0586f, 0.4175f, 0.073f, 0.051f, 0.675f
};

// 3. Connection Order (Convergence order)
const std::vector<std::string> CA3ConnectionNames = {
    // CA3_PC targets (11)
    "LEC_CA3PC", "MEC_CA3PC", "DGGC_CA3PC", "CA3PC_CA3PC", 
    "CA3AAC_CA3PC", "CA3BC_CA3PC","CA3BCCCK_CA3PC", "CA3BisC_CA3PC", "CA3MFA_CA3PC", "CA3OLM_CA3PC", "CA3TL_CA3PC", 
    // CA3_AAC targets (8)
    "LEC_CA3AAC", "MEC_CA3AAC", "DGGC_CA3AAC", "CA3PC_CA3AAC", 
    "CA3BCCCK_CA3AAC", "CA3BisC_CA3AAC", "CA3OLM_CA3AAC", "CA3TL_CA3AAC",
    // CA3_BC targets (10)
    "LEC_CA3BC", "MEC_CA3BC", "DGGC_CA3BC", "CA3PC_CA3BC", 
    "CA3BC_CA3BC", "CA3BCCCK_CA3BC", "CA3BisC_CA3BC", "CA3MFA_CA3BC", "CA3OLM_CA3BC", "CA3TL_CA3BC", 
    // CA3_BCCCK targets (8)
    "DGGC_CA3BCCCK", "CA3PC_CA3BCCCK", 
    "CA3BC_CA3BCCCK", "CA3BCCCK_CA3BCCCK", "CA3BisC_CA3BCCCK", "CA3MFA_CA3BCCCK", "CA3OLM_CA3BCCCK", "CA3TL_CA3BCCCK",
    // CA3_BisC targets (8)
    "DGGC_CA3BisC", "CA3PC_CA3BisC", 
    "CA3BC_CA3BisC", "CA3BCCCK_CA3BisC", "CA3BisC_CA3BisC", "CA3MFA_CA3BisC", "CA3OLM_CA3BisC", "CA3TL_CA3BisC", 
    // CA3_MFA targets (8)
    "DGGC_CA3MFA", "CA3PC_CA3MFA", 
    "CA3BC_CA3MFA", "CA3BCCCK_CA3MFA", "CA3BisC_CA3MFA", "CA3MFA_CA3MFA", "CA3OLM_CA3MFA", "CA3TL_CA3MFA", 
    // CA3_OLM targets (4)
    "CA3PC_CA3OLM", 
    "CA3BisC_CA3OLM", "CA3OLM_CA3OLM", "CA3TL_CA3OLM",
    // CA3_TL targets (4)
    "CA3PC_CA3TL", 
    "CA3BisC_CA3TL", "CA3OLM_CA3TL", "CA3TL_CA3TL"
    
};

// 4. Helper to find scale by name
auto getScale = [&](std::string name) {
    auto it = std::find(CA3ConnectionNames.begin(), CA3ConnectionNames.end(), name);
    if (it != CA3ConnectionNames.end()) {
        return scalingFactors[std::distance(CA3ConnectionNames.begin(), it)];
    }
    return 1.0f; 
};

// 5. Insert weight
// --------------------------- EC_LEC ---------------------------
std::map<std::string, float> weights_EC_LEC;
weights_EC_LEC.insert({"CA3_PC",  baselineWts[0] * getScale("LEC_CA3PC")});  // 0.393 * 0.562535 = 0.221076
weights_EC_LEC.insert({"CA3_AAC", baselineWts[1] * getScale("LEC_CA3AAC")}); // 2.110 * 0.0549658 = 0.115977
weights_EC_LEC.insert({"CA3_BC",  baselineWts[2] * getScale("LEC_CA3BC")});  // 1.020 * 0.030393 = 0.031000
map_weight.insert({"EC_LEC", weights_EC_LEC});

// --------------------------- EC_MEC ---------------------------
std::map<std::string, float> weights_EC_MEC;
weights_EC_MEC.insert({"CA3_PC",  baselineWts[3] * getScale("MEC_CA3PC")});  // 0.393 * 0.883057 = 0.347041
weights_EC_MEC.insert({"CA3_AAC", baselineWts[4] * getScale("MEC_CA3AAC")}); // 2.110 * 0.0000422 = 0.000089
weights_EC_MEC.insert({"CA3_BC",  baselineWts[5] * getScale("MEC_CA3BC")});  // 1.020 * 0.0613681 = 0.062595
map_weight.insert({"EC_MEC", weights_EC_MEC});

// --------------------------- DG_GC ----------------------------
std::map<std::string, float> weights_DG_GC;
weights_DG_GC.insert({"CA3_PC",    baselineWts[6]  * getScale("DGGC_CA3PC")});    // 2.21 * 0.77061 = 1.703048
weights_DG_GC.insert({"CA3_AAC",   baselineWts[7]  * getScale("DGGC_CA3AAC")});   // 4.1 * 0.067358 = 0.276167
weights_DG_GC.insert({"CA3_BC",    baselineWts[8]  * getScale("DGGC_CA3BC")});    // 1.405 * 0.0459346 = 0.064538
weights_DG_GC.insert({"CA3_BCCCK", baselineWts[9]  * getScale("DGGC_CA3BCCCK")}); // 1.315 * 0.0197274 = 0.025941
weights_DG_GC.insert({"CA3_BisC",  baselineWts[10] * getScale("DGGC_CA3BisC")});  // 1.02 * 0.134331 = 0.137017
weights_DG_GC.insert({"CA3_MFA",   baselineWts[11] * getScale("DGGC_CA3MFA")});   // 1.877 * 0.877547 = 1.647155
map_weight.insert({"DG_GC", weights_DG_GC});

// --------------------------- CA3_PC ---------------------------
std::map<std::string, float> weights_CA3_PC;
weights_CA3_PC.insert({"CA3_PC",    baselineWts[12] * getScale("CA3PC_CA3PC")});    // 0.00025 * 0.546818 = 0.000136
weights_CA3_PC.insert({"CA3_AAC",   baselineWts[13] * getScale("CA3PC_CA3AAC")});   // 2.8 * 0.0662842 = 0.185595
weights_CA3_PC.insert({"CA3_BC",    baselineWts[14] * getScale("CA3PC_CA3BC")});    // 1.18 * 0.0434706 = 0.051295
weights_CA3_PC.insert({"CA3_BCCCK", baselineWts[15] * getScale("CA3PC_CA3BCCCK")}); // 3.64 * 0.022615 = 0.082318
weights_CA3_PC.insert({"CA3_BisC",  baselineWts[16] * getScale("CA3PC_CA3BisC")});  // 1.48 * 0.117801 = 0.174345
weights_CA3_PC.insert({"CA3_MFA",   baselineWts[17] * getScale("CA3PC_CA3MFA")});   // 5.29 * 1.76186 = 9.320239
weights_CA3_PC.insert({"CA3_OLM",   baselineWts[18] * getScale("CA3PC_CA3OLM")});   // 0.122 * 0.670741 = 0.081830
weights_CA3_PC.insert({"CA3_TL",    baselineWts[19] * getScale("CA3PC_CA3TL")});    // 0.134 * 0.299254 = 0.040100
map_weight.insert({"CA3_PC", weights_CA3_PC});

// --------------------------- CA3_AAC --------------------------
std::map<std::string, float> weights_CA3_AAC;
weights_CA3_AAC.insert({"CA3_PC", baselineWts[20] * getScale("CA3AAC_CA3PC")}); // 2.557 * 0.894335 = 2.286814
map_weight.insert({"CA3_AAC", weights_CA3_AAC});

// --------------------------- CA3_BC ---------------------------
std::map<std::string, float> weights_CA3_BC;
weights_CA3_BC.insert({"CA3_PC",    baselineWts[21] * getScale("CA3BC_CA3PC")});    // 2.557 * 1.25144 = 3.199932
weights_CA3_BC.insert({"CA3_BC",    baselineWts[22] * getScale("CA3BC_CA3BC")});    // 0.947 * 1.43569 = 1.359598
weights_CA3_BC.insert({"CA3_BCCCK", baselineWts[23] * getScale("CA3BC_CA3BCCCK")}); // 0.469 * 1.1 = 0.5159
weights_CA3_BC.insert({"CA3_BisC",  baselineWts[24] * getScale("CA3BC_CA3BisC")});  // 3.48 * 0.753616 = 2.622583
weights_CA3_BC.insert({"CA3_MFA",   baselineWts[25] * getScale("CA3BC_CA3MFA")});   // 0.582 * 0.134331 = 0.078180
map_weight.insert({"CA3_BC", weights_CA3_BC});

// --------------------------- CA3_BCCCK ------------------------
std::map<std::string, float> weights_CA3_BCCCK;
weights_CA3_BCCCK.insert({"CA3_PC",    baselineWts[26] * getScale("CA3BCCCK_CA3PC")});    // 2.557 * 1.34284 = 3.433641
weights_CA3_BCCCK.insert({"CA3_AAC",   baselineWts[27] * getScale("CA3BCCCK_CA3AAC")});   // 1.567 * 1.25133 = 1.960834
weights_CA3_BCCCK.insert({"CA3_BC",    baselineWts[28] * getScale("CA3BCCCK_CA3BC")});    // 0.947 * 1.62147 = 1.535532
weights_CA3_BCCCK.insert({"CA3_BCCCK", baselineWts[29] * getScale("CA3BCCCK_CA3BCCCK")}); // 0.469 * 1.1 = 0.5159
weights_CA3_BCCCK.insert({"CA3_BisC",  baselineWts[30] * getScale("CA3BCCCK_CA3BisC")});  // 3.48 * 0.877547 = 3.053863
weights_CA3_BCCCK.insert({"CA3_MFA",   baselineWts[31] * getScale("CA3BCCCK_CA3MFA")});   // 0.582 * 1.1 = 0.6402
map_weight.insert({"CA3_BCCCK", weights_CA3_BCCCK});

// --------------------------- CA3_BisC -------------------------
std::map<std::string, float> weights_CA3_BisC;
weights_CA3_BisC.insert({"CA3_PC",    baselineWts[32] * getScale("CA3BisC_CA3PC")});    // 2.557 * 0.896828 = 2.293189
weights_CA3_BisC.insert({"CA3_AAC",   baselineWts[33] * getScale("CA3BisC_CA3AAC")});   // 1.567 * 2.39896 = 3.759170
weights_CA3_BisC.insert({"CA3_BC",    baselineWts[34] * getScale("CA3BisC_CA3BC")});    // 0.947 * 0.885881 = 0.838929
weights_CA3_BisC.insert({"CA3_BCCCK", baselineWts[35] * getScale("CA3BisC_CA3BCCCK")}); // 0.469 * 2.0 = 0.938
weights_CA3_BisC.insert({"CA3_BisC",  baselineWts[36] * getScale("CA3BisC_CA3BisC")});  // 3.48 * 1.76186 = 6.131272
weights_CA3_BisC.insert({"CA3_MFA",   baselineWts[37] * getScale("CA3BisC_CA3MFA")});   // 0.582 * 0.475951 = 0.276993
weights_CA3_BisC.insert({"CA3_OLM",   baselineWts[38] * getScale("CA3BisC_CA3OLM")});   // 0.404 * 0.403057 = 0.162835
weights_CA3_BisC.insert({"CA3_TL",    baselineWts[39] * getScale("CA3BisC_CA3TL")});    // 5.4 * 1.09794 = 5.928876
map_weight.insert({"CA3_BisC", weights_CA3_BisC});

// --------------------------- CA3_MFA --------------------------
std::map<std::string, float> weights_CA3_MFA;
weights_CA3_MFA.insert({"CA3_PC",    baselineWts[40] * getScale("CA3MFA_CA3PC")});    // 2.557 * 1.33033 = 3.401653
weights_CA3_MFA.insert({"CA3_BC",    baselineWts[41] * getScale("CA3MFA_CA3BC")});    // 0.947 * 1.57527 = 1.491780
weights_CA3_MFA.insert({"CA3_BCCCK", baselineWts[42] * getScale("CA3MFA_CA3BCCCK")}); // 0.469 * 1.1 = 0.5159
weights_CA3_MFA.insert({"CA3_BisC",  baselineWts[43] * getScale("CA3MFA_CA3BisC")});  // 3.48 * 1.50085 = 5.222958
weights_CA3_MFA.insert({"CA3_MFA",   baselineWts[44] * getScale("CA3MFA_CA3MFA")});   // 0.582 * 1.74645 = 1.016434
map_weight.insert({"CA3_MFA", weights_CA3_MFA});

// --------------------------- CA3_OLM --------------------------
std::map<std::string, float> weights_CA3_OLM;
weights_CA3_OLM.insert({"CA3_PC",    baselineWts[45] * getScale("CA3OLM_CA3PC")});    // 2.557 * 1.48873 = 3.806682
weights_CA3_OLM.insert({"CA3_AAC",   baselineWts[46] * getScale("CA3OLM_CA3AAC")});   // 1.567 * 1.04194 = 1.632719
weights_CA3_OLM.insert({"CA3_BC",    baselineWts[47] * getScale("CA3OLM_CA3BC")});    // 0.947 * 1.55292 = 1.470615
weights_CA3_OLM.insert({"CA3_BCCCK", baselineWts[48] * getScale("CA3OLM_CA3BCCCK")}); // 0.469 * 1.1 = 0.5159
weights_CA3_OLM.insert({"CA3_BisC",  baselineWts[49] * getScale("CA3OLM_CA3BisC")});  // 3.48 * 1.68935 = 5.878938
weights_CA3_OLM.insert({"CA3_MFA",   baselineWts[50] * getScale("CA3OLM_CA3MFA")});   // 0.582 * 0.352524 = 0.205169
weights_CA3_OLM.insert({"CA3_OLM",   baselineWts[51] * getScale("CA3OLM_CA3OLM")});   // 0.404 * 0.479305 = 0.193639
weights_CA3_OLM.insert({"CA3_TL",    baselineWts[52] * getScale("CA3OLM_CA3TL")});    // 5.4 * 1.05992 = 5.723568
map_weight.insert({"CA3_OLM", weights_CA3_OLM});

// --------------------------- CA3_TL ---------------------------
std::map<std::string, float> weights_CA3_TL;
weights_CA3_TL.insert({"CA3_PC",    baselineWts[53] * getScale("CA3TL_CA3PC")});    // 2.557 * 1.72201 = 4.403179
weights_CA3_TL.insert({"CA3_AAC",   baselineWts[54] * getScale("CA3TL_CA3AAC")});   // 1.567 * 12.9065 = 20.22448
weights_CA3_TL.insert({"CA3_BC",    baselineWts[55] * getScale("CA3TL_CA3BC")});    // 0.947 * 1.1 = 1.0417
weights_CA3_TL.insert({"CA3_BCCCK", baselineWts[56] * getScale("CA3TL_CA3BCCCK")}); // 0.469 * 1.1 = 0.5159
weights_CA3_TL.insert({"CA3_BisC",  baselineWts[57] * getScale("CA3TL_CA3BisC")});  // 3.48 * 1.64209 = 5.714473
weights_CA3_TL.insert({"CA3_MFA",   baselineWts[58] * getScale("CA3TL_CA3MFA")});   // 0.582 * 0.620019 = 0.360851
weights_CA3_TL.insert({"CA3_OLM",   baselineWts[59] * getScale("CA3TL_CA3OLM")});   // 0.404 * 0.457089 = 0.184664
weights_CA3_TL.insert({"CA3_TL",    baselineWts[60] * getScale("CA3TL_CA3TL")});    // 5.4 * 1.02148 = 5.515992
map_weight.insert({"CA3_TL", weights_CA3_TL});
    
