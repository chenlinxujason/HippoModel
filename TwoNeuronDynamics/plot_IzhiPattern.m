clear;
close all;
clc;
%% Define postsynaptic neuron parameters in a struct array for easy iteration
% last three:  Wt, tau_fast, tau_slow
% C Vr Vt k Vpeak a b c d
neuron_types = {
%     'PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,  455,'ASP'; % type3
    'PC', 297, -60.53, -21.24, 0.54, 38.02, 0.004, 5.21, -36.52, 48,    455,'ASP'; % type2
    'BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,    397,'ASP.SLN';
    %'HAAC', 154, -58.52, -33.5, 0.63, 36.09, 0.002, -16.44, -38.5, 21,   632,'ASP'; 
    'AAC', 165, -57.1, -51.72, 3.96, 27.8, 0.005, 8.68, -73.97, 15,     632,'ASP'; 
    'BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,    407,'ASP.NASP';
    'BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,  309,'PSTUT';
    'OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,      292,'ASP';
    'TL', 227, -57.87, -37.93, 2.64, 4.77, 0.009, 3.59, -45.87, 2,      576,'NASP'; % CA1 RTL
    'MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,     409,'ASP.NASP';    
};

% Parameters common to all neurons
Integrator = 2; % RK method
T = 1000; %1000ms
step = 0.1; % ms (0.2ms - iterate 5 times; 0.1ms - iterate 10 times)
n = round(T/step); % simulation time steps
PulseWidth = 0.9;
TTP = 0.1; %time to peak (sec) 0.1: TTP = 100ms; 0.0332: TTP = 33.2ms;0.011 - 11ms
t = step*(1:n);%correct!
STP_U = 0.45; % 0.45(STD,only Pyramidal) or 0.15(STF)
STP_tau_u = 50; % 50ms(STD,only Pyramidal) or 750ms(STF),tau_f,facilitation time constant
STP_tau_x = 750;  %750 ms(STD,only Pyramidal) or 50ms(STF),tau_d,depression time constant

num_neurontypes = size(neuron_types, 1);

figure;
% set(gcf, 'Position', [100, 100, 1400, 800]); % Adjust size as needed

% Loop over all subplots
for i = 1:num_neurontypes
    % Determine the subplot index
    subplot_index = i; % Each subplot corresponds to a different connection type
    
    % Subplot placement assuming 6 rows and as many columns as needed up to 6
    subplot(num_neurontypes, 1, subplot_index);
    C1 = neuron_types{i, 2};
    vr1 = neuron_types{i, 3};
    vt1 = neuron_types{i, 4};
    k1 = neuron_types{i, 5};
    vpeak1 = neuron_types{i, 6};
    a1 = neuron_types{i, 7};
    b1 = neuron_types{i, 8};
    c1 = neuron_types{i, 9};
    d1 = neuron_types{i, 10};
    amp1 = neuron_types{i, 11};
    pattern_name = neuron_types{i, 12};
    
    [v1,u1,spike_trains1,I1] = ...
    izhikevich_presynaptic_neuron(Integrator,amp1,C1,vr1,vt1,k1,...
    vpeak1,a1,b1,c1,d1,T,step,PulseWidth);
    
    plot_color = 'k';  % Black color
    line_width = 1.2;    % Standard line
   
    plot(t, v1, plot_color, 'LineWidth', line_width);title('Current(pA)');
%     xlim([80, 400]);
%     ylim([min(I_syn)-3.5, max(I_syn)+3.5]);
    title([neuron_types{i, 1}]);
    legend(pattern_name);
    set(gca, 'XTickLabel', [], 'YTickLabel', []); % Removes labels on x and y axis
    set(gca, 'XTick', [], 'YTick', []);           % Removes tick marks on x and y axis
end