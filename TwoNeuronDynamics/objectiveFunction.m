function error = objectiveFunction(tau_params)
    epsp_width = calculateEPSPwidth(tau_params);
    HHW_real = 33.5;
    error = abs(epsp_width - HHW_real);
end