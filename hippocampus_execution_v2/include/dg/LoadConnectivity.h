// Read ID ranges and coordinates, then load connectivity.
// This header contains statements included inside main, sharing its local variables.

    // Open HDF5 connectivity file for reading
    File file(FILE_NAME, File::ReadOnly);

    // Obtain ID ranges
    std::string dataset_idranges_EC_LEC = "IDranges/EC/LEC";
    std::string dataset_idranges_EC_MEC = "IDranges/EC/MEC";
    std::string dataset_idranges_DG_GC = "IDranges/DG/GC";
    std::string dataset_idranges_DG_MC = "IDranges/DG/MC";
    std::string dataset_idranges_DG_BC = "IDranges/DG/BC";
    std::string dataset_idranges_DG_AAC = "IDranges/DG/AAC";
    std::string dataset_idranges_DG_BCCCK = "IDranges/DG/BCCCK";
    std::string dataset_idranges_DG_HICAP = "IDranges/DG/HICAP";
	std::string dataset_idranges_DG_HIPP = "IDranges/DG/HIPP";
	std::string dataset_idranges_DG_MOPP = "IDranges/DG/MOPP";
	std::string dataset_idranges_DG_TML = "IDranges/DG/TML";
	
    std::vector<int> IDrange_EC_LEC;
    std::vector<int> IDrange_EC_MEC;
    std::vector<int> IDrange_DG_GC;
    std::vector<int> IDrange_DG_MC;
    std::vector<int> IDrange_DG_BC;
    std::vector<int> IDrange_DG_AAC;
    std::vector<int> IDrange_DG_BCCCK;
    std::vector<int> IDrange_DG_HICAP;
    std::vector<int> IDrange_DG_HIPP;
    std::vector<int> IDrange_DG_MOPP;
    std::vector<int> IDrange_DG_TML;
    
    std::vector<std::vector<float>> locs;
    std::vector<std::vector<float>> locs_EC;
    
    file.getDataSet(dataset_idranges_DG_GC).read(IDrange_DG_GC);
    file.getDataSet(dataset_idranges_DG_MC).read(IDrange_DG_MC);
    file.getDataSet(dataset_idranges_DG_BC).read(IDrange_DG_BC);
    file.getDataSet(dataset_idranges_DG_AAC).read(IDrange_DG_AAC);
    file.getDataSet(dataset_idranges_DG_BCCCK).read(IDrange_DG_BCCCK);
    file.getDataSet(dataset_idranges_DG_HICAP).read(IDrange_DG_HICAP);
    file.getDataSet(dataset_idranges_DG_HIPP).read(IDrange_DG_HIPP);
    file.getDataSet(dataset_idranges_DG_MOPP).read(IDrange_DG_MOPP);
    file.getDataSet(dataset_idranges_DG_TML).read(IDrange_DG_TML);
    file.getDataSet("Locs/HC").read(locs);// Access the 'Locs/HC' dataset from the file
    //IDrange_DG_GC[0]: start index(i.e, 0), IDrange_DG_GC[1]: end index(i.e, 231999)
    //Therefore, num_DG = IDrange_DG_GC[1] - IDrange_DG_GC[0] +1
    
    file.getDataSet(dataset_idranges_EC_LEC).read(IDrange_EC_LEC);
    file.getDataSet(dataset_idranges_EC_MEC).read(IDrange_EC_MEC);
    file.getDataSet("Locs/HC").read(locs_EC);// EC project to Pe pos - calculate delay
    //file.getDataSet("Locs/EC").read(locs_EC);// EC en pos

    map_IDoffset.insert(std::pair<std::string, int>("EC_LEC", IDrange_EC_LEC[0]));
	map_IDoffset.insert(std::pair<std::string, int>("EC_MEC", IDrange_EC_MEC[0]));
	map_IDoffset.insert(std::pair<std::string, int>("DG_GC", IDrange_DG_GC[0]));
	map_IDoffset.insert(std::pair<std::string, int>("DG_MC", IDrange_DG_MC[0]));
	map_IDoffset.insert(std::pair<std::string, int>("DG_BC", IDrange_DG_BC[0]));
	map_IDoffset.insert(std::pair<std::string, int>("DG_AAC", IDrange_DG_AAC[0]));
	map_IDoffset.insert(std::pair<std::string, int>("DG_BCCCK", IDrange_DG_BCCCK[0]));
	map_IDoffset.insert(std::pair<std::string, int>("DG_HICAP", IDrange_DG_HICAP[0]));
	map_IDoffset.insert(std::pair<std::string, int>("DG_HIPP", IDrange_DG_HIPP[0]));
	map_IDoffset.insert(std::pair<std::string, int>("DG_MOPP", IDrange_DG_MOPP[0]));
	map_IDoffset.insert(std::pair<std::string, int>("DG_TML", IDrange_DG_TML[0]));
	
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
    
    // Get DG GC locations
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
    
    // Get DG MC locations
	for (int id = IDrange_DG_MC[0]; id <= IDrange_DG_MC[1]; id++) {
         
         float x_coord_DGMC = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_DGMC = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_DGMC.push_back(x_coord_DGMC);
         locs_y_DGMC.push_back(y_coord_DGMC);
      }

    std::cout << "locs_x_DGMC size is: " << locs_x_DGMC.size() << std::endl;
    std::cout << "locs_y_DGMC size is: " << locs_y_DGMC.size() << std::endl;
    saveToBinaryFile(locs_x_DGMC, locs_y_DGMC, "locations/locs_DGMC.dat");//DGMC location
    
    // Get DG BC locations
	for (int id = IDrange_DG_BC[0]; id <= IDrange_DG_BC[1]; id++) {
         
         float x_coord_DGBC = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_DGBC = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_DGBC.push_back(x_coord_DGBC);
         locs_y_DGBC.push_back(y_coord_DGBC);
      }

    std::cout << "locs_x_DGBC size is: " << locs_x_DGBC.size() << std::endl;
    std::cout << "locs_y_DGBC size is: " << locs_y_DGBC.size() << std::endl;
    saveToBinaryFile(locs_x_DGBC, locs_y_DGBC, "locations/locs_DGBC.dat");//DGBC location
    
    // Get DG AAC locations
	for (int id = IDrange_DG_AAC[0]; id <= IDrange_DG_AAC[1]; id++) {
         
         float x_coord_DGAAC = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_DGAAC = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_DGAAC.push_back(x_coord_DGAAC);
         locs_y_DGAAC.push_back(y_coord_DGAAC);
      }

    std::cout << "locs_x_DGAAC size is: " << locs_x_DGAAC.size() << std::endl;
    std::cout << "locs_y_DGAAC size is: " << locs_y_DGAAC.size() << std::endl;
    saveToBinaryFile(locs_x_DGAAC, locs_y_DGAAC, "locations/locs_DGAAC.dat");//DGAAC location
    
    // Get DG BCCCK locations
	for (int id = IDrange_DG_BCCCK[0]; id <= IDrange_DG_BCCCK[1]; id++) {
         
         float x_coord_DGBCCCK = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_DGBCCCK = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_DGBCCCK.push_back(x_coord_DGBCCCK);
         locs_y_DGBCCCK.push_back(y_coord_DGBCCCK);
      }

    std::cout << "locs_x_DGBCCCK size is: " << locs_x_DGBCCCK.size() << std::endl;
    std::cout << "locs_y_DGBCCCK size is: " << locs_y_DGBCCCK.size() << std::endl;
    saveToBinaryFile(locs_x_DGBCCCK, locs_y_DGBCCCK, "locations/locs_DGBCCCK.dat");//DGBCCCK location
    
    // Get DG HICAP locations
	for (int id = IDrange_DG_HICAP[0]; id <= IDrange_DG_HICAP[1]; id++) {
         
         float x_coord_DGHICAP = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_DGHICAP = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_DGHICAP.push_back(x_coord_DGHICAP);
         locs_y_DGHICAP.push_back(y_coord_DGHICAP);
      }

    std::cout << "locs_x_DGHICAP size is: " << locs_x_DGHICAP.size() << std::endl;
    std::cout << "locs_y_DGHICAP size is: " << locs_y_DGHICAP.size() << std::endl;
    saveToBinaryFile(locs_x_DGHICAP, locs_y_DGHICAP, "locations/locs_DGHICAP.dat");//DGHICAP location
    
    // Get DG HIPP locations
	for (int id = IDrange_DG_HIPP[0]; id <= IDrange_DG_HIPP[1]; id++) {
         
         float x_coord_DGHIPP = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_DGHIPP = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_DGHIPP.push_back(x_coord_DGHIPP);
         locs_y_DGHIPP.push_back(y_coord_DGHIPP);
      }

    std::cout << "locs_x_DGHIPP size is: " << locs_x_DGHIPP.size() << std::endl;
    std::cout << "locs_y_DGHIPP size is: " << locs_y_DGHIPP.size() << std::endl;
    saveToBinaryFile(locs_x_DGHIPP, locs_y_DGHIPP, "locations/locs_DGHIPP.dat");//DGHIPP location
    
    // Get DG MOPP locations
	for (int id = IDrange_DG_MOPP[0]; id <= IDrange_DG_MOPP[1]; id++) {
         
         float x_coord_DGMOPP = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_DGMOPP = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_DGMOPP.push_back(x_coord_DGMOPP);
         locs_y_DGMOPP.push_back(y_coord_DGMOPP);
      }

    std::cout << "locs_x_DGMOPP size is: " << locs_x_DGMOPP.size() << std::endl;
    std::cout << "locs_y_DGMOPP size is: " << locs_y_DGMOPP.size() << std::endl;
    saveToBinaryFile(locs_x_DGMOPP, locs_y_DGMOPP, "locations/locs_DGMOPP.dat");//DGMOPP location
    
    // Get DG TML locations
	for (int id = IDrange_DG_TML[0]; id <= IDrange_DG_TML[1]; id++) {
         
         float x_coord_DGTML = locs[id][0]; // Get the x-coordinate of the presynaptic ID
         float y_coord_DGTML = locs[id][1]; // Get the y-coordinate of the presynaptic ID
         
         locs_x_DGTML.push_back(x_coord_DGTML);
         locs_y_DGTML.push_back(y_coord_DGTML);
      }

    std::cout << "locs_x_DGTML size is: " << locs_x_DGTML.size() << std::endl;
    std::cout << "locs_y_DGTML size is: " << locs_y_DGTML.size() << std::endl;
    saveToBinaryFile(locs_x_DGTML, locs_y_DGTML, "locations/locs_DGTML.dat");//DGTML location
    
