#include "hippomodel/region/DG/DGRegionSpec.h"

namespace hippomodel::DG {

DGRegionSpec makeDGRegionSpec() {
    DGRegionSpec spec;

    spec.h5_groups = {
        {"EC_LEC", "IDranges/EC/LEC", "EC-LEC"},
        {"EC_MEC", "IDranges/EC/MEC", "EC-MEC"},
        {"DG_GC", "IDranges/DG/GC", "DG-GC"},
        {"DG_MC", "IDranges/DG/MC", "DG-MC"},
        {"DG_AAC", "IDranges/DG/AAC", "DG-AAC"},
        {"DG_BC", "IDranges/DG/BC", "DG-BC"},
        {"DG_BCCCK", "IDranges/DG/BCCCK", "DG-BCCCK"},
        {"DG_HICAP", "IDranges/DG/HICAP", "DG-HICAP"},
        {"DG_HIPP", "IDranges/DG/HIPP", "DG-HIPP"},
        {"DG_MOPP", "IDranges/DG/MOPP", "DG-MOPP"},
        {"DG_TML", "IDranges/DG/TML", "DG-TML"},
    };

    spec.optimized_connection_order = {
        // DGGC targets (0..9)
        "LEC_DGGC", "MEC_DGGC", "DGMC_DGGC", "DGAAC_DGGC",
        "DGBC_DGGC", "DGBCCCK_DGGC", "DGHICAP_DGGC", "DGHIPP_DGGC",
        "DGMOPP_DGGC", "DGTML_DGGC",

        // DGMC targets (10..13)
        "DGGC_DGMC", "DGMC_DGMC", "DGAAC_DGMC", "DGTML_DGMC",

        // DGAAC targets (14..23)
        "LEC_DGAAC", "MEC_DGAAC", "DGGC_DGAAC", "DGMC_DGAAC",
        "DGBC_DGAAC", "DGBCCCK_DGAAC", "DGHICAP_DGAAC", "DGHIPP_DGAAC",
        "DGMOPP_DGAAC", "DGTML_DGAAC",

        // DGBC targets (24..33)
        "LEC_DGBC", "MEC_DGBC", "DGGC_DGBC", "DGMC_DGBC",
        "DGBC_DGBC", "DGBCCCK_DGBC", "DGHICAP_DGBC", "DGHIPP_DGBC",
        "DGMOPP_DGBC", "DGTML_DGBC",

        // DGBCCCK targets (34..42)
        "LEC_DGBCCCK", "MEC_DGBCCCK", "DGAAC_DGBCCCK", "DGBC_DGBCCCK",
        "DGBCCCK_DGBCCCK", "DGHICAP_DGBCCCK", "DGHIPP_DGBCCCK", "DGMOPP_DGBCCCK",
        "DGTML_DGBCCCK",

        // DGHICAP targets (43..52)
        "LEC_DGHICAP", "MEC_DGHICAP", "DGGC_DGHICAP", "DGMC_DGHICAP",
        "DGBC_DGHICAP", "DGBCCCK_DGHICAP", "DGHICAP_DGHICAP", "DGHIPP_DGHICAP",
        "DGMOPP_DGHICAP", "DGTML_DGHICAP",

        // DGHIPP targets (53..55)
        "DGGC_DGHIPP", "DGMC_DGHIPP", "DGTML_DGHIPP",

        // DGMOPP targets (56..60)
        "LEC_DGMOPP", "MEC_DGMOPP", "DGHIPP_DGMOPP", "DGMOPP_DGMOPP",
        "DGTML_DGMOPP",

        // DGTML targets (61..66)
        "LEC_DGTML", "MEC_DGTML", "DGHICAP_DGTML", "DGHIPP_DGTML",
        "DGMOPP_DGTML", "DGTML_DGTML",

    };

    spec.default_fr_targets = {
        {"DG_GC", 0.66}, {"DG_MC", 1.6}, {"DG_BC", 20.0}, {"DG_AAC", 20.0},
        {"DG_BCCCK", 5.0}, {"DG_HICAP", 5.0}, {"DG_HIPP", 20.0},
        {"DG_MOPP", 5.0}, {"DG_TML", 5.0}
    };

    spec.default_fr_bounds = {
        {"DG_GC", {0.55, 0.92}}, {"DG_MC", {0.98, 2.92}},
        {"DG_BC", {15.0, 36.0}}, {"DG_AAC", {15.0, 36.0}},
        {"DG_BCCCK", {1.0, 8.0}}, {"DG_HICAP", {1.0, 8.0}},
        {"DG_HIPP", {4.0, 36.0}}, {"DG_MOPP", {4.0, 25.0}},
        {"DG_TML", {4.0, 25.0}}
    };

    spec.ei_registrations = {
        {"DG_GC",    {0,1,2},       {3,4,5,6,7,8,9}},
        {"DG_MC",    {10,11},       {12,13}},
        {"DG_AAC",   {14,15,16,17}, {18,19,20,21,22,23}},
        {"DG_BC",    {24,25,26,27}, {28,29,30,31,32,33}},
        {"DG_BCCCK", {34,35},       {36,37,38,39,40,41,42}},
        {"DG_HICAP", {43,44,45,46}, {47,48,49,50,51,52}},
        {"DG_HIPP",  {53,54},       {55}},
        {"DG_MOPP",  {56,57},       {58,59,60}},
        {"DG_TML",   {61,62},       {63,64,65,66}}
    };

    spec.default_velocity = 0.13;
    spec.velocity_by_pre_group = { {"EC_MEC", 0.32}, {"EC_LEC", 1.36} };
    spec.ec_to_gc_infra_weight_scale = 1.19;

    return spec;
}

}  // namespace hippomodel::DG
