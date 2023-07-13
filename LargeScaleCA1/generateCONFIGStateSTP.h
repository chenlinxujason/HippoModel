
#ifdef __NO_CUDA__
   int CA1_Pyramidal = sim.createGroup("CA1_Pyramidal", 388637.0, //159341.0, //for mice,
                              EXCITATORY_NEURON, 0, CPU_CORES);//388637 for rat
                              
   int CA1_Radiatum_Giant = sim.createGroup("CA1_Radiatum_Giant", 9716.0,//3984.0, //for mice,
                              EXCITATORY_NEURON, 0, CPU_CORES);
                              
   int CA1_Axo_axonic = sim.createGroup("CA1_Axo_axonic", 762.0,//312.0, //for mice,
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA1_Horizontal_Axo_axonic = sim.createGroup("CA1_Horizontal_Axo_axonic", 494.0,//203.0, //for mice,
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA1_Back_Projection = sim.createGroup("CA1_Back_Projection", 1934.0,//793.0, //for mice,
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA1_Basket = sim.createGroup("CA1_Basket", 819.0,//336.0, //for mice,
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA1_Basket_CCK = sim.createGroup("CA1_Basket_CCK", 963.0,//395.0, //for mice,
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA1_Horizontal_Basket = sim.createGroup("CA1_Horizontal_Basket", 811.0,//333.0, //for mice,
                              INHIBITORY_NEURON, 0, CPU_CORES);
                                                   
   int CA1_Bistratified = sim.createGroup("CA1_Bistratified", 1962.0, //804.0, //for mice,
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA1_Ivy = sim.createGroup("CA1_Ivy", 1898.0,//778.0, //for mice,
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA1_LMR = sim.createGroup("CA1_LMR", 331.0,//136.0, //for mice
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA1_Neurogliaform = sim.createGroup("CA1_Neurogliaform", 2716.0,//1114.0, //for mice
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA1_Neurogliaform_Projecting = sim.createGroup("CA1_Neurogliaform_Projecting", 235.0,//96.0,//for mice
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA1_OLM = sim.createGroup("CA1_OLM", 1271.0,//521.0,//for mice
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA1_Recurrent_O_LM = sim.createGroup("CA1_Recurrent_O_LM", 170.0,//70.0,//for mice
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA1_O_LMR = sim.createGroup("CA1_O_LMR", 1400.0,//574.0,//for mice
                              INHIBITORY_NEURON, 0, CPU_CORES); 
                              
   int CA1_Oriens_Alveus = sim.createGroup("CA1_Oriens_Alveus", 1480.0, //607.0,//for mice
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA1_Oriens_Bistratified = sim.createGroup("CA1_Oriens_Bistratified", 830.0,//340.0,//for mice
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA1_OR_LM = sim.createGroup("CA1_OR_LM", 1777.0,//729.0,//for mice
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA1_Perforant_Path_Associated = sim.createGroup("CA1_Perforant_Path_Associated", 1129.0,//463.0,//for mice
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA1_Perforant_Path_Associated_QuadD = sim.createGroup("CA1_Perforant_Path_Associated_QuadD", 53.0,//22.0,//for mice
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA1_Quadrilaminar = sim.createGroup("CA1_Quadrilaminar", 23.0,//9.0,//for mice
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA1_Radiatum = sim.createGroup("CA1_Radiatum", 227.0,//93.0,//for mice
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA1_R_Receiving_Apical_Target = sim.createGroup("CA1_R_Receiving_Apical_Target", 311.0,//128.0,//for mice
                              INHIBITORY_NEURON, 0, CPU_CORES);
                                                   
   int CA1_Schaffer_Collateral_Associated = sim.createGroup("CA1_Schaffer_Collateral_Associated", 2404.0, //986.0,//for mice
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA1_SO_SO = sim.createGroup("CA1_SO_SO", 763.0,//313.0,//for mice
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA1_Trilaminar = sim.createGroup("CA1_Trilaminar", 977.0,//401.0,//for mice
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA1_Radial_Trilaminar = sim.createGroup("CA1_Radial_Trilaminar", 290.0,//119.0,//for mice
                              INHIBITORY_NEURON, 0, CPU_CORES);                       
                              
#else
   int CA1_Pyramidal = sim.createGroup("CA1_Pyramidal", 388637.0, //159341.0, //for mice,
                              EXCITATORY_NEURON, 0, GPU_CORES);//388637 for rat
                              
   int CA1_Radiatum_Giant = sim.createGroup("CA1_Radiatum_Giant", 9716.0,//3984.0, //for mice,
                              EXCITATORY_NEURON, 0, GPU_CORES);
                              
   int CA1_Axo_axonic = sim.createGroup("CA1_Axo_axonic", 762.0,//312.0, //for mice,
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA1_Horizontal_Axo_axonic = sim.createGroup("CA1_Horizontal_Axo_axonic", 494.0,//203.0, //for mice,
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA1_Back_Projection = sim.createGroup("CA1_Back_Projection", 1934.0,//793.0, //for mice,
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA1_Basket = sim.createGroup("CA1_Basket", 819.0,//336.0, //for mice,
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA1_Basket_CCK = sim.createGroup("CA1_Basket_CCK", 963.0,//395.0, //for mice,
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA1_Horizontal_Basket = sim.createGroup("CA1_Horizontal_Basket", 811.0,//333.0, //for mice,
                              INHIBITORY_NEURON, 0, GPU_CORES);
                                                   
   int CA1_Bistratified = sim.createGroup("CA1_Bistratified", 1962.0, //804.0, //for mice,
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA1_Ivy = sim.createGroup("CA1_Ivy", 1898.0,//778.0, //for mice,
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA1_LMR = sim.createGroup("CA1_LMR", 331.0,//136.0, //for mice
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA1_Neurogliaform = sim.createGroup("CA1_Neurogliaform", 2716.0,//1114.0, //for mice
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA1_Neurogliaform_Projecting = sim.createGroup("CA1_Neurogliaform_Projecting", 235.0,//96.0,//for mice
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA1_OLM = sim.createGroup("CA1_OLM", 1271.0,//521.0,//for mice
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA1_Recurrent_O_LM = sim.createGroup("CA1_Recurrent_O_LM", 170.0,//70.0,//for mice
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA1_O_LMR = sim.createGroup("CA1_O_LMR", 1400.0,//574.0,//for mice
                              INHIBITORY_NEURON, 0, GPU_CORES); 
                              
   int CA1_Oriens_Alveus = sim.createGroup("CA1_Oriens_Alveus", 1480.0, //607.0,//for mice
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA1_Oriens_Bistratified = sim.createGroup("CA1_Oriens_Bistratified", 830.0,//340.0,//for mice
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA1_OR_LM = sim.createGroup("CA1_OR_LM", 1777.0,//729.0,//for mice
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA1_Perforant_Path_Associated = sim.createGroup("CA1_Perforant_Path_Associated", 1129.0,//463.0,//for mice
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA1_Perforant_Path_Associated_QuadD = sim.createGroup("CA1_Perforant_Path_Associated_QuadD", 53.0,//22.0,//for mice
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA1_Quadrilaminar = sim.createGroup("CA1_Quadrilaminar", 23.0,//9.0,//for mice
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA1_Radiatum = sim.createGroup("CA1_Radiatum", 227.0,//93.0,//for mice
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA1_R_Receiving_Apical_Target = sim.createGroup("CA1_R_Receiving_Apical_Target", 311.0,//128.0,//for mice
                              INHIBITORY_NEURON, 0, GPU_CORES);
                                                   
   int CA1_Schaffer_Collateral_Associated = sim.createGroup("CA1_Schaffer_Collateral_Associated", 2404.0, //986.0,//for mice
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA1_SO_SO = sim.createGroup("CA1_SO_SO", 763.0,//313.0,//for mice
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA1_Trilaminar = sim.createGroup("CA1_Trilaminar", 977.0,//401.0,//for mice
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA1_Radial_Trilaminar = sim.createGroup("CA1_Radial_Trilaminar", 290.0,//119.0,//for mice
                              INHIBITORY_NEURON, 0, GPU_CORES);                       
                                                                              
#endif

                                                
sim.setNeuronParameters(CA1_Pyramidal, 334.0, 0.0, 1.56, 0.0,
                             -69.36, 0.0, -53.22, 0.0, 
                             0.0, 0.0, -17.25, 0.0, 
                             25.46, 0.0, -60.22, 0.0,
                             16.0, 0.0); //CA1_Pyramidal
                           
sim.setNeuronParameters(CA1_Radiatum_Giant, 725.0, 0.0, 0.73, 0.0,
                             -66.09, 0.0, -27.01, 0.0, 
                             0.0, 0.0, 91.37, 0.0, 
                             13.37, 0.0, -46.97, 0.0,
                             100.0, 0.0); //CA1_Radiatum_Giant
                             
sim.setNeuronParameters(CA1_Axo_axonic, 234.0, 0.0, 9.83, 0.0,
                             -66.76, 0.0, -65.78, 0.0, 
                             0.002, 0.0, 14.47, 0.0, 
                             3.18, 0.0, -62.22, 0.0,
                             26.0, 0.0); //CA1_Axo-axonic
                                                      
sim.setNeuronParameters(CA1_Horizontal_Axo_axonic, 88.0, 0.0, 2.15, 0.0,
                             -56.45, 0.0, -41.32, 0.0, 
                             0.03, 0.0, -47.85, 0.0, 
                             23.89, 0.0, -46.01, 0.0,
                             277.0, 0.0); //CA1_Horizontal_Axo_axonic
                             
sim.setNeuronParameters(CA1_Back_Projection, 133.0, 0.0, 0.67, 0.0,
                             -60.28, 0.0, -47.12, 0.0, 
                             0.004, 0.0, 15.66, 0.0, 
                             0.59, 0.0, -60.41, 0.0,
                             -30.0, 0.0); //CA1_Back_Projection
 
sim.setNeuronParameters(CA1_Basket, 114.0, 0.0, 1.19, 0.0,
                             -57.63, 0.0, -35.53, 0.0, 
                             0.005, 0.0, 0.22, 0.0, 
                             21.72, 0.0, -48.7, 0.0,
                             2, 0.0); //CA1_Basket
                             
sim.setNeuronParameters(CA1_Basket_CCK, 59.0, 0.0, 1.06, 0.0,
                             -63.18, 0.0, -38.18, 0.0, 
                             0.023, 0.0, -26.87, 0.0, 
                             27.44, 0.0, -53.32, 0.0,
                             294, 0.0); //CA1_Basket_CCK
                             
sim.setNeuronParameters(CA1_Horizontal_Basket, 46.0, 0.0, 0.83, 0.0,
                             -55.52, 0.0, -27.75, 0.0, 
                             0.002, 0.0, 0.26, 0.0, 
                             20.28, 0.0, -45.42, 0.0,
                             1, 0.0); //CA1_Horizontal_Basket
                             
sim.setNeuronParameters(CA1_Bistratified, 107.0, 0.0, 3.94, 0.0,
                             -64.67, 0.0, -58.74, 0.0, 
                             0.002, 0.0, 16.58, 0.0, 
                             -9.93, 0.0, -59.7, 0.0,
                             19, 0.0); //CA1_Bistratified
                             
sim.setNeuronParameters(CA1_Ivy, 364.0, 0.0, 1.92, 0.0,
                             -70.43, 0.0, -40.86, 0.0, 
                             0.009, 0.0, 1.91, 0.0, 
                             -6.92, 0.0, -53.4, 0.0,
                             45, 0.0); //CA1_Ivy
                             
sim.setNeuronParameters(CA1_LMR, 40.0, 0.0, 0.65, 0.0,
                             -53.95, 0.0, -43.83, 0.0, 
                             0.003, 0.0, -12.12, 0.0, 
                             25.2, 0.0, -54.05, 0.0,
                             11, 0.0); //CA1_LMR

sim.setNeuronParameters(CA1_Neurogliaform, 254.0, 0.0, 2.36, 0.0,
                             -63.33, 0.0, -47.62, 0.0, 
                             0.009, 0.0, 17.56, 0.0, 
                             10.7, 0.0, -50.78, 0.0,
                             40, 0.0); //CA1_Neurogliaform
                             
sim.setNeuronParameters(CA1_Neurogliaform_Projecting, 456.0, 0.0, 1.86, 0.0,
                             -63.35, 0.0, -56.26, 0.0, 
                             0.003, 0.0, -2.72, 0.0, 
                             17.06, 0.0, -52.77, 0.0,
                             90, 0.0); //CA1_Neurogliaform_Projecting
                             
sim.setNeuronParameters(CA1_OLM, 73.0, 0.0, 4.47, 0.0,
                             -60, 0.0, -56.41, 0.0, 
                             0.069, 0.0, 74.3, 0.0, 
                             7.99, 0.0, -58.16, 0.0,
                             299, 0.0); //CA1_OLM
                             
sim.setNeuronParameters(CA1_Recurrent_O_LM, 210.0, 0.0, 0.64, 0.0,
                             -68.46, 0.0, -40.03, 0.0, 
                             0.001, 0.0, 1.93, 0.0, 
                             24.6, 0.0, -68.06, 0.0,
                             20, 0.0); //CA1_Recurrent_O_LM
                             
sim.setNeuronParameters(CA1_O_LMR, 96.0, 0.0, 0.33, 0.0,
                             -56.44, 0.0, -27.62, 0.0, 
                             0.006, 0.0, 0.4, 0.0, 
                             29.48, 0.0, -51.29, 0.0,
                             48, 0.0); //CA1_O_LMR
                             
sim.setNeuronParameters(CA1_Oriens_Alveus, 49.0, 0.0, 1.21, 0.0,
                             -51.65, 0.0, -41.92, 0.0, 
                             0.056, 0.0, -44.92, 0.0, 
                             -5.45, 0.0, -46.01, 0.0,
                             416, 0.0); //CA1_Oriens_Alveus
                             
sim.setNeuronParameters(CA1_Oriens_Bistratified, 841.0, 0.0, 2.91, 0.0,
                             -57.08, 0.0, -48.47, 0.0, 
                             0.002, 0.0, 13.67, 0.0, 
                             4.15, 0.0, -52.91, 0.0,
                             35, 0.0); //CA1_Oriens_Bistratified
                             
sim.setNeuronParameters(CA1_OR_LM, 248.0, 0.0, 0.56, 0.0,
                             -57.03, 0.0, -42.75, 0.0, 
                             0.014, 0.0, 2.09, 0.0, 
                             82.73, 0.0, -45.49, 0.0,
                             -15, 0.0); //CA1_OR_LM
                             
sim.setNeuronParameters(CA1_Perforant_Path_Associated, 233.0, 0.0, 4.1, 0.0,
                             -55.47, 0.0, -46.1, 0.0, 
                             0.0, 0.0, 5.05, 0.0, 
                             -5.27, 0.0, -51.04, 0.0,
                             47, 0.0); //CA1_Perforant_Path_Associated *subtype2
                             
//sim.setNeuronParameters(CA1_Perforant_Path_Associated, 12.0, 0.0, 4.84, 0.0,
                             //-55.44, 0.0, -42.5, 0.0, 
                             //0.045, 0.0, -49.31, 0.0, 
                             //-0.05, 0.0, -51, 0.0,
                             //194, 0.0); //CA1_Perforant_Path_Associated * subtype 1 can't be finished in some cases, i.e 100pA+900ms PW
 
sim.setNeuronParameters(CA1_Perforant_Path_Associated_QuadD, 12.0, 0.0, 4.66, 0.0,
                             -64.88, 0.0, -51.84, 0.0, 
                             0.096, 0.0, -44.34, 0.0, 
                             -2.99, 0.0, -62.54, 0.0,
                             290, 0.0); //CA1_Perforant_Path_Associated_QuadD * can't be finished in some cases, i.e 100pA+900ms PW
                             
sim.setNeuronParameters(CA1_Quadrilaminar, 186.0, 0.0, 1.78, 0.0,
                             -73.48, 0.0, -54.94, 0.0, 
                             0.006, 0.0, -3.45, 0.0, 
                             7.07, 0.0, -64.4, 0.0,
                             52, 0.0); //CA1_Quadrilaminar
                             
sim.setNeuronParameters(CA1_Radiatum, 194.0, 0.0, 3.34, 0.0,
                             -68.98, 0.0, -58.15, 0.0, 
                             0.011, 0.0, 14.89, 0.0, 
                             -8.59, 0.0, -68.03, 0.0,
                             20, 0.0);//CA1_Radiatum
                             
sim.setNeuronParameters(CA1_R_Receiving_Apical_Target, 92.0, 0.0, 0.67, 0.0,
                             -57.28, 0.0, -43.19, 0.0, 
                             0.027, 0.0, -9.29, 0.0, 
                             -6.34, 0.0, -46.58, 0.0,
                             142, 0.0);//CA1_R_Receiving_Apical_Target
                             
sim.setNeuronParameters(CA1_Schaffer_Collateral_Associated, 224.0, 0.0, 2.99, 0.0,
                             -75.31, 0.0, -64.86, 0.0, 
                             0.002, 0.0, 24.81, 0.0, 
                             0.53, 0.0, -67.72, 0.0,
                             34, 0.0);//CA1_Schaffer_Collateral_Associated
                             
sim.setNeuronParameters(CA1_SO_SO, 177.0, 0.0, 0.32, 0.0,
                             -77.24, 0.0, -54.22, 0.0, 
                             0.008, 0.0, 1.72, 0.0, 
                             -22, 0.0, -61.09, 0.0,
                             -5, 0.0);//CA1_SO_SO

sim.setNeuronParameters(CA1_Trilaminar, 38.0, 0.0, 0.16, 0.0,
                             -60.94, 0.0, -46.19, 0.0, 
                             0.004, 0.0, 2.72, 0.0, 
                             -0.92, 0.0, -55.34, 0.0,
                             -3, 0.0);//CA1_Trilaminar
                             
sim.setNeuronParameters(CA1_Radial_Trilaminar, 227.0, 0.0, 2.64, 0.0,
                             -57.87, 0.0, -37.93, 0.0, 
                             0.009, 0.0, 3.59, 0.0, 
                             4.77, 0.0, -45.87, 0.0,
                             2, 0.0);//CA1_Radial_Trilaminar
                             
                             
sim.connect(CA1_Pyramidal, CA1_Pyramidal, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.000423f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.473054473f, 0.0f);//P=00127150931137853f
                                       
sim.connect(CA1_Pyramidal, CA1_Axo_axonic, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00036f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.815288206f, 0.0f);//p=0.00108599914488327f
                                       
sim.connect(CA1_Pyramidal, CA1_Horizontal_Axo_axonic, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.000252f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.308152788f, 0.0f);//p=0.000756709636622332f
                                       
sim.connect(CA1_Pyramidal, CA1_Back_Projection, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00041f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.183249644f, 0.0f);//p=0.00123316404727436f
                                       
sim.connect(CA1_Pyramidal, CA1_Basket, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.0004f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.869561088f, 0.0f);//p=0.00120429985538339f
                                       
sim.connect(CA1_Pyramidal, CA1_Basket_CCK, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00035f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.750808378f, 0.0f);//p=0.00105830452844035f
                                       
sim.connect(CA1_Pyramidal, CA1_Horizontal_Basket, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00109f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.02478806f, 0.0f);//p=0.00329155784358381
                                       
sim.connect(CA1_Pyramidal, CA1_Bistratified, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00107669491436201f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 3.281611994f, 0.0f);//p=0.00107669491436201
                                       
sim.connect(CA1_Pyramidal, CA1_Ivy, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00036f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.686238357f, 0.0f);//p=0.000933311676572734
                                       
sim.connect(CA1_Pyramidal, CA1_OLM, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00045f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.770407646f, 0.0f);//p=0.00135044860692346
                                       
sim.connect(CA1_Pyramidal, CA1_Recurrent_O_LM, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00106f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.808726221f, 0.0f);//p=0.00332097488397586
                                       
sim.connect(CA1_Pyramidal, CA1_O_LMR, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00036f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.572405696f, 0.0f);//p=0.00108152229447178
                                       
sim.connect(CA1_Pyramidal, CA1_Oriens_Alveus, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.0003f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.334971075f, 0.0f);//p=0.000907363613184553
                                       
sim.connect(CA1_Pyramidal, CA1_Oriens_Bistratified, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00027f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.493830393f, 0.0f);//p=0.000832438843566096
                                       
sim.connect(CA1_Pyramidal, CA1_OR_LM, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00041f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.745239175f, 0.0f);//p=0.00124428830827416
                                       
sim.connect(CA1_Pyramidal, CA1_Perforant_Path_Associated_QuadD, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00029f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.965567683f, 0.0f);//p=0.000876321577096939
                                       
sim.connect(CA1_Pyramidal, CA1_Quadrilaminar, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00036f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.371483576f, 0.0f);//p=0.00109248806828132
                                       
sim.connect(CA1_Pyramidal, CA1_SO_SO, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00083f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.355214118f, 0.0f);//p=0.00248761386943741
                                       
sim.connect(CA1_Pyramidal, CA1_Trilaminar, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00072f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.306303671f, 0.0f);//p=0.00217744729840552
                                       
sim.connect(CA1_Pyramidal, CA1_Radial_Trilaminar, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00029f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.490477376f, 0.0f);//p=0.00086410217295918
                                          
                                          
                                       
sim.connect(CA1_Radiatum_Giant, CA1_Pyramidal, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00104346352110085f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.655173699f, 0.0f);
                                       
sim.connect(CA1_Radiatum_Giant, CA1_Axo_axonic, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00079565788498559f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.99431849f, 0.0f);
                                       
sim.connect(CA1_Radiatum_Giant, CA1_Horizontal_Axo_axonic, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.000404292063184485f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.442647868f, 0.0f);
                                       
sim.connect(CA1_Radiatum_Giant, CA1_Back_Projection, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.000767424102694258f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.547036443f, 0.0f);
                                       
sim.connect(CA1_Radiatum_Giant, CA1_Basket, "random", RangeWeight(0.0f, 0.65f, 1.65f), 0.000734746918248041f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.061179756f, 0.0f);
                                       
sim.connect(CA1_Radiatum_Giant, CA1_Basket_CCK, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.000637916915866454f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.567727407f, 0.0f);
                                       
sim.connect(CA1_Radiatum_Giant, CA1_Horizontal_Basket, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00128865455247373f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.431148109f, 0.0f);
                                       
sim.connect(CA1_Radiatum_Giant, CA1_Bistratified, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.000557508443863263f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.567261924f, 0.0f);
                                       
sim.connect(CA1_Radiatum_Giant, CA1_Ivy, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.000621359799053533f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.758382851f, 0.0f);
                                       
sim.connect(CA1_Radiatum_Giant, CA1_OLM, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00112482628826848f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.111359644f, 0.0f);
                                       
sim.connect(CA1_Radiatum_Giant, CA1_Recurrent_O_LM, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00212675498927006f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.54009769f, 0.0f);
                                       
sim.connect(CA1_Radiatum_Giant, CA1_O_LMR, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.000862936946248948f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.660111909f, 0.0f);
                                       
sim.connect(CA1_Radiatum_Giant, CA1_Oriens_Alveus, "random", RangeWeight(0.0f, 0.65f, 1.65f), 0.000481559617927507f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.142741525f, 0.0f);
                                       
sim.connect(CA1_Radiatum_Giant, CA1_Oriens_Bistratified, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.000425416625096541f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.687214907f, 0.0f);
                                       
sim.connect(CA1_Radiatum_Giant, CA1_OR_LM, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.000825342995844802f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.540661646f, 0.0f);
                                       
sim.connect(CA1_Radiatum_Giant, CA1_Perforant_Path_Associated_QuadD, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.000429989070422132f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.471995564f, 0.0f);
                                       
sim.connect(CA1_Radiatum_Giant, CA1_Quadrilaminar, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.000516924033963639f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.628518636f, 0.0f);
                                       
sim.connect(CA1_Radiatum_Giant, CA1_SO_SO, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00151011877793738f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.972333716f, 0.0f);
                                       
sim.connect(CA1_Radiatum_Giant, CA1_Trilaminar, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00163474369573346f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.415044453f, 0.0f);
                                       
sim.connect(CA1_Radiatum_Giant, CA1_Radial_Trilaminar, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.000395630209256037f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.536494845f, 0.0f);
                                          
                                          
// no probability data at Hippo.org,  let p = 0.0001 //  
                                    
sim.connect(CA1_Axo_axonic, CA1_Pyramidal, "random", RangeWeight(0.0f, 0.65f, 1.65f), 0.0001f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.081976802f, 0.0f);
                                       
sim.connect(CA1_Axo_axonic, CA1_Radiatum_Giant, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.0001f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.552656079f, 0.0f);
                                       
sim.connect(CA1_Horizontal_Axo_axonic, CA1_Pyramidal, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.0001f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.360315289f, 0.0f);

sim.connect(CA1_Horizontal_Axo_axonic, CA1_Radiatum_Giant, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.0001f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.815288206f, 0.0f);

// no probability data at Hippo.org,  let p =0.0001 //                                                                         
                                          
                                       
sim.connect(CA1_Back_Projection, CA1_Pyramidal, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.0123261366098635f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.308152788f, 0.0f);
                                       
sim.connect(CA1_Back_Projection, CA1_Radiatum_Giant, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.005450336419487f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.183249644f, 0.0f);
                                       
sim.connect(CA1_Back_Projection, CA1_Axo_axonic, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.0124140043779388f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.869561088f, 0.0f);
                                       
sim.connect(CA1_Back_Projection, CA1_Horizontal_Axo_axonic, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00194716825989726f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.750808378f, 0.0f);
                                       
sim.connect(CA1_Back_Projection, CA1_Back_Projection, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00607096615924573f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.02478806f, 0.0f);
                                       
sim.connect(CA1_Back_Projection, CA1_Basket, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.0120185702073015f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 3.281611994f, 0.0f);
                                       
sim.connect(CA1_Back_Projection, CA1_Basket_CCK, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.0129441618004567f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.686238357f, 0.0f);
                                       
sim.connect(CA1_Back_Projection, CA1_Horizontal_Basket, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00658567348875283f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.770407646f, 0.0f);
                                       
sim.connect(CA1_Back_Projection, CA1_Bistratified, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00916411450501508f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.808726221f, 0.0f);
                                       
sim.connect(CA1_Back_Projection, CA1_Ivy, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.0085564607723404f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.572405696f, 0.0f);
                                       
sim.connect(CA1_Back_Projection, CA1_LMR, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00399342546784309f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.334971075f, 0.0f);
                                       
sim.connect(CA1_Back_Projection, CA1_Neurogliaform, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00299289213621645f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.493830393f, 0.0f);
                                       
sim.connect(CA1_Back_Projection, CA1_Neurogliaform_Projecting, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00215572620712745f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.745239175f, 0.0f);
                                       
sim.connect(CA1_Back_Projection, CA1_OLM, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.002871429796372f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.965567683f, 0.0f);
                                       
sim.connect(CA1_Back_Projection, CA1_Recurrent_O_LM, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00535274785698602f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.371483576f, 0.0f);
                                       
sim.connect(CA1_Back_Projection, CA1_O_LMR, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.0025252862078986f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.355214118f, 0.0f);
                                       
sim.connect(CA1_Back_Projection, CA1_Oriens_Alveus, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.011523828324261f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.306303671f, 0.0f);
                                       
sim.connect(CA1_Back_Projection, CA1_Oriens_Bistratified, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.0020632653718241f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.490477376f, 0.0f);
                                       
sim.connect(CA1_Back_Projection, CA1_OR_LM, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00666124723698879f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.655173699f, 0.0f);
                                       
sim.connect(CA1_Back_Projection, CA1_Perforant_Path_Associated, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00514853199335474f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.99431849f, 0.0f);
                                       
sim.connect(CA1_Back_Projection, CA1_Perforant_Path_Associated_QuadD, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.0154783056682552f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.442647868f, 0.0f);
                                       
sim.connect(CA1_Back_Projection, CA1_Quadrilaminar, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.0133129638519197f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.547036443f, 0.0f);
                                       
sim.connect(CA1_Back_Projection, CA1_Radiatum, "random", RangeWeight(0.0f, 0.65f, 1.65f), 0.00217527373084303f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.061179756f, 0.0f);
                                       
sim.connect(CA1_Back_Projection, CA1_R_Receiving_Apical_Target, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00268436548507933f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.567727407f, 0.0f);
                                       
sim.connect(CA1_Back_Projection, CA1_Schaffer_Collateral_Associated, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00498575384118393f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.431148109f, 0.0f);
                                       
sim.connect(CA1_Back_Projection, CA1_SO_SO, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.0043619346009599f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.567261924f, 0.0f);
                                       
sim.connect(CA1_Back_Projection, CA1_Trilaminar, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00386910645816496f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.758382851f, 0.0f);
                                       
sim.connect(CA1_Back_Projection, CA1_Radial_Trilaminar, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.0114996845880838f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.111359644f, 0.0f);//
                                          
                                          
// no probability data at Hippo.org,  let p = 0.0001 //  
                                   
sim.connect(CA1_Basket, CA1_Pyramidal, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.0001f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.54009769f, 0.0f);
                                       
sim.connect(CA1_Basket, CA1_Radiatum_Giant, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.0001f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.660111909f, 0.0f);
                                       
sim.connect(CA1_Basket, CA1_Axo_axonic, "random", RangeWeight(0.0f, 0.65f, 1.65f), 0.0001f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.142741525f, 0.0f);
                                       
sim.connect(CA1_Basket, CA1_Basket, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.0001f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.687214907f, 0.0f);
                                       
sim.connect(CA1_Basket, CA1_Basket_CCK, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.0001f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.540661646f, 0.0f);
                                       
sim.connect(CA1_Basket, CA1_Horizontal_Basket, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.0001f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.471995564f, 0.0f);
                                       
sim.connect(CA1_Basket, CA1_Bistratified, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.0001f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.628518636f, 0.0f);
                                       
sim.connect(CA1_Basket, CA1_Ivy, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.0001f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.972333716f, 0.0f);
                                       
sim.connect(CA1_Basket, CA1_OR_LM, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.0001f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.415044453f, 0.0f);
                                       
sim.connect(CA1_Basket, CA1_Radial_Trilaminar, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.0001f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.536494845f, 0.0f);
                                       
sim.connect(CA1_Basket_CCK, CA1_Pyramidal, "random", RangeWeight(0.0f, 0.65f, 1.65f), 0.0001f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.081976802f, 0.0f);
                                       
sim.connect(CA1_Basket_CCK, CA1_Radiatum_Giant, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.0001f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.552656079f, 0.0f);
                                       
sim.connect(CA1_Basket_CCK, CA1_Axo_axonic, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.0001f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.360315289f, 0.0f);

sim.connect(CA1_Basket_CCK, CA1_Basket, "random", RangeWeight(0.0f, 1.25f, 2.25f), 0.0001f,
                                      RangeDelay(1/*,2*/), RadiusRF(-1.0), SYN_PLASTIC, 0.874424964f, 0.0f);
                            
sim.connect(CA1_Basket_CCK, CA1_Basket_CCK, "random", RangeWeight(0.0f, 0.7f, 1.7f), 0.0001f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.932621138f, 0.0f);
                                   
sim.connect(CA1_Basket_CCK, CA1_Horizontal_Basket, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.0001f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.172460639f, 0.0f);
                                   
sim.connect(CA1_Basket_CCK, CA1_Bistratified, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.0001f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.847532877f, 0.0f);
                                   
sim.connect(CA1_Basket_CCK, CA1_Ivy, "random", RangeWeight(0.0f, 0.7f, 1.7f), 0.0001f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.883682094f, 0.0f);
                                   
sim.connect(CA1_Basket_CCK, CA1_OR_LM, "random", RangeWeight(0.0f, 1.35f, 2.35f), 0.0001f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.314331038f, 0.0f);
                                   
sim.connect(CA1_Basket_CCK, CA1_Radial_Trilaminar, "random", RangeWeight(0.0f, 1.25f, 2.25f), 0.0001f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.88025265f, 0.0f);
                                   
sim.connect(CA1_Horizontal_Basket, CA1_Pyramidal, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.0001f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.553062478f, 0.0f);
                                      
sim.connect(CA1_Horizontal_Basket, CA1_Radiatum_Giant, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.0001f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.111359644f, 0.0f);
                                       
sim.connect(CA1_Horizontal_Basket, CA1_Axo_axonic, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.0001f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.54009769f, 0.0f);
                                       
sim.connect(CA1_Horizontal_Basket, CA1_Basket, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.0001f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.660111909f, 0.0f);
                                       
sim.connect(CA1_Horizontal_Basket, CA1_Basket_CCK, "random", RangeWeight(0.0f, 0.65f, 1.65f), 0.0001f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.142741525f, 0.0f);
                                       
sim.connect(CA1_Horizontal_Basket, CA1_Horizontal_Basket, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.0001f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.687214907f, 0.0f);
                                       
sim.connect(CA1_Horizontal_Basket, CA1_Bistratified, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.0001f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.540661646f, 0.0f);
                                       
sim.connect(CA1_Horizontal_Basket, CA1_Ivy, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.0001f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.471995564f, 0.0f);
                                       
sim.connect(CA1_Horizontal_Basket, CA1_OR_LM, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.0001f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.628518636f, 0.0f);
                                       
sim.connect(CA1_Horizontal_Basket, CA1_Radial_Trilaminar, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.0001f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.972333716f, 0.0f);

// no probability data at Hippo.org,  let p = 0.0001 //                                         
                                          
                                       
sim.connect(CA1_Bistratified, CA1_Pyramidal, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00708185132213423f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.415044453f, 0.0f);
                                       
sim.connect(CA1_Bistratified, CA1_Radiatum_Giant, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00336064587332807f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.536494845f, 0.0f);
                                       
sim.connect(CA1_Bistratified, CA1_Axo_axonic, "random", RangeWeight(0.0f, 0.65f, 1.65f), 0.00684438865001624f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.081976802f, 0.0f);
                                       
sim.connect(CA1_Bistratified, CA1_Horizontal_Axo_axonic, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00149959689061685f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.552656079f, 0.0f);
                                       
sim.connect(CA1_Bistratified, CA1_Back_Projection, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00338774260613161f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.360315289f, 0.0f);

sim.connect(CA1_Bistratified, CA1_Basket, "random", RangeWeight(0.0f, 1.25f, 2.25f), 0.00713145106585477f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.874424964f, 0.0f);
                            
sim.connect(CA1_Bistratified, CA1_Basket_CCK, "random", RangeWeight(0.0f, 0.7f, 1.7f), 0.0072641968222481f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.932621138f, 0.0f);
                                   
sim.connect(CA1_Bistratified, CA1_Horizontal_Basket, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00546324326079072f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.172460639f, 0.0f);
                                   
sim.connect(CA1_Bistratified, CA1_Bistratified, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00725813414415121f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.847532877f, 0.0f);
                                   
sim.connect(CA1_Bistratified, CA1_Ivy, "random", RangeWeight(0.0f, 0.7f, 1.7f), 0.00629577208596343f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.883682094f, 0.0f);
                                   
sim.connect(CA1_Bistratified, CA1_LMR, "random", RangeWeight(0.0f, 1.35f, 2.35f), 0.00210058926497569f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.314331038f, 0.0f);
                                   
sim.connect(CA1_Bistratified, CA1_OLM, "random", RangeWeight(0.0f, 1.25f, 2.25f), 0.00234269237859618f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.88025265f, 0.0f);
                                   
sim.connect(CA1_Bistratified, CA1_Recurrent_O_LM, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00468883914114048f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.553062478f, 0.0f);

sim.connect(CA1_Bistratified, CA1_O_LMR, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00201549736723949f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.660111909f, 0.0f);
                                       
sim.connect(CA1_Bistratified, CA1_Oriens_Alveus, "random", RangeWeight(0.0f, 0.65f, 1.65f), 0.00640201217689129f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.142741525f, 0.0f);
                                       
sim.connect(CA1_Bistratified, CA1_Oriens_Bistratified, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00160113590011146f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.687214907f, 0.0f);
                                       
sim.connect(CA1_Bistratified, CA1_OR_LM, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00717105626034708f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.540661646f, 0.0f);
                                       
sim.connect(CA1_Bistratified, CA1_Perforant_Path_Associated, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00291295757966647f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.471995564f, 0.0f);
                                       
sim.connect(CA1_Bistratified, CA1_Perforant_Path_Associated_QuadD, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00959169695685757f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.628518636f, 0.0f);
                                       
sim.connect(CA1_Bistratified, CA1_Quadrilaminar, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00775762455693906f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.972333716f, 0.0f);
                                       
sim.connect(CA1_Bistratified, CA1_Radiatum, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00316362347972443f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.415044453f, 0.0f);
                                       
sim.connect(CA1_Bistratified, CA1_R_Receiving_Apical_Target, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.0036930414663524f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.536494845f, 0.0f);
                                       
sim.connect(CA1_Bistratified, CA1_Schaffer_Collateral_Associated, "random", RangeWeight(0.0f, 0.65f, 1.65f), 0.00350851800097895f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.081976802f, 0.0f);
                                       
sim.connect(CA1_Bistratified, CA1_SO_SO, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00373052991882894f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.552656079f, 0.0f);
                                       
sim.connect(CA1_Bistratified, CA1_Trilaminar, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00329533970173145f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.360315289f, 0.0f);

sim.connect(CA1_Bistratified, CA1_Radial_Trilaminar, "random", RangeWeight(0.0f, 1.25f, 2.25f), 0.00653926632860379f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.874424964f, 0.0f);
                                      
sim.connect(CA1_Ivy, CA1_Pyramidal, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00587955614373247f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.415044453f, 0.0f);
                                       
sim.connect(CA1_Ivy, CA1_Radiatum_Giant, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00135915315184043f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.536494845f, 0.0f);
                                       
sim.connect(CA1_Ivy, CA1_Axo_axonic, "random", RangeWeight(0.0f, 0.65f, 1.65f), 0.00571617996350559f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.081976802f, 0.0f);
                                       
sim.connect(CA1_Ivy, CA1_Horizontal_Axo_axonic, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00187453225948097f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.552656079f, 0.0f);
                                       
sim.connect(CA1_Ivy, CA1_Back_Projection, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00449699783083579f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.360315289f, 0.0f);

sim.connect(CA1_Ivy, CA1_Basket, "random", RangeWeight(0.0f, 1.25f, 2.25f), 0.00604341879019321f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.874424964f, 0.0f);
                            
sim.connect(CA1_Ivy, CA1_Basket_CCK, "random", RangeWeight(0.0f, 0.7f, 1.7f), 0.00634356900318466f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.932621138f, 0.0f);
                                   
sim.connect(CA1_Ivy, CA1_Horizontal_Basket, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00729236041814029f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.172460639f, 0.0f);
                                   
sim.connect(CA1_Ivy, CA1_Bistratified, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00634687158994051f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.847532877f, 0.0f);
                                   
sim.connect(CA1_Ivy, CA1_Ivy, "random", RangeWeight(0.0f, 0.7f, 1.7f), 0.00576232259745834f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.883682094f, 0.0f);
                                   
sim.connect(CA1_Ivy, CA1_LMR, "random", RangeWeight(0.0f, 1.35f, 2.35f), 0.000617246713539798f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.314331038f, 0.0f);
                                   
sim.connect(CA1_Ivy, CA1_OLM, "random", RangeWeight(0.0f, 1.25f, 2.25f), 0.00252018830072697f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.88025265f, 0.0f);
                                   
sim.connect(CA1_Ivy, CA1_Recurrent_O_LM, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00513873253348295f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.553062478f, 0.0f);

sim.connect(CA1_Ivy, CA1_O_LMR, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.0022128214723015f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.660111909f, 0.0f);
                                       
sim.connect(CA1_Ivy, CA1_Oriens_Alveus, "random", RangeWeight(0.0f, 0.65f, 1.65f), 0.00544446367290896f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.142741525f, 0.0f);
                                       
sim.connect(CA1_Ivy, CA1_Oriens_Bistratified, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00201489732396098f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.687214907f, 0.0f);
                                       
sim.connect(CA1_Ivy, CA1_OR_LM, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.0051376033121665f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.540661646f, 0.0f);
                                       
sim.connect(CA1_Ivy, CA1_Perforant_Path_Associated, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00105473621562512f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.471995564f, 0.0f);
                                       
sim.connect(CA1_Ivy, CA1_Perforant_Path_Associated_QuadD, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00830488605853363f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.628518636f, 0.0f);
                                       
sim.connect(CA1_Ivy, CA1_Quadrilaminar, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00672090102461175f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.972333716f, 0.0f);
                                       
sim.connect(CA1_Ivy, CA1_Radiatum, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00121125277476474f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.415044453f, 0.0f);
                                       
sim.connect(CA1_Ivy, CA1_R_Receiving_Apical_Target, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00162769785162497f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.536494845f, 0.0f);
                                       
sim.connect(CA1_Ivy, CA1_Schaffer_Collateral_Associated, "random", RangeWeight(0.0f, 0.65f, 1.65f), 0.00143241997569509f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.081976802f, 0.0f);
                                       
sim.connect(CA1_Ivy, CA1_SO_SO, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00417902597485542f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.552656079f, 0.0f);
                                       
sim.connect(CA1_Ivy, CA1_Trilaminar, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00354048890270619f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.360315289f, 0.0f);

sim.connect(CA1_Ivy, CA1_Radial_Trilaminar, "random", RangeWeight(0.0f, 1.25f, 2.25f), 0.00573376919110213f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.874424964f,0.0f); 
                                          
                                          
                                                                                                                             
sim.connect(CA1_LMR, CA1_Pyramidal, "random", RangeWeight(0.0f, 0.7f, 1.7f), 0.00409992715348617f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.932621138f, 0.0f);
                                   
sim.connect(CA1_LMR, CA1_Radiatum_Giant, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00459566690360535f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.172460639f, 0.0f);
                                   
sim.connect(CA1_LMR, CA1_Axo_axonic, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00398653230344581f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.847532877f, 0.0f);
                                   
sim.connect(CA1_LMR, CA1_Basket, "random", RangeWeight(0.0f, 0.7f, 1.7f), 0.00370219121560366f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.883682094f, 0.0f);
                                   
sim.connect(CA1_LMR, CA1_Basket_CCK, "random", RangeWeight(0.0f, 1.35f, 2.35f), 0.00411684395586997f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.314331038f, 0.0f);
                                   
sim.connect(CA1_LMR, CA1_Bistratified, "random", RangeWeight(0.0f, 1.25f, 2.25f), 0.00267138910950126f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.88025265f, 0.0f);
                                   
sim.connect(CA1_LMR, CA1_Ivy, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00182175876241352f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.553062478f, 0.0f); 
                                                                                                       
sim.connect(CA1_LMR, CA1_LMR, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00332141339610458f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.54009769f, 0.0f);
                                       
sim.connect(CA1_LMR, CA1_Neurogliaform, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00133663639889658f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.660111909f, 0.0f);
                                       
sim.connect(CA1_LMR, CA1_Neurogliaform_Projecting, "random", RangeWeight(0.0f, 0.65f, 1.65f), 0.00108859638418279f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.142741525f, 0.0f);
                                       
sim.connect(CA1_LMR, CA1_Oriens_Alveus, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00368280511830021f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.687214907f, 0.0f);
                                       
sim.connect(CA1_LMR, CA1_OR_LM, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00405195139316016f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.540661646f, 0.0f);
                                       
sim.connect(CA1_LMR, CA1_Perforant_Path_Associated, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00427710297763939f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.471995564f, 0.0f);
                                       
sim.connect(CA1_LMR, CA1_Perforant_Path_Associated_QuadD, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00744160201846244f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.628518636f, 0.0f);
                                       
sim.connect(CA1_LMR, CA1_Quadrilaminar, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00500828760520177f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.972333716f, 0.0f);
                                       
sim.connect(CA1_LMR, CA1_Radiatum, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00297890506639086f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.415044453f, 0.0f);
                                       
sim.connect(CA1_LMR, CA1_R_Receiving_Apical_Target, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00325030601588938f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.536494845f, 0.0f);
                                       
sim.connect(CA1_LMR, CA1_Schaffer_Collateral_Associated, "random", RangeWeight(0.0f, 0.65f, 1.65f), 0.00455043820974321f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.081976802f, 0.0f);
                                       
sim.connect(CA1_LMR, CA1_Radial_Trilaminar, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00395249776338002f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.552656079f, 0.0f);
                                          
                                          
                                          
sim.connect(CA1_Neurogliaform, CA1_Pyramidal, "random", RangeWeight(0.0f, 0.7f, 1.7f), 0.00170651280450562f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.932621138f, 0.0f);
                                   
sim.connect(CA1_Neurogliaform, CA1_Radiatum_Giant, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00182329821352555f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.172460639f, 0.0f);
                                   
sim.connect(CA1_Neurogliaform, CA1_Axo_axonic, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00183903233259064f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.847532877f, 0.0f);
                                   
sim.connect(CA1_Neurogliaform, CA1_Basket, "random", RangeWeight(0.0f, 0.7f, 1.7f), 0.00138239104136894f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.883682094f, 0.0f);
                                   
sim.connect(CA1_Neurogliaform, CA1_Basket_CCK, "random", RangeWeight(0.0f, 1.35f, 2.35f), 0.00176764993113887f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.314331038f, 0.0f);
                                       
sim.connect(CA1_Neurogliaform, CA1_LMR, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00143268175427646f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.360315289f, 0.0f);

sim.connect(CA1_Neurogliaform, CA1_Neurogliaform, "random", RangeWeight(0.0f, 1.25f, 2.25f), 0.00175104714566431f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.874424964f, 0.0f);
                            
sim.connect(CA1_Neurogliaform, CA1_Neurogliaform_Projecting, "random", RangeWeight(0.0f, 0.7f, 1.7f), 0.00162259353465143f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.932621138f, 0.0f);
                                   
sim.connect(CA1_Neurogliaform, CA1_Oriens_Alveus, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00155634907881996f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.172460639f, 0.0f);
                                   
sim.connect(CA1_Neurogliaform, CA1_Perforant_Path_Associated, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00191682696338779f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.847532877f, 0.0f);
                                   
sim.connect(CA1_Neurogliaform, CA1_Perforant_Path_Associated_QuadD, "random", RangeWeight(0.0f, 0.7f, 1.7f),  0.0024000155916789f, 
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.883682094f, 0.0f);
                                   
sim.connect(CA1_Neurogliaform, CA1_Quadrilaminar, "random", RangeWeight(0.0f, 1.35f, 2.35f), 0.00196522873462556f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.314331038f, 0.0f);
                                   
sim.connect(CA1_Neurogliaform, CA1_Schaffer_Collateral_Associated, "random", RangeWeight(0.0f, 1.25f, 2.25f), 0.00143209695148804f, 
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.88025265f, 0.0f);
                                   
sim.connect(CA1_Neurogliaform, CA1_Radial_Trilaminar, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00157764456573272f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.553062478f, 0.0f);
                                      
                                      
                                                                                                             
sim.connect(CA1_Neurogliaform_Projecting, CA1_Pyramidal, "random", RangeWeight(0.0f, 0.7f, 1.7f), 0.00144020857040616f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.932621138f, 0.0f);
                                   
sim.connect(CA1_Neurogliaform_Projecting, CA1_Radiatum_Giant, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00150840689114251f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.172460639f, 0.0f);
                                   
sim.connect(CA1_Neurogliaform_Projecting, CA1_Axo_axonic, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00159336025333933f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.847532877f, 0.0f);
                                   
sim.connect(CA1_Neurogliaform_Projecting, CA1_Basket, "random", RangeWeight(0.0f, 0.7f, 1.7f), 0.00112299880198418f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.883682094f, 0.0f);
                                   
sim.connect(CA1_Neurogliaform_Projecting, CA1_Basket_CCK, "random", RangeWeight(0.0f, 1.35f, 2.35f), 0.00151134464361701f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.314331038f, 0.0f);
                                       
sim.connect(CA1_Neurogliaform_Projecting, CA1_LMR, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00115556247925174f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.360315289f, 0.0f);

sim.connect(CA1_Neurogliaform_Projecting, CA1_Neurogliaform, "random", RangeWeight(0.0f, 1.25f, 2.25f), 0.00154909266413227f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.874424964f, 0.0f);
                            
sim.connect(CA1_Neurogliaform_Projecting, CA1_Neurogliaform_Projecting, "random", RangeWeight(0.0f, 0.7f, 1.7f),0.001353301218044f,                  RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.932621138f, 0.0f);
                                   
sim.connect(CA1_Neurogliaform_Projecting, CA1_Oriens_Alveus, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00128506666524452f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.172460639f, 0.0f);
                                   
sim.connect(CA1_Neurogliaform_Projecting, CA1_Perforant_Path_Associated, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00159213562668292f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.847532877f, 0.0f);
                                   
sim.connect(CA1_Neurogliaform_Projecting, CA1_Perforant_Path_Associated_QuadD, "random", RangeWeight(0.0f, 0.7f, 1.7f),  0.0019820777169871f, 
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.883682094f, 0.0f);
                                   
sim.connect(CA1_Neurogliaform_Projecting, CA1_Quadrilaminar, "random", RangeWeight(0.0f, 1.35f, 2.35f), 0.00161509388613911f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.314331038f, 0.0f);
                                   
sim.connect(CA1_Neurogliaform_Projecting, CA1_Schaffer_Collateral_Associated, "random", RangeWeight(0.0f, 1.25f, 2.25f), 0.00111275028836221f, 
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.88025265f, 0.0f);
                                   
sim.connect(CA1_Neurogliaform_Projecting, CA1_Radial_Trilaminar, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00118259312511459f, 
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.553062478f,0.0f);
                                      
                                      
                                                                      
                                                                           
sim.connect(CA1_OLM, CA1_Pyramidal, "random", RangeWeight(0.0f, 0.7f, 1.7f), 0.00191656265396489f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.932621138f, 0.0f);
                                   
sim.connect(CA1_OLM, CA1_Radiatum_Giant, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00201070486909316f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.172460639f, 0.0f);
                                   
sim.connect(CA1_OLM, CA1_Axo_axonic, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.0020662606349795f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.847532877f, 0.0f);
                                   
sim.connect(CA1_OLM, CA1_Basket, "random", RangeWeight(0.0f, 0.7f, 1.7f), 0.00157745106952311f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.883682094f, 0.0f);
                                   
sim.connect(CA1_OLM, CA1_Basket_CCK, "random", RangeWeight(0.0f, 1.35f, 2.35f), 0.00198629813258743f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.314331038f, 0.0f);
                                       
sim.connect(CA1_OLM, CA1_LMR, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00161822392570387f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.360315289f, 0.0f);

sim.connect(CA1_OLM, CA1_Neurogliaform, "random", RangeWeight(0.0f, 1.25f, 2.25f), 0.00200108476925864f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.874424964f, 0.0f);
                            
sim.connect(CA1_OLM, CA1_Neurogliaform_Projecting, "random", RangeWeight(0.0f, 0.7f, 1.7f),0.00182648758337622f,                  
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.932621138f, 0.0f);
                                   
sim.connect(CA1_OLM, CA1_Oriens_Alveus, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00175501191798299f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.172460639f, 0.0f);
                                   
sim.connect(CA1_OLM, CA1_Perforant_Path_Associated, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00210382446661083f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.847532877f, 0.0f);
                                   
sim.connect(CA1_OLM, CA1_Perforant_Path_Associated_QuadD, "random", RangeWeight(0.0f, 0.7f, 1.7f),  0.00256519084109652f,    
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.883682094f, 0.0f);
                                   
sim.connect(CA1_OLM, CA1_Quadrilaminar, "random", RangeWeight(0.0f, 1.35f, 2.35f), 0.0021411794085423f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.314331038f, 0.0f);
                                   
sim.connect(CA1_OLM, CA1_Schaffer_Collateral_Associated, "random", RangeWeight(0.0f, 1.25f, 2.25f), 0.00158598906087992f,  
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.88025265f, 0.0f);
                                   
sim.connect(CA1_OLM, CA1_Radial_Trilaminar, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00169466809614748f, 
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.553062478f, 0.0f);  
                                      
                                            
                                                                     
sim.connect(CA1_Recurrent_O_LM, CA1_Pyramidal, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00874128732702073f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.308152788f, 0.0f);
                                       
sim.connect(CA1_Recurrent_O_LM, CA1_Radiatum_Giant, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00554933319745454f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.183249644f, 0.0f);
                                       
sim.connect(CA1_Recurrent_O_LM, CA1_Axo_axonic, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00889796007109755f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.869561088f, 0.0f);
                                       
sim.connect(CA1_Recurrent_O_LM, CA1_Horizontal_Axo_axonic, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00155924492266212f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.750808378f, 0.0f);
                                       
sim.connect(CA1_Recurrent_O_LM, CA1_Back_Projection, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00220166823393697f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.02478806f, 0.0f);
                                       
sim.connect(CA1_Recurrent_O_LM, CA1_Basket, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00818329277148988f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 3.281611994f, 0.0f);
                                       
sim.connect(CA1_Recurrent_O_LM, CA1_Basket_CCK, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00878223289510293f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.686238357f, 0.0f);
                                       
sim.connect(CA1_Recurrent_O_LM, CA1_Horizontal_Basket, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00596881823499961f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.770407646f, 0.0f);
                                       
sim.connect(CA1_Recurrent_O_LM, CA1_Bistratified, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00202911110466597f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.808726221f, 0.0f);
                                       
sim.connect(CA1_Recurrent_O_LM, CA1_Ivy, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00180556116517771f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.572405696f, 0.0f);
                                       
sim.connect(CA1_Recurrent_O_LM, CA1_LMR, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00487186827875862f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.334971075f, 0.0f);
                                       
sim.connect(CA1_Recurrent_O_LM, CA1_Neurogliaform, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00654653816258199f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.493830393f, 0.0f);
                                       
sim.connect(CA1_Recurrent_O_LM, CA1_Neurogliaform_Projecting, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00549895698915903f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.745239175f, 0.0f);
                                       
sim.connect(CA1_Recurrent_O_LM, CA1_OLM, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00230522575357161f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.965567683f, 0.0f);
                                       
sim.connect(CA1_Recurrent_O_LM, CA1_Recurrent_O_LM, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00474888508413262f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.371483576f, 0.0f);
                                       
sim.connect(CA1_Recurrent_O_LM, CA1_O_LMR, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00199052894460372f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.355214118f, 0.0f);
                                       
sim.connect(CA1_Recurrent_O_LM, CA1_Oriens_Alveus, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00815134335714462f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.306303671f, 0.0f);
                                       
sim.connect(CA1_Recurrent_O_LM, CA1_Oriens_Bistratified, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.0016738689711423f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.490477376f, 0.0f);
                                       
sim.connect(CA1_Recurrent_O_LM, CA1_OR_LM, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00220495615982929f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.655173699f, 0.0f);
                                       
sim.connect(CA1_Recurrent_O_LM, CA1_Perforant_Path_Associated, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00568814758225311f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.99431849f, 0.0f);
                                       
sim.connect(CA1_Recurrent_O_LM, CA1_Perforant_Path_Associated_QuadD, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00906213747585626f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.442647868f, 0.0f);
                                       
sim.connect(CA1_Recurrent_O_LM, CA1_Quadrilaminar, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00894039293669579f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.547036443f, 0.0f);
                                       
sim.connect(CA1_Recurrent_O_LM, CA1_Schaffer_Collateral_Associated, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00438606546425501f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.431148109f, 0.0f);
                                       
sim.connect(CA1_Recurrent_O_LM, CA1_SO_SO, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00379471584968649f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.567261924f, 0.0f);
                                       
sim.connect(CA1_Recurrent_O_LM, CA1_Trilaminar, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00328038823279108f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.758382851f, 0.0f);
                                       
sim.connect(CA1_Recurrent_O_LM, CA1_Radial_Trilaminar, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00746424320844618f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.111359644f, 0.0f);



sim.connect(CA1_O_LMR, CA1_Pyramidal, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00239052911158688f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.308152788f, 0.0f);
                                       
sim.connect(CA1_O_LMR, CA1_Radiatum_Giant, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00282216515427635f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.183249644f, 0.0f);
                                       
sim.connect(CA1_O_LMR, CA1_Axo_axonic, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00227200617525924f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.869561088f, 0.0f);
                                                                                                                
sim.connect(CA1_O_LMR, CA1_Basket, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00201918087432018f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 3.281611994f, 0.0f);
                                       
sim.connect(CA1_O_LMR, CA1_Basket_CCK, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00235964220961026f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.686238357f, 0.0f);
                                       
sim.connect(CA1_O_LMR, CA1_Bistratified, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00104031358354639f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.808726221f, 0.0f);
                                       
sim.connect(CA1_O_LMR, CA1_Ivy, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.000546042902802468f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.572405696f, 0.0f);
                                       
sim.connect(CA1_O_LMR, CA1_LMR, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00167483408970214f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.334971075f, 0.0f);
                                       
sim.connect(CA1_O_LMR, CA1_Neurogliaform, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00106437047204088f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.493830393f, 0.0f);
                                       
sim.connect(CA1_O_LMR, CA1_Neurogliaform_Projecting, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.000883050925532757f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.745239175f, 0.0f);
                                       
sim.connect(CA1_O_LMR, CA1_Oriens_Alveus, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00198921517018579f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.306303671f, 0.0f);
                                       
sim.connect(CA1_O_LMR, CA1_OR_LM, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00227165749551949f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.655173699f, 0.0f);
                                       
sim.connect(CA1_O_LMR, CA1_Perforant_Path_Associated, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00255199357370528f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.99431849f, 0.0f);
                                       
sim.connect(CA1_O_LMR, CA1_Perforant_Path_Associated_QuadD, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00535330967736402f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.442647868f, 0.0f);
                                       
sim.connect(CA1_O_LMR, CA1_Quadrilaminar, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00302712140100103f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.547036443f, 0.0f);
                                       
sim.connect(CA1_O_LMR, CA1_Radiatum, "random", RangeWeight(0.0f, 0.65f, 1.65f), 0.0013135868342704f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.061179756f, 0.0f);
                                       
sim.connect(CA1_O_LMR, CA1_R_Receiving_Apical_Target, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00167699072777161f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.567727407f, 0.0f);
                                       
sim.connect(CA1_O_LMR, CA1_Schaffer_Collateral_Associated, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00269901393949445f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.431148109f, 0.0f);
                                                                            
sim.connect(CA1_O_LMR, CA1_Radial_Trilaminar, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00208267051354993f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.111359644f, 0.0f);
                                          
                                          

sim.connect(CA1_Oriens_Alveus, CA1_Pyramidal, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00264530036242438f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.308152788f, 0.0f);
                                       
sim.connect(CA1_Oriens_Alveus, CA1_Axo_axonic, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00265808542795631f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.869561088f, 0.0f);
                                       
sim.connect(CA1_Oriens_Alveus, CA1_Horizontal_Axo_axonic, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00122916254422089f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.750808378f, 0.0f);
                                       
sim.connect(CA1_Oriens_Alveus, CA1_Back_Projection, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00300189365763947f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.02478806f, 0.0f);
                                       
sim.connect(CA1_Oriens_Alveus, CA1_Basket, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00285879820067491f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 3.281611994f, 0.0f);
                                       
sim.connect(CA1_Oriens_Alveus, CA1_Basket_CCK, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00310653895369517f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.686238357f, 0.0f);
                                       
sim.connect(CA1_Oriens_Alveus, CA1_Horizontal_Basket, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00587346299020685f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.770407646f, 0.0f);
                                       
sim.connect(CA1_Oriens_Alveus, CA1_Bistratified, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00303832585408847f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.808726221f, 0.0f);
                                       
sim.connect(CA1_Oriens_Alveus, CA1_Ivy, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00304672424402041f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.572405696f, 0.0f);
                                       
sim.connect(CA1_Oriens_Alveus, CA1_OLM, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00176665721099433f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.965567683f, 0.0f);
                                       
sim.connect(CA1_Oriens_Alveus, CA1_Recurrent_O_LM, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00426824844359075f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.371483576f, 0.0f);
                                       
sim.connect(CA1_Oriens_Alveus, CA1_O_LMR, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00148047498453507f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.355214118f, 0.0f);
                                       
sim.connect(CA1_Oriens_Alveus, CA1_Oriens_Alveus, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00250379740516104f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.306303671f, 0.0f);
                                       
sim.connect(CA1_Oriens_Alveus, CA1_Oriens_Bistratified, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00135816328667481f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.490477376f, 0.0f);
                                       
sim.connect(CA1_Oriens_Alveus, CA1_OR_LM, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00174798119979968f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.655173699f, 0.0f);
                                       
sim.connect(CA1_Oriens_Alveus, CA1_Perforant_Path_Associated_QuadD, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00265420303127306f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.442647868f, 0.0f);
                                       
sim.connect(CA1_Oriens_Alveus, CA1_Quadrilaminar, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00302425502791336f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.547036443f, 0.0f);
                                       
sim.connect(CA1_Oriens_Alveus, CA1_SO_SO, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00334448329710534f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.567261924f, 0.0f);
                                       
sim.connect(CA1_Oriens_Alveus, CA1_Trilaminar, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00274874867714536f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.758382851f, 0.0f);
                                       
sim.connect(CA1_Oriens_Alveus, CA1_Radial_Trilaminar, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00270427211854362f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.111359644f, 0.0f);
                                          
                                          
                                      
sim.connect(CA1_Oriens_Bistratified, CA1_Pyramidal, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00252518946102431f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.308152788f, 0.0f);
                                       
sim.connect(CA1_Oriens_Bistratified, CA1_Radiatum_Giant, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.0016824360379859f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.183249644f, 0.0f);
                                       
sim.connect(CA1_Oriens_Bistratified, CA1_Axo_axonic, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00207361535106187f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.869561088f, 0.0f);
                                       
sim.connect(CA1_Oriens_Bistratified, CA1_Horizontal_Axo_axonic, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.000371584095797405f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.750808378f, 0.0f);
                                       
sim.connect(CA1_Oriens_Bistratified, CA1_Back_Projection, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.000721467691749744f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.02478806f, 0.0f);
                                       
sim.connect(CA1_Oriens_Bistratified, CA1_Basket, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00255531575263456f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 3.281611994f, 0.0f);
                                       
sim.connect(CA1_Oriens_Bistratified, CA1_Basket_CCK, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00226651443313341f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.686238357f, 0.0f);
                                       
sim.connect(CA1_Oriens_Bistratified, CA1_Horizontal_Basket, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00218616574863173f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.770407646f, 0.0f);
                                       
sim.connect(CA1_Oriens_Bistratified, CA1_Bistratified, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00238769712734698f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.808726221f, 0.0f);
                                       
sim.connect(CA1_Oriens_Bistratified, CA1_Ivy, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00141676179056526f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.572405696f, 0.0f);
                                       
sim.connect(CA1_Oriens_Bistratified, CA1_LMR, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.000798188816295564f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.334971075f, 0.0f);
                                       
sim.connect(CA1_Oriens_Bistratified, CA1_OLM, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00074731629952085f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.965567683f, 0.0f);
                                       
sim.connect(CA1_Oriens_Bistratified, CA1_Recurrent_O_LM, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00246707318366712f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.371483576f, 0.0f);
                                       
sim.connect(CA1_Oriens_Bistratified, CA1_O_LMR, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.000518298105864012f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.355214118f, 0.0f);
                                       
sim.connect(CA1_Oriens_Bistratified, CA1_Oriens_Alveus, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00202644514665084f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.306303671f, 0.0f);
                                       
sim.connect(CA1_Oriens_Bistratified, CA1_Oriens_Bistratified, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.000449311521702577f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.490477376f, 0.0f);
                                       
sim.connect(CA1_Oriens_Bistratified, CA1_OR_LM, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00380630441701268f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.655173699f, 0.0f);
                                       
sim.connect(CA1_Oriens_Bistratified, CA1_Perforant_Path_Associated, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00134626792869319f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.99431849f, 0.0f);
                                       
sim.connect(CA1_Oriens_Bistratified, CA1_Perforant_Path_Associated_QuadD, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00468529553132257f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.442647868f, 0.0f);
                                       
sim.connect(CA1_Oriens_Bistratified, CA1_Quadrilaminar, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00285120461071819f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.547036443f, 0.0f);
                                       
sim.connect(CA1_Oriens_Bistratified, CA1_Radiatum, "random", RangeWeight(0.0f, 0.65f, 1.65f), 0.00147470371167279f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.061179756f, 0.0f);
                                       
sim.connect(CA1_Oriens_Bistratified, CA1_R_Receiving_Apical_Target, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00202258221006035f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.567727407f, 0.0f);
                                       
sim.connect(CA1_Oriens_Bistratified, CA1_Schaffer_Collateral_Associated, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00171606547332947f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.431148109f, 0.0f);
                                       
sim.connect(CA1_Oriens_Bistratified, CA1_SO_SO, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00176059225904723f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.567261924f, 0.0f);
                                       
sim.connect(CA1_Oriens_Bistratified, CA1_Trilaminar, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00149814526150438f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.758382851f, 0.0f);
                                       
sim.connect(CA1_Oriens_Bistratified, CA1_Radial_Trilaminar, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00190810134063423f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.111359644f, 0.0f);              
                                          
                                                                   

sim.connect(CA1_OR_LM, CA1_Pyramidal, "random", RangeWeight(0.0f, 0.7f, 1.7f), 0.0011521126374151f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.932621138f, 0.0f);
                                   
sim.connect(CA1_OR_LM, CA1_Radiatum_Giant, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00124104152661674f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.172460639f, 0.0f);
                                   
sim.connect(CA1_OR_LM, CA1_Axo_axonic, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00128515625558056f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.847532877f, 0.0f);
                                   
sim.connect(CA1_OR_LM, CA1_Basket, "random", RangeWeight(0.0f, 0.7f, 1.7f), 0.000855743998250169f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.883682094f, 0.0f);
                                   
sim.connect(CA1_OR_LM, CA1_Basket_CCK, "random", RangeWeight(0.0f, 1.35f, 2.35f), 0.0012132349687346f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.314331038f, 0.0f);
                                       
sim.connect(CA1_OR_LM, CA1_LMR, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.000897845464010282f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.360315289f, 0.0f);

sim.connect(CA1_OR_LM, CA1_Neurogliaform, "random", RangeWeight(0.0f, 1.25f, 2.25f), 0.00121616467611074f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.874424964f, 0.0f);
                            
sim.connect(CA1_OR_LM, CA1_Neurogliaform_Projecting, "random", RangeWeight(0.0f, 0.7f, 1.7f),0.0010730207231403f,                  
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.932621138f, 0.0f);
                                   
sim.connect(CA1_OR_LM, CA1_Oriens_Alveus, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00101139177040943f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.172460639f, 0.0f);
                                   
sim.connect(CA1_OR_LM, CA1_Perforant_Path_Associated, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00132306587821573f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.847532877f, 0.0f);
                                   
sim.connect(CA1_OR_LM, CA1_Perforant_Path_Associated_QuadD, "random", RangeWeight(0.0f, 0.7f, 1.7f),  0.00171889158468496f,    
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.883682094f, 0.0f);
                                   
sim.connect(CA1_OR_LM, CA1_Quadrilaminar, "random", RangeWeight(0.0f, 1.35f, 2.35f), 0.00135497593090017f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.314331038f, 0.0f);
                                   
sim.connect(CA1_OR_LM, CA1_Schaffer_Collateral_Associated, "random", RangeWeight(0.0f, 1.25f, 2.25f), 0.000887248579519717f,  
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.88025265f, 0.0f);
                                   
sim.connect(CA1_OR_LM, CA1_Radial_Trilaminar, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.000985607785945252f, 
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.553062478f, 0.0f);  
                                      
                                      
                                   
sim.connect(CA1_Perforant_Path_Associated, CA1_Pyramidal, "random", RangeWeight(0.0f, 0.7f, 1.7f), 0.00551428603148873f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.932621138f, 0.0f);
                                   
sim.connect(CA1_Perforant_Path_Associated, CA1_Radiatum_Giant, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.0052573776424375f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.172460639f, 0.0f);
                                   
sim.connect(CA1_Perforant_Path_Associated, CA1_Axo_axonic, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.0060974862926667f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.847532877f, 0.0f);
                                   
sim.connect(CA1_Perforant_Path_Associated, CA1_Basket, "random", RangeWeight(0.0f, 0.7f, 1.7f), 0.00464247089252978f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.883682094f, 0.0f);
                                   
sim.connect(CA1_Perforant_Path_Associated, CA1_Basket_CCK, "random", RangeWeight(0.0f, 1.35f, 2.35f), 0.00579713163086803f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.314331038f, 0.0f);
                                       
sim.connect(CA1_Perforant_Path_Associated, CA1_LMR, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00454664879879396f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.360315289f, 0.0f);

sim.connect(CA1_Perforant_Path_Associated, CA1_Neurogliaform, "random", RangeWeight(0.0f, 1.25f, 2.25f), 0.00654270455816474f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.874424964f, 0.0f);
                            
sim.connect(CA1_Perforant_Path_Associated, CA1_Neurogliaform_Projecting, "random", RangeWeight(0.0f, 0.7f, 1.7f),0.00524695327502167f,                  
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.932621138f, 0.0f);
                                   
sim.connect(CA1_Perforant_Path_Associated, CA1_Oriens_Alveus, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00502641022505712f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.172460639f, 0.0f);
                                   
sim.connect(CA1_Perforant_Path_Associated, CA1_Perforant_Path_Associated, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00540143390878866f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.847532877f, 0.0f);
                                   
sim.connect(CA1_Perforant_Path_Associated, CA1_Perforant_Path_Associated_QuadD, "random", RangeWeight(0.0f, 0.7f, 1.7f),  0.00578970092985875f,    
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.883682094f, 0.0f);
                                   
sim.connect(CA1_Perforant_Path_Associated, CA1_Quadrilaminar, "random", RangeWeight(0.0f, 1.35f, 2.35f), 0.00528628822440002f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.314331038f, 0.0f);
                                   
sim.connect(CA1_Perforant_Path_Associated, CA1_Schaffer_Collateral_Associated, "random", RangeWeight(0.0f, 1.25f, 2.25f), 0.00399667094286693f,  
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.88025265f, 0.0f);
                                   
sim.connect(CA1_Perforant_Path_Associated, CA1_Radial_Trilaminar, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00373941042888481f, 
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.553062478f, 0.0f);
                                      
                                        

sim.connect(CA1_Perforant_Path_Associated_QuadD, CA1_Pyramidal, "random", RangeWeight(0.0f, 0.7f, 1.7f), 0.00659628655349553f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.932621138f, 0.0f);
                                   
sim.connect(CA1_Perforant_Path_Associated_QuadD, CA1_Radiatum_Giant, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00634549793362626f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.172460639f, 0.0f);
                                   
sim.connect(CA1_Perforant_Path_Associated_QuadD, CA1_Axo_axonic, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00718112453629837f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.847532877f, 0.0f);
                                   
sim.connect(CA1_Perforant_Path_Associated_QuadD, CA1_Basket, "random", RangeWeight(0.0f, 0.7f, 1.7f), 0.00568186535327963f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.883682094f, 0.0f);
                                   
sim.connect(CA1_Perforant_Path_Associated_QuadD, CA1_Basket_CCK, "random", RangeWeight(0.0f, 1.35f, 2.35f), 0.00688180835422969f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.314331038f, 0.0f);
                                       
sim.connect(CA1_Perforant_Path_Associated_QuadD, CA1_LMR, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00558363802402361f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.360315289f, 0.0f);

sim.connect(CA1_Perforant_Path_Associated_QuadD, CA1_Neurogliaform, "random", RangeWeight(0.0f, 1.25f, 2.25f), 0.00759966220359342f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.874424964f, 0.0f);
                            
sim.connect(CA1_Perforant_Path_Associated_QuadD, CA1_Neurogliaform_Projecting, "random", RangeWeight(0.0f, 0.7f, 1.7f),0.00632083247801029f,                  
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.932621138f, 0.0f);
                                   
sim.connect(CA1_Perforant_Path_Associated_QuadD, CA1_Oriens_Alveus, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00609109498453608f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.172460639f, 0.0f);
                                   
sim.connect(CA1_Perforant_Path_Associated_QuadD, CA1_Perforant_Path_Associated, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.0064985360121883f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.847532877f, 0.0f);
                                   
sim.connect(CA1_Perforant_Path_Associated_QuadD, CA1_Perforant_Path_Associated_QuadD, "random", RangeWeight(0.0f, 0.7f, 1.7f),  0.00692876624119254f,    
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.883682094f, 0.0f);
                                   
sim.connect(CA1_Perforant_Path_Associated_QuadD, CA1_Quadrilaminar, "random", RangeWeight(0.0f, 1.35f, 2.35f), 0.0063855527122959f,
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.314331038f, 0.0f);
                                   
sim.connect(CA1_Perforant_Path_Associated_QuadD, CA1_Schaffer_Collateral_Associated, "random", RangeWeight(0.0f, 1.25f, 2.25f), 0.00499249717851635f,  
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.88025265f, 0.0f);
                                   
sim.connect(CA1_Perforant_Path_Associated_QuadD, CA1_Radial_Trilaminar, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00471626311599948f, 
                                      RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.553062478f, 0.0f); 
                                      
                                      
                                      
sim.connect(CA1_Quadrilaminar, CA1_Pyramidal, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00507122208132515f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.308152788f, 0.0f);
                                       
sim.connect(CA1_Quadrilaminar, CA1_Radiatum_Giant, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00398180923784452f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.183249644f, 0.0f);
                                       
sim.connect(CA1_Quadrilaminar, CA1_Axo_axonic, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00493921568044397f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.869561088f, 0.0f);
                                       
sim.connect(CA1_Quadrilaminar, CA1_Horizontal_Axo_axonic, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.000448019677967148f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.750808378f, 0.0f);
                                       
sim.connect(CA1_Quadrilaminar, CA1_Back_Projection, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00144674606255046f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.02478806f, 0.0f);
                                       
sim.connect(CA1_Quadrilaminar, CA1_Basket, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00487881824467195f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 3.281611994f, 0.0f);
                                       
sim.connect(CA1_Quadrilaminar, CA1_Basket_CCK, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00551768258556462f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.686238357f, 0.0f);
                                       
sim.connect(CA1_Quadrilaminar, CA1_Horizontal_Basket, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00212127476526913f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.770407646f, 0.0f);
                                       
sim.connect(CA1_Quadrilaminar, CA1_Bistratified, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00428107129724053f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.808726221f, 0.0f);
                                       
sim.connect(CA1_Quadrilaminar, CA1_Ivy, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00345798281617337f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.572405696f, 0.0f);
                                       
sim.connect(CA1_Quadrilaminar, CA1_LMR, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00269064077177216f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.334971075f, 0.0f);
                                       
sim.connect(CA1_Quadrilaminar, CA1_Neurogliaform, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00106495754930202f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.493830393f, 0.0f);
                                       
sim.connect(CA1_Quadrilaminar, CA1_Neurogliaform_Projecting, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.000821723817190589f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.745239175f, 0.0f);
                                       
sim.connect(CA1_Quadrilaminar, CA1_OLM, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.000901150607523382f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.965567683f, 0.0f);
                                       
sim.connect(CA1_Quadrilaminar, CA1_Recurrent_O_LM, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00252512346983246f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.371483576f, 0.0f);
                                       
sim.connect(CA1_Quadrilaminar, CA1_O_LMR, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.000670472606008165f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.355214118f, 0.0f);
                                       
sim.connect(CA1_Quadrilaminar, CA1_Oriens_Alveus, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00458036120160532f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.306303671f, 0.0f);
                                       
sim.connect(CA1_Quadrilaminar, CA1_Oriens_Bistratified, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.000508739315879025f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.490477376f, 0.0f);
                                       
sim.connect(CA1_Quadrilaminar, CA1_OR_LM, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00485749628979892f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.655173699f, 0.0f);
                                       
sim.connect(CA1_Quadrilaminar, CA1_Perforant_Path_Associated, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00365472715963388f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.99431849f, 0.0f);
                                       
sim.connect(CA1_Quadrilaminar, CA1_Perforant_Path_Associated_QuadD, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00852098661481703f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.442647868f, 0.0f);
                                       
sim.connect(CA1_Quadrilaminar, CA1_Quadrilaminar, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.0063938238521165f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.547036443f, 0.0f);
                                       
sim.connect(CA1_Quadrilaminar, CA1_Radiatum, "random", RangeWeight(0.0f, 0.65f, 1.65f), 0.00249784488813087f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.061179756f, 0.0f);
                                       
sim.connect(CA1_Quadrilaminar, CA1_R_Receiving_Apical_Target, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00290225272485256f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.567727407f, 0.0f);
                                       
sim.connect(CA1_Quadrilaminar, CA1_Schaffer_Collateral_Associated, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00391245042290155f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.431148109f, 0.0f);
                                       
sim.connect(CA1_Quadrilaminar, CA1_SO_SO, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00181659531730016f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.567261924f, 0.0f);
                                       
sim.connect(CA1_Quadrilaminar, CA1_Trilaminar, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00161632608930462f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.758382851f, 0.0f);
                                       
sim.connect(CA1_Quadrilaminar, CA1_Radial_Trilaminar, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00518446830524377f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.111359644f, 0.0f); 
                                          
                                          
                                          
sim.connect(CA1_Radiatum, CA1_Pyramidal, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00348142150274266f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.308152788f, 0.0f);
                                       
sim.connect(CA1_Radiatum, CA1_Radiatum_Giant, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00381814342665742f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.183249644f, 0.0f);
                                       
sim.connect(CA1_Radiatum, CA1_Axo_axonic, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00311548339958711f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.869561088f, 0.0f);
                                       
sim.connect(CA1_Radiatum, CA1_Basket, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00339954095796168f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 3.281611994f, 0.0f);
                                       
sim.connect(CA1_Radiatum, CA1_Basket_CCK, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00326530361541776f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.686238357f, 0.0f);
                                       
sim.connect(CA1_Radiatum, CA1_Bistratified, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00331765546295736f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.808726221f, 0.0f);
                                       
sim.connect(CA1_Radiatum, CA1_Ivy, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00233209497586217f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.572405696f, 0.0f);
                                       
sim.connect(CA1_Radiatum, CA1_LMR, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00264245448251099f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.334971075f, 0.0f);
                                       
sim.connect(CA1_Radiatum, CA1_Oriens_Alveus, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00304748172782542f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.306303671f, 0.0f);
                                       
sim.connect(CA1_Radiatum, CA1_OR_LM, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00487073434109497f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.655173699f, 0.0f);
                                       
sim.connect(CA1_Radiatum, CA1_Perforant_Path_Associated, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.0033783297658646f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.99431849f, 0.0f);
                                       
sim.connect(CA1_Radiatum, CA1_Perforant_Path_Associated_QuadD, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00616541821254568f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.442647868f, 0.0f);
                                       
sim.connect(CA1_Radiatum, CA1_Quadrilaminar, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00385234988987404f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.547036443f, 0.0f);
                                       
sim.connect(CA1_Radiatum, CA1_Radiatum, "random", RangeWeight(0.0f, 0.65f, 1.65f), 0.00370355030312552f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.061179756f, 0.0f);
                                       
sim.connect(CA1_Radiatum, CA1_R_Receiving_Apical_Target, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00407396005405191f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.567727407f, 0.0f);
                                       
sim.connect(CA1_Radiatum, CA1_Schaffer_Collateral_Associated, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00405357909872239f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.431148109f, 0.0f);
                                       
sim.connect(CA1_Radiatum, CA1_Radial_Trilaminar, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.0028962574667507f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.111359644f, 0.0f);
                                          
                                          
                                          
sim.connect(CA1_R_Receiving_Apical_Target, CA1_Pyramidal, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.0111372210614393f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.308152788f, 0.0f);
                                       
sim.connect(CA1_R_Receiving_Apical_Target, CA1_Radiatum_Giant, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.0113782486198141f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.183249644f, 0.0f);
                                       
sim.connect(CA1_R_Receiving_Apical_Target, CA1_Axo_axonic, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.0109490817803928f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.869561088f, 0.0f);
                                       
sim.connect(CA1_R_Receiving_Apical_Target, CA1_Basket, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.0104851839316794f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 3.281611994f, 0.0f);
                                       
sim.connect(CA1_R_Receiving_Apical_Target, CA1_Basket_CCK, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.0109049316664838f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.686238357f, 0.0f);
                                       
sim.connect(CA1_R_Receiving_Apical_Target, CA1_Bistratified, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.0058918624556582f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.808726221f, 0.0f);
                                       
sim.connect(CA1_R_Receiving_Apical_Target, CA1_Ivy, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.004176949942433f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.572405696f, 0.0f);
                                       
sim.connect(CA1_R_Receiving_Apical_Target, CA1_LMR, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00918794860815053f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.334971075f, 0.0f);
                                       
sim.connect(CA1_R_Receiving_Apical_Target, CA1_Neurogliaform, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00400937441131055f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.493830393f, 0.0f);
                                       
sim.connect(CA1_R_Receiving_Apical_Target, CA1_Neurogliaform_Projecting, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00300557151888392f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.745239175f, 0.0f); 
                                       
sim.connect(CA1_R_Receiving_Apical_Target, CA1_Oriens_Alveus, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.0101705075897675f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.306303671f, 0.0f);
                                       
sim.connect(CA1_R_Receiving_Apical_Target, CA1_OR_LM, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.0084134561684559f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.655173699f, 0.0f);
                                       
sim.connect(CA1_R_Receiving_Apical_Target, CA1_Perforant_Path_Associated, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.0109552095640564f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.99431849f, 0.0f);
                                       
sim.connect(CA1_R_Receiving_Apical_Target, CA1_Perforant_Path_Associated_QuadD, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.0144281463870344f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.442647868f, 0.0f);
                                       
sim.connect(CA1_R_Receiving_Apical_Target, CA1_Quadrilaminar, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.0113454010068815f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.547036443f, 0.0f);
                                       
sim.connect(CA1_R_Receiving_Apical_Target, CA1_Radiatum, "random", RangeWeight(0.0f, 0.65f, 1.65f), 0.00669928533890529f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.061179756f, 0.0f);
                                       
sim.connect(CA1_R_Receiving_Apical_Target, CA1_R_Receiving_Apical_Target, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00762852402291092f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.567727407f, 0.0f);
                                       
sim.connect(CA1_R_Receiving_Apical_Target, CA1_Schaffer_Collateral_Associated, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.0107803436820507f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.431148109f, 0.0f);
                                       
sim.connect(CA1_R_Receiving_Apical_Target, CA1_Radial_Trilaminar, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00893991717702591f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.111359644f, 0.0f); 
                                          
                                          
                                          
sim.connect(CA1_Schaffer_Collateral_Associated, CA1_Pyramidal, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00593217991437833f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.308152788f, 0.0f);
                                       
sim.connect(CA1_Schaffer_Collateral_Associated, CA1_Radiatum_Giant, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00265836101101202f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.183249644f, 0.0f);
                                       
sim.connect(CA1_Schaffer_Collateral_Associated, CA1_Axo_axonic, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00583713347907244f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.869561088f, 0.0f);
                                       
sim.connect(CA1_Schaffer_Collateral_Associated, CA1_Horizontal_Axo_axonic, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.000554383713221695f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.750808378f, 0.0f);
                                       
sim.connect(CA1_Schaffer_Collateral_Associated, CA1_Back_Projection, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00292036982314269f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.02478806f, 0.0f);
                                       
sim.connect(CA1_Schaffer_Collateral_Associated, CA1_Basket, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00595261999656016f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 3.281611994f, 0.0f);
                                       
sim.connect(CA1_Schaffer_Collateral_Associated, CA1_Basket_CCK, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00630594335815137f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.686238357f, 0.0f);
                                       
sim.connect(CA1_Schaffer_Collateral_Associated, CA1_Horizontal_Basket, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00224328810232676f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.770407646f, 0.0f);
                                       
sim.connect(CA1_Schaffer_Collateral_Associated, CA1_Bistratified, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00619906642095891f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.808726221f, 0.0f);
                                       
sim.connect(CA1_Schaffer_Collateral_Associated, CA1_Ivy, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00558791515296885f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.572405696f, 0.0f);
                                       
sim.connect(CA1_Schaffer_Collateral_Associated, CA1_LMR, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00163416761143042f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.334971075f, 0.0f);
                                       
sim.connect(CA1_Schaffer_Collateral_Associated, CA1_OLM, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00113266992714988f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.965567683f, 0.0f);
                                       
sim.connect(CA1_Schaffer_Collateral_Associated, CA1_Recurrent_O_LM, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.0027338774712996f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.371483576f, 0.0f);
                                       
sim.connect(CA1_Schaffer_Collateral_Associated, CA1_O_LMR, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.000884052524841139f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.355214118f, 0.0f);
                                       
sim.connect(CA1_Schaffer_Collateral_Associated, CA1_Oriens_Alveus, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00528613934842991f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.306303671f, 0.0f);
                                       
sim.connect(CA1_Schaffer_Collateral_Associated, CA1_Oriens_Bistratified, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.000605859219305449f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.490477376f, 0.0f);
                                       
sim.connect(CA1_Schaffer_Collateral_Associated, CA1_OR_LM, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00509295785589136f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.655173699f, 0.0f);
                                       
sim.connect(CA1_Schaffer_Collateral_Associated, CA1_Perforant_Path_Associated, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00225547523384317f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.99431849f, 0.0f);
                                       
sim.connect(CA1_Schaffer_Collateral_Associated, CA1_Perforant_Path_Associated_QuadD, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00842612236567919f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.442647868f, 0.0f);
                                       
sim.connect(CA1_Schaffer_Collateral_Associated, CA1_Quadrilaminar, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00654216413410613f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.547036443f, 0.0f);
                                       
sim.connect(CA1_Schaffer_Collateral_Associated, CA1_Radiatum, "random", RangeWeight(0.0f, 0.65f, 1.65f), 0.00254653437592244f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.061179756f, 0.0f);
                                       
sim.connect(CA1_Schaffer_Collateral_Associated, CA1_R_Receiving_Apical_Target, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00290576826431276f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.567727407f, 0.0f);
                                       
sim.connect(CA1_Schaffer_Collateral_Associated, CA1_Schaffer_Collateral_Associated, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00286404842089837f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.431148109f, 0.0f);
                                       
sim.connect(CA1_Schaffer_Collateral_Associated, CA1_SO_SO, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00199350871982151f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.567261924f, 0.0f);
                                       
sim.connect(CA1_Schaffer_Collateral_Associated, CA1_Trilaminar, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.0018406951037998f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.758382851f, 0.0f);
                                       
sim.connect(CA1_Schaffer_Collateral_Associated, CA1_Radial_Trilaminar, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00554300892200754f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.111359644f, 0.0f);  
                                          
                                          

sim.connect(CA1_SO_SO, CA1_Pyramidal, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00399868070194497f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.308152788f, 0.0f); 
                                       
sim.connect(CA1_SO_SO, CA1_Axo_axonic, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00366447671085423f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.869561088f, 0.0f);
                                       
sim.connect(CA1_SO_SO, CA1_Horizontal_Axo_axonic, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00285305301951821f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.750808378f, 0.0f);
                                       
sim.connect(CA1_SO_SO, CA1_Back_Projection, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00381851658009346f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.02478806f, 0.0f);
                                       
sim.connect(CA1_SO_SO, CA1_Basket, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00376312052723049f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 3.281611994f, 0.0f);
                                       
sim.connect(CA1_SO_SO, CA1_Basket_CCK, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00351015163328016f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.686238357f, 0.0f);
                                       
sim.connect(CA1_SO_SO, CA1_Horizontal_Basket, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.0081216183615661f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.770407646f, 0.0f);
                                       
sim.connect(CA1_SO_SO, CA1_Bistratified, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00347011616726344f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.808726221f, 0.0f);
                                       
sim.connect(CA1_SO_SO, CA1_Ivy, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00335100403725896f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.572405696f, 0.0f);
                                       
sim.connect(CA1_SO_SO, CA1_OLM, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00411490857398677f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.965567683f, 0.0f);
                                       
sim.connect(CA1_SO_SO, CA1_Recurrent_O_LM, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00670992648535073f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.371483576f, 0.0f);
                                       
sim.connect(CA1_SO_SO, CA1_O_LMR, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00370545463211224f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.355214118f, 0.0f);
                                       
sim.connect(CA1_SO_SO, CA1_Oriens_Alveus, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00315761359835187f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.306303671f, 0.0f);
                                       
sim.connect(CA1_SO_SO, CA1_Oriens_Bistratified, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00298214741666047f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.490477376f, 0.0f);
                                       
sim.connect(CA1_SO_SO, CA1_OR_LM, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00386318792790885f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.655173699f, 0.0f);
                                       
sim.connect(CA1_SO_SO, CA1_Perforant_Path_Associated_QuadD, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00304912988866623f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.442647868f, 0.0f);
                                       
sim.connect(CA1_SO_SO, CA1_Quadrilaminar, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00347049054899728f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.547036443f, 0.0f);
                                       
sim.connect(CA1_SO_SO, CA1_SO_SO, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00565202817229082f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.567261924f, 0.0f);
                                       
sim.connect(CA1_SO_SO, CA1_Trilaminar, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00517148477826445f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.758382851f, 0.0f);
                                       
sim.connect(CA1_SO_SO, CA1_Radial_Trilaminar, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00298713691925034f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.111359644f, 0.0f);
                                          
                                          
                                          
sim.connect(CA1_Trilaminar, CA1_Pyramidal, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.0130201382113253f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.308152788f, 0.0f);
                                       
sim.connect(CA1_Trilaminar, CA1_Radiatum_Giant, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.0032486777511782f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.183249644f, 0.0f);
                                       
sim.connect(CA1_Trilaminar, CA1_Axo_axonic, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.0134184370667187f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.869561088f, 0.0f);
                                       
sim.connect(CA1_Trilaminar, CA1_Horizontal_Axo_axonic, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00247545053012843f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.750808378f, 0.0f);
                                       
sim.connect(CA1_Trilaminar, CA1_Back_Projection, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00873106772682874f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.02478806f, 0.0f);
                                       
sim.connect(CA1_Trilaminar, CA1_Basket, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.0132592629886918f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 3.281611994f, 0.0f);
                                       
sim.connect(CA1_Trilaminar, CA1_Basket_CCK, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.0139729074442008f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.686238357f, 0.0f);
                                       
sim.connect(CA1_Trilaminar, CA1_Horizontal_Basket, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00915206988110106f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.770407646f, 0.0f);
                                       
sim.connect(CA1_Trilaminar, CA1_Bistratified, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.0136046660171507f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.808726221f, 0.0f);
                                       
sim.connect(CA1_Trilaminar, CA1_Ivy, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.0130626383427262f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.572405696f, 0.0f);
                                       
sim.connect(CA1_Trilaminar, CA1_LMR, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00223383921060105f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.334971075f, 0.0f);
                                       
sim.connect(CA1_Trilaminar, CA1_OLM, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00299163216597231f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.965567683f, 0.0f);
                                       
sim.connect(CA1_Trilaminar, CA1_Recurrent_O_LM, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00577596465709617f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.371483576f, 0.0f);
                                       
sim.connect(CA1_Trilaminar, CA1_O_LMR, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00269337407489589f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.355214118f, 0.0f);
                                       
sim.connect(CA1_Trilaminar, CA1_Oriens_Alveus, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.0122911536980424f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.306303671f, 0.0f);
                                       
sim.connect(CA1_Trilaminar, CA1_Oriens_Bistratified, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00264704833146289f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.490477376f, 0.0f);
                                       
sim.connect(CA1_Trilaminar, CA1_OR_LM, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00747619810553257f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.655173699f, 0.0f);
                                       
sim.connect(CA1_Trilaminar, CA1_Perforant_Path_Associated, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.0028355903618128f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.99431849f, 0.0f);
                                       
sim.connect(CA1_Trilaminar, CA1_Perforant_Path_Associated_QuadD, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.0156825100130678f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.442647868f, 0.0f);
                                       
sim.connect(CA1_Trilaminar, CA1_Quadrilaminar, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.0138176060526492f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.547036443f, 0.0f);
                                       
sim.connect(CA1_Trilaminar, CA1_Radiatum, "random", RangeWeight(0.0f, 0.65f, 1.65f), 0.00319325497280675f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.061179756f, 0.0f);
                                       
sim.connect(CA1_Trilaminar, CA1_R_Receiving_Apical_Target, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00345062787974148f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.567727407f, 0.0f);
                                       
sim.connect(CA1_Trilaminar, CA1_Schaffer_Collateral_Associated, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00352738443357314f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.431148109f, 0.0f);
                                       
sim.connect(CA1_Trilaminar, CA1_SO_SO, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00481836093742893f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.567261924f, 0.0f);
                                       
sim.connect(CA1_Trilaminar, CA1_Trilaminar, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00405313849494881f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.758382851f, 0.0f);
                                       
sim.connect(CA1_Trilaminar, CA1_Radial_Trilaminar, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.0125970634538635f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.111359644f, 0.0f); 



sim.connect(CA1_Radial_Trilaminar, CA1_Pyramidal, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00549749868777815f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.308152788f, 0.0f);
                                       
sim.connect(CA1_Radial_Trilaminar, CA1_Radiatum_Giant, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00189816145405985f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.183249644f, 0.0f);
                                       
sim.connect(CA1_Radial_Trilaminar, CA1_Axo_axonic, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00511434575274227f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.869561088f, 0.0f);
                                       
sim.connect(CA1_Radial_Trilaminar, CA1_Horizontal_Axo_axonic, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00117139854055403f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.750808378f, 0.0f);
                                       
sim.connect(CA1_Radial_Trilaminar, CA1_Back_Projection, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00326447804368601f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.02478806f, 0.0f);
                                       
sim.connect(CA1_Radial_Trilaminar, CA1_Basket, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00544253433999475f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 3.281611994f, 0.0f);
                                       
sim.connect(CA1_Radial_Trilaminar, CA1_Basket_CCK, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00559751395390684f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.686238357f, 0.0f);
                                       
sim.connect(CA1_Radial_Trilaminar, CA1_Horizontal_Basket, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.0039040051235708f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.770407646f, 0.0f);
                                       
sim.connect(CA1_Radial_Trilaminar, CA1_Bistratified, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00545114822390147f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.808726221f, 0.0f);
                                       
sim.connect(CA1_Radial_Trilaminar, CA1_Ivy, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00493463773115299f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.572405696f, 0.0f);
                                       
sim.connect(CA1_Radial_Trilaminar, CA1_LMR, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.000928189980647364f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.334971075f, 0.0f);
                                       
sim.connect(CA1_Radial_Trilaminar, CA1_OLM, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00221558020705203f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.965567683f, 0.0f);
                                       
sim.connect(CA1_Radial_Trilaminar, CA1_Recurrent_O_LM, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00420837601767754f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.371483576f, 0.0f);
                                       
sim.connect(CA1_Radial_Trilaminar, CA1_O_LMR, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.0018578420897608f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.355214118f, 0.0f);
                                       
sim.connect(CA1_Radial_Trilaminar, CA1_Oriens_Alveus, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.0046763489348216f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.306303671f, 0.0f);
                                       
sim.connect(CA1_Radial_Trilaminar, CA1_Oriens_Bistratified, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00123863070997098f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.490477376f, 0.0f);
                                       
sim.connect(CA1_Radial_Trilaminar, CA1_OR_LM, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00560630123413141f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.655173699f, 0.0f);
                                       
sim.connect(CA1_Radial_Trilaminar, CA1_Perforant_Path_Associated, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00153856660108242f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.99431849f, 0.0f);
                                       
sim.connect(CA1_Radial_Trilaminar, CA1_Perforant_Path_Associated_QuadD, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00758367404335702f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.442647868f, 0.0f);
                                       
sim.connect(CA1_Radial_Trilaminar, CA1_Quadrilaminar, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.0057696533524244f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.547036443f, 0.0f);
                                       
sim.connect(CA1_Radial_Trilaminar, CA1_Radiatum, "random", RangeWeight(0.0f, 0.65f, 1.65f), 0.00166960366417823f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.061179756f, 0.0f);
                                       
sim.connect(CA1_Radial_Trilaminar, CA1_R_Receiving_Apical_Target, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00226336627728906f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.567727407f, 0.0f);
                                       
sim.connect(CA1_Radial_Trilaminar, CA1_Schaffer_Collateral_Associated, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00192866128210889f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.431148109f, 0.0f);
                                       
sim.connect(CA1_Radial_Trilaminar, CA1_SO_SO, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00326491702942077f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.567261924f, 0.0f);
                                       
sim.connect(CA1_Radial_Trilaminar, CA1_Trilaminar, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00307932307284608f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.758382851f, 0.0f);
                                       
sim.connect(CA1_Radial_Trilaminar, CA1_Radial_Trilaminar, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00465262523801679f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.111359644f, 0.0f);                                                                                                                                                                  
                                      

//no connection specific!//                                   
sim.setSTP(CA1_Pyramidal, true, 0.45f, 50.0f, 750.0f); // STD
                                     
sim.setSTP(CA1_Radiatum_Giant, true, 0.15f, 750.0f, 50.0f);
                                     
sim.setSTP(CA1_Axo_axonic, true, 0.15f, 750.0f, 50.0f);
                                     
sim.setSTP(CA1_Horizontal_Axo_axonic, true, 0.15f, 750.0f, 50.0f);
                                     
sim.setSTP(CA1_Back_Projection, true, 0.15f, 750.0f, 50.0f);
                                     
sim.setSTP(CA1_Basket, true, 0.15f, 750.0f, 50.0f);
                                     
sim.setSTP(CA1_Basket_CCK, true, 0.15f, 750.0f, 50.0f);

sim.setSTP(CA1_Horizontal_Basket, true, 0.15f, 750.0f, 50.0f);

sim.setSTP(CA1_Bistratified, true, 0.15f, 750.0f, 50.0f);
                                     
sim.setSTP(CA1_Ivy, true, 0.15f, 750.0f, 50.0f);
                                     
sim.setSTP(CA1_LMR, true, 0.15f, 750.0f, 50.0f);
                                     
sim.setSTP(CA1_Neurogliaform, true, 0.15f, 750.0f, 50.0f);
                                     
sim.setSTP(CA1_Neurogliaform_Projecting, true, 0.15f, 750.0f, 50.0f);
                                     
sim.setSTP(CA1_OLM, true, 0.15f, 750.0f, 50.0f);
                                     
sim.setSTP(CA1_Recurrent_O_LM, true, 0.15f, 750.0f, 50.0f);

sim.setSTP(CA1_O_LMR, true, 0.15f, 750.0f, 50.0f);

sim.setSTP(CA1_Oriens_Alveus, true, 0.15f, 750.0f, 50.0f);
                                     
sim.setSTP(CA1_Oriens_Bistratified, true, 0.15f, 750.0f, 50.0f);
                                     
sim.setSTP(CA1_OR_LM, true, 0.15f, 750.0f, 50.0f);
                                     
sim.setSTP(CA1_Perforant_Path_Associated, true, 0.15f, 750.0f, 50.0f);

sim.setSTP(CA1_Perforant_Path_Associated_QuadD, true, 0.15f, 750.0f, 50.0f);
                                     
sim.setSTP(CA1_Quadrilaminar, true, 0.15f, 750.0f, 50.0f);
                                     
sim.setSTP(CA1_Radiatum, true, 0.15f, 750.0f, 50.0f);
                                     
sim.setSTP(CA1_R_Receiving_Apical_Target, true, 0.15f, 750.0f, 50.0f);

sim.setSTP(CA1_Schaffer_Collateral_Associated, true, 0.15f, 750.0f, 50.0f);

sim.setSTP(CA1_SO_SO, true, 0.15f, 750.0f, 50.0f);
                                     
sim.setSTP(CA1_Trilaminar, true, 0.15f, 750.0f, 50.0f);

sim.setSTP(CA1_Radial_Trilaminar, true, 0.15f, 750.0f, 50.0f);

//sim.setConductances(false);//
//sim.setConductances(true);//


//no connection specific!//
//tdGABA for excitatory neuron and tdAMPA for inhibitory neuron are 5ms, 150ms//
sim.setConductances(CA1_Pyramidal, 6.9, 0, 150, 5, 0, 150); // Exc

sim.setConductances(CA1_Radiatum_Giant, 7.2, 0, 150, 5, 0, 150);// Exc

sim.setConductances(CA1_Axo_axonic, 5, 0, 150, 6.8, 0, 150);// Inh

sim.setConductances(CA1_Horizontal_Axo_axonic, 5, 0, 150, 7.8, 0, 150);// Inh

sim.setConductances(CA1_Back_Projection, 5, 0, 150, 8.7, 0, 150);// Inh

sim.setConductances(CA1_Basket, 5, 0, 150, 4.7, 0, 150);// Inh

sim.setConductances(CA1_Basket_CCK, 5, 0, 150, 8.9, 0, 150);// Inh

sim.setConductances(CA1_Horizontal_Basket, 5, 0, 150, 9.8, 0, 150);// Inh

sim.setConductances(CA1_Bistratified, 5, 0, 150, 12.1, 0, 150);// Inh

sim.setConductances(CA1_Ivy, 5, 0, 150, 11.0, 0, 150);// Inh

sim.setConductances(CA1_LMR, 5, 0, 150, 9.1, 0, 150);// Inh

sim.setConductances(CA1_Neurogliaform, 5, 0, 150, 9.9, 0, 150);// Inh

sim.setConductances(CA1_Neurogliaform_Projecting, 5, 0, 150, 10.2, 0, 150);// Inh

sim.setConductances(CA1_OLM, 5, 0, 150, 8.8, 0, 150);// Inh

sim.setConductances(CA1_Recurrent_O_LM, 5, 0, 150, 8.8, 0, 150);// Inh

sim.setConductances(CA1_O_LMR, 5, 0, 150, 8.2, 0, 150);// Inh

sim.setConductances(CA1_Oriens_Alveus, 5, 0, 150, 7.7, 0, 150);// Inh

sim.setConductances(CA1_Oriens_Bistratified, 5, 0, 150, 9.2, 0, 150);// Inh

sim.setConductances(CA1_OR_LM, 5, 0, 150, 8.4, 0, 150);// Inh

sim.setConductances(CA1_Perforant_Path_Associated, 5, 0, 150, 8.1, 0, 150);// Inh

sim.setConductances(CA1_Perforant_Path_Associated_QuadD, 5, 0, 150, 8.3, 0, 150);// Inh

sim.setConductances(CA1_Quadrilaminar, 5, 0, 150, 8.2, 0, 150);// Inh

sim.setConductances(CA1_Radiatum, 5, 0, 150, 12.2, 0, 150);// Inh

sim.setConductances(CA1_R_Receiving_Apical_Target, 5, 0, 150, 8.5, 0, 150);// Inh

sim.setConductances(CA1_Schaffer_Collateral_Associated, 5, 0, 150, 8.5, 0, 150);// Inh

sim.setConductances(CA1_SO_SO, 5, 0, 150, 9.0, 0, 150);// Inh

sim.setConductances(CA1_Trilaminar, 5, 0, 150, 9.2, 0, 150);// Inh

sim.setConductances(CA1_Radial_Trilaminar, 5, 0, 150, 9.0, 0, 150);// Inh



// set Neuron Monitor 
sim.setNeuronMonitor(CA1_Pyramidal, "DEFAULT");

sim.setNeuronMonitor(CA1_Radiatum_Giant, "DEFAULT");

sim.setNeuronMonitor(CA1_Axo_axonic, "DEFAULT");

sim.setNeuronMonitor(CA1_Horizontal_Axo_axonic, "DEFAULT");

sim.setNeuronMonitor(CA1_Back_Projection, "DEFAULT");

sim.setNeuronMonitor(CA1_Basket, "DEFAULT");

sim.setNeuronMonitor(CA1_Basket_CCK, "DEFAULT");

sim.setNeuronMonitor(CA1_Horizontal_Basket, "DEFAULT");

sim.setNeuronMonitor(CA1_Bistratified, "DEFAULT");

sim.setNeuronMonitor(CA1_Ivy, "DEFAULT");

sim.setNeuronMonitor(CA1_LMR, "DEFAULT");

sim.setNeuronMonitor(CA1_Neurogliaform, "DEFAULT");

sim.setNeuronMonitor(CA1_Neurogliaform_Projecting, "DEFAULT");

sim.setNeuronMonitor(CA1_OLM, "DEFAULT");

sim.setNeuronMonitor(CA1_Recurrent_O_LM, "DEFAULT");

sim.setNeuronMonitor(CA1_O_LMR, "DEFAULT");

sim.setNeuronMonitor(CA1_Oriens_Alveus, "DEFAULT");

sim.setNeuronMonitor(CA1_Oriens_Bistratified, "DEFAULT");

sim.setNeuronMonitor(CA1_OR_LM, "DEFAULT");

sim.setNeuronMonitor(CA1_Perforant_Path_Associated, "DEFAULT");

sim.setNeuronMonitor(CA1_Perforant_Path_Associated_QuadD, "DEFAULT");

sim.setNeuronMonitor(CA1_Quadrilaminar, "DEFAULT");

sim.setNeuronMonitor(CA1_Radiatum, "DEFAULT");

sim.setNeuronMonitor(CA1_R_Receiving_Apical_Target, "DEFAULT");

sim.setNeuronMonitor(CA1_Schaffer_Collateral_Associated, "DEFAULT");

sim.setNeuronMonitor(CA1_SO_SO, "DEFAULT");

sim.setNeuronMonitor(CA1_Trilaminar, "DEFAULT");

sim.setNeuronMonitor(CA1_Radial_Trilaminar, "DEFAULT");