//------------------ load connectivity ---------------------------------//
std::map<std::string, std::map<int, std::vector<int>>> div_EC_LEC;
std::map<std::string, std::map<int, std::vector<int>>> div_EC_MEC;
std::map<std::string, std::map<int, std::vector<int>>> div_DG_GC;
std::map<std::string, std::map<int, std::vector<int>>> div_DG_MC;
std::map<std::string, std::map<int, std::vector<int>>> div_DG_BC;
std::map<std::string, std::map<int, std::vector<int>>> div_DG_AAC;
std::map<std::string, std::map<int, std::vector<int>>> div_DG_BCCCK;
std::map<std::string, std::map<int, std::vector<int>>> div_DG_HICAP;
std::map<std::string, std::map<int, std::vector<int>>> div_DG_HIPP;
std::map<std::string, std::map<int, std::vector<int>>> div_DG_MOPP;
std::map<std::string, std::map<int, std::vector<int>>> div_DG_TML;

// ------------------------------------------------------------
// DG_GC (Granule Cells)
// ------------------------------------------------------------

// EC-LEC -> DG_GC
std::cout << "Loading EC_LEC to DG_GC" << std::endl;
std::map<int, std::vector<int>> div_EC_LEC_DG_GC;
for (int i = IDrange_EC_LEC[0]; i <= IDrange_EC_LEC[1]; i++) {
    std::string dataset_div_post = "Div/EC-LEC/DG-GC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < div_data.size(); j++) {
        div_data[j] -= IDrange_DG_GC[0];
    }
    div_EC_LEC_DG_GC.insert({ i - IDrange_EC_LEC[0], div_data });
}

// EC-MEC -> DG_GC
std::cout << "Loading EC_MEC to DG_GC" << std::endl;
std::map<int, std::vector<int>> div_EC_MEC_DG_GC;
for (int i = IDrange_EC_MEC[0]; i <= IDrange_EC_MEC[1]; i++) {
    std::string dataset_div_post = "Div/EC-MEC/DG-GC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < div_data.size(); j++) {
        div_data[j] -= IDrange_DG_GC[0];
    }
    div_EC_MEC_DG_GC.insert({ i - IDrange_EC_MEC[0], div_data });
}

// DG-MC -> DG_GC
std::map<int, std::vector<int>> div_DG_MC_DG_GC;
for (int i = IDrange_DG_MC[0]; i <= IDrange_DG_MC[1]; i++) {
    std::string dataset_div_post = "Div/DG-MC/DG-GC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < div_data.size(); j++) {
        div_data[j] -= IDrange_DG_GC[0];
    }
    div_DG_MC_DG_GC.insert({ i - IDrange_DG_MC[0], div_data });
}

// DG-BC -> DG_GC
std::map<int, std::vector<int>> div_DG_BC_DG_GC;
for (int i = IDrange_DG_BC[0]; i <= IDrange_DG_BC[1]; i++) {
    std::string dataset_div_post = "Div/DG-BC/DG-GC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < div_data.size(); j++) {
        div_data[j] -= IDrange_DG_GC[0];
    }
    div_DG_BC_DG_GC.insert({ i - IDrange_DG_BC[0], div_data });
}

