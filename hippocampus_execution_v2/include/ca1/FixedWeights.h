// Set the original fixed baseline weights and optimized scaling factors.
// This header contains statements included inside main, sharing its local variables.
// ======================================
// Add values to weight map from optimization
// ======================================

// 1. Optimization Output
std::vector<float> scalingFactors = { 4.98003, 4.7772, 5.11118, 5.40146, 0.166467, 0.177746, 0.134867, 0.286608, 0.175445, 0.138673, 0.155884, 1.67128, 2.28088, 2.15176, 1.25944, 0.443194, 1.13972, 0.478154, 0.883739, 0.397616, 0.512402, 2.2173, 1.954, 1.8652, 2.95247, 0.325202, 0.408532, 0.886055, 0.337514, 0.36027, 0.88401, 2.32797, 2.74702, 1.93566, 5.26767, 0.414795, 0.301385, 0.380864, 0.397994, 0.280878, 0.213323, 0.931896, 0.734984, 1.07555, 1.8909, 1.73879, 1.70011, 2.91169, 2.854, 0.1686, 0.197524, 1.76043, 0.433721, 1.18663, 0.872768, 1.03511, 0.723665, 0.523701, 1.12149 };//



// 2. Baseline Weights - CA1PC(type1)
float baselineWts[] = {
    // EC_LEC3 (PRE) -> {CA1_PC, CA1_AAC, CA1_BC, CA1_BCCCK, CA1_NG}
    0.25f, 0.26f, 0.185f, 0.3f, 0.55f, //0.238f, 0.8f, 0.37f, 0.9f, 0.55f
    
    // EC_MEC3 (PRE) -> {CA1_PC, CA1_AAC, CA1_BC, CA1_BCCCK, CA1_NG}
    0.31f, 0.26f, 0.185f, 0.3f, 0.55f, //0.238f, 0.8f, 0.37f, 0.9f, 0.55f

    // CA3_PC (PRE) -> {CA1_PC, CA1_AAC, CA1_BC, CA1_BCCCK, CA1_BisC, CA1_OLM, CA1_TL} - correct CA3PC-CA1PC=0.001
    0.045f, 0.54f, 0.284f, 0.9f, 1.1f, 0.32f, 0.093f, //0.28f, 1.36f, 0.355f, 1.13f, 1.1f, 0.635f, 0.149f

    // CA1_PC (PRE) -> {CA1_PC, CA1_AAC, CA1_BC, CA1_BCCCK, CA1_BisC, CA1_OLM, CA1_TL}
    0.2f, 0.968f, 0.355f, 1.58f, 0.883f, 0.159f, 0.07f, //0.39f, 7.75f, 0.568f, 3.175f, 8.83f, 1.27f, 0.571f,

    // CA1_AAC (PRE) -> {CA1_PC}
    2.365f,

    // CA1_BC (PRE) -> {CA1_PC, CA1_AAC, CA1_BC, CA1_BCCCK, CA1_BisC}
    2.745f, 1.8f, 0.947f, 0.313f, 0.313f,

    // CA1_BCCCK (PRE) -> {CA1_PC, CA1_AAC, CA1_BC, CA1_BCCCK, CA1_BisC}
    2.745f, 1.8f, 0.158f, 0.375f, 0.375f,

    // CA1_BisC (PRE) -> {CA1_PC, CA1_AAC, CA1_BC, CA1_BCCCK, CA1_BisC, CA1_OLM, CA1_TL}
    0.244f, 0.18f, 0.129f, 0.188f, 0.182f, 0.1f, 0.0138f,

    // CA1_NG (PRE) -> {CA1_PC, CA1_AAC, CA1_BC, CA1_BCCCK, CA1_NG}
    1.39f, 1.8f, 0.947f, 0.47f, 3.7f,

    // CA1_OLM (PRE) -> {CA1_PC, CA1_AAC, CA1_BC, CA1_BCCCK, CA1_NG}
    1.39f, 1.8f, 0.947f, 0.47f, 3.7f,

    // CA1_TL (PRE) -> {CA1_PC, CA1_AAC, CA1_BC, CA1_BCCCK, CA1_BisC, CA1_OLM, CA1_TL}
    0.244f, 0.18f, 0.129f, 0.188f, 0.182f, 0.1f, 0.0138f
};


