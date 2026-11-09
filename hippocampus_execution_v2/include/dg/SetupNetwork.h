// Set up the simulator, groups, inputs, neuron parameters, synapses, and monitors.
// This header contains statements included inside main, sharing its local variables.
    // keep track of execution time
	Stopwatch watch;
	
	// ---------------- CONFIG STATE -------------------
	// initialize random seed
	int randSeed = 42; // Same random seed, whatever neuron number change
    
	// instantiate sim
	int numGPUs = 1;  // Patch Killian; up to 8 for CARLsim; try prefer partition, 0,1,2,3
	CARLsim sim("DG", GPU_MODE, USER, numGPUs, randSeed);
    
    // Set userconn
    sim.setUserConnectivity(map_bigcon);
	
	// instantiate neuron types
	int num_EC_LEC = IDrange_EC_LEC[1] - IDrange_EC_LEC[0] + 1;
	int num_EC_MEC = IDrange_EC_MEC[1] - IDrange_EC_MEC[0] + 1;
	int num_DG_GC = IDrange_DG_GC[1] - IDrange_DG_GC[0] + 1;
	int num_DG_MC = IDrange_DG_MC[1] - IDrange_DG_MC[0] + 1;
	int num_DG_BC = IDrange_DG_BC[1] - IDrange_DG_BC[0] + 1;
	int num_DG_AAC = IDrange_DG_AAC[1] - IDrange_DG_AAC[0] + 1;
	int num_DG_BCCCK = IDrange_DG_BCCCK[1] - IDrange_DG_BCCCK[0] + 1;
	int num_DG_HICAP = IDrange_DG_HICAP[1] - IDrange_DG_HICAP[0] + 1;
	int num_DG_HIPP = IDrange_DG_HIPP[1] - IDrange_DG_HIPP[0] + 1;
	int num_DG_MOPP = IDrange_DG_MOPP[1] - IDrange_DG_MOPP[0] + 1;
	int num_DG_TML = IDrange_DG_TML[1] - IDrange_DG_TML[0] + 1;

	int EC_LEC = sim.createSpikeGeneratorGroup("EC_LEC", num_EC_LEC, EXCITATORY_NEURON);
	int EC_MEC = sim.createSpikeGeneratorGroup("EC_MEC", num_EC_MEC, EXCITATORY_NEURON);
	int DG_GC = sim.createGroup("DG_GC", num_DG_GC, EXCITATORY_NEURON);
	int DG_MC = sim.createGroup("DG_MC", num_DG_MC, EXCITATORY_NEURON);
	int DG_BC = sim.createGroup("DG_BC", num_DG_BC, INHIBITORY_NEURON);
	int DG_AAC = sim.createGroup("DG_AAC", num_DG_AAC, INHIBITORY_NEURON);
	int DG_BCCCK = sim.createGroup("DG_BCCCK", num_DG_BCCCK, INHIBITORY_NEURON);
	int DG_HICAP = sim.createGroup("DG_HICAP", num_DG_HICAP, INHIBITORY_NEURON);
	int DG_HIPP = sim.createGroup("DG_HIPP", num_DG_HIPP, INHIBITORY_NEURON);
	int DG_MOPP = sim.createGroup("DG_MOPP", num_DG_MOPP, INHIBITORY_NEURON);
	int DG_TML = sim.createGroup("DG_TML", num_DG_TML, INHIBITORY_NEURON);
	
	std::cout << "Number of EC_MEC: " << num_EC_MEC << std::endl;//always 66000
    std::cout << "Number of EC_LEC: " << num_EC_LEC << std::endl;
	std::cout << "Number of DG_GC: " << num_DG_GC << std::endl;
	std::cout << "Number of DG_MC: " << num_DG_MC << std::endl;
	std::cout << "Number of DG_BC: " << num_DG_BC << std::endl;
	std::cout << "Number of DG_AAC: " << num_DG_AAC << std::endl;
	std::cout << "Number of DG_BCCCK: " << num_DG_BCCCK << std::endl;
    std::cout << "Number of DG_HICAP: " << num_DG_HICAP << std::endl;
    std::cout << "Number of DG_HIPP: " << num_DG_HIPP << std::endl;
    std::cout << "Number of DG_MOPP: " << num_DG_MOPP << std::endl;
    std::cout << "Number of DG_TML: " << num_DG_TML << std::endl;

	
	// Need to regenerate .dat file using 0-based index
    SpikeGeneratorFromFile SGF_MEC("results/MEC_66000cells_1200.0sec(mean=2.1Hz,ymax=2.4,60x60cm,non-uniform grid field,d*10,min=0.1Hz)_SimData_MCscale5.dat"); //non-unifrom grid field
    //SpikeGeneratorFromFile SGF_MEC("results/MEC_66000cells_1200.0sec(max=7.28Hz,scale500_Model.dat"); //scale 500 reduced model
    //SpikeGeneratorFromFile SGF_MEC("results/MEC_66000cells_1200.0sec(max=7.28Hz,scale100_Model.dat"); //scale 100 reduced model
    sim.setSpikeGenerator(EC_MEC, &SGF_MEC);

	//sim.setConductances(true);// COBA
	
    //sim.setConductances(DG_GC, 10.02, 0, 35.22, 24.83, 0, 229.93);// type1,ok(modify b,vth,k,d),EC-GC, 12ms HHW
	sim.setConductances(DG_GC, 40.91, 0, 105.032, 24.83, 0, 229.93);// type1,ok(modify b,vth,k,d),EC-GC, 33.5ms HHW - Gene
	//sim.setConductances(DG_GC, 1.1, 0, 15.07, 24.83, 0, 229.93);// type1,ok(modify b,vth,k,d),MC-GC
    //sim.setConductances(DG_GC, 37.72, 0, 97.818, 26.936, 0, 239.606);// type1,ok(Gene)(modify a,b)

    //sim.setConductances(DG_MC, 1.0, 0, 14.83, 18.58, 0, 201.177);// ok(GC-MC Exc old)
    sim.setConductances(DG_MC, 1.0, 0, 14.83, 8.63, 0, 155.43);// ok(GC-MC Exc modify)
    
    //sim.setConductances(DG_AAC, 3.962, 0, 21.525, 14.075, 0, 180.443);// modify,ok(EC-AAC)
    sim.setConductances(DG_AAC, 1.0, 0, 14.83, 14.075, 0, 180.443);// ok(EC/GC-AAC,Gene's simulation)
    //sim.setConductances(DG_AAC, 3.22, 0, 19.85, 14.075, 0, 180.443);// modify,ok(DGGC-AAC)
    //sim.setConductances(DG_AAC, 3.293, 0, 20.011, 14.075, 0, 180.443);// modify,ok(DGMC-AAC)
    
    //sim.setConductances(DG_BC, 9.32, 0, 53.03, 9.644, 0, 160.062);// ok(EC-BC)
    sim.setConductances(DG_BC, 1.0, 0, 14.83, 9.644, 0, 160.062);// ok(EC/GC-BC,Gene's simulation)
    //sim.setConductances(DG_BC, 7.13, 0, 53.03, 9.644, 0, 160.062);// ok(DGGC-BC)
    //sim.setConductances(DG_BC, 1.066, 0, 53.03, 9.644, 0, 160.062);// ok(DGMC-BC)

    //sim.setConductances(DG_BCCCK, 2.751, 0, 18.788, 13.11, 0, 176.02);// ok(EC-BCCCK)
    sim.setConductances(DG_BCCCK, 1.0, 0, 14.83, 13.11, 0, 176.02);// ok(EC-BCCCK,Gene's simulation)
    

    sim.setConductances(DG_HICAP, 1.593, 0, 16.168, 21.278, 0, 213.578);// ok(EC-HICAP,Gene's simulation)
    //sim.setConductances(DG_HICAP, 1.52, 0, 16.01, 21.278, 0, 213.578);// ok(DGGC-HICAP,Gene's simulation)
    //sim.setConductances(DG_HICAP, 5.3, 0, 24.54, 21.278, 0, 213.578);// ok(DGMC-HICAP,Gene's simulation)
    
    //sim.setConductances(DG_HIPP, 3.04, 0, 19.43, 6.411, 0, 145.191);// modify,ok(DGGC-HIPP)
    sim.setConductances(DG_HIPP, 1.0, 0, 14.83, 6.411, 0, 145.191);// modify,ok(DGGC-HIPP,Gene's simulation)
    //sim.setConductances(DG_HIPP, 1.0, 0, 14.83, 6.411, 0, 145.191);// modify,ok(DGMC-HIPP)
    
    //sim.setConductances(DG_MOPP, 2.055, 0, 17.214, 30.165, 0, 254.46);// modify,ok(EC-MOPP)
    sim.setConductances(DG_MOPP, 4.84, 0, 23.51, 30.165, 0, 254.46);// modify,ok(EC-MOPP,Gene's simulation)
    
    //sim.setConductances(DG_TML, 2.237, 0, 17.626, 10.586, 0, 164.396);//ok(EC-TML)
    sim.setConductances(DG_TML, 1.0, 0, 14.83, 10.576, 0, 164.352);//ok(EC-TML,Gene's simulation)
    

	// set-up network parameters(C,k,Vr,Vt,a,b,Vpeak,Vmin,d)
	
	sim.setNeuronParameters(DG_GC, 38.0, 0.0, 0.71, 0.0, -77.4, 0.0, -50.7, 0.0, 0.003, 0.0, 6.8, 0.0, 15.49, 0.0, -66.47, 0.0, 79.0, 0.0);//type1, modify b,vth,d,k,d
	//sim.setNeuronParameters(DG_GC, 38.0, 0.0, 0.45, 0.0, -77.4, 0.0, -44.9, 0.0, 0.003, 0.0, 24.48, 0.0, 15.49, 0.0, -66.47, 0.0, 50.0, 0.0);//type1 old
	//sim.setNeuronParameters(DG_GC, 38.0, 0.0, 0.45, 0.0, -77.4, 0.0, -44.9, 0.0, 0.001, 0.0, 10.0, 0.0, 15.49, 0.0, -66.47, 0.0, 50.0, 0.0);//type1, modify a=0.001,b=10
	
	sim.setNeuronParameters(DG_MC, 258.0, 0.0, 1.5, 0.0, -63.67, 0.0, -37.11, 0.0, 0.004, 0.0, -20.84, 0.0, 28.29, 0.0, -47.98, 0.0, 117.0, 0.0);//ok
	
	sim.setNeuronParameters(DG_AAC, 109.0, 0.0, 1.52, 0.0, -65.25, 0.0, -54.35, 0.0, 0.049, 0.0, 3.0, 0.0, 5.07, 0.0, -64.47, 0.0, -1.0, 0.0);// modify, eliminate after-hyperpolarization
	
	sim.setNeuronParameters(DG_BC, 208.0, 0.0, 0.81, 0.0, -61.02, 0.0, -45.87, 0.0, 0.097, 0.0, 1.89, 0.0, 14.08, 0.0, -36.23, 0.0, 553.0, 0.0);//DG BC (type1), modified vth match with literature
	//sim.setNeuronParameters(DG_BC, 208.0, 0.0, 0.81, 0.0, -61.02, 0.0, -37.84, 0.0, 0.097, 0.0, 1.89, 0.0, 14.08, 0.0, -36.23, 0.0, 553.0, 0.0);//works
	
	sim.setNeuronParameters(DG_BCCCK, 135.0, 0.0, 0.58, 0.0, -59.0, 0.0, -39.4, 0.0, 0.006, 0.0, -1.24, 0.0, 18.27, 0.0, -42.77, 0.0, 54.0, 0.0);// use CA3 BCCCK for DG BCCCK since there is no DG BCCCK Izhi parameter in Hippo.org
	
	sim.setNeuronParameters(DG_HICAP, 61.0, 0.0, 0.5, 0.0, -61.28, 0.0, -35.36, 0.0, 0.039, 0.0, -1.62, 0.0, 38.79, 0.0, -60.77, 0.0, 49.0, 0.0);
	
	
	sim.setNeuronParameters(DG_HIPP, 132.0, 0.0, 0.55, 0.0, -62.16, 0.0, -43.16, 0.0, 0.043, 0.0, -3.15, 0.0, 13.2, 0.0, -37.71, 0.0, 231.0, 0.0);// modified from DG BC (type2), also make Vth match
	//sim.setNeuronParameters(DG_HIPP, 208.0, 0.0, 0.81, 0.0, -61.02, 0.0, -42.02, 0.0, 0.097, 0.0, 1.89, 0.0, 14.08, 0.0, -36.23, 0.0, 553.0, 0.0);//DG BC (type1), modified vth match with literature
	
	sim.setNeuronParameters(DG_MOPP, 100.0, 0.0, 1.39, 0.0, -74.67, 0.0, -29.07, 0.0, 0.0018, 0.0, -37.42, 0.0, 17.03, 0.0, -47.0, 0.0, 110.0, 0.0);// modified, okay; vth=-74.67mV, dep to -57.8 works
	
	sim.setNeuronParameters(DG_TML, 236.0, 0.0, 0.92, 0.0, -54.91, 0.0, -41.69, 0.0, 0.001, 0.0, -3.12, 0.0, -11.61, 0.0, -48.73, 0.0, 8.0, 0.0);
	//sim.setNeuronParameters(DG_TML, 208.0, 0.0, 0.81, 0.0, -61.02, 0.0, -37.84, 0.0, 0.097, 0.0, 1.89, 0.0, 14.08, 0.0, -36.23, 0.0, 553.0, 0.0);//replace TML as BC
                                                
                                                
	// create an instance of MyConnection class and pass it to CARLsim::connect
	// only CCK- and HICAP- has 0.07 GABAb
	MyConnection* myConn = new MyConnection;
	short int LEC_DGGC = sim.connect(EC_LEC, DG_GC, myConn, 1.0, 0.11, SYN_FIXED);//0.38(young) or 0.11(mature)
	short int MEC_DGGC = sim.connect(EC_MEC, DG_GC, myConn, 1.0, 0.11, SYN_FIXED);//0.38(young) or 0.11(mature)
	short int DGMC_DGGC = sim.connect(DG_MC, DG_GC, myConn, 1.0, 0.11, SYN_FIXED);//0.38(young) or 0.11(mature)
	short int DGAAC_DGGC = sim.connect(DG_AAC, DG_GC, myConn, 1.0, 0.0, SYN_FIXED);
	short int DGBC_DGGC = sim.connect(DG_BC, DG_GC, myConn, 1.0, 0.0, SYN_FIXED);
	short int DGBCCCK_DGGC = sim.connect(DG_BCCCK, DG_GC, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.07 
	short int DGHICAP_DGGC = sim.connect(DG_HICAP, DG_GC, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.07 
	short int DGHIPP_DGGC = sim.connect(DG_HIPP, DG_GC, myConn, 1.0, 0.0, SYN_FIXED); 
	short int DGMOPP_DGGC = sim.connect(DG_MOPP, DG_GC, myConn, 1.0, 0.0, SYN_FIXED);
	short int DGTML_DGGC = sim.connect(DG_TML, DG_GC, myConn, 1.0, 0.0, SYN_FIXED);
	
	short int DGGC_DGMC = sim.connect(DG_GC, DG_MC, myConn, 1.0, 0.11, SYN_FIXED);//0.38(young) or 0.11(mature)
	short int DGMC_DGMC = sim.connect(DG_MC, DG_MC, myConn, 1.0, 0.11, SYN_FIXED);//0.38(young) or 0.11(mature)
	short int DGAAC_DGMC = sim.connect(DG_AAC, DG_MC, myConn, 1.0, 0.0, SYN_FIXED);
	short int DGTML_DGMC = sim.connect(DG_TML, DG_MC, myConn, 1.0, 0.0, SYN_FIXED);
	
	short int LEC_DGAAC = sim.connect(EC_LEC, DG_AAC, myConn, 1.0, 0.39, SYN_FIXED);//DGGC-DGBC conductance
	short int MEC_DGAAC = sim.connect(EC_MEC, DG_AAC, myConn, 1.0, 0.39, SYN_FIXED);//DGGC-DGBC conductance
	short int DGGC_DGAAC = sim.connect(DG_GC, DG_AAC, myConn, 1.0, 0.39, SYN_FIXED);//DGGC-DGBC conductance
	short int DGMC_DGAAC = sim.connect(DG_MC, DG_AAC, myConn, 1.0, 0.39, SYN_FIXED);//DGGC-DGBC conductance
	short int DGBC_DGAAC = sim.connect(DG_BC, DG_AAC, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.0
	short int DGBCCCK_DGAAC = sim.connect(DG_BCCCK, DG_AAC, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.07 
	short int DGHICAP_DGAAC = sim.connect(DG_HICAP, DG_AAC, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.07 
	short int DGHIPP_DGAAC = sim.connect(DG_HIPP, DG_AAC, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.0 
	short int DGMOPP_DGAAC = sim.connect(DG_MOPP, DG_AAC, myConn, 1.0, 0.0, SYN_FIXED);
	short int DGTML_DGAAC = sim.connect(DG_TML, DG_AAC, myConn, 1.0, 0.0, SYN_FIXED);

	
	short int LEC_DGBC = sim.connect(EC_LEC, DG_BC, myConn, 1.0, 0.39, SYN_FIXED);//DGGC-DGBC conductance
	short int MEC_DGBC = sim.connect(EC_MEC, DG_BC, myConn, 1.0, 0.39, SYN_FIXED);//DGGC-DGBC conductance
	short int DGMC_DGBC = sim.connect(DG_MC, DG_BC, myConn, 1.0, 0.39, SYN_FIXED);//DGGC-DGBC conductance
	short int DGGC_DGBC = sim.connect(DG_GC, DG_BC, myConn, 1.0, 0.39, SYN_FIXED);//DGGC-DGBC conductance
	short int DGBC_DGBC = sim.connect(DG_BC, DG_BC, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.07 
	short int DGBCCCK_DGBC = sim.connect(DG_BCCCK, DG_BC, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.07 
	short int DGHICAP_DGBC = sim.connect(DG_HICAP, DG_BC, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.07 
	short int DGHIPP_DGBC = sim.connect(DG_HIPP, DG_BC, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.0 
	short int DGMOPP_DGBC = sim.connect(DG_MOPP, DG_BC, myConn, 1.0, 0.0, SYN_FIXED);
	short int DGTML_DGBC = sim.connect(DG_TML, DG_BC, myConn, 1.0, 0.0, SYN_FIXED);
	
	
	short int LEC_DGBCCCK = sim.connect(EC_LEC, DG_BCCCK, myConn, 1.0, 0.39, SYN_FIXED);//DGGC-DGBC conductance
	short int MEC_DGBCCCK = sim.connect(EC_MEC, DG_BCCCK, myConn, 1.0, 0.39, SYN_FIXED);//DGGC-DGBC conductance
	////short int DGGC_DGBCCCK = sim.connect(DG_GC, DG_BCCCK, myConn, 1.0, 0.39, SYN_FIXED);//check!!
	short int DGAAC_DGBCCCK = sim.connect(DG_AAC, DG_BCCCK, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.0 
	short int DGBC_DGBCCCK = sim.connect(DG_BC, DG_BCCCK, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.0
	short int DGBCCCK_DGBCCCK = sim.connect(DG_BCCCK, DG_BCCCK, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.07 
	short int DGHICAP_DGBCCCK = sim.connect(DG_HICAP, DG_BCCCK, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.07 
	short int DGHIPP_DGBCCCK = sim.connect(DG_HIPP, DG_BCCCK, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.0 
	short int DGMOPP_DGBCCCK = sim.connect(DG_MOPP, DG_BCCCK, myConn, 1.0, 0.0, SYN_FIXED);
	short int DGTML_DGBCCCK = sim.connect(DG_TML, DG_BCCCK, myConn, 1.0, 0.0, SYN_FIXED);
	
	short int LEC_DGHICAP = sim.connect(EC_LEC, DG_HICAP, myConn, 1.0, 0.39, SYN_FIXED);//DGGC-DGBC conductance
	short int MEC_DGHICAP = sim.connect(EC_MEC, DG_HICAP, myConn, 1.0, 0.39, SYN_FIXED);//DGGC-DGBC conductance
	short int DGGC_DGHICAP = sim.connect(DG_GC, DG_HICAP, myConn, 1.0, 0.39, SYN_FIXED);//DGGC-DGBC conductance
	short int DGMC_DGHICAP = sim.connect(DG_MC, DG_HICAP, myConn, 1.0, 0.39, SYN_FIXED);//DGGC-DGBC conductance
	short int DGBC_DGHICAP = sim.connect(DG_BC, DG_HICAP, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.0
	short int DGBCCCK_DGHICAP = sim.connect(DG_BCCCK, DG_HICAP, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.07 
	short int DGHICAP_DGHICAP = sim.connect(DG_HICAP, DG_HICAP, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.07 
	short int DGHIPP_DGHICAP = sim.connect(DG_HIPP, DG_HICAP, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.0 
	short int DGMOPP_DGHICAP = sim.connect(DG_MOPP, DG_HICAP, myConn, 1.0, 0.0, SYN_FIXED);
	short int DGTML_DGHICAP = sim.connect(DG_TML, DG_HICAP, myConn, 1.0, 0.0, SYN_FIXED);
	
	short int DGGC_DGHIPP = sim.connect(DG_GC, DG_HIPP, myConn, 1.0, 0.39, SYN_FIXED);//DGGC-DGBC conductance
	short int DGMC_DGHIPP = sim.connect(DG_MC, DG_HIPP, myConn, 1.0, 0.39, SYN_FIXED);//DGGC-DGBC conductance
	short int DGTML_DGHIPP = sim.connect(DG_TML, DG_HIPP, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.0
	
	short int LEC_DGMOPP = sim.connect(EC_LEC, DG_MOPP, myConn, 1.0, 0.39, SYN_FIXED);//DGGC-DGBC conductance
	short int MEC_DGMOPP = sim.connect(EC_MEC, DG_MOPP, myConn, 1.0, 0.39, SYN_FIXED);//DGGC-DGBC conductance
	short int DGHIPP_DGMOPP = sim.connect(DG_HIPP, DG_MOPP, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.0
	short int DGMOPP_DGMOPP = sim.connect(DG_MOPP, DG_MOPP, myConn, 1.0, 0.0, SYN_FIXED);
	short int DGTML_DGMOPP = sim.connect(DG_TML, DG_MOPP, myConn, 1.0, 0.0, SYN_FIXED);
	
	short int LEC_DGTML = sim.connect(EC_LEC, DG_TML, myConn, 1.0, 0.39, SYN_FIXED);//DGGC-DGBC conductance
	short int MEC_DGTML = sim.connect(EC_MEC, DG_TML, myConn, 1.0, 0.39, SYN_FIXED);//DGGC-DGBC conductance
	short int DGHICAP_DGTML = sim.connect(DG_HICAP, DG_TML, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.07 
	short int DGHIPP_DGTML = sim.connect(DG_HIPP, DG_TML, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.0 
	short int DGMOPP_DGTML = sim.connect(DG_MOPP, DG_TML, myConn, 1.0, 0.0, SYN_FIXED);
	short int DGTML_DGTML = sim.connect(DG_TML, DG_TML, myConn, 1.0, 0.0, SYN_FIXED);
    
    sim.setIntegrationMethod(RUNGE_KUTTA4, 10); 
    
	// ---------------- SETUP STATE -------------------	
	watch.lap("setupNetwork");
	
	// build the network
	sim.setupNetwork();
	
	
	//setup baseline input
	
	PoissonRate poissRate_EC_LEC(num_EC_LEC, true);
	poissRate_EC_LEC.setRates(2.1f);
	sim.setSpikeRate(EC_LEC, &poissRate_EC_LEC);
	
	/*
	PoissonRate poissRate_EC_MEC(num_EC_MEC, true);
	poissRate_EC_MEC.setRates(2.1f);
	sim.setSpikeRate(EC_MEC, &poissRate_EC_MEC);
	*/
	
	sim.setSpikeMonitor(EC_MEC, "DEFAULT");
	sim.setSpikeMonitor(EC_LEC, "DEFAULT");
	sim.setSpikeMonitor(DG_GC, "DEFAULT");
	sim.setSpikeMonitor(DG_MC, "DEFAULT");
	sim.setSpikeMonitor(DG_BC, "DEFAULT");
	sim.setSpikeMonitor(DG_AAC, "DEFAULT");
	sim.setSpikeMonitor(DG_BCCCK, "DEFAULT");
	sim.setSpikeMonitor(DG_HICAP, "DEFAULT");
	sim.setSpikeMonitor(DG_HIPP, "DEFAULT");
	sim.setSpikeMonitor(DG_MOPP, "DEFAULT");
	sim.setSpikeMonitor(DG_TML, "DEFAULT");
	
