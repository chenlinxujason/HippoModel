clear;
close all;
clc;


%% Define postsynaptic neuron parameters in a struct array for easy iteration
% last three:  Wt, tau_fast, tau_slow
% C Vr Vt k Vpeak a b c d

Connection_types = {
    'PC-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,   0.482, 26.0, 43.2, 1.0, 0.43;
    'PC-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,     1.343, 37.4, 43.2, 1.0, 0.27;
    'PC-AAC', 165, -57.1, -51.72, 3.96, 27.8, 0.005, 8.68, -73.97, 15,      1.143, 13.5, 43.2, 1.0, 0.26;
    'PC-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,     0.227, 4.6, 18.8, 1.0, 0.5;
     'PC-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,   1.085, 1.87, 3.4, 1.0, 0.3;
    'PC-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,       0.577, 2.0, 43.2, 1.0, 0.37;
    
    'BC-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,   1.61, 10.8, 15.9, 1.0, 0.15;
    'BC-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,     0.0, 9.0, 43.2, 1.0, 0.15;
    'BC-AAC', 165, -57.1, -51.72, 3.96, 27.8, 0.005, 8.68, -73.97, 15,      3.288, 3.2, 6.3, 1.0, 0.15;
    'BC-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,     0.0, 1.2, 2.5, 1.0, 0.15;
    'BC-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,   0.0, 1.35, 2.9, 1.0, 0.15;
    'BC-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,       0.0, 2.0, 13.2, 1.0, 0.15;
    
    'AAC-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,  1.61, 10.8, 15.9, 1.0, 0.15;
    'AAC-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,    2.787, 9.0, 43.2, 1.0, 0.15;
    'AAC-AAC', 165, -57.1, -51.72, 3.96, 27.8, 0.005, 8.68, -73.97, 15,     0.0, 3.2, 6.3, 1.0, 0.15;
    'AAC-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,    0.0, 1.2, 2.5, 1.0, 0.15;
    'AAC-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,  0.0, 1.35, 2.9, 1.0, 0.15;
    'AAC-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,      0.0, 2.0, 13.2, 1.0, 0.15;
    
    'BCCCK-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138, 1.61, 10.8, 15.9, 1.0, 0.15;
    'BCCCK-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,   2.787, 9.0, 43.2, 1.0, 0.15;
    'BCCCK-AAC', 165, -57.1, -51.72, 3.96, 27.8, 0.005, 8.68, -73.97, 15,    3.288, 3.2, 6.3, 1.0, 0.15;
    'BCCCK-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,   0.0, 1.2, 2.5, 1.0, 0.15;
    'BCCCK-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19, 0.0, 1.35, 2.9, 1.0, 0.15;
    'BCCCK-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,     0.0, 2.0, 13.2, 1.0, 0.15;
    
    'BisC-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,  1.61, 10.8, 15.9, 1.0, 0.15;
    'BisC-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,    2.787, 9.0, 43.2, 1.0, 0.15;
    'BisC-AAC', 165, -57.1, -51.72, 3.96, 27.8, 0.005, 8.68, -73.97, 15,     3.288, 3.2, 6.3, 1.0, 0.15;
    'BisC-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,    2.5, 1.2, 2.5, 1.0, 0.15;
    'BisC-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,  5.01, 1.35, 2.9, 1.0, 0.15;
    'BisC-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,      1.963, 2.0, 13.2, 1.0, 0.15;
    
    'OLM-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,   1.61, 10.8, 15.9, 1.0, 0.15;
    'OLM-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,     2.787, 9.0, 43.2, 1.0, 0.15;
    'OLM-AAC', 165, -57.1, -51.72, 3.96, 27.8, 0.005, 8.68, -73.97, 15,      3.288, 3.2, 6.3, 1.0, 0.15;
    'OLM-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,     2.5, 1.2, 2.5, 1.0, 0.15;
    'OLM-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,   5.01, 1.35, 2.9, 1.0, 0.15;
    'OLM-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,       1.963, 2.0, 13.2, 1.0, 0.15;
    % Repeat for other connections ensuring each row has exactly 13 elements
};


% Parameters common to all neurons
amp1 = 440; %external current at presynaptic neuron, pA
amp2 = 0; %external current at postsynaptic neuron, pA
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
I2 = amp2*t;
% fast_gain = 1.0;
% slow_gain = 1.0;
%
%% Use presynaptic spike as postsynaptic input
% pre_neuron =  CA1_Pyramidal;
% C1 = 334; vr1 = -69.36; vt1 = -53.22; k1 = 1.56; vpeak1 = 25.46;
% a1 = 0; b1 = -17.25; c1 = -60.22; d1 = 16;
% 
% [v1,u1,spike_trains1,I1] = ...
% izhikevich_presynaptic_neuron(Integrator,amp1,C1,vr1,vt1,k1,...
% vpeak1,a1,b1,c1,d1,T,step,PulseWidth);

