#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <cmath> 
#include <numeric>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <omp.h> // OpenMP header for parallelization

// Helper functions

// Function to print results
void printVector(const std::vector<double>& vec, double value) {
    for (const auto& v : vec) {
        std::cout << v << " ";
    }
    std::cout << " with Objective: " << value << std::endl;
}

// Function to clip parameters within lower and upper bound
void clip(std::vector<double>& parameters, double lowerBound, double upperBound) {
    for (auto& value : parameters) {
        value = std::max(lowerBound, std::min(value, upperBound));
    }
}

// Function to save data
void saveData(const std::vector<int>& iterations, const std::vector<double>& objectiveValues, const std::vector<std::vector<double>>& parameterTrajectory, const std::string& filename) {
    std::ofstream file(filename);
    for (size_t i = 0; i < iterations.size(); i++) {
        file << iterations[i] << ", " << objectiveValues[i];
        for (double param : parameterTrajectory[i]) {
            file << ", " << param;
        }
        file << "\n";
    }
    file.close();
}

// Function to sort simplex and calculate centroid
void updateSimplexAndCentroid(
    std::vector<std::pair<std::vector<double>, double>>& simplex_pairs,
    std::vector<double>& centroid) 
{
    //std::cout << "Start sorting simplex" << std::endl;
    std::sort(simplex_pairs.begin(), simplex_pairs.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;  // Sort based on the second element of the pairs
    });
    //std::cout << "Finish sorting simplex" << std::endl;

    // Calculate the centroid of all but the worst point
    std::fill(centroid.begin(), centroid.end(), 0.0);
    for (size_t i = 0; i < simplex_pairs.size() - 1; ++i) {
        for (size_t j = 0; j < simplex_pairs[i].first.size(); ++j) {
            centroid[j] += simplex_pairs[i].first[j];
        }
    }
    for (size_t j = 0; j < centroid.size(); ++j) {
        centroid[j] /= (simplex_pairs.size() - 1);
    }
}


// Function to reinstall simplex when objective value reach local minimal that far away from targeted value.
void CheckReinstall(int& stallCounter, double& lastBestValue, double bestObjectiveValue, 
                    std::vector<std::pair<std::vector<double>, double>>& simplex_pairs, 
                    const std::vector<double>& bestSolution, double lowerBound, double upperBound, 
                    std::vector<int>& iterations, std::vector<double>& objectiveValues, 
                    std::vector<std::vector<double>>& parameterTrajectory, 
                    const std::function<double(const std::vector<double>&, bool)>& func, 
                    std::vector<double>& centroid, int& iteration) {

    if (std::fabs(lastBestValue - bestObjectiveValue) <= 0.02) {
        stallCounter++;
        std::cout << "stallCount = " << stallCounter << std::endl;
        if (stallCounter >= 5) {
            std::cout << "Stalling detected. Performing an informed restart...\n";
            
            // Reset the first vertex to the best solution
            simplex_pairs[0].first = bestSolution;
            simplex_pairs[0].second = bestObjectiveValue;  // Update with the known best value

            // Randomly generate new solutions around the best solution
            for (size_t i = 1; i < simplex_pairs.size(); ++i) {
                for (size_t j = 0; j < simplex_pairs[i].first.size(); ++j) {
                    //double random_offset = ((double)rand() / RAND_MAX - 0.5) * (upperBound - lowerBound) * 0.1;
                    double random_offset = ((double)rand() / RAND_MAX - 0.5) * (upperBound - lowerBound) * 0.1;
                    simplex_pairs[i].first[j] = bestSolution[j] + random_offset;
                    //std::cout << "Random offset for vertex " << i << ", dimension " << j << ": " << random_offset << std::endl;
                }
                clip(simplex_pairs[i].first, lowerBound, upperBound);
                simplex_pairs[i].second = func(simplex_pairs[i].first, false);
            }

            lastBestValue = bestObjectiveValue;
            stallCounter = 0;
            
            iteration++;
            iterations.push_back(iteration);
            objectiveValues.push_back(bestObjectiveValue);
            parameterTrajectory.push_back(bestSolution);
            saveData(iterations, objectiveValues, parameterTrajectory, "nelder_mead_output.txt");
            
            std::cout << "Iteration " << iteration << ": Restart and reinitialization completed.\n";
        }
    } else {
        stallCounter = 0;
        lastBestValue = bestObjectiveValue;
    }
}

