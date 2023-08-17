clear
clc
close
initial_guess = [5, 150]; % [tau_fast, tau_slow]
lb = [0, 0];
ub = [50, 200];  % Adjust the upper bounds if needed

Connection = '1'; % As an example, it was hardcoded in the function
V_rev_fast = 0; % Assuming excitatory connection based on 'Connection = 1'
V_rev_slow = 0;

optimized_params = fmincon(@(tau_params) objectiveFunction(tau_params), initial_guess, [], [], [], [], lb, ub);

%% Initial is already optimized?
optimized_tau_fast = optimized_params(1);
optimized_tau_slow = optimized_params(2);
