// Set the original fixed baseline weights and optimized scaling factors.
// This header contains statements included inside main, sharing its local variables.
// ======================================
// Add values to weight map from optimization
// ======================================

// 1. Optimization Output (Direct Output of Scaling Factors of Optimization) - just copy and paste the NM output

/*
// scale500 theta baselineWts - old only modify a and b, did not optimize conduction velocity
float baselineWts[] = {
    // EC_LEC (7)
    0.36, 0.097, 0.17, 0.12, 0.045, 0.1, 0.21, //0.051, 0.97, 1.7, 1.198, 0.451, 0.607, 2.1 (divided by 10)
    // EC_MEC (7)
    0.36, 0.097, 0.17, 0.12, 0.045, 0.1, 0.21, //0.051, 0.97, 1.7, 1.198, 0.451, 0.607, 2.1(divided by 10)
    // DG_GC (5)y 4; better initial guess by increase MC-GC: 0.0326
    // DG_AAC (3)
    0.24, 1.3, 0.5, //0.24 inh, 0.358, 2.76, 1.087,(divided by 2)
    // DG_BC (5)
    0.24, 0.3, 0.8, 0.5, 0.3, //0.24 inh,0.14, 0.736, 1.623, 1.087, 0.678, (divided by 2)
    // DG_BCCCK (5)
    0.24, 0.3, 0.8, 0.5, 0.3, //0.24 inh,0.14, 0.736, 1.623, 1.087, 0.678, (divided by 2)
    // DG_HICAP (6)
    0.24, 0.3, 0.8, 0.5, 0.3, 0.9, //0.24 inh,0.14, 0.736, 1.623, 1.087, 0.678, 1.912, (divided by 2)
    // DG_HIPP (7)
    0.24, 0.245, 0.541, 0.362, 0.226, 0.64, 0.637, //0.24 inh,0.358, 0.736, 1.623, 1.087, 0.678, 1.92, 1.912, (divided by 3)
    // DG_MOPP (7)
    0.24, 0.3, 0.8, 0.5, 0.3, 0.9, 0.9, //0.24 inh,0.14, 0.736, 1.623, 1.087, 0.678, 1.92, 1.912,(divided by 2)
    // DG_TML (9)
    0.24, 1.38, 0.245, 0.541, 0.362, 0.226, 0.46, 0.64, 0.637 //0.24 inh,0.358, 2.76, 0.736, 1.623, 1.087, 0.678, 1.4, 1.92, 1.912(divided by 3, TML-BC scale 2)
};
*/

