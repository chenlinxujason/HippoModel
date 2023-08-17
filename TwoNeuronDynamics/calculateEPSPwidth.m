function epsp_width = calculateEPSPwidth(tau_params)
    tau_fast = tau_params(1);
    tau_slow = tau_params(2);

    Connection = '1';
   amp1 = 800; %external current at presynaptic neuron, pA
amp2 = 0; %external current at postsynaptic neuron, pA
Integrator = 2; % RK method
T = 1000; %1000ms
step = 0.1; %0.2ms, itergate 5 times per 1 ms
n = round(T/step); % simulation time steps
PulseWidth = 0.9;
t = step*(1:n);%correct!
STP_U = 0.45; % 0.45(STD,only Pyramidal) or 0.15(STF)
STP_tau_u = 50; % 50ms(STD,only Pyramidal) or 750ms(STF),tau_f,facilitation time constant
STP_tau_x = 750;  %750 ms(STD,only Pyramidal) or 50ms(STF),tau_d,depression time constant
% tau_fast = 5; % AMPA decay time, ms
% tau_slow = 150; % NMDA decay time, ms
w = 1.0; % synaptic weight (or relatively weight of AMPA - CARLsim Synaptic weight)

%%%%%%%%%%%%%%%%%%%%%%% presynaptic neuron
C1 = 38; vr1 = -77.4; vt1 = -44.9; k1 = 0.45; vpeak1 = 15.49;
a1 = 0.003; b1 = 24.48; c1 = -66.47; d1 = 50;

%%%%%%%%%%%%%%%%%%%%%%% postsynaptic neuron
% RS 
C2 = 100; vr2 = -60; vt2 = -40; k2 = 0.7; vpeak2 = 35;
a2 = 0.03; b2 = -2.0; c2 = -50; d2 = 100;


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

[v1,u1,spike_trains1,I1] = ...
izhikevich_presynaptic_neuron(Integrator,amp1,C1,vr1,vt1,k1,...
vpeak1,a1,b1,c1,d1,T,step,PulseWidth);

[v2,u2,U,x,g_fast,g_slow,g_syn,I_fast,I_slow,I_syn,spike_trains2,I2] = ...
izhikevich_postsynaptic_neuron(Integrator,conn_type,spike_trains1,...
STP_U,STP_tau_u,STP_tau_x,V_rev_fast,V_rev_slow,tau_fast,...
tau_slow,w,amp2,C2,vr2,vt2,k2,vpeak2,a2,b2,c2,d2,T,step,PulseWidth);
    
    % Calculate epsp_width
    y = v2(510:620); 
    halfHeight = (min(y) + max(y)) / 2;
    index1 = find(y >= halfHeight, 1, 'first');
    index2 = find(y >= halfHeight, 1, 'last');
    epsp_width = t(index2) - t(index1);
end