// DG-AAC -> DG_GC
std::map<int, std::vector<int>> div_DG_AAC_DG_GC;
for (int i = IDrange_DG_AAC[0]; i <= IDrange_DG_AAC[1]; i++) {
    std::string dataset_div_post = "Div/DG-AAC/DG-GC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < div_data.size(); j++) {
        div_data[j] -= IDrange_DG_GC[0];
    }
    div_DG_AAC_DG_GC.insert({ i - IDrange_DG_AAC[0], div_data });
}

// DG-BCCCK -> DG_GC
std::map<int, std::vector<int>> div_DG_BCCCK_DG_GC;
for (int i = IDrange_DG_BCCCK[0]; i <= IDrange_DG_BCCCK[1]; i++) {
    std::string dataset_div_post = "Div/DG-BCCCK/DG-GC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < div_data.size(); j++) {
        div_data[j] -= IDrange_DG_GC[0];
    }
    div_DG_BCCCK_DG_GC.insert({ i - IDrange_DG_BCCCK[0], div_data });
}

// DG-HICAP -> DG_GC
std::cout << "Loading DG_HICAP to DG_GC" << std::endl;
std::map<int, std::vector<int>> div_DG_HICAP_DG_GC;
for (int i = IDrange_DG_HICAP[0]; i <= IDrange_DG_HICAP[1]; i++) {
    std::string dataset_div_post = "Div/DG-HICAP/DG-GC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_GC[0];
    div_DG_HICAP_DG_GC.insert({ i - IDrange_DG_HICAP[0], div_data });
}

// DG-HIPP -> DG_GC
std::cout << "Loading DG_HIPP to DG_GC" << std::endl;
std::map<int, std::vector<int>> div_DG_HIPP_DG_GC;
for (int i = IDrange_DG_HIPP[0]; i <= IDrange_DG_HIPP[1]; i++) {
    std::string dataset_div_post = "Div/DG-HIPP/DG-GC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_GC[0];
    div_DG_HIPP_DG_GC.insert({ i - IDrange_DG_HIPP[0], div_data });
}

// DG-MOPP -> DG_GC
std::cout << "Loading DG_MOPP to DG_GC" << std::endl;
std::map<int, std::vector<int>> div_DG_MOPP_DG_GC;
for (int i = IDrange_DG_MOPP[0]; i <= IDrange_DG_MOPP[1]; i++) {
    std::string dataset_div_post = "Div/DG-MOPP/DG-GC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_GC[0];
    div_DG_MOPP_DG_GC.insert({ i - IDrange_DG_MOPP[0], div_data });
}

// DG-TML -> DG_GC
std::cout << "Loading DG_TML to DG_GC" << std::endl;
std::map<int, std::vector<int>> div_DG_TML_DG_GC;
for (int i = IDrange_DG_TML[0]; i <= IDrange_DG_TML[1]; i++) {
    std::string dataset_div_post = "Div/DG-TML/DG-GC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_GC[0];
    div_DG_TML_DG_GC.insert({ i - IDrange_DG_TML[0], div_data });
}


// Insert DG_GC into divergence maps
div_EC_LEC.insert({ "DG_GC", div_EC_LEC_DG_GC });
div_EC_MEC.insert({ "DG_GC", div_EC_MEC_DG_GC });
div_DG_MC.insert({ "DG_GC",  div_DG_MC_DG_GC });
div_DG_BC.insert({ "DG_GC",  div_DG_BC_DG_GC });
div_DG_AAC.insert({ "DG_GC", div_DG_AAC_DG_GC });
div_DG_BCCCK.insert({ "DG_GC", div_DG_BCCCK_DG_GC });
div_DG_HICAP.insert({ "DG_GC", div_DG_HICAP_DG_GC });
div_DG_HIPP.insert({ "DG_GC", div_DG_HIPP_DG_GC });
div_DG_MOPP.insert({ "DG_GC", div_DG_MOPP_DG_GC });
div_DG_TML.insert({ "DG_GC", div_DG_TML_DG_GC });

// ------------------------------------------------------------
// DG_MC (Mossy Cells)
// ------------------------------------------------------------

// DG-GC -> DG_MC
std::map<int, std::vector<int>> div_DG_GC_DG_MC;
for (int i = IDrange_DG_GC[0]; i <= IDrange_DG_GC[1]; i++) {
    std::string dataset_div_post = "Div/DG-GC/DG-MC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < div_data.size(); j++) {
        div_data[j] -= IDrange_DG_MC[0];
    }
    div_DG_GC_DG_MC.insert({ i - IDrange_DG_GC[0], div_data });
}

// DG-MC -> DG_MC
std::map<int, std::vector<int>> div_DG_MC_DG_MC;
for (int i = IDrange_DG_MC[0]; i <= IDrange_DG_MC[1]; i++) {
    std::string dataset_div_post = "Div/DG-MC/DG-MC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < div_data.size(); j++) {
        div_data[j] -= IDrange_DG_MC[0];
    }
    div_DG_MC_DG_MC.insert({ i - IDrange_DG_MC[0], div_data });
}

// DG-AAC -> DG_MC
std::map<int, std::vector<int>> div_DG_AAC_DG_MC;
for (int i = IDrange_DG_AAC[0]; i <= IDrange_DG_AAC[1]; i++) {
    std::string dataset_div_post = "Div/DG-AAC/DG-MC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < div_data.size(); j++) {
        div_data[j] -= IDrange_DG_MC[0];
    }
    div_DG_AAC_DG_MC.insert({ i - IDrange_DG_AAC[0], div_data });
}

// DG-TML -> DG_MC
std::cout << "Loading DG_TML to DG_MC" << std::endl;
std::map<int, std::vector<int>> div_DG_TML_DG_MC;
for (int i = IDrange_DG_TML[0]; i <= IDrange_DG_TML[1]; i++) {
    std::string dataset_div_post = "Div/DG-TML/DG-MC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_MC[0];
    div_DG_TML_DG_MC.insert({ i - IDrange_DG_TML[0], div_data });
}


// Insert DG_MC into divergence maps
div_DG_GC.insert({ "DG_MC",  div_DG_GC_DG_MC });
div_DG_MC.insert({ "DG_MC",  div_DG_MC_DG_MC });
div_DG_AAC.insert({ "DG_MC", div_DG_AAC_DG_MC });
div_DG_TML.insert({ "DG_MC", div_DG_TML_DG_MC });

// ------------------------------------------------------------
// DG_BC (DG Basket Cells)
// ------------------------------------------------------------

