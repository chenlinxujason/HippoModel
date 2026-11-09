// Set up the simulator, groups, inputs, neuron parameters, synapses, and monitors.
// This header contains statements included inside main, sharing its local variables.
    // keep track of execution time
	Stopwatch watch;

	// ---------------- CONFIG STATE -------------------
	// initialize random seed
	int randSeed = 42;

	// instantiate sim
	int numGPUs = 1;  // Patch Killian
	CARLsim sim("CA1", GPU_MODE, USER, numGPUs, randSeed);
	
    sim.setUserConnectivity(map_bigcon);

	// instantiate neuron types
	int num_EC_LEC3 = IDrange_EC_LEC3[1] - IDrange_EC_LEC3[0] + 1;
	int num_EC_MEC3 = IDrange_EC_MEC3[1] - IDrange_EC_MEC3[0] + 1;
	int num_CA3_PC = IDrange_CA3_PC[1] - IDrange_CA3_PC[0] + 1;
	int num_CA1_PC = IDrange_CA1_PC[1] - IDrange_CA1_PC[0] + 1;
	int num_CA1_AAC = IDrange_CA1_AAC[1] - IDrange_CA1_AAC[0] + 1;
	int num_CA1_BC = IDrange_CA1_BC[1] - IDrange_CA1_BC[0] + 1;
	int num_CA1_BCCCK = IDrange_CA1_BCCCK[1] - IDrange_CA1_BCCCK[0] + 1;
	int num_CA1_BisC = IDrange_CA1_BisC[1] - IDrange_CA1_BisC[0] + 1;
	int num_CA1_OLM = IDrange_CA1_OLM[1] - IDrange_CA1_OLM[0] + 1;
	int num_CA1_TL = IDrange_CA1_TL[1] - IDrange_CA1_TL[0] + 1;
	int num_CA1_NG = IDrange_CA1_NG[1] - IDrange_CA1_NG[0] + 1;
	
	// Loading MEC3, LEC3 and CA3PC activity from file
	int EC_LEC3 = sim.createSpikeGeneratorGroup("EC_LEC3", num_EC_LEC3, EXCITATORY_NEURON);
	int EC_MEC3 = sim.createSpikeGeneratorGroup("EC_MEC3", num_EC_MEC3, EXCITATORY_NEURON);
	int CA3_PC = sim.createSpikeGeneratorGroup("CA3_PC", num_CA3_PC, EXCITATORY_NEURON);
	
    // CA1 cells as izikevich
	int CA1_PC = sim.createGroup("CA1_PC", num_CA1_PC, EXCITATORY_NEURON);
	int CA1_AAC = sim.createGroup("CA1_AAC", num_CA1_AAC, INHIBITORY_NEURON);
	int CA1_BC = sim.createGroup("CA1_BC", num_CA1_BC, INHIBITORY_NEURON);
	int CA1_BCCCK = sim.createGroup("CA1_BCCCK", num_CA1_BCCCK, INHIBITORY_NEURON);
	int CA1_BisC = sim.createGroup("CA1_BisC", num_CA1_BisC, INHIBITORY_NEURON);
	int CA1_OLM = sim.createGroup("CA1_OLM", num_CA1_OLM, INHIBITORY_NEURON);
	int CA1_TL = sim.createGroup("CA1_TL", num_CA1_TL, INHIBITORY_NEURON);
	int CA1_NG = sim.createGroup("CA1_NG", num_CA1_NG, INHIBITORY_NEURON);
	
	std::cout << "Number of CA3_PC: " << num_CA3_PC << std::endl;
	std::cout << "Number of CA1_PC: " << num_CA1_PC << std::endl;
	std::cout << "Number of CA1_AAC: " << num_CA1_AAC << std::endl;
	std::cout << "Number of CA1_BC: " << num_CA1_BC << std::endl;
	std::cout << "Number of CA1_BCCCK: " << num_CA1_BCCCK << std::endl;
	std::cout << "Number of CA1_BisC: " << num_CA1_BisC << std::endl;
	std::cout << "Number of CA1_OLM: " << num_CA1_OLM << std::endl;
	std::cout << "Number of CA1_TL: " << num_CA1_TL << std::endl;
	std::cout << "Number of CA1_NG: " << num_CA1_NG << std::endl;

	
	// Create spike gen from file	
	SpikeGeneratorFromFile SGF_MEC3("results/MEC_128000cells_1200.0sec(mean=2.1Hz,ymax=2.4,60x60cm,non-uniform grid field,d*10,min=0.1Hz)_SimData_MCscale5.dat");
	sim.setSpikeGenerator(EC_MEC3, &SGF_MEC3);

	SpikeGeneratorFromFile SGF_CA3PC("results/spk_CA3_PC.dat");
	sim.setSpikeGenerator(CA3_PC, &SGF_CA3PC);
	
	// set conductance
	sim.setConductances(CA1_PC, 7.295, 0, 29.057, 53.27, 0, 360.76); //ok - type3, CA3PC-CA1PC, CA1BisC-CA1PC
	
    sim.setConductances(CA1_AAC, 1.36, 0, 15.65, 15.55, 0, 187.23); //ok(CA3PC-CA1AAC, CA1BC-CA1AAC)

    sim.setConductances(CA1_BC, 1.0, 0, 14.83, 29.4, 0, 250.92);//ok(CA3PC-CA1BC, CA1BisC-CA1BC)

    sim.setConductances(CA1_BCCCK, 1.0, 0, 14.83, 16.6, 0, 192.04);//ok(CA3PC-CA1BCCCK, CA1BC-CA1BCCCK),type2 (modify,correct EPSP shape)

    //sim.setConductances(CA1_BisC, 1.1, 0, 15.06, 33.69, 0, 270.67); //modify,ok(CA1PC-CA3BisC)type1
    sim.setConductances(CA1_BisC, 2.26, 0, 17.67, 32.65, 0, 265.9); //ok(CA3PC-CA1BisC,CA1BisC-CA1BisC)type2
    
    sim.setConductances(CA1_NG, 25.61, 0, 70.44, 3.0, 0, 129.5); //ok(EC-CA1NG,-CA1NG)

    sim.setConductances(CA1_OLM, 4.45, 0, 22.64, 31.6, 0, 261.06); //ok(CA3/CA1PC-CA1OLM, CA1BisC-CA1OLM),modify CA1 OLM
   
    sim.setConductances(CA1_TL, 1.0, 0, 14.83, 17.566, 0, 196.5); //ok(CA3/CA1PC-CA1TL,CA1BC-CA1TL),type1 modify
   
    
    // To be continuted ... //
    //sim.setConductances(CA1_Ivy, 8.3, 0, 48.26, 16.1, 0, 417.5); //
    //sim.setConductances(CA1_Sch, 8.3, 0, 48.26, 16.1, 0, 417.5); //
	

	// set-up network parameters(C,k,Vr,Vt,a,b,Vpeak,Vmin,d)
	sim.setNeuronParameters(CA1_PC, 506.0, 0.0, 5.89, 0.0, -62.16, 0.0, -48.42, 0.0, 0.081, 0.0, -15.09, 0.0, 32.77, 0.0, -52.21, 0.0, 483.0, 0.0);//type3
	
    sim.setNeuronParameters(CA1_AAC, 287.0, 0.0, 4.0, 0.0, -65.16, 0.0, -49.04, 0.0, 0.013, 0.0, -4.02, 0.0, 15.13, 0.0, -55.48, 0.0, 38.0, 0.0);// CA1 AAC, type2 ASP, modify vpeak from -0.61 to 15.13 to fix its action potential as its original vpeak<0
	
	sim.setNeuronParameters(CA1_BC, 114.0, 0.0, 1.19, 0.0, -57.63, 0.0, -35.53, 0.0, 0.005, 0.0, 0.22, 0.0, 21.72, 0.0, -48.7, 0.0, 2.0, 0.0);

	sim.setNeuronParameters(CA1_BCCCK, 477.0, 0.0, 2.0, 0.0, -63.1, 0.0, -40.6, 0.0, 0.04, 0.0, -12.2, 0.0, 27.12, 0.0, -56.15, 0.0, 460.0, 0.0);// CA1 BCCCK, type2, modify k,a,Vr so that IPSP shape correct and pattern also correct
	//sim.setNeuronParameters(CA1_BCCCK, 477.0, 0.0, 2.48, 0.0, -63.1, 0.0, -51.93, 0.0, 0.016, 0.0, -12.2, 0.0, 27.12, 0.0, -56.15, 0.0, 460.0, 0.0);// CA1 BCCCK, type2, incorrect IPSP shape
	//sim.setNeuronParameters(CA1_BCCCK, 59.0, 0.0, 1.06, 0.0, -63.18, 0.0, -38.18, 0.0, 0.023, 0.0, -26.87, 0.0, 27.44, 0.0, -53.32, 0.0, 294.0, 0.0);// CA1 BCCCK, type1 incorrect EPSP shape
	
	sim.setNeuronParameters(CA1_BisC, 208.0, 0.0, 3.06, 0.0, -64.94, 0.0, -44.58, 0.0, 0.026, 0.0, 7.36, 0.0, 6.92, 0.0, -51.09, 0.0, 4, 0.0); //CA1 Bistratified type2 modift AP amplitude (avg 51.5)
	//sim.setNeuronParameters(CA1_BisC, 112.0, 0.0, 1.2, 0.0, -64.67, 0.0, -47.67, 0.0, 0.008,0.0, 16.4, 0.0, 3.83, 0.0, -50.2, 0.0, 19.0, 0.0);// modified CA1 BisC(type1),Vth,Vpeak and patterns correct

    sim.setNeuronParameters(CA1_NG, 254.0, 0.0, 2.36, 0.0, -63.33, 0.0, -47.62, 0.0, 0.0075, 0.0, 9.2, 0.0, 10.7, 0.0, -50.78, 0.0, 80, 0.0); //modified CA1 Neurogliaform to avoid undershoot: decrease b to 9.2, then decrease a = 0.0075, increase d = 80
	
	//sim.setNeuronParameters(CA1_OLM, 65.0, 0.0, 0.51, 0.0, -60.04, 0.0, -30.87, 0.0, 0.01, 0.0, 2.39, 0.0, 19.77, 0.0, -52.81, 0.0, 6.0, 0.0);//use CA3 OLM parameters
	//sim.setNeuronParameters(CA1_OLM, 73.0, 0.0, 4.47, 0.0, -60, 0.0, -56.41, 0.0, 0.069, 0.0, 74.3, 0.0, 7.99, 0.0, -58.16, 0.0, 299, 0.0); //CA1 OLM,wrong
	sim.setNeuronParameters(CA1_OLM, 103.0, 0.0, 2.1, 0.0, -60, 0.0, -46.0, 0.0, 0.001, 0.0, 42.0, 0.0, 7.99, 0.0, -58.16, 0.0, 14, 0.0); //modify CA1 OLM
	
	//sim.setNeuronParameters(CA1_TL, 38.0, 0.0, 0.16, 0.0, -60.94, 0.0, -46.19, 0.0, 0.004, 0.0, 2.72, 0.0, -0.92, 0.0, -55.34, 0.0, -3, 0.0);//CA1 Trilaminar, subtype1
    sim.setNeuronParameters(CA1_TL, 45.0, 0.0, 0.16, 0.0, -60.94, 0.0, -46.19, 0.0, 0.001, 0.0, 1, 0.0, -0.92, 0.0, -55.34, 0.0, 3, 0.0);//CA1 Trilaminar, subtype1 modify: decrease a to 0.001 to avoid rebound, and increase C to 45, increase d to 1 to avoid cell become too excitable
    
    sim.setNeuronMonitor(CA1_PC, "DEFAULT"); 
    
    // Connect neuron groups
    //#include "../loadConnectivityCA1_sim.h"
    
    //sim.setSTP(CA1_PC, true, 0.45f, 50.0f, 750.0f);


	// create an instance of MyConnection class and pass it to CARLsim::connect
	// only CCK- and NG- has 0.07 GABAb
	MyConnection* myConn = new MyConnection;
	short int LEC3_CA1PC = sim.connect(EC_LEC3, CA1_PC, myConn, 1.0, 0.268, SYN_FIXED);//0.268
	short int MEC3_CA1PC = sim.connect(EC_MEC3, CA1_PC, myConn, 1.0, 0.268, SYN_FIXED);//0.268
	short int CA3PC_CA1PC = sim.connect(CA3_PC, CA1_PC, myConn, 1.0, 0.608, SYN_FIXED);//0.608
	short int CA1PC_CA1PC = sim.connect(CA1_PC, CA1_PC, myConn, 1.0, 0.97, SYN_FIXED);//0.97
	short int CA1AAC_CA1PC = sim.connect(CA1_AAC, CA1_PC, myConn, 1.0, 0.0, SYN_FIXED);//presynaptic AAC, GABAa only
	short int CA1BC_CA1PC = sim.connect(CA1_BC, CA1_PC, myConn, 1.0, 0.0, SYN_FIXED);//presynaptic BC, GABAa only
	short int CA1BCCCK_CA1PC = sim.connect(CA1_BCCCK, CA1_PC, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.2 (0.2 GABAb generate horizontal line!)
	short int CA1BisC_CA1PC = sim.connect(CA1_BisC, CA1_PC, myConn, 1.0, 0.0, SYN_FIXED);//horizontal line
	short int CA1NG_CA1PC = sim.connect(CA1_NG, CA1_PC, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.2 (0.2 GABAb generate horizontal line!)
	short int CA1OLM_CA1PC = sim.connect(CA1_OLM, CA1_PC, myConn, 1.0, 0.0, SYN_FIXED);
	short int CA1TL_CA1PC = sim.connect(CA1_TL, CA1_PC, myConn, 1.0, 0.0, SYN_FIXED);
	
	short int LEC3_CA1AAC = sim.connect(EC_LEC3, CA1_AAC, myConn, 1.0, 0.769, SYN_FIXED);//0.769 - 0.686 - [0.21,1)
	short int MEC3_CA1AAC = sim.connect(EC_MEC3, CA1_AAC, myConn, 1.0, 0.769, SYN_FIXED);//0.769 - 0.686 - [0.21,1)
	short int CA3PC_CA1AAC = sim.connect(CA3_PC, CA1_AAC, myConn, 1.0, 0.769, SYN_FIXED);//0.769 - 0.686 - [0.21,1)
	short int CA1PC_CA1AAC = sim.connect(CA1_PC, CA1_AAC, myConn, 1.0, 0.769, SYN_FIXED);//0.769 - 0.686 - [0.21,1)
	short int CA1BC_CA1AAC = sim.connect(CA1_BC, CA1_AAC, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.07
	short int CA1BCCCK_CA1AAC = sim.connect(CA1_BCCCK, CA1_AAC, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.07
	short int CA1BisC_CA1AAC = sim.connect(CA1_BisC, CA1_AAC, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.07
	short int CA1NG_CA1AAC = sim.connect(CA1_NG, CA1_AAC, myConn, 1.0, 0.07, SYN_FIXED);//*1.0, 0.07
	short int CA1OLM_CA1AAC = sim.connect(CA1_OLM, CA1_AAC, myConn, 1.0, 0.0, SYN_FIXED);//*1.0, 0.07
	short int CA1TL_CA1AAC = sim.connect(CA1_TL, CA1_AAC, myConn, 1.0, 0.0, SYN_FIXED);//
	
    short int LEC3_CA1BC = sim.connect(EC_LEC3, CA1_BC, myConn, 1.0, 0.769, SYN_FIXED);//0.769 - 0.686 - [0.21,1)
	short int MEC3_CA1BC = sim.connect(EC_MEC3, CA1_BC, myConn, 1.0, 0.769, SYN_FIXED);//0.769 - 0.686 - [0.21,1)
	short int CA3PC_CA1BC = sim.connect(CA3_PC, CA1_BC, myConn, 1.0, 0.769, SYN_FIXED);//0.769 - 0.686 - [0.21,1)
	short int CA1PC_CA1BC = sim.connect(CA1_PC, CA1_BC, myConn, 1.0, 0.769, SYN_FIXED);//0.769 - 0.686 - [0.21,1)
	short int CA1BC_CA1BC = sim.connect(CA1_BC, CA1_BC, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.07
	short int CA1BCCCK_CA1BC = sim.connect(CA1_BCCCK, CA1_BC, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.07
    short int CA1BisC_CA1BC = sim.connect(CA1_BisC, CA1_BC, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.07
    short int CA1NG_CA1BC = sim.connect(CA1_NG, CA1_BC, myConn, 1.0, 0.07, SYN_FIXED);//*1.0, 0.07
    short int CA1OLM_CA1BC = sim.connect(CA1_OLM, CA1_BC, myConn, 1.0, 0.0, SYN_FIXED);//*1.0, 0.07
    short int CA1TL_CA1BC = sim.connect(CA1_TL, CA1_BC, myConn, 1.0, 0.0, SYN_FIXED);	
	
	short int LEC3_CA1BCCCK = sim.connect(EC_LEC3, CA1_BCCCK, myConn, 1.0, 1.045, SYN_FIXED);//1.045 - 0.554 - [0.533,1.045]
	short int MEC3_CA1BCCCK = sim.connect(EC_MEC3, CA1_BCCCK, myConn, 1.0, 1.045, SYN_FIXED);//1.045 - 0.554 - [0.533,1.045]
	short int CA3PC_CA1BCCCK = sim.connect(CA3_PC, CA1_BCCCK, myConn, 1.0, 1.045, SYN_FIXED);//1.045 - 0.554 - [0.533,1.045]
	short int CA1PC_CA1BCCCK = sim.connect(CA1_PC, CA1_BCCCK, myConn, 1.0, 1.045, SYN_FIXED);//1.045 - 0.554 - [0.533,1.045]
	short int CA1BC_CA1BCCCK = sim.connect(CA1_BC, CA1_BCCCK, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.07
	short int CA1BCCCK_CA1BCCCK = sim.connect(CA1_BCCCK, CA1_BCCCK, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.07
    short int CA1BisC_CA1BCCCK = sim.connect(CA1_BisC, CA1_BCCCK, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.07
    short int CA1NG_CA1BCCCK = sim.connect(CA1_NG, CA1_BCCCK, myConn, 1.0, 0.07, SYN_FIXED);//*1.0, 0.07
    short int CA1OLM_CA1BCCCK = sim.connect(CA1_OLM, CA1_BCCCK, myConn, 1.0, 0.0, SYN_FIXED);//*1.0, 0.07
    short int CA1TL_CA1BCCCK = sim.connect(CA1_TL, CA1_BCCCK, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.07
   
    
    ////No EC-CA1BisC in h5 connectivity matrix
	short int CA3PC_CA1BisC = sim.connect(CA3_PC, CA1_BisC, myConn, 1.0, 0.81, SYN_FIXED);//0.81 - 0.715 - [0.591,0.981]
	short int CA1PC_CA1BisC = sim.connect(CA1_PC, CA1_BisC, myConn, 1.0, 0.81, SYN_FIXED);//0.81 - 0.715 - [0.591,0.981]
	short int CA1BC_CA1BisC = sim.connect(CA1_BC, CA1_BisC, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.07
	short int CA1BCCCK_CA1BisC = sim.connect(CA1_BCCCK, CA1_BisC, myConn, 1.0, 0.07, SYN_FIXED);//1.0, 0.07
    short int CA1BisC_CA1BisC = sim.connect(CA1_BisC, CA1_BisC, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.07
    short int CA1TL_CA1BisC = sim.connect(CA1_TL, CA1_BisC, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.07
    
    
    short int LEC3_CA1NG = sim.connect(EC_LEC3, CA1_NG, myConn, 1.0, 0.9, SYN_FIXED);//0.9 - 0.69 - (0,1)
	short int MEC3_CA1NG = sim.connect(EC_MEC3, CA1_NG, myConn, 1.0, 0.9, SYN_FIXED);//0.9 - 0.69 - (0,1)
	short int CA1NG_CA1NG = sim.connect(CA1_NG, CA1_NG, myConn, 1.0, 0.07, SYN_FIXED);//*1.0, 0.07
	short int CA1OLM_CA1NG = sim.connect(CA1_OLM, CA1_NG, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.07
  
    
	short int CA3PC_CA1OLM = sim.connect(CA3_PC, CA1_OLM, myConn, 1.0, 0.9, SYN_FIXED);//0.9 - 0.69 - (0,1)
	short int CA1PC_CA1OLM = sim.connect(CA1_PC, CA1_OLM, myConn, 1.0, 0.9, SYN_FIXED);//0.9 - 0.69 - (0,1)
	short int CA1BisC_CA1OLM = sim.connect(CA1_BisC, CA1_OLM, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.07
    short int CA1TL_CA1OLM = sim.connect(CA1_TL, CA1_OLM, myConn, 1.0, 0.0, SYN_FIXED);// for OLM, pre-OLM and OLM-post all has GABAb
	
	short int CA3PC_CA1TL = sim.connect(CA3_PC, CA1_TL, myConn, 1.0, 0.9, SYN_FIXED);//0.9 - 0.69 - (0,1)
	short int CA1PC_CA1TL = sim.connect(CA1_PC, CA1_TL, myConn, 1.0, 0.9, SYN_FIXED);//0.9 - 0.69 - (0,1)
	short int CA1BisC_CA1TL = sim.connect(CA1_BisC, CA1_TL, myConn, 1.0, 0.0, SYN_FIXED);//1.0, 0.07
    short int CA1TL_CA1TL = sim.connect(CA1_TL, CA1_TL, myConn, 1.0, 0.0, SYN_FIXED);//
   
   
	
   // Load simulation
   // FILE* fID = NULL;
   // fID = fopen("network_CA1_type3.dat", "rb");
   // sim.loadSimulation(fID);
 
    sim.setIntegrationMethod(RUNGE_KUTTA4, 10); 
 


	// ---------------- SETUP STATE -------------------

	watch.lap("setupNetwork");
	// build the network
	sim.setupNetwork();

  // save simulation file
	//sim.saveSimulation("network_CA1_type2.dat", true); //fileName, saveSynapseInfo

	// Close load file
	//fclose(fID);

	//setup baseline input
	//PoissonRate poissRate_EC_MEC3(num_EC_MEC3, true);
	//poissRate_EC_MEC3.setRates(2.1f);
	//sim.setSpikeRate(EC_MEC3, &poissRate_EC_MEC3);
	
    PoissonRate poissRate_EC_LEC3(num_EC_LEC3, true);
	poissRate_EC_LEC3.setRates(2.1f);
	sim.setSpikeRate(EC_LEC3, &poissRate_EC_LEC3);
	
	//PoissonRate poissRate_CA3_PC(num_CA3_PC, true);
	//poissRate_CA3_PC.setRates(0.88f);
	//sim.setSpikeRate(CA3_PC, &poissRate_CA3_PC);
	
	
	// set some monitors
	sim.setSpikeMonitor(EC_MEC3, "DEFAULT");
	sim.setSpikeMonitor(EC_LEC3, "DEFAULT");
	sim.setSpikeMonitor(CA3_PC, "NULL");

	sim.setSpikeMonitor(CA1_PC, "DEFAULT");
	sim.setSpikeMonitor(CA1_BC, "DEFAULT");
	sim.setSpikeMonitor(CA1_AAC, "DEFAULT");
	sim.setSpikeMonitor(CA1_BCCCK, "DEFAULT");
	sim.setSpikeMonitor(CA1_BisC, "DEFAULT");
	sim.setSpikeMonitor(CA1_NG, "DEFAULT");
	sim.setSpikeMonitor(CA1_OLM, "DEFAULT");
	sim.setSpikeMonitor(CA1_TL, "DEFAULT");


