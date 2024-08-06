
% execute izhikevich neuron function
clear 
close all
clc

Connection = input('Enter 1(excitatory) or 2(inhibitory)','s');
disp('For optimizae PSP,presynaptic neuron could be any type since they just provide spike input')

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
% parameter need to be tuned
tau_fast_init = 5;% initial value of tau_fast, only for tuning

tau_fast = 5;% AMPA decay time, ms，16.9
tau_slow = 150.0; % NMDA decay time, ms,43.2
Wt = 1.0; % synaptic weight, 0.214
fast_gain = 1.0;% synaptic specific gain factor
slow_gain = 1.0;% 0.2*fast_gain (CA1)
w_fast = Wt.*fast_gain;% actual synpatic weight should be Wt*gain
w_slow = Wt.*slow_gain;
I2 = amp2*t;
targeted_amp = -0.45;%mV
targeted_HHW = 31.6;%ms

%% presynaptic neuron
% pre_neuron =  CA1_Pyramidal;
C1 = 334; vr1 = -69.36; vt1 = -53.22; k1 = 1.56; vpeak1 = 25.46;
a1 = 0; b1 = -17.25; c1 = -60.22; d1 = 16;

% pre_neuron =  'DG Granule';
% C1 = 38; vr1 = -77.4; vt1 = -44.9; k1 = 0.45; vpeak1 = 15.49;
% a1 = 0.003; b1 = 24.48; c1 = -66.47; d1 = 50;

%% postsynaptic neuron
post_neuron = 'RS';
C2 = 100; vr2 = -60; vt2 = -40; k2 = 0.7; vpeak2 = 35;
a2 = 0.03; b2 = -2.0; c2 = -50; d2 = 100;

% DG Granule 
% C2 = 38; vr2 = -77.4; vt2 = -44.9; k2 = 0.45; vpeak2 = 15.49;
% a2 = 0.003; b2 = 24.48; c2 = -66.47; d2 = 50;
% vr2 = -57.8;% depolarized vr

% DG Basket 
% C2 = 208; vr2 = -61.02; vt2 = -37.84; k2 = 0.81; vpeak2 = 14.08;
% a2 = 0.097; b2 = 1.89; c2 = -36.23; d2 = 553;

% post_neuron = 'CA3_Pyramidal(type3,ASP)';
% C2 = 382; vr2 = -58.63; vt2 = -42.74; k2 = 0.98; vpeak2 = 38.55;
% a2 = 0.008; b2 = 12.49; c2 = -34.52; d2 = 138;
% 
% post_neuron = 'CA3_Pyramidal(type2,ASP.NASP)';
% k2=0.54;a2= 0.004;b2= 5.21;d2= 48;C2= 297;vr2= -60.53;
% vt2= -21.24;vpeak2= 38.02;c2= -36.52;

% post_neuron = 'CA3_Basket';
% C2 = 45; vr2 = -57.51; vt2 = -23.38; k2 = 1.0; vpeak2 = 18.45;
% a2 = 0.004; b2 = 9.26; c2 = -47.56; d2 = -6.0;

% post_neuron = 'CA3_AAC';% AAC
% k2=3.96;a2= 0.005;b2= 8.68;d2= 15;C2= 165;
% vr2= -57.1;vt2= -51.72;vpeak2= 27.8;c2= -73.97;

% post_neuron = 'CA3_HAAC';% Horizontal AAC
% k2=0.63;a2= 0.002;b2= -16.44;d2= 21;C2= 154;
% vr2= -58.52;vt2= -33.5;vpeak2= 36.09;c2= -38.5;

% post_neuron = 'CA3_BCCCK';
% k2=0.58;a2= 0.006;b2= -1.24;d2= 54;C2= 135;vr2= -59;
% vt2= -39.4;vpeak2= 18.27;c2= -42.77;
 
% post_neuron = 'CA3_Bistratified';% use CA1 BisC(subtype1) value
% k2=3.94;a2= 0.002;b2= 16.58;d2= 19;C2= 107;vr2= -64.67;vt2= -58.74;
% vpeak2= -9.93;c2= -59.7;

% post_neuron = 'CA3_OLM';
% k2=0.51;a2= 0.01;b2= 2.39;d2= 6;C2= 65;vr2= -60.04;vt2= -30.87;
% vpeak2= 19.77;c2= -52.81;

% post_neuron = 'CA3_TL';
% k2=0.93;a2= 0;b2= -18.76;d2= 74;C2= 251;vr2= -63.13;vt2= -55.64;
% vpeak2= 17.01;c2= -52.62;

