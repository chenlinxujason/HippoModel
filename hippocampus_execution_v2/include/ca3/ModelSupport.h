// Original simulator includes, connectivity callback, and coordinate writer.
/* * Copyright (c) 2016 Regents of the University of California. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
*
* 3. The names of its contributors may not be used to endorse or promote
*    products derived from this software without specific prior written
*    permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
* PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* *********************************************************************************************** *
* CARLsim
* created by: (MDR) Micah Richert, (JN) Jayram M. Nageswaran
* maintained by:
* (MA) Mike Avery <averym@uci.edu>
* (MB) Michael Beyeler <mbeyeler@uci.edu>,
* (KDC) Kristofor Carlson <kdcarlso@uci.edu>
* (TSC) Ting-Shuo Chou <tingshuc@uci.edu>
* (HK) Hirak J Kashyap <kashyaph@uci.edu>
*
* CARLsim v1.0: JM, MDR
* CARLsim v2.0/v2.1/v2.2: JM, MDR, MA, MB, KDC
* CARLsim3: MB, KDC, TSC
* CARLsim4: TSC, HK
* CARLsim5: HK, JX, KC
* CARLsim6: LN, JX, KC, KW
*
* CARLsim available from http://socsci.uci.edu/~jkrichma/CARLsim/
* Ver 12/31/2016
*/

#include <spikegen_from_file.h>

// include CARLsim user interface
#include <carlsim.h>

// include stopwatch for timing
#include <stopwatch.h>

// include library for hdf5 i/o
#include <highfive/H5File.hpp>
using HighFive::File;

using HighFive::DataSet;// chatGPT
using namespace std;//chatGPT
#include <iostream>     // std::cout
#include <sstream>      // std::istringstream
#include <map>
#include <unordered_map>
#include <spikegen_from_file.h>
#include <numeric>
#include <cmath> 
#include <fstream>
#include <vector>
#include <random>    // <-- added for jitter (0,1] ms

// File name
const std::string FILE_NAME = "connectivity/CA1EC_scale2_DGMC_scale5_data_divergence_scale10.h5";//scale 10
//const std::string FILE_NAME = "connectivity/CA1_ECscale2_data_divergence_scale500.h5";//scale 500

// Global variable to access connectivity
std::map<std::string, std::map<std::string, std::map<int, std::vector<int>>>> map_bigcon;
std::map<std::string, int> map_IDoffset;
std::map<std::string, std::map<std::string, float>> map_weight;
//std::map<int, std::vector<int>> bigcon;


// Global variable - seperate CA3PC as a, b and c (ab looks fine, only need c)
//std::vector<int> IDs_ab;  
std::vector<int> IDs_a; 
std::vector<int> IDs_b; 
std::vector<int> IDs_c;

// Global variable - Seperate DGGC 
std::vector<int> IDs_supra; 
std::vector<int> IDs_infra; 

// Helper function that tries to read a dataset.
// If it doesn’t exist, returns an empty vector.

std::vector<int> tryReadVector(File& file, const std::string& datasetName) {
    std::vector<int> con_data;
    try {
        file.getDataSet(datasetName).read(con_data);
    } catch (HighFive::Exception& e) {
        // If dataset doesn’t exist or can’t be read, return empty
        con_data.clear();
    }
    return con_data;
}

// custom class for loading connectivity from hdf5 file
#include <algorithm> // for std::count, std::find
std::vector<float> locs_x_MEC,    locs_y_MEC;
std::vector<float> locs_x_LEC,    locs_y_LEC;
std::vector<float> locs_x_DGGC,   locs_y_DGGC;
std::vector<float> locs_x_CA3PC,   locs_y_CA3PC;
std::vector<float> locs_x_CA3AAC, locs_y_CA3AAC;
std::vector<float> locs_x_CA3BC,   locs_y_CA3BC;
std::vector<float> locs_x_CA3BCCCK, locs_y_CA3BCCCK;
std::vector<float> locs_x_CA3BisC, locs_y_CA3BisC;
std::vector<float> locs_x_CA3MFA,  locs_y_CA3MFA;
std::vector<float> locs_x_CA3OLM, locs_y_CA3OLM;
std::vector<float> locs_x_CA3TL,  locs_y_CA3TL;