/*
// scale500 theta scalingfactor - old only modify a and b, did not optimize conduction velocity
std::vector<float> scalingFactors = { 0.538048, 1.70151, 0.552039, 1.14882, 1.05432, 0.625614, 0.624031, 0.648585, 1.29162, 0.611839, 2.70807, 1.63153, 0.811268, 0.834112, 0.487725, 0.80998, 1.1692, 0.950946, 1.13809, 0.832586, 0.740166, 0.636242, 0.904648, 1.34741, 1.06398, 1.81393, 2.21435, 1.0484, 0.422074, 1.22778, 0.603919, 0.506116, 0.513381, 1.15606, 3.55032, 1.81736, 0.165646, 0.346889, 0.383212, 0.271151, 0.363127, 0.335655, 0.256987, 1.97762, 4.14831, 3.54346, 6.78853, 0.472637, 0.222626, 0.15987, 0.107582, 0.175773, 0.166674, 2.62341, 2.3433, 0.248077, 10.8974, 13.4264, 0.0849257, 0.0320303, 0.082077, 1.77976, 3.904, 0.116957, 0.365161, 0.174522, 0.335775 };//scale 500 model - low corr, high theta, 54%, MC-GC baseWt=0.0326,set MC upper bound 1.5

std::vector<float> scalingFactors = { 0.674757, 1.15415, 1.2897, 1.25449, 1.35882, 1.32687, 1.12552, 1.66303, 0.741722, 0.513235, 2.36833, 3.53508, 0.386368, 0.262214, 1.03266, 1.11618, 0.742582, 1.06697, 0.183632, 1.02165, 0.742742, 0.825582, 0.816475, 1.38989, 1.6992, 1.1877, 0.523748, 1.57927, 0.613421, 1.06073, 0.94321, 0.84487, 0.392437, 0.494713, 2.23471, 3.23287, 0.623371, 0.208857, 0.648347, 0.427668, 0.142521, 0.719151, 0.57892, 1.66745, 3.52877, 3.62037, 3.9367, 0.109962, 0.27829, 0.578755, 0.492131, 0.481146, 0.0695164, 3.24495, 0.72796, 0.353643, 14.7985, 14.6979, 0.0185788, 0.0251375, 0.0220314, 2.23565, 4.26622, 0.266439, 0.438277, 0.530592, 0.459961 };//scale 500 model - high corr, high theta, 35%, MC-GC baseWt=0.0326, ok

std::vector<float> scalingFactors = { 1.65732, 0.844386, 0.466473, 3.02672, 0.869561, 0.888899, 1.00428, 0.586562, 1.7292, 1.96302, 3.83792, 1.33672, 1.01548, 0.64203, 0.6568, 0.350629, 1.204, 0.381871, 1.70987, 2.01666, 0.781557, 0.753998, 1.48071, 1.0476, 1.93964, 1.1939, 1.37687, 1.11955, 0.334423, 1.18079, 0.846181, 2.53792, 0.337004, 0.5225, 2.36135, 3.79914, 0.295932, 0.165757, 0.211047, 0.476665, 0.121622, 0.133429, 0.460364, 1.97533, 2.21673, 3.16241, 1.96262, 0.358046, 0.627887, 0.260696, 0.262268, 0.37712, 0.379358, 3.24634, 1.79137, 0.0893394, 11.6878, 14.3089, 0.0374604, 0.0101802, 0.0265069, 2.55044, 4.09693, 0.0467262, 0.115572, 0.0883099, 0.201425 };//scale 500 model - low corr, low theta, 3.685%, MC-GC baseWt=0.0326, ok

std::vector<float> scalingFactors = { 0.992856, 1.466, 1.41302, 1.21254, 0.879302, 0.961928, 2.17279, 0.547487, 1.02207, 1.31454, 2.63434, 1.84168, 0.538811, 1.15069, 0.64579, 0.652385, 1.30221, 0.79183, 1.38816, 1.22265, 0.50248, 0.601766, 0.68089, 0.41988, 1.15583, 0.776699, 4.69944, 1.11079, 0.464847, 1.23016, 1.25614, 0.903988, 0.705909, 0.780639, 3.18916, 3.41312, 0.219476, 0.418697, 0.26088, 0.0939271, 0.22526, 0.267171, 0.192743, 1.6632, 3.21268, 3.40543, 3.9346, 0.374515, 0.35976, 0.182982, 0.249518, 0.276387, 0.128165, 4.04394, 4.30997, 0.125455, 13.5059, 11.9943, 0.0388075, 0.0456362, 0.067473, 2.36987, 5.1009, 0.133501, 0.200838, 0.094425, 0.164761 };//scale 500 model - high corr, low theta, 18%, MC-GC baseWt=0.0326

std::vector<float> scalingFactors = { 0.965745f, 1.29151f, 0.930308f, 1.66064f, 1.0405f, 0.950828f, 1.23166f, 0.861416f, 1.19615f, 1.10066f, 2.88716f, 2.08625f, 0.687982f, 0.722262f, 0.705744f, 0.732293f, 1.1045f, 0.797904f, 1.10494f, 1.27339f, 0.691736f, 0.704397f, 0.970681f, 1.0512f, 1.46466f, 1.24306f, 2.2036f, 1.2145f, 0.458691f, 1.17487f, 0.912362f, 1.19822f, 0.487183f, 0.738478f, 2.83389f, 3.06562f, 0.326106f, 0.28505f, 0.375872f, 0.317353f, 0.213133f, 0.363851f, 0.372254f, 1.8209f, 3.27662f, 3.43292f, 4.15561f, 0.32879f, 0.372141f, 0.295576f, 0.277875f, 0.327606f, 0.185928f, 3.28966f, 2.29315f, 0.204129f, 12.7224f, 13.6069f, 0.0449431f, 0.028246f, 0.0495221f, 2.23393f, 4.34201f, 0.140906f, 0.279962f, 0.221962f, 0.29048f }; // average wn scaling factors across four DG regimes - no firing at all for GC
*/