% post_neuron = 'CA3_TL(modified)';
% k2=0.93;a2= 0.02;b2= 0.2;d2= 2;C2= 251;vr2= -63.13;vt2= -55.64;
% vpeak2= 17.01;c2= -52.62;

% post_neuron = 'CA3_TL(CA1 RTL)';
% k2=2.64;a2= 0.009;b2= 3.59;d2= 2;C2= 227;vr2= -57.87;
% vt2= -37.93;vpeak2= 4.77;c2= -45.87;

% post_neuron = 'CA3_MFA';
% k2=0.55;a2= 0.003;b2= 3.69;d2= 5;C2= 185;vr2= -59.41;vt2= -36.59;
% vpeak2= 9.99;c2= -43.55;

% CA1 Pyramidal type2 min>3Hz not working!
% k2 = 1.25;a2 = 0.001;b2 = -38.7;d2 = 43;C2 = 23;
% vr2 = -69.75;vt2 = -46.56;vpeak2 = 24.57;c2 = -54.88;

% CA1 Pyramidal type3
% k2 = 5.89;a2 = 0.081;b2 = -15.09;d2 = 483;C2 = 506;
% vr2 = -62.16;vt2 = -48.42;vpeak2 = 32.77;c2 = -52.21;

% CA1 Basket
% k2 = 1.19; a2 = 0.005; b2 = 0.22;d2 = 2;C2 = 114; vr2 = -57.63;
% vt2 = -35.53; vpeak2 = 21.72;c2 = -48.7;
% 
switch Connection
    case '1' % excitatory connection
        conn_type = 1;
        V_rev_fast = 0; % Excitatory reversal potential(AMPA), mV
        V_rev_slow = 0; % Excitatory reversal potential(NMDA), mV

    case '2' % inhibitory connection
        conn_type = 2;
        V_rev_fast = -70; %Inhibitory reversal potential(GABAa), mV
        V_rev_slow = -90; %Inhibitory reversal potential(GABAb), mV
end

%% Execute Presynaptic neuron
% Check presynaptic input
[v1,u1,spike_trains1,I1] = ...
izhikevich_presynaptic_neuron(Integrator,amp1,C1,vr1,vt1,k1,...
vpeak1,a1,b1,c1,d1,T,step,PulseWidth);

%% ExecutePostsynaptic neuron
% Use single spike as input
spike_amp = (1/step);
spike_trains1 = [zeros(1,(int32(TTP*n)-1)),spike_amp,...
    zeros(1,int32(n-(TTP)*n))];

[v2,u2,U,x,g_fast,g_slow,g_syn,I_fast,I_slow,I_syn,spike_trains2] = ...
izhikevich_postsynaptic_neuron(Integrator,conn_type,spike_trains1,...
STP_U,STP_tau_u,STP_tau_x,V_rev_fast,V_rev_slow,tau_fast,...
tau_slow,w_fast,w_slow,C2,vr2,vt2,k2,vpeak2,a2,b2,c2,d2,T,step,I2);

figure(11)
% v_CARL = xlsread('gain factor check','A3:ALL3');%user define, specify gain=1
v_CARL = xlsread('gain factor check','A4:ALL4');%user define, not specify gain
t_carl = 1:1000;
plot(t_carl,v_CARL,'r','LineWidth',2);
hold on
plot(t,v2,'b','LineWidth', 2);
%% include STDP
% [v2,u2,U,x,g_fast,g_slow,g_syn,I_fast,I_slow,I_syn,spike_trains2] = ...
% izhikevich_postsynaptic_neuron_STDP(Integrator,conn_type,spike_trains1,...
% STP_U,STP_tau_u,STP_tau_x,V_rev_fast,V_rev_slow,tau_fast,...
% tau_slow,w_fast,w_slow,C2,vr2,vt2,k2,vpeak2,a2,b2,c2,d2,T,step,I2);

%% HHW
%%% Find peak value and HHW
switch Connection
    case '1' % excitatory connection
        conn_type = 1;
        halfHeight = (vr2 + max(v2)) / 2; %find half high
        index1 = find(v2 >= halfHeight, 1, 'first');% find left edge
        index2 = find(v2 >= halfHeight, 1, 'last');% find right edge
        
    case '2' % inhibitory connection
        conn_type = 2;
        halfHeight = (vr2 + min(v2)) / 2; %find half high
        index1 = find(v2 <= halfHeight, 1, 'first');% find left edge
        index2 = find(v2 <= halfHeight, 1, 'last');% find right edge
