#include "hippomodel/region/DG/DGOptimizationBounds.h"

namespace hippomodel::DG {

OptimizationBounds makeDGOptimizationBounds(const std::vector<double>& initGuess,
                                            double lowerScale,
                                            double upperScale) {
    // This function preserves the original DG NM per-connection scaling-factor bounds.
    // The variable names and grouping follow main_largescalemodel_EC_DG_div(NMOpt).cpp.

    // ----------------------------------------------------------
    // EC_LEC as PRE (7)  baselineWts[0..6]
    // ----------------------------------------------------------
    double lowerLECGC     = lowerScale * initGuess[0];  double upperLECGC     = 3.17 / 0.204;// maxWt = 3.18, set 3.17
    double lowerLECAAC    = lowerScale * initGuess[1];  double upperLECAAC    = 16 / 0.097;// maxWt = 17, set 16
    double lowerLECBC     = lowerScale * initGuess[2];  double upperLECBC     = 38 / 0.17;// maxWt = 39, set 38
    double lowerLECCCK    = lowerScale * initGuess[3];  double upperLECCCK    = 30 / 0.1198;// maxWt = 31; set 30
    double lowerLECHICAP  = lowerScale * initGuess[4];  double upperLECHICAP  = 16 / 0.0451;// maxWt = 17; set 16
    double lowerLECMOPP   = lowerScale * initGuess[5];  double upperLECMOPP   = 36 / 0.4;// maxWt = 37; set 36
    double lowerLECTML    = lowerScale * initGuess[6];  double upperLECTML    = 33 / 0.21; // maxWt = 34; set 33

    // ----------------------------------------------------------
    // EC_MEC as PRE (7)  baselineWts[7..13]
    // ----------------------------------------------------------
    double lowerMECGC     = lowerScale * initGuess[7];   double upperMECGC     = 3.17 / 0.204;// maxWt = 3.18, set 3.17
    double lowerMECAAC    = lowerScale * initGuess[8];   double upperMECAAC    = 16 / 0.097;// maxWt = 17, set 16
    double lowerMECBC     = lowerScale * initGuess[9];   double upperMECBC     = 38 / 0.17;// maxWt = 39, set 38
    double lowerMECCCK    = lowerScale * initGuess[10];  double upperMECCCK    = 30 / 0.1198;// maxWt = 31; set 30
    double lowerMECHICAP  = lowerScale * initGuess[11];  double upperMECHICAP  = 16 / 0.0451;// maxWt = 17; set 16
    double lowerMECMOPP   = lowerScale * initGuess[12];  double upperMECMOPP   = 36 / 0.4;// maxWt = 37; set 36
    double lowerMECTML    = lowerScale * initGuess[13];  double upperMECTML    = 33 / 0.21; // maxWt = 34; set 33

    // ----------------------------------------------------------
    // DG_GC as PRE (5)  baselineWts[14..18]
    // ----------------------------------------------------------
    double lowerGCMC      = lowerScale * initGuess[14];  double upperGCMC      = 120 / 0.932;// maxWt = 121, set 120
    double lowerGCAAC     = lowerScale * initGuess[15];  double upperGCAAC     = 16 / 0.377;// maxWt = 17, set 16
    double lowerGCBC      = lowerScale * initGuess[16];  double upperGCBC      = 38 / 0.67;// maxWt = 39, set 38
    double lowerGCHICAP   = lowerScale * initGuess[17];  double upperGCHICAP   = 16 / 0.1824;// maxWt = 17; set 16
    double lowerGCHIPP    = lowerScale * initGuess[18];  double upperGCHIPP    = 22 / 0.4328;//maxWt = 24; set 22; GC-HIPP should smaller

    // ----------------------------------------------------------
    // DG_MC as PRE (6)  baselineWts[19..24], use smaller upperbound (1.5 or 1.0) for low corr; higher upperbound (3.5) for high corr
    // ----------------------------------------------------------
    double lowerMCGC      = lowerScale * initGuess[19];  double upperMCGC      = 1.5 * initGuess[19];
    double lowerMCMC      = lowerScale * initGuess[20];  double upperMCMC      = 1.5 * initGuess[20];
    double lowerMCAAC     = lowerScale * initGuess[21];  double upperMCAAC     = 1.5 * initGuess[21];
    double lowerMCBC      = lowerScale * initGuess[22];  double upperMCBC      = 1.5 * initGuess[22];
    double lowerMCHICAP   = lowerScale * initGuess[23];  double upperMCHICAP   = 1.5 * initGuess[23];
    double lowerMCHIPP    = lowerScale * initGuess[24];  double upperMCHIPP    = 1.5 * initGuess[24];

    // ----------------------------------------------------------
    // DG_AAC as PRE (3)  baselineWts[25..27]
    // ----------------------------------------------------------
    double lowerAACGC     = lowerScale * initGuess[25];  double upperAACGC     = upperScale * initGuess[25];
    double lowerAACMC     = lowerScale * initGuess[26];  double upperAACMC     = upperScale * initGuess[26];
    double lowerAACCCK    = lowerScale * initGuess[27];  double upperAACCCK    = upperScale * initGuess[27];

    // ----------------------------------------------------------
    // DG_BC as PRE (5)  baselineWts[28..32]
    // ----------------------------------------------------------
    double lowerBCGC      = lowerScale * initGuess[28];  double upperBCGC      = upperScale * initGuess[28];
    double lowerBCAAC     = lowerScale * initGuess[29];  double upperBCAAC     = upperScale * initGuess[29];
    double lowerBCBC      = lowerScale * initGuess[30];  double upperBCBC      = upperScale * initGuess[30];
    double lowerBCCCK     = lowerScale * initGuess[31];  double upperBCCCK     = upperScale * initGuess[31];
    double lowerBCHICAP   = lowerScale * initGuess[32];  double upperBCHICAP   = upperScale * initGuess[32];

    // ----------------------------------------------------------
    // DG_BCCCK as PRE (5)  baselineWts[33..37]
    // ----------------------------------------------------------
    double lowerCCKGC     = lowerScale * initGuess[33];  double upperCCKGC     = upperScale * initGuess[33];
    double lowerCCKAAC    = lowerScale * initGuess[34];  double upperCCKAAC    = upperScale * initGuess[34];
    double lowerCCKBC     = lowerScale * initGuess[35];  double upperCCKBC     = upperScale * initGuess[35];
    double lowerCCKCCK    = lowerScale * initGuess[36];  double upperCCKCCK    = upperScale * initGuess[36];
    double lowerCCKHICAP  = lowerScale * initGuess[37];  double upperCCKHICAP  = upperScale * initGuess[37];

    // ----------------------------------------------------------
    // DG_HICAP as PRE (6)  baselineWts[38..43]
    // ----------------------------------------------------------
    double lowerHICAPGC     = lowerScale * initGuess[38];  double upperHICAPGC     = upperScale * initGuess[38];
    double lowerHICAPAAC    = lowerScale * initGuess[39];  double upperHICAPAAC    = upperScale * initGuess[39];
    double lowerHICAPBC     = lowerScale * initGuess[40];  double upperHICAPBC     = upperScale * initGuess[40];
    double lowerHICAPCCK    = lowerScale * initGuess[41];  double upperHICAPCCK    = upperScale * initGuess[41];
    double lowerHICAPHICAP  = lowerScale * initGuess[42];  double upperHICAPHICAP  = upperScale * initGuess[42];
    double lowerHICAPTML    = lowerScale * initGuess[43];  double upperHICAPTML    = upperScale * initGuess[43];

    // ----------------------------------------------------------
    // DG_HIPP as PRE (7)  baselineWts[44..50]
    // ----------------------------------------------------------
    double lowerHIPPGC     = lowerScale * initGuess[44];  double upperHIPPGC     = upperScale * initGuess[44];
    double lowerHIPPAAC    = lowerScale * initGuess[45];  double upperHIPPAAC    = upperScale * initGuess[45];
    double lowerHIPPBC     = lowerScale * initGuess[46];  double upperHIPPBC     = upperScale * initGuess[46];
    double lowerHIPPCCK    = lowerScale * initGuess[47];  double upperHIPPCCK    = upperScale * initGuess[47];
    double lowerHIPPHICAP  = lowerScale * initGuess[48];  double upperHIPPHICAP  = upperScale * initGuess[48];
    double lowerHIPPMOPP   = lowerScale * initGuess[49];  double upperHIPPMOPP   = upperScale * initGuess[49];
    double lowerHIPPTML    = lowerScale * initGuess[50];  double upperHIPPTML    = upperScale * initGuess[50];

    // ----------------------------------------------------------
    // DG_MOPP as PRE (7)  baselineWts[51..57]
    // ----------------------------------------------------------
    double lowerMOPPGC     = lowerScale * initGuess[51];  double upperMOPPGC     = upperScale * initGuess[51];
    double lowerMOPPAAC    = lowerScale * initGuess[52];  double upperMOPPAAC    = upperScale * initGuess[52];
    double lowerMOPPBC     = lowerScale * initGuess[53];  double upperMOPPBC     = upperScale * initGuess[53];
    double lowerMOPPCCK    = lowerScale * initGuess[54];  double upperMOPPCCK    = upperScale * initGuess[54];
    double lowerMOPPHICAP  = lowerScale * initGuess[55];  double upperMOPPHICAP  = upperScale * initGuess[55];
    double lowerMOPPMOPP   = lowerScale * initGuess[56];  double upperMOPPMOPP   = upperScale * initGuess[56];
    double lowerMOPPTML    = lowerScale * initGuess[57];  double upperMOPPTML    = upperScale * initGuess[57];

    // ----------------------------------------------------------
    // DG_TML as PRE (9)  baselineWts[58..66]
    // ----------------------------------------------------------
    double lowerTMLGC     = lowerScale * initGuess[58];  double upperTMLGC     = upperScale * initGuess[58];
    double lowerTMLMC     = lowerScale * initGuess[59];  double upperTMLMC     = upperScale * initGuess[59];
    double lowerTMLAAC    = lowerScale * initGuess[60];  double upperTMLAAC    = upperScale * initGuess[60];
    double lowerTMLBC     = lowerScale * initGuess[61];  double upperTMLBC     = upperScale * initGuess[61];
    double lowerTMLCCK    = lowerScale * initGuess[62];  double upperTMLCCK    = upperScale * initGuess[62];
    double lowerTMLHICAP  = lowerScale * initGuess[63];  double upperTMLHICAP  = upperScale * initGuess[63];
    double lowerTMLHIPP   = lowerScale * initGuess[64];  double upperTMLHIPP   = upperScale * initGuess[64];
    double lowerTMLMOPP   = lowerScale * initGuess[65];  double upperTMLMOPP   = upperScale * initGuess[65];
    double lowerTMLTML    = lowerScale * initGuess[66];  double upperTMLTML    = upperScale * initGuess[66];

    OptimizationBounds bounds;
    bounds.lower = {
        // EC_LEC as PRE (7)
        lowerLECGC, lowerLECAAC, lowerLECBC, lowerLECCCK, lowerLECHICAP, lowerLECMOPP, lowerLECTML,
        // EC_MEC as PRE (7)
        lowerMECGC, lowerMECAAC, lowerMECBC, lowerMECCCK, lowerMECHICAP, lowerMECMOPP, lowerMECTML,
        // DG_GC as PRE (5)
        lowerGCMC, lowerGCAAC, lowerGCBC, lowerGCHICAP, lowerGCHIPP,
        // DG_MC as PRE (6)
        lowerMCGC, lowerMCMC, lowerMCAAC, lowerMCBC, lowerMCHICAP, lowerMCHIPP,
        // DG_AAC as PRE (3)
        lowerAACGC, lowerAACMC, lowerAACCCK,
        // DG_BC as PRE (5)
        lowerBCGC, lowerBCAAC, lowerBCBC, lowerBCCCK, lowerBCHICAP,
        // DG_BCCCK as PRE (5)
        lowerCCKGC, lowerCCKAAC, lowerCCKBC, lowerCCKCCK, lowerCCKHICAP,
        // DG_HICAP as PRE (6)
        lowerHICAPGC, lowerHICAPAAC, lowerHICAPBC, lowerHICAPCCK, lowerHICAPHICAP, lowerHICAPTML,
        // DG_HIPP as PRE (7)
        lowerHIPPGC, lowerHIPPAAC, lowerHIPPBC, lowerHIPPCCK, lowerHIPPHICAP, lowerHIPPMOPP, lowerHIPPTML,
        // DG_MOPP as PRE (7)
        lowerMOPPGC, lowerMOPPAAC, lowerMOPPBC, lowerMOPPCCK, lowerMOPPHICAP, lowerMOPPMOPP, lowerMOPPTML,
        // DG_TML as PRE (9)
        lowerTMLGC, lowerTMLMC, lowerTMLAAC, lowerTMLBC, lowerTMLCCK, lowerTMLHICAP, lowerTMLHIPP, lowerTMLMOPP, lowerTMLTML
    };

    bounds.upper = {
        // EC_LEC as PRE (7)
        upperLECGC, upperLECAAC, upperLECBC, upperLECCCK, upperLECHICAP, upperLECMOPP, upperLECTML,
        // EC_MEC as PRE (7)
        upperMECGC, upperMECAAC, upperMECBC, upperMECCCK, upperMECHICAP, upperMECMOPP, upperMECTML,
        // DG_GC as PRE (5)
        upperGCMC, upperGCAAC, upperGCBC, upperGCHICAP, upperGCHIPP,
        // DG_MC as PRE (6)
        upperMCGC, upperMCMC, upperMCAAC, upperMCBC, upperMCHICAP, upperMCHIPP,
        // DG_AAC as PRE (3)
        upperAACGC, upperAACMC, upperAACCCK,
        // DG_BC as PRE (5)
        upperBCGC, upperBCAAC, upperBCBC, upperBCCCK, upperBCHICAP,
        // DG_BCCCK as PRE (5)
        upperCCKGC, upperCCKAAC, upperCCKBC, upperCCKCCK, upperCCKHICAP,
        // DG_HICAP as PRE (6)
        upperHICAPGC, upperHICAPAAC, upperHICAPBC, upperHICAPCCK, upperHICAPHICAP, upperHICAPTML,
        // DG_HIPP as PRE (7)
        upperHIPPGC, upperHIPPAAC, upperHIPPBC, upperHIPPCCK, upperHIPPHICAP, upperHIPPMOPP, upperHIPPTML,
        // DG_MOPP as PRE (7)
        upperMOPPGC, upperMOPPAAC, upperMOPPBC, upperMOPPCCK, upperMOPPHICAP, upperMOPPMOPP, upperMOPPTML,
        // DG_TML as PRE (9)
        upperTMLGC, upperTMLMC, upperTMLAAC, upperTMLBC, upperTMLCCK, upperTMLHICAP, upperTMLHIPP, upperTMLMOPP, upperTMLTML
    };

    return bounds;
}

}  // namespace hippomodel::DG