// 3. Connection Order (Convergence order)
const std::vector<std::string> CA1ConnectionNames = {
    // CA1PC targets (11)
    "LEC3_CA1PC", "MEC3_CA1PC", "CA3PC_CA1PC", "CA1PC_CA1PC", "CA1BC_CA1PC", "CA1AAC_CA1PC", "CA1BCCCK_CA1PC", "CA1BisC_CA1PC", "CA1NG_CA1PC", "CA1OLM_CA1PC", "CA1TL_CA1PC", 
    // CA1AAC targets (10)
    "LEC3_CA1AAC", "MEC3_CA1AAC", "CA3PC_CA1AAC", "CA1PC_CA1AAC", "CA1BC_CA1AAC", "CA1BCCCK_CA1AAC", "CA1BisC_CA1AAC", "CA1NG_CA1AAC", "CA1OLM_CA1AAC", "CA1TL_CA1AAC",
    // CA1BC targets (10)
    "LEC3_CA1BC", "MEC3_CA1BC", "CA3PC_CA1BC", "CA1PC_CA1BC", "CA1BC_CA1BC", "CA1BCCCK_CA1BC", "CA1BisC_CA1BC", "CA1NG_CA1BC", "CA1OLM_CA1BC", "CA1TL_CA1BC",
    // CA1BCCCK targets (10)
    "LEC3_CA1BCCCK", "MEC3_CA1BCCCK", "CA3PC_CA1BCCCK", "CA1PC_CA1BCCCK", "CA1BC_CA1BCCCK", "CA1BCCCK_CA1BCCCK", "CA1BisC_CA1BCCCK", "CA1NG_CA1BCCCK", "CA1OLM_CA1BCCCK", "CA1TL_CA1BCCCK",
    // CA1BisC targets (6)
    "CA3PC_CA1BisC", "CA1PC_CA1BisC", "CA1BC_CA1BisC", "CA1BCCCK_CA1BisC", "CA1BisC_CA1BisC", "CA1TL_CA1BisC",
    // CA1NG targets (4)
    "LEC3_CA1NG", "MEC3_CA1NG", "CA1NG_CA1NG", "CA1OLM_CA1NG",
    // CA1OLM targets (4)
    "CA3PC_CA1OLM", "CA1PC_CA1OLM", "CA1BisC_CA1OLM", "CA1TL_CA1OLM",
    // CA1TL targets (4)
    "CA3PC_CA1TL", "CA1PC_CA1TL", "CA1BisC_CA1TL", "CA1TL_CA1TL"
};

// 4. Helper to find scale by name
auto getScale = [&](std::string name) {
    auto it = std::find(CA1ConnectionNames.begin(), CA1ConnectionNames.end(), name);
    if (it != CA1ConnectionNames.end()) {
        return scalingFactors[std::distance(CA1ConnectionNames.begin(), it)];
    }
    return 1.0f; 
};

// 5. Insert weight
// --------------------------- EC_LEC3 ---------------------------
std::map<std::string, float> weights_EC_LEC3;
weights_EC_LEC3.insert({"CA1_PC",    baselineWts[0] * getScale("LEC3_CA1PC")});
weights_EC_LEC3.insert({"CA1_AAC",   baselineWts[1] * getScale("LEC3_CA1AAC")});
weights_EC_LEC3.insert({"CA1_BC",    baselineWts[2] * getScale("LEC3_CA1BC")});
weights_EC_LEC3.insert({"CA1_BCCCK", baselineWts[3] * getScale("LEC3_CA1BCCCK")});
weights_EC_LEC3.insert({"CA1_NG",    baselineWts[4] * getScale("LEC3_CA1NG")});
map_weight.insert({"EC_LEC3", weights_EC_LEC3});

