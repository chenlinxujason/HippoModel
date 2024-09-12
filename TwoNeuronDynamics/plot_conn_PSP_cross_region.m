clear;
close all;
clc;

neuron_names = {'MEC','LEC','DGGC','CA3PC','CA3BC'};
input_names = {'MEC','LEC','DGGC'};
CA3neuron_names = {'CA3PC','CA3BC'};

%% CA3 Local - Initial
% Connection_types = {
%     'MEC-CA3PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,   0.47, 36.2, 47.0, 1.0, 0.97;
%     'MEC-CA3BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,     1.3, 37.3, 89.4, 1.0, 0.769;
%     'LEC-CA3PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,   0.47, 36.2, 47.0, 1.0, 0.97;
%     'LEC-CA3BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,     1.3, 37.3, 89.4, 1.0, 0.769;
%     'DGGC-CA3PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,  1.496, 36.2, 47.0, 1.0, 0.97;
%     'DGGC-CA3BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,    1.567, 33.4, 89.4, 1.0, 0.769;
%     };


%% CA3 Local - Fine tune
Connection_types = {
    'MEC-CA3PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,   0.74, 36.2, 47.0, 1.0, 0.97;
    'MEC-CA3BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,     0.95, 37.3, 89.4, 1.0, 0.769;
    'LEC-CA3PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,   0.74, 36.2, 47.0, 1.0, 0.97;
    'LEC-CA3BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,     0.95, 37.3, 89.4, 1.0, 0.769;
    'DGGC-CA3PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,  2.0, 36.2, 47.0, 1.0, 0.97;
    'DGGC-CA3BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,    1.22, 33.4, 89.4, 1.0, 0.769;
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

% Prepare the figure
figure;
num_connections = size(Connection_types, 1);
num_neurons = length(neuron_names); % Get number of neuron names

% Loop over all subplots
for i = 1:num_connections
    % Determine the subplot index
    subplot_index = i; % Each subplot corresponds to a different connection type
    
    % Subplot placement assuming 8 rows and as many columns as needed up to 6
    ax = subplot(3, 2, subplot_index);  % Capture the axis handle for later use
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
    connection_name = Connection_types{i, 1};
    conn_type = 1; % Excitatory
    V_rev_fast = 0;
    V_rev_slow = 0;
    
    % Execute the neuron model (assuming izhikevich_postsynaptic_neuron function is defined)
    spike_amp = (1/step)+0.39; % spike modify 
    spike_trains1 = [zeros(1,(int32(TTP*n)-1)),spike_amp, zeros(1,int32(n-(TTP)*n))];

    w_fast = Wt*fast_gain;
    w_slow = Wt*slow_gain;

    [v2,u2,U,x,g_fast,g_slow,g_syn,I_fast,I_slow,I_syn,spike_trains2] = ...
    izhikevich_postsynaptic_neuron(Integrator,conn_type,spike_trains1,...
    STP_U,STP_tau_u,STP_tau_x,V_rev_fast,V_rev_slow,tau_fast,...
    tau_slow,w_fast,w_slow,C2,vr2,vt2,k2,vpeak2,a2,b2,c2,d2,T,step,I2);

    % Plotting
    plot_color = 'r';  % Red color for excitatory
    line_width = 1.4;    % Standard line
    
    plot(t, v2, plot_color, 'LineWidth', line_width); 
    xlim([80, 280]); 
    %ylim([vr2-1.0, vr2+5.3]);% initial
    ylim([vr2-1.8, vr2+11.0]);% fine tune
    %ylim([min(v2)-0.6, max(v2)+0.6]);% fine tune

    % Set ylabel for the first column and make it bold
    if mod(subplot_index - 1, 2) == 0
        ylabel(neuron_names{ceil(subplot_index / 2)}, 'FontWeight', 'bold');
    end

    % Set the title for the first row and make it bold
    if subplot_index <= 2
        title(CA3neuron_names{subplot_index}, 'FontWeight', 'bold');
    end

    set(gca, 'XTick', [], 'YTick', []);  % Removes tick marks on x and y axis
    set(gca, 'XTickLabel', []);  % Removes labels on x and y axis

    % Add the bar plot for each subplot as a custom "legend"
    % Get the position of the current subplot
    pos = get(ax, 'Position');

    % Define the size of the custom bar plot legend
    legend_width = pos(3) * 0.4;  % Make the legend width 40% of subplot width
    legend_height = pos(4) * 0.2; % 20% of subplot height
    
    % Define the lower-left corner position for the custom legend
    legend_x = pos(1) + pos(3) * 0.55;  % Position it slightly to the right
    legend_y = pos(2) + pos(4) * 0.7;   % Position it near the top
    
     % Standardize the total length of the bar (use the total of fast_gain + slow_gain)
    total_gain = fast_gain + slow_gain;
    fast_proportion = fast_gain / total_gain;  % Proportion of fast_gain
    slow_proportion = slow_gain / total_gain;  % Proportion of slow_gain
    
    % Add the red and blue rectangles for the bar plot with standardized length
   annotation('rectangle', [legend_x, legend_y, legend_width * fast_proportion, legend_height], 'FaceColor', [0.8,0.8,0.8], 'EdgeColor', 'none');% grey fast
   annotation('rectangle', [legend_x + legend_width * fast_proportion, legend_y, legend_width * slow_proportion, legend_height], 'FaceColor', 'k', 'EdgeColor', 'none');% black slow
    
    clear v2
end