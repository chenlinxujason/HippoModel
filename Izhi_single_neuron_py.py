# -*- coding: utf-8 -*-
"""
Created on Tue Jul 26 22:01:53 2022

@author: Chenlin Xu (Jason)
"""
import matplotlib.pyplot as plt
import numpy as np
from numpy import savetxt

#Simulation time = 1000ms
iteration_times = 5; #iterate 5 times per 1 ms (1000ms), so 5 points = 1ms
dt = 1/iteration_times; #step size for Euler method
h = 1/iteration_times; #step size for RK method


short_duration = 1*(1/dt); #1ms; 5 points = 1ms; 2ms: 2*(n/T)
long_duration = 400*(1/dt); # long duration, 400ms
interval = 99*(1/dt);#stimulation interval(time spans = 1000ms), ms
initial_time = 500*(1/dt);#initial time(time spans = 1000ms), ms
end_time = 200*(1/dt); #time lasting after stimulation

#Define electrical stimulation parameters
pulses_number = 4;# 4 pulses of stimulus
amp_pulse = 2200; #for pulse stimulation, pA
amp_long = 70; #for long duration stimulation, pA

stim = amp_pulse*np.ones(int(short_duration)); #stimulus array
inter = np.zeros(int(interval)); #interval array

#intermediate array of stimulus
current_span = np.append(stim,inter);#intermediate array of stimulus
current_span = np.tile(current_span,(1,pulses_number));# 4 pulse
current_1 = np.append(np.zeros(int(initial_time)),current_span);
current_2 = np.append(np.zeros(int(initial_time)),amp_long*np.ones(int(long_duration)));

current_pulses = np.append(current_1,np.zeros(int(end_time)));#4 pulse current
current_long = np.append(current_2,np.zeros(int(end_time)));#long duration stimulus

T = len(current_pulses)/(1/dt); #simulation time span, ms
#T = len(current_long)/(1/dt); #simulation time span, ms
n = int(np.around(T/dt));#the number of points
t = np.linspace(1,n,n)
t = t/iteration_times; #iterate 5 times per 1 ms (1000ms)

#Stimulus
#I1 = current_long; #External stimulus of pre-synaptic neuron: long duration stimulus
I1 = current_pulses; #External stimulus of pre-synaptic neuron: 4 pulses
I2 = np.zeros(len(I1));# External stimulus of post-synaptic neuron: 0

low = 400;#low time limit for plot
high = 1000;#high time limit for plot


#9 parameter Izhikevich model for RS neuron
C = 100; vr = -60; vt = -40; k = 0.7; vpeak = 35;
a = 0.03; b = -2.0; c = -50; d = 100;

#4 parameter Izhikevich model for RS neuron
#a = 0.02;b = 0.2; c = -65; d = 8; vpeak = 30;

STP_U = 0.45; # 0.45(STD) or 0.15(STF)
STP_tau_u = 50; # 50ms(STD) or 750ms(STF),tau_f,facilitation time constant
STP_tau_x = 750; #750 ms(STD) or 50ms(STF),tau_d,depression time constant
tau_AMPA = 5; # fast synaptic decay time(AMPA), ms
tau_NMDA = 150; # slow synaptic decay time(NMDA), ms
tau_GABAa = 5; # fast synaptic decay time(GABAa), ms
tau_GABAb = 150; # slow synaptic decay time(GABAb), ms
A = 1/STP_U; # synaptic weight A, inverse of STP_U(1/0.45=2.22)
w = 0.5; # relatively weight of AMPA component
V_rev_E = 0; # Excitatory reversal potentia, mV
V_rev_I = -80; # Inhibitory reversal potentia, mV

# set up initial values 
v1 = vr*np.ones(n); # pre-synaptic voltage
v2 = vr*np.ones(n); # post-synaptic voltage
u1 = np.zeros(n); # Izhikevich recovery variable u: pre-synaptic neuron
u2 = np.zeros(n); # Izhikevich recovery variable u: post-synaptic voltage
U = np.zeros(n); #  fraction of neurotransmitter before spike
U1 = np.zeros(n);# fraction of neurotransmitter after spike
x = np.zeros(n);# fraction of neurotransmitter remain in the synaptic cleft
x[0] = 1;
g_AMPA = np.zeros(n); # fast conductance(AMPA) 
g_NMDA = np.zeros(n); # slow conductance(NMDA)
g_E = np.zeros(n); # g_AMPA + g_NMDA
I_AMPA = np.zeros(n);# AMPA current
I_NMDA = np.zeros(n);# NMDA current
I_syn_E = np.zeros(n);# Excitatory synaptic current of postsynaptic neuron
g_GABAa = np.zeros(n); # fast conductance(GABAa) 
g_GABAb = np.zeros(n); # slow conductance(GABAb)
g_I = np.zeros(n); # g_GABAa + g_GABAb
I_GABAa = np.zeros(n);# GABAa current
I_GABAb = np.zeros(n);# GABAb current
I_syn_I = np.zeros(n);# Inhibitory synaptic current of postsynaptic neuron
spike_events = np.zeros(n);# check spike timing




