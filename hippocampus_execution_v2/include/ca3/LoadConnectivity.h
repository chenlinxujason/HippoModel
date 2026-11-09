// Read ID ranges and coordinates, then load connectivity.
// This header contains statements included inside main, sharing its local variables.

    // Open HDF5 connectivity file for reading
    File file(FILE_NAME, File::ReadOnly);

    // Obtain ID ranges
	std::string dataset_idranges_EC_LEC = "IDranges/EC/LEC";
    std::string dataset_idranges_EC_MEC = "IDranges/EC/MEC";
    std::string dataset_idranges_DG_GC = "IDranges/DG/GC";
	std::string dataset_idranges_CA3_PC = "IDranges/CA3/PC";
	std::string dataset_idranges_CA3_BC = "IDranges/CA3/BC";
	std::string dataset_idranges_CA3_AAC = "IDranges/CA3/AAC";
	std::string dataset_idranges_CA3_BCCCK = "IDranges/CA3/BCCCK";
	std::string dataset_idranges_CA3_BisC = "IDranges/CA3/Bistratified";
	std::string dataset_idranges_CA3_OLM = "IDranges/CA3/OLM";
	std::string dataset_idranges_CA3_TL = "IDranges/CA3/Trilaminar";
	std::string dataset_idranges_CA3_MFA = "IDranges/CA3/MFA";

    std::vector<int> IDrange_EC_LEC;
    std::vector<int> IDrange_EC_MEC;
	std::vector<int> IDrange_DG_GC;
	std::vector<int> IDrange_CA3_PC;
	std::vector<int> IDrange_CA3_BC;
	std::vector<int> IDrange_CA3_AAC;
	std::vector<int> IDrange_CA3_BCCCK;
	std::vector<int> IDrange_CA3_BisC;
	std::vector<int> IDrange_CA3_OLM;
	std::vector<int> IDrange_CA3_TL;
	std::vector<int> IDrange_CA3_MFA;
	
	std::vector<std::vector<float>> locs;
	std::vector<std::vector<float>> locs_EC;
	std::vector<int> CA3_pc_region;// seperate CA3PC as a,b and c

    /*
	std::vector<float> locs_x_CA3PC;
    std::vector<float> locs_y_CA3PC;
	
    std::vector<float> locs_x_CA3BC;
    std::vector<float> locs_y_CA3BC;
  
    std::vector<float> locs_x_CA3AAC;
    std::vector<float> locs_y_CA3AAC;
    
    std::vector<float> locs_x_CA3BCCCK;
    std::vector<float> locs_y_CA3BCCCK;
    
    std::vector<float> locs_x_CA3BisC;
    std::vector<float> locs_y_CA3BisC;
    
    std::vector<float> locs_x_CA3OLM;
    std::vector<float> locs_y_CA3OLM;
    
    std::vector<float> locs_x_CA3TL;
    std::vector<float> locs_y_CA3TL;
    
    std::vector<float> locs_x_CA3MFA;
    std::vector<float> locs_y_CA3MFA;
    */
    
    
    file.getDataSet(dataset_idranges_DG_GC).read(IDrange_DG_GC);
    file.getDataSet(dataset_idranges_CA3_PC).read(IDrange_CA3_PC);
    file.getDataSet(dataset_idranges_CA3_BC).read(IDrange_CA3_BC);
    file.getDataSet(dataset_idranges_CA3_AAC).read(IDrange_CA3_AAC);
    file.getDataSet(dataset_idranges_CA3_BCCCK).read(IDrange_CA3_BCCCK);
    file.getDataSet(dataset_idranges_CA3_BisC).read(IDrange_CA3_BisC);
    file.getDataSet(dataset_idranges_CA3_OLM).read(IDrange_CA3_OLM);
    file.getDataSet(dataset_idranges_CA3_TL).read(IDrange_CA3_TL);
    file.getDataSet(dataset_idranges_CA3_MFA).read(IDrange_CA3_MFA);
    file.getDataSet("Locs/HC").read(locs);// Access the 'Locs/HC' dataset from the file
    
    //file.getDataSet("CAregion").read(CA3_pc_region);
    HighFive::Group grpCAregion = file.getGroup("CAregion");
    
    file.getDataSet(dataset_idranges_EC_LEC).read(IDrange_EC_LEC);
    file.getDataSet(dataset_idranges_EC_MEC).read(IDrange_EC_MEC);
    file.getDataSet("Locs/HC").read(locs_EC);// Access the 'Locs/HC' dataset from the file
    //file.getDataSet("Locs/EC").read(locs_EC);
	
    map_IDoffset.insert(std::pair<std::string, int>("EC_LEC", IDrange_EC_LEC[0]));
	map_IDoffset.insert(std::pair<std::string, int>("EC_MEC", IDrange_EC_MEC[0]));
	map_IDoffset.insert(std::pair<std::string, int>("DG_GC", IDrange_DG_GC[0]));
	map_IDoffset.insert(std::pair<std::string, int>("CA3_PC", IDrange_CA3_PC[0]));
	map_IDoffset.insert(std::pair<std::string, int>("CA3_BC", IDrange_CA3_BC[0]));
	map_IDoffset.insert(std::pair<std::string, int>("CA3_AAC", IDrange_CA3_AAC[0]));
	map_IDoffset.insert(std::pair<std::string, int>("CA3_BCCCK", IDrange_CA3_BCCCK[0]));
	map_IDoffset.insert(std::pair<std::string, int>("CA3_BisC", IDrange_CA3_BisC[0]));
	map_IDoffset.insert(std::pair<std::string, int>("CA3_OLM", IDrange_CA3_OLM[0]));
	map_IDoffset.insert(std::pair<std::string, int>("CA3_TL", IDrange_CA3_TL[0]));
	map_IDoffset.insert(std::pair<std::string, int>("CA3_MFA", IDrange_CA3_MFA[0]));
	
	// Get MEC locations
	for (int id = IDrange_EC_MEC[0]; id <= IDrange_EC_MEC[1]; id++) {
         
         float x_coord_MEC = locs_EC[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_MEC = locs_EC[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_MEC.push_back(x_coord_MEC);
         locs_y_MEC.push_back(y_coord_MEC);
      }

    std::cout << "locs_x_MEC size is: " << locs_x_MEC.size() << std::endl;
    std::cout << "locs_y_MEC size is: " << locs_y_MEC.size() << std::endl;
    saveToBinaryFile(locs_x_MEC, locs_y_MEC, "locations/locs_MEC.dat");//MEC location
	
	// Get LEC locations
	for (int id = IDrange_EC_LEC[0]; id <= IDrange_EC_LEC[1]; id++) {
         
         float x_coord_LEC = locs_EC[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_LEC = locs_EC[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_LEC.push_back(x_coord_LEC);
         locs_y_LEC.push_back(y_coord_LEC);
      }

    std::cout << "locs_x_LEC size is: " << locs_x_LEC.size() << std::endl;
    std::cout << "locs_y_LEC size is: " << locs_y_LEC.size() << std::endl;
    saveToBinaryFile(locs_x_LEC, locs_y_LEC, "locations/locs_LEC.dat");//LEC location
    
   // Get DG-GC locations
    for (int id = IDrange_DG_GC[0]; id <= IDrange_DG_GC[1]; id++) {
         
         float x_coord = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_DGGC.push_back(x_coord);
         locs_y_DGGC.push_back(y_coord);
         
         if (x_coord < 0) {
             IDs_infra.push_back(id);
         } else { // else { ; else if (x_coord < 0) {
             IDs_supra.push_back(id);
         }
      }
      
    std::cout << "Number of IDs classified as supra: " << IDs_supra.size() << std::endl;
    std::cout << "Number of IDs classified as infra: " << IDs_infra.size() << std::endl;
    std::cout << "locs_x_DGGC size is: " << locs_x_DGGC.size() << std::endl;
    std::cout << "locs_y_DGGC size is: " << locs_y_DGGC.size() << std::endl;
    
    saveToBinaryFile(locs_x_DGGC, locs_y_DGGC, "locations/locs_DGGC.dat");//DG GC location
    
	
	// Get CA3 PC locations. Classify CA3 PC IDs into ab vs. c
	for (int id = IDrange_CA3_PC[0]; id <= IDrange_CA3_PC[1]; id++) {
         
         float x_coord_CA3PC = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_CA3PC = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_CA3PC.push_back(x_coord_CA3PC);
         locs_y_CA3PC.push_back(y_coord_CA3PC);
         
         // read one-byte dataset → 'a', 'b', or 'c'
         std::string utf8;// holds "a" / "b" / "c"   
         grpCAregion.getDataSet(std::to_string(id)).read(utf8);
         char regionTag = utf8.empty() ? 'x' : utf8[0];               // pick first byte

         if (regionTag == 'c')
             IDs_c.push_back(id);
         else if (regionTag == 'b')
             IDs_b.push_back(id);
         else
             IDs_a.push_back(id);
       }

    std::cout << "locs_x_CA3PC size is: " << locs_x_CA3PC.size() << std::endl;
    std::cout << "locs_y_CA3PC size is: " << locs_y_CA3PC.size() << std::endl;
    saveToBinaryFile(locs_x_CA3PC, locs_y_CA3PC, "locations/locs_CA3PC.dat");//CA3PC location
    
   
	// Get CA3 BC locations
	for (int id = IDrange_CA3_BC[0]; id <= IDrange_CA3_BC[1]; id++) {

         
         float x_coord_CA3BC = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_CA3BC = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_CA3BC.push_back(x_coord_CA3BC);
         locs_y_CA3BC.push_back(y_coord_CA3BC);
      }

    std::cout << "locs_x_CA3BC size is: " << locs_x_CA3BC.size() << std::endl;
    std::cout << "locs_y_CA3BC size is: " << locs_y_CA3BC.size() << std::endl;
    saveToBinaryFile(locs_x_CA3BC, locs_y_CA3BC, "locations/locs_CA3BC.dat");//CA3BC location
	
	
	// Get CA3 AAC locations
	for (int id = IDrange_CA3_AAC[0]; id <= IDrange_CA3_AAC[1]; id++) {
         
         float x_coord_CA3AAC = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_CA3AAC = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_CA3AAC.push_back(x_coord_CA3AAC);
         locs_y_CA3AAC.push_back(y_coord_CA3AAC);
      }

    std::cout << "locs_x_CA3AAC size is: " << locs_x_CA3AAC.size() << std::endl;
    std::cout << "locs_y_CA3AAC size is: " << locs_y_CA3AAC.size() << std::endl;
    saveToBinaryFile(locs_x_CA3AAC, locs_y_CA3AAC, "locations/locs_CA3AAC.dat");//CA3AAC location
	
	
	// Get CA3 BCCCK locations
	for (int id = IDrange_CA3_BCCCK[0]; id <= IDrange_CA3_BCCCK[1]; id++) {
         
         float x_coord_CA3BCCCK = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_CA3BCCCK = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_CA3BCCCK.push_back(x_coord_CA3BCCCK);
         locs_y_CA3BCCCK.push_back(y_coord_CA3BCCCK);
      }

    std::cout << "locs_x_CA3BCCCK size is: " << locs_x_CA3BCCCK.size() << std::endl;
    std::cout << "locs_y_CA3BCCCK size is: " << locs_y_CA3BCCCK.size() << std::endl;
    saveToBinaryFile(locs_x_CA3BCCCK, locs_y_CA3BCCCK, "locations/locs_CA3BCCCK.dat");//CA3BCCCK location
    
	
	// Get CA3 BisC locations
	for (int id = IDrange_CA3_BisC[0]; id <= IDrange_CA3_BisC[1]; id++) {
         
         float x_coord_CA3BisC = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_CA3BisC = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_CA3BisC.push_back(x_coord_CA3BisC);
         locs_y_CA3BisC.push_back(y_coord_CA3BisC);
      }

    std::cout << "locs_x_CA3BisC size is: " << locs_x_CA3BisC.size() << std::endl;
    std::cout << "locs_y_CA3BisC size is: " << locs_y_CA3BisC.size() << std::endl;
    saveToBinaryFile(locs_x_CA3BisC, locs_y_CA3BisC, "locations/locs_CA3BisC.dat");//CA3BisC location
    
     // Get CA3 MFA locations
	for (int id = IDrange_CA3_MFA[0]; id <= IDrange_CA3_MFA[1]; id++) {
         
         float x_coord_CA3MFA = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_CA3MFA = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_CA3MFA.push_back(x_coord_CA3MFA);
         locs_y_CA3MFA.push_back(y_coord_CA3MFA);
      }

    std::cout << "locs_x_CA3MFA size is: " << locs_x_CA3MFA.size() << std::endl;
    std::cout << "locs_y_CA3MFA size is: " << locs_y_CA3MFA.size() << std::endl;
    saveToBinaryFile(locs_x_CA3MFA, locs_y_CA3MFA, "locations/locs_CA3MFA.dat");//CA3MFA location
    
	
	// Get CA3 OLM locations
	for (int id = IDrange_CA3_OLM[0]; id <= IDrange_CA3_OLM[1]; id++) {
         
         float x_coord_CA3OLM = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_CA3OLM = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_CA3OLM.push_back(x_coord_CA3OLM);
         locs_y_CA3OLM.push_back(y_coord_CA3OLM);
      }

    std::cout << "locs_x_CA3OLM size is: " << locs_x_CA3OLM.size() << std::endl;
    std::cout << "locs_y_CA3OLM size is: " << locs_y_CA3OLM.size() << std::endl;
    saveToBinaryFile(locs_x_CA3OLM, locs_y_CA3OLM, "locations/locs_CA3OLM.dat");//CA3OLM location
	
	// Get CA3 Trilaminar locations
	for (int id = IDrange_CA3_TL[0]; id <= IDrange_CA3_TL[1]; id++) {
         
         float x_coord_CA3TL = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_CA3TL = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_CA3TL.push_back(x_coord_CA3TL);
         locs_y_CA3TL.push_back(y_coord_CA3TL);
      }

    std::cout << "locs_x_CA3TL size is: " << locs_x_CA3TL.size() << std::endl;
    std::cout << "locs_y_CA3TL size is: " << locs_y_CA3TL.size() << std::endl;
    saveToBinaryFile(locs_x_CA3TL, locs_y_CA3TL, "locations/locs_CA3TL.dat");//CA3TL location
    
//-----------------------------------------------------------------------
// MAIN CONNECTIVITY-LOADING SNIPPET (DIVERGENCE STYLE: PRE -> POST)
//-----------------------------------------------------------------------

std::map<std::string, std::map<int, std::vector<int>>> div_EC_LEC;
std::map<std::string, std::map<int, std::vector<int>>> div_EC_MEC;
std::map<std::string, std::map<int, std::vector<int>>> div_DG_GC;
std::map<std::string, std::map<int, std::vector<int>>> div_CA3_PC;
std::map<std::string, std::map<int, std::vector<int>>> div_CA3_AAC;
std::map<std::string, std::map<int, std::vector<int>>> div_CA3_BC;
std::map<std::string, std::map<int, std::vector<int>>> div_CA3_BCCCK;
std::map<std::string, std::map<int, std::vector<int>>> div_CA3_BisC;
std::map<std::string, std::map<int, std::vector<int>>> div_CA3_MFA;
std::map<std::string, std::map<int, std::vector<int>>> div_CA3_OLM;
std::map<std::string, std::map<int, std::vector<int>>> div_CA3_TL;


// ==========================================================================
// CA3_PC (Pyramidal Cells): PRE ∈ { EC_LEC, EC_MEC, CA3_PC, DG_GC,
//                                  CA3_AAC, CA3_BC, CA3_BCCCK, CA3_BisC,
//                                  CA3_MFA, CA3_OLM, CA3_TL }
// ==========================================================================

// EC-LEC -> CA3_PC
std::cout << "Loading EC_LEC to CA3_PC" << std::endl;
std::map<int, std::vector<int>> div_EC_LEC_CA3_PC;
for (int i = IDrange_EC_LEC[0]; i <= IDrange_EC_LEC[1]; i++) {
    std::string dataset_div_post = "Div/EC-LEC/CA3-PC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_PC[0];
    div_EC_LEC_CA3_PC.insert({ i - IDrange_EC_LEC[0], div_data });
}

// EC-MEC -> CA3_PC
std::cout << "Loading EC_MEC to CA3_PC" << std::endl;
std::map<int, std::vector<int>> div_EC_MEC_CA3_PC;
for (int i = IDrange_EC_MEC[0]; i <= IDrange_EC_MEC[1]; i++) {
    std::string dataset_div_post = "Div/EC-MEC/CA3-PC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_PC[0];
    div_EC_MEC_CA3_PC.insert({ i - IDrange_EC_MEC[0], div_data });
}

// CA3-PC -> CA3_PC
std::cout << "Loading CA3_PC to CA3_PC" << std::endl;
std::map<int, std::vector<int>> div_CA3_PC_CA3_PC;
for (int i = IDrange_CA3_PC[0]; i <= IDrange_CA3_PC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-PC/CA3-PC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_PC[0];
    div_CA3_PC_CA3_PC.insert({ i - IDrange_CA3_PC[0], div_data });
}

// DG-GC -> CA3_PC
std::cout << "Loading DG_GC to CA3_PC" << std::endl;
std::map<int, std::vector<int>> div_DG_GC_CA3_PC;
for (int i = IDrange_DG_GC[0]; i <= IDrange_DG_GC[1]; i++) {
    std::string dataset_div_post = "Div/DG-GC/CA3-PC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_PC[0];
    div_DG_GC_CA3_PC.insert({ i - IDrange_DG_GC[0], div_data });
}

// CA3-AAC -> CA3_PC
std::cout << "Loading CA3_AAC to CA3_PC" << std::endl;
std::map<int, std::vector<int>> div_CA3_AAC_CA3_PC;
for (int i = IDrange_CA3_AAC[0]; i <= IDrange_CA3_AAC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-AAC/CA3-PC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_PC[0];
    div_CA3_AAC_CA3_PC.insert({ i - IDrange_CA3_AAC[0], div_data });
}

// CA3-BC -> CA3_PC
std::cout << "Loading CA3_BC to CA3_PC" << std::endl;
std::map<int, std::vector<int>> div_CA3_BC_CA3_PC;
for (int i = IDrange_CA3_BC[0]; i <= IDrange_CA3_BC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-BC/CA3-PC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_PC[0];
    div_CA3_BC_CA3_PC.insert({ i - IDrange_CA3_BC[0], div_data });
}

// CA3-BCCCK -> CA3_PC
std::cout << "Loading CA3_BCCCK to CA3_PC" << std::endl;
std::map<int, std::vector<int>> div_CA3_BCCCK_CA3_PC;
for (int i = IDrange_CA3_BCCCK[0]; i <= IDrange_CA3_BCCCK[1]; i++) {
    std::string dataset_div_post = "Div/CA3-BCCCK/CA3-PC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_PC[0];
    div_CA3_BCCCK_CA3_PC.insert({ i - IDrange_CA3_BCCCK[0], div_data });
}

// CA3-Bistratified -> CA3_PC
std::cout << "Loading CA3_BisC to CA3_PC" << std::endl;
std::map<int, std::vector<int>> div_CA3_BisC_CA3_PC;
for (int i = IDrange_CA3_BisC[0]; i <= IDrange_CA3_BisC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-Bistratified/CA3-PC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_PC[0];
    div_CA3_BisC_CA3_PC.insert({ i - IDrange_CA3_BisC[0], div_data });
}

// CA3-MFA -> CA3_PC
std::cout << "Loading CA3_MFA to CA3_PC" << std::endl;
std::map<int, std::vector<int>> div_CA3_MFA_CA3_PC;
for (int i = IDrange_CA3_MFA[0]; i <= IDrange_CA3_MFA[1]; i++) {
    std::string dataset_div_post = "Div/CA3-MFA/CA3-PC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_PC[0];
    div_CA3_MFA_CA3_PC.insert({ i - IDrange_CA3_MFA[0], div_data });
}

// CA3-OLM -> CA3_PC
std::cout << "Loading CA3_OLM to CA3_PC" << std::endl;
std::map<int, std::vector<int>> div_CA3_OLM_CA3_PC;
for (int i = IDrange_CA3_OLM[0]; i <= IDrange_CA3_OLM[1]; i++) {
    std::string dataset_div_post = "Div/CA3-OLM/CA3-PC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_PC[0];
    div_CA3_OLM_CA3_PC.insert({ i - IDrange_CA3_OLM[0], div_data });
}

// CA3-Trilaminar -> CA3_PC
std::cout << "Loading CA3_TL to CA3_PC" << std::endl;
std::map<int, std::vector<int>> div_CA3_TL_CA3_PC;
for (int i = IDrange_CA3_TL[0]; i <= IDrange_CA3_TL[1]; i++) {
    std::string dataset_div_post = "Div/CA3-Trilaminar/CA3-PC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_PC[0];
    div_CA3_TL_CA3_PC.insert({ i - IDrange_CA3_TL[0], div_data });
}

// Register PRE maps (targets: CA3_PC)
div_EC_LEC.insert({ "CA3_PC", div_EC_LEC_CA3_PC });
div_EC_MEC.insert({ "CA3_PC", div_EC_MEC_CA3_PC });
div_CA3_PC.insert({ "CA3_PC", div_CA3_PC_CA3_PC });
div_DG_GC.insert({ "CA3_PC", div_DG_GC_CA3_PC });
div_CA3_AAC.insert({ "CA3_PC", div_CA3_AAC_CA3_PC });
div_CA3_BC.insert({ "CA3_PC", div_CA3_BC_CA3_PC });
div_CA3_BCCCK.insert({ "CA3_PC", div_CA3_BCCCK_CA3_PC });
div_CA3_BisC.insert({ "CA3_PC", div_CA3_BisC_CA3_PC });
div_CA3_MFA.insert({ "CA3_PC", div_CA3_MFA_CA3_PC });
div_CA3_OLM.insert({ "CA3_PC", div_CA3_OLM_CA3_PC });
div_CA3_TL.insert({ "CA3_PC", div_CA3_TL_CA3_PC });


// ==========================================================================
// CA3_BC: PRE ∈ { EC_LEC, EC_MEC, DG_GC, CA3_PC, CA3_BC, CA3_BCCCK,
//                 CA3_BisC, CA3_MFA, CA3_OLM, CA3_TL }
// ==========================================================================

// EC-LEC -> CA3_BC
std::cout << "Loading EC_LEC to CA3_BC" << std::endl;
std::map<int, std::vector<int>> div_EC_LEC_CA3_BC;
for (int i = IDrange_EC_LEC[0]; i <= IDrange_EC_LEC[1]; i++) {
    std::string dataset_div_post = "Div/EC-LEC/CA3-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_BC[0];
    div_EC_LEC_CA3_BC.insert({ i - IDrange_EC_LEC[0], div_data });
}

// EC-MEC -> CA3_BC
std::cout << "Loading EC_MEC to CA3_BC" << std::endl;
std::map<int, std::vector<int>> div_EC_MEC_CA3_BC;
for (int i = IDrange_EC_MEC[0]; i <= IDrange_EC_MEC[1]; i++) {
    std::string dataset_div_post = "Div/EC-MEC/CA3-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_BC[0];
    div_EC_MEC_CA3_BC.insert({ i - IDrange_EC_MEC[0], div_data });
}

// DG-GC -> CA3_BC
std::cout << "Loading DG_GC to CA3_BC" << std::endl;
std::map<int, std::vector<int>> div_DG_GC_CA3_BC;
for (int i = IDrange_DG_GC[0]; i <= IDrange_DG_GC[1]; i++) {
    std::string dataset_div_post = "Div/DG-GC/CA3-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_BC[0];
    div_DG_GC_CA3_BC.insert({ i - IDrange_DG_GC[0], div_data });
}

// CA3-PC -> CA3_BC
std::cout << "Loading CA3_PC to CA3_BC" << std::endl;
std::map<int, std::vector<int>> div_CA3_PC_CA3_BC;
for (int i = IDrange_CA3_PC[0]; i <= IDrange_CA3_PC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-PC/CA3-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_BC[0];
    div_CA3_PC_CA3_BC.insert({ i - IDrange_CA3_PC[0], div_data });
}

// CA3-BC -> CA3_BC
std::cout << "Loading CA3_BC to CA3_BC" << std::endl;
std::map<int, std::vector<int>> div_CA3_BC_CA3_BC;
for (int i = IDrange_CA3_BC[0]; i <= IDrange_CA3_BC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-BC/CA3-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_BC[0];
    div_CA3_BC_CA3_BC.insert({ i - IDrange_CA3_BC[0], div_data });
}

// CA3-BCCCK -> CA3_BC
std::cout << "Loading CA3_BCCCK to CA3_BC" << std::endl;
std::map<int, std::vector<int>> div_CA3_BCCCK_CA3_BC;
for (int i = IDrange_CA3_BCCCK[0]; i <= IDrange_CA3_BCCCK[1]; i++) {
    std::string dataset_div_post = "Div/CA3-BCCCK/CA3-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_BC[0];
    div_CA3_BCCCK_CA3_BC.insert({ i - IDrange_CA3_BCCCK[0], div_data });
}

// CA3-Bistratified -> CA3_BC
std::cout << "Loading CA3_BisC to CA3_BC" << std::endl;
std::map<int, std::vector<int>> div_CA3_BisC_CA3_BC;
for (int i = IDrange_CA3_BisC[0]; i <= IDrange_CA3_BisC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-Bistratified/CA3-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_BC[0];
    div_CA3_BisC_CA3_BC.insert({ i - IDrange_CA3_BisC[0], div_data });
}

// CA3-MFA -> CA3_BC
std::cout << "Loading CA3_MFA to CA3_BC" << std::endl;
std::map<int, std::vector<int>> div_CA3_MFA_CA3_BC;
for (int i = IDrange_CA3_MFA[0]; i <= IDrange_CA3_MFA[1]; i++) {
    std::string dataset_div_post = "Div/CA3-MFA/CA3-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_BC[0];
    div_CA3_MFA_CA3_BC.insert({ i - IDrange_CA3_MFA[0], div_data });
}

// CA3-OLM -> CA3_BC
std::cout << "Loading CA3_OLM to CA3_BC" << std::endl;
std::map<int, std::vector<int>> div_CA3_OLM_CA3_BC;
for (int i = IDrange_CA3_OLM[0]; i <= IDrange_CA3_OLM[1]; i++) {
    std::string dataset_div_post = "Div/CA3-OLM/CA3-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_BC[0];
    div_CA3_OLM_CA3_BC.insert({ i - IDrange_CA3_OLM[0], div_data });
}

// CA3-Trilaminar -> CA3_BC
std::cout << "Loading CA3_TL to CA3_BC" << std::endl;
std::map<int, std::vector<int>> div_CA3_TL_CA3_BC;
for (int i = IDrange_CA3_TL[0]; i <= IDrange_CA3_TL[1]; i++) {
    std::string dataset_div_post = "Div/CA3-Trilaminar/CA3-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_BC[0];
    div_CA3_TL_CA3_BC.insert({ i - IDrange_CA3_TL[0], div_data });
}

// Register PRE maps (targets: CA3_BC)
div_EC_LEC.insert({ "CA3_BC", div_EC_LEC_CA3_BC });
div_EC_MEC.insert({ "CA3_BC", div_EC_MEC_CA3_BC });
div_DG_GC.insert({ "CA3_BC", div_DG_GC_CA3_BC });
div_CA3_PC.insert({ "CA3_BC", div_CA3_PC_CA3_BC });
div_CA3_BC.insert({ "CA3_BC", div_CA3_BC_CA3_BC });
div_CA3_BCCCK.insert({ "CA3_BC", div_CA3_BCCCK_CA3_BC });
div_CA3_BisC.insert({ "CA3_BC", div_CA3_BisC_CA3_BC });
div_CA3_MFA.insert({ "CA3_BC", div_CA3_MFA_CA3_BC });
div_CA3_OLM.insert({ "CA3_BC", div_CA3_OLM_CA3_BC });
div_CA3_TL.insert({ "CA3_BC", div_CA3_TL_CA3_BC });


// ==========================================================================
// CA3_AAC: PRE ∈ { EC_LEC, EC_MEC, DG_GC, CA3_PC, CA3_BCCCK, CA3_BisC, CA3_OLM, CA3_TL }
// ==========================================================================

// EC-LEC -> CA3_AAC
std::cout << "Loading EC_LEC to CA3_AAC" << std::endl;
std::map<int, std::vector<int>> div_EC_LEC_CA3_AAC;
for (int i = IDrange_EC_LEC[0]; i <= IDrange_EC_LEC[1]; i++) {
    std::string dataset_div_post = "Div/EC-LEC/CA3-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_AAC[0];
    div_EC_LEC_CA3_AAC.insert({ i - IDrange_EC_LEC[0], div_data });
}

// EC-MEC -> CA3_AAC
std::cout << "Loading EC_MEC to CA3_AAC" << std::endl;
std::map<int, std::vector<int>> div_EC_MEC_CA3_AAC;
for (int i = IDrange_EC_MEC[0]; i <= IDrange_EC_MEC[1]; i++) {
    std::string dataset_div_post = "Div/EC-MEC/CA3-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_AAC[0];
    div_EC_MEC_CA3_AAC.insert({ i - IDrange_EC_MEC[0], div_data });
}

// DG-GC -> CA3_AAC
std::cout << "Loading DG_GC to CA3_AAC" << std::endl;
std::map<int, std::vector<int>> div_DG_GC_CA3_AAC;
for (int i = IDrange_DG_GC[0]; i <= IDrange_DG_GC[1]; i++) {
    std::string dataset_div_post = "Div/DG-GC/CA3-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_AAC[0];
    div_DG_GC_CA3_AAC.insert({ i - IDrange_DG_GC[0], div_data });
}

// CA3-PC -> CA3_AAC
std::cout << "Loading CA3_PC to CA3_AAC" << std::endl;
std::map<int, std::vector<int>> div_CA3_PC_CA3_AAC;
for (int i = IDrange_CA3_PC[0]; i <= IDrange_CA3_PC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-PC/CA3-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_AAC[0];
    div_CA3_PC_CA3_AAC.insert({ i - IDrange_CA3_PC[0], div_data });
}

// CA3-BCCCK -> CA3_AAC
std::cout << "Loading CA3_BCCCK to CA3_AAC" << std::endl;
std::map<int, std::vector<int>> div_CA3_BCCCK_CA3_AAC;
for (int i = IDrange_CA3_BCCCK[0]; i <= IDrange_CA3_BCCCK[1]; i++) {
    std::string dataset_div_post = "Div/CA3-BCCCK/CA3-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_AAC[0];
    div_CA3_BCCCK_CA3_AAC.insert({ i - IDrange_CA3_BCCCK[0], div_data });
}

// CA3-Bistratified -> CA3_AAC
std::cout << "Loading CA3_BisC to CA3_AAC" << std::endl;
std::map<int, std::vector<int>> div_CA3_BisC_CA3_AAC;
for (int i = IDrange_CA3_BisC[0]; i <= IDrange_CA3_BisC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-Bistratified/CA3-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_AAC[0];
    div_CA3_BisC_CA3_AAC.insert({ i - IDrange_CA3_BisC[0], div_data });
}

// CA3-OLM -> CA3_AAC
std::cout << "Loading CA3_OLM to CA3_AAC" << std::endl;
std::map<int, std::vector<int>> div_CA3_OLM_CA3_AAC;
for (int i = IDrange_CA3_OLM[0]; i <= IDrange_CA3_OLM[1]; i++) {
    std::string dataset_div_post = "Div/CA3-OLM/CA3-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_AAC[0];
    div_CA3_OLM_CA3_AAC.insert({ i - IDrange_CA3_OLM[0], div_data });
}

// CA3-Trilaminar -> CA3_AAC
std::cout << "Loading CA3_TL to CA3_AAC" << std::endl;
std::map<int, std::vector<int>> div_CA3_TL_CA3_AAC;
for (int i = IDrange_CA3_TL[0]; i <= IDrange_CA3_TL[1]; i++) {
    std::string dataset_div_post = "Div/CA3-Trilaminar/CA3-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_AAC[0];
    div_CA3_TL_CA3_AAC.insert({ i - IDrange_CA3_TL[0], div_data });
}

// Register PRE maps (targets: CA3_AAC)
div_EC_LEC.insert({ "CA3_AAC", div_EC_LEC_CA3_AAC });
div_EC_MEC.insert({ "CA3_AAC", div_EC_MEC_CA3_AAC });
div_DG_GC.insert({ "CA3_AAC", div_DG_GC_CA3_AAC });
div_CA3_PC.insert({ "CA3_AAC", div_CA3_PC_CA3_AAC });
div_CA3_BCCCK.insert({ "CA3_AAC", div_CA3_BCCCK_CA3_AAC });
div_CA3_BisC.insert({ "CA3_AAC", div_CA3_BisC_CA3_AAC });
div_CA3_OLM.insert({ "CA3_AAC", div_CA3_OLM_CA3_AAC });
div_CA3_TL.insert({ "CA3_AAC", div_CA3_TL_CA3_AAC });


// ==========================================================================
// CA3_BCCCK: PRE ∈ { DG_GC, CA3_PC, CA3_BC, CA3_BisC, CA3_MFA, CA3_OLM, CA3_TL }
// ==========================================================================

// DG-GC -> CA3_BCCCK
std::cout << "Loading DG_GC to CA3_BCCCK" << std::endl;
std::map<int, std::vector<int>> div_DG_GC_CA3_BCCCK;
for (int i = IDrange_DG_GC[0]; i <= IDrange_DG_GC[1]; i++) {
    std::string dataset_div_post = "Div/DG-GC/CA3-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_BCCCK[0];
    div_DG_GC_CA3_BCCCK.insert({ i - IDrange_DG_GC[0], div_data });
}

// CA3-PC -> CA3_BCCCK
std::cout << "Loading CA3_PC to CA3_BCCCK" << std::endl;
std::map<int, std::vector<int>> div_CA3_PC_CA3_BCCCK;
for (int i = IDrange_CA3_PC[0]; i <= IDrange_CA3_PC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-PC/CA3-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_BCCCK[0];
    div_CA3_PC_CA3_BCCCK.insert({ i - IDrange_CA3_PC[0], div_data });
}

// CA3-BC -> CA3_BCCCK
std::cout << "Loading CA3_BC to CA3_BCCCK" << std::endl;
std::map<int, std::vector<int>> div_CA3_BC_CA3_BCCCK;
for (int i = IDrange_CA3_BC[0]; i <= IDrange_CA3_BC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-BC/CA3-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_BCCCK[0];
    div_CA3_BC_CA3_BCCCK.insert({ i - IDrange_CA3_BC[0], div_data });
}

// CA3-BCCCK -> CA3_BCCCK
std::cout << "Loading CA3_BCCCK to CA3_BCCCK" << std::endl;
std::map<int, std::vector<int>> div_CA3_BCCCK_CA3_BCCCK;
for (int i = IDrange_CA3_BCCCK[0]; i <= IDrange_CA3_BCCCK[1]; i++) {
    std::string dataset_div_post = "Div/CA3-BCCCK/CA3-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_BCCCK[0];
    div_CA3_BCCCK_CA3_BCCCK.insert({ i - IDrange_CA3_BCCCK[0], div_data });
}

// CA3-Bistratified -> CA3_BCCCK
std::cout << "Loading CA3_BisC to CA3_BCCCK" << std::endl;
std::map<int, std::vector<int>> div_CA3_BisC_CA3_BCCCK;
for (int i = IDrange_CA3_BisC[0]; i <= IDrange_CA3_BisC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-Bistratified/CA3-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_BCCCK[0];
    div_CA3_BisC_CA3_BCCCK.insert({ i - IDrange_CA3_BisC[0], div_data });
}

// CA3-MFA -> CA3_BCCCK
std::cout << "Loading CA3_MFA to CA3_BCCCK" << std::endl;
std::map<int, std::vector<int>> div_CA3_MFA_CA3_BCCCK;
for (int i = IDrange_CA3_MFA[0]; i <= IDrange_CA3_MFA[1]; i++) {
    std::string dataset_div_post = "Div/CA3-MFA/CA3-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_BCCCK[0];
    div_CA3_MFA_CA3_BCCCK.insert({ i - IDrange_CA3_MFA[0], div_data });
}

// CA3-OLM -> CA3_BCCCK
std::cout << "Loading CA3_OLM to CA3_BCCCK" << std::endl;
std::map<int, std::vector<int>> div_CA3_OLM_CA3_BCCCK;
for (int i = IDrange_CA3_OLM[0]; i <= IDrange_CA3_OLM[1]; i++) {
    std::string dataset_div_post = "Div/CA3-OLM/CA3-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_BCCCK[0];
    div_CA3_OLM_CA3_BCCCK.insert({ i - IDrange_CA3_OLM[0], div_data });
}

// CA3-Trilaminar -> CA3_BCCCK
std::cout << "Loading CA3_TL to CA3_BCCCK" << std::endl;
std::map<int, std::vector<int>> div_CA3_TL_CA3_BCCCK;
for (int i = IDrange_CA3_TL[0]; i <= IDrange_CA3_TL[1]; i++) {
    std::string dataset_div_post = "Div/CA3-Trilaminar/CA3-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_BCCCK[0];
    div_CA3_TL_CA3_BCCCK.insert({ i - IDrange_CA3_TL[0], div_data });
}

// Register PRE maps (targets: CA3_BCCCK)
div_DG_GC.insert({ "CA3_BCCCK", div_DG_GC_CA3_BCCCK });
div_CA3_PC.insert({ "CA3_BCCCK", div_CA3_PC_CA3_BCCCK });
div_CA3_BC.insert({ "CA3_BCCCK", div_CA3_BC_CA3_BCCCK });
div_CA3_BCCCK.insert({ "CA3_BCCCK", div_CA3_BCCCK_CA3_BCCCK });
div_CA3_BisC.insert({ "CA3_BCCCK", div_CA3_BisC_CA3_BCCCK });
div_CA3_MFA.insert({ "CA3_BCCCK", div_CA3_MFA_CA3_BCCCK });
div_CA3_OLM.insert({ "CA3_BCCCK", div_CA3_OLM_CA3_BCCCK });
div_CA3_TL.insert({ "CA3_BCCCK", div_CA3_TL_CA3_BCCCK });


// ==========================================================================
// CA3_BisC: PRE ∈ { DG_GC, CA3_PC, CA3_BC, CA3_BisC, CA3_MFA, CA3_OLM, CA3_TL }
// ==========================================================================

// DG-GC -> CA3_BisC
std::cout << "Loading DG_GC to CA3_BisC" << std::endl;
std::map<int, std::vector<int>> div_DG_GC_CA3_BisC;
for (int i = IDrange_DG_GC[0]; i <= IDrange_DG_GC[1]; i++) {
    std::string dataset_div_post = "Div/DG-GC/CA3-Bistratified/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_BisC[0];
    div_DG_GC_CA3_BisC.insert({ i - IDrange_DG_GC[0], div_data });
}

// CA3-PC -> CA3_BisC
std::cout << "Loading CA3_PC to CA3_BisC" << std::endl;
std::map<int, std::vector<int>> div_CA3_PC_CA3_BisC;
for (int i = IDrange_CA3_PC[0]; i <= IDrange_CA3_PC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-PC/CA3-Bistratified/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_BisC[0];
    div_CA3_PC_CA3_BisC.insert({ i - IDrange_CA3_PC[0], div_data });
}

// CA3-BC -> CA3_BisC
std::cout << "Loading CA3_BC to CA3_BisC" << std::endl;
std::map<int, std::vector<int>> div_CA3_BC_CA3_BisC;
for (int i = IDrange_CA3_BC[0]; i <= IDrange_CA3_BC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-BC/CA3-Bistratified/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_BisC[0];
    div_CA3_BC_CA3_BisC.insert({ i - IDrange_CA3_BC[0], div_data });
}

// CA3-BCCCK -> CA3_BisC
std::cout << "Loading CA3_BCCCK to CA3_BisC" << std::endl;
std::map<int, std::vector<int>> div_CA3_BCCCK_CA3_BisC;
for (int i = IDrange_CA3_BCCCK[0]; i <= IDrange_CA3_BCCCK[1]; i++) {
    std::string dataset_div_post = "Div/CA3-BCCCK/CA3-Bistratified/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_BisC[0];
    div_CA3_BCCCK_CA3_BisC.insert({ i - IDrange_CA3_BCCCK[0], div_data });
}

// CA3-BisC -> CA3_BisC
std::cout << "Loading CA3_BisC to CA3_BisC" << std::endl;
std::map<int, std::vector<int>> div_CA3_BisC_CA3_BisC;
for (int i = IDrange_CA3_BisC[0]; i <= IDrange_CA3_BisC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-Bistratified/CA3-Bistratified/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_BisC[0];
    div_CA3_BisC_CA3_BisC.insert({ i - IDrange_CA3_BisC[0], div_data });
}

// CA3-MFA -> CA3_BisC
std::cout << "Loading CA3_MFA to CA3_BisC" << std::endl;
std::map<int, std::vector<int>> div_CA3_MFA_CA3_BisC;
for (int i = IDrange_CA3_MFA[0]; i <= IDrange_CA3_MFA[1]; i++) {
    std::string dataset_div_post = "Div/CA3-MFA/CA3-Bistratified/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_BisC[0];
    div_CA3_MFA_CA3_BisC.insert({ i - IDrange_CA3_MFA[0], div_data });
}

// CA3-OLM -> CA3_BisC
std::cout << "Loading CA3_OLM to CA3_BisC" << std::endl;
std::map<int, std::vector<int>> div_CA3_OLM_CA3_BisC;
for (int i = IDrange_CA3_OLM[0]; i <= IDrange_CA3_OLM[1]; i++) {
    std::string dataset_div_post = "Div/CA3-OLM/CA3-Bistratified/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_BisC[0];
    div_CA3_OLM_CA3_BisC.insert({ i - IDrange_CA3_OLM[0], div_data });
}

// CA3-Trilaminar -> CA3_BisC
std::cout << "Loading CA3_TL to CA3_BisC" << std::endl;
std::map<int, std::vector<int>> div_CA3_TL_CA3_BisC;
for (int i = IDrange_CA3_TL[0]; i <= IDrange_CA3_TL[1]; i++) {
    std::string dataset_div_post = "Div/CA3-Trilaminar/CA3-Bistratified/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_BisC[0];
    div_CA3_TL_CA3_BisC.insert({ i - IDrange_CA3_TL[0], div_data });
}

// Register PRE maps (targets: CA3_BisC)
div_DG_GC.insert({ "CA3_BisC", div_DG_GC_CA3_BisC });
div_CA3_PC.insert({ "CA3_BisC", div_CA3_PC_CA3_BisC });
div_CA3_BC.insert({ "CA3_BisC", div_CA3_BC_CA3_BisC });
div_CA3_BCCCK.insert({ "CA3_BisC", div_CA3_BCCCK_CA3_BisC });
div_CA3_BisC.insert({ "CA3_BisC", div_CA3_BisC_CA3_BisC });
div_CA3_MFA.insert({ "CA3_BisC", div_CA3_MFA_CA3_BisC });
div_CA3_OLM.insert({ "CA3_BisC", div_CA3_OLM_CA3_BisC });
div_CA3_TL.insert({ "CA3_BisC", div_CA3_TL_CA3_BisC });


// ==========================================================================
// CA3_MFA: PRE ∈ { DG_GC, CA3_PC, CA3_BC, CA3_BCCCK, CA3_BisC,
//                  CA3_MFA, CA3_OLM, CA3_TL }
// ==========================================================================

// DG-GC -> CA3_MFA
std::cout << "Loading DG_GC to CA3_MFA" << std::endl;
std::map<int, std::vector<int>> div_DG_GC_CA3_MFA;
for (int i = IDrange_DG_GC[0]; i <= IDrange_DG_GC[1]; i++) {
    std::string dataset_div_post = "Div/DG-GC/CA3-MFA/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_MFA[0];
    div_DG_GC_CA3_MFA.insert({ i - IDrange_DG_GC[0], div_data });
}

// CA3-PC -> CA3_MFA
std::cout << "Loading CA3_PC to CA3_MFA" << std::endl;
std::map<int, std::vector<int>> div_CA3_PC_CA3_MFA;
for (int i = IDrange_CA3_PC[0]; i <= IDrange_CA3_PC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-PC/CA3-MFA/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_MFA[0];
    div_CA3_PC_CA3_MFA.insert({ i - IDrange_CA3_PC[0], div_data });
}

// CA3-BC -> CA3_MFA
std::cout << "Loading CA3_BC to CA3_MFA" << std::endl;
std::map<int, std::vector<int>> div_CA3_BC_CA3_MFA;
for (int i = IDrange_CA3_BC[0]; i <= IDrange_CA3_BC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-BC/CA3-MFA/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_MFA[0];
    div_CA3_BC_CA3_MFA.insert({ i - IDrange_CA3_BC[0], div_data });
}

// CA3-BCCCK -> CA3_MFA
std::cout << "Loading CA3_BCCCK to CA3_MFA" << std::endl;
std::map<int, std::vector<int>> div_CA3_BCCCK_CA3_MFA;
for (int i = IDrange_CA3_BCCCK[0]; i <= IDrange_CA3_BCCCK[1]; i++) {
    std::string dataset_div_post = "Div/CA3-BCCCK/CA3-MFA/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_MFA[0];
    div_CA3_BCCCK_CA3_MFA.insert({ i - IDrange_CA3_BCCCK[0], div_data });
}

// CA3-Bistratified -> CA3_MFA
std::cout << "Loading CA3_BisC to CA3_MFA" << std::endl;
std::map<int, std::vector<int>> div_CA3_BisC_CA3_MFA;
for (int i = IDrange_CA3_BisC[0]; i <= IDrange_CA3_BisC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-Bistratified/CA3-MFA/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_MFA[0];
    div_CA3_BisC_CA3_MFA.insert({ i - IDrange_CA3_BisC[0], div_data });
}

// CA3-MFA -> CA3_MFA
std::cout << "Loading CA3_MFA to CA3_MFA" << std::endl;
std::map<int, std::vector<int>> div_CA3_MFA_CA3_MFA;
for (int i = IDrange_CA3_MFA[0]; i <= IDrange_CA3_MFA[1]; i++) {
    std::string dataset_div_post = "Div/CA3-MFA/CA3-MFA/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_MFA[0];
    div_CA3_MFA_CA3_MFA.insert({ i - IDrange_CA3_MFA[0], div_data });
}

// CA3-OLM -> CA3_MFA
std::cout << "Loading CA3_OLM to CA3_MFA" << std::endl;
std::map<int, std::vector<int>> div_CA3_OLM_CA3_MFA;
for (int i = IDrange_CA3_OLM[0]; i <= IDrange_CA3_OLM[1]; i++) {
    std::string dataset_div_post = "Div/CA3-OLM/CA3-MFA/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_MFA[0];
    div_CA3_OLM_CA3_MFA.insert({ i - IDrange_CA3_OLM[0], div_data });
}

// CA3-Trilaminar -> CA3_MFA
std::cout << "Loading CA3_TL to CA3_MFA" << std::endl;
std::map<int, std::vector<int>> div_CA3_TL_CA3_MFA;
for (int i = IDrange_CA3_TL[0]; i <= IDrange_CA3_TL[1]; i++) {
    std::string dataset_div_post = "Div/CA3-Trilaminar/CA3-MFA/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_MFA[0];
    div_CA3_TL_CA3_MFA.insert({ i - IDrange_CA3_TL[0], div_data });
}

// Register PRE maps (targets: CA3_MFA)
div_DG_GC.insert({ "CA3_MFA", div_DG_GC_CA3_MFA });
div_CA3_PC.insert({ "CA3_MFA", div_CA3_PC_CA3_MFA });
div_CA3_BC.insert({ "CA3_MFA", div_CA3_BC_CA3_MFA });
div_CA3_BCCCK.insert({ "CA3_MFA", div_CA3_BCCCK_CA3_MFA });
div_CA3_BisC.insert({ "CA3_MFA", div_CA3_BisC_CA3_MFA });
div_CA3_MFA.insert({ "CA3_MFA", div_CA3_MFA_CA3_MFA });
div_CA3_OLM.insert({ "CA3_MFA", div_CA3_OLM_CA3_MFA });
div_CA3_TL.insert({ "CA3_MFA", div_CA3_TL_CA3_MFA });


// ==========================================================================
// CA3_OLM: PRE ∈ { CA3_PC, CA3_BisC, CA3_OLM, CA3_TL }
// ==========================================================================

// CA3-PC -> CA3_OLM
std::cout << "Loading CA3_PC to CA3_OLM" << std::endl;
std::map<int, std::vector<int>> div_CA3_PC_CA3_OLM;
for (int i = IDrange_CA3_PC[0]; i <= IDrange_CA3_PC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-PC/CA3-OLM/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_OLM[0];
    div_CA3_PC_CA3_OLM.insert({ i - IDrange_CA3_PC[0], div_data });
}

// CA3-BisC -> CA3_OLM
std::cout << "Loading CA3_BisC to CA3_OLM" << std::endl;
std::map<int, std::vector<int>> div_CA3_BisC_CA3_OLM;
for (int i = IDrange_CA3_BisC[0]; i <= IDrange_CA3_BisC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-Bistratified/CA3-OLM/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_OLM[0];
    div_CA3_BisC_CA3_OLM.insert({ i - IDrange_CA3_BisC[0], div_data });
}

// CA3-OLM -> CA3_OLM
std::cout << "Loading CA3_OLM to CA3_OLM" << std::endl;
std::map<int, std::vector<int>> div_CA3_OLM_CA3_OLM;
for (int i = IDrange_CA3_OLM[0]; i <= IDrange_CA3_OLM[1]; i++) {
    std::string dataset_div_post = "Div/CA3-OLM/CA3-OLM/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_OLM[0];
    div_CA3_OLM_CA3_OLM.insert({ i - IDrange_CA3_OLM[0], div_data });
}

// CA3-Trilaminar -> CA3_OLM
std::cout << "Loading CA3_TL to CA3_OLM" << std::endl;
std::map<int, std::vector<int>> div_CA3_TL_CA3_OLM;
for (int i = IDrange_CA3_TL[0]; i <= IDrange_CA3_TL[1]; i++) {
    std::string dataset_div_post = "Div/CA3-Trilaminar/CA3-OLM/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_OLM[0];
    div_CA3_TL_CA3_OLM.insert({ i - IDrange_CA3_TL[0], div_data });
}

// Register PRE maps (targets: CA3_OLM)
div_CA3_PC.insert({ "CA3_OLM", div_CA3_PC_CA3_OLM });
div_CA3_BisC.insert({ "CA3_OLM", div_CA3_BisC_CA3_OLM });
div_CA3_OLM.insert({ "CA3_OLM", div_CA3_OLM_CA3_OLM });
div_CA3_TL.insert({ "CA3_OLM", div_CA3_TL_CA3_OLM });


// ==========================================================================
// CA3_TL: PRE ∈ { CA3_PC }   (only, per convergence snippet)
// ==========================================================================

// CA3-PC -> CA3_TL
std::cout << "Loading CA3_PC to CA3_TL" << std::endl;
std::map<int, std::vector<int>> div_CA3_PC_CA3_TL;
for (int i = IDrange_CA3_PC[0]; i <= IDrange_CA3_PC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-PC/CA3-Trilaminar/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_TL[0];
    div_CA3_PC_CA3_TL.insert({ i - IDrange_CA3_PC[0], div_data });
}

// CA3-BisC -> CA3_TL
std::cout << "Loading CA3_BisC to CA3_TL" << std::endl;
std::map<int, std::vector<int>> div_CA3_BisC_CA3_TL;
for (int i = IDrange_CA3_BisC[0]; i <= IDrange_CA3_BisC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-Bistratified/CA3-Trilaminar/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_TL[0];
    div_CA3_BisC_CA3_TL.insert({ i - IDrange_CA3_BisC[0], div_data });
}

// CA3-OLM -> CA3_TL
std::cout << "Loading CA3_OLM to CA3_TL" << std::endl;
std::map<int, std::vector<int>> div_CA3_OLM_CA3_TL;
for (int i = IDrange_CA3_OLM[0]; i <= IDrange_CA3_OLM[1]; i++) {
    std::string dataset_div_post = "Div/CA3-OLM/CA3-Trilaminar/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_TL[0];
    div_CA3_OLM_CA3_TL.insert({ i - IDrange_CA3_OLM[0], div_data });
}

// CA3-TL -> CA3_TL
std::cout << "Loading CA3_TL to CA3_TL" << std::endl;
std::map<int, std::vector<int>> div_CA3_TL_CA3_TL;
for (int i = IDrange_CA3_TL[0]; i <= IDrange_CA3_TL[1]; i++) {
    std::string dataset_div_post = "Div/CA3-Trilaminar/CA3-Trilaminar/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA3_TL[0];
    div_CA3_TL_CA3_TL.insert({ i - IDrange_CA3_TL[0], div_data });
}

// Register PRE maps (targets: CA3_TL)
div_CA3_PC.insert({ "CA3_TL", div_CA3_PC_CA3_TL });
div_CA3_BisC.insert({ "CA3_TL", div_CA3_BisC_CA3_TL });
div_CA3_OLM.insert({ "CA3_TL", div_CA3_OLM_CA3_TL });
div_CA3_TL.insert({ "CA3_TL", div_CA3_TL_CA3_TL });


// ==========================================================================
// Finally add divergence maps into big map
// ==========================================================================

map_bigcon.insert({ "EC_LEC",   div_EC_LEC });
map_bigcon.insert({ "EC_MEC",   div_EC_MEC });
map_bigcon.insert({ "DG_GC",    div_DG_GC });
map_bigcon.insert({ "CA3_PC",   div_CA3_PC });
map_bigcon.insert({ "CA3_BC",   div_CA3_BC });
map_bigcon.insert({ "CA3_AAC",  div_CA3_AAC });
map_bigcon.insert({ "CA3_BCCCK",div_CA3_BCCCK });
map_bigcon.insert({ "CA3_BisC", div_CA3_BisC });
map_bigcon.insert({ "CA3_MFA",  div_CA3_MFA });
map_bigcon.insert({ "CA3_OLM",  div_CA3_OLM });
map_bigcon.insert({ "CA3_TL",   div_CA3_TL });

