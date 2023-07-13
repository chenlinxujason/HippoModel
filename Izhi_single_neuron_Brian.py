# -*- coding: utf-8 -*-
"""
Created on Wed Jul 27 20:52:41 2022

@author: Chenlin Xu (Jason)
"""

from brian2 import *
from brian2 import SpikeGeneratorGroup
import numpy as np
from numpy import savetxt
from matplotlib import pyplot as plt  
#reversal potential, time constant (tau), synaptic conductance(w) can determine
#excitatory or inhibitory synapse


#num_e = 1 # number of excitatory neuron
#num_i = 1 # number of inhibitory neuron
num = 1

duration = 1000*ms  # Total simulation time
sim_dt = 0.1*ms  # integration time (step size), 0.2ms ~ iterate 5 times; 0.1ms ~ 10 times

# Set the integration time 
defaultclock.dt = sim_dt

### Neuron parameters
STP_U = 0.15; # 0.45(STD) or 0.15(STF)
STP_tau_u = 750*ms; # 50ms(STD) or 750ms(STF),tau_f,facilitation time constant
STP_tau_x = 50*ms; #750 ms(STD) or 50ms(STF),tau_d,depression time constant
tau_AMPA = 5*ms; # fast synaptic decay time(AMPA), ms
tau_NMDA = 150*ms; # slow synaptic decay time(NMDA), ms
tau_GABAa = 5*ms; # fast synaptic decay time(GABAa), ms
tau_GABAb = 150*ms; # slow synaptic decay time(GABAb), ms
A = 1/STP_U; # synaptic weight A, inverse of STP_U(1/0.45=2.22)
w = 1.0; # synaptic weight 
V_rev_E = 0*mV; # Excitatory reversal potentia, mV
V_rev_I_GABAa = -70*mV; #Inhibitory reversal potential, mV -70,correct!
V_rev_I_GABAb = -90*mV; #Inhibitory reversal potential, mV -90,correct!
amp_pulse = 2200*pA
amp_long = 451*pA


############################### Input neuron ##############################
### RS neuron ###
#C1 = 100; vr1 = -60; vt1 = -40; k1 = 0.7; vpeak1 = 35;
#a1 = 0.03; b1 = -2.0; c1 = -50; d1 = 100;

### CA3 Pyramidal neuron ###
#C1 = 366; vr1 = -63.2044008171655; vt1 = -33.6041733124267; k1 = 0.792338703789581; vpeak1 = 35.8614648558726;
#a1 = 0.00838350334098279; b1 = -42.5524776883928; c1 = -38.8680990294091; d1 = 588;


### CA3 BCCCK ###
#C1 = 135; vr1 = -58.99667734; vt1 = -39.39832097; k1 = 0.583005186; vpeak1 = 18.27458854;
#a1 = 0.00574483; b1 = -1.244845715; c1 = -42.7711851; d1 = 54.0;

### CA3 MFA ORDEN ##
#C1 = 209; vr1 = -57.076423571379; vt1 = -39.1020427841762; k1 = 1.37980713457205; vpeak1 = 16.3132681887705;
#a1 = 0.00783805979364104; b1 = 12.9332855397722; c1 = -40.6806648852695; d1 = 0;

### CA1_H_AA
#C1 = 88; k1 = 2.15; vr1 = -56.45; vt1 = -41.32;
#a1 = 0.03; b1 = -47.85;vpeak1 = 23.89;c1 = -46.01; d1 = 277;

### CA1_BP
#C1 = 133; k1 = 0.67; vr1 = -60.28; vt1 = -47.12;
#a1 = 0.004; b1 = 15.66; vpeak1 = 0.59; c1 = -60.14; d1 = -30;

### CA1_Basket_CCK
#C1 = 59; k1 = 1.06; vr1 = -63.18; vt1 = -38.18;
#a1 = 0.023; b1 = -26.87; vpeak1 = 27.44; c1 = -53.32; d1 = 294;