# pre-synaptic neuron
for i in range (0,n-1):
    
    ###################### 9 para Euler 
    #v1[i+1]=v1[i]+dt*(k*(v1[i]-vr)*(v1[i]-vt)-u1[i]+I1[i])/C;
    #u1[i+1]=u1[i]+dt*a*(b*(v1[i]-vr)-u1[i]);
    ###################### 9 para Euler 
    
    
    ###################### 4 para Euler 
    #v1[i+1] = v1[i] + dt*(0.04*v1[i]^2+5*v1[i]+140-u1[i]+I1[i]);%-g[i]*(v1[i]-0));
    #u1[i+1] = u1[i] + dt*0.02*(0.2*v1[i]-u1[i]);
    ###################### 4 para Euler 
    
    
    ###################### 9 para RK 
    k1 = (k*(v1[i]-vr)*(v1[i]-vt)-u1[i]+I1[i])/C;
    k2 = (k*((v1[i]+0.5*h*k1)-vr)*((v1[i]+0.5*h*k1)-vt)-u1[i]+I1[i])/C;
    k3 = (k*((v1[i]+0.5*h*k2)-vr)*((v1[i]+0.5*h*k2)-vt)-u1[i]+I1[i])/C;
    k4 = (k*((v1[i]+k3*h)-vr)*((v1[i]+k3*h)-vt)-u1[i]+I1[i])/C;
  
    kk1 = a*(b*(v1[i]-vr)-u1[i]);
    kk2 = a*(b*(v1[i]-vr)-(u1[i]+0.5*h*kk1));
    kk3 = a*(b*(v1[i]-vr)-(u1[i]+0.5*h*kk2));
    kk4 = a*(b*(v1[i]-vr)-(u1[i]+h*kk3));
    ###################### 9 para RK 
    
    
    ###################### 4 para RK 
    #k1=(0.04*v1[i]^2+5*v1[i]+140-u1[i]+I1[i]);
    #k2=(0.04*(v1[i]+0.5*h*k1)^2+5*(v1[i]+0.5*h*k1)+140-u1[i]);
    #k3=(0.04*(v1[i]+0.5*h*k2)^2+5*(v1[i]+0.5*h*k2)+140-u1[i]);
    #k4=(0.04*(v1[i]+h*k3)^2+5*(v1[i]+h*k3)+140-u1[i]);

    #kk1 = 0.02*(0.2*v1[i]-u1[i]);
    #kk2 = 0.02*(0.2*v1[i]-(u1[i]+0.5*h*kk1));
    #kk3 = 0.02*(0.2*v1[i]-(u1[i]+0.5*h*kk2));
    #kk4 = 0.02*(0.2*v1[i]-(u1[i]+h*kk3));
    ###################### 4 para RK 
    
    v1[i+1] = v1[i] + (1/6)*(k1+2*k2+2*k3+k4)*h;
    #u1[i+1] = u1[i] + (1/6)*(kk1+2*kk2+2*kk3+kk4)*h; 
    u1[i+1]=u1[i]+dt*a*(b*(v1[i]-vr)-u1[i]);
    
    if v1[i+1]>=vpeak:
       v1[i]=vpeak;
       v1[i+1]=c;
       u1[i+1]=u1[i+1]+d;
   

def diracfunc(vpeak,p,iter):
       if p >= vpeak:
        return 1/(1/iter);
       else:
        return 0;



for i in range (0,n-1):
   spike_events[i]=diracfunc(vpeak,v1[i],iteration_times);


#Find STP using Euler method, iterate 1 time per 1 ms (not the same as