end

t1 = t(index1);
t2 = t(index2);
HHW = t2 - t1;


targeted_V = vr2 + targeted_amp;
labelText_V = ['PSP=',num2str(targeted_amp),'mV,',...
    'V=',num2str(targeted_V),'mV'];
labelText_HHW = ['HHW=',num2str(targeted_HHW),'ms'];

%% CARLsim check
% v2_carl = xlsread('EPSP-DGGC-weight','A1:ALL1');% DG_Granule
% v2_carl = xlsread('EPSP-DGGC-weight','A2:ALL2');% DG_Basket
% 
% sz=6;
% t_carl = 1:1000;
% plot(t_carl,v2_carl,'r','LineWidth',2);
% % scatter(t_carl,v2_carl,sz,'r','filled');
% hold on
% plot(t,v2,'b','LineWidth',2);
% % scatter(t,v2,sz,'b','filled');
% hold off
% legend('CARLsim','MATLAB');

%% synaptic gain check
% v_gain = xlsread('gain factor check','A1:BXX1');% DG Basket
% v_Nogain = xlsread('gain factor check','A2:BXX2');% DG Basket
% t_carl = 1:1000;
% 
% figure(9)
% subplot(3,1,1)
% % Filter out the zeros
% non_zero_indices = spike_trains1 ~= 0;
% t_filtered = t(non_zero_indices);
% spike_trains1_filtered = spike_trains1(non_zero_indices);
% % Scatter plot
% scatter(t_filtered, spike_trains1_filtered, 30, 'k', 'filled');
% xlim([0,1000]);title('Spike input');
% ylabel('Spike input');%xlabel('Time(ms)');
% 
% subplot(3,1,2)
% scatter(t_carl,v_gain, 5, 'r', 'filled');
% hold on
% scatter(t_carl,v_Nogain, 5, 'b', 'filled');
% hold off
% title('Postsynaptic voltage');ylabel('V(mV)');xlabel('Time(ms)');
% legend('Set fast and slow gain = 1.0','No specify gain');

%% scale weight
% v2_all = [];
% initWt = 0.04*fast_gain;
% initWt_const = initWt;% store initWt value
% scale = 1.1;
% scale_time = 15; 
% for i = 1:scale_time
% [v2,u2,U,x,g_fast,g_slow,g_syn,I_fast,I_slow,I_syn,spike_trains2] = ...
% izhikevich_postsynaptic_neuron(Integrator,conn_type,spike_trains1,...
% STP_U,STP_tau_u,STP_tau_x,V_rev_fast,V_rev_slow,tau_fast,...
% tau_slow,initWt,w_slow,C2,vr2,vt2,k2,vpeak2,a2,b2,c2,d2,T,step,I2);
% v2_all(i,:) = v2;
% initWt = initWt * scale;
% end

% % plot weight curve
% weight_value = initWt_const;
% for i = 1:T:scale_time*T
%         weight(i:i+T-1) = weight_value;
%         weight_value = weight_value .* scale;
% end

% figure(9) weight curve
% figure(9)
% subplot(3,1,1)
% sz = 12;
% % Filter out the zeros
% non_zero_indices = spike_trains1 ~= 0;
% t_filtered = t(non_zero_indices);
% spike_trains1_filtered = spike_trains1(non_zero_indices);
% % Scatter plot
% scatter(t_filtered, spike_trains1_filtered, 50, 'k', 'filled');
% xlim([0,1000]);
% ylabel('Spike trains input');xlabel('Time(ms)');
% 
% subplot(3,1,2)
% plot(weight);
% % xlabel('Time(ms)');
% set(gca, 'XTick', []);
% ylabel('Synaptic weight');title('Weight');
% 
% subplot(3,1,3)
% for i=1:scale_time
% plot(t,v2_all(i,:),'b','LineWidth',1);
% hold on
% end
% hold on
% 
% line([0, T], [targeted_V, targeted_V], 'Color', 'r', 'LineWidth', 1); % Replace xmin and xmax with your desired x-axis limits
% line([0, T], [targeted_V, targeted_V], 'Color', 'red', 'LineWidth', 1); % Replace xmin and xmax with your desired x-axis limits
% line([t1, t1], [min(v2), max(v2)], 'Color', 'black', 'LineWidth', 1); % Vertical line at t1
% line([t2, t2], [min(v2), max(v2)], 'Color', 'black', 'LineWidth', 1); % Vertical line at t2
% line([0, T], [halfHeight, halfHeight], 'Color', 'red', 'LineStyle', '--', 'LineWidth', 1); % Dashed horizontal line at halfHeight
% 
% hold on
% text(300, targeted_V, labelText_V, 'HorizontalAlignment', 'right', ...
%      'VerticalAlignment', 'bottom', ...
%      'FontSize', 10, 'FontWeight', 'bold');
% text(300, halfHeight, labelText_HHW, 'HorizontalAlignment', 'right', ...
%      'VerticalAlignment', 'bottom', ...
%      'FontSize', 10, 'FontWeight', 'bold');%% text(600,halfHeight),halfHeight must match...
%  %line(600, halfHeight)