### CA1_HB
#C1 = 46; k1 = 0.83; vr1 = -55.72; vt1 = -27.75;
#a1 = 0.002; b1 = 0.26; vpeak1 = 20.28; c1 = -45.42; d1 = 1;

### CA1_Bist
#C1 = 107; k1 = 3.94; vr1 = -64.67; vt1 = -58.74;
#a1 = 0.002; b1 = 16.58; vpeak1 = -9.93; c1 = -59.7; d1 = 19;

### CA1_Neurogliaform
#C1 = 254; k1 = 2.36; vr1 = -63.33; vt1 = -47.62;
#a1 = 0.009; b1 = 17.56; vpeak1 = 10.7; c1 = -50.78; d1 = 40;

### CA1_O_LM
#C1 = 73; k1 = 4.47; vr1 = -60; vt1 = -56.41;
#a1 = 0.069; b1 = 74.3; vpeak1 = 7.99; c1 = -58.16; d1 = 299;

### CA1_OR_LM
#C1 = 248; k1 = 0.56; vr1 = -57.03; vt1 = -42.75;
#a1 = 0.014; b1 = 2.09; vpeak1 = 82.73; c1 = -45.49; d1 = -15;

### CA1_OA
C1 = 49; k1 = 1.21; vr1 = -51.65; vt1 = -41.92;
a1 = 0.056; b1 = -44.92; vpeak1 = -5.45; c1 = -46.01; d1 = 416;

### CA1_PPA
#C1 = 12; k1 = 4.84; vr1 = -55.44; vt1 = -42.5;
#a1 = 0.045; b1 = -49.31; vpeak1 = -0.05; c1 = -51; d1 = 194;

### CA1_PPAQ
#C1 = 12; k1 = 4.66; vr1 = -64.88; vt1 = -51.84;
#a1 = 0.096; b1 = -44.34; vpeak1 = -2.99; c1 = -62.54; d1 = 290;

### CA1_R-Receiving Apical-Target RRAT
#C1 = 92; k1 = 0.67; vr1 = -57.28; vt1 = -43.19;
#a1 = 0.027; b1 = -9.29; vpeak1 = -6.34; c1 = -46.58; d1 = 142; 

### CA1_T
#C1 = 38; k1 = 0.16; vr1 = -60.94; vt1 = -46.19;
#a1 = 0.004; b1 = 2.72; vpeak1 = -0.92; c1 = -55.34; d1 = -3;

### CA1_RT
#C1 = 227; k1 = 2.64; vr1 = -57.87; vt1 = -37.93;
#a1 = 0.009; b1 = 3.59; vpeak1 = 4.77; c1 = -45.87; d1 = 2;


############################### Output neuron ##############################
### RS neuron ###
#C2 = 100; vr2 = -60; vt2 = -40; k2 = 0.7; vpeak2 = 35;
#a2 = 0.03; b2 = -2.0; c2 = -50; d2 = 100;

### CA3 Pyramidal neuron ###
#C2 = 366; vr2 = -63.2044008171655; vt2 = -33.6041733124267; k2 = 0.792338703789581; vpeak2 = 35.8614648558726;
#a2 = 0.00838350334098279; b2 = -42.5524776883928; c2 = -38.8680990294091; d2 = 588;

### CA3 BCCCK ###
#C2 = 135; vr2 = -58.99667734; vt2 = -39.39832097; k2 = 0.583005186; vpeak2 = 18.27458854;
#a2 = 0.00574483; b2 = -1.244845715; c2 = -42.7711851; d2 = 54.0;

#C2 = 135; vr2 = -59; vt2 = -39.4; k2 = 0.58; vpeak2 = 18.27;
#a2 = 0.006; b2 = -1.24; c2 = -42.77; d2 = 54;

### CA3 MFA ORDEN ##
C2 = 209; vr2 = -57.076423571379; vt2 = -39.1020427841762; k2 = 1.37980713457205; vpeak2 = 16.3132681887705;
a2 = 0.00783805979364104; b2 = 12.9332855397722; c2 = -40.6806648852695; d2 = 0;