// Function to adjuast alpha,gamma,rho,and sigma dynamically based on the proximity to targeted value
double adjustCoefficient(double currentCoefficient, double bestObjectiveValue, double tolerance, bool isImproving) {
    double adjustmentFactor = 1.0;
    double distanceToTolerance = fabs(bestObjectiveValue - tolerance);

    if (!isImproving) {
        if (distanceToTolerance > tolerance * 150) {  
            currentCoefficient = currentCoefficient + 0.6;
            adjustmentFactor = 1.1; 
        }
        
        else if (distanceToTolerance > tolerance * 90 && distanceToTolerance <= tolerance * 150) {  
            currentCoefficient = currentCoefficient + 0.3;
            adjustmentFactor = 1.06; 
        }
        
        else if (distanceToTolerance > tolerance * 30 && distanceToTolerance <= tolerance * 90) {  
            currentCoefficient = currentCoefficient + 0.2;
            adjustmentFactor = 1.0; 
        }
        
        else {  // Close to tolerance, be more conservative
            currentCoefficient = currentCoefficient + 0.1;
            adjustmentFactor = 0.95;//0.95
        }
    } 
    
    
    else {
        currentCoefficient = currentCoefficient - 0.3;
        adjustmentFactor = 0.98; // Slow down adjustments if improving,0.98
    }
    return currentCoefficient * adjustmentFactor;
}