// EC-LEC -> DG_BC
std::map<int, std::vector<int>> div_EC_LEC_DG_BC;
for (int i = IDrange_EC_LEC[0]; i <= IDrange_EC_LEC[1]; i++) {
    std::string dataset_div_post = "Div/EC-LEC/DG-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < div_data.size(); j++) {
        div_data[j] -= IDrange_DG_BC[0];
    }
    div_EC_LEC_DG_BC.insert({ i - IDrange_EC_LEC[0], div_data });
}

// EC-MEC -> DG_BC
std::map<int, std::vector<int>> div_EC_MEC_DG_BC;
for (int i = IDrange_EC_MEC[0]; i <= IDrange_EC_MEC[1]; i++) {
    std::string dataset_div_post = "Div/EC-MEC/DG-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < div_data.size(); j++) {
        div_data[j] -= IDrange_DG_BC[0];
    }
    div_EC_MEC_DG_BC.insert({ i - IDrange_EC_MEC[0], div_data });
}

// DG-MC -> DG_BC
std::map<int, std::vector<int>> div_DG_MC_DG_BC;
for (int i = IDrange_DG_MC[0]; i <= IDrange_DG_MC[1]; i++) {
    std::string dataset_div_post = "Div/DG-MC/DG-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < div_data.size(); j++) {
        div_data[j] -= IDrange_DG_BC[0];
    }
    div_DG_MC_DG_BC.insert({ i - IDrange_DG_MC[0], div_data });
}

// DG-BC -> DG-BC
std::map<int, std::vector<int>> div_DG_BC_DG_BC;
for (int i = IDrange_DG_BC[0]; i <= IDrange_DG_BC[1]; i++) {
    std::string dataset_div_post = "Div/DG-BC/DG-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < div_data.size(); j++) {
        div_data[j] -= IDrange_DG_BC[0];
    }
    div_DG_BC_DG_BC.insert({ i - IDrange_DG_BC[0], div_data });
}

// DG-GC -> DG_BC in Hippo
std::map<int, std::vector<int>> div_DG_GC_DG_BC;
for (int i = IDrange_DG_GC[0]; i <= IDrange_DG_GC[1]; i++){
   std::string dataset_div_post = "Div/DG-GC/DG-BC/"+std::to_string(i);
   std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < div_data.size(); j++) {
        div_data[j] -= IDrange_DG_BC[0];
    }
    div_DG_GC_DG_BC.insert({ i - IDrange_DG_GC[0], div_data });
}
   
// DG-BCCCK -> DG_BC
std::map<int, std::vector<int>> div_DG_BCCCK_DG_BC;
for (int i = IDrange_DG_BCCCK[0]; i <= IDrange_DG_BCCCK[1]; i++) {
    std::string dataset_div_post = "Div/DG-BCCCK/DG-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < div_data.size(); j++) {
        div_data[j] -= IDrange_DG_BC[0];
    }
    div_DG_BCCCK_DG_BC.insert({ i - IDrange_DG_BCCCK[0], div_data });
}

// DG-HICAP -> DG_BC
std::cout << "Loading DG_HICAP to DG_BC" << std::endl;
std::map<int, std::vector<int>> div_DG_HICAP_DG_BC;
for (int i = IDrange_DG_HICAP[0]; i <= IDrange_DG_HICAP[1]; i++) {
    std::string dataset_div_post = "Div/DG-HICAP/DG-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_BC[0];
    div_DG_HICAP_DG_BC.insert({ i - IDrange_DG_HICAP[0], div_data });
}

// DG-HIPP -> DG_BC
std::cout << "Loading DG_HIPP to DG_BC" << std::endl;
std::map<int, std::vector<int>> div_DG_HIPP_DG_BC;
for (int i = IDrange_DG_HIPP[0]; i <= IDrange_DG_HIPP[1]; i++) {
    std::string dataset_div_post = "Div/DG-HIPP/DG-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_BC[0];
    div_DG_HIPP_DG_BC.insert({ i - IDrange_DG_HIPP[0], div_data });
}

// DG-MOPP -> DG_BC
std::cout << "Loading DG_MOPP to DG_BC" << std::endl;
std::map<int, std::vector<int>> div_DG_MOPP_DG_BC;
for (int i = IDrange_DG_MOPP[0]; i <= IDrange_DG_MOPP[1]; i++) {
    std::string dataset_div_post = "Div/DG-MOPP/DG-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_BC[0];
    div_DG_MOPP_DG_BC.insert({ i - IDrange_DG_MOPP[0], div_data });
}

// DG-TML -> DG_BC
std::cout << "Loading DG_TML to DG_BC" << std::endl;
std::map<int, std::vector<int>> div_DG_TML_DG_BC;
for (int i = IDrange_DG_TML[0]; i <= IDrange_DG_TML[1]; i++) {
    std::string dataset_div_post = "Div/DG-TML/DG-BC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_BC[0];
    div_DG_TML_DG_BC.insert({ i - IDrange_DG_TML[0], div_data });
}

// Insert DG_BC into divergence maps
div_EC_LEC.insert({ "DG_BC", div_EC_LEC_DG_BC });
div_EC_MEC.insert({ "DG_BC", div_EC_MEC_DG_BC });
div_DG_MC.insert({ "DG_BC",  div_DG_MC_DG_BC });
div_DG_GC.insert({ "DG_BC", div_DG_GC_DG_BC }); // commented out in your snippet
div_DG_BC.insert({ "DG_BC",  div_DG_BC_DG_BC });
div_DG_BCCCK.insert({ "DG_BC",  div_DG_BCCCK_DG_BC });
div_DG_HICAP.insert({ "DG_BC", div_DG_HICAP_DG_BC });
div_DG_HIPP.insert({ "DG_BC", div_DG_HIPP_DG_BC });
div_DG_MOPP.insert({ "DG_BC", div_DG_MOPP_DG_BC });
div_DG_TML.insert({ "DG_BC",  div_DG_TML_DG_BC });

// ------------------------------------------------------------
// DG_AAC (DG Axo-Axonic Cells)
// ------------------------------------------------------------

// EC-LEC -> DG_AAC
std::map<int, std::vector<int>> div_EC_LEC_DG_AAC;
for (int i = IDrange_EC_LEC[0]; i <= IDrange_EC_LEC[1]; i++) {
    std::string dataset_div_post = "Div/EC-LEC/DG-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < div_data.size(); j++) {
        div_data[j] -= IDrange_DG_AAC[0];
    }
    div_EC_LEC_DG_AAC.insert({ i - IDrange_EC_LEC[0], div_data });
}

// EC-MEC -> DG_AAC
std::map<int, std::vector<int>> div_EC_MEC_DG_AAC;
for (int i = IDrange_EC_MEC[0]; i <= IDrange_EC_MEC[1]; i++) {
    std::string dataset_div_post = "Div/EC-MEC/DG-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < div_data.size(); j++) {
        div_data[j] -= IDrange_DG_AAC[0];
    }
    div_EC_MEC_DG_AAC.insert({ i - IDrange_EC_MEC[0], div_data });
}