% hold off
% title('EPSP');
% xlabel('Time(ms)');
% % xlim([0,300]);
% ylabel('V(mV)');


%% scale tdAMPA
v2_all = [];
initTd = tau_fast_init;
initTd_const = initTd;% store initWt value
scale = 1.1;
scale_time = 15; 
for i = 1:scale_time
[v2,u2,U,x,g_fast,g_slow,g_syn,I_fast,I_slow,I_syn,spike_trains2] = ...
izhikevich_postsynaptic_neuron(Integrator,conn_type,spike_trains1,...
STP_U,STP_tau_u,STP_tau_x,V_rev_fast,V_rev_slow,initTd,...
tau_slow,w_fast,w_slow,C2,vr2,vt2,k2,vpeak2,a2,b2,c2,d2,T,step,I2);
v2_all(i,:) = v2;
g_fast_all(i,:) = g_fast;
g_slow_all(i,:) = g_slow;
I_fast_all(i,:) = I_fast;
I_slow_all(i,:) = I_slow;
initTd = initTd * scale;
end

% plot Td curve
timelist = 1:t;
Td_value = initTd_const;
for i = 1:T:scale_time*T
        Td(i:i+T-1) = Td_value;
        Td_value = Td_value .* scale;
end
%% figure(2) Td curev
figure(2)
subplot(4,1,1)
plot(Td,'k','LineWidth',2);
hold on
sz = 12;
scatter(2454, 10, 30, 'k', 'filled');% Scatter plot
% % Filter out the zeros
% non_zero_indices = spike_trains1 ~= 0;
% t_filtered = t(non_zero_indices);
% spike_trains1_filtered = spike_trains1(non_zero_indices);
% % spike_trains1_filtered = 15;
% t_filtered = 100;
% scatter(t_filtered, spike_trains1_filtered, 50, 'k', 'filled');% Scatter plot
% % ylabel('Spike trains input');xlabel('Time(ms)');
% hold off;
% xlim([0,1000]);
set(gca, 'XTick', []);
ylabel('tdAMPA(ms)');title('tdAMPA');


subplot(4,1,2)
for i=1:scale_time
plot(t,g_fast_all(i,:),'b','LineWidth',0.1);
hold on
plot(t,g_slow_all(i,:),'r','LineWidth',2);
hold on
end
hold off
title('Conductance');ylabel('g(nS)');legend('fast','slow');xlim([80,200]);

subplot(4,1,3)
for i=1:scale_time
plot(t,I_fast_all(i,:),'b','LineWidth',0.1);
hold on
plot(t,I_slow_all(i,:),'r','LineWidth',2);
hold on
end
hold off
title('EPSC');ylabel('I(pA)');legend('fast','slow');xlim([80,200]);

subplot(4,1,4)
for i=1:scale_time
plot(t,v2_all(i,:),'b','LineWidth',0.2);
hold on
end
hold on
title('EPSP');xlabel('Time(ms)');ylabel('V(mV)');xlim([80,350]);
line([0, T], [targeted_V, targeted_V], 'Color', 'r', 'LineWidth', 1); % Replace xmin and xmax with your desired x-axis limits
line([0, T], [targeted_V, targeted_V], 'Color', 'red', 'LineWidth', 1); % Replace xmin and xmax with your desired x-axis limits
line([t1, t1], [min(v2), max(v2)], 'Color', 'black', 'LineWidth', 1); % Vertical line at t1
line([t2, t2], [min(v2), max(v2)], 'Color', 'black', 'LineWidth', 1); % Vertical line at t2
line([0, T], [halfHeight, halfHeight], 'Color', 'red', 'LineStyle', '--', 'LineWidth', 1); % Dashed horizontal line at halfHeight

