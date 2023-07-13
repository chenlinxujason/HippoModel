#ifdef __NO_CUDA__
   int CA3_QuadD_LM = sim.createGroup("CA3_QuadD_LM", 13120.0, //3280.0,
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA3_Axo_Axonic = sim.createGroup("CA3_Axo_Axonic", 7636.0,//1909.0,
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA3_Basket = sim.createGroup("CA3_Basket", 2060.0,//515.0,
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA3_BC_CCK = sim.createGroup("CA3_BC_CCK", 2660.0,//665.0,
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA3_Bistratified = sim.createGroup("CA3_Bistratified", 18524.0,//4631.0,
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA3_Ivy = sim.createGroup("CA3_Ivy", 9336.0,//2334.0,
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA3_MFA_ORDEN = sim.createGroup("CA3_MFA_ORDEN", 6104.0,//1526.0,
                              INHIBITORY_NEURON, 0, CPU_CORES);
                              
   int CA3_Pyramidal = sim.createGroup("CA3_Pyramidal", 297464,//74366.0,
                              EXCITATORY_NEURON, 0, CPU_CORES);
                              
#else
      int CA3_QuadD_LM = sim.createGroup("CA3_QuadD_LM", 13120.0, //3280.0,
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA3_Axo_Axonic = sim.createGroup("CA3_Axo_Axonic", 7636.0,//1909.0,
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA3_Basket = sim.createGroup("CA3_Basket", 2060.0,//515.0,
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA3_BC_CCK = sim.createGroup("CA3_BC_CCK", 2660.0,//665.0,
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA3_Bistratified = sim.createGroup("CA3_Bistratified", 18524.0,//4631.0,
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA3_Ivy = sim.createGroup("CA3_Ivy", 9336.0,//2334.0,
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA3_MFA_ORDEN = sim.createGroup("CA3_MFA_ORDEN", 6104.0,//1526.0,
                              INHIBITORY_NEURON, 0, GPU_CORES);
                              
   int CA3_Pyramidal = sim.createGroup("CA3_Pyramidal", 297464,//74366.0,
                              EXCITATORY_NEURON, 0, GPU_CORES);
#endif
                                                
sim.setNeuronParameters(CA3_QuadD_LM, 186.0, 0.0, 1.77600861583782, 0.0,
                                                -73.4821116922868, 0.0, -54.9369058996129, 0.0, 0.00584332072216318,
                                                0.0, -3.44873648365723, 0.0, 7.06631328236041,
                                                0.0, -64.4037157222031, 0.0,
                                                52.0, 0.0);
                     
sim.setNeuronParameters(CA3_Axo_Axonic, 165.0, 0.0, 3.96146287759279, 0.0,
                                                -57.099782869594, 0.0, -51.7187562820223, 0.0, 0.00463860807187154,
                                                0.0, 8.68364493653417, 0.0, 27.7986355932787,
                                                0.0, -73.9685042125372, 0.0,
                                                15.0, 0.0);
                     
sim.setNeuronParameters(CA3_Basket, 45.0, 0.0, 0.9951729, 0,
                                                -57.506126, 0.0, -23.378766, 0.0, 0.003846186,
                                                0.0, 9.2642765, 0.0, 18.454934,
                                                0.0, -47.555661, 0.0,
                                                -6.0, 0.0);
                     
sim.setNeuronParameters(CA3_BC_CCK, 135.0, 0.0, 0.583005186, 0.0,
                                                -58.99667734, 0.0, -39.39832097, 0.0, 0.00574483,
                                                0.0, -1.244845715, 0.0, 18.27458854,
                                                0.0, -42.7711851, 0.0,
                                                54.0, 0.0);
                     
sim.setNeuronParameters(CA3_Bistratified, 107.0, 0.0, 3.935030495, 0.0,
                                                -64.67262808, 0.0, -58.74397154, 0.0, 0.001952449,
                                                0.0, 16.57957046, 0.0, -9.928793958,
                                                0.0, -59.70326258, 0.0,
                                                19.0, 0.0);
                     
sim.setNeuronParameters(CA3_Ivy, 364.0, 0.0, 1.91603822942046, 0.0,
                                                -70.4345135750261, 0.0, -40.8589263758355, 0.0, 0.009151158130158,
                                                0.0, 1.90833702318966, 0.0, -6.91973671560226,
                                                0.0, -53.3998503336009, 0.0,
                                                45.0, 0.0);
                     
sim.setNeuronParameters(CA3_MFA_ORDEN, 209.0, 0.0, 1.37980713457205, 0.0,
                                                -57.076423571379, 0.0, -39.1020427841762, 0.0, 0.00783805979364104,
                                                0.0, 12.9332855397722, 0.0, 16.3132681887705,
                                                0.0, -40.6806648852695, 0.0,
                                                0.0, 0.0);
                     
sim.setNeuronParameters(CA3_Pyramidal, 366.0, 0.0, 0.792338703789581, 0.0,
                                                -63.2044008171655, 0.0, -33.6041733124267, 0.0, 0.00838350334098279,
                                                0.0, -42.5524776883928, 0.0, 35.8614648558726,
                                                0.0, -38.8680990294091, 0.0,
                                                588.0, 0.0);
// range weight
sim.connect(CA3_QuadD_LM, CA3_Axo_Axonic, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00132f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.473054473f, 0.0f);//0.00529496670795314f
                                       
sim.connect(CA3_QuadD_LM, CA3_Basket, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.0167f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.815288206f, 0.0f);//0.0667209642727206f
                                       
sim.connect(CA3_QuadD_LM, CA3_BC_CCK, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.0124f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.308152788f, 0.0f);//0.0495724663599669f
                                       
sim.connect(CA3_QuadD_LM, CA3_Pyramidal, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.0297f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.183249644f, 0.0f);//0.11882477878628f
                                       
sim.connect(CA3_Axo_Axonic, CA3_Pyramidal, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.0375f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.869561088f, 0.0f);//0.15f
                                       
sim.connect(CA3_Basket, CA3_QuadD_LM, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00125f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.750808378f, 0.0f);//0.005f
                                       
sim.connect(CA3_Basket, CA3_Axo_Axonic, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00625f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.02478806f, 0.0f);//0.025
                                       
sim.connect(CA3_Basket, CA3_Basket, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00125f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 3.281611994f, 0.0f);//0.005
                                       
sim.connect(CA3_Basket, CA3_BC_CCK, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00125f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.686238357f, 0.0f);//0.005
                                       
sim.connect(CA3_Basket, CA3_Bistratified, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00625f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.770407646f, 0.0f);//0.025
                                       
sim.connect(CA3_Basket, CA3_MFA_ORDEN, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00125f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.808726221f, 0.0f);//0.005
                                       
sim.connect(CA3_Basket, CA3_Pyramidal, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.0375f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.572405696f, 0.0f);//0.15
                                       
sim.connect(CA3_BC_CCK, CA3_QuadD_LM, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00625f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.334971075f, 0.0f);//0.025
                                       
sim.connect(CA3_BC_CCK, CA3_Axo_Axonic, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00625f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.493830393f, 0.0f);//0.025
                                       
sim.connect(CA3_BC_CCK, CA3_Basket, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00125f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.745239175f, 0.0f);//0.005
                                       
sim.connect(CA3_BC_CCK, CA3_BC_CCK, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00125f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 0.965567683f, 0.0f);//0.005
                                       
sim.connect(CA3_BC_CCK, CA3_Bistratified, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00625f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.371483576f, 0.0f);//0.025
                                       
sim.connect(CA3_BC_CCK, CA3_MFA_ORDEN, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00125f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.355214118f, 0.0f);//0.005
                                       
sim.connect(CA3_BC_CCK, CA3_Pyramidal, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.0375f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.306303671f, 0.0f);//0.15
                                       
sim.connect(CA3_Bistratified, CA3_QuadD_LM, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00194f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.490477376f, 0.0f);//0.00775423637622817
                                       
sim.connect(CA3_Bistratified, CA3_Axo_Axonic, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.0022f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.655173699f, 0.0f);//0.00659307293350001
                                       
sim.connect(CA3_Bistratified, CA3_Basket, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00165f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.99431849f, 0.0f);//0.00926382440444106
                                       
sim.connect(CA3_Bistratified, CA3_BC_CCK, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00108f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.442647868f, 0.0f);//0.00431732093529376
                                       
sim.connect(CA3_Bistratified, CA3_Bistratified, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00814f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.547036443f, 0.0f);//0.0325785208207766
                                       
sim.connect(CA3_Bistratified, CA3_Ivy, "random", RangeWeight(0.0f, 0.65f, 1.65f), 0.000964f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.061179756f, 0.0f);//0.00385580973430123
                                       
sim.connect(CA3_Bistratified, CA3_MFA_ORDEN, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00215f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.567727407f, 0.0f);//0.00862472688778918
                                       
sim.connect(CA3_Bistratified, CA3_Pyramidal, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00697f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.431148109f, 0.0f);//0.0278686093547943
                                       
sim.connect(CA3_Ivy, CA3_QuadD_LM, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.000495f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.567261924f, 0.0f);//0.00198176910683873
                                       
sim.connect(CA3_Ivy, CA3_Axo_Axonic, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00106f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.758382851f, 0.0f);//0.00424634524060682
                                       
sim.connect(CA3_Ivy, CA3_Basket, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00408f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.111359644f, 0.0f);//0.016300617068683923
                                       
sim.connect(CA3_Ivy, CA3_BC_CCK, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00269f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.54009769f, 0.0f);//0.010742278540606838
                                       
sim.connect(CA3_Ivy, CA3_Bistratified, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00426f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.660111909f, 0.0f);//0.01703156100118382f
                                       
sim.connect(CA3_Ivy, CA3_Ivy, "random", RangeWeight(0.0f, 0.65f, 1.65f), 0.000938f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.142741525f, 0.0f);//0.00375271870052702f
                                       
sim.connect(CA3_Ivy, CA3_MFA_ORDEN, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.00423f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.687214907f, 0.0f);//0.0169285421706311f
                                       
sim.connect(CA3_Ivy, CA3_Pyramidal, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.0180f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.540661646f, 0.0f);//0.0720967942651253f
                                       
sim.connect(CA3_MFA_ORDEN, CA3_QuadD_LM, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.000939f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.471995564f, 0.0f);//0.00375566003798539f
                                       
sim.connect(CA3_MFA_ORDEN, CA3_Axo_Axonic, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00109f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.628518636f, 0.0f);//0.00437941786544469f
                                       
sim.connect(CA3_MFA_ORDEN, CA3_Basket, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00182f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.972333716f, 0.0f);//0.0072882240621001f
                                       
sim.connect(CA3_MFA_ORDEN, CA3_BC_CCK, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00132f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.415044453f, 0.0f);//0.00526662735486614f
                                       
sim.connect(CA3_MFA_ORDEN, CA3_Bistratified, "random", RangeWeight(0.0f, 1.3f, 2.3f), 0.00120f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.536494845f, 0.0f);//0.00480204193183194
                                       
sim.connect(CA3_MFA_ORDEN, CA3_Ivy, "random", RangeWeight(0.0f, 0.65f, 1.65f), 0.000670f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 2.081976802f, 0.0f);//0.00267981747242981
                                       
sim.connect(CA3_MFA_ORDEN, CA3_MFA_ORDEN, "random", RangeWeight(0.0f, 0.75f, 1.75f), 0.000526f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.552656079f, 0.0f);//0.00210548528014741
                                       
sim.connect(CA3_MFA_ORDEN, CA3_Pyramidal, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.0104f,
                                          RangeDelay(1), RadiusRF(-1.0), SYN_PLASTIC, 1.360315289f, 0.0f);//0.0417555599977689f

//  patch RangeDelay(1,2)
// [ERROR C:\cockroach-ut3\src\CARLsim6\carlsim\kernel\src\snn_manager.cpp:5908] STP with delays > 1 ms is currently not supported.

sim.connect(CA3_Pyramidal, CA3_QuadD_LM, "random", RangeWeight(0.0f, 1.25f, 2.25f), 0.00334f,
                                      RangeDelay(1/*2*/), RadiusRF(-1.0), SYN_PLASTIC, 0.874424964f, 0.0f);//0.0133672243607345
                            
sim.connect(CA3_Pyramidal, CA3_Axo_Axonic, "random", RangeWeight(0.0f, 0.7f, 1.7f), 0.00370f,
                                      RangeDelay(1/*2*/), RadiusRF(-1.0), SYN_PLASTIC, 0.932621138f, 0.0f);//0.0148205394733136f
                                   
sim.connect(CA3_Pyramidal, CA3_Basket, "random", RangeWeight(0.0f, 1.45f, 2.45f), 0.00494f,
                                      RangeDelay(1/*2*/), RadiusRF(-1.0), SYN_PLASTIC, 1.172460639f, 0.0f);//0.0197417562762975f
                                   
sim.connect(CA3_Pyramidal, CA3_BC_CCK, "random", RangeWeight(0.0f, 1.0f, 2.0f), 0.00432f,
                                      RangeDelay(1/*2*/), RadiusRF(-1.0), SYN_PLASTIC, 0.847532877f, 0.0f);//0.0172994236281402f
                                   
sim.connect(CA3_Pyramidal, CA3_Bistratified, "random", RangeWeight(0.0f, 0.7f, 1.7f), 0.00396f,
                                      RangeDelay(1/*2*/), RadiusRF(-1.0), SYN_PLASTIC, 0.883682094f, 0.0f);//0.015857085924813f
                                   
sim.connect(CA3_Pyramidal, CA3_Ivy, "random", RangeWeight(0.0f, 1.35f, 2.35f), 0.00629f,
                                      RangeDelay(1/*2*/), RadiusRF(-1.0), SYN_PLASTIC, 1.314331038f, 0.0f);//0.0251567907913944f
                                   
sim.connect(CA3_Pyramidal, CA3_MFA_ORDEN, "random", RangeWeight(0.0f, 1.25f, 2.25f), 0.00525f,
                                      RangeDelay(1/*2*/), RadiusRF(-1.0), SYN_PLASTIC, 0.88025265f, 0.0f);//0.0209934225689348f
                                   
sim.connect(CA3_Pyramidal, CA3_Pyramidal, "random", RangeWeight(0.0f, 0.55f, 1.55f), 0.00627f,
                                      RangeDelay(1/*2*/), RadiusRF(-1.0), SYN_PLASTIC, 0.553062478f, 0.0f);//0.0250664662231983f
                                      
                                                                       
sim.setSTP(CA3_QuadD_LM, true, 0.15f, 750.0f, 50.0f);
                                     
sim.setSTP(CA3_Axo_Axonic, true, 0.15f, 750.0f, 50.0f);
                                     
sim.setSTP(CA3_Basket, true, 0.15f, 750.0f, 50.0f);
                                     
sim.setSTP(CA3_BC_CCK, true, 0.15f, 750.0f, 50.0f);
                                     
sim.setSTP(CA3_Bistratified, true, 0.15f, 750.0f, 50.0f);
                                     
sim.setSTP(CA3_Ivy, true, 0.15f, 750.0f, 50.0f);
                                     
sim.setSTP(CA3_MFA_ORDEN, true, 0.15f, 750.0f, 50.0f);

sim.setSTP(CA3_Pyramidal, true, 0.45f, 50.0f, 750.0f);

//sim.setConductances(false);//
//sim.setConductances(true);//


//setConductances at neuron group level//
sim.setConductances(CA3_QuadD_LM, 5, 0, 150, 4, 0, 150);

sim.setConductances(CA3_Axo_Axonic, 5, 0, 150, 8, 0, 150);

sim.setConductances(CA3_Basket, 5, 0, 150, 5, 0, 150);

sim.setConductances(CA3_BC_CCK, 5, 0, 150, 6, 0, 150);

sim.setConductances(CA3_Bistratified, 5, 0, 150, 5, 0, 150);

sim.setConductances(CA3_Ivy, 5, 0, 150, 5, 0, 150);

sim.setConductances(CA3_MFA_ORDEN, 5, 0, 150, 5, 0, 150);

sim.setConductances(CA3_Pyramidal, 4, 0, 150, 6, 0, 150);
//setConductances at neuron group level//
                                 
sim.setNeuronMonitor(CA3_QuadD_LM, "DEFAULT");
                                 
sim.setNeuronMonitor(CA3_Axo_Axonic, "DEFAULT");
                                 
sim.setNeuronMonitor(CA3_Basket, "DEFAULT");
                                 
sim.setNeuronMonitor(CA3_BC_CCK, "DEFAULT");
                                 
sim.setNeuronMonitor(CA3_Bistratified, "DEFAULT");
                                 
sim.setNeuronMonitor(CA3_Ivy, "DEFAULT");
                                 
sim.setNeuronMonitor(CA3_MFA_ORDEN, "DEFAULT");
                                 
sim.setNeuronMonitor(CA3_Pyramidal, "DEFAULT");
