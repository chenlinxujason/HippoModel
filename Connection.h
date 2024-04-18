connectionIDs["DGGC_DGBC"] = sim.connect(DG_GC, DG_BC, "random", RangeWeight(baselineWts[0]), 0.003460f, RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.0f, 0.0f);//wt = 1.064 - 3.693
    connectionIDs["DGBC_DGGC"] = sim.connect(DG_BC, DG_GC, "random", RangeWeight(baselineWts[1]), 0.005f, RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.0f, 0.0f);// wt = 1.38 - 4.361
    connectionIDs["MEC_DGGC"] = sim.connect(EC_MEC, DG_GC, "random", RangeWeight(baselineWts[2]), 0.002f, RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.0f, 0.0f);//wt = 1.112 - 4.179
    connectionIDs["LEC_DGGC"] = sim.connect(EC_LEC, DG_GC, "random", RangeWeight(baselineWts[3]), 0.002f, RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.0f, 0.0f);// wt = 1.112 - 4.179 (LEC-DGGC not available at Hippocampome.org)
    connectionIDs["MEC_DGBC"] = sim.connect(EC_MEC, DG_BC, "random", RangeWeight(baselineWts[4]), 0.002f, RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.0f, 0.0f);// wt = 0.992 - 3.481
    connectionIDs["LEC_DGBC"] = sim.connect(EC_LEC, DG_BC, "random", RangeWeight(baselineWts[5]), 0.002f, RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.0f, 0.0f);// wt = 0.992 - 3.481 (LEC-DGGC not available at Hippocampome.org)
