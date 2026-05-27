#include "hippomodel/region/CA3/CA3RegionSpec.h"

namespace hippomodel::CA3 {

CA3RegionSpec makeCA3RegionSpec() {
    CA3RegionSpec spec;

    spec.h5_groups = {
        {"EC_LEC", "IDranges/EC/LEC", "EC-LEC"},
        {"EC_MEC", "IDranges/EC/MEC", "EC-MEC"},
        {"DG_GC", "IDranges/DG/GC", "DG-GC"},
        {"CA3_PC", "IDranges/CA3/PC", "CA3-PC"},
        {"CA3_AAC", "IDranges/CA3/AAC", "CA3-AAC"},
        {"CA3_BC", "IDranges/CA3/BC", "CA3-BC"},
        {"CA3_BCCCK", "IDranges/CA3/BCCCK", "CA3-BCCCK"},
        {"CA3_BisC", "IDranges/CA3/Bistratified", "CA3-Bistratified"},
        {"CA3_MFA", "IDranges/CA3/MFA", "CA3-MFA"},
        {"CA3_OLM", "IDranges/CA3/OLM", "CA3-OLM"},
        {"CA3_TL", "IDranges/CA3/Trilaminar", "CA3-Trilaminar"},
    };

    spec.optimized_connection_order = {
        // CA3PC targets (0..10)
        "LEC_CA3PC", "MEC_CA3PC", "DGGC_CA3PC", "CA3PC_CA3PC",
        "CA3AAC_CA3PC", "CA3BC_CA3PC", "CA3BCCCK_CA3PC", "CA3BisC_CA3PC",
        "CA3MFA_CA3PC", "CA3OLM_CA3PC", "CA3TL_CA3PC",

        // CA3AAC targets (11..18)
        "LEC_CA3AAC", "MEC_CA3AAC", "DGGC_CA3AAC", "CA3PC_CA3AAC",
        "CA3BCCCK_CA3AAC", "CA3BisC_CA3AAC", "CA3OLM_CA3AAC", "CA3TL_CA3AAC",

        // CA3BC targets (19..28)
        "LEC_CA3BC", "MEC_CA3BC", "DGGC_CA3BC", "CA3PC_CA3BC",
        "CA3BC_CA3BC", "CA3BCCCK_CA3BC", "CA3BisC_CA3BC", "CA3MFA_CA3BC",
        "CA3OLM_CA3BC", "CA3TL_CA3BC",

        // CA3BCCCK targets (29..36)
        "DGGC_CA3BCCCK", "CA3PC_CA3BCCCK", "CA3BC_CA3BCCCK",
        "CA3BCCCK_CA3BCCCK", "CA3BisC_CA3BCCCK", "CA3MFA_CA3BCCCK",
        "CA3OLM_CA3BCCCK", "CA3TL_CA3BCCCK",

        // CA3BisC targets (37..44)
        "DGGC_CA3BisC", "CA3PC_CA3BisC", "CA3BC_CA3BisC",
        "CA3BCCCK_CA3BisC", "CA3BisC_CA3BisC", "CA3MFA_CA3BisC",
        "CA3OLM_CA3BisC", "CA3TL_CA3BisC",

        // CA3MFA targets (45..52)
        "DGGC_CA3MFA", "CA3PC_CA3MFA", "CA3BC_CA3MFA",
        "CA3BCCCK_CA3MFA", "CA3BisC_CA3MFA", "CA3MFA_CA3MFA",
        "CA3OLM_CA3MFA", "CA3TL_CA3MFA",

        // CA3OLM targets (53..56)
        "CA3PC_CA3OLM", "CA3BisC_CA3OLM", "CA3OLM_CA3OLM", "CA3TL_CA3OLM",

        // CA3TL targets (57..60)
        "CA3PC_CA3TL", "CA3BisC_CA3TL", "CA3OLM_CA3TL", "CA3TL_CA3TL",
    };

    spec.default_fr_targets = { {"CA3_PC", 0.9}, {"CA3_AAC", 17.58}, {"CA3_BC", 21.0}, {"CA3_BCCCK", 2.82}, {"CA3_BisC", 30.44}, {"CA3_MFA", 2.82}, {"CA3_OLM", 6.14}, {"CA3_TL", 19.5} };

    spec.default_fr_bounds = { {"CA3_PC", {0.67, 1.24}}, {"CA3_AAC", {7.63, 22.0}}, {"CA3_BC", {13.0, 22.0}}, {"CA3_BCCCK", {1.2, 8.0}}, {"CA3_BisC", {15.0, 26.0}}, {"CA3_MFA", {1.2, 8.0}}, {"CA3_OLM", {4.0, 25.0}}, {"CA3_TL", {15.0, 30.5}} };

    spec.ei_registrations = {
        {"CA3_PC", {0,1,2,3}, {4,5,6,7,8,9,10}},
        {"CA3_AAC", {11,12,13,14}, {15,16,17,18}},
        {"CA3_BC", {19,20,21,22}, {23,24,25,26,27,28}},
        {"CA3_BCCCK", {29,30}, {31,32,33,34,35,36}},
        {"CA3_BisC", {37,38}, {39,40,41,42,43,44}},
        {"CA3_MFA", {45,46}, {47,48,49,50,51,52}},
        {"CA3_OLM", {53}, {54,55,56}},
        {"CA3_TL", {57}, {58,59,60}}
    };

    spec.default_velocity = 0.13;
    spec.velocity_by_pre_group = { {"EC_MEC", 0.32}, {"EC_LEC", 1.36}, {"DG_GC", 0.27}, {"CA3_PC", 0.39} };

    return spec;
}

}  // namespace hippomodel::CA3
