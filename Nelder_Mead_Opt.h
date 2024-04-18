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

// Helper function to print vector
void printVector(const std::vector<double>& vec, double value) {
    for (const auto& v : vec) {
        std::cout << v << " ";
    }
    std::cout << " with Objective: " << value << std::endl;
}

// Sorts simplex based on the objective function values
void sortSimplex(std::vector<std::vector<double>>& simplex, const std::function<double(const std::vector<double>&, bool)>& func) {
    std::sort(simplex.begin(), simplex.end(),
         [&](const std::vector<double>& a, const std::vector<double>& b) {
             return func(a, false) < func(b, false);
         });
}

// Nelder-Mead algorithm implementation
std::vector<double> nelderMead(const std::function<double(const std::vector<double>&, bool)>& func,
                               std::vector<std::vector<double>> simplex,
                               double tolerance, // Default tolerance adjusted for example
                               int maxIterations) {  // Maximum iterations
    const double alpha = 1.4;  // Reflection coefficient
    const double gamma = 2.0;  // Expansion coefficient
    const double rho = 0.5;    // Contraction coefficient
    const double sigma = 0.5;  // Shrinkage coefficient

    std::vector<double> bestSolution = simplex[0];
    double bestObjectiveValue = func(bestSolution, false);
    std::cout << "Initial Best Objective Value: " << bestObjectiveValue << std::endl;

    bool foundOptimal = false;
    int iteration = 0;
    while (iteration < maxIterations && !foundOptimal) {
        // Custom sort the simplex and check for early termination
        for (size_t i = 0; i < simplex.size(); ++i) {
            double objI = func(simplex[i], false);
            if (objI < tolerance) {
                bestSolution = simplex[i];
                bestObjectiveValue = objI;
                foundOptimal = true;
                std::cout << "Optimal solution found during sorting.\n";
                break;
            }

            for (size_t j = i + 1; j < simplex.size(); ++j) {
                double objJ = func(simplex[j], false);
                if (objJ < tolerance) {
                    bestSolution = simplex[j];
                    bestObjectiveValue = objJ;
                    foundOptimal = true;
                    std::cout << "Optimal solution found during sorting.\n";
                    break;
                }
                if (objI > objJ) {
                    std::swap(simplex[i], simplex[j]);
                }
            }
            iteration++;
            if (foundOptimal) break;
            std::cout << "Iteration " << iteration << ": Sorting vertex " << i + 1 << std::endl;
        }
        if (foundOptimal) break;

        // Proceed with other operations only if optimal hasn't been found during sorting
        if (!foundOptimal) {
            std::vector<double> centroid(simplex[0].size(), 0.0);
            for (size_t i = 0; i < simplex.size() - 1; ++i) {
                for (size_t j = 0; j < simplex[i].size(); ++j) {
                    centroid[j] += simplex[i][j];
                }
            }
            for (size_t j = 0; j < centroid.size(); ++j) {
                centroid[j] /= (simplex.size() - 1);
            }

            std::vector<double> reflection(centroid.size());
            for (size_t j = 0; j < centroid.size(); ++j) {
                reflection[j] = centroid[j] + alpha * (centroid[j] - simplex.back()[j]);
            }
            
            double reflectionValue = func(reflection, true);
            iteration++;
            std::cout << "Iteration " << iteration << ": Reflection performed to point ";
            printVector(reflection, reflectionValue);

            if (reflectionValue < tolerance) {
                bestSolution = reflection;
                bestObjectiveValue = reflectionValue;
                std::cout << "Optimal solution found during reflection.\n";
                break;
            }

            if (reflectionValue < bestObjectiveValue) {
                simplex.back() = reflection;
                bestObjectiveValue = reflectionValue;
                bestSolution = reflection;
                continue;
            }

            // Expansion
            std::vector<double> expansion(centroid.size());
            for (size_t j = 0; j < centroid.size(); ++j) {
                expansion[j] = centroid[j] + gamma * (reflection[j] - centroid[j]);
            }
            double expansionValue = func(expansion, true);
            iteration++;
            std::cout << "Iteration " << iteration << ": Expansion performed to point ";
            printVector(expansion, expansionValue);

            if (expansionValue < tolerance) {
                bestSolution = expansion;
                bestObjectiveValue = expansionValue;
                std::cout << "Optimal solution found during expansion.\n";
                break;
            }

            if (expansionValue < reflectionValue) {
                simplex.back() = expansion;
                bestObjectiveValue = expansionValue;
                bestSolution = expansion;
                continue;
            }

            // Contraction
            std::vector<double> contraction(centroid.size());
            for (size_t j = 0; j < centroid.size(); ++j) {
                contraction[j] = centroid[j] + rho * (simplex.back()[j] - centroid[j]);
            }
            double contractionValue = func(contraction, true);
            iteration++;
            std::cout << "Iteration " << iteration << ": Contraction performed to point ";
            printVector(contraction, contractionValue);

            if (contractionValue < tolerance) {
                bestSolution = contraction;
                bestObjectiveValue = contractionValue;
                std::cout << "Optimal solution found during contraction.\n";
                break;
            }

            if (contractionValue < bestObjectiveValue) {
                simplex.back() = contraction;
                bestObjectiveValue = contractionValue;
                bestSolution = contraction;
                continue;
            }

            // Shrink
            for (size_t i = 1; i < simplex.size(); ++i) {
                for (size_t j = 0; j < simplex[i].size(); ++j) {
                    simplex[i][j] = simplex[0][j] + sigma * (simplex[i][j] - simplex[0][j]);
                }
                double shrinkValue = func(simplex[i], true);
                iteration++;
                std::cout << "Iteration " << iteration << ": Shrink performed to point ";
                printVector(simplex[i], shrinkValue);

                if (shrinkValue < tolerance) {
                    bestSolution = simplex[i];
                    bestObjectiveValue = shrinkValue;
                    std::cout << "Optimal solution found during shrink.\n";
                    foundOptimal = true;
                    break;
                }
            }
            if (foundOptimal) break;
        }
    }

    std::cout << "Best Solution Found: ";
    printVector(bestSolution, bestObjectiveValue);

    return bestSolution;  // Return the best solution found
}

// Multi-start version of the Nelder-Mead algorithm
//std::vector<double> multiStartNelderMead(const std::function<double(const std::vector<double>&)>& func,
 //                                        int numStarts, int dimension,
//                                         double tolerance = 1e-2, int maxIterations = 20) {
//    double bestObjectiveValue = std::numeric_limits<double>::infinity();
//    std::vector<double> bestSolution(dimension);

    // Seed the random number generator for reproducibility
//    std::srand(static_cast<unsigned int>(std::time(nullptr)));
//
//    for (int start = 0; start < numStarts; ++start) {
        // Initialize a random simplex for the current start
//        std::vector<std::vector<double>> simplex;
 //       for (int i = 0; i <= dimension; ++i) {
//            std::vector<double> point(dimension);
 //           for (int j = 0; j < dimension; ++j) {
                // Generate points within a specified range, adjust as necessary
 //               point[j] = (double)std::rand() / RAND_MAX * 5.0; // Example: 0 to 5 range
 //           }
 //           simplex.push_back(point);
 //       }

//        std::vector<double> solution = nelderMead(func, simplex, tolerance, maxIterations);
//        double objectiveValue = func(solution,true);

//        if (objectiveValue < bestObjectiveValue) {
//            bestObjectiveValue = objectiveValue;
 //           bestSolution = solution;
//        }
//    }

 //   return bestSolution;
//}