//scale 10 - update conduction velocity (modify b,vth,k,d) - 33.5ms HHW - correct
float baselineWts[] = {
    // EC_LEC (7)
    0.069, 0.291, 0.51, 0.4792, 0.1353, 0.4, 0.63, //0.088, 0.097, 0.17, 0.1198, 0.0451, 0.4, 0.21
    // EC_MEC (7)
    0.069, 0.291, 0.51, 0.4792, 0.1353, 0.4, 0.63, //0.088, 0.097, 0.17, 0.1198, 0.0451, 0.4, 0.21
    // DG_GC (5)
    4.66, 0.377, 0.67, 0.1824, 0.4328, //9.32, 3.77, 6.7, 1.824, 4.328, (divided by 10)
    // DG_MC (6) 
    0.0245, 0.7045, 0.059, 0.126, 0.015, 0.0826, //0.0457, 1.17, 1.78, 3.8, 0.46, 2.479;  OLD:1.798, 2.3, 3.75, 6.66, 0.46, 2.479; 
    // DG_AAC (3)
    1.032, 0.926, 0.5, //0.24 inh, 0.358, 2.76, 1.087,(divided by 2)
    // DG_BC (5)
    1.032, 0.3, 0.8, 0.5, 0.3, //0.24 inh,0.14, 0.736, 1.623, 1.087, 0.678, (divided by 2)
    // DG_BCCCK (5)
    1.032, 0.3, 0.8, 0.5, 0.3, //0.24 inh,0.14, 0.736, 1.623, 1.087, 0.678, (divided by 2)
    // DG_HICAP (6)
    1.032, 0.3, 0.8, 0.5, 0.3, 0.9, //0.24 inh,0.14, 0.736, 1.623, 1.087, 0.678, 1.912, (divided by 2)
    // DG_HIPP (7)
    1.032, 0.245, 0.541, 0.362, 0.226, 0.64, 0.637, //0.24 inh,0.358, 0.736, 1.623, 1.087, 0.678, 1.92, 1.912, (divided by 3)
    // DG_MOPP (7)
    1.032, 0.3, 0.8, 0.5, 0.3, 0.9, 0.9, //0.24 inh,0.14, 0.736, 1.623, 1.087, 0.678, 1.92, 1.912,(divided by 2)
    // DG_TML (9)
    1.032, 0.926, 0.245, 0.541, 0.362, 0.226, 0.46, 0.64, 0.637 //0.24 inh,0.358, 2.76, 0.736, 1.623, 1.087, 0.678, 1.4, 1.92, 1.912(divided by 3, TML-BC scale 2)
};

// scale 10 - update conduction velocity (modify b,vth,k,d) - 33.5ms HHW
std::vector<float> scalingFactors = { 5.462, 10.6172, 0.73281, 0.0915174, 0.145243, 0.0493088, 0.20404, 0.140271, 0.165101, 0.182515, 1.3194, 1.31141, 0.666096, 1.75421, 1.02813, 1.1974, 2.39377, 1.1779, 1.675, 0.771732, 0.611848, 0.647825, 0.911139, 0.820431, 2.84355, 1.88097, 2.97285, 0.717067, 0.480332, 0.472488, 0.388372, 0.339123, 0.728505, 0.332676, 6.36314, 6.80747, 0.289864, 0.230284, 0.123751, 0.144693, 0.224654, 0.28356, 0.158263, 4.76416, 5.78078, 3.60187, 1.11303, 0.223168, 0.255345, 0.167174, 0.196443, 0.21204, 0.208932, 2.54761, 0.948762, 0.232283, 2.64831, 4.13911, 0.37612, 0.204398, 0.243056, 3.32646, 4.70159, 0.289112, 0.165677, 0.44537, 0.416257 }; //scale 10 model - 75% - correct



//scale 10 - update conduction velocity (modify b,vth,k,d) - 12ms HHW (MC-MC: 1.409/3/10=0.0469)
/*
float baselineWts[] = {
    // EC_LEC (7)
    0.088, 0.291, 0.51, 0.4792, 0.1353, 0.4, 0.63, //0.088, 0.097, 0.17, 0.1198, 0.0451, 0.4, 0.21
    // EC_MEC (7)
    0.088, 0.291, 0.51, 0.4792, 0.1353, 0.4, 0.63, //0.088, 0.097, 0.17, 0.1198, 0.0451, 0.4, 0.21
    // DG_GC (5)
    8.0, 0.377, 0.67, 0.1824, 0.4328, //9.32, 3.77, 6.7, 1.824, 4.328, (divided by 10)
    // DG_MC (6) 
    0.023, 0.0469, 0.059, 0.126, 0.015, 0.0826, //0.0457, 1.17, 1.78, 3.8, 0.46, 2.479;  OLD:1.798, 2.3, 3.75, 6.66, 0.46, 2.479; 
    // DG_AAC (3)
    0.344, 0.926, 0.5, //0.24 inh, 0.358, 2.76, 1.087,(divided by 2)
    // DG_BC (5)
    0.344, 0.3, 0.8, 0.5, 0.3, //0.24 inh,0.14, 0.736, 1.623, 1.087, 0.678, (divided by 2)
    // DG_BCCCK (5)
    0.344, 0.3, 0.8, 0.5, 0.3, //0.24 inh,0.14, 0.736, 1.623, 1.087, 0.678, (divided by 2)
    // DG_HICAP (6)
    0.344, 0.3, 0.8, 0.5, 0.3, 0.9, //0.24 inh,0.14, 0.736, 1.623, 1.087, 0.678, 1.912, (divided by 2)
    // DG_HIPP (7)
    0.344, 0.245, 0.541, 0.362, 0.226, 0.64, 0.637, //0.24 inh,0.358, 0.736, 1.623, 1.087, 0.678, 1.92, 1.912, (divided by 3)
    // DG_MOPP (7)
    0.344, 0.3, 0.8, 0.5, 0.3, 0.9, 0.9, //0.24 inh,0.14, 0.736, 1.623, 1.087, 0.678, 1.92, 1.912,(divided by 2)
    // DG_TML (9)
    0.344, 0.926, 0.245, 0.541, 0.362, 0.226, 0.46, 0.64, 0.637 //0.24 inh,0.358, 2.76, 0.736, 1.623, 1.087, 0.678, 1.4, 1.92, 1.912(divided by 3, TML-BC scale 2)
};
*/