%% Use single spike as postsynaptic input
% spike_amp = (1/step)+0.45; % spike modify 
% spike_trains1 = [zeros(1,(int32(TTP*n)-1)),spike_amp,...
%     zeros(1,int32(n-(TTP)*n))];

num_connections = size(Connection_types, 1);

% Prepare the figure
figure;
% set(gcf, 'Position', [100, 100, 1400, 800]); % Adjust size as needed

% Loop over all subplots
for i = 1:num_connections
    % Determine the subplot index
    subplot_index = i; % Each subplot corresponds to a different connection type
    
    % Subplot placement assuming 6 rows and as many columns as needed up to 6
    subplot(6, min(6, num_connections), subplot_index);
    C2 = Connection_types{i, 2};
    vr2 = Connection_types{i, 3};
    vt2 = Connection_types{i, 4};
    k2 = Connection_types{i, 5};
    vpeak2 = Connection_types{i, 6};
    a2 = Connection_types{i, 7};
    b2 = Connection_types{i, 8};
    c2 = Connection_types{i, 9};
    d2 = Connection_types{i, 10};
    Wt = Connection_types{i, 11};
    tau_fast = Connection_types{i, 12};
    tau_slow = Connection_types{i, 13};
    fast_gain = Connection_types{i, 14};
    slow_gain = Connection_types{i, 15};
    
    
    % Set connection-specific parameters
     % Set connection-specific parameters based on the connection type
    connection_name = Connection_types{i, 1};
    if any(strcmp(connection_name, {'PC-PC', 'PC-BC', 'PC-AAC', 'PC-BCCCK', 'PC-BisC', 'PC-OLM'}))
        conn_type = 1; % Excitatory
        V_rev_fast = 0;
        V_rev_slow = 0;
    else
        conn_type = 2; % Inhibitory
        V_rev_fast = -70;
        V_rev_slow = -90;
    end
    
    % Execute the neuron model (assuming izhikevich_postsynaptic_neuron function is defined)
    spike_amp = (1/step)+0.39; % spike modify 

    spike_trains1 = [zeros(1,(int32(TTP*n)-1)),spike_amp,...
    zeros(1,int32(n-(TTP)*n))];

    w_fast = Wt*fast_gain;
    w_slow = Wt*slow_gain;
% 
   [v2,u2,U,x,g_fast,g_slow,g_syn,I_fast,I_slow,I_syn,spike_trains2] = ...
izhikevich_postsynaptic_neuron(Integrator,conn_type,spike_trains1,...
STP_U,STP_tau_u,STP_tau_x,V_rev_fast,V_rev_slow,tau_fast,...
tau_slow,w_fast,w_slow,C2,vr2,vt2,k2,vpeak2,a2,b2,c2,d2,T,step,I2);

    % Plotting
    % Conditional plotting based on synaptic weight
    if Wt == 0
        plot_color = 'r';  % Red color
        line_width = 3.5;    % Thicker line
    else
        plot_color = 'b';  % Black color
        line_width = 1.4;    % Standard line
    end
    
    plot(t, v2, plot_color, 'LineWidth', line_width);title('Voltage(mV)');xlim([80, 280]);ylim([min(v2)-0.5, max(v2)+0.5]);
%     plot(t, g_syn, plot_color, 'LineWidth', line_width);xlim([80, 400]);ylim([min(g_syn)-0.5, max(g_syn)+0.5]);hold on;
%     plot(t, g_fast, 'r', 'LineWidth',1.0);xlim([80, 400]);ylim([min(g_syn)-0.5, max(g_syn)+0.5]);hold on;
%     plot(t, g_slow, 'b', 'LineWidth',1.0);xlim([80, 400]);ylim([min(g_syn)-0.5, max(g_syn)+0.5]);hold on;

%     plot(t, I_syn, plot_color, 'LineWidth', line_width);title('Current(pA)');xlim([80, 400]);ylim([min(I_syn)-3.5, max(I_syn)+3.5]);
    title([Connection_types{i, 1}]);
%     xlabel('Time (ms)');
    set(gca, 'XTickLabel', [], 'YTickLabel', []); % Removes labels on x and y axis
    set(gca, 'XTick', [], 'YTick', []);           % Removes tick marks on x and y axis
    clear v2 
end