std::vector<double> nelderMead(const std::function<double(const std::vector<double>&, bool)>& func,
                               std::vector<std::vector<double>> simplex,
                               double lowerBound, double upperBound,
                               double tolerance, int maxIterations) {  
    
    // Default parameters
    double alpha = 1.0;
    double gamma = 2.0;
    double rho = 0.5;
    double sigma = 0.5;

    for (auto& vertex : simplex) {
        clip(vertex, lowerBound, upperBound);
    }

    double bestObjectiveValue = std::numeric_limits<double>::infinity();
    std::vector<double> bestSolution;
    
    std::vector<int> iterations;
    std::vector<double> objectiveValues;
    std::vector<std::vector<double>> parameterTrajectory;
    std::vector<double> centroid(simplex[0].size(), 0.0);

    int iteration = 0;
    int stallCounter = 0;
    double lastBestValue = bestObjectiveValue;
    bool foundOptimal = false;
    
    iterations.push_back(iteration);
    objectiveValues.push_back(bestObjectiveValue);
    parameterTrajectory.push_back(bestSolution);
    saveData(iterations, objectiveValues, parameterTrajectory, "nelder_mead_output.txt");
    

    // Use simplex_pairs to store objective function value to avoid multiple access of function
    std::vector<double> objectives(simplex.size());
    std::vector<std::pair<std::vector<double>, double>> simplex_pairs(simplex.size());
    for (size_t i = 0; i < simplex.size(); ++i) {
        objectives[i] = func(simplex[i], false);
        simplex_pairs[i].first = simplex[i];
        simplex_pairs[i].second = objectives[i];
        if (objectives[i] < bestObjectiveValue) {
            bestObjectiveValue = objectives[i];
            bestSolution = simplex[i];
        }
        iteration++;
        std::cout << "Iteration " << iteration << ": calculate vertice " << i + 1 << " to point ";
        printVector(simplex[i], objectives[i]);
        
        iterations.push_back(iteration);
        objectiveValues.push_back(objectives[i]);
        parameterTrajectory.push_back(simplex[i]);
        saveData(iterations, objectiveValues, parameterTrajectory, "nelder_mead_output.txt");
        
        if (bestObjectiveValue <= tolerance) {
            foundOptimal = true;
            std::cout << "Optimal solution found during sorting with objective value: " << bestObjectiveValue << ".\n";
            iterations.push_back(iteration);
            objectiveValues.push_back(bestObjectiveValue);
            parameterTrajectory.push_back(bestSolution);
            saveData(iterations, objectiveValues, parameterTrajectory, "nelder_mead_output.txt");
            return bestSolution;
        }
    }

   // updateSimplexAndCentroid(simplex, centroid, func);

    while (iteration < maxIterations && !foundOptimal) {
    
       updateSimplexAndCentroid(simplex_pairs, centroid);
       double worstObjectiveValue = simplex_pairs.back().second;
       double secondWorstObjectiveValue = simplex_pairs[simplex_pairs.size() - 2].second;
       double bestObjectiveValue = simplex_pairs.front().second;
       
        // Reflection process 
        std::vector<double> reflection(centroid.size());
        for (size_t j = 0; j < centroid.size(); ++j) {
            //reflection[j] = centroid[j] + alpha * (centroid[j] - simplex.back()[j]);
            reflection[j] = centroid[j] + alpha * (centroid[j] - simplex_pairs.back().first[j]);
        }

        clip(reflection, lowerBound, upperBound);
        double reflectionValue = func(reflection, true);
        iteration++;
        iterations.push_back(iteration);
        objectiveValues.push_back(reflectionValue);
        parameterTrajectory.push_back(reflection);
        saveData(iterations, objectiveValues, parameterTrajectory, "nelder_mead_output.txt");
        
        std::cout << "Iteration " << iteration << ": Reflection performed to point ";
        printVector(reflection, reflectionValue);

        if (reflectionValue <= tolerance) {
            std::cout << "Optimal solution found during reflection.\n";
            return reflection;
        }
        
        // Decision logic for next steps based on the reflection result
        if (reflectionValue < bestObjectiveValue) { // Expansion if reflection is better
            
            //alpha *= 1.01; // Increase alpha that encourages further exploration in that direction
            double alpha = adjustCoefficient(alpha, bestObjectiveValue, tolerance, reflectionValue < bestObjectiveValue);

            std::vector<double> expansion(centroid.size());
            for (size_t j = 0; j < centroid.size(); ++j) {
                expansion[j] = centroid[j] + gamma * (reflection[j] - centroid[j]);
            }
            
            clip(expansion, lowerBound, upperBound);
            double expansionValue = func(expansion, true);
            iteration++;
            iterations.push_back(iteration);
            objectiveValues.push_back(expansionValue);
            parameterTrajectory.push_back(expansion);
            saveData(iterations, objectiveValues, parameterTrajectory, "nelder_mead_output.txt");
            
            std::cout << "Iteration " << iteration << ": Expansion performed to point ";
            printVector(expansion, expansionValue);

            if (expansionValue < reflectionValue) { // Replace worst with expansion
                //gamma *= 1.01;
                double gamma = adjustCoefficient(gamma, bestObjectiveValue, tolerance, expansionValue < reflectionValue);

                //simplex.back() = expansion; // Replace worst with expansion
                simplex_pairs.back().first = expansion;  // Do not directly access func, use simplex_pair to replace
                simplex_pairs.back().second = expansionValue;
                bestSolution = expansion;
                bestObjectiveValue = expansionValue;
                //updateSimplexAndCentroid(simplex, centroid, func);
                updateSimplexAndCentroid(simplex_pairs, centroid);
                
                if (expansionValue <= tolerance) {
                    std::cout << "Optimal solution found during expansion.\n";
                    return expansion;
                }
                
                CheckReinstall(stallCounter, lastBestValue, bestObjectiveValue, simplex_pairs, bestSolution, 
                   lowerBound, upperBound, iterations, objectiveValues, parameterTrajectory, 
                   func, centroid, iteration);
            
             }  else { // Replace worst with reflection
                //gamma *= 0.98;
                double gamma = adjustCoefficient(gamma, bestObjectiveValue, tolerance, expansionValue < reflectionValue);

                //simplex.back() = reflection; 
                simplex_pairs.back().first = reflection;  
                simplex_pairs.back().second = reflectionValue;
                bestSolution = reflection;
                bestObjectiveValue = reflectionValue;
                //updateSimplexAndCentroid(simplex, centroid, func);
                updateSimplexAndCentroid(simplex_pairs, centroid);
                
                if (reflectionValue <= tolerance) {
                    std::cout << "Optimal solution found during reflection.\n";
                    return reflection;
                }
                
                CheckReinstall(stallCounter, lastBestValue, bestObjectiveValue, simplex_pairs, bestSolution, 
                   lowerBound, upperBound, iterations, objectiveValues, parameterTrajectory, 
                   func, centroid, iteration);
                
            }

        } else if (reflectionValue >= worstObjectiveValue) { // Handle contraction towards worst
            
            //alpha *= 0.98; // Decrease alpha if reflection was not successful
            double alpha = adjustCoefficient(alpha, bestObjectiveValue, tolerance, reflectionValue < bestObjectiveValue);
            
            // Contraction towards centroid if reflection is not better than the worst
            
            std::vector<double> contraction(centroid.size());
            for (size_t j = 0; j < centroid.size(); ++j) {
               // contraction[j] = centroid[j] + rho * (simplex.back()[j] - centroid[j]);simplex_pairs.back().first[j]
               contraction[j] = centroid[j] + rho * (simplex_pairs.back().first[j] - centroid[j]);
            }

            clip(contraction, lowerBound, upperBound);
            double contractionValue = func(contraction, true);
            iteration++;
            iterations.push_back(iteration);
            objectiveValues.push_back(contractionValue);
            parameterTrajectory.push_back(contraction);
            saveData(iterations, objectiveValues, parameterTrajectory, "nelder_mead_output.txt");
            
            std::cout << "Iteration " << iteration << ": Contraction performed to point ";
            printVector(contraction, contractionValue);

            if (contractionValue < worstObjectiveValue) {
                //rho *= 1.01;
                double rho = adjustCoefficient(rho, bestObjectiveValue, tolerance, contractionValue < worstObjectiveValue);

                //simplex.back() = contraction; // Replace worst with contraction
                simplex_pairs.back().first = contraction;  
                simplex_pairs.back().second = contractionValue;
                updateSimplexAndCentroid(simplex_pairs, centroid);
                //updateSimplexAndCentroid(simplex, centroid, func);
                if (contractionValue <= tolerance) {
                    std::cout << "Optimal solution found during contraction.\n";
                    return contraction;
                }
            } else {
                
                //rho *= 1.0;
                double rho = adjustCoefficient(rho, bestObjectiveValue, tolerance, contractionValue < worstObjectiveValue);
                
                // Shrink towards best if contraction doesn't improve.Don't need to modify sigma
                for (size_t i = 1; i < simplex_pairs.size(); ++i) {
                    for (size_t j = 0; j < simplex_pairs[i].first.size(); ++j) {
                         simplex_pairs[i].first[j] = simplex_pairs[0].first[j] + sigma * (simplex_pairs[i].first[j] - simplex_pairs[0].first[j]);
                    }
                         clip(simplex_pairs[i].first, lowerBound, upperBound);
                         simplex_pairs[i].second = func(simplex_pairs[i].first, true);  // Recalculate the objective value after shrink

                         iteration++;
                         iterations.push_back(iteration);
                         objectiveValues.push_back(simplex_pairs[i].second);
                         parameterTrajectory.push_back(simplex_pairs[i].first);
                         saveData(iterations, objectiveValues, parameterTrajectory, "nelder_mead_output.txt");

                         std::cout << "Iteration " << iteration << ": Shrink performed to point ";
                         printVector(simplex_pairs[i].first, simplex_pairs[i].second);

                         // Optional: in rare case, shrinkValue < bestObjectiveValue
                         if (simplex_pairs[i].second < bestObjectiveValue) {
                             bestSolution = simplex_pairs[i].first;
                             bestObjectiveValue = simplex_pairs[i].second;
                         }

                         if (simplex_pairs[i].second <= tolerance) {
                             std::cout << "Optimal solution found during shrink.\n";
                             return simplex_pairs[i].first;
                         }


                        updateSimplexAndCentroid(simplex_pairs, centroid);
                    
                CheckReinstall(stallCounter, lastBestValue, bestObjectiveValue, simplex_pairs, bestSolution, 
                   lowerBound, upperBound, iterations, objectiveValues, parameterTrajectory, 
                   func, centroid, iteration);
                }
            }
            
        } else if (reflectionValue < worstObjectiveValue) { // Handle contraction towards reflection
        
        //alpha *= 0.98; // still decrease alpha
          double alpha = adjustCoefficient(alpha, bestObjectiveValue, tolerance, reflectionValue < bestObjectiveValue);
            
        std::vector<double> contraction(centroid.size());
        for (size_t j = 0; j < centroid.size(); ++j) {
            contraction[j] = centroid[j] + rho * (reflection[j] - centroid[j]);//correct!
        }
        clip(contraction, lowerBound, upperBound);
        double contractionValue = func(contraction, true);
        
        iteration++;
        iterations.push_back(iteration);
        objectiveValues.push_back(contractionValue);
        parameterTrajectory.push_back(contraction);
        saveData(iterations, objectiveValues, parameterTrajectory, "nelder_mead_output.txt");
            
        std::cout << "Iteration " << iteration << ": Contraction performed to point ";
        printVector(contraction, contractionValue);
        
          if (contractionValue < reflectionValue) {
 
                double rho = adjustCoefficient(rho, bestObjectiveValue, tolerance, contractionValue < worstObjectiveValue);
                
                //simplex.back() = contraction; // Replace worst with contraction
                //updateSimplexAndCentroid(simplex, centroid, func);
                simplex_pairs.back().first = contraction;  
                simplex_pairs.back().second = contractionValue;
                updateSimplexAndCentroid(simplex_pairs, centroid);
                
                if (contractionValue <= tolerance) {
                    std::cout << "Optimal solution found during contraction.\n";
                    return contraction;
                }
            } else {

                double rho = adjustCoefficient(rho, bestObjectiveValue, tolerance, contractionValue < worstObjectiveValue);
                
                // Shrink if contraction < reflection. Don't need to modify sigma
                for (size_t i = 1; i < simplex_pairs.size(); ++i) {
                    for (size_t j = 0; j < simplex_pairs[i].first.size(); ++j) {
                         simplex_pairs[i].first[j] = simplex_pairs[0].first[j] + sigma * (simplex_pairs[i].first[j] - simplex_pairs[0].first[j]);
                    }
                         clip(simplex_pairs[i].first, lowerBound, upperBound);
                         simplex_pairs[i].second = func(simplex_pairs[i].first, true);  // Recalculate the objective value after shrink

                         iteration++;
                         iterations.push_back(iteration);
                         objectiveValues.push_back(simplex_pairs[i].second);
                         parameterTrajectory.push_back(simplex_pairs[i].first);
                         saveData(iterations, objectiveValues, parameterTrajectory, "nelder_mead_output.txt");

                         std::cout << "Iteration " << iteration << ": Shrink performed to point ";
                         printVector(simplex_pairs[i].first, simplex_pairs[i].second);

                         // Optional: in rare case, shrinkValue < bestObjectiveValue
                         if (simplex_pairs[i].second < bestObjectiveValue) {
                             bestSolution = simplex_pairs[i].first;
                             bestObjectiveValue = simplex_pairs[i].second;
                         }

                         if (simplex_pairs[i].second <= tolerance) {
                             std::cout << "Optimal solution found during shrink.\n";
                             return simplex_pairs[i].first;
                         }


                        updateSimplexAndCentroid(simplex_pairs, centroid);
                        
        CheckReinstall(stallCounter, lastBestValue, bestObjectiveValue, simplex_pairs, bestSolution, 
                   lowerBound, upperBound, iterations, objectiveValues, parameterTrajectory, 
                   func, centroid, iteration);
                }
                //CheckReinstall(stallCounter, lastBestValue, bestObjectiveValue, simplex, bestSolution, lowerBound, upperBound, iterations, objectiveValues, parameterTrajectory, objectives, func, centroid, iteration);
            }
            
    } else if (bestObjectiveValue <= reflectionValue && reflectionValue < secondWorstObjectiveValue) {
        // Replace worst with reflection and recalculate centroid
        //simplex.back() = reflection;
        //updateSimplexAndCentroid(simplex, centroid, func);
          simplex_pairs.back().first = reflection;  
          simplex_pairs.back().second = reflectionValue;
          updateSimplexAndCentroid(simplex_pairs, centroid);
    }

        CheckReinstall(stallCounter, lastBestValue, bestObjectiveValue, simplex_pairs, bestSolution, 
                   lowerBound, upperBound, iterations, objectiveValues, parameterTrajectory, 
                   func, centroid, iteration);
 }

    std::cout << "Best Solution Found: ";
    printVector(bestSolution, bestObjectiveValue);

    return bestSolution;  // Return the best solution found
}