// scale 10 - update conduction velocity (modify b,vth,k,d) - 12ms HHW
//std::vector<float> scalingFactors = { 6.97131, 5.85315, 1.17914, 0.135783, 0.126384, 0.154625, 0.166825, 0.23275, 0.174998, 0.1868, 1.07077, 0.827391, 2.14057, 2.27026, 1.49146, 0.977273, 1.30611, 1.08813, 0.926976, 0.521788, 0.695641, 0.80343, 1.18642, 0.825582, 1.74365, 1.74148, 2.79454, 0.683008, 0.456688, 0.254937, 1.0778, 0.592737, 0.166794, 0.204121, 3.32757, 5.32411, 0.287052, 0.290456, 0.0711649, 0.229386, 0.127279, 0.234598, 0.181825, 3.13432, 3.27325, 3.84953, 0.833894, 0.342241, 0.377529, 0.194494, 0.231308, 0.351742, 0.336865, 3.2821, 0.754016, 0.143439, 5.71064, 6.44562, 0.11376, 0.0747824, 0.184232, 5.04458, 5.86381, 0.125093, 0.270848, 0.274274, 0.479604 }; //scale 10 model - 107.252% 

/*
//--------------------------------------------------
// Designed scaling factor and Wt: 
// FR good; Corr=0.3 ; beta=0.27; gamma=0.45
// 0.753458 2.37882 27.3248 17.922 1.87 3.68193 11.2142 4.08 4.07231
//--------------------------------------------------
std::vector<float> scalingFactors = { 4.80823, 6.47028, 1.17173, 0.0609754, 0.196673, 0.128488, 0.0869127, 0.194732, 0.335721, 0.236739, 0.52524, 0.522366, 2.40807, 4.05544, 2.39444, 1.72995, 1.13239, 0.5943, 2.56837, 0.598114, 0.330459, 0.5202, 0.497792, 0.531875, 1.23611, 1.92959, 4.32636, 0.969557, 0.507741, 0.804123, 0.371222, 0.530859, 0.295249, 0.273772, 1.45612, 2.07597, 0.278227, 0.26522, 0.192178, 0.282141, 0.412735, 0.577335, 0.431299, 1.42945, 2.12972, 3.04269, 0.795021, 0.444725, 0.433882, 0.377767, 0.317888, 0.436908, 0.450279, 2.57369, 0.824046, 0.330378, 3.4401, 4.15349, 0.116035, 0.114156, 0.0991023, 2.75595, 3.32782, 0.422861, 0.454146, 0.208649, 0.360774 }; //scale 500 model - 44.9167% - FR good; Corr=0.3 ; beta=0.27; gamma=0.45

std::map<std::string, float> baselineWts = {
    // EC_LEC (7)
    {"LEC_DGGC",    0.1f}, 
    {"LEC_DGAAC",   0.4f},
    {"LEC_DGBC",    0.3f},
    {"LEC_DGBCCCK", 0.9f},
    {"LEC_DGHICAP", 0.2f},
    {"LEC_DGMOPP",  0.5f},
    {"LEC_DGTML",   0.7f},
    // EC_MEC (7)
    {"MEC_DGGC",    0.1f}, 
    {"MEC_DGAAC",   0.3f},
    {"MEC_DGBC",    0.2f},
    {"MEC_DGBCCCK", 0.8f},
    {"MEC_DGHICAP", 0.2f},
    {"MEC_DGMOPP",  0.4f},
    {"MEC_DGTML",   0.7f},
    // DG_GC (5)
    {"DGGC_DGMC",    5.0f},//9.32 PSP, 8.0 for tdAMPA=10.02; 9.32/2=4.66 for tdAMPA=40.91
    {"DGGC_DGAAC",   0.2f},
    {"DGGC_DGBC",    0.7f},
    {"DGGC_DGHICAP", 0.2f},
    {"DGGC_DGHIPP",  0.5f},
    // DG_MC (6) //0.0457, 1.17, 1.78, 3.8, 0.46, 2.479;
    // IN: divided by 50; MC-GC divided by 2
    {"DGMC_DGGC",    0.02f}, 
    {"DGMC_DGMC",    0.5f},
    {"DGMC_DGAAC",   0.03f},
    {"DGMC_DGBC",    0.1f},
    {"DGMC_DGHICAP", 0.02f},
    {"DGMC_DGHIPP",  0.06f},
    // DG_AAC (3)
    {"DGAAC_DGGC",    0.8f},//0.344 borrow PSP; try 0.344*3 = 1.032 to compensate low Exc-GC iteration
    {"DGAAC_DGMC",    0.7f},//1.3 old; 2.78 PSP, try 2.78/3 = 0.926
    {"DGAAC_DGBCCCK", 0.4f},
    // DG_BC (5)
    {"DGBC_DGGC",    0.9f},//0.344 borrow PSP; try 0.344*3 = 1.032 to compensate low Exc-GC iteration
    {"DGBC_DGAAC",   0.35f},
    {"DGBC_DGBC",    0.7f},
    {"DGBC_DGBCCCK", 0.2f},
    {"DGBC_DGHICAP", 0.2f},
    // DG_BCCCK (5)
    {"DGBCCCK_DGGC",    1.0f},//0.344 borrow PSP; try 0.344*3 = 1.032 to compensate low Exc-GC iteration
    {"DGBCCCK_DGAAC",   0.6f},
    {"DGBCCCK_DGBC",    0.5f},
    {"DGBCCCK_DGBCCCK", 0.5f},
    {"DGBCCCK_DGHICAP", 0.34f},
    // DG_HICAP (6)
    {"DGHICAP_DGGC",    1.032f},//0.344 borrow PSP; try 0.344*3 = 1.032 to compensate low Exc-GC iteration
    {"DGHICAP_DGAAC",   0.3f},
    {"DGHICAP_DGBC",    0.8f},
    {"DGHICAP_DGBCCCK", 0.5f},
    {"DGHICAP_DGHICAP", 0.3f},
    {"DGHICAP_DGTML",   0.9f},
    // DG_HIPP (7)
    {"DGHIPP_DGGC",    1.0f},//0.344 borrow PSP; try 0.344*3 = 1.032 to compensate low Exc-GC iteration
    {"DGHIPP_DGAAC",   0.5f},
    {"DGHIPP_DGBC",    0.4f},
    {"DGHIPP_DGBCCCK", 0.3f},
    {"DGHIPP_DGHICAP", 0.3f},
    {"DGHIPP_DGMOPP",  0.56f},
    {"DGHIPP_DGTML",   0.7f},
    // DG_MOPP (7)
    {"DGMOPP_DGGC",    0.8f},//0.344 borrow PSP; try 0.344*3 = 1.032 to compensate low Exc-GC iteration
    {"DGMOPP_DGAAC",   0.4f},
    {"DGMOPP_DGBC",    0.9f},
    {"DGMOPP_DGBCCCK", 0.3f},
    {"DGMOPP_DGHICAP", 0.2f},
    {"DGMOPP_DGMOPP",  0.7f},
    {"DGMOPP_DGTML",   0.8f},
    // DG_TML (9)
    {"DGTML_DGGC",    1.0f},//0.344 borrow PSP; try 0.344*3 = 1.032 to compensate low Exc-GC iteration
    {"DGTML_DGMC",    0.8f},//1.38 old; 2.78 PSP, try 2.78/3 = 0.926
    {"DGTML_DGAAC",   0.4f},
    {"DGTML_DGBC",    0.5f},
    {"DGTML_DGBCCCK", 0.24f},
    {"DGTML_DGHICAP", 0.36f},
    {"DGTML_DGHIPP",  0.5f},
    {"DGTML_DGMOPP",  0.6f},
    {"DGTML_DGTML",   0.64f},
};
*/