for i in range (0,n-1):
   U[i+1]=U[i]+dt*((-U[i]/STP_tau_u)+STP_U*(1-U[i])*spike_events[i+1]);
   U1[i+1]=(U[i]*(1-STP_U))+STP_U;
   x[i+1]=x[i]+dt*(((1-x[i])/STP_tau_x)-U1[i+1]*x[i]*spike_events[i+1]);
   
   g_AMPA[i+1]=g_AMPA[i]+dt*(((-g_AMPA[i]/tau_AMPA))+A*U1[i+1]*x[i]*spike_events[i+1]);
   g_NMDA[i+1]=g_NMDA[i]+dt*(((-g_NMDA[i]/tau_NMDA))+A*U1[i+1]*x[i]*spike_events[i+1]);
   g_E[i+1]=w*g_AMPA[i+1]+(1-w)*g_NMDA[i+1];


   I_AMPA[i+1]=g_AMPA[i+1]*(v2[i+1]-V_rev_E);
   I_NMDA[i+1]=g_NMDA[i+1]*(v2[i+1]-V_rev_E)*(((v2[i+1]+80)/60)**2/(1+((v2[i+1]+80)/60)**2));
   I_syn_E[i+1]= -(I_AMPA[i+1]+I_NMDA[i+1]); 
    
    ###################### 9 para Euler 
    #v2[i+1]=v2[i]+dt*(k*(v2[i]-vr)*(v2[i]-vt)-u2[i]+I2[i])/C;
    #u2[i+1]=u2[i]+dt*a*(b*(v2[i]-vr)-u2[i]);
    ###################### 9 para Euler 
    
    
    ###################### 4 para Euler 
    #v2[i+1] = v2[i] + dt*(0.04*v2[i]^2+5*v2[i]+140-u2[i]+I2[i]);%-g[i]*(v2[i]-0));
    #u2[i+1] = u2[i] + dt*0.02*(0.2*v2[i]-u2[i]);
    ###################### 4 para Euler 

    
    ###################### 9 para RK 
   k1_2 = (k*(v2[i]-vr)*(v2[i]-vt)-u2[i]+I2[i]+I_syn_E[i])/C;
   k2_2 = (k*((v2[i]+0.5*h*k1_2)-vr)*((v2[i]+0.5*h*k1_2)-vt)-u2[i]+I2[i]+I_syn_E[i])/C;
   k3_2 = (k*((v2[i]+0.5*h*k2_2)-vr)*((v2[i]+0.5*h*k2_2)-vt)-u2[i]+I2[i]+I_syn_E[i])/C;
   k4_2 = (k*((v2[i]+k3_2*h)-vr)*((v2[i]+k3_2*h)-vt)-u2[i]+I2[i]+I_syn_E[i])/C;

   kk1_2 = a*(b*(v2[i]-vr)-u2[i]);
   kk2_2 = a*(b*(v2[i]-vr)-(u2[i]+0.5*h*kk1_2));
   kk3_2 = a*(b*(v2[i]-vr)-(u2[i]+0.5*h*kk2_2));
   kk4_2 = a*(b*(v2[i]-vr)-(u2[i]+h*kk3_2));
    ###################### 9 para RK 
    
    
    ###################### 4 para RK 
    #k1=(0.04*v2[i]^2+5*v2[i]+140-u2[i]+I2[i]);
    #k2=(0.04*(v2[i]+0.5*h*k1)^2+5*(v2[i]+0.5*h*k1)+140-u2[i]);
    #k3=(0.04*(v2[i]+0.5*h*k2)^2+5*(v2[i]+0.5*h*k2)+140-u2[i]);
    #k4=(0.04*(v2[i]+h*k3)^2+5*(v2[i]+h*k3)+140-u2[i]);

    #kk1 = 0.02*(0.2*v2[i]-u2[i]);
    #kk2 = 0.02*(0.2*v2[i]-(u2[i]+0.5*h*kk1));
    #kk3 = 0.02*(0.2*v2[i]-(u2[i]+0.5*h*kk2));
    #kk4 = 0.02*(0.2*v2[i]-(u2[i]+h*kk3));
    ###################### 4 para RK 
    
   v2[i+1] = v2[i] + (h/6)*(k1_2+2*k2_2+2*k3_2+k4_2);
   #u2[i+1] = u2[i] + (h/6)*(kk1_2+2*kk2_2+2*kk3_2+kk4_2); 
   u2[i+1]=u2[i]+dt*a*(b*(v2[i]-vr)-u2[i]);
    
   if v2[i+1]>=vpeak:
       v2[i]=vpeak;
       v2[i+1]=c;
       u2[i+1]=u2[i+1]+d;