#C2 = 209; vr2 = -57.08; vt2 = -39.1; k2 = 1.38; vpeak2 = 16.31;
#a2 = 0.008; b2 = 12.93; c2 = -40.68; d2 = 0;



eqs_in = '''
dv1/dt = ((k1*(v1-vr1)*(v1-vt1)-u+I/pA)/C1)/ms: 1
du/dt = (a1*(b1*(v1-vr1)-u))/ms: 1
I : amp
'''

eqs_out_Exc = '''

dv2/dt = ((k2*(v2-vr2)*(v2-vt2)-u+I/pA-(g_AMPA*(v2-V_rev_E/mV)+g_NMDA*(v2-V_rev_E/mV)*(((v2+80)/60)**2/(1+((v2+80)/60)**2))))/C2)/ms: 1
du/dt = (a2*(b2*(v2-vr2)-u))/ms: 1
dg_AMPA/dt = (-g_AMPA/tau_AMPA):1
dg_NMDA/dt = (-g_NMDA/tau_NMDA):1
dg_exc/dt = ((-g_AMPA/tau_AMPA) + (-g_NMDA/tau_NMDA)):1
dI2/dt = -((-g_AMPA/tau_AMPA)*(v2-V_rev_E/mV)+(-g_NMDA/tau_NMDA)*(v2-V_rev_E/mV)*(((v2+80)/60)**2/(1+((v2+80)/60)**2))):1

I : amp
'''

eqs_out_Inh = '''

dv3/dt = ((k2*(v3-vr2)*(v3-vt2)-u+I/pA-(g_GABAa*(v3-V_rev_I_GABAa/mV)+g_GABAb*(v3-V_rev_I_GABAb/mV)))/C2)/ms: 1
du/dt = (a2*(b2*(v3-vr2)-u))/ms: 1
dg_GABAa/dt = (-g_GABAa/tau_GABAa):1
dg_GABAb/dt = (-g_GABAb/tau_GABAb):1
dg_inh/dt = ((-g_GABAa/tau_GABAa) + (-g_GABAb/tau_GABAb)):1
dI3/dt = -((-g_GABAa/tau_GABAa)*(v3-V_rev_I_GABAa/mV)+(-g_GABAb/tau_GABAb)*(v3-V_rev_I_GABAb/mV)):1

I : amp
'''


# STP 
synapses_eqs = '''
dU/dt = -U/STP_tau_u     : 1 (clock-driven)
dx/dt = (1-x)/STP_tau_x  : 1 (clock-driven)
'''
synapse_action = '''
U += STP_U*(1 - U)
r_S = U*x
x -= r_S
'''

conductance_action_Exc = '''
g_AMPA += w*A*r_S 
g_NMDA += w*A*r_S
g_exc = g_AMPA + g_NMDA
I2 = -(g_AMPA*(v2-V_rev_E/mV)+g_NMDA*(v2-V_rev_E/mV)*(((v2+80)/60)**2/(1+((v2+80)/60)**2)))
'''

conductance_action_Inh = '''
g_GABAa += w*A*r_S 
g_GABAb += w*A*r_S
g_inh = g_GABAa + g_GABAb
I3 = -(g_GABAa*(v3-V_rev_I_GABAa/mV)+g_GABAb*(v3-V_rev_I_GABAb/mV))
'''

indices = array([0,0,0,0])
times = array([100,300,500,700])*ms
G = SpikeGeneratorGroup(1, indices, times) # spike generator

G1 = NeuronGroup(num, eqs_in, clock=Clock(defaultclock.dt),
                   threshold='v1>vpeak1', 
                   reset=''' 
                   v1 = c1
                   u = u+d1 ''',
                   method='rk4') # input neuron
G1.v1 = vr1;

G2 = NeuronGroup(num, eqs_out_Exc, clock=Clock(defaultclock.dt),
                   threshold='v2>vpeak2', 
                   reset=''' 
                   v2 = c2
                   u = u+d2 ''',
                   method='rk4') # output neuron with excitatory synapse