// 3. Connection Order (Convergence order)
const std::vector<std::string> DGConnectionNames = {
    // DGGC targets(10)
    "LEC_DGGC", "MEC_DGGC", "DGMC_DGGC", "DGAAC_DGGC", "DGBC_DGGC", "DGBCCCK_DGGC", "DGHICAP_DGGC", "DGHIPP_DGGC", "DGMOPP_DGGC", "DGTML_DGGC",
    // DGMC targets(4)
    "DGGC_DGMC", "DGMC_DGMC", "DGAAC_DGMC", "DGTML_DGMC",
    // DGAAC targets(10)
    "LEC_DGAAC", "MEC_DGAAC", "DGGC_DGAAC", "DGMC_DGAAC", "DGBC_DGAAC", "DGBCCCK_DGAAC", "DGHICAP_DGAAC", "DGHIPP_DGAAC", "DGMOPP_DGAAC", "DGTML_DGAAC",
    // DGBC targets(10)
    "LEC_DGBC", "MEC_DGBC", "DGGC_DGBC", "DGMC_DGBC", "DGBC_DGBC", "DGBCCCK_DGBC", "DGHICAP_DGBC", "DGHIPP_DGBC", "DGMOPP_DGBC", "DGTML_DGBC",
    // DGBCCCK targets(9)
    "LEC_DGBCCCK", "MEC_DGBCCCK", "DGAAC_DGBCCCK", "DGBC_DGBCCCK", "DGBCCCK_DGBCCCK", "DGHICAP_DGBCCCK", "DGHIPP_DGBCCCK", "DGMOPP_DGBCCCK", "DGTML_DGBCCCK",
    // DGHICAP targets(10)
    "LEC_DGHICAP", "MEC_DGHICAP", "DGGC_DGHICAP", "DGMC_DGHICAP", "DGBC_DGHICAP", "DGBCCCK_DGHICAP", "DGHICAP_DGHICAP", "DGHIPP_DGHICAP", "DGMOPP_DGHICAP", "DGTML_DGHICAP",
    // DGHIPP targets(3)
    "DGGC_DGHIPP", "DGMC_DGHIPP", "DGTML_DGHIPP",
    // DGMOPP targets(5)
    "LEC_DGMOPP", "MEC_DGMOPP", "DGHIPP_DGMOPP", "DGMOPP_DGMOPP", "DGTML_DGMOPP",
    // DGTML targets(6)
    "LEC_DGTML", "MEC_DGTML", "DGHICAP_DGTML", "DGHIPP_DGTML", "DGMOPP_DGTML", "DGTML_DGTML"
};


