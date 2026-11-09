// Read ID ranges and coordinates, then load connectivity.
// This header contains statements included inside main, sharing its local variables.

    // Open HDF5 connectivity file for reading
    File file(FILE_NAME, File::ReadOnly);

    // Obtain ID ranges
    std::string dataset_idranges_EC_LEC3 = "IDranges/EC/LEC3";
    std::string dataset_idranges_EC_MEC3 = "IDranges/EC/MEC3";
	std::string dataset_idranges_CA3_PC = "IDranges/CA3/PC";
	std::string dataset_idranges_CA1_PC = "IDranges/CA1/PC";
	std::string dataset_idranges_CA1_BC = "IDranges/CA1/BC";
	std::string dataset_idranges_CA1_AAC = "IDranges/CA1/AAC";
	std::string dataset_idranges_CA1_BCCCK = "IDranges/CA1/BCCCK";
	std::string dataset_idranges_CA1_BisC = "IDranges/CA1/Bistratified";
	std::string dataset_idranges_CA1_OLM = "IDranges/CA1/OLM";
	std::string dataset_idranges_CA1_TL = "IDranges/CA1/Trilaminar";
	std::string dataset_idranges_CA1_NG = "IDranges/CA1/Neurogliaform";

    std::vector<int> IDrange_EC_LEC3;
    std::vector<int> IDrange_EC_MEC3;
	std::vector<int> IDrange_CA3_PC;
	std::vector<int> IDrange_CA1_PC;
	std::vector<int> IDrange_CA1_BC;
	std::vector<int> IDrange_CA1_AAC;
	std::vector<int> IDrange_CA1_BCCCK;
	std::vector<int> IDrange_CA1_BisC;
	std::vector<int> IDrange_CA1_OLM;
	std::vector<int> IDrange_CA1_TL;
	std::vector<int> IDrange_CA1_NG;
	
	std::vector<std::vector<float>> locs;
	std::vector<std::vector<float>> locs_EC3;
	
	/*
	std::vector<float> locs_x_MEC3;
    std::vector<float> locs_y_MEC3;
    
	std::vector<float> locs_x_LEC3;
    std::vector<float> locs_y_LEC3;
	
	std::vector<float> locs_x_CA3PC;
    std::vector<float> locs_y_CA3PC;
    
    std::vector<float> locs_x_CA1PC;
    //std::vector<float> locs_y_CA1PC;// //need to comment out for y specific Wt!
	
    std::vector<float> locs_x_CA1BC;
    std::vector<float> locs_y_CA1BC;
  
    std::vector<float> locs_x_CA1AAC;
    std::vector<float> locs_y_CA1AAC;
    
    std::vector<float> locs_x_CA1BCCCK;
    std::vector<float> locs_y_CA1BCCCK;
    
    std::vector<float> locs_x_CA1BisC;
    std::vector<float> locs_y_CA1BisC;
    
    std::vector<float> locs_x_CA1OLM;
    std::vector<float> locs_y_CA1OLM;
    
    std::vector<float> locs_x_CA1TL;
    std::vector<float> locs_y_CA1TL;
    
    std::vector<float> locs_x_CA1NG;
    std::vector<float> locs_y_CA1NG;
    */
    
    file.getDataSet(dataset_idranges_CA3_PC).read(IDrange_CA3_PC);
    file.getDataSet(dataset_idranges_CA1_PC).read(IDrange_CA1_PC);
    file.getDataSet(dataset_idranges_CA1_BC).read(IDrange_CA1_BC);
    file.getDataSet(dataset_idranges_CA1_AAC).read(IDrange_CA1_AAC);
    file.getDataSet(dataset_idranges_CA1_BCCCK).read(IDrange_CA1_BCCCK);
    file.getDataSet(dataset_idranges_CA1_BisC).read(IDrange_CA1_BisC);
    file.getDataSet(dataset_idranges_CA1_OLM).read(IDrange_CA1_OLM);
    file.getDataSet(dataset_idranges_CA1_TL).read(IDrange_CA1_TL);
    file.getDataSet(dataset_idranges_CA1_NG).read(IDrange_CA1_NG);
    file.getDataSet("Locs/HC").read(locs);// Access the 'Locs/HC' dataset from the file
    
    HighFive::Group grpCAregion = file.getGroup("CAregion");
    
    // Read EC3 location of Entorhinal cortex
    file.getDataSet(dataset_idranges_EC_LEC3).read(IDrange_EC_LEC3);
    file.getDataSet(dataset_idranges_EC_MEC3).read(IDrange_EC_MEC3);
    //file.getDataSet("Locs/EC").read(locs_EC3);
    file.getDataSet("Locs/HC").read(locs_EC3);
	
	map_IDoffset.insert(std::pair<std::string, int>("EC_LEC3", IDrange_EC_LEC3[0]));
	map_IDoffset.insert(std::pair<std::string, int>("EC_MEC3", IDrange_EC_MEC3[0]));
	map_IDoffset.insert(std::pair<std::string, int>("CA3_PC", IDrange_CA3_PC[0]));
	map_IDoffset.insert(std::pair<std::string, int>("CA1_PC", IDrange_CA1_PC[0]));
	map_IDoffset.insert(std::pair<std::string, int>("CA1_BC", IDrange_CA1_BC[0]));
	map_IDoffset.insert(std::pair<std::string, int>("CA1_AAC", IDrange_CA1_AAC[0]));
	map_IDoffset.insert(std::pair<std::string, int>("CA1_BCCCK", IDrange_CA1_BCCCK[0]));
	map_IDoffset.insert(std::pair<std::string, int>("CA1_BisC", IDrange_CA1_BisC[0]));
	map_IDoffset.insert(std::pair<std::string, int>("CA1_OLM", IDrange_CA1_OLM[0]));
	map_IDoffset.insert(std::pair<std::string, int>("CA1_TL", IDrange_CA1_TL[0]));
	map_IDoffset.insert(std::pair<std::string, int>("CA1_NG", IDrange_CA1_NG[0]));
	
	// Get MEC3 locations
	for (int id = IDrange_EC_MEC3[0]; id <= IDrange_EC_MEC3[1]; id++) {
         
         float x_coord_MEC3 = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_MEC3 = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_MEC3.push_back(x_coord_MEC3);
         locs_y_MEC3.push_back(y_coord_MEC3);
      }

    std::cout << "locs_x_MEC3 size is: " << locs_x_MEC3.size() << std::endl;
    std::cout << "locs_y_MEC3 size is: " << locs_y_MEC3.size() << std::endl;
    saveToBinaryFile(locs_x_MEC3, locs_y_MEC3, "locations/locs_MEC3.dat");//MEC3 location
	
	// Get LEC3 locations
	for (int id = IDrange_EC_LEC3[0]; id <= IDrange_EC_LEC3[1]; id++) {
         
         float x_coord_LEC3 = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_LEC3 = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_LEC3.push_back(x_coord_LEC3);
         locs_y_LEC3.push_back(y_coord_LEC3);
      }

    std::cout << "locs_x_LEC3 size is: " << locs_x_LEC3.size() << std::endl;
    std::cout << "locs_y_LEC3 size is: " << locs_y_LEC3.size() << std::endl;
    saveToBinaryFile(locs_x_LEC3, locs_y_LEC3, "locations/locs_LEC3.dat");//LEC3 location
    
    // Get CA3 PC locations. Classify CA3 PC IDs into ab vs. c
	for (int id = IDrange_CA3_PC[0]; id <= IDrange_CA3_PC[1]; id++) {
         
         float x_coord_CA3PC = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_CA3PC = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_CA3PC.push_back(x_coord_CA3PC);
         locs_y_CA3PC.push_back(y_coord_CA3PC);
         
         // read one-byte dataset → 'a', 'b', or 'c'
         std::string utf8;// holds "a" / "b" / "c"   
         grpCAregion.getDataSet(std::to_string(id)).read(utf8);
         char regionTag = utf8.empty() ? 'x' : utf8[0]; // pick first byte

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
    
    
	// Get CA1 PC locations
	for (int id = IDrange_CA1_PC[0]; id <= IDrange_CA1_PC[1]; id++) {
         
         float x_coord_CA1PC = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_CA1PC = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_CA1PC.push_back(x_coord_CA1PC);
         locs_y_CA1PC.push_back(y_coord_CA1PC);
      }
      
    std::cout << "locs_x_CA1PC size is: " << locs_x_CA1PC.size() << std::endl;
    std::cout << "locs_y_CA1PC size is: " << locs_y_CA1PC.size() << std::endl;
    saveToBinaryFile(locs_x_CA1PC, locs_y_CA1PC, "locations/locs_CA1PC.dat");//CA3PC location
    
    // Get CA1 BC locations
	for (int id = IDrange_CA1_BC[0]; id <= IDrange_CA1_BC[1]; id++) {
         
         float x_coord_CA1BC = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_CA1BC = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_CA1BC.push_back(x_coord_CA1BC);
         locs_y_CA1BC.push_back(y_coord_CA1BC);
      }
      
    std::cout << "locs_x_CA1BC size is: " << locs_x_CA1BC.size() << std::endl;
    std::cout << "locs_y_CA1BC size is: " << locs_y_CA1BC.size() << std::endl;
    saveToBinaryFile(locs_x_CA1BC, locs_y_CA1BC, "locations/locs_CA1BC.dat");//DGBC location

   // Get CA1 AAC locations
	for (int id = IDrange_CA1_AAC[0]; id <= IDrange_CA1_AAC[1]; id++) {
         
         float x_coord_CA1AAC = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_CA1AAC = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_CA1AAC.push_back(x_coord_CA1AAC);
         locs_y_CA1AAC.push_back(y_coord_CA1AAC);
      }

    std::cout << "locs_x_CA1AAC size is: " << locs_x_CA1AAC.size() << std::endl;
    std::cout << "locs_y_CA1AAC size is: " << locs_y_CA1AAC.size() << std::endl;
    saveToBinaryFile(locs_x_CA1AAC, locs_y_CA1AAC, "locations/locs_CA1AAC.dat");//CA1AAC location
	
	
	// Get CA1 BCCCK locations
	for (int id = IDrange_CA1_BCCCK[0]; id <= IDrange_CA1_BCCCK[1]; id++) {
         
         float x_coord_CA1BCCCK = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_CA1BCCCK = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_CA1BCCCK.push_back(x_coord_CA1BCCCK);
         locs_y_CA1BCCCK.push_back(y_coord_CA1BCCCK);
      }

    std::cout << "locs_x_CA1BCCCK size is: " << locs_x_CA1BCCCK.size() << std::endl;
    std::cout << "locs_y_CA1BCCCK size is: " << locs_y_CA1BCCCK.size() << std::endl;
    saveToBinaryFile(locs_x_CA1BCCCK, locs_y_CA1BCCCK, "locations/locs_CA1BCCCK.dat");//CA1BCCCK location
    
	
	// Get CA1 BisC locations
	for (int id = IDrange_CA1_BisC[0]; id <= IDrange_CA1_BisC[1]; id++) {
         
         float x_coord_CA1BisC = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_CA1BisC = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_CA1BisC.push_back(x_coord_CA1BisC);
         locs_y_CA1BisC.push_back(y_coord_CA1BisC);
      }

    std::cout << "locs_x_CA1BisC size is: " << locs_x_CA1BisC.size() << std::endl;
    std::cout << "locs_y_CA1BisC size is: " << locs_y_CA1BisC.size() << std::endl;
    saveToBinaryFile(locs_x_CA1BisC, locs_y_CA1BisC, "locations/locs_CA1BisC.dat");//CA1BisC location
    
	
	// Get CA1 OLM locations
	for (int id = IDrange_CA1_OLM[0]; id <= IDrange_CA1_OLM[1]; id++) {
         
         float x_coord_CA1OLM = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_CA1OLM = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_CA1OLM.push_back(x_coord_CA1OLM);
         locs_y_CA1OLM.push_back(y_coord_CA1OLM);
      }

    std::cout << "locs_x_CA1OLM size is: " << locs_x_CA1OLM.size() << std::endl;
    std::cout << "locs_y_CA1OLM size is: " << locs_y_CA1OLM.size() << std::endl;
    saveToBinaryFile(locs_x_CA1OLM, locs_y_CA1OLM, "locations/locs_CA1OLM.dat");//CA1OLM location
	
	// Get CA1 Trilaminar locations
	for (int id = IDrange_CA1_TL[0]; id <= IDrange_CA1_TL[1]; id++) {
         
         float x_coord_CA1TL = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_CA1TL = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_CA1TL.push_back(x_coord_CA1TL);
         locs_y_CA1TL.push_back(y_coord_CA1TL);
      }

    std::cout << "locs_x_CA1TL size is: " << locs_x_CA1TL.size() << std::endl;
    std::cout << "locs_y_CA1TL size is: " << locs_y_CA1TL.size() << std::endl;
    saveToBinaryFile(locs_x_CA1TL, locs_y_CA1TL, "locations/locs_CA1TL.dat");//CA1TL location
    
    // Get CA1 Neurogliaform locations
	for (int id = IDrange_CA1_NG[0]; id <= IDrange_CA1_NG[1]; id++) {
         
         float x_coord_CA1NG = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_CA1NG = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_CA1NG.push_back(x_coord_CA1NG);
         locs_y_CA1NG.push_back(y_coord_CA1NG);
      }

    std::cout << "locs_x_CA1NG size is: " << locs_x_CA1NG.size() << std::endl;
    std::cout << "locs_y_CA1NG size is: " << locs_y_CA1NG.size() << std::endl;
    saveToBinaryFile(locs_x_CA1NG, locs_y_CA1NG, "locations/locs_CA1NG.dat");//CA1NG location
 
 
// load h file   

//-----------------------------------------------------------------------
// MAIN CONNECTIVITY-LOADING SNIPPET (DIVERGENCE STYLE: PRE -> POST) — CA1
//-----------------------------------------------------------------------

std::map<std::string, std::map<int, std::vector<int>>> div_EC_LEC3;
std::map<std::string, std::map<int, std::vector<int>>> div_EC_MEC3;
std::map<std::string, std::map<int, std::vector<int>>> div_CA3_PC;
std::map<std::string, std::map<int, std::vector<int>>> div_CA1_PC;
std::map<std::string, std::map<int, std::vector<int>>> div_CA1_BC;
std::map<std::string, std::map<int, std::vector<int>>> div_CA1_AAC;
std::map<std::string, std::map<int, std::vector<int>>> div_CA1_BCCCK;
std::map<std::string, std::map<int, std::vector<int>>> div_CA1_BisC;
std::map<std::string, std::map<int, std::vector<int>>> div_CA1_NG;
std::map<std::string, std::map<int, std::vector<int>>> div_CA1_OLM;
std::map<std::string, std::map<int, std::vector<int>>> div_CA1_TL;


// ==========================================================================
// CA1_PC: PRE ∈ { EC_LEC3, EC_MEC3, CA3_PC, CA1_PC, CA1_BC, CA1_AAC,
//                 CA1_BCCCK, CA1_BisC, CA1_OLM, CA1_TL, CA1_NG }
// ==========================================================================

// EC-LEC3 -> CA1_PC
std::cout << "Loading EC_LEC3 to CA1_PC" << std::endl;
std::map<int, std::vector<int>> div_EC_LEC3_CA1_PC;
for (int i = IDrange_EC_LEC3[0]; i <= IDrange_EC_LEC3[1]; i++) {
    std::string dataset_div_post = "Div/EC-LEC3/CA1-PC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_PC[0];
    div_EC_LEC3_CA1_PC.insert({ i - IDrange_EC_LEC3[0], div_data });
}

// EC-MEC3 -> CA1_PC
std::cout << "Loading EC_MEC3 to CA1_PC" << std::endl;
std::map<int, std::vector<int>> div_EC_MEC3_CA1_PC;
for (int i = IDrange_EC_MEC3[0]; i <= IDrange_EC_MEC3[1]; i++) {
    std::string dataset_div_post = "Div/EC-MEC3/CA1-PC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_PC[0];
    div_EC_MEC3_CA1_PC.insert({ i - IDrange_EC_MEC3[0], div_data });
}

// CA3-PC -> CA1_PC
std::cout << "Loading CA3_PC to CA1_PC" << std::endl;
std::map<int, std::vector<int>> div_CA3_PC_CA1_PC;
for (int i = IDrange_CA3_PC[0]; i <= IDrange_CA3_PC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-PC/CA1-PC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_PC[0];
    div_CA3_PC_CA1_PC.insert({ i - IDrange_CA3_PC[0], div_data });
}

// CA1-PC -> CA1_PC
std::cout << "Loading CA1_PC to CA1_PC" << std::endl;
std::map<int, std::vector<int>> div_CA1_PC_CA1_PC;
for (int i = IDrange_CA1_PC[0]; i <= IDrange_CA1_PC[1]; i++) {
    std::string dataset_div_post = "Div/CA1-PC/CA1-PC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_PC[0];
    div_CA1_PC_CA1_PC.insert({ i - IDrange_CA1_PC[0], div_data });
}

// CA1-BC -> CA1_PC
std::cout << "Loading CA1_BC to CA1_PC" << std::endl;
std::map<int, std::vector<int>> div_CA1_BC_CA1_PC;
for (int i = IDrange_CA1_BC[0]; i <= IDrange_CA1_BC[1]; i++) {
    std::string dataset_div_post = "Div/CA1-BC/CA1-PC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_PC[0];
    div_CA1_BC_CA1_PC.insert({ i - IDrange_CA1_BC[0], div_data });
}

// CA1-AAC -> CA1_PC
std::cout << "Loading CA1_AAC to CA1_PC" << std::endl;
std::map<int, std::vector<int>> div_CA1_AAC_CA1_PC;
for (int i = IDrange_CA1_AAC[0]; i <= IDrange_CA1_AAC[1]; i++) {
    std::string dataset_div_post = "Div/CA1-AAC/CA1-PC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_PC[0];
    div_CA1_AAC_CA1_PC.insert({ i - IDrange_CA1_AAC[0], div_data });
}

// CA1-BCCCK -> CA1_PC
std::cout << "Loading CA1_BCCCK to CA1_PC" << std::endl;
std::map<int, std::vector<int>> div_CA1_BCCCK_CA1_PC;
for (int i = IDrange_CA1_BCCCK[0]; i <= IDrange_CA1_BCCCK[1]; i++) {
    std::string dataset_div_post = "Div/CA1-BCCCK/CA1-PC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_PC[0];
    div_CA1_BCCCK_CA1_PC.insert({ i - IDrange_CA1_BCCCK[0], div_data });
}

// CA1-Bistratified -> CA1_PC
std::cout << "Loading CA1_BisC to CA1_PC" << std::endl;
std::map<int, std::vector<int>> div_CA1_BisC_CA1_PC;
for (int i = IDrange_CA1_BisC[0]; i <= IDrange_CA1_BisC[1]; i++) {
    std::string dataset_div_post = "Div/CA1-Bistratified/CA1-PC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_PC[0];
    div_CA1_BisC_CA1_PC.insert({ i - IDrange_CA1_BisC[0], div_data });
}

// CA1-OLM -> CA1_PC
std::cout << "Loading CA1_OLM to CA1_PC" << std::endl;
std::map<int, std::vector<int>> div_CA1_OLM_CA1_PC;
for (int i = IDrange_CA1_OLM[0]; i <= IDrange_CA1_OLM[1]; i++) {
    std::string dataset_div_post = "Div/CA1-OLM/CA1-PC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_PC[0];
    div_CA1_OLM_CA1_PC.insert({ i - IDrange_CA1_OLM[0], div_data });
}

// CA1-Trilaminar -> CA1_PC
std::cout << "Loading CA1_TL to CA1_PC" << std::endl;
std::map<int, std::vector<int>> div_CA1_TL_CA1_PC;
for (int i = IDrange_CA1_TL[0]; i <= IDrange_CA1_TL[1]; i++) {
    std::string dataset_div_post = "Div/CA1-Trilaminar/CA1-PC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_PC[0];
    div_CA1_TL_CA1_PC.insert({ i - IDrange_CA1_TL[0], div_data });
}

// CA1-Neurogliaform -> CA1_PC
std::cout << "Loading CA1_NG to CA1_PC" << std::endl;
std::map<int, std::vector<int>> div_CA1_NG_CA1_PC;
for (int i = IDrange_CA1_NG[0]; i <= IDrange_CA1_NG[1]; i++) {
    std::string dataset_div_post = "Div/CA1-Neurogliaform/CA1-PC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_PC[0];
    div_CA1_NG_CA1_PC.insert({ i - IDrange_CA1_NG[0], div_data });
}

// Register PRE maps (targets: CA1_PC)
div_EC_LEC3.insert({ "CA1_PC", div_EC_LEC3_CA1_PC });
div_EC_MEC3.insert({ "CA1_PC", div_EC_MEC3_CA1_PC });
div_CA3_PC.insert({ "CA1_PC", div_CA3_PC_CA1_PC });
div_CA1_PC.insert({ "CA1_PC", div_CA1_PC_CA1_PC });
div_CA1_BC.insert({ "CA1_PC", div_CA1_BC_CA1_PC });
div_CA1_AAC.insert({ "CA1_PC", div_CA1_AAC_CA1_PC });
div_CA1_BCCCK.insert({ "CA1_PC", div_CA1_BCCCK_CA1_PC });
div_CA1_BisC.insert({ "CA1_PC", div_CA1_BisC_CA1_PC });
div_CA1_OLM.insert({ "CA1_PC", div_CA1_OLM_CA1_PC });
div_CA1_TL.insert({ "CA1_PC", div_CA1_TL_CA1_PC });
div_CA1_NG.insert({ "CA1_PC", div_CA1_NG_CA1_PC });


// ==========================================================================
// CA1_AAC: PRE ∈ { EC_LEC3, EC_MEC3, CA3_PC, CA1_PC, CA1_BC, CA1_BCCCK,
//                  CA1_BisC, CA1_NG, CA1_OLM, CA1_TL }
// ==========================================================================

// EC-LEC3 -> CA1_AAC
std::cout << "Loading EC_LEC3 to CA1_AAC" << std::endl;
std::map<int, std::vector<int>> div_EC_LEC3_CA1_AAC;
for (int i = IDrange_EC_LEC3[0]; i <= IDrange_EC_LEC3[1]; i++) {
    std::string dataset_div_post = "Div/EC-LEC3/CA1-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_AAC[0];
    div_EC_LEC3_CA1_AAC.insert({ i - IDrange_EC_LEC3[0], div_data });
}

// EC-MEC3 -> CA1_AAC
std::cout << "Loading EC_MEC3 to CA1_AAC" << std::endl;
std::map<int, std::vector<int>> div_EC_MEC3_CA1_AAC;
for (int i = IDrange_EC_MEC3[0]; i <= IDrange_EC_MEC3[1]; i++) {
    std::string dataset_div_post = "Div/EC-MEC3/CA1-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_AAC[0];
    div_EC_MEC3_CA1_AAC.insert({ i - IDrange_EC_MEC3[0], div_data });
}

// CA3-PC -> CA1_AAC
std::cout << "Loading CA3_PC to CA1_AAC" << std::endl;
std::map<int, std::vector<int>> div_CA3_PC_CA1_AAC;
for (int i = IDrange_CA3_PC[0]; i <= IDrange_CA3_PC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-PC/CA1-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_AAC[0];
    div_CA3_PC_CA1_AAC.insert({ i - IDrange_CA3_PC[0], div_data });
}

// CA1-PC -> CA1_AAC
std::cout << "Loading CA1_PC to CA1_AAC" << std::endl;
std::map<int, std::vector<int>> div_CA1_PC_CA1_AAC;
for (int i = IDrange_CA1_PC[0]; i <= IDrange_CA1_PC[1]; i++) {
    std::string dataset_div_post = "Div/CA1-PC/CA1-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_AAC[0];
    div_CA1_PC_CA1_AAC.insert({ i - IDrange_CA1_PC[0], div_data });
}

// CA1-BC -> CA1_AAC
std::cout << "Loading CA1_BC to CA1_AAC" << std::endl;
std::map<int, std::vector<int>> div_CA1_BC_CA1_AAC;
for (int i = IDrange_CA1_BC[0]; i <= IDrange_CA1_BC[1]; i++) {
    std::string dataset_div_post = "Div/CA1-BC/CA1-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_AAC[0];
    div_CA1_BC_CA1_AAC.insert({ i - IDrange_CA1_BC[0], div_data });
}

// CA1-BCCCK -> CA1_AAC
std::cout << "Loading CA1_BCCCK to CA1_AAC" << std::endl;
std::map<int, std::vector<int>> div_CA1_BCCCK_CA1_AAC;
for (int i = IDrange_CA1_BCCCK[0]; i <= IDrange_CA1_BCCCK[1]; i++) {
    std::string dataset_div_post = "Div/CA1-BCCCK/CA1-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_AAC[0];
    div_CA1_BCCCK_CA1_AAC.insert({ i - IDrange_CA1_BCCCK[0], div_data });
}

// CA1-Bistratified -> CA1_AAC
std::cout << "Loading CA1_BisC to CA1_AAC" << std::endl;
std::map<int, std::vector<int>> div_CA1_BisC_CA1_AAC;
for (int i = IDrange_CA1_BisC[0]; i <= IDrange_CA1_BisC[1]; i++) {
    std::string dataset_div_post = "Div/CA1-Bistratified/CA1-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_AAC[0];
    div_CA1_BisC_CA1_AAC.insert({ i - IDrange_CA1_BisC[0], div_data });
}

// CA1-Neurogliaform -> CA1_AAC
std::cout << "Loading CA1_NG to CA1_AAC" << std::endl;
std::map<int, std::vector<int>> div_CA1_NG_CA1_AAC;
for (int i = IDrange_CA1_NG[0]; i <= IDrange_CA1_NG[1]; i++) {
    std::string dataset_div_post = "Div/CA1-Neurogliaform/CA1-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_AAC[0];
    div_CA1_NG_CA1_AAC.insert({ i - IDrange_CA1_NG[0], div_data });
}

// CA1-OLM -> CA1_AAC
std::cout << "Loading CA1_OLM to CA1_AAC" << std::endl;
std::map<int, std::vector<int>> div_CA1_OLM_CA1_AAC;
for (int i = IDrange_CA1_OLM[0]; i <= IDrange_CA1_OLM[1]; i++) {
    std::string dataset_div_post = "Div/CA1-OLM/CA1-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_AAC[0];
    div_CA1_OLM_CA1_AAC.insert({ i - IDrange_CA1_OLM[0], div_data });
}

// CA1-Trilaminar -> CA1_AAC
std::cout << "Loading CA1_TL to CA1_AAC" << std::endl;
std::map<int, std::vector<int>> div_CA1_TL_CA1_AAC;
for (int i = IDrange_CA1_TL[0]; i <= IDrange_CA1_TL[1]; i++) {
    std::string dataset_div_post = "Div/CA1-Trilaminar/CA1-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_AAC[0];
    div_CA1_TL_CA1_AAC.insert({ i - IDrange_CA1_TL[0], div_data });
}

// Register PRE maps (targets: CA1_AAC)
div_EC_LEC3.insert({ "CA1_AAC", div_EC_LEC3_CA1_AAC });
div_EC_MEC3.insert({ "CA1_AAC", div_EC_MEC3_CA1_AAC });
div_CA3_PC.insert({ "CA1_AAC", div_CA3_PC_CA1_AAC });
div_CA1_PC.insert({ "CA1_AAC", div_CA1_PC_CA1_AAC });
div_CA1_BC.insert({ "CA1_AAC", div_CA1_BC_CA1_AAC });
div_CA1_BCCCK.insert({ "CA1_AAC", div_CA1_BCCCK_CA1_AAC });
div_CA1_BisC.insert({ "CA1_AAC", div_CA1_BisC_CA1_AAC });
div_CA1_NG.insert({ "CA1_AAC", div_CA1_NG_CA1_AAC });
div_CA1_OLM.insert({ "CA1_AAC", div_CA1_OLM_CA1_AAC });
div_CA1_TL.insert({ "CA1_AAC", div_CA1_TL_CA1_AAC });


// ==========================================================================
// CA1_BC: PRE ∈ { EC_LEC3, EC_MEC3, CA3_PC, CA1_PC, CA1_BC, CA1_BCCCK,
//                 CA1_BisC, CA1_NG, CA1_OLM, CA1_TL }
// ==========================================================================

// EC-LEC3 -> CA1_BC
std::cout << "Loading EC_LEC3 to CA1_BC" << std::endl;
std::map<int, std::vector<int>> div_EC_LEC3_CA1_BC;
for (int i = IDrange_EC_LEC3[0]; i <= IDrange_EC_LEC3[1]; i++) {
    std::string dataset_div_post = "Div/EC-LEC3/CA1-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_BC[0];
    div_EC_LEC3_CA1_BC.insert({ i - IDrange_EC_LEC3[0], div_data });
}

// EC-MEC3 -> CA1_BC
std::cout << "Loading EC_MEC3 to CA1_BC" << std::endl;
std::map<int, std::vector<int>> div_EC_MEC3_CA1_BC;
for (int i = IDrange_EC_MEC3[0]; i <= IDrange_EC_MEC3[1]; i++) {
    std::string dataset_div_post = "Div/EC-MEC3/CA1-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_BC[0];
    div_EC_MEC3_CA1_BC.insert({ i - IDrange_EC_MEC3[0], div_data });
}

// CA3-PC -> CA1_BC
std::cout << "Loading CA3_PC to CA1_BC" << std::endl;
std::map<int, std::vector<int>> div_CA3_PC_CA1_BC;
for (int i = IDrange_CA3_PC[0]; i <= IDrange_CA3_PC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-PC/CA1-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_BC[0];
    div_CA3_PC_CA1_BC.insert({ i - IDrange_CA3_PC[0], div_data });
}

// CA1-PC -> CA1_BC
std::cout << "Loading CA1_PC to CA1_BC" << std::endl;
std::map<int, std::vector<int>> div_CA1_PC_CA1_BC;
for (int i = IDrange_CA1_PC[0]; i <= IDrange_CA1_PC[1]; i++) {
    std::string dataset_div_post = "Div/CA1-PC/CA1-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_BC[0];
    div_CA1_PC_CA1_BC.insert({ i - IDrange_CA1_PC[0], div_data });
}

// CA1-BC -> CA1_BC
std::cout << "Loading CA1_BC to CA1_BC" << std::endl;
std::map<int, std::vector<int>> div_CA1_BC_CA1_BC;
for (int i = IDrange_CA1_BC[0]; i <= IDrange_CA1_BC[1]; i++) {
    std::string dataset_div_post = "Div/CA1-BC/CA1-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_BC[0];
    div_CA1_BC_CA1_BC.insert({ i - IDrange_CA1_BC[0], div_data });
}

// CA1-BCCCK -> CA1_BC
std::cout << "Loading CA1_BCCCK to CA1_BC" << std::endl;
std::map<int, std::vector<int>> div_CA1_BCCCK_CA1_BC;
for (int i = IDrange_CA1_BCCCK[0]; i <= IDrange_CA1_BCCCK[1]; i++) {
    std::string dataset_div_post = "Div/CA1-BCCCK/CA1-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_BC[0];
    div_CA1_BCCCK_CA1_BC.insert({ i - IDrange_CA1_BCCCK[0], div_data });
}

// CA1-Bistratified -> CA1_BC
std::cout << "Loading CA1_BisC to CA1_BC" << std::endl;
std::map<int, std::vector<int>> div_CA1_BisC_CA1_BC;
for (int i = IDrange_CA1_BisC[0]; i <= IDrange_CA1_BisC[1]; i++) {
    std::string dataset_div_post = "Div/CA1-Bistratified/CA1-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_BC[0];
    div_CA1_BisC_CA1_BC.insert({ i - IDrange_CA1_BisC[0], div_data });
}

// CA1-Neurogliaform -> CA1_BC
std::cout << "Loading CA1_NG to CA1_BC" << std::endl;
std::map<int, std::vector<int>> div_CA1_NG_CA1_BC;
for (int i = IDrange_CA1_NG[0]; i <= IDrange_CA1_NG[1]; i++) {
    std::string dataset_div_post = "Div/CA1-Neurogliaform/CA1-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_BC[0];
    div_CA1_NG_CA1_BC.insert({ i - IDrange_CA1_NG[0], div_data });
}

// CA1-OLM -> CA1_BC
std::cout << "Loading CA1_OLM to CA1_BC" << std::endl;
std::map<int, std::vector<int>> div_CA1_OLM_CA1_BC;
for (int i = IDrange_CA1_OLM[0]; i <= IDrange_CA1_OLM[1]; i++) {
    std::string dataset_div_post = "Div/CA1-OLM/CA1-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_BC[0];
    div_CA1_OLM_CA1_BC.insert({ i - IDrange_CA1_OLM[0], div_data });
}

// CA1-Trilaminar -> CA1_BC
std::cout << "Loading CA1_TL to CA1_BC" << std::endl;
std::map<int, std::vector<int>> div_CA1_TL_CA1_BC;
for (int i = IDrange_CA1_TL[0]; i <= IDrange_CA1_TL[1]; i++) {
    std::string dataset_div_post = "Div/CA1-Trilaminar/CA1-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_BC[0];
    div_CA1_TL_CA1_BC.insert({ i - IDrange_CA1_TL[0], div_data });
}

// Register PRE maps (targets: CA1_BC)
div_EC_LEC3.insert({ "CA1_BC", div_EC_LEC3_CA1_BC });
div_EC_MEC3.insert({ "CA1_BC", div_EC_MEC3_CA1_BC });
div_CA3_PC.insert({ "CA1_BC", div_CA3_PC_CA1_BC });
div_CA1_PC.insert({ "CA1_BC", div_CA1_PC_CA1_BC });
div_CA1_BC.insert({ "CA1_BC", div_CA1_BC_CA1_BC });
div_CA1_BCCCK.insert({ "CA1_BC", div_CA1_BCCCK_CA1_BC });
div_CA1_BisC.insert({ "CA1_BC", div_CA1_BisC_CA1_BC });
div_CA1_NG.insert({ "CA1_BC", div_CA1_NG_CA1_BC });
div_CA1_OLM.insert({ "CA1_BC", div_CA1_OLM_CA1_BC });
div_CA1_TL.insert({ "CA1_BC", div_CA1_TL_CA1_BC });


// ==========================================================================
// CA1_BCCCK: PRE ∈ { EC_LEC3, EC_MEC3, CA3_PC, CA1_PC, CA1_BC, CA1_BCCCK,
//                    CA1_BisC, CA1_NG, CA1_OLM, CA1_TL }
// ==========================================================================

// EC-LEC3 -> CA1_BCCCK
std::cout << "Loading EC_LEC3 to CA1_BCCCK" << std::endl;
std::map<int, std::vector<int>> div_EC_LEC3_CA1_BCCCK;
for (int i = IDrange_EC_LEC3[0]; i <= IDrange_EC_LEC3[1]; i++) {
    std::string dataset_div_post = "Div/EC-LEC3/CA1-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_BCCCK[0];
    div_EC_LEC3_CA1_BCCCK.insert({ i - IDrange_EC_LEC3[0], div_data });
}

// EC-MEC3 -> CA1_BCCCK
std::cout << "Loading EC_MEC3 to CA1_BCCCK" << std::endl;
std::map<int, std::vector<int>> div_EC_MEC3_CA1_BCCCK;
for (int i = IDrange_EC_MEC3[0]; i <= IDrange_EC_MEC3[1]; i++) {
    std::string dataset_div_post = "Div/EC-MEC3/CA1-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_BCCCK[0];
    div_EC_MEC3_CA1_BCCCK.insert({ i - IDrange_EC_MEC3[0], div_data });
}

// CA3-PC -> CA1_BCCCK
std::cout << "Loading CA3_PC to CA1_BCCCK" << std::endl;
std::map<int, std::vector<int>> div_CA3_PC_CA1_BCCCK;
for (int i = IDrange_CA3_PC[0]; i <= IDrange_CA3_PC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-PC/CA1-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_BCCCK[0];
    div_CA3_PC_CA1_BCCCK.insert({ i - IDrange_CA3_PC[0], div_data });
}

// CA1-PC -> CA1_BCCCK
std::cout << "Loading CA1_PC to CA1_BCCCK" << std::endl;
std::map<int, std::vector<int>> div_CA1_PC_CA1_BCCCK;
for (int i = IDrange_CA1_PC[0]; i <= IDrange_CA1_PC[1]; i++) {
    std::string dataset_div_post = "Div/CA1-PC/CA1-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_BCCCK[0];
    div_CA1_PC_CA1_BCCCK.insert({ i - IDrange_CA1_PC[0], div_data });
}

// CA1-BC -> CA1_BCCCK
std::cout << "Loading CA1_BC to CA1_BCCCK" << std::endl;
std::map<int, std::vector<int>> div_CA1_BC_CA1_BCCCK;
for (int i = IDrange_CA1_BC[0]; i <= IDrange_CA1_BC[1]; i++) {
    std::string dataset_div_post = "Div/CA1-BC/CA1-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_BCCCK[0];
    div_CA1_BC_CA1_BCCCK.insert({ i - IDrange_CA1_BC[0], div_data });
}

// CA1-BCCCK -> CA1_BCCCK
std::cout << "Loading CA1_BCCCK to CA1_BCCCK" << std::endl;
std::map<int, std::vector<int>> div_CA1_BCCCK_CA1_BCCCK;
for (int i = IDrange_CA1_BCCCK[0]; i <= IDrange_CA1_BCCCK[1]; i++) {
    std::string dataset_div_post = "Div/CA1-BCCCK/CA1-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_BCCCK[0];
    div_CA1_BCCCK_CA1_BCCCK.insert({ i - IDrange_CA1_BCCCK[0], div_data });
}

// CA1-Bistratified -> CA1_BCCCK
std::cout << "Loading CA1_BisC to CA1_BCCCK" << std::endl;
std::map<int, std::vector<int>> div_CA1_BisC_CA1_BCCCK;
for (int i = IDrange_CA1_BisC[0]; i <= IDrange_CA1_BisC[1]; i++) {
    std::string dataset_div_post = "Div/CA1-Bistratified/CA1-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_BCCCK[0];
    div_CA1_BisC_CA1_BCCCK.insert({ i - IDrange_CA1_BisC[0], div_data });
}

// CA1-Neurogliaform -> CA1_BCCCK
std::cout << "Loading CA1_NG to CA1_BCCCK" << std::endl;
std::map<int, std::vector<int>> div_CA1_NG_CA1_BCCCK;
for (int i = IDrange_CA1_NG[0]; i <= IDrange_CA1_NG[1]; i++) {
    std::string dataset_div_post = "Div/CA1-Neurogliaform/CA1-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_BCCCK[0];
    div_CA1_NG_CA1_BCCCK.insert({ i - IDrange_CA1_NG[0], div_data });
}

// CA1-OLM -> CA1_BCCCK
std::cout << "Loading CA1_OLM to CA1_BCCCK" << std::endl;
std::map<int, std::vector<int>> div_CA1_OLM_CA1_BCCCK;
for (int i = IDrange_CA1_OLM[0]; i <= IDrange_CA1_OLM[1]; i++) {
    std::string dataset_div_post = "Div/CA1-OLM/CA1-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_BCCCK[0];
    div_CA1_OLM_CA1_BCCCK.insert({ i - IDrange_CA1_OLM[0], div_data });
}

// CA1-Trilaminar -> CA1_BCCCK
std::cout << "Loading CA1_TL to CA1_BCCCK" << std::endl;
std::map<int, std::vector<int>> div_CA1_TL_CA1_BCCCK;
for (int i = IDrange_CA1_TL[0]; i <= IDrange_CA1_TL[1]; i++) {
    std::string dataset_div_post = "Div/CA1-Trilaminar/CA1-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_BCCCK[0];
    div_CA1_TL_CA1_BCCCK.insert({ i - IDrange_CA1_TL[0], div_data });
}

// Register PRE maps (targets: CA1_BCCCK)
div_EC_LEC3.insert({ "CA1_BCCCK", div_EC_LEC3_CA1_BCCCK });
div_EC_MEC3.insert({ "CA1_BCCCK", div_EC_MEC3_CA1_BCCCK });
div_CA3_PC.insert({ "CA1_BCCCK", div_CA3_PC_CA1_BCCCK });
div_CA1_PC.insert({ "CA1_BCCCK", div_CA1_PC_CA1_BCCCK });
div_CA1_BC.insert({ "CA1_BCCCK", div_CA1_BC_CA1_BCCCK });
div_CA1_BCCCK.insert({ "CA1_BCCCK", div_CA1_BCCCK_CA1_BCCCK });
div_CA1_BisC.insert({ "CA1_BCCCK", div_CA1_BisC_CA1_BCCCK });
div_CA1_NG.insert({ "CA1_BCCCK", div_CA1_NG_CA1_BCCCK });
div_CA1_OLM.insert({ "CA1_BCCCK", div_CA1_OLM_CA1_BCCCK });
div_CA1_TL.insert({ "CA1_BCCCK", div_CA1_TL_CA1_BCCCK });


// ==========================================================================
// CA1_BisC: PRE ∈ { CA3_PC, CA1_PC, CA1_BC, CA1_BCCCK, CA1_BisC, CA1_TL }
// ==========================================================================

// CA3-PC -> CA1_BisC
std::cout << "Loading CA3_PC to CA1_BisC" << std::endl;
std::map<int, std::vector<int>> div_CA3_PC_CA1_BisC;
for (int i = IDrange_CA3_PC[0]; i <= IDrange_CA3_PC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-PC/CA1-Bistratified/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_BisC[0];
    div_CA3_PC_CA1_BisC.insert({ i - IDrange_CA3_PC[0], div_data });
}

// CA1-PC -> CA1_BisC
std::cout << "Loading CA1_PC to CA1_BisC" << std::endl;
std::map<int, std::vector<int>> div_CA1_PC_CA1_BisC;
for (int i = IDrange_CA1_PC[0]; i <= IDrange_CA1_PC[1]; i++) {
    std::string dataset_div_post = "Div/CA1-PC/CA1-Bistratified/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_BisC[0];
    div_CA1_PC_CA1_BisC.insert({ i - IDrange_CA1_PC[0], div_data });
}

// CA1-BC -> CA1_BisC
std::cout << "Loading CA1_BC to CA1_BisC" << std::endl;
std::map<int, std::vector<int>> div_CA1_BC_CA1_BisC;
for (int i = IDrange_CA1_BC[0]; i <= IDrange_CA1_BC[1]; i++) {
    std::string dataset_div_post = "Div/CA1-BC/CA1-Bistratified/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_BisC[0];
    div_CA1_BC_CA1_BisC.insert({ i - IDrange_CA1_BC[0], div_data });
}

// CA1-BCCCK -> CA1_BisC
std::cout << "Loading CA1_BCCCK to CA1_BisC" << std::endl;
std::map<int, std::vector<int>> div_CA1_BCCCK_CA1_BisC;
for (int i = IDrange_CA1_BCCCK[0]; i <= IDrange_CA1_BCCCK[1]; i++) {
    std::string dataset_div_post = "Div/CA1-BCCCK/CA1-Bistratified/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_BisC[0];
    div_CA1_BCCCK_CA1_BisC.insert({ i - IDrange_CA1_BCCCK[0], div_data });
}

// CA1-BisC -> CA1_BisC
std::cout << "Loading CA1_BisC to CA1_BisC" << std::endl;
std::map<int, std::vector<int>> div_CA1_BisC_CA1_BisC;
for (int i = IDrange_CA1_BisC[0]; i <= IDrange_CA1_BisC[1]; i++) {
    std::string dataset_div_post = "Div/CA1-Bistratified/CA1-Bistratified/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_BisC[0];
    div_CA1_BisC_CA1_BisC.insert({ i - IDrange_CA1_BisC[0], div_data });
}

// CA1-Trilaminar -> CA1_BisC
std::cout << "Loading CA1_TL to CA1_BisC" << std::endl;
std::map<int, std::vector<int>> div_CA1_TL_CA1_BisC;
for (int i = IDrange_CA1_TL[0]; i <= IDrange_CA1_TL[1]; i++) {
    std::string dataset_div_post = "Div/CA1-Trilaminar/CA1-Bistratified/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_BisC[0];
    div_CA1_TL_CA1_BisC.insert({ i - IDrange_CA1_TL[0], div_data });
}

// Register PRE maps (targets: CA1_BisC)
div_CA3_PC.insert({ "CA1_BisC", div_CA3_PC_CA1_BisC });
div_CA1_PC.insert({ "CA1_BisC", div_CA1_PC_CA1_BisC });
div_CA1_BC.insert({ "CA1_BisC", div_CA1_BC_CA1_BisC });
div_CA1_BCCCK.insert({ "CA1_BisC", div_CA1_BCCCK_CA1_BisC });
div_CA1_BisC.insert({ "CA1_BisC", div_CA1_BisC_CA1_BisC });
div_CA1_TL.insert({ "CA1_BisC", div_CA1_TL_CA1_BisC });


// ==========================================================================
// CA1_NG: PRE ∈ { EC_LEC3, EC_MEC3, CA1_NG, CA1_OLM }
// ==========================================================================

// EC-LEC3 -> CA1_NG
std::cout << "Loading EC_LEC3 to CA1_NG" << std::endl;
std::map<int, std::vector<int>> div_EC_LEC3_CA1_NG;
for (int i = IDrange_EC_LEC3[0]; i <= IDrange_EC_LEC3[1]; i++) {
    std::string dataset_div_post = "Div/EC-LEC3/CA1-Neurogliaform/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_NG[0];
    div_EC_LEC3_CA1_NG.insert({ i - IDrange_EC_LEC3[0], div_data });
}

// EC-MEC3 -> CA1_NG
std::cout << "Loading EC_MEC3 to CA1_NG" << std::endl;
std::map<int, std::vector<int>> div_EC_MEC3_CA1_NG;
for (int i = IDrange_EC_MEC3[0]; i <= IDrange_EC_MEC3[1]; i++) {
    std::string dataset_div_post = "Div/EC-MEC3/CA1-Neurogliaform/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_NG[0];
    div_EC_MEC3_CA1_NG.insert({ i - IDrange_EC_MEC3[0], div_data });
}

// CA1-NG -> CA1_NG
std::cout << "Loading CA1_NG to CA1_NG" << std::endl;
std::map<int, std::vector<int>> div_CA1_NG_CA1_NG;
for (int i = IDrange_CA1_NG[0]; i <= IDrange_CA1_NG[1]; i++) {
    std::string dataset_div_post = "Div/CA1-Neurogliaform/CA1-Neurogliaform/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_NG[0];
    div_CA1_NG_CA1_NG.insert({ i - IDrange_CA1_NG[0], div_data });
}

// CA1-OLM -> CA1_NG
std::cout << "Loading CA1_OLM to CA1_NG" << std::endl;
std::map<int, std::vector<int>> div_CA1_OLM_CA1_NG;
for (int i = IDrange_CA1_OLM[0]; i <= IDrange_CA1_OLM[1]; i++) {
    std::string dataset_div_post = "Div/CA1-OLM/CA1-Neurogliaform/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_NG[0];
    div_CA1_OLM_CA1_NG.insert({ i - IDrange_CA1_OLM[0], div_data });
}

// Register PRE maps (targets: CA1_NG)
div_EC_LEC3.insert({ "CA1_NG", div_EC_LEC3_CA1_NG });
div_EC_MEC3.insert({ "CA1_NG", div_EC_MEC3_CA1_NG });
div_CA1_NG.insert({ "CA1_NG", div_CA1_NG_CA1_NG });
div_CA1_OLM.insert({ "CA1_NG", div_CA1_OLM_CA1_NG });


// ==========================================================================
// CA1_OLM: PRE ∈ { CA3_PC, CA1_PC, CA1_BisC, CA1_TL }
// ==========================================================================

// CA3-PC -> CA1_OLM
std::cout << "Loading CA3_PC to CA1_OLM" << std::endl;
std::map<int, std::vector<int>> div_CA3_PC_CA1_OLM;
for (int i = IDrange_CA3_PC[0]; i <= IDrange_CA3_PC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-PC/CA1-OLM/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_OLM[0];
    div_CA3_PC_CA1_OLM.insert({ i - IDrange_CA3_PC[0], div_data });
}

// CA1-PC -> CA1_OLM
std::cout << "Loading CA1_PC to CA1_OLM" << std::endl;
std::map<int, std::vector<int>> div_CA1_PC_CA1_OLM;
for (int i = IDrange_CA1_PC[0]; i <= IDrange_CA1_PC[1]; i++) {
    std::string dataset_div_post = "Div/CA1-PC/CA1-OLM/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_OLM[0];
    div_CA1_PC_CA1_OLM.insert({ i - IDrange_CA1_PC[0], div_data });
}

// CA1-Bistratified -> CA1_OLM
std::cout << "Loading CA1_BisC to CA1_OLM" << std::endl;
std::map<int, std::vector<int>> div_CA1_BisC_CA1_OLM;
for (int i = IDrange_CA1_BisC[0]; i <= IDrange_CA1_BisC[1]; i++) {
    std::string dataset_div_post = "Div/CA1-Bistratified/CA1-OLM/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_OLM[0];
    div_CA1_BisC_CA1_OLM.insert({ i - IDrange_CA1_BisC[0], div_data });
}

// CA1-Trilaminar -> CA1_OLM
std::cout << "Loading CA1_TL to CA1_OLM" << std::endl;
std::map<int, std::vector<int>> div_CA1_TL_CA1_OLM;
for (int i = IDrange_CA1_TL[0]; i <= IDrange_CA1_TL[1]; i++) {
    std::string dataset_div_post = "Div/CA1-Trilaminar/CA1-OLM/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_OLM[0];
    div_CA1_TL_CA1_OLM.insert({ i - IDrange_CA1_TL[0], div_data });
}

// Register PRE maps (targets: CA1_OLM)
div_CA3_PC.insert({ "CA1_OLM", div_CA3_PC_CA1_OLM });
div_CA1_PC.insert({ "CA1_OLM", div_CA1_PC_CA1_OLM });
div_CA1_BisC.insert({ "CA1_OLM", div_CA1_BisC_CA1_OLM });
div_CA1_TL.insert({ "CA1_OLM", div_CA1_TL_CA1_OLM });


// ==========================================================================
// CA1_TL: PRE ∈ { CA3_PC, CA1_PC, CA1_BisC, CA1_TL }
// ==========================================================================

// CA3-PC -> CA1_TL
std::cout << "Loading CA3_PC to CA1_TL" << std::endl;
std::map<int, std::vector<int>> div_CA3_PC_CA1_TL;
for (int i = IDrange_CA3_PC[0]; i <= IDrange_CA3_PC[1]; i++) {
    std::string dataset_div_post = "Div/CA3-PC/CA1-Trilaminar/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_TL[0];
    div_CA3_PC_CA1_TL.insert({ i - IDrange_CA3_PC[0], div_data });
}

// CA1-PC -> CA1_TL
std::cout << "Loading CA1_PC to CA1_TL" << std::endl;
std::map<int, std::vector<int>> div_CA1_PC_CA1_TL;
for (int i = IDrange_CA1_PC[0]; i <= IDrange_CA1_PC[1]; i++) {
    std::string dataset_div_post = "Div/CA1-PC/CA1-Trilaminar/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_TL[0];
    div_CA1_PC_CA1_TL.insert({ i - IDrange_CA1_PC[0], div_data });
}

// CA1-Bistratified -> CA1_TL
std::cout << "Loading CA1_BisC to CA1_TL" << std::endl;
std::map<int, std::vector<int>> div_CA1_BisC_CA1_TL;
for (int i = IDrange_CA1_BisC[0]; i <= IDrange_CA1_BisC[1]; i++) {
    std::string dataset_div_post = "Div/CA1-Bistratified/CA1-Trilaminar/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_TL[0];
    div_CA1_BisC_CA1_TL.insert({ i - IDrange_CA1_BisC[0], div_data });
}

// CA1-TL -> CA1_TL
std::cout << "Loading CA1_TL to CA1_TL" << std::endl;
std::map<int, std::vector<int>> div_CA1_TL_CA1_TL;
for (int i = IDrange_CA1_TL[0]; i <= IDrange_CA1_TL[1]; i++) {
    std::string dataset_div_post = "Div/CA1-Trilaminar/CA1-Trilaminar/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_CA1_TL[0];
    div_CA1_TL_CA1_TL.insert({ i - IDrange_CA1_TL[0], div_data });
}

// Register PRE maps (targets: CA1_TL)
div_CA3_PC.insert({ "CA1_TL", div_CA3_PC_CA1_TL });
div_CA1_PC.insert({ "CA1_TL", div_CA1_PC_CA1_TL });
div_CA1_BisC.insert({ "CA1_TL", div_CA1_BisC_CA1_TL });
div_CA1_TL.insert({ "CA1_TL", div_CA1_TL_CA1_TL });


// ==========================================================================
// Finally add divergence maps into big map (CA1 + afferents)
// ==========================================================================

map_bigcon.insert({ "EC_LEC3",   div_EC_LEC3 });
map_bigcon.insert({ "EC_MEC3",   div_EC_MEC3 });
map_bigcon.insert({ "CA3_PC",    div_CA3_PC });
map_bigcon.insert({ "CA1_PC",    div_CA1_PC });
map_bigcon.insert({ "CA1_BC",    div_CA1_BC });
map_bigcon.insert({ "CA1_AAC",   div_CA1_AAC });
map_bigcon.insert({ "CA1_BCCCK", div_CA1_BCCCK });
map_bigcon.insert({ "CA1_BisC",  div_CA1_BisC });
map_bigcon.insert({ "CA1_NG",    div_CA1_NG });
map_bigcon.insert({ "CA1_OLM",   div_CA1_OLM });
map_bigcon.insert({ "CA1_TL",    div_CA1_TL });
 