hold on
text(150, targeted_V, labelText_V, 'HorizontalAlignment', 'right', ...
     'VerticalAlignment', 'bottom', ...
     'FontSize', 10, 'FontWeight', 'bold');
text(200, halfHeight, labelText_HHW, 'HorizontalAlignment', 'right', ...
     'VerticalAlignment', 'bottom', ...
     'FontSize', 10, 'FontWeight', 'bold');%% text(600,halfHeight),halfHeight must match...
 %line(600, halfHeight)
hold off

%% figure(3) postsynaptic dynamics
% figure(3)
% subplot(4,1,1)
% scatter(100, 10, 30, 'k', 'filled');% Scatter plot
% % scatter(2454, 10, 30, 'k', 'filled');% Scatter plot
% xlim([90,210]);
% title('Single Spike Input');
% 
% subplot(4,1,2)
% Wt = 0.368; 
% w_fast = Wt.*fast_gain;
% w_slow = Wt.*slow_gain;
% [v2,u2,U,x,g_fast,g_slow,g_syn,I_fast,I_slow,I_syn,spike_trains2] = ...
% izhikevich_postsynaptic_neuron(Integrator,conn_type,spike_trains1,...
% STP_U,STP_tau_u,STP_tau_x,V_rev_fast,V_rev_slow,tau_fast,...
% tau_slow,w_fast,w_slow,C2,vr2,vt2,k2,vpeak2,a2,b2,c2,d2,T,step,I2);
% 
% scatter(t,g_syn,5,'b','filled');
% hold on
% 
% Wt = 1.0; 
% w_fast = Wt.*fast_gain;
% w_slow = Wt.*slow_gain;
% [v2,u2,U,x,g_fast,g_slow,g_syn,I_fast,I_slow,I_syn,spike_trains2] = ...
% izhikevich_postsynaptic_neuron(Integrator,conn_type,spike_trains1,...
% STP_U,STP_tau_u,STP_tau_x,V_rev_fast,V_rev_slow,tau_fast,...
% tau_slow,w_fast,w_slow,C2,vr2,vt2,k2,vpeak2,a2,b2,c2,d2,T,step,I2);
% 
% scatter(t,g_syn,5,'r','filled');
% hold off
% title('Conductance');xlabel('Time(ms)');ylabel('g(nS)');
% xlim([90,210]);% [low,high]
% legend('Wt=0.368','Wt=1');
% 
% subplot(4,1,3)
% Wt = 0.368; 
% w_fast = Wt.*fast_gain;
% w_slow = Wt.*slow_gain;
% [v2,u2,U,x,g_fast,g_slow,g_syn,I_fast,I_slow,I_syn,spike_trains2] = ...
% izhikevich_postsynaptic_neuron(Integrator,conn_type,spike_trains1,...
% STP_U,STP_tau_u,STP_tau_x,V_rev_fast,V_rev_slow,tau_fast,...
% tau_slow,w_fast,w_slow,C2,vr2,vt2,k2,vpeak2,a2,b2,c2,d2,T,step,I2);

% scatter(t,I_syn,5,'b','filled');
% hold on
% 
% Wt = 1.0; 
% w_fast = Wt.*fast_gain;
% w_slow = Wt.*slow_gain;
% [v2,u2,U,x,g_fast,g_slow,g_syn,I_fast,I_slow,I_syn,spike_trains2] = ...
% izhikevich_postsynaptic_neuron(Integrator,conn_type,spike_trains1,...
% STP_U,STP_tau_u,STP_tau_x,V_rev_fast,V_rev_slow,tau_fast,...
% tau_slow,w_fast,w_slow,C2,vr2,vt2,k2,vpeak2,a2,b2,c2,d2,T,step,I2);
% 
% scatter(t,I_syn,5,'r','filled');
% 
% title('Postsynaptic Current');ylabel('I(pA)');
% legend('Wt=0.368','Wt=1');
% xlim([90,210]);
% 
% subplot(4,1,4)
% 
% Wt = 0.368; 
% w_fast = Wt.*fast_gain;
% w_slow = Wt.*slow_gain;
% [v2,u2,U,x,g_fast,g_slow,g_syn,I_fast,I_slow,I_syn,spike_trains2] = ...
% izhikevich_postsynaptic_neuron(Integrator,conn_type,spike_trains1,...
% STP_U,STP_tau_u,STP_tau_x,V_rev_fast,V_rev_slow,tau_fast,...
% tau_slow,w_fast,w_slow,C2,vr2,vt2,k2,vpeak2,a2,b2,c2,d2,T,step,I2);
% 
% scatter(t,v2,5,'b','filled');
% hold on
% 
% Wt = 1.0; 
% w_fast = Wt.*fast_gain;
% w_slow = Wt.*slow_gain;
% [v2,u2,U,x,g_fast,g_slow,g_syn,I_fast,I_slow,I_syn,spike_trains2] = ...
% izhikevich_postsynaptic_neuron(Integrator,conn_type,spike_trains1,...
% STP_U,STP_tau_u,STP_tau_x,V_rev_fast,V_rev_slow,tau_fast,...
% tau_slow,w_fast,w_slow,C2,vr2,vt2,k2,vpeak2,a2,b2,c2,d2,T,step,I2);
% 
% scatter(t,v2,5,'r','filled');
% title('Postsynaptic Voltage');xlabel('Time(ms)');ylabel('V(mV)');
% legend('Wt=0.368','Wt=1');
% xlim([90,210]);