// 4. Helper to find scale by name
auto getScale = [&](std::string name) {
    auto it = std::find(DGConnectionNames.begin(), DGConnectionNames.end(), name);
    if (it != DGConnectionNames.end()) {
        return scalingFactors[std::distance(DGConnectionNames.begin(), it)];
    }
    return 1.0f; 
};

// 5. Insert weight
// EC_LEC
// --------------------------- EC_LEC ---------------------------
std::map<std::string, float> weights_EC_LEC;
weights_EC_LEC.insert({"DG_GC",    baselineWts[0] * getScale("LEC_DGGC")});        // 0.3 * 0.938720 = 0.281616
weights_EC_LEC.insert({"DG_AAC",   baselineWts[1] * getScale("LEC_DGAAC")});       // 0.0485 * 1.071300 = 0.051958
weights_EC_LEC.insert({"DG_BC",    baselineWts[2] * getScale("LEC_DGBC")});        // 0.085 * 1.277720 = 0.108606
weights_EC_LEC.insert({"DG_BCCCK", baselineWts[3] * getScale("LEC_DGBCCCK")});     // 0.06 * 6.785590 = 0.407135
weights_EC_LEC.insert({"DG_HICAP", baselineWts[4] * getScale("LEC_DGHICAP")});     // 0.2 * 2.807730 = 0.561546
weights_EC_LEC.insert({"DG_MOPP",  baselineWts[5] * getScale("LEC_DGMOPP")});      // 0.3 * 4.607100 = 1.382130
weights_EC_LEC.insert({"DG_TML",   baselineWts[6] * getScale("LEC_DGTML")});       // 0.105 * 7.851030 = 0.824358
map_weight.insert({"EC_LEC", weights_EC_LEC});


// --------------------------- EC_MEC ---------------------------
std::map<std::string, float> weights_EC_MEC;
weights_EC_MEC.insert({"DG_GC",    baselineWts[7] * getScale("MEC_DGGC")});        // 0.3 * 2.048490 = 0.614547
weights_EC_MEC.insert({"DG_AAC",   baselineWts[8] * getScale("MEC_DGAAC")});       // 0.0485 * 2.314090 = 0.112233
weights_EC_MEC.insert({"DG_BC",    baselineWts[9] * getScale("MEC_DGBC")});        // 0.085 * 2.792460 = 0.237359
weights_EC_MEC.insert({"DG_BCCCK", baselineWts[10] * getScale("MEC_DGBCCCK")});    // 0.06 * 8.749700 = 0.524982
weights_EC_MEC.insert({"DG_HICAP", baselineWts[11] * getScale("MEC_DGHICAP")});    // 0.2 * 2.389190 = 0.477838
weights_EC_MEC.insert({"DG_MOPP",  baselineWts[12] * getScale("MEC_DGMOPP")});     // 0.3 * 4.007450 = 1.202235
weights_EC_MEC.insert({"DG_TML",   baselineWts[13] * getScale("MEC_DGTML")});      // 0.105 * 4.806240 = 0.504655
map_weight.insert({"EC_MEC", weights_EC_MEC});


// --------------------------- DG_GC ---------------------------
std::map<std::string, float> weights_DG_GC;
weights_DG_GC.insert({"DG_MC",    baselineWts[14] * getScale("DGGC_DGMC")});       // 0.467 * 5.198040 = 2.427485
weights_DG_GC.insert({"DG_AAC",   baselineWts[15] * getScale("DGGC_DGAAC")});      // 0.09 * 1.761200 = 0.158508
weights_DG_GC.insert({"DG_BC",    baselineWts[16] * getScale("DGGC_DGBC")});       // 0.167 * 3.199460 = 0.534310
weights_DG_GC.insert({"DG_HICAP", baselineWts[17] * getScale("DGGC_DGHICAP")});    // 0.24 * 0.212958 = 0.051110
weights_DG_GC.insert({"DG_HIPP",  baselineWts[18] * getScale("DGGC_DGHIPP")});     // 0.6 * 2.920410 = 1.752246
map_weight.insert({"DG_GC", weights_DG_GC});


