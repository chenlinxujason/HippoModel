
#include <carlsim.h> // include CARLsim user interface
#include <boost/iterator/counting_iterator.hpp>
#include <ctime>
#include <cstdlib>
#include <spikegen_from_file.h>
#include <stopwatch.h>
#include <map>
#include "../Nelder_Mead_Opt.h"// 

#include <spikegen_from_file.h>
#include <carlsim.h>
#include <stopwatch.h>

//Global variables
int randSeed = 42; //user defined randseed
int numGPUs = 1;  // Patch Killian
CARLsim sim("dg_test", GPU_MODE, USER, numGPUs, randSeed);

std::map<std::string, int> connectionIDs;  // Connection identifiers
// usage: connectionIDs["string"] = 2, meaning: string,2

SpikeMonitor* spikeMonDGGC = nullptr;
SpikeMonitor* spikeMonDGBC = nullptr;

float targetMeanDGGC = 0.4f;
float targetMeanDGBC = 20.0f;

// Initial weights
float baselineWts[] = {1.064f, 1.38f, 1.112f, 1.112f, 0.992f, 0.992f};  // Baseline weights - Hippocampome.org
//float baselineWts[] = {0.001f, 0.02f, 0.5f, 0.5f, 1.1f, 1.1f};  // Baseline weights - fine-tune results

// lower and upper bound
const double lowerBound = 0.0001f;
const double upperBound = 4.0f;

// Defined the number of neurons in the network
int num_EC_MEC = 66000;//66000
int num_EC_LEC = 46000;//46000
int num_DGGC = 119998;//119998
int num_DGBC = 8075;//8075

// Outputs both scaled factors and their effective weights given the baseline
void printOptimizedParameters(const std::vector<double>& optimizedParams, const float baselineWts[]) {
    std::cout << "Optimized Scaling Factors: ";
    for (auto& scale : optimizedParams) {
        std::cout << scale << " ";
    }
    std::cout << std::endl;

    std::cout << "Optimized Weights: ";
    for (int i = 0; i < optimizedParams.size(); ++i) {
        std::cout << (baselineWts[i] * optimizedParams[i]) << " ";
    }
    std::cout << std::endl;
}

double clip(double value, double lowerBound, double upperBound) {
    double clipped = std::max(lowerBound, std::min(value, upperBound));
    return (clipped <= lowerBound) ? lowerBound + std::numeric_limits<double>::epsilon() : clipped;
}

// setup Network
void setupNetwork() {

   // Set Izhikevich Neuron  
    int DG_GC = sim.createGroup("DG_GC", num_DGGC, EXCITATORY_NEURON, 0, GPU_CORES);                        
    int DG_BC = sim.createGroup("DG_BC", num_DGBC, INHIBITORY_NEURON, 0, GPU_CORES);                        
    int EC_MEC = sim.createSpikeGeneratorGroup("EC_MEC", num_EC_MEC, EXCITATORY_NEURON, 0, GPU_CORES);               
    int EC_LEC = sim.createSpikeGeneratorGroup("EC_LEC", num_EC_LEC, EXCITATORY_NEURON, 0, GPU_CORES); 

//SpikeGeneratorFromFile SGF("results/MEC_65999cells_10sec.dat"); //AER format MECCells_Spike.dat

// associate group g0 with SGF
//sim.setSpikeGenerator(EC_MEC, &SGF);
 
   // Set Izhikevich Parameter: C , k, Vr, Vt, a , b , vpeak , vmin , d
    sim.setNeuronParameters(DG_GC, 38.0, 0.0, 0.45, 0.0, -77.4, 0.0, -44.9, 0.0, 0.003, 0.0, 24.48, 0.0, 15.49, 0.0, -66.47, 0.0, 50.0, 0.0);//ok
                     
    sim.setNeuronParameters(DG_BC, 208.0, 0.0, 0.81, 0.0, -61.02, 0.0, -37.84, 0.0, 0.097, 0.0, 1.89, 0.0, 14.08, 0.0, -36.23, 0.0, 553.0, 0.0);//ok
    
    // Connect neuron groups
    #include "../Connection.h"
    
    sim.setConductances(true);// COBA
    sim.setConductances(DG_GC, 8.6, 0, 43.2, 30.6, 0, 43.2); //exc: 8.6ms 43.2ms; inh: 30.6ms 43.2ms
    sim.setConductances(DG_BC, 12.8, 0, 43.2, 5, 0, 43.2);//or 0.65ms, 43.2ms; 4,150

    //set NeuronMonitor                                   
    //sim.setNeuronMonitor(DG_GC, "DEFAULT"); 
    //sim.setNeuronMonitor(DG_BC, "DEFAULT");

	sim.setIntegrationMethod(RUNGE_KUTTA4, 10);
	
	sim.setupNetwork();// setup network BEFORE Poisson generator
    
    // set Poisson generator
    PoissonRate* const poissRate_EC_MEC = new PoissonRate(num_EC_MEC);
    poissRate_EC_MEC->setRates(2.04f);  // Set firing rate
    sim.setSpikeRate(EC_MEC, poissRate_EC_MEC);  

    PoissonRate* const poissRate_EC_LEC = new PoissonRate(num_EC_LEC);
    poissRate_EC_LEC->setRates(2.04f);  // Set firing rate
    sim.setSpikeRate(EC_LEC, poissRate_EC_LEC);  

    //sim.setSpikeMonitor(EC_MEC, "DEFAULT");
    //sim.setSpikeMonitor(EC_LEC, "DEFAULT");
    
	spikeMonDGGC = sim.setSpikeMonitor(DG_GC, "NULL");//"DEFAULT": create binary file; "NULL": no binary file
    spikeMonDGBC = sim.setSpikeMonitor(DG_BC, "NULL");//"DEFAULT": create binary file; "NULL": no binary file
                                                                       
}