// --------------------------- EC_MEC3 ---------------------------
std::map<std::string, float> weights_EC_MEC3;
weights_EC_MEC3.insert({"CA1_PC",    baselineWts[5] * getScale("MEC3_CA1PC")});
weights_EC_MEC3.insert({"CA1_AAC",   baselineWts[6] * getScale("MEC3_CA1AAC")});
weights_EC_MEC3.insert({"CA1_BC",    baselineWts[7] * getScale("MEC3_CA1BC")});
weights_EC_MEC3.insert({"CA1_BCCCK", baselineWts[8] * getScale("MEC3_CA1BCCCK")});
weights_EC_MEC3.insert({"CA1_NG",    baselineWts[9] * getScale("MEC3_CA1NG")});
map_weight.insert({"EC_MEC3", weights_EC_MEC3});

// --------------------------- CA3_PC ---------------------------
std::map<std::string, float> weights_CA3_PC;
weights_CA3_PC.insert({"CA1_PC",    baselineWts[10] * getScale("CA3PC_CA1PC")});
weights_CA3_PC.insert({"CA1_AAC",   baselineWts[11] * getScale("CA3PC_CA1AAC")});
weights_CA3_PC.insert({"CA1_BC",    baselineWts[12] * getScale("CA3PC_CA1BC")});
weights_CA3_PC.insert({"CA1_BCCCK", baselineWts[13] * getScale("CA3PC_CA1BCCCK")});
weights_CA3_PC.insert({"CA1_BisC",  baselineWts[14] * getScale("CA3PC_CA1BisC")});
weights_CA3_PC.insert({"CA1_OLM",   baselineWts[15] * getScale("CA3PC_CA1OLM")});
weights_CA3_PC.insert({"CA1_TL",    baselineWts[16] * getScale("CA3PC_CA1TL")});
map_weight.insert({"CA3_PC", weights_CA3_PC});

// --------------------------- CA1_PC ---------------------------
std::map<std::string, float> weights_CA1_PC;
weights_CA1_PC.insert({"CA1_PC",    baselineWts[17] * getScale("CA1PC_CA1PC")});
weights_CA1_PC.insert({"CA1_AAC",   baselineWts[18] * getScale("CA1PC_CA1AAC")});
weights_CA1_PC.insert({"CA1_BC",    baselineWts[19] * getScale("CA1PC_CA1BC")});
weights_CA1_PC.insert({"CA1_BCCCK", baselineWts[20] * getScale("CA1PC_CA1BCCCK")});
weights_CA1_PC.insert({"CA1_BisC",  baselineWts[21] * getScale("CA1PC_CA1BisC")});
weights_CA1_PC.insert({"CA1_OLM",   baselineWts[22] * getScale("CA1PC_CA1OLM")});
weights_CA1_PC.insert({"CA1_TL",    baselineWts[23] * getScale("CA1PC_CA1TL")});
map_weight.insert({"CA1_PC", weights_CA1_PC});

// --------------------------- CA1_AAC ---------------------------
std::map<std::string, float> weights_CA1_AAC;
weights_CA1_AAC.insert({"CA1_PC", baselineWts[24] * getScale("CA1AAC_CA1PC")});
map_weight.insert({"CA1_AAC", weights_CA1_AAC});

// --------------------------- CA1_BC ---------------------------
std::map<std::string, float> weights_CA1_BC;
weights_CA1_BC.insert({"CA1_PC",    baselineWts[25] * getScale("CA1BC_CA1PC")});
weights_CA1_BC.insert({"CA1_AAC",   baselineWts[26] * getScale("CA1BC_CA1AAC")});
weights_CA1_BC.insert({"CA1_BC",    baselineWts[27] * getScale("CA1BC_CA1BC")});
weights_CA1_BC.insert({"CA1_BCCCK", baselineWts[28] * getScale("CA1BC_CA1BCCCK")});
weights_CA1_BC.insert({"CA1_BisC",  baselineWts[29] * getScale("CA1BC_CA1BisC")});
map_weight.insert({"CA1_BC", weights_CA1_BC});

// --------------------------- CA1_BCCCK ---------------------------
std::map<std::string, float> weights_CA1_BCCCK;
weights_CA1_BCCCK.insert({"CA1_PC",    baselineWts[30] * getScale("CA1BCCCK_CA1PC")});
weights_CA1_BCCCK.insert({"CA1_AAC",   baselineWts[31] * getScale("CA1BCCCK_CA1AAC")});
weights_CA1_BCCCK.insert({"CA1_BC",    baselineWts[32] * getScale("CA1BCCCK_CA1BC")});
weights_CA1_BCCCK.insert({"CA1_BCCCK", baselineWts[33] * getScale("CA1BCCCK_CA1BCCCK")});
weights_CA1_BCCCK.insert({"CA1_BisC",  baselineWts[34] * getScale("CA1BCCCK_CA1BisC")});
map_weight.insert({"CA1_BCCCK", weights_CA1_BCCCK});