// DG-GC -> DG_AAC
std::map<int, std::vector<int>> div_DG_GC_DG_AAC;
for (int i = IDrange_DG_GC[0]; i <= IDrange_DG_GC[1]; i++) {
    std::string dataset_div_post = "Div/DG-GC/DG-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < div_data.size(); j++) {
        div_data[j] -= IDrange_DG_AAC[0];
    }
    div_DG_GC_DG_AAC.insert({ i - IDrange_DG_GC[0], div_data });
}

// DG-MC -> DG_AAC
std::map<int, std::vector<int>> div_DG_MC_DG_AAC;
for (int i = IDrange_DG_MC[0]; i <= IDrange_DG_MC[1]; i++) {
    std::string dataset_div_post = "Div/DG-MC/DG-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < div_data.size(); j++) {
        div_data[j] -= IDrange_DG_AAC[0];
    }
    div_DG_MC_DG_AAC.insert({ i - IDrange_DG_MC[0], div_data });
}

// DG-BC -> DG_AAC
std::map<int, std::vector<int>> div_DG_BC_DG_AAC;
for (int i = IDrange_DG_BC[0]; i <= IDrange_DG_BC[1]; i++) {
    std::string dataset_div_post = "Div/DG-BC/DG-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < div_data.size(); j++) {
        div_data[j] -= IDrange_DG_AAC[0];
    }
    div_DG_BC_DG_AAC.insert({ i - IDrange_DG_BC[0], div_data });
}

// DG-BCCCK -> DG_AAC
std::map<int, std::vector<int>> div_DG_BCCCK_DG_AAC;
for (int i = IDrange_DG_BCCCK[0]; i <= IDrange_DG_BCCCK[1]; i++) {
    std::string dataset_div_post = "Div/DG-BCCCK/DG-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < div_data.size(); j++) {
        div_data[j] -= IDrange_DG_AAC[0];
    }
    div_DG_BCCCK_DG_AAC.insert({ i - IDrange_DG_BCCCK[0], div_data });
}

// DG-HICAP -> DG_AAC
std::cout << "Loading DG_HICAP to DG_AAC" << std::endl;
std::map<int, std::vector<int>> div_DG_HICAP_DG_AAC;
for (int i = IDrange_DG_HICAP[0]; i <= IDrange_DG_HICAP[1]; i++) {
    std::string dataset_div_post = "Div/DG-HICAP/DG-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_AAC[0];
    div_DG_HICAP_DG_AAC.insert({ i - IDrange_DG_HICAP[0], div_data });
}

// DG-HIPP -> DG_AAC
std::cout << "Loading DG_HIPP to DG_AAC" << std::endl;
std::map<int, std::vector<int>> div_DG_HIPP_DG_AAC;
for (int i = IDrange_DG_HIPP[0]; i <= IDrange_DG_HIPP[1]; i++) {
    std::string dataset_div_post = "Div/DG-HIPP/DG-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_AAC[0];
    div_DG_HIPP_DG_AAC.insert({ i - IDrange_DG_HIPP[0], div_data });
}

// DG-MOPP -> DG_AAC
std::cout << "Loading DG_MOPP to DG_AAC" << std::endl;
std::map<int, std::vector<int>> div_DG_MOPP_DG_AAC;
for (int i = IDrange_DG_MOPP[0]; i <= IDrange_DG_MOPP[1]; i++) {
    std::string dataset_div_post = "Div/DG-MOPP/DG-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_AAC[0];
    div_DG_MOPP_DG_AAC.insert({ i - IDrange_DG_MOPP[0], div_data });
}

// DG-TML -> DG_AAC
std::cout << "Loading DG_TML to DG_AAC" << std::endl;
std::map<int, std::vector<int>> div_DG_TML_DG_AAC;
for (int i = IDrange_DG_TML[0]; i <= IDrange_DG_TML[1]; i++) {
    std::string dataset_div_post = "Div/DG-TML/DG-AAC/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_AAC[0];
    div_DG_TML_DG_AAC.insert({ i - IDrange_DG_TML[0], div_data });
}


// Insert DG_AAC into divergence maps
div_EC_LEC.insert({ "DG_AAC", div_EC_LEC_DG_AAC });
div_EC_MEC.insert({ "DG_AAC", div_EC_MEC_DG_AAC });
div_DG_GC.insert({ "DG_AAC",  div_DG_GC_DG_AAC });
div_DG_MC.insert({ "DG_AAC",  div_DG_MC_DG_AAC });
div_DG_BC.insert({ "DG_AAC",  div_DG_BC_DG_AAC });
div_DG_BCCCK.insert({ "DG_AAC",  div_DG_BCCCK_DG_AAC });
div_DG_HICAP.insert({ "DG_AAC", div_DG_HICAP_DG_AAC });
div_DG_HIPP.insert({ "DG_AAC", div_DG_HIPP_DG_AAC });
div_DG_MOPP.insert({ "DG_AAC", div_DG_MOPP_DG_AAC });
div_DG_TML.insert({ "DG_AAC",  div_DG_TML_DG_AAC });

// ------------------------------------------------------------
// DG_BCCCK (DG Basket CCK)
// ------------------------------------------------------------

// EC-LEC -> DG_BCCCK
std::map<int, std::vector<int>> div_EC_LEC_DG_BCCCK;
for (int i = IDrange_EC_LEC[0]; i <= IDrange_EC_LEC[1]; i++) {
    std::string dataset_div_post = "Div/EC-LEC/DG-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < div_data.size(); j++) {
        div_data[j] -= IDrange_DG_BCCCK[0];
    }
    div_EC_LEC_DG_BCCCK.insert({ i - IDrange_EC_LEC[0], div_data });
}

// EC-MEC -> DG_BCCCK
std::map<int, std::vector<int>> div_EC_MEC_DG_BCCCK;
for (int i = IDrange_EC_MEC[0]; i <= IDrange_EC_MEC[1]; i++) {
    std::string dataset_div_post = "Div/EC-MEC/DG-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < div_data.size(); j++) {
        div_data[j] -= IDrange_DG_BCCCK[0];
    }
    div_EC_MEC_DG_BCCCK.insert({ i - IDrange_EC_MEC[0], div_data });
}

// DG-GC -> DG_BCCCK
std::map<int, std::vector<int>> div_DG_GC_DG_BCCCK;
for (int i = IDrange_DG_GC[0]; i <= IDrange_DG_GC[1]; i++) {
    std::string dataset_div_post = "Div/DG-GC/DG-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < div_data.size(); j++) {
        div_data[j] -= IDrange_DG_BCCCK[0];
    }
    div_DG_GC_DG_BCCCK.insert({ i - IDrange_DG_GC[0], div_data });
}

