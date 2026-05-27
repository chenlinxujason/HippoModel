#include "hippomodel/region/CA1/CA1RegionSpec.h"

namespace hippomodel::CA1 {

CA1RegionSpec makeCA1RegionSpec() {
    CA1RegionSpec spec;

    spec.h5_groups = {
        {"EC_LEC3", "IDranges/EC/LEC3", "EC-LEC3"},
        {"EC_MEC3", "IDranges/EC/MEC3", "EC-MEC3"},
        {"CA3_PC", "IDranges/CA3/PC", "CA3-PC"},
        {"CA1_PC", "IDranges/CA1/PC", "CA1-PC"},
        {"CA1_AAC", "IDranges/CA1/AAC", "CA1-AAC"},
        {"CA1_BC", "IDranges/CA1/BC", "CA1-BC"},
        {"CA1_BCCCK", "IDranges/CA1/BCCCK", "CA1-BCCCK"},
        {"CA1_BisC", "IDranges/CA1/Bistratified", "CA1-Bistratified"},
        {"CA1_NG", "IDranges/CA1/Neurogliaform", "CA1-Neurogliaform"},
        {"CA1_OLM", "IDranges/CA1/OLM", "CA1-OLM"},
        {"CA1_TL", "IDranges/CA1/Trilaminar", "CA1-Trilaminar"},
    };

    spec.optimized_connection_order = {
        // CA1PC targets (0..10)
        "LEC3_CA1PC", "MEC3_CA1PC", "CA3PC_CA1PC", "CA1PC_CA1PC",
        "CA1AAC_CA1PC", "CA1BC_CA1PC", "CA1BCCCK_CA1PC", "CA1BisC_CA1PC",
        "CA1NG_CA1PC", "CA1OLM_CA1PC", "CA1TL_CA1PC",

        // CA1AAC targets (11..20)
        "LEC3_CA1AAC", "MEC3_CA1AAC", "CA3PC_CA1AAC", "CA1PC_CA1AAC",
        "CA1BC_CA1AAC", "CA1BCCCK_CA1AAC", "CA1BisC_CA1AAC", "CA1NG_CA1AAC",
        "CA1OLM_CA1AAC", "CA1TL_CA1AAC",

        // CA1BC targets (21..30)
        "LEC3_CA1BC", "MEC3_CA1BC", "CA3PC_CA1BC", "CA1PC_CA1BC",
        "CA1BC_CA1BC", "CA1BCCCK_CA1BC", "CA1BisC_CA1BC", "CA1NG_CA1BC",
        "CA1OLM_CA1BC", "CA1TL_CA1BC",

        // CA1BCCCK targets (31..40)
        "LEC3_CA1BCCCK", "MEC3_CA1BCCCK", "CA3PC_CA1BCCCK", "CA1PC_CA1BCCCK",
        "CA1BC_CA1BCCCK", "CA1BCCCK_CA1BCCCK", "CA1BisC_CA1BCCCK",
        "CA1NG_CA1BCCCK", "CA1OLM_CA1BCCCK", "CA1TL_CA1BCCCK",

        // CA1BisC targets (41..46)
        "CA3PC_CA1BisC", "CA1PC_CA1BisC", "CA1BC_CA1BisC",
        "CA1BCCCK_CA1BisC", "CA1BisC_CA1BisC", "CA1TL_CA1BisC",

        // CA1NG targets (47..50)
        "LEC3_CA1NG", "MEC3_CA1NG", "CA1NG_CA1NG", "CA1OLM_CA1NG",

        // CA1OLM targets (51..54)
        "CA3PC_CA1OLM", "CA1PC_CA1OLM", "CA1BisC_CA1OLM", "CA1TL_CA1OLM",

        // CA1TL targets (55..58)
        "CA3PC_CA1TL", "CA1PC_CA1TL", "CA1BisC_CA1TL", "CA1TL_CA1TL",
    };

    spec.default_fr_targets = { {"CA1_PC", 2.6}, {"CA1_AAC", 7.85}, {"CA1_BC", 18.1}, {"CA1_BCCCK", 25.24}, {"CA1_BisC", 30.42}, {"CA1_NG", 8.0}, {"CA1_OLM", 17.3}, {"CA1_TL", 19.0} };

    spec.default_fr_bounds = { {"CA1_PC", {2.5, 3.59}}, {"CA1_AAC", {6.9, 8.8}}, {"CA1_BC", {10.07, 26.35}}, {"CA1_BCCCK", {15.3, 35.18}}, {"CA1_BisC", {18.7, 55.0}}, {"CA1_NG", {1.0, 30.44}}, {"CA1_OLM", {15.3, 22.3}}, {"CA1_TL", {7.0, 30.0}} };

    spec.ei_registrations = {
        {"CA1_PC", {0,1,2,3}, {4,5,6,7,8,9,10}},
        {"CA1_AAC", {11,12,13,14}, {15,16,17,18,19,20}},
        {"CA1_BC", {21,22,23,24}, {25,26,27,28,29,30}},
        {"CA1_BCCCK", {31,32,33,34}, {35,36,37,38,39,40}},
        {"CA1_BisC", {41,42}, {43,44,45,46}},
        {"CA1_NG", {47,48}, {49}},
        {"CA1_OLM", {50,51}, {52}},
        {"CA1_TL", {53,54}, {55,56,57,58}}
    };

    spec.default_velocity = 0.13;
    spec.velocity_by_pre_group = { {"EC_MEC3", 0.32}, {"EC_LEC3", 1.36}, {"CA3_PC", 0.25}, {"CA1_PC", 0.34} };

    return spec;
}

}  // namespace hippomodel::CA1