//double objectiveFunction(const std::vector<double>& params) {
double objectiveFunction(const std::vector<double>& params, bool output = true) {
  
    std::vector<double> scaledParams(params.size());
    double penalty = 0.0;

    // Clip parameters
    for (int i = 0; i < params.size(); ++i) {
        scaledParams[i] = clip(params[i], lowerBound, upperBound);
    }

    // Scale weights according to the parameters for measurement
    sim.scaleWeights(connectionIDs["DGGC_DGBC"], scaledParams[0], true);
    sim.scaleWeights(connectionIDs["DGBC_DGGC"], scaledParams[1], true);
    sim.scaleWeights(connectionIDs["MEC_DGGC"], scaledParams[2], true);
    sim.scaleWeights(connectionIDs["LEC_DGGC"], scaledParams[3], true);
    sim.scaleWeights(connectionIDs["MEC_DGBC"], scaledParams[4], true);
    sim.scaleWeights(connectionIDs["LEC_DGBC"], scaledParams[5], true);

    // Measurement phase
    sim.runNetwork(10,0);  // Run 10 sec as transient time when synpatic weights are scaled
    
    // Start measurment
    spikeMonDGGC->startRecording();
    spikeMonDGBC->startRecording();
    
    sim.runNetwork(10,0);  // Run for 10 seconds for measurements
    
    spikeMonDGGC->stopRecording();
    spikeMonDGBC->stopRecording();

    std::vector<float> DGGCFRs = spikeMonDGGC->getAllFiringRates(); //6512 supra, 5488 infra
    std::vector<float> DGBCFRs = spikeMonDGBC->getAllFiringRates(); //6512 supra, 5488 infra
    
    // Reset weights to baseline after measurement
    sim.scaleWeights(connectionIDs["DGGC_DGBC"], 1.0 / scaledParams[0], true);
    sim.scaleWeights(connectionIDs["DGBC_DGGC"], 1.0 / scaledParams[1], true);
    sim.scaleWeights(connectionIDs["MEC_DGGC"], 1.0 / scaledParams[2], true);
    sim.scaleWeights(connectionIDs["LEC_DGGC"], 1.0 / scaledParams[3], true);
    sim.scaleWeights(connectionIDs["MEC_DGBC"], 1.0 / scaledParams[4], true);
    sim.scaleWeights(connectionIDs["LEC_DGBC"], 1.0 / scaledParams[5], true);
    
    // Calculate mean firing rates  
    int sizeDGGC = DGGCFRs.size();
    float sumDGGC = std::accumulate(DGGCFRs.begin(), DGGCFRs.end(), 0.0f);
    float meanDGGC = sumDGGC / sizeDGGC;
          
    int sizeDGBC = DGBCFRs.size();
    float sumDGBC = std::accumulate(DGBCFRs.begin(), DGBCFRs.end(), 0.0f);
    float meanDGBC = sumDGBC / sizeDGBC;


    // Calculate error with penalties for large deviations
    double deviationDGGC = fabs(meanDGGC - targetMeanDGGC);
    double deviationDGBC = fabs(meanDGBC - targetMeanDGBC);

    double errorDGGC = deviationDGGC / fabs(targetMeanDGGC); 
    double errorDGBC = deviationDGBC / fabs(targetMeanDGBC);
    double totalError = pow(errorDGGC,2) + pow(errorDGBC,2);
    
    // Adding penalties for deviations exceeding specific thresholds
    if (deviationDGGC > 0.1 * targetMeanDGGC) {
        penalty += 2 * std::pow(deviationDGGC - 0.1 * targetMeanDGGC, 2);
    }
    if (deviationDGBC > 0.1 * targetMeanDGBC) {
        penalty += 10 * std::pow(deviationDGBC - 0.1 * targetMeanDGBC, 2);
    }
    
    totalError += penalty;
           
    std::cout << "mean firing rate of DGGC = " << meanDGGC << std::endl;
    std::cout << "mean firing rate of DGBC = " << meanDGBC << std::endl;
    std::cout << "Total error (including penalties):" << totalError << std::endl;
    
    return totalError;
    
    //return std::numeric_limits<double>::max();
}



int main() {

try {
    // Initialize the simplex with your starting guesses for the parameters
    #include "../InitializeSimplex.h"
    
    // Setup Network
    setupNetwork();
    
    // Run transient phase (without scaled weights)
    sim.runNetwork(10,0);  // Initial transient time
    
    // Run Nelder-Mead optimization with specific simplex
    std::vector<double> optimizedParams = nelderMead(objectiveFunction, initialSimplex);
    
    // Run multi-start Nelder-Mead optimization
    //int numStarts = 20; // Number of random starts
    //int dimensions = 6; // Number of parameters
    //std::vector<double> optimizedParams = multiStartNelderMead(objectiveFunction, numStarts, dimensions);
    

    printOptimizedParameters(optimizedParams, baselineWts);  // Print both scaling factors and effective weights


    return 0;// success
 } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
        return 1;  // signal error
    }
    return 0;
}