G2.v2 = vr2;

G3 = NeuronGroup(num, eqs_out_Inh, clock=Clock(defaultclock.dt),
                   threshold='v3>vpeak2', 
                   reset=''' 
                   v3 = c2
                   u = u+d2 ''',
                   method='rk4') # output neuron with inhibitory synase
G3.v3 = vr2;




# input neuron - excitatory synapse - output neuron
#exc_syn = Synapses(G1, G2, clock=Clock(defaultclock.dt), 
#                   model = synapses_eqs,
#                   method='rk4',
#                   on_pre = synapse_action + conductance_action_Exc, 
#                   );

#exc_syn.connect(j='i');
#exc_syn.x = 1;# initial value of STP-x, neurotransmitter resources

# input neuron - inhibitory synapse - output neuron
#inh_syn = Synapses(G1, G3, clock=Clock(defaultclock.dt), 
#                   model = synapses_eqs,
#                   method='rk4',
#                   on_pre = synapse_action + conductance_action_Inh, 
#                   );

#inh_syn.connect(j='i');
#inh_syn.x = 1;# initial value of STP-x, neurotransmitter resources


# spike generator - inhibitory synapse - output neuron
spk_gen_syn = Synapses(G, G3, clock=Clock(defaultclock.dt), 
                   model = synapses_eqs,
                   method='rk4',
                   on_pre = synapse_action + conductance_action_Inh, 
                   );

spk_gen_syn.connect(j='i');
spk_gen_syn.x = 1;# initial value of STP-x, neurotransmitter resources

spike_mon = SpikeMonitor(G)

M1= StateMonitor(G1, 'v1', record=True); # neuron monitor, must place before generating current
#spikemon1 = SpikeMonitor(G1); # spike train monitor

#M2= StateMonitor(G2, ['v2','g_AMPA','g_NMDA','g_exc','I2'], record=True); # neuron monitor, must place before generating current
#spikemon2 = SpikeMonitor(G2); # spike train monitor

M3= StateMonitor(G3, ['v3','g_GABAa','g_GABAb','g_inh','I3'], record=True); # neuron monitor, must place before generating current
spikemon3 = SpikeMonitor(G3); # spike train monitor

#M4= StateMonitor(exc_syn, ['U','x'], record=True); # neuron monitor, must place before generating current

#M5= StateMonitor(inh_syn, ['U','x'], record=True); # neuron monitor, must place before generating current

M6= StateMonitor(spk_gen_syn, ['U','x'], record=True); # neuron monitor, must place before generating current


#spike generator, make G1.I=0
#G1.I = 0*pA 
#run(1000.0*ms,report='text')

#long duration stimulation
G1.I = 0*pA 
run(100*ms)

G1.I = amp_long
run(105.648*ms)

#pulse stimulation
#G1.I = amp_pulse 
#run(1*ms)

#G1.I = 0*pA
#run(99.0*ms)

#G1.I = amp_pulse 
#run(1*ms)

#G1.I = 0*pA
#run(99.0*ms)

#G1.I = amp_pulse 
#run(1*ms)

#G1.I = 0*pA
#run(99.0*ms)

#G1.I = amp_pulse 
#run(1*ms)

G1.I = 0*pA
run(900.0*ms)

low = 0;
high = 1.0;

savetxt('v1_CA1OA_brian.csv', M1.v1, delimiter=',');

#savetxt('I1.csv', I1, delimiter=',');
#savetxt('v1_mfa_brian.csv', M1.v1, delimiter=',');
#savetxt('g_GABAa_mfa_brian.csv', M3.g_GABAa, delimiter=',');
#savetxt('g_GABAb_mfa_brian.csv', M3.g_GABAb, delimiter=',');
#savetxt('g_mfa_brian.csv', M3.g_inh, delimiter=',');
#savetxt('U_mfa_brian.csv', M5.U, delimiter=',');
#savetxt('x_mfa_brian.csv', M5.x, delimiter=',');
#savetxt('I2_mfa_brian.csv', M3.I3, delimiter=',');
#savetxt('v2_mfa_brian.csv', M3.v3, delimiter=',');

