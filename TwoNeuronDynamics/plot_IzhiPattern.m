clear;
close all;
clc;
%% Generate Izhi pattern plot that best match with literature
% Actual simulation parameters will be modified 
%% Define postsynaptic neuron parameters in a struct array for easy iteration
% last three:  Wt, tau_fast, tau_slow
% C Vr Vt k Vpeak a b c d



neuron_types = {
    'PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,  455, 337, 'ASP'; % type3
    'BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,    397, 874.857','ASP.SLN';
    'AAC', 165, -57.1, -51.72, 3.96, 27.8, 0.005, 8.68, -73.97, 15,     632,620,'ASP'; 
    'BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,    407,860,'ASP.NASP';
    'BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,  408,475.746,'PSTUT';
    'OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,      292,624,'ASP';
    'TL', 227, -57.87, -37.93, 2.64, 4.77, 0.009, 3.59, -45.87, 2,      395,297.75,'NASP'; % CA1 RTL
    'MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,     402, 1080.25,'ASP.NASP';    
};

% Parameters common to all neurons
Integrator = 2; % RK method
T = 1200; %1000ms
step = 0.1; % ms (0.2ms - iterate 5 times; 0.1ms - iterate 10 times)
n = round(T/step); % simulation time steps
PulseStart = 100; % Pulse start time in ms
%PulseEnd = 600; % Pulse end time in ms, must < T
TTP = PulseStart/1000; %time to peak (sec)
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
    PulseEnd = neuron_types{i, 12};
%     taw_fast = neuron_types{i, 13};
%     taw_slow = neuron_types{i, 14};
    pattern_name = neuron_types{i, 13};
    
    current = vr1*ones(1,n); 
    PulseStartIndex = round(PulseStart/step) + 1; % Index for pulse start
    PulseEndIndex = round(PulseEnd/step); % Index for pulse end
    current(PulseStartIndex:PulseEndIndex) = amp1;
    
    [v1,u1,spike_trains1,I1] = ...
izhikevich_presynaptic_neuron(Integrator,amp1,C1,vr1,vt1,k1,...
vpeak1,a1,b1,c1,d1,T,step,PulseStart,PulseEnd);
    
    plot_color = 'k';  % Black color
    line_width = 1.2;    % Standard line
   
    plot(t, v1, plot_color, 'LineWidth', line_width);title('Voltage(mV)');
    hold on
    check = current/10;   
    plot(t,check);
%     xlim([80, 400]);
%     ylim([min(I_syn)-3.5, max(I_syn)+3.5]);
    title([neuron_types{i, 1}]);
    if i == 8
        xlabel('Time(ms)');
    else
        set(gca, 'XTick', [], 'YTick', []); 
    end
    legend(pattern_name);
%     set(gca, 'XTickLabel', [], 'YTickLabel', []); % Removes labels on x and y axis
%     set(gca, 'XTick', [], 'YTick', []);           % Removes tick marks on x and y axis
      set(gca, 'YTick', []);   
end

fast_gain = 1;
slow_gain = 0.62;

% Create bar plot legend
% legend_ax = axes('Position', [0.2, 0.7, 0.1, 0.1]); % Adjust position and size as needed
% hold(legend_ax, 'on');
% % Plot the first half (fast_gain) in red in the legend
% rectangle('Position', [0, 0.7, 1, 0.2], 'FaceColor', 'r', 'EdgeColor', 'none', 'Parent', legend_ax);
% % Plot the second half (slow_gain) in blue in the legend
% rectangle('Position', [1, 0.7, 0.62, 0.2], 'FaceColor', 'b', 'EdgeColor', 'none', 'Parent', legend_ax);
% % Remove axes from the legend
% set(legend_ax, 'XColor', 'none', 'YColor', 'none', 'XTick', [], 'YTick', []);
% % Set limits for the inset axes
% xlim(legend_ax, [0 1.62]);
% ylim(legend_ax, [0 1]);
% 
% % Add text to the custom legend
% text(legend_ax, 0.8, 0.5, 'Custom Legend', 'HorizontalAlignment', 'center');
% hold(legend_ax, 'off');
% % Make sure the original plot is visible
% hold off;
%