%% figure(4) check optimized PSP, HHW, g, PSC
fig4 = figure(4);% check optimized PSP, HHW, and corresponding g, PSC
subplot(5,1,1)
% Filter out the zeros
non_zero_indices = spike_trains1 ~= 0;
t_filtered = t(non_zero_indices);
spike_trains1_filtered = spike_trains1(non_zero_indices);
% Scatter plot
scatter(t_filtered, spike_trains1_filtered, 30, 'k', 'filled');
xlim([0,1000]);title('Spike input');
ylabel('Spike input');%xlabel('Time(ms)');

subplot(5,1,2)
plot(t,g_fast,'b','LineWidth',1.5);hold on
plot(t,g_slow,'r','LineWidth',1.5);hold off
title('Conductance(nS)');

ylabel('g(nS)');%xlabel('Time(ms)');
switch Connection
    case '1' % excitatory connection
        conn_type = 1;
        legend('AMPA','NMDA');
    case '2' % inhibitory connection    
        conn_type = 2;
        legend('GABAa','GABAb');
end

subplot(5,1,3)
plot(t,I_fast,'b','LineWidth',1.5);hold on
plot(t,I_slow,'r','LineWidth',1.5);
title('Posynaptic current(pA)');
ylabel('I(pA)');%xlabel('Time(ms)');
switch Connection
    case '1' % excitatory connection
        conn_type = 1;
        legend('AMPA','NMDA');
    case '2' % inhibitory connection    
        conn_type = 2;
        legend('GABAa','GABAb');
end

subplot(5,1,[4,5])
plot(t,v2,'b','LineWidth', 2);
hold on
line([0, T], [targeted_V, targeted_V], 'Color', 'red', 'LineWidth', 1); % Replace xmin and xmax with your desired x-axis limits
text(400, targeted_V, labelText_V, 'HorizontalAlignment', 'right', ...
     'VerticalAlignment', 'bottom', ...
     'FontSize', 10, 'FontWeight', 'bold');
 
hold on
line([t1, t1], [min(v2), max(v2)], 'Color', 'black', 'LineWidth', 1); % Vertical line at t1
line([t2, t2], [min(v2), max(v2)], 'Color', 'black', 'LineWidth', 1); % Vertical line at t2
line([0, T], [halfHeight, halfHeight], 'Color', 'red', 'LineStyle', '--', 'LineWidth', 1); % Dashed horizontal line at halfHeight

text(300, targeted_HHW, labelText_HHW, 'HorizontalAlignment', 'right', ...
     'VerticalAlignment', 'bottom', ...
     'FontSize', 10, 'FontWeight', 'bold');

hold off
title('Postsynaptic potential(mV)');
ylabel('V(mV)');xlabel('Time(ms)');
% xlim([0,300]);