// DG-AAC -> DG_BCCCK
std::map<int, std::vector<int>> div_DG_AAC_DG_BCCCK;
for (int i = IDrange_DG_AAC[0]; i <= IDrange_DG_AAC[1]; i++) {
    std::string dataset_div_post = "Div/DG-AAC/DG-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < div_data.size(); j++) {
        div_data[j] -= IDrange_DG_BCCCK[0];
    }
    div_DG_AAC_DG_BCCCK.insert({ i - IDrange_DG_AAC[0], div_data });
}

// DG-BC -> DG_BCCCK
std::map<int, std::vector<int>> div_DG_BC_DG_BCCCK;
for (int i = IDrange_DG_BC[0]; i <= IDrange_DG_BC[1]; i++) {
    std::string dataset_div_post = "Div/DG-BC/DG-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < div_data.size(); j++) {
        div_data[j] -= IDrange_DG_BCCCK[0];
    }
    div_DG_BC_DG_BCCCK.insert({ i - IDrange_DG_BC[0], div_data });
}

// DG-BCCCK -> DG_BCCCK
std::map<int, std::vector<int>> div_DG_BCCCK_DG_BCCCK;
for (int i = IDrange_DG_BCCCK[0]; i <= IDrange_DG_BCCCK[1]; i++) {
    std::string dataset_div_post = "Div/DG-BCCCK/DG-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < div_data.size(); j++) {
        div_data[j] -= IDrange_DG_BCCCK[0];
    }
    div_DG_BCCCK_DG_BCCCK.insert({ i - IDrange_DG_BCCCK[0], div_data });
}

// DG-HICAP -> DG_BCCCK
std::cout << "Loading DG_HICAP to DG_BCCCK" << std::endl;
std::map<int, std::vector<int>> div_DG_HICAP_DG_BCCCK;
for (int i = IDrange_DG_HICAP[0]; i <= IDrange_DG_HICAP[1]; i++) {
    std::string dataset_div_post = "Div/DG-HICAP/DG-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_BCCCK[0];
    div_DG_HICAP_DG_BCCCK.insert({ i - IDrange_DG_HICAP[0], div_data });
}

// DG-HIPP -> DG_BCCCK
std::cout << "Loading DG_HIPP to DG_BCCCK" << std::endl;
std::map<int, std::vector<int>> div_DG_HIPP_DG_BCCCK;
for (int i = IDrange_DG_HIPP[0]; i <= IDrange_DG_HIPP[1]; i++) {
    std::string dataset_div_post = "Div/DG-HIPP/DG-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_BCCCK[0];
    div_DG_HIPP_DG_BCCCK.insert({ i - IDrange_DG_HIPP[0], div_data });
}

// DG-MOPP -> DG_BCCCK
std::cout << "Loading DG_MOPP to DG_BCCCK" << std::endl;
std::map<int, std::vector<int>> div_DG_MOPP_DG_BCCCK;
for (int i = IDrange_DG_MOPP[0]; i <= IDrange_DG_MOPP[1]; i++) {
    std::string dataset_div_post = "Div/DG-MOPP/DG-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_BCCCK[0];
    div_DG_MOPP_DG_BCCCK.insert({ i - IDrange_DG_MOPP[0], div_data });
}

// DG-TML -> DG_BCCCK
std::cout << "Loading DG_TML to DG_BCCCK" << std::endl;
std::map<int, std::vector<int>> div_DG_TML_DG_BCCCK;
for (int i = IDrange_DG_TML[0]; i <= IDrange_DG_TML[1]; i++) {
    std::string dataset_div_post = "Div/DG-TML/DG-BCCCK/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_BCCCK[0];
    div_DG_TML_DG_BCCCK.insert({ i - IDrange_DG_TML[0], div_data });
}


// Insert DG_BCCCK into divergence maps
div_EC_LEC.insert({ "DG_BCCCK", div_EC_LEC_DG_BCCCK });
div_EC_MEC.insert({ "DG_BCCCK", div_EC_MEC_DG_BCCCK });
div_DG_GC.insert({ "DG_BCCCK", div_DG_GC_DG_BCCCK });
div_DG_AAC.insert({ "DG_BCCCK", div_DG_AAC_DG_BCCCK });
div_DG_BC.insert({ "DG_BCCCK", div_DG_BC_DG_BCCCK });
div_DG_BCCCK.insert({ "DG_BCCCK", div_DG_BCCCK_DG_BCCCK });
div_DG_HICAP.insert({ "DG_BCCCK", div_DG_HICAP_DG_BCCCK });
div_DG_HIPP.insert({ "DG_BCCCK", div_DG_HIPP_DG_BCCCK });
div_DG_MOPP.insert({ "DG_BCCCK", div_DG_MOPP_DG_BCCCK });
div_DG_TML.insert({ "DG_BCCCK",  div_DG_TML_DG_BCCCK });

// ------------------------------------------------------------
// DG_HICAP
// Presyn: EC_LEC, EC_MEC, DG_GC, DG_MC, DG_BC, DG_BCCCK, DG_HICAP, DG_HIPP, DG_MOPP, DG_TML
// ------------------------------------------------------------

std::cout << "Loading EC_LEC to DG_HICAP" << std::endl;
std::map<int, std::vector<int>> div_EC_LEC_DG_HICAP;
for (int i = IDrange_EC_LEC[0]; i <= IDrange_EC_LEC[1]; i++) {
    std::string dataset_div_post = "Div/EC-LEC/DG-HICAP/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_HICAP[0];
    div_EC_LEC_DG_HICAP.insert({ i - IDrange_EC_LEC[0], div_data });
}

std::cout << "Loading EC_MEC to DG_HICAP" << std::endl;
std::map<int, std::vector<int>> div_EC_MEC_DG_HICAP;
for (int i = IDrange_EC_MEC[0]; i <= IDrange_EC_MEC[1]; i++) {
    std::string dataset_div_post = "Div/EC-MEC/DG-HICAP/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_HICAP[0];
    div_EC_MEC_DG_HICAP.insert({ i - IDrange_EC_MEC[0], div_data });
}

std::cout << "Loading DG_GC to DG_HICAP" << std::endl;
std::map<int, std::vector<int>> div_DG_GC_DG_HICAP;
for (int i = IDrange_DG_GC[0]; i <= IDrange_DG_GC[1]; i++) {
    std::string dataset_div_post = "Div/DG-GC/DG-HICAP/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_HICAP[0];
    div_DG_GC_DG_HICAP.insert({ i - IDrange_DG_GC[0], div_data });
}

std::cout << "Loading DG_MC to DG_HICAP" << std::endl;
std::map<int, std::vector<int>> div_DG_MC_DG_HICAP;
for (int i = IDrange_DG_MC[0]; i <= IDrange_DG_MC[1]; i++) {
    std::string dataset_div_post = "Div/DG-MC/DG-HICAP/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_HICAP[0];
    div_DG_MC_DG_HICAP.insert({ i - IDrange_DG_MC[0], div_data });
}

