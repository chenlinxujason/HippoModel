
% execute izhikevich neuron function
clear 
close all
clc

amp1 = 154; %external current at presynaptic neuron, pA
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
tau_fast = 5; % AMPA decay time, ms
tau_slow = 150; % NMDA decay time, ms
w = 1.0; % synaptic weight (or relatively weight of AMPA)

%%%%%%%%%%%%%%%%%%%%%%% presynaptic neuron
C1 = 334; vr1 = -69.36; vt1 = -53.22; k1 = 1.56; vpeak1 = 25.46;
a1 = 0; b1 = -17.25; c1 = -60.22; d1 = 16;%CA1_Pyramidal

% RS 
%C1 = 100; vr1 = -60; vt1 = -40; k1 = 0.7; vpeak1 = 35;
%a1 = 0.03; b1 = -2.0; c1 = -50; d1 = 100;

% DG Granule
%C1 = 38; vr1 = -77.4; vt1 = -44.9; k1 = 0.45; vpeak1 = 15.49;
%a1 = 0.003; b1 = 24.48; c1 = -66.47; d1 = 50;

% CA3_Pyramidal 
%C1 = 366; vr1 = -63.2044008171655; vt1 = -33.6041733124267; k1 = 0.792338703789581; vpeak1 = 35.8614648558726;
%a1 = 0.00838350334098279; b1 = -42.5524776883928; c1 = -38.8680990294091; d1 = 588;

% CA3_MFA_ORDEN
%C1 = 209; vr1 = -57.076423571379; vt1 = -39.1020427841762; k1 = 1.37980713457205; vpeak1 = 16.3132681887705;
%a1 = 0.00783805979364104; b1 = 12.9332855397722; c1 = -40.6806648852695; d1 = 0;

% CA3_Ivy 
%C1 = 364; vr1 = -70.4345135750261; vt1 = -40.8589263758355; k1 = 1.91603822942046; vpeak1 = -6.91973671560226;
%a1 = 0.009151158130158; b1 = 1.90833702318966; c1 = -53.3998503336009; d1 = 45.0;

%%%%%%%%%%%%%%%%%%%%%%% postsynaptic neuron

% RS 
C2 = 100; vr2 = -60; vt2 = -40; k2 = 0.7; vpeak2 = 35;
a2 = 0.03; b2 = -2.0; c2 = -50; d2 = 100;

% DG Granule 
%C2 = 38; vr2 = -77.4; vt2 = -44.9; k2 = 0.45; vpeak2 = 15.49;
%a2 = 0.003; b2 = 24.48; c2 = -66.47; d2 = 50;

% CA3_Pyramidal 
%C2 = 366; vr2 = -63.2044008171655; vt2 = -33.6041733124267; k2 = 0.792338703789581; vpeak2 = 35.8614648558726;
%a2 = 0.00838350334098279; b2 = -42.5524776883928; c2 = -38.8680990294091; d2 = 588;

% CA3_MFA_ORDEN
%C2 = 209; vr2 = -57.076423571379; vt2 = -39.1020427841762; k2 = 1.37980713457205; vpeak2 = 16.3132681887705;
%a2 = 0.00783805979364104; b2 = 12.9332855397722; c2 = -40.6806648852695; d2 = 0;

% CA3_Ivy neuron
%C2 = 364; vr2 = -70.4345135750261; vt2 = -40.8589263758355; k2 = 1.91603822942046; vpeak2 = -6.91973671560226;
%a2 = 0.009151158130158; b2 = 1.90833702318966; c2 = -53.3998503336009; d2 = 45.0;

conn_type = 1; % excitatory
V_rev_fast = 0; % Excitatory reversal potential(AMPA), mV
V_rev_slow = 0; % Excitatory reversal potential(NMDA), mV

%conn_type = 2; % inhibitory
%V_rev_fast = -70; %Inhibitory reversal potential(GABAa), mV
%V_rev_slow = -90; %Inhibitory reversal potential(GABAb), mV

[v1,u1,spike_trains1,I1] = ...
izhikevich_presynaptic_neuron(Integrator,amp1,C1,vr1,vt1,k1,...
vpeak1,a1,b1,c1,d1,T,step,PulseWidth);

[v2,u2,U,x,g_fast,g_slow,g_syn,I_fast,I_slow,I_syn,spike_trains2,I2] = ...
izhikevich_postsynaptic_neuron(Integrator,conn_type,spike_trains1,...
STP_U,STP_tau_u,STP_tau_x,V_rev_fast,V_rev_slow,tau_fast,...
tau_slow,w,amp2,C2,vr2,vt2,k2,vpeak2,a2,b2,c2,d2,T,step,PulseWidth);

figure(1)% 
sgtitle('RS,Excitatory (COBA+STP)'); 
%sgtitle('CA3-Pyramidal,Excitatory (COBA+STP)'); 
%sgtitle('CA3-MFA-ORDEN,Excitatory (COBA+STP)'); 
%sgtitle('CA3-Ivy,Excitatory (COBA+STP)'); 
%sgtitle('RS,Excitatory (COBA+STP) - Euler method');

subplot(6,1,1)
plot(t,I1,'r','LineWidth',2);
title('Input current on neuron 1(2200pA,dur=1ms)'); 
xlabel('Time(ms)');
%xlim([low,high]);
ylabel('I(pA)');

subplot(6,1,2)
plot(t,v1,'b','LineWidth',2);
title('output voltage on neuron 1');
xlabel('Time(ms)');
%xlim([low,high]);
ylabel('V(mV)');

subplot(6,1,3)
plot(t,g_syn,'b','LineWidth',2);
title('Conductance');
xlabel('Time(ms)');
%xlim([low,high]);
ylabel('g(nS)');

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


figure(2) % EPSP
plot(t,v2,'b','LineWidth',2);
title('EPSP(MATLAB),iter=5');
xlabel('Time(ms)');
%xlim([510,620]);
ylabel('V(mV)');


figure(3) % synaptic current of post-synaptic neuron
sgtitle('synaptic current')
subplot(3,1,1)
plot(t,I_fast,'r','LineWidth',2);
title('AMPA current');
xlabel('Time(ms)');
%xlim([low,high]);
ylabel('I(pA)');

subplot(3,1,2)
plot(t,I_slow,'b','LineWidth',2);
title('NMDA current');
xlabel('Time(ms)');
%xlim([low,high]);
ylabel('I(pA)');

subplot(3,1,3)
plot(t,I_syn,'k','LineWidth',2);
title('synaptic current');
xlabel('Time(ms)');
%xlim([low,high]);
ylabel('I(pA)');

figure(4)% conductance
plot(t,g_syn,'.');
title('Conductance scatter plot');
xlabel('Time(ms)');
%xlim([low,high]);
ylabel('g(nS)');

figure(5)
subplot(2,1,1)
plot(t,I1,'r','LineWidth',2);
title('Input current on neuron 1(0.01pA,dur=1ms)'); 
xlabel('Time(ms)');
%xlim([low,high]);
ylabel('I(pA)');

subplot(2,1,2)
plot(t,v1,'b','LineWidth',2);
title('output voltage on CA3 Pyramidal neuron');
xlabel('Time(ms)');
%xlim([low,high]);
ylabel('V(mV)');