// --------------------------- CA1_BisC ---------------------------
std::map<std::string, float> weights_CA1_BisC;
weights_CA1_BisC.insert({"CA1_PC",    baselineWts[35] * getScale("CA1BisC_CA1PC")});
weights_CA1_BisC.insert({"CA1_AAC",   baselineWts[36] * getScale("CA1BisC_CA1AAC")});
weights_CA1_BisC.insert({"CA1_BC",    baselineWts[37] * getScale("CA1BisC_CA1BC")});
weights_CA1_BisC.insert({"CA1_BCCCK", baselineWts[38] * getScale("CA1BisC_CA1BCCCK")});
weights_CA1_BisC.insert({"CA1_BisC",  baselineWts[39] * getScale("CA1BisC_CA1BisC")});
weights_CA1_BisC.insert({"CA1_OLM",   baselineWts[40] * getScale("CA1BisC_CA1OLM")});
weights_CA1_BisC.insert({"CA1_TL",    baselineWts[41] * getScale("CA1BisC_CA1TL")});
map_weight.insert({"CA1_BisC", weights_CA1_BisC});

// --------------------------- CA1_NG ---------------------------
std::map<std::string, float> weights_CA1_NG;
weights_CA1_NG.insert({"CA1_PC",    baselineWts[42] * getScale("CA1NG_CA1PC")});
weights_CA1_NG.insert({"CA1_AAC",   baselineWts[43] * getScale("CA1NG_CA1AAC")});
weights_CA1_NG.insert({"CA1_BC",    baselineWts[44] * getScale("CA1NG_CA1BC")});
weights_CA1_NG.insert({"CA1_BCCCK", baselineWts[45] * getScale("CA1NG_CA1BCCCK")});
weights_CA1_NG.insert({"CA1_NG",    baselineWts[46] * getScale("CA1NG_CA1NG")});
map_weight.insert({"CA1_NG", weights_CA1_NG});

// --------------------------- CA1_OLM ---------------------------
std::map<std::string, float> weights_CA1_OLM;
weights_CA1_OLM.insert({"CA1_PC",    baselineWts[47] * getScale("CA1OLM_CA1PC")});
weights_CA1_OLM.insert({"CA1_AAC",   baselineWts[48] * getScale("CA1OLM_CA1AAC")});
weights_CA1_OLM.insert({"CA1_BC",    baselineWts[49] * getScale("CA1OLM_CA1BC")});
weights_CA1_OLM.insert({"CA1_BCCCK", baselineWts[50] * getScale("CA1OLM_CA1BCCCK")});
weights_CA1_OLM.insert({"CA1_NG",    baselineWts[51] * getScale("CA1OLM_CA1NG")});
map_weight.insert({"CA1_OLM", weights_CA1_OLM});

// --------------------------- CA1_TL ---------------------------
std::map<std::string, float> weights_CA1_TL;
weights_CA1_TL.insert({"CA1_PC",    baselineWts[52] * getScale("CA1TL_CA1PC")});
weights_CA1_TL.insert({"CA1_AAC",   baselineWts[53] * getScale("CA1TL_CA1AAC")});
weights_CA1_TL.insert({"CA1_BC",    baselineWts[54] * getScale("CA1TL_CA1BC")});
weights_CA1_TL.insert({"CA1_BCCCK", baselineWts[55] * getScale("CA1TL_CA1BCCCK")});
weights_CA1_TL.insert({"CA1_BisC",  baselineWts[56] * getScale("CA1TL_CA1BisC")});
weights_CA1_TL.insert({"CA1_OLM",   baselineWts[57] * getScale("CA1TL_CA1OLM")});
weights_CA1_TL.insert({"CA1_TL",    baselineWts[58] * getScale("CA1TL_CA1TL")});
map_weight.insert({"CA1_TL", weights_CA1_TL});


