// Set up the simulator, groups, inputs, neuron parameters, synapses, and monitors.
// This header contains statements included inside main, sharing its local variables.
    // keep track of execution time
	Stopwatch watch;
	
	// ---------------- CONFIG STATE -------------------
	// initialize random seed
	int randSeed = 42;
    
	// instantiate sim
	int numGPUs = 1;  // Patch Killian
	CARLsim sim("CA3", GPU_MODE, USER, numGPUs, randSeed);
	
	sim.setUserConnectivity(map_bigcon);
	
	// instantiate neuron types
	int num_EC_LEC = IDrange_EC_LEC[1] - IDrange_EC_LEC[0] + 1;
	int num_EC_MEC = IDrange_EC_MEC[1] - IDrange_EC_MEC[0] + 1;
	int num_DG_GC = IDrange_DG_GC[1] - IDrange_DG_GC[0] + 1;
	int num_CA3_PC = IDrange_CA3_PC[1] - IDrange_CA3_PC[0] + 1;
	int num_CA3_AAC = IDrange_CA3_AAC[1] - IDrange_CA3_AAC[0] + 1;
	int num_CA3_BC = IDrange_CA3_BC[1] - IDrange_CA3_BC[0] + 1;
	int num_CA3_BCCCK = IDrange_CA3_BCCCK[1] - IDrange_CA3_BCCCK[0] + 1;
	int num_CA3_BisC = IDrange_CA3_BisC[1] - IDrange_CA3_BisC[0] + 1;
	int num_CA3_MFA = IDrange_CA3_MFA[1] - IDrange_CA3_MFA[0] + 1;
	int num_CA3_OLM = IDrange_CA3_OLM[1] - IDrange_CA3_OLM[0] + 1;
	int num_CA3_TL = IDrange_CA3_TL[1] - IDrange_CA3_TL[0] + 1;
	
	
	// MEC cells as Poisson processes, DG_CG cells as activity from file, CA3 cells as Izhikevich neuron
	int EC_LEC = sim.createSpikeGeneratorGroup("EC_LEC", num_EC_LEC, EXCITATORY_NEURON);
	int EC_MEC = sim.createSpikeGeneratorGroup("EC_MEC", num_EC_MEC, EXCITATORY_NEURON);
	int DG_GC = sim.createSpikeGeneratorGroup("DG_GC", num_DG_GC, EXCITATORY_NEURON);
		
	int CA3_PC = sim.createGroup("CA3_PC", num_CA3_PC, EXCITATORY_NEURON);
	int CA3_AAC = sim.createGroup("CA3_AAC", num_CA3_AAC, INHIBITORY_NEURON);
	int CA3_BC = sim.createGroup("CA3_BC", num_CA3_BC, INHIBITORY_NEURON);
	int CA3_BCCCK = sim.createGroup("CA3_BCCCK", num_CA3_BCCCK, INHIBITORY_NEURON);
	int CA3_BisC = sim.createGroup("CA3_BisC", num_CA3_BisC, INHIBITORY_NEURON);
	int CA3_MFA = sim.createGroup("CA3_MFA", num_CA3_MFA, INHIBITORY_NEURON);
	int CA3_OLM = sim.createGroup("CA3_OLM", num_CA3_OLM, INHIBITORY_NEURON);
	int CA3_TL = sim.createGroup("CA3_TL", num_CA3_TL, INHIBITORY_NEURON);
	

    std::cout << "Number of EC_MEC: " << num_EC_MEC << std::endl;//always 66000
	std::cout << "Number of EC_LEC: " << num_EC_LEC << std::endl;
	std::cout << "Number of DG_GC: " << num_DG_GC << std::endl;
	std::cout << "Number of CA3_PC: " << num_CA3_PC << std::endl;
	std::cout << "Number of CA3_AAC: " << num_CA3_AAC << std::endl;
	std::cout << "Number of CA3_BC: " << num_CA3_BC << std::endl;
    std::cout << "Number of CA3_BCCCK: " << num_CA3_BCCCK << std::endl;
    std::cout << "Number of CA3_Bistratified: " << num_CA3_BisC << std::endl;
    std::cout << "Number of CA3_MFA: " << num_CA3_MFA << std::endl;
    std::cout << "Number of CA3_OLM: " << num_CA3_OLM << std::endl;  
    std::cout << "Number of CA3_TL: "<< num_CA3_TL << std::endl;

    std::cout << "Number of IDs classified as CA3PC a: " << IDs_a.size()  << std::endl;
    std::cout << "Number of IDs classified as CA3PC b: " << IDs_b.size()  << std::endl;
    std::cout << "Number of IDs classified as CA3PC c: " << IDs_c.size() << std::endl;
	
	// Create spike gen from file
	
	SpikeGeneratorFromFile SGF_DGGC("results/spk_DG_GC.dat");
	sim.setSpikeGenerator(DG_GC, &SGF_DGGC);
	
	SpikeGeneratorFromFile SGF_MEC("results/spk_EC_MEC.dat");
	sim.setSpikeGenerator(EC_MEC, &SGF_MEC);
	
	SpikeGeneratorFromFile SGF_LEC("results/spk_EC_LEC.dat");
	sim.setSpikeGenerator(EC_LEC, &SGF_LEC);
	
	
	//-----------------------------------------------------------------------------------------------------
	// Set conductance in group level (use the one has largest num AvgPresynapse to replace)
	//-----------------------------------------------------------------------------------------------------
	
	//sim.setConductances(true);// COBA, CARLsim default tao must be greater than 1, and tao_slow > tao_fast
	
    sim.setConductances(CA3_PC, 21.543, 0, 29.122, 4.6, 0, 136.84); //wfa,type2, ok(CA3PC-CA3PC)

    sim.setConductances(CA3_AAC, 7.62, 0, 29.78, 25.57, 0, 233.33); //modify,ok(CA3PC-CA3AAC) 

    sim.setConductances(CA3_BC, 10.06, 0, 35.3, 33.3, 0, 268.89); //ok(CA3PC-CA3BC)
    
    sim.setConductances(CA3_BCCCK, 1.0, 0, 14.83, 28.49, 0, 246.76); //ok(CA3PC-CA3BCCCK,but can't constraint CA3PC-CA3BCCCK)

    sim.setConductances(CA3_BisC, 3.85, 0, 21.28, 1.0, 0, 120.3); //modify,ok(CA3PC-CA3BisC)
    
    sim.setConductances(CA3_MFA, 1.0, 0, 14.83, 26.516, 0, 237.675); //ok(CA3PC-CA3MFA, but can't constraint CA3PC-CA3MFA)

    sim.setConductances(CA3_OLM, 44.62, 0, 113.4, 55.42, 0, 370.65); //ok(CA3PC-CA3OLM)
   
    sim.setConductances(CA3_TL, 16.879, 0, 50.717, 1.0, 0, 120.3); //modified CA1TL(type2),ok(CA3PC-CA3TL)\
    
    
    //sim.setConductances(CA3_PC, 29.3, 0, 34.082, 7.347, 0, 149.498); //wfa:type1, ok(EC-CA3PC)
	//sim.setConductances(CA3_PC, 94.97, 0, 227.21, 7.347, 0, 149.498); //wfa:type1, ok(DGGC-CA3PC)
	//sim.setConductances(CA3_PC, 24.058, 0, 31.065, 7.347, 0, 149.498); //wfa:type1, ok(CA3PC-CA3PC)
	
	
	//sim.setConductances(CA3_PC, 71.677, 0, 116.18, 42.718, 0, 312.203); //burst:type4, ok(EC-CA3PC)
    //sim.setConductances(CA3_PC, 3900.0, 0, 7922.0, 42.718, 0, 312.203);  //burst:type4, ok(DGGC-CA3PC)
	//sim.setConductances(CA3_PC, 61.585, 0, 107.46, 42.718, 0, 312.203);  //burst:type4, ok(CA3PC-CA3PC)

	
	//-----------------------------------------------------------------------------------------------------
    // set-up network parameters(C,k,Vr,Vt,a,b,Vpeak,Vmin,d)
    //-----------------------------------------------------------------------------------------------------
  
    sim.setNeuronParameters(CA3_PC, 297.0, 0.0, 0.54, 0.0, -60.53, 0.0, -39.23, 0.0, 0.004, 0.0, 5.21, 0.0, 38.02, 0.0, -36.52, 0.0, 48.0, 0.0);//wfa: type2,ASP, modify vth=-39.23
        
	sim.setNeuronParameters(CA3_BC, 45.0, 0.0, 1.0, 0.0, -57.51, 0.0, -23.38, 0.0, 0.004, 0.0, 9.26, 0.0, 18.45, 0.0, -47.56, 0.0, -6.0, 0.0);
	
	sim.setNeuronParameters(CA3_AAC, 165.0, 0.0, 3.96, 0.0, -57.1, 0.0, -44.5, 0.0, 0.005, 0.0, 8.68, 0.0, 27.8, 0.0, -73.97, 0.0, 15.0, 0.0);// modify Vt from -51.72 to -44.5
	
	sim.setNeuronParameters(CA3_BCCCK, 135.0, 0.0, 0.58, 0.0, -59.0, 0.0, -39.4, 0.0, 0.006, 0.0, -1.24, 0.0, 18.27, 0.0, -42.77, 0.0, 54.0, 0.0);// CA3 BCCCK
	
	sim.setNeuronParameters(CA3_BisC, 112.0, 0.0, 1.2, 0.0, -64.67, 0.0, -47.67, 0.0, 0.008,0.0, 16.4, 0.0, 3.83, 0.0, -50.2, 0.0, 19.0, 0.0);// CA3 BisC, use modified CA1 BisC(type1),Vth,Vpeak and patterns correct
	
	sim.setNeuronParameters(CA3_MFA, 185.0, 0.0, 0.55, 0.0, -59.41, 0.0, -36.59, 0.0, 0.003, 0.0, 3.69, 0.0, 9.99, 0.0, -43.55, 0.0, 5.0, 0.0);
	//sim.setNeuronParameters(CA3_MFA, 209.0, 0.0, 1.38, 0.0, -57.08, 0.0, -39.1, 0.0, 0.008, 0.0, 12.93, 0.0, 16.31, 0.0, -40.68, 0.0, 0.0, 0.0);//MFA_ORDEN
	
	sim.setNeuronParameters(CA3_OLM, 65.0, 0.0, 0.51, 0.0, -60.04, 0.0, -30.87, 0.0, 0.01, 0.0, 2.39, 0.0, 19.77, 0.0, -52.81, 0.0, 6.0, 0.0);
	
	sim.setNeuronParameters(CA3_TL, 205.0, 0.0, 0.52, 0.0, -64.64, 0.0, -52.64, 0.0, 0.002, 0.0, 1.24, 0.0, 0.17, 0.0, -60.62, 0.0, -19.0, 0.0);//modfified CA1 TL(type2) vth=-52.64, b=1.24
	//CA3 TL parameters are wrong

	// Create an instance of MyConnection class and pass it to CARLsim::connect
	// Only CCK- and MFA- has 0.07 GABAb, MFA also express CCK
	
	MyConnection* myConn = new MyConnection;
	short int LEC_CA3PC = sim.connect(EC_LEC, CA3_PC, myConn, 1.0, 0.268, SYN_FIXED);//0.268
	short int MEC_CA3PC = sim.connect(EC_MEC, CA3_PC, myConn, 1.0, 0.268, SYN_FIXED);//0.268
	short int DGGC_CA3PC = sim.connect(DG_GC, CA3_PC, myConn, 1.0, 1.633, SYN_FIXED);//EPSC RATIO = 0.88
	short int CA3PC_CA3PC = sim.connect(CA3_PC, CA3_PC, myConn, 1.0, 0.97, SYN_FIXED);//EPSC RATIO = 0.43
	short int CA3AAC_CA3PC = sim.connect(CA3_AAC, CA3_PC, myConn, 1.0, 0.0, SYN_FIXED);// 
	short int CA3BC_CA3PC = sim.connect(CA3_BC, CA3_PC, myConn, 1.0, 0.0, SYN_FIXED);// 
	short int CA3BCCCK_CA3PC = sim.connect(CA3_BCCCK, CA3_PC, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.2 (0.2 GABAb generate horizontal line)
	short int CA3BisC_CA3PC = sim.connect(CA3_BisC, CA3_PC, myConn, 1.0, 0.0, SYN_FIXED);// Start to generate oscillation!
	short int CA3MFA_CA3PC = sim.connect(CA3_MFA, CA3_PC, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.2 (0.2 GABAb generate horizontal line)
    short int CA3OLM_CA3PC = sim.connect(CA3_OLM, CA3_PC, myConn, 1.0, 0.0, SYN_FIXED);// 
	short int CA3TL_CA3PC = sim.connect(CA3_TL, CA3_PC, myConn, 1.0, 0.0, SYN_FIXED);// 
	
	short int LEC_CA3AAC = sim.connect(EC_LEC, CA3_AAC, myConn, 1.0, 0.769, SYN_FIXED);//EPSC RATIO = 0.27
	short int MEC_CA3AAC = sim.connect(EC_MEC, CA3_AAC, myConn, 1.0, 0.769, SYN_FIXED);//EPSC RATIO = 0.27
	short int DGGC_CA3AAC = sim.connect(DG_GC, CA3_AAC, myConn, 1.0, 0.769, SYN_FIXED);//EPSC RATIO = 0.27
	short int CA3PC_CA3AAC = sim.connect(CA3_PC, CA3_AAC, myConn, 1.0, 0.769, SYN_FIXED);//EPSC RATIO = 0.27
	short int CA3BCCCK_CA3AAC = sim.connect(CA3_BCCCK, CA3_AAC, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.07 
	short int CA3BisC_CA3AAC = sim.connect(CA3_BisC, CA3_AAC, myConn, 1.0, 0.0, SYN_FIXED);//
	short int CA3OLM_CA3AAC = sim.connect(CA3_OLM, CA3_AAC, myConn, 1.0, 0.0, SYN_FIXED);
	short int CA3TL_CA3AAC = sim.connect(CA3_TL, CA3_AAC, myConn, 1.0, 0.0, SYN_FIXED);

    // For INs, it takes 2-20 input to generate IPSPb, so I take 1/11=0.09 as overall ratio, then divided by connection.
	short int LEC_CA3BC = sim.connect(EC_LEC, CA3_BC, myConn, 1.0, 0.769, SYN_FIXED);//EPSC RATIO = 0.27
	short int MEC_CA3BC = sim.connect(EC_MEC, CA3_BC, myConn, 1.0, 0.769, SYN_FIXED);//EPSC RATIO = 0.27
	short int DGGC_CA3BC = sim.connect(DG_GC, CA3_BC, myConn, 1.0, 0.769, SYN_FIXED);//EPSC RATIO = 0.27
	short int CA3PC_CA3BC = sim.connect(CA3_PC, CA3_BC, myConn, 1.0, 0.769, SYN_FIXED);//EPSC RATIO = 0.27
	short int CA3BC_CA3BC = sim.connect(CA3_BC, CA3_BC, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.07 
	short int CA3BCCCK_CA3BC = sim.connect(CA3_BCCCK, CA3_BC, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.07 
    short int CA3BisC_CA3BC = sim.connect(CA3_BisC, CA3_BC, myConn, 1.0, 0.0, SYN_FIXED);//
    short int CA3MFA_CA3BC = sim.connect(CA3_MFA, CA3_BC, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.07 
	short int CA3OLM_CA3BC = sim.connect(CA3_OLM, CA3_BC, myConn, 1.0, 0.0, SYN_FIXED);
	short int CA3TL_CA3BC = sim.connect(CA3_TL, CA3_BC, myConn, 1.0, 0.0, SYN_FIXED);
	
	short int DGGC_CA3BCCCK = sim.connect(DG_GC, CA3_BCCCK, myConn, 1.0, 1.045, SYN_FIXED);//EPSC RATIO = 0.5
	short int CA3PC_CA3BCCCK = sim.connect(CA3_PC, CA3_BCCCK, myConn, 1.0, 1.045, SYN_FIXED);//EPSC RATIO = 0.5
	short int CA3BC_CA3BCCCK = sim.connect(CA3_BC, CA3_BCCCK, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.07 
	short int CA3BCCCK_CA3BCCCK = sim.connect(CA3_BCCCK, CA3_BCCCK, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.07
	short int CA3BisC_CA3BCCCK = sim.connect(CA3_BisC, CA3_BCCCK, myConn, 1.0, 0.0, SYN_FIXED);// 
	short int CA3MFA_CA3BCCCK = sim.connect(CA3_MFA, CA3_BCCCK, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.07 
	short int CA3OLM_CA3BCCCK = sim.connect(CA3_OLM, CA3_BCCCK, myConn, 1.0, 0.0, SYN_FIXED);
	short int CA3TL_CA3BCCCK = sim.connect(CA3_TL, CA3_BCCCK, myConn, 1.0, 0.0, SYN_FIXED);
	
	short int DGGC_CA3BisC = sim.connect(DG_GC, CA3_BisC, myConn, 1.0, 0.81, SYN_FIXED);//EPSC RATIO = 0.3
	short int CA3PC_CA3BisC = sim.connect(CA3_PC, CA3_BisC, myConn, 1.0, 0.81, SYN_FIXED);//EPSC RATIO = 0.3
	short int CA3BC_CA3BisC = sim.connect(CA3_BC, CA3_BisC, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.07 
	short int CA3BCCCK_CA3BisC = sim.connect(CA3_BCCCK, CA3_BisC, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.07 - add BCCCK-BisC
	short int CA3BisC_CA3BisC = sim.connect(CA3_BisC, CA3_BisC, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.07 
	short int CA3MFA_CA3BisC = sim.connect(CA3_MFA, CA3_BisC, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.07 
	short int CA3OLM_CA3BisC = sim.connect(CA3_OLM, CA3_BisC, myConn, 1.0, 0.0, SYN_FIXED);
	short int CA3TL_CA3BisC = sim.connect(CA3_TL, CA3_BisC, myConn, 1.0, 0.0, SYN_FIXED);
	
	short int DGGC_CA3MFA = sim.connect(DG_GC, CA3_MFA, myConn, 1.0, 1.045, SYN_FIXED);//EPSC RATIO = 0.5, borrow CCK as MFA also expressed CCK
	short int CA3PC_CA3MFA = sim.connect(CA3_PC, CA3_MFA, myConn, 1.0, 1.045, SYN_FIXED);//EPSC RATIO = 0.5, borrow CCK as MFA also expressed CCK
	short int CA3BC_CA3MFA = sim.connect(CA3_BC, CA3_MFA, myConn, 1.0, 0.0, SYN_FIXED);//
	short int CA3BCCCK_CA3MFA = sim.connect(CA3_BCCCK, CA3_MFA, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.07 
	short int CA3BisC_CA3MFA = sim.connect(CA3_BisC, CA3_MFA, myConn, 1.0, 0.0, SYN_FIXED);//
	short int CA3MFA_CA3MFA = sim.connect(CA3_MFA, CA3_MFA, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.07  
	short int CA3OLM_CA3MFA = sim.connect(CA3_OLM, CA3_MFA, myConn, 1.0, 0.0, SYN_FIXED);//0 
	short int CA3TL_CA3MFA = sim.connect(CA3_TL, CA3_MFA, myConn, 1.0, 0.0, SYN_FIXED);
	
	short int CA3PC_CA3OLM = sim.connect(CA3_PC, CA3_OLM, myConn, 1.0, 0.9, SYN_FIXED);//EPSC RATIO = 0.37
	short int CA3BisC_CA3OLM = sim.connect(CA3_BisC, CA3_OLM, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.07 
	short int CA3OLM_CA3OLM = sim.connect(CA3_OLM, CA3_OLM, myConn, 1.0, 0.0, SYN_FIXED);
	short int CA3TL_CA3OLM = sim.connect(CA3_TL, CA3_OLM, myConn, 1.0, 0.0, SYN_FIXED);
	
	short int CA3PC_CA3TL = sim.connect(CA3_PC, CA3_TL, myConn, 1.0, 0.9, SYN_FIXED);//EPSC RATIO = 0.37, borrow OLM
    short int CA3BisC_CA3TL = sim.connect(CA3_BisC, CA3_TL, myConn, 1.0, 0.0, SYN_FIXED);//
	short int CA3OLM_CA3TL = sim.connect(CA3_OLM, CA3_TL, myConn, 1.0, 0.0, SYN_FIXED);//
	short int CA3TL_CA3TL = sim.connect(CA3_TL, CA3_TL, myConn, 1.0, 0.0, SYN_FIXED);//
	
    //set STP 
    //sim.setSTP(CA3_PC, true, 0.45f, 50.0f, 750.0f);
    
    //sim.setSTP(CA3_AAC, true, 0.15f, 750.0f, 50.0f);
    
    //sim.setSTP(CA3_BC, true, 0.15f, 750.0f, 50.0f);
                                                         
    //sim.setSTP(CA3_BCCCK, true, 0.15f, 750.0f, 50.0f);
                                               
    //sim.setSTP(CA3_BisC, true, 0.15f, 750.0f, 50.0f);
    
    //sim.setSTP(CA3_MFA, true, 0.15f, 750.0f, 50.0f);
                                     
    //sim.setSTP(CA3_OLM, true, 0.15f, 750.0f, 50.0f);
    
    //sim.setSTP(CA3_TL, true, 0.15f, 750.0f, 50.0f);
                            
             
    // Load simulation                         
    //FILE* fID = NULL;
    //fID = fopen("network_CA3.dat", "rb");
    //sim.loadSimulation(fID);
    
     sim.setIntegrationMethod(RUNGE_KUTTA4, 10); 
    
     //sim.setNeuronMonitor(CA3_PC, "DEFAULT"); 
     
	// ---------------- SETUP STATE -------------------	
	
	watch.lap("setupNetwork");
	// build the network
	sim.setupNetwork();
	
	//fclose(fID);
	
	// save simulation file
	//sim.saveSimulation("network_CA3.dat", true); //fileName, saveSynapseInfo
	
	//setup baseline input
	/*
	PoissonRate poissRate_EC_MEC(num_EC_MEC, true);
	poissRate_EC_MEC.setRates(2.1f);
	sim.setSpikeRate(EC_MEC, &poissRate_EC_MEC);
	
    PoissonRate poissRate_EC_LEC(num_EC_LEC, true);
	poissRate_EC_LEC.setRates(2.1f);
	sim.setSpikeRate(EC_LEC, &poissRate_EC_LEC);
	
	PoissonRate poissRate_DG_GC(num_DG_GC, true);
	poissRate_DG_GC.setRates(0.66f);
	sim.setSpikeRate(DG_GC, &poissRate_DG_GC);
    */
    
	// set some monitors
	sim.setSpikeMonitor(EC_MEC, "NULL");
	sim.setSpikeMonitor(EC_LEC, "NULL");
	sim.setSpikeMonitor(DG_GC, "NULL");
	
	sim.setSpikeMonitor(CA3_PC, "DEFAULT");
	sim.setSpikeMonitor(CA3_AAC, "DEFAULT");
	sim.setSpikeMonitor(CA3_BC, "DEFAULT");
	sim.setSpikeMonitor(CA3_BCCCK, "DEFAULT");
	sim.setSpikeMonitor(CA3_BisC, "DEFAULT");
	sim.setSpikeMonitor(CA3_MFA, "DEFAULT");
	sim.setSpikeMonitor(CA3_OLM, "DEFAULT");
	sim.setSpikeMonitor(CA3_TL, "DEFAULT");
	
	