#savetxt('v1_rs_brian.csv', M1.v1, delimiter=',');
#savetxt('g_AMPA_pc_brian.csv', M2.g_AMPA, delimiter=',');
#savetxt('g_NMDA_pc_brian.csv', M2.g_NMDA, delimiter=',');
#savetxt('g_pc_brian.csv', M2.g_exc, delimiter=',');
#savetxt('U_pc_brian.csv', M4.U, delimiter=',');
#savetxt('x_pc_brian.csv', M4.x, delimiter=',');
#savetxt('I2_pc_brian.csv', M2.I2, delimiter=',');
#savetxt('v2_pc_brian.csv', M2.v2, delimiter=',');

#RS
#savetxt('I1.csv', I1, delimiter=',');
#savetxt('v1_RS_brian.csv', M1.v1, delimiter=',');
#savetxt('g_AMPA_RS_brian.csv', M2.g_AMPA, delimiter=',');
#savetxt('g_NMDA_RS_brian.csv', M2.g_NMDA, delimiter=',');
#savetxt('g_RS_brian.csv', M2.g_exc, delimiter=',');
#savetxt('U_RS_brian.csv', M4.U, delimiter=',');
#savetxt('x_RS_brian.csv', M4.x, delimiter=',');
#savetxt('I2_RS_brian.csv', M2.I2, delimiter=',');
#savetxt('v2_RS_brian.csv', M2.v2, delimiter=',');

#BCCCK
#savetxt('v1_bccck_brian.csv', M1.v1, delimiter=',');
#savetxt('g_GABAa_bccck_brian.csv', M3.g_GABAa, delimiter=',');
#savetxt('g_GABAb_bccck_brian.csv', M3.g_GABAb, delimiter=',');
#savetxt('g_bccck_brian.csv', M3.g_inh, delimiter=',');
#savetxt('U_bccck_brian.csv', M5.U, delimiter=',');
#savetxt('x_bccck_brian.csv', M5.x, delimiter=',');
#savetxt('I2_bccck_brian.csv', M3.I3, delimiter=',');
#savetxt('v2_bccck_brian.csv', M3.v3, delimiter=',');


#Spike generator input
#savetxt('g_GABAa_mfa(spk-g)_brian.csv', M3.g_GABAa, delimiter=',');
#savetxt('g_GABAb_mfa(spk-g)_brian.csv', M3.g_GABAb, delimiter=',');
#savetxt('g_mfa(spk-g)_brian.csv', M3.g_inh, delimiter=',');
#savetxt('U_mfa(spk-g)_brian.csv', M6.U, delimiter=',');
#savetxt('x_mfa(spk-g)_brian.csv', M6.x, delimiter=',');
#savetxt('I2_mfa(spk-g)_brian.csv', M3.I3, delimiter=',');
#savetxt('v2_mfa(spk-g)_brian.csv', M3.v3, delimiter=',');


#xlabel('I (pA)')
#ylabel('Input current on neuron1')

#figure(1)
#plt.figure(figsize=(12,10),dpi=90)
#subplot(4,1,1)
#plt.plot(M1.t,M1.v1[0]);
#plt.xlabel('Time(second)');
#plt.xlim(low, high);
#plt.ylabel('Voltage(mV)');
#plt.title('Output voltage on neuron1 (I=2.2nA)');

#subplot(4,1,2)
#plt.plot(M2.t,M2.g_exc[0]);
#plt.xlabel('Time(second)');
#plt.xlim(low, high);
#plt.ylabel('g(nS)');
#plt.title('conductance');

#subplot(4,1,3)
#plt.plot(M2.t,M2.I2[0]);
#plt.xlabel('Time(second)');
#plt.xlim(low, high);
#plt.ylabel('EPSC(pA)');
#plt.title('EPSC');