// --------------------------- DG_MC ---------------------------
std::map<std::string, float> weights_DG_MC;
weights_DG_MC.insert({"DG_GC",    baselineWts[19] * getScale("DGMC_DGGC")});       // 0.0126 * 1.223170 = 0.015412
weights_DG_MC.insert({"DG_MC",    baselineWts[20] * getScale("DGMC_DGMC")});       // 0.0161 * 4.788830 = 0.077102
weights_DG_MC.insert({"DG_AAC",   baselineWts[21] * getScale("DGMC_DGAAC")});      // 0.026 * 1.704890 = 0.044327
weights_DG_MC.insert({"DG_BC",    baselineWts[22] * getScale("DGMC_DGBC")});       // 0.047 * 3.037620 = 0.142768
weights_DG_MC.insert({"DG_HICAP", baselineWts[23] * getScale("DGMC_DGHICAP")});    // 0.0032 * 0.364113 = 0.001165
weights_DG_MC.insert({"DG_HIPP",  baselineWts[24] * getScale("DGMC_DGHIPP")});     // 0.0174 * 0.459359 = 0.007994
map_weight.insert({"DG_MC", weights_DG_MC});


// --------------------------- DG_AAC ---------------------------
std::map<std::string, float> weights_DG_AAC;
weights_DG_AAC.insert({"DG_GC",    baselineWts[25] * getScale("DGAAC_DGGC")});      // 0.24 * 0.802381 = 0.192571
weights_DG_AAC.insert({"DG_MC",    baselineWts[26] * getScale("DGAAC_DGMC")});      // 1.38 * 0.154246 = 0.212860
weights_DG_AAC.insert({"DG_BCCCK", baselineWts[27] * getScale("DGAAC_DGBCCCK")});   // 0.54 * 0.115278 = 0.062250
map_weight.insert({"DG_AAC", weights_DG_AAC});


// --------------------------- DG_BC ---------------------------
std::map<std::string, float> weights_DG_BC;
weights_DG_BC.insert({"DG_GC",    baselineWts[28] * getScale("DGBC_DGGC")});        // 0.24 * 0.325178 = 0.078043
weights_DG_BC.insert({"DG_AAC",   baselineWts[29] * getScale("DGBC_DGAAC")});       // 0.36 * 0.513497 = 0.184859
weights_DG_BC.insert({"DG_BC",    baselineWts[30] * getScale("DGBC_DGBC")});        // 0.8 * 0.296138 = 0.236910
weights_DG_BC.insert({"DG_BCCCK", baselineWts[31] * getScale("DGBC_DGBCCCK")});     // 0.54 * 0.191522 = 0.103422
weights_DG_BC.insert({"DG_HICAP", baselineWts[32] * getScale("DGBC_DGHICAP")});     // 0.34 * 0.243285 = 0.082717
map_weight.insert({"DG_BC", weights_DG_BC});


// --------------------------- DG_BCCCK ---------------------------
std::map<std::string, float> weights_DG_BCCCK;
weights_DG_BCCCK.insert({"DG_GC",    baselineWts[33] * getScale("DGBCCCK_DGGC")});      // 0.24 * 0.481869 = 0.115649
weights_DG_BCCCK.insert({"DG_AAC",   baselineWts[34] * getScale("DGBCCCK_DGAAC")});     // 0.36 * 0.532195 = 0.191590
weights_DG_BCCCK.insert({"DG_BC",    baselineWts[35] * getScale("DGBCCCK_DGBC")});      // 0.8 * 0.504009 = 0.403207
weights_DG_BCCCK.insert({"DG_BCCCK", baselineWts[36] * getScale("DGBCCCK_DGBCCCK")});   // 0.54 * 0.110632 = 0.059741
weights_DG_BCCCK.insert({"DG_HICAP", baselineWts[37] * getScale("DGBCCCK_DGHICAP")});   // 0.34 * 0.265810 = 0.090375
map_weight.insert({"DG_BCCCK", weights_DG_BCCCK});


// --------------------------- DG_HICAP ---------------------------
std::map<std::string, float> weights_DG_HICAP;
weights_DG_HICAP.insert({"DG_GC",    baselineWts[38] * getScale("DGHICAP_DGGC")});      // 0.24 * 1.079330 = 0.259039
weights_DG_HICAP.insert({"DG_AAC",   baselineWts[39] * getScale("DGHICAP_DGAAC")});     // 0.36 * 0.374139 = 0.134690
weights_DG_HICAP.insert({"DG_BC",    baselineWts[40] * getScale("DGHICAP_DGBC")});      // 0.8 * 0.259490 = 0.207592
weights_DG_HICAP.insert({"DG_BCCCK", baselineWts[41] * getScale("DGHICAP_DGBCCCK")});   // 0.54 * 0.152987 = 0.082613
weights_DG_HICAP.insert({"DG_HICAP", baselineWts[42] * getScale("DGHICAP_DGHICAP")});   // 0.34 * 0.174632 = 0.059375
weights_DG_HICAP.insert({"DG_TML",   baselineWts[43] * getScale("DGHICAP_DGTML")});     // 0.95 * 0.207316 = 0.196950
map_weight.insert({"DG_HICAP", weights_DG_HICAP});