std::cout << "Loading DG_BC to DG_HICAP" << std::endl;
std::map<int, std::vector<int>> div_DG_BC_DG_HICAP;
for (int i = IDrange_DG_BC[0]; i <= IDrange_DG_BC[1]; i++) {
    std::string dataset_div_post = "Div/DG-BC/DG-HICAP/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_HICAP[0];
    div_DG_BC_DG_HICAP.insert({ i - IDrange_DG_BC[0], div_data });
}

std::cout << "Loading DG_BCCCK to DG_HICAP" << std::endl;
std::map<int, std::vector<int>> div_DG_BCCCK_DG_HICAP;
for (int i = IDrange_DG_BCCCK[0]; i <= IDrange_DG_BCCCK[1]; i++) {
    std::string dataset_div_post = "Div/DG-BCCCK/DG-HICAP/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_HICAP[0];
    div_DG_BCCCK_DG_HICAP.insert({ i - IDrange_DG_BCCCK[0], div_data });
}

std::cout << "Loading DG_HICAP to DG_HICAP" << std::endl;
std::map<int, std::vector<int>> div_DG_HICAP_DG_HICAP;
for (int i = IDrange_DG_HICAP[0]; i <= IDrange_DG_HICAP[1]; i++) {
    std::string dataset_div_post = "Div/DG-HICAP/DG-HICAP/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_HICAP[0];
    div_DG_HICAP_DG_HICAP.insert({ i - IDrange_DG_HICAP[0], div_data });
}

std::cout << "Loading DG_HIPP to DG_HICAP" << std::endl;
std::map<int, std::vector<int>> div_DG_HIPP_DG_HICAP;
for (int i = IDrange_DG_HIPP[0]; i <= IDrange_DG_HIPP[1]; i++) {
    std::string dataset_div_post = "Div/DG-HIPP/DG-HICAP/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_HICAP[0];
    div_DG_HIPP_DG_HICAP.insert({ i - IDrange_DG_HIPP[0], div_data });
}

std::cout << "Loading DG_MOPP to DG_HICAP" << std::endl;
std::map<int, std::vector<int>> div_DG_MOPP_DG_HICAP;
for (int i = IDrange_DG_MOPP[0]; i <= IDrange_DG_MOPP[1]; i++) {
    std::string dataset_div_post = "Div/DG-MOPP/DG-HICAP/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_HICAP[0];
    div_DG_MOPP_DG_HICAP.insert({ i - IDrange_DG_MOPP[0], div_data });
}

std::cout << "Loading DG_TML to DG_HICAP" << std::endl;
std::map<int, std::vector<int>> div_DG_TML_DG_HICAP;
for (int i = IDrange_DG_TML[0]; i <= IDrange_DG_TML[1]; i++) {
    std::string dataset_div_post = "Div/DG-TML/DG-HICAP/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_HICAP[0];
    div_DG_TML_DG_HICAP.insert({ i - IDrange_DG_TML[0], div_data });
}

// Collect
div_EC_LEC.insert({ "DG_HICAP", div_EC_LEC_DG_HICAP });
div_EC_MEC.insert({ "DG_HICAP", div_EC_MEC_DG_HICAP });
div_DG_GC.insert({ "DG_HICAP",  div_DG_GC_DG_HICAP });
div_DG_MC.insert({ "DG_HICAP",  div_DG_MC_DG_HICAP });
div_DG_BC.insert({ "DG_HICAP",  div_DG_BC_DG_HICAP });
div_DG_BCCCK.insert({ "DG_HICAP", div_DG_BCCCK_DG_HICAP });
div_DG_HICAP.insert({ "DG_HICAP", div_DG_HICAP_DG_HICAP });
div_DG_HIPP.insert({ "DG_HICAP", div_DG_HIPP_DG_HICAP });
div_DG_MOPP.insert({ "DG_HICAP", div_DG_MOPP_DG_HICAP });
div_DG_TML.insert({ "DG_HICAP", div_DG_TML_DG_HICAP });


// ------------------------------------------------------------
// DG_HIPP
// Presyn: DG_GC, DG_MC, DG_TML
// ------------------------------------------------------------

std::cout << "Loading DG_GC to DG_HIPP" << std::endl;
std::map<int, std::vector<int>> div_DG_GC_DG_HIPP;
for (int i = IDrange_DG_GC[0]; i <= IDrange_DG_GC[1]; i++) {
    std::string dataset_div_post = "Div/DG-GC/DG-HIPP/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_HIPP[0];
    div_DG_GC_DG_HIPP.insert({ i - IDrange_DG_GC[0], div_data });
}

std::cout << "Loading DG_MC to DG_HIPP" << std::endl;
std::map<int, std::vector<int>> div_DG_MC_DG_HIPP;
for (int i = IDrange_DG_MC[0]; i <= IDrange_DG_MC[1]; i++) {
    std::string dataset_div_post = "Div/DG-MC/DG-HIPP/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_HIPP[0];
    div_DG_MC_DG_HIPP.insert({ i - IDrange_DG_MC[0], div_data });
}

std::cout << "Loading DG_TML to DG_HIPP" << std::endl;
std::map<int, std::vector<int>> div_DG_TML_DG_HIPP;
for (int i = IDrange_DG_TML[0]; i <= IDrange_DG_TML[1]; i++) {
    std::string dataset_div_post = "Div/DG-TML/DG-HIPP/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_HIPP[0];
    div_DG_TML_DG_HIPP.insert({ i - IDrange_DG_TML[0], div_data });
}

// Collect
div_DG_GC.insert({ "DG_HIPP", div_DG_GC_DG_HIPP });
div_DG_MC.insert({ "DG_HIPP", div_DG_MC_DG_HIPP });
div_DG_TML.insert({ "DG_HIPP", div_DG_TML_DG_HIPP });


// ------------------------------------------------------------
// DG_MOPP
// Presyn: EC_LEC, EC_MEC, DG_HIPP, DG_MOPP, DG_TML
// ------------------------------------------------------------

std::cout << "Loading EC_LEC to DG_MOPP" << std::endl;
std::map<int, std::vector<int>> div_EC_LEC_DG_MOPP;
for (int i = IDrange_EC_LEC[0]; i <= IDrange_EC_LEC[1]; i++) {
    std::string dataset_div_post = "Div/EC-LEC/DG-MOPP/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_MOPP[0];
    div_EC_LEC_DG_MOPP.insert({ i - IDrange_EC_LEC[0], div_data });
}