%% TMM proposal - EPSP and firing rate
% numSegments=16;
% load('pdf_values.mat');
% load('x_values.mat');
% 
% % downsample
% % N = length(t) / 1; % This should be 100 for your case
% % t_downsampled = t(1:N:end); % This selects every 100th element from t
% % v2_all_downsampled = v2_all(:,1:N:end);
% % plot(t_downsampled,v2_all_downsampled(5,:),'b');hold on; 
% % plot(t_downsampled,v2_all_downsampled(10,:),'b');hold on;
% % plot(t_downsampled,v2_all_downsampled(15,:),'k');hold off;
% % xlim([80,250]);axis off; hold on;
% 
% fig10 = figure(10);
% set(fig10, 'Units', 'normalized', 'Position', [0.1, 0.1, 0.8, 0.6]); % Adjust the figure size
% 
% subplot(2,2,[1,3])
% for i=1:scale_time
%     if i == 15
%         plot(t,v2_all(i,:),'k','LineWidth',3.5);
%     else
%         plot(t,v2_all(i,:),'b','LineWidth',2);
% hold on
%     end
% end
% hold on
% title('EPSP','FontSize',16);
% xlabel('Time(ms)','FontSize',14);
% ylabel('V(mV)','FontSize',14);xlim([80,250]);
% line([0, T], [targeted_V, targeted_V], 'Color', 'r', 'LineWidth', 1); % Replace xmin and xmax with your desired x-axis limits
% line([0, T], [targeted_V, targeted_V], 'Color', 'red', 'LineWidth', 1); % Replace xmin and xmax with your desired x-axis limits
% line([t1, t1], [min(v2), max(v2)], 'Color', 'black', 'LineWidth', 1); % Vertical line at t1
% line([t2, t2], [min(v2), max(v2)], 'Color', 'black', 'LineWidth', 1); % Vertical line at t2
% line([0, T], [halfHeight, halfHeight], 'Color', 'red', 'LineStyle', '--', 'LineWidth', 1); % Dashed horizontal line at halfHeight
% 
% hold on
% text(180, targeted_V, labelText_V, 'HorizontalAlignment', 'right', ...
%      'VerticalAlignment', 'bottom', ...
%      'FontSize', 10, 'FontWeight', 'bold');
% text(190, halfHeight, labelText_HHW, 'HorizontalAlignment', 'right', ...
%      'VerticalAlignment', 'bottom', ...
%      'FontSize', 10, 'FontWeight', 'bold');%% text(600,halfHeight),halfHeight must match...
%  %line(600, halfHeight)
% hold off
% 
% subplot(2,2,[2,4])
% hold on;
% colors = lines(numSegments); % Assuming numSegments is defined
% % for segment = 8:numSegments
% for segment = 8:12
%     x_values = x_values_segments{segment};
%     pdf_values = pdf_values_segments{segment};
%     if ~isempty(pdf_values)
%         % Normalize the PDF values by their integral to make the area under each curve sum to one
%         area_under_curve = trapz(x_values, pdf_values);
%         normalized_pdf_values = pdf_values / area_under_curve;
%         
%         % Adjust plotting to use normalized PDF values
%         if segment == 10
%             plot(x_values, normalized_pdf_values,'k');%, 'LineWidth', 3.5, 'Color', 'k');
%         else
%             plot(x_values, normalized_pdf_values);%, 'LineWidth', 2); % Colors can be adjusted as needed
%         end
%     end
% end
% xlabel('Firing Rate (Hz)','FontSize',14); xlim([0.19,7]);
% ylabel('Density','FontSize',14);
% title('Gamma Distribution of Firing Rates','FontSize',16);
% hold off;
% 
% % Adjust the figure and save as a high-resolution PNG
% set(fig10, 'Units', 'pixels');
% screenSize = get(0, 'ScreenSize'); % Get the screen size
% figHeight = screenSize(4) * 0.6; % Make the figure height 60% of the screen height
% set(fig10, 'Position', [0 0 screenSize(3) figHeight]); % Adjust figure size
% % print('KDE and EPSP optimization DEMO','-dpng','-r400'); % Save the figure as png
% % print(fig10, 'fig10', '-depsc');% Save the figure as eps

%% print the PSP and HHW    
switch Connection
    case '1' % excitatory connection
        conn_type = 1;
        peak_amp = max(v2) - vr2; % peak amplitude
        
    case '2' % inhibitory connection
        conn_type = 2;
        peak_amp = min(v2) - vr2; % peak amplitude
end

disp(post_neuron)
disp(['HHW = ', num2str(HHW), 'ms']);
disp(['PSP = ', num2str(peak_amp), 'mV']);  

disp(['targeted HHW = ', num2str(targeted_HHW), 'ms']);
disp(['targeted PSP = ', num2str(targeted_amp), 'mV']);  
    
