// 62 variables(0 - 61 connections), 63 vertex 
// These variables are synaptic weight, range from 0.07 - 1.0


//#ifndef INITIAL_SIMPLEX_DG_H
//#define INITIAL_SIMPLEX_DG_H

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

// Define the inputVertices structure with three vertices, each containing initial values for all neuron groups
std::vector<std::vector<double>> inputVertices = {
    // Vertex 1: bioWt
    {
        // DGGC Exc (scale 10)
        0.223, 0.223, 0.789, //0.223,0.223,0.789; or 0.292,0.292,0.789
        // DGGC Inh
        0.33, 0.33, 0.33, 0.33, 0.33, 0.33, 0.33,// 0.33 or 0.544
        // DGMC Exc (scale 10)
        1.504, 1.504, //1.504, 1.504
        // DGMC Inh
        3.27, 3.27,
        // DGAAC Exc (scale 10)
        0.983, 0.983, 1.928, 1.105, //0.527, 0.527, 0.527, 0.527,
        // DGAAC Inh
        0.517, 0.517, 0.517, 0.517, 0.517, 0.517,
        // DGBC Exc (scale 10)
        1.33, 1.33, 2.65, 0.8,
        // DGBC Inh
        1.542, 1.542, 1.542, 1.542, 1.542, 1.542,
        // DGBCCCK Exc (scale 10)
        1.092, 1.092,
        // DGBCCCK Inh
        1.096, 1.096, 1.096, 1.096, 1.096, 1.096, 1.096,
        // DGHICAP Exc (scale 10)
        0.669, 0.669, 1.341, 0.671,
        // DGHICAP Inh
        0.656, 0.656, 0.656, 0.656, 0.656, 0.656,
        // DGHIPP Exc (scale 10)
        2.066, 1.568,
        // DGHIPP Inh
        1.374,
        // DGMOPP Exc (scale 10)
        0.822, 0.822,
        // DGMOPP Inh
        1.85, 1.85, 1.85,
        // DGTML Exc (scale 10)
        1.45, 1.45,
        // DGTML Inh
        1.862, 1.862, 1.862, 1.862
    }//,
/*
    // Vertex 2: scaleWt modify
    {
        // DGGC Exc (scale 10)
        0.748, 0.748, 0.04, //0.223,0.223,0.789; or 0.292,0.292,0.789
        // DGGC Inh
        0.33, 0.33, 0.33, 0.33, 0.33, 0.33, 0.33,// 0.33 or 0.544
        // DGMC Exc (scale 10)
        1.0, 1.0, //1.504, 1.504
        // DGMC Inh
        1.66, 1.66,
        // DGAAC Exc (scale 10)
        0.065, 0.065, 0.07, 0.06, //0.527, 0.527, 0.527, 0.527,
        // DGAAC Inh
        0.57, 0.57, 0.57, 0.57, 0.57, 0.57,
        // DGBC Exc (scale 10)
        0.5, 0.5, 0.52, 0.7,
        // DGBC Inh
        0.32, 0.32, 0.32, 0.32, 0.32, 0.32,
        // DGBCCCK Exc (scale 10)
        1.96, 1.96,
        // DGBCCCK Inh
        0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.4,
        // DGHICAP Exc (scale 10)
        1.81, 1.81, 1.78, 1.297,
        // DGHICAP Inh
        0.36, 0.36, 0.36, 0.36, 0.36, 0.36,
        // DGHIPP Exc (scale 10)
        1.6, 1.1,
        // DGHIPP Inh
        0.9,
        // DGMOPP Exc (scale 10)
        2.2, 2.2,
        // DGMOPP Inh
        0.9, 0.9, 0.9,
        // DGTML Exc (scale 10)
        2.6, 2.6,
        // DGTML Inh
        1.0, 1.0, 1.0, 1.0
    }//,
   */

};

// Define group sizes for each neuron type

const size_t numDGGCExc = 3;
const size_t numDGGCInh = 7;
const size_t numDGMCExc = 2;
const size_t numDGMCInh = 2;
const size_t numDGBCExc = 4;
const size_t numDGBCInh = 6;
const size_t numDGAACExc = 4;
const size_t numDGAACInh = 6;
const size_t numDGBCCCKExc = 2;
const size_t numDGBCCCKInh = 7;
const size_t numDGHICAPExc = 4;
const size_t numDGHICAPInh = 6;
const size_t numDGHIPPExc = 2;
const size_t numDGHIPPInh = 1;
const size_t numDGMOPPExc = 2;
const size_t numDGMOPPInh = 3;
const size_t numDGTMLExc = 2;
const size_t numDGTMLInh = 4;

//#endif // INITIAL_SIMPLEX_CA3_H
