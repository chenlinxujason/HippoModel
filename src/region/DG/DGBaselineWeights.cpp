#include "hippomodel/region/DG/DGBaselineWeights.h"

namespace hippomodel::DG {

std::vector<ConnectionEndpoint> makeDGConnectionEndpoints() {
    return {
        // EC_LEC (7)
        {"LEC_DGGC", "EC_LEC", "DG_GC"},
        {"LEC_DGAAC", "EC_LEC", "DG_AAC"},
        {"LEC_DGBC", "EC_LEC", "DG_BC"},
        {"LEC_DGBCCCK", "EC_LEC", "DG_BCCCK"},
        {"LEC_DGHICAP", "EC_LEC", "DG_HICAP"},
        {"LEC_DGMOPP", "EC_LEC", "DG_MOPP"},
        {"LEC_DGTML", "EC_LEC", "DG_TML"},
        // EC_MEC (7)
        {"MEC_DGGC", "EC_MEC", "DG_GC"},
        {"MEC_DGAAC", "EC_MEC", "DG_AAC"},
        {"MEC_DGBC", "EC_MEC", "DG_BC"},
        {"MEC_DGBCCCK", "EC_MEC", "DG_BCCCK"},
        {"MEC_DGHICAP", "EC_MEC", "DG_HICAP"},
        {"MEC_DGMOPP", "EC_MEC", "DG_MOPP"},
        {"MEC_DGTML", "EC_MEC", "DG_TML"},
        // DG_GC (5)
        {"DGGC_DGMC", "DG_GC", "DG_MC"},
        {"DGGC_DGAAC", "DG_GC", "DG_AAC"},
        {"DGGC_DGBC", "DG_GC", "DG_BC"},
        {"DGGC_DGHICAP", "DG_GC", "DG_HICAP"},
        {"DGGC_DGHIPP", "DG_GC", "DG_HIPP"},
        // DG_MC (6)
        {"DGMC_DGGC", "DG_MC", "DG_GC"},
        {"DGMC_DGMC", "DG_MC", "DG_MC"},
        {"DGMC_DGAAC", "DG_MC", "DG_AAC"},
        {"DGMC_DGBC", "DG_MC", "DG_BC"},
        {"DGMC_DGHICAP", "DG_MC", "DG_HICAP"},
        {"DGMC_DGHIPP", "DG_MC", "DG_HIPP"},
        // DG_AAC (3)
        {"DGAAC_DGGC", "DG_AAC", "DG_GC"},
        {"DGAAC_DGMC", "DG_AAC", "DG_MC"},
        {"DGAAC_DGBCCCK", "DG_AAC", "DG_BCCCK"},
        // DG_BC (5)
        {"DGBC_DGGC", "DG_BC", "DG_GC"},
        {"DGBC_DGAAC", "DG_BC", "DG_AAC"},
        {"DGBC_DGBC", "DG_BC", "DG_BC"},
        {"DGBC_DGBCCCK", "DG_BC", "DG_BCCCK"},
        {"DGBC_DGHICAP", "DG_BC", "DG_HICAP"},
        // DG_BCCCK (5)
        {"DGBCCCK_DGGC", "DG_BCCCK", "DG_GC"},
        {"DGBCCCK_DGAAC", "DG_BCCCK", "DG_AAC"},
        {"DGBCCCK_DGBC", "DG_BCCCK", "DG_BC"},
        {"DGBCCCK_DGBCCCK", "DG_BCCCK", "DG_BCCCK"},
        {"DGBCCCK_DGHICAP", "DG_BCCCK", "DG_HICAP"},
        // DG_HICAP (6)
        {"DGHICAP_DGGC", "DG_HICAP", "DG_GC"},
        {"DGHICAP_DGAAC", "DG_HICAP", "DG_AAC"},
        {"DGHICAP_DGBC", "DG_HICAP", "DG_BC"},
        {"DGHICAP_DGBCCCK", "DG_HICAP", "DG_BCCCK"},
        {"DGHICAP_DGHICAP", "DG_HICAP", "DG_HICAP"},
        {"DGHICAP_DGTML", "DG_HICAP", "DG_TML"},
        // DG_HIPP (7)
        {"DGHIPP_DGGC", "DG_HIPP", "DG_GC"},
        {"DGHIPP_DGAAC", "DG_HIPP", "DG_AAC"},
        {"DGHIPP_DGBC", "DG_HIPP", "DG_BC"},
        {"DGHIPP_DGBCCCK", "DG_HIPP", "DG_BCCCK"},
        {"DGHIPP_DGHICAP", "DG_HIPP", "DG_HICAP"},
        {"DGHIPP_DGMOPP", "DG_HIPP", "DG_MOPP"},
        {"DGHIPP_DGTML", "DG_HIPP", "DG_TML"},
        // DG_MOPP (7)
        {"DGMOPP_DGGC", "DG_MOPP", "DG_GC"},
        {"DGMOPP_DGAAC", "DG_MOPP", "DG_AAC"},
        {"DGMOPP_DGBC", "DG_MOPP", "DG_BC"},
        {"DGMOPP_DGBCCCK", "DG_MOPP", "DG_BCCCK"},
        {"DGMOPP_DGHICAP", "DG_MOPP", "DG_HICAP"},
        {"DGMOPP_DGMOPP", "DG_MOPP", "DG_MOPP"},
        {"DGMOPP_DGTML", "DG_MOPP", "DG_TML"},
        // DG_TML (9)
        {"DGTML_DGGC", "DG_TML", "DG_GC"},
        {"DGTML_DGMC", "DG_TML", "DG_MC"},
        {"DGTML_DGAAC", "DG_TML", "DG_AAC"},
        {"DGTML_DGBC", "DG_TML", "DG_BC"},
        {"DGTML_DGBCCCK", "DG_TML", "DG_BCCCK"},
        {"DGTML_DGHICAP", "DG_TML", "DG_HICAP"},
        {"DGTML_DGHIPP", "DG_TML", "DG_HIPP"},
        {"DGTML_DGMOPP", "DG_TML", "DG_MOPP"},
        {"DGTML_DGTML", "DG_TML", "DG_TML"},
    };
}

std::map<std::string, float> makeDGBaselineWeights() {
    std::map<std::string, float> baselineWts = {
        // EC_LEC (7)
        {"LEC_DGGC",    0.408f}, // 0.36 or 0.051 or 0.204 (0.051*8)
        {"LEC_DGAAC",   0.097f},
        {"LEC_DGBC",    0.17f},
        {"LEC_DGBCCCK", 0.1198f},
        {"LEC_DGHICAP", 0.0451f},
        {"LEC_DGMOPP",  0.4f}, // 0.1
        {"LEC_DGTML",   0.21f},
        // EC_MEC (7)
        {"MEC_DGGC",    0.408f}, // 0.36 or 0.051 or 0.204 (0.051*8)
        {"MEC_DGAAC",   0.097f},
        {"MEC_DGBC",    0.17f},
        {"MEC_DGBCCCK", 0.1198f},
        {"MEC_DGHICAP", 0.0451f},
        {"MEC_DGMOPP",  0.4f}, // 0.1
        {"MEC_DGTML",   0.21f},
        // DG_GC (5)
        {"DGGC_DGMC",    0.932f},
        {"DGGC_DGAAC",   0.377f},
        {"DGGC_DGBC",    0.67f},
        {"DGGC_DGHICAP", 0.1824f},
        {"DGGC_DGHIPP",  0.4328f},
        // DG_MC (6) // 0.0457, 1.17, 1.78, 3.8, 0.46, 2.479;
        // IN: divided by 50; MC-GC divided by 2
        {"DGMC_DGGC",    0.0228f}, // 0.0326 for scale 500 four regimes; 0.0228 for scale 10 better cover
        {"DGMC_DGMC",    0.0234f}, // 0.0234
        {"DGMC_DGAAC",   0.0356f}, // 0.0356
        {"DGMC_DGBC",    0.076f},  // 0.076
        {"DGMC_DGHICAP", 0.0092f}, // 0.0092
        {"DGMC_DGHIPP",  0.04958f}, // 0.04958
        // DG_AAC (3)
        {"DGAAC_DGGC",    0.24f},
        {"DGAAC_DGMC",    1.3f},
        {"DGAAC_DGBCCCK", 0.5f},
        // DG_BC (5)
        {"DGBC_DGGC",    0.24f},
        {"DGBC_DGAAC",   0.3f},
        {"DGBC_DGBC",    0.8f},
        {"DGBC_DGBCCCK", 0.5f},
        {"DGBC_DGHICAP", 0.3f},
        // DG_BCCCK (5)
        {"DGBCCCK_DGGC",    0.24f},
        {"DGBCCCK_DGAAC",   0.3f},
        {"DGBCCCK_DGBC",    0.8f},
        {"DGBCCCK_DGBCCCK", 0.5f},
        {"DGBCCCK_DGHICAP", 0.3f},
        // DG_HICAP (6)
        {"DGHICAP_DGGC",    0.24f},
        {"DGHICAP_DGAAC",   0.3f},
        {"DGHICAP_DGBC",    0.8f},
        {"DGHICAP_DGBCCCK", 0.5f},
        {"DGHICAP_DGHICAP", 0.3f},
        {"DGHICAP_DGTML",   0.9f},
        // DG_HIPP (7)
        {"DGHIPP_DGGC",    0.24f},
        {"DGHIPP_DGAAC",   0.245f},
        {"DGHIPP_DGBC",    0.541f},
        {"DGHIPP_DGBCCCK", 0.362f},
        {"DGHIPP_DGHICAP", 0.226f},
        {"DGHIPP_DGMOPP",  0.64f},
        {"DGHIPP_DGTML",   0.637f},
        // DG_MOPP (7)
        {"DGMOPP_DGGC",    0.24f},
        {"DGMOPP_DGAAC",   0.3f},
        {"DGMOPP_DGBC",    0.8f},
        {"DGMOPP_DGBCCCK", 0.5f},
        {"DGMOPP_DGHICAP", 0.3f},
        {"DGMOPP_DGMOPP",  0.9f},
        {"DGMOPP_DGTML",   0.9f},
        // DG_TML (9)
        {"DGTML_DGGC",    0.24f},
        {"DGTML_DGMC",    1.38f},
        {"DGTML_DGAAC",   0.245f},
        {"DGTML_DGBC",    0.541f},
        {"DGTML_DGBCCCK", 0.362f},
        {"DGTML_DGHICAP", 0.226f},
        {"DGTML_DGHIPP",  0.46f},
        {"DGTML_DGMOPP",  0.64f},
        {"DGTML_DGTML",   0.637f},
    };
    return baselineWts;
}

}  // namespace hippomodel::DG