#subplot(4,1,4)
#plt.plot(M2.t,M2.v2[0]);
#plt.xlabel('Time(second)');
#plt.xlim(low, high);
#plt.ylabel('EPSP(mV)');
#plt.title('EPSP');

#plt.tight_layout();
#plt.show();


#figure(2)
#plt.figure(figsize=(9,8),dpi=80)
#subplot(3,1,1)
#plt.plot(M2.t,M2.g_AMPA[0]);
#plt.xlabel('Time(second)');
#plt.xlim(low, high);
#plt.ylabel('g(nS)');
#plt.title('AMPA conductance');

#subplot(3,1,2)
#plt.plot(M2.t,M2.g_NMDA[0]);
#plt.xlabel('Time(second)');
#plt.xlim(low, high);
#plt.ylabel('g(nS)');
#plt.title('NMDA conductance');

#subplot(3,1,3)
#plt.plot(M4.t,M4.U[0]);
#plt.plot(M4.t,M4.x[0]);
#plt.xlabel('Time(second)');
#plt.xlim(low, high);
#plt.ylabel('a.u');
#plt.title('Synapse STP');

#plt.tight_layout();
#plt.show();


figure(1)
plt.figure(figsize=(12,10),dpi=90)
subplot(4,1,1)
plt.plot(spike_mon.t/ms,spike_mon.i, '.k');
plt.xlabel('Time(second)');
#plt.xlim(low, high);
plt.ylabel('V(mV)');
plt.title('spike generator');

subplot(4,1,2)
plt.plot(M3.t,M3.g_inh[0]);
#plt.plot(M2.t,M2.g_exc[0]);
plt.xlabel('Time(second)');
plt.xlim(low, high);
plt.ylabel('g(nS)');
plt.title('Conductance');

subplot(4,1,3)
plt.plot(M3.t,M3.I3[0]);
#plt.plot(M2.t,M2.I2[0]);
plt.xlabel('Time(second)');
plt.xlim(low, high);
plt.ylabel('IPSC(pA)');
plt.title('IPSC');

subplot(4,1,4)
plt.plot(M3.t,M3.v3[0]);
#plt.plot(M2.t,M2.v2[0]);
plt.xlabel('Time(second)');
plt.xlim(low, high);
plt.ylabel('IPSP(mV)');
plt.title('IPSP');

plt.tight_layout();
plt.show();


figure(2)

plt.figure(figsize=(9,8),dpi=80)
subplot(3,1,1)
plt.plot(M3.t,M3.g_GABAa[0]);
#plt.plot(M2.t,M2.g_AMPA[0]);
plt.xlabel('Time(second)');
plt.xlim(low, high);
plt.ylabel('g(nS)');
#plt.title('GABAa conductance');
plt.title('AMPA conductance');

subplot(3,1,2)
plt.plot(M3.t,M3.g_GABAb[0]);
#plt.plot(M2.t,M2.g_NMDA[0]);
plt.xlabel('Time(second)');
plt.xlim(low, high);
plt.ylabel('g(nS)');
#plt.title('GABAb conductance');
plt.title('NMDA conductance');

subplot(3,1,3)
plt.plot(M6.t,M6.U[0]);
plt.plot(M6.t,M6.x[0]);
#plt.plot(M5.t,M5.U[0]);
#plt.plot(M5.t,M5.x[0]);
#plt.plot(M4.t,M4.U[0]);
#plt.plot(M4.t,M4.x[0]);
plt.xlabel('Time(second)');
plt.xlim(low, high);
plt.ylabel('a.u');
plt.title('Synapse STP');

plt.tight_layout();
plt.show();

figure(3)
plt.figure(figsize=(9,8),dpi=80)
plt.plot(M1.t,M1.v1[0]);
plt.xlabel('Time(second)');
#plt.xlim(low, high);
plt.ylabel('V(mV)');
plt.title('CA1 output');