// --------------------------- DG_HIPP ---------------------------
std::map<std::string, float> weights_DG_HIPP;
weights_DG_HIPP.insert({"DG_GC",    baselineWts[44] * getScale("DGHIPP_DGGC")});        // 0.17 * 0.631046 = 0.107278
weights_DG_HIPP.insert({"DG_AAC",   baselineWts[45] * getScale("DGHIPP_DGAAC")});       // 0.29 * 0.633392 = 0.183683
weights_DG_HIPP.insert({"DG_BC",    baselineWts[46] * getScale("DGHIPP_DGBC")});        // 0.65 * 0.275340 = 0.178971
weights_DG_HIPP.insert({"DG_BCCCK", baselineWts[47] * getScale("DGHIPP_DGBCCCK")});     // 0.43 * 0.267422 = 0.114991
weights_DG_HIPP.insert({"DG_HICAP", baselineWts[48] * getScale("DGHIPP_DGHICAP")});     // 0.27 * 2.920410 = 0.788511
weights_DG_HIPP.insert({"DG_MOPP",  baselineWts[49] * getScale("DGHIPP_DGMOPP")});      // 0.77 * 2.073040 = 1.596241
weights_DG_HIPP.insert({"DG_TML",   baselineWts[50] * getScale("DGHIPP_DGTML")});       // 0.76 * 0.188242 = 0.143064
map_weight.insert({"DG_HIPP", weights_DG_HIPP});


// --------------------------- DG_MOPP ---------------------------
std::map<std::string, float> weights_DG_MOPP;
weights_DG_MOPP.insert({"DG_GC",    baselineWts[51] * getScale("DGMOPP_DGGC")});        // 0.24 * 0.846702 = 0.203208
weights_DG_MOPP.insert({"DG_AAC",   baselineWts[52] * getScale("DGMOPP_DGAAC")});       // 0.36 * 0.336482 = 0.121133
weights_DG_MOPP.insert({"DG_BC",    baselineWts[53] * getScale("DGMOPP_DGBC")});        // 0.8 * 0.268409 = 0.214727
weights_DG_MOPP.insert({"DG_BCCCK", baselineWts[54] * getScale("DGMOPP_DGBCCCK")});     // 0.54 * 0.188316 = 0.101691
weights_DG_MOPP.insert({"DG_HICAP", baselineWts[55] * getScale("DGMOPP_DGHICAP")});     // 0.34 * 2.338840 = 0.795206
weights_DG_MOPP.insert({"DG_MOPP",  baselineWts[56] * getScale("DGMOPP_DGMOPP")});      // 0.96 * 4.607100 = 4.422816
weights_DG_MOPP.insert({"DG_TML",   baselineWts[57] * getScale("DGMOPP_DGTML")});       // 0.95 * 7.851030 = 7.458479
map_weight.insert({"DG_MOPP", weights_DG_MOPP});


// --------------------------- DG_TML ---------------------------
std::map<std::string, float> weights_DG_TML;
weights_DG_TML.insert({"DG_GC",    baselineWts[58] * getScale("DGTML_DGGC")});         // 0.17 * 1.087520 = 0.184878
weights_DG_TML.insert({"DG_MC",    baselineWts[59] * getScale("DGTML_DGMC")});         // 1.38 * 0.389887 = 0.538045
weights_DG_TML.insert({"DG_AAC",   baselineWts[60] * getScale("DGTML_DGAAC")});        // 0.29 * 0.712688 = 0.206679
weights_DG_TML.insert({"DG_BC",    baselineWts[61] * getScale("DGTML_DGBC")});         // 0.65 * 0.195871 = 0.127316
weights_DG_TML.insert({"DG_BCCCK", baselineWts[62] * getScale("DGTML_DGBCCCK")});      // 0.43 * 0.230990 = 0.099325
weights_DG_TML.insert({"DG_HICAP", baselineWts[63] * getScale("DGTML_DGHICAP")});      // 0.27 * 0.267422 = 0.072204
weights_DG_TML.insert({"DG_HIPP",  baselineWts[64] * getScale("DGTML_DGHIPP")});       // 0.56 * 0.299344 = 0.167633
weights_DG_TML.insert({"DG_MOPP",  baselineWts[65] * getScale("DGTML_DGMOPP")});       // 0.77 * 0.177763 = 0.136878
weights_DG_TML.insert({"DG_TML",   baselineWts[66] * getScale("DGTML_DGTML")});        // 0.76 * 0.134282 = 0.102054
map_weight.insert({"DG_TML", weights_DG_TML});
    