#Find peak value and HHW
#y = v(580:748); % take the first EPSP waveform
#halfHeight = (min(y) + max(y)) / 2; %find half high

#index1 = find(y >= halfHeight, 1, 'first');% find left edge
#t1 = t(index1);
#index2 = find(y >= halfHeight, 1, 'last');% find right edge
#t2 = t(index2);

#HHW and peak amplitude.
#peak_amp = max(y) - min(y) %peak amplitude
#HHW = t2 - t1 %half height width (ms)

savetxt('I1.csv', I1, delimiter=',');
savetxt('v1.csv', v1, delimiter=',');
savetxt('g_E.csv', g_E, delimiter=',');
savetxt('U.csv', U, delimiter=',');
savetxt('x.csv', x, delimiter=',');
savetxt('I_syn_E.csv', I_syn_E, delimiter=',');
savetxt('v2.csv', v2, delimiter=',');

plt.figure(1)
#sgtitle('Excitatory (COBA+STP) - RK method'); 
#sgtitle('Excitatory (COBA+STP) - Euler method');
plt.figure(figsize=(12,10),dpi=90)
plt.subplot(6,1,1)
plt.plot(t,I1,'r','LineWidth',2);
plt.title('Input current on neuron 1 (2200pA,dur=1ms)'); 
plt.xlabel('Time(ms)');
plt.xlim([low,high]);
plt.ylabel('I(pA)');


plt.subplot(6,1,2)
plt.plot(t,v1,'b','LineWidth',2);
plt.title('output voltage on neuron 1');
plt.xlabel('Time(ms)');
plt.xlim([low,high]);
plt.ylabel('V(mV)');
plt.ylim([-70,50]);

plt.subplot(6,1,3)
plt.plot(t,g_E,'b','LineWidth',2);
plt.title('Conductance');
plt.xlabel('Time(ms)');
plt.xlim([low,high]);
plt.ylabel('g(nS)');
plt.ylim([0,1.25]);

plt.subplot(6,1,4)
plt.plot(t,U,'k','LineWidth',2);
plt.plot(t,x,'g','LineWidth',2);
plt.title('Synapse STP');
plt.xlabel('Time(ms)');
plt.xlim([low,high]);
plt.ylim([0,1]);
plt.ylabel('a.u');
#plt.legend('U','x');

plt.subplot(6,1,5)
plt.plot(t,I_syn_E,'b','LineWidth',2);
plt.title('Synaptic current on postsynaptic neuron'); 
plt.xlabel('Time(ms)');
plt.xlim([low,high]);
plt.ylabel('I(pA)');


plt.subplot(6,1,6)
plt.plot(t,v2,'b','LineWidth',2);
plt.title('output voltage on neuron 2');
plt.xlabel('Time(ms)');
plt.xlim([low,high]);
plt.ylabel('V(mV)');
plt.ylim([-60,-58]);
plt.tight_layout();
#plt.show();

plt.figure(2) #EPSP
plt.plot(t,v2,'b','LineWidth',2);
plt.title('output voltage on neuron 2');
plt.xlabel('Time(ms)');
plt.xlim([low,high]);
plt.ylabel('V(mV)');
plt.ylim([-60,-58]);

plt.figure(3)# postsynaptic current
plt.subplot(3,1,1)
plt.plot(t,I_AMPA,'r','LineWidth',2);
plt.title('AMPA current'); 
plt.xlabel('Time(ms)');
plt.xlim([low,high]);
plt.ylabel('I(pA)');

plt.subplot(3,1,2)
plt.plot(t,I_NMDA,'b','LineWidth',2);
plt.title('NMDA current'); 
plt.xlabel('Time(ms)');
plt.xlim([low,high]);
plt.ylabel('I(pA)');

plt.subplot(3,1,3)
plt.plot(t,I_syn_E,'k','LineWidth',2);
plt.title('Synaptic current on postsynaptic neuron'); 
plt.xlabel('Time(ms)');
plt.xlim([low,high]);
plt.ylabel('I(pA)');
plt.tight_layout();
plt.show();

plt.figure(4)# conductance
plt.plot(t,g_E,'b','LineWidth',2);
plt.title('Conductance');
plt.xlabel('Time(ms)');
plt.xlim([low,high]);
plt.ylabel('g(nS)');
plt.ylim([0,1.25]);

