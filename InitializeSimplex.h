// Initialize the simplex with your starting guesses for the parameters
    std::vector<std::vector<double>> initialSimplex = {
    {1.0, 1.0, 1.0, 1.0, 1.0, 1.0}, // First vertex - always all 1, to match with baseline
    {3.47, 3.16, 3.7581, 3.7581, 3.509, 3.509}, // Second vertex - maximal weight
    {0.414282, 0.389909, 0.597221, 0.597221, 0.564092, 0.564092}, // Third vertex,objective=5.4
    {0.351969, 0.333514, 0.615213, 0.615213, 0.57989, 0.57989}, // Fourth vertex
    {2.47, 2.16, 2.758, 2.758, 2.509, 2.509}, // Fifth vertex - half of baseline + maximal
    {0.418356, 0.396952, 0.610215, 0.610215, 0.592565, 0.592565}, // Sixth vertex, objective=6.9
    {0.355799,0.341967,0.536795,0.536795,0.529019,0.529019}//Seventh vertex
};

//0.355799 0.341967 0.536795 0.536795 0.529019 0.529019  with Objective(Total error): 85.5634
//mean firing rate of DGGC = 0.719717; mean firing rate of DGBC = 11.4966