%% Only for DG Basket, find 10% - 90% rise time
% tolerance = 0.001; % for example, 0.01 units
% target_10 = V_rest + targeted_amp * 0.1;
% target_90 = V_rest + targeted_amp * 0.9;
% 
% % Find the index where v2 is closest to target_10 within the tolerance
% [~, t_10] = min(abs(v2 - target_10));
% if abs(v2(t_10) - target_10) > tolerance
%     warning('No value within tolerance for 10% target');
% end
% % 
% % % Find the index where v2 is closest to target_90 within the tolerance
% indices_within_time_range = find(t < 112);
% v2_within_time_range = v2(indices_within_time_range);
% 
% [min_difference1, index_within_range1] = min(abs(v2_within_time_range - target_10));
% [min_difference2, index_within_range2] = min(abs(v2_within_time_range - target_90));
% 
% if min_difference1 > tolerance
%     warning('No value within tolerance for 10%% target before t=112.5');
% else
%     % Get the actual index in the full vector 'v2' and the corresponding time
%     t_10_index = indices_within_time_range(index_within_range1);
%     t_10 = t(t_10_index);
% end
% 
% if min_difference2 > tolerance
%     warning('No value within tolerance for 90%% target before t=112.5');
% else
%     % Get the actual index in the full vector 'v2' and the corresponding time
%     t_90_index = indices_within_time_range(index_within_range2);
%     t_90 = t(t_90_index);
% end
% 
% t_rise = t_90 - t_10 % rise time from 10% - 90% amp, ms


%% Measure Rin and τm
% % Parameters
% T = 2000; % simulation duration
% step = 0.1; % time step
% PulseWidth = 0.9; % duration of the current pulse
% 
% % Small current step
% I_step = 10; % pA
% 
% % Simulate neuron with I_step
% [v,u,~,~] = izhikevich_presynaptic_neuron(2, I_step,C1,vr1,vt1,k1,...
%  vpeak1,a1,b1,c1,d1,T,step,PulseWidth); % use the rest of your parameters
% 
% % Calculate delta V: the difference between steady state voltage and baseline voltage
% baseline_voltage = mean(v(1:round((1-PulseWidth)*0.8*T/step))); % average voltage before stimulus
% steady_state_voltage = mean(v(round(T*0.9/step):end)); % average voltage towards the end of the simulation
% delta_V = steady_state_voltage - baseline_voltage;
% 
% % Calculate Rin
% Rin = (delta_V / I_step)*10000; % MΩ
% 
% % Determine tau_m
% time_to_reach_632 = find(v >= baseline_voltage + 0.632*delta_V, 1) * step - (1-PulseWidth)*T;
% 
% disp(['Input resistance, Rin: ', num2str(Rin), ' MΩ']);
% disp(['Membrane time constant, tau_m: ', num2str(time_to_reach_632), ' ms']);

%% figure(1) pre and post
% % figure(1)
% % % sgtitle('CA3-Pyramidal,Excitsgtitle('RS,Excitatory (COBA+STP)'); 
% % %sgtitle('CA3-MFA-ORDEN,Excitatory (COBA+STP)'); 
% % %sgtitle('CA3-Ivy,Excitatory (COBA+STP)'); 
% % %sgtitle('RS,Excitatory (COBA+STP) - Euler method');
% % 
subplot(6,1,1)
plot(t,I1,'r','LineWidth',2);
title('Input current on CA3 Bistratified(0.2nA)'); 
xlabel('Time(ms)');
%xlim([low,high]);
ylabel('I(pA)');

subplot(6,1,2)
plot(t,v1,'b','LineWidth',2);
title('output voltage on CA3 Bistratified');
xlabel('Time(ms)');
%xlim([low,high]);
ylabel('V(mV)');

subplot(6,1,3)
plot(t,g_syn,'b','LineWidth',2);
title('Conductance');
xlabel('Time(ms)');
%xlim([low,high]);
ylabel('g(nS)');
% 
subplot(6,1,4)
plot(t,U,'k','LineWidth',2);
hold on
plot(t,x,'g','LineWidth',2);
hold off
title('Synapse STP');
xlabel('Time(ms)');
%xlim([low,high]);
ylabel('a.u');
legend('u','x');
% 
subplot(6,1,5)
plot(t,I_syn,'b','LineWidth',2);
title('Synaptic current on postsynaptic neuron');
xlabel('Time(ms)');
%xlim([low,high]);
ylabel('I(pA)');

subplot(6,1,6)
plot(t,v2,'b','LineWidth',2);
title('postsynaptic voltage');
xlabel('Time(ms)');
%xlim([low,high]);
ylabel('V(mV)');