std::cout << "Loading EC_MEC to DG_MOPP" << std::endl;
std::map<int, std::vector<int>> div_EC_MEC_DG_MOPP;
for (int i = IDrange_EC_MEC[0]; i <= IDrange_EC_MEC[1]; i++) {
    std::string dataset_div_post = "Div/EC-MEC/DG-MOPP/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_MOPP[0];
    div_EC_MEC_DG_MOPP.insert({ i - IDrange_EC_MEC[0], div_data });
}

std::cout << "Loading DG_HIPP to DG_MOPP" << std::endl;
std::map<int, std::vector<int>> div_DG_HIPP_DG_MOPP;
for (int i = IDrange_DG_HIPP[0]; i <= IDrange_DG_HIPP[1]; i++) {
    std::string dataset_div_post = "Div/DG-HIPP/DG-MOPP/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_MOPP[0];
    div_DG_HIPP_DG_MOPP.insert({ i - IDrange_DG_HIPP[0], div_data });
}

std::cout << "Loading DG_MOPP to DG_MOPP" << std::endl;
std::map<int, std::vector<int>> div_DG_MOPP_DG_MOPP;
for (int i = IDrange_DG_MOPP[0]; i <= IDrange_DG_MOPP[1]; i++) {
    std::string dataset_div_post = "Div/DG-MOPP/DG-MOPP/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_MOPP[0];
    div_DG_MOPP_DG_MOPP.insert({ i - IDrange_DG_MOPP[0], div_data });
}

std::cout << "Loading DG_TML to DG_MOPP" << std::endl;
std::map<int, std::vector<int>> div_DG_TML_DG_MOPP;
for (int i = IDrange_DG_TML[0]; i <= IDrange_DG_TML[1]; i++) {
    std::string dataset_div_post = "Div/DG-TML/DG-MOPP/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_MOPP[0];
    div_DG_TML_DG_MOPP.insert({ i - IDrange_DG_TML[0], div_data });
}

// Collect
div_EC_LEC.insert({ "DG_MOPP", div_EC_LEC_DG_MOPP });
div_EC_MEC.insert({ "DG_MOPP", div_EC_MEC_DG_MOPP });
div_DG_HIPP.insert({ "DG_MOPP", div_DG_HIPP_DG_MOPP });
div_DG_MOPP.insert({ "DG_MOPP", div_DG_MOPP_DG_MOPP });
div_DG_TML.insert({ "DG_MOPP", div_DG_TML_DG_MOPP });


// ------------------------------------------------------------
// DG_TML
// Presyn: EC_LEC, EC_MEC, DG_HICAP, DG_HIPP, DG_MOPP, DG_TML
// ------------------------------------------------------------

std::cout << "Loading EC_LEC to DG_TML" << std::endl;
std::map<int, std::vector<int>> div_EC_LEC_DG_TML;
for (int i = IDrange_EC_LEC[0]; i <= IDrange_EC_LEC[1]; i++) {
    std::string dataset_div_post = "Div/EC-LEC/DG-TML/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_TML[0];
    div_EC_LEC_DG_TML.insert({ i - IDrange_EC_LEC[0], div_data });
}

std::cout << "Loading EC_MEC to DG_TML" << std::endl;
std::map<int, std::vector<int>> div_EC_MEC_DG_TML;
for (int i = IDrange_EC_MEC[0]; i <= IDrange_EC_MEC[1]; i++) {
    std::string dataset_div_post = "Div/EC-MEC/DG-TML/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_TML[0];
    div_EC_MEC_DG_TML.insert({ i - IDrange_EC_MEC[0], div_data });
}

std::cout << "Loading DG_HICAP to DG_TML" << std::endl;
std::map<int, std::vector<int>> div_DG_HICAP_DG_TML;
for (int i = IDrange_DG_HICAP[0]; i <= IDrange_DG_HICAP[1]; i++) {
    std::string dataset_div_post = "Div/DG-HICAP/DG-TML/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_TML[0];
    div_DG_HICAP_DG_TML.insert({ i - IDrange_DG_HICAP[0], div_data });
}

std::cout << "Loading DG_HIPP to DG_TML" << std::endl;
std::map<int, std::vector<int>> div_DG_HIPP_DG_TML;
for (int i = IDrange_DG_HIPP[0]; i <= IDrange_DG_HIPP[1]; i++) {
    std::string dataset_div_post = "Div/DG-HIPP/DG-TML/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_TML[0];
    div_DG_HIPP_DG_TML.insert({ i - IDrange_DG_HIPP[0], div_data });
}

std::cout << "Loading DG_MOPP to DG_TML" << std::endl;
std::map<int, std::vector<int>> div_DG_MOPP_DG_TML;
for (int i = IDrange_DG_MOPP[0]; i <= IDrange_DG_MOPP[1]; i++) {
    std::string dataset_div_post = "Div/DG-MOPP/DG-TML/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_TML[0];
    div_DG_MOPP_DG_TML.insert({ i - IDrange_DG_MOPP[0], div_data });
}

std::cout << "Loading DG_TML to DG_TML" << std::endl;
std::map<int, std::vector<int>> div_DG_TML_DG_TML;
for (int i = IDrange_DG_TML[0]; i <= IDrange_DG_TML[1]; i++) {
    std::string dataset_div_post = "Div/DG-TML/DG-TML/" + std::to_string(i);
    std::vector<int> div_data = tryReadVector(file, dataset_div_post);
    for (int j = 0; j < (int)div_data.size(); j++) div_data[j] -= IDrange_DG_TML[0];
    div_DG_TML_DG_TML.insert({ i - IDrange_DG_TML[0], div_data });
}

// Collect
div_EC_LEC.insert({ "DG_TML", div_EC_LEC_DG_TML });
div_EC_MEC.insert({ "DG_TML", div_EC_MEC_DG_TML });
div_DG_HICAP.insert({ "DG_TML", div_DG_HICAP_DG_TML });
div_DG_HIPP.insert({ "DG_TML", div_DG_HIPP_DG_TML });
div_DG_MOPP.insert({ "DG_TML", div_DG_MOPP_DG_TML });
div_DG_TML.insert({ "DG_TML",  div_DG_TML_DG_TML });


// Finally add divergence maps into big map
map_bigcon.insert({ "EC_LEC", div_EC_LEC});
map_bigcon.insert({ "EC_MEC", div_EC_MEC });
map_bigcon.insert({ "DG_GC", div_DG_GC });
map_bigcon.insert({ "DG_MC", div_DG_MC });
map_bigcon.insert({ "DG_BC", div_DG_BC });
map_bigcon.insert({ "DG_AAC", div_DG_AAC });
map_bigcon.insert({ "DG_BCCCK", div_DG_BCCCK });
map_bigcon.insert({ "DG_HICAP",div_DG_HICAP});
map_bigcon.insert({ "DG_HIPP", div_DG_HIPP });
map_bigcon.insert({ "DG_MOPP", div_DG_MOPP });
map_bigcon.insert({ "DG_TML",  div_DG_TML  });