class MyConnection : public ConnectionGenerator {
public:
    MyConnection() {}
    ~MyConnection() {}

    void connect(CARLsim* sim, int srcGrp, int i, int destGrp, int j, float& weight, float& maxWt, float& delay, bool& connected) {
        // Group names
        std::string name_src  = sim->getGroupName(srcGrp);
        std::string name_dest = sim->getGroupName(destGrp);

        // Global IDs
        int ID_pre  = i + map_IDoffset[name_src];
        int ID_post = j + map_IDoffset[name_dest];

        // Fan-out list for this post neuron from this source group
        auto& fanout = map_bigcon[name_src][name_dest][ID_pre];  // reduant: connected = (std::find(fanout.begin(), fanout.end(), ID_post) != fanout.end());
        // Example: if pre neuron 5 connects twice to post neuron 0, then fanout[0] = { 5, 5, 7, 8 };
        connected = true;// All iterated connections are true but need to set synaptic weight

        float w_0 = map_weight[name_src][name_dest]; // Don't need to count repeats for divergence
        float base_w = w_0;

        if (name_dest == "CA3_PC") { // IDs_c is global ID
            int post_gid = map_IDoffset["CA3_PC"] + j;   // global CA3_PC id
            const bool postIsC_c = (std::find(IDs_c.begin(), IDs_c.end(), post_gid) != IDs_c.end());

            if (postIsC_c) {
                if (name_src == "CA3_PC")                                base_w = w_0;         // unchanged
                else if (name_src == "EC_MEC" || name_src == "EC_LEC")   base_w = w_0 * 1.0f;  // unchanged
                else if (name_src == "DG_GC")                            base_w = w_0 * 1.8f;  // stronger DG→CA3c,1.8
                else                                                     base_w = w_0 * 0.8f;  // inhibitory to CA3c slightly down,0.8
            }
            // else: CA3_PC a/b → keep base_w = w_0; 
        }

        weight = base_w;  // don't need to count repeat
       
       //maxWt = 2.0f;
       //delay  = 1.0f; // fixed delay
        
        // ##############################################################
        // ## Delay: directly from HDF5 soma coordinates (in mm) — safe
        // ##############################################################
        
        // Check missing offset
        auto getCoords = [&](const std::string& g, int gid)->std::pair<float,float> {
             static int nan_dbg = 0;                // only report a few times to avoid spam
             auto it = map_IDoffset.find(g);
             if (it == map_IDoffset.end()) {
                 if (nan_dbg < 20) {
                     std::cout << "[COORDS] MISSING OFFSET for group=" << g << " (gid=" << gid << ")" << std::endl;
                     nan_dbg++;
                 }
                 return {NAN, NAN};
             }

         int local_id = gid - it->second;

         // 'Out of Bound, OOB' check
         auto safe = [&](const std::vector<float>& xs, const std::vector<float>& ys) {
             if (local_id >= 0 && local_id < (int)xs.size() && local_id < (int)ys.size())
                 return std::make_pair(xs[local_id], ys[local_id]);
             if (nan_dbg < 20) {
                 std::cout << "[COORDS] OOB for group=" << g
                           << " gid=" << gid << " offset=" << it->second
                           << " local_id=" << local_id
                           << " xs.size()=" << xs.size()
                           << " ys.size()=" << ys.size() << std::endl;
                 nan_dbg++;
             }
             return std::make_pair(NAN, NAN);
         };

         if (g == "EC_MEC") return safe(locs_x_MEC, locs_y_MEC);
         else if (g == "EC_LEC") return safe(locs_x_LEC, locs_y_LEC);
         else if (g == "DG_GC") return safe(locs_x_DGGC, locs_y_DGGC);
         else if (g == "CA3_PC") return safe(locs_x_CA3PC, locs_y_CA3PC);
         else if (g == "CA3_AAC") return safe(locs_x_CA3AAC, locs_y_CA3AAC);
         else if (g == "CA3_BC") return safe(locs_x_CA3BC, locs_y_CA3BC);
         else if (g == "CA3_BCCCK") return safe(locs_x_CA3BCCCK, locs_y_CA3BCCCK);
         else if (g == "CA3_BisC") return safe(locs_x_CA3BisC, locs_y_CA3BisC);
         else if (g == "CA3_MFA") return safe(locs_x_CA3MFA, locs_y_CA3MFA);
         else if (g == "CA3_OLM") return safe(locs_x_CA3OLM, locs_y_CA3OLM);
         else if (g == "CA3_TL") return safe(locs_x_CA3TL, locs_y_CA3TL);
  
         if (nan_dbg < 20) {
             std::cout << "[COORDS] UNKNOWN GROUP=" << g << " (gid=" << gid << ")" << std::endl;
             nan_dbg++;
         }
         return {NAN, NAN};
       };

        auto preXY  = getCoords(name_src,  ID_pre);// use global ID to calculate distance
        auto postXY = getCoords(name_dest, ID_post);// use global ID to calculate distance

        float x_pre_mm  = preXY.first,  y_pre_mm  = preXY.second;
        float x_post_mm = postXY.first, y_post_mm = postXY.second;

        float velocity = 0.13f;  // default velocity for INs

        if (name_src == "EC_MEC") {velocity = 0.32f;} // MEC_SC(layer 2) velocity
        else if (name_src == "EC_LEC") {velocity = 1.36f;} // LEC_SC(layer 2) velocity
        else if (name_src == "DG_GC") {velocity = 0.27f;} // DG_GC mossy fiber velocity
        else if (name_src == "CA3_PC") {velocity = 0.39f;}// CA3_PC associational velocity
        
        float dx=0.0f, dy=0.0f, dist_mm=0.0f;
        if (std::isfinite(x_pre_mm) && std::isfinite(y_pre_mm) &&
            std::isfinite(x_post_mm) && std::isfinite(y_post_mm)) {
            dx = x_pre_mm - x_post_mm;
            dy = y_pre_mm - y_post_mm;
            dist_mm = std::sqrt(dx*dx + dy*dy);
            delay = dist_mm / velocity;
        } else {
            delay = 1.0f;
        }
        
        // -------------------------------
        // Extra jitter for REPEAT fanout:
        // if this pre→post pair appears >1 times in fanout, add random (0,1] ms
        // -------------------------------
        {
            int repeats = std::count(fanout.begin(), fanout.end(), ID_post);
            if (repeats > 1) {
                // thread-local RNG for OpenMP safety
                static thread_local std::mt19937 rng(std::random_device{}());
                std::uniform_real_distribution<float> U01(0.0f, 1.0f); // [0,1)
                float jitter_ms = 1.0f - U01(rng); // (0,1]
                delay += jitter_ms;
            }
        }

         //  Debug: print only first 10 valid connections

        static int conn_count = 0;
        if (conn_count < 10) {
            std::cout << "Conn " << (conn_count+1)
                      << " | src=" << name_src << " GID_pre=" << ID_pre
                      << " | dst=" << name_dest << " GID_post=" << ID_post
                      << " | pre=(" << x_pre_mm << "," << y_pre_mm << ")"
                      << " post=("<< x_post_mm << "," << y_post_mm << ")"
                      << " | dist_mm=" << dist_mm
                      << " | velocity=" << velocity
                      << " | delay_ms=" << delay
                 << std::endl;
            conn_count++;
           }
        }
};


// Save locs data to binary file
void saveToBinaryFile(const std::vector<float>& locs_x, const std::vector<float>& locs_y, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file");
    }

    // Assuming locs_x and locs_y are of the same size
    for (size_t i = 0; i < locs_x.size(); ++i) {
        file.write(reinterpret_cast<const char*>(&locs_x[i]), sizeof(float));
        file.write(reinterpret_cast<const char*>(&locs_y[i]), sizeof(float));
    }

    file.close();
}



