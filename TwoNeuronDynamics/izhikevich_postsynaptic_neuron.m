function [v,u,U,x,g_fast,g_slow,g_syn,I_fast,I_slow,I_syn,spikes] = ...
izhikevich_postsynaptic_neuron(Integrator,conn_type,spike_trains,STP_U,STP_tau_u,...
STP_tau_x,V_rev_fast,V_rev_slow, tau_fast,tau_slow,w_fast,w_slow,...
C,vr,vt,k,vpeak,a,b,c,d,T,step,I)

% This code do not have CARLsim Synaptic Receptor-Specific Gain Factors

% Integrator: set integration method. Integrator=1: Euler | Integrator=2: Runge Kutta
% conn_type: set connection type. conn_type=1: excitatory | conn_type=2: inhibitory
% spike_trains: spikes from presynaptic neuron, should be 0 and 1

% STP_U: STP U variable. 0.45 for excitatory neuron, 0.15 for inhibitory
% neuron. STP_U is a parameter related to the utilization of synaptic efficacy in 
% STP models. 

% A: synaptic weight, how much neurotransmitter is released during synaptic 
% transmission(the proportion of neurotransmitter that released). In CARLsim, 
% A is set as 1/STP_U

% STP_tau_u: STP tau_u variable
% STP_tau_x: STP tau_x variable
% V_rev_fast: reversal potential of fast neurotransmitter receptor(0 for AMPA, -70mV for GABAa)
% V_rev_slow: reversal potential of slow neurotransmitter receptor(0 for NMDA, -90mV for GABAb)
% tau_fast: fast conductance (AMPA or GABAa)(ms)
% tau_slow: slow conductance (NMDA or GABAb)(ms)

% w: weight, it refers to the strength or efficacy of the connection between two 
% neurons. Factors that influence it include: Neurotransmitter release; Receptor
% availability, the number and type of available receptors on the postsynaptic
% membrane; Ion channel conductance(I=GV);Postsynaptic response(EPSP amplitude)

% w_fast: w*fast_gain, fast_gain represent the amount of fast conductance
% w_slow: w*slow_gain, slow_gain represent the amount of slow conductance


%% Notes for CARLsim conductance and STP:
% In CARLsim, when we call setConductance(neuron,...) and setSTP(neuron,..),
% the neuron should be postsynaptic neuron + presynaptic synapse. However, default
% CARLsim6 don't have connection-specific commands for them, so setConductance and
% setSTP only set in postsynaptic neuron level, and thus we don't need to worry about
% presynaptic neuron. In future, when we have connection-specific setConductance and
% setSTP commands, the setConductance and setSTP should be set in postsynaptic
% neuron + presynaptic synapse, and we need to consider presynaptic neuron.
    
n = round(T/step); % simulation time steps
iteration_times = 1/step;
v = vr*ones(1,n); % initial values of membrane potential
A = 1/STP_U;
u = zeros(1,n);  % initial values of recovery
U = zeros(1,n); % fraction of neurotransmitter before spike
U1 = zeros(1,n);% fraction of neurotransmitter after spike
x = zeros(1,n);% fraction of neurotransmitter remain in the synaptic cleft
x(1) = 1;%1
g_fast = zeros(1,n); % fast neurotransmitter conductance
g_slow = zeros(1,n); % slow neurotransmitter conductance
g_syn = zeros(1,n); % g_AMPA + g_NMDA or g_GABAa + g_GABAb
I_fast = zeros(1,n);% fast neurotransmitter current
I_slow = zeros(1,n);% slow neurotransmitter current
I_syn = zeros(1,n); % post-synaptic synaptic current
% f = zeros(1,n);

 for i=1:n-1
   % Find STP
    U(i+1)=U(i)+step*((-U(i)/STP_tau_u)+STP_U*(1-U(i))*spike_trains(i+1));
    U1(i+1)=U(i)+STP_U*(1-U(i));
    x(i+1)=x(i)+step*(((1-x(i))/STP_tau_x)-U1(i+1)*x(i)*spike_trains(i+1));

    g_fast(i+1)=g_fast(i)+step*(((-g_fast(i)/tau_fast))+w_fast*A*U1(i+1)*x(i)*spike_trains(i+1));%synaptic weight w=1
    g_slow(i+1)=g_slow(i)+step*(((-g_slow(i)/tau_slow))+w_slow*A*U1(i+1)*x(i)*spike_trains(i+1));%synaptic weight w=1
    g_syn(i+1)=g_fast(i+1)+g_slow(i+1); 
 end 
 
 switch Integrator 
     case 1
      for i=1:n-1
          v(i+1)=v(i)+step*(k*(v(i)-vr)*(v(i)-vt)-u(i)+I(i)-g_fast(i)*(v(i)-V_rev_fast)-g_slow(i)*(v(i)-V_rev_slow))/C;
          u(i+1)=u(i)+step*a*(b*(v(i)-vr)-u(i));
          
          if v(i+1)>= vpeak 
              v(i)=vpeak;
              v(i+1)=c;
              u(i+1)=u(i+1)+d;
          end
      end
      
     case 2
     for i=1:n-1
         switch conn_type
             case 1 % excitatory - *presynaptic neuron has excitatory synapse
                 I_fast(i+1)=w_fast*g_fast(i+1)*(v(i+1)-V_rev_fast);
                 I_slow(i+1)=w_slow*g_slow(i+1)*(v(i+1)-V_rev_slow)*(((v(i+1)+80)/60)^2)/(1+(((v(i+1)+80)/60)^2));
                 I_syn(i+1)= -(I_fast(i+1)+I_slow(i+1));
             case 2 % inhibitory - *presynaptic neuron has inhibitory synapse
                 I_fast(i+1)=g_fast(i+1)*(v(i+1)-V_rev_fast);
                 I_slow(i+1)=g_slow(i+1)*(v(i+1)-V_rev_slow);
                 I_syn(i+1)= -(I_fast(i+1)+I_slow(i+1));        
         end
         
         K1=(k*(v(i)-vr)*(v(i)-vt)-u(i)+I(i)+I_syn(i))/C;
         K2=(k*((v(i)+0.5*step*K1)-vr)*((v(i)+0.5*step*K1)-vt)-u(i)+I(i)+I_syn(i))/C;
         K3=(k*((v(i)+0.5*step*K2)-vr)*((v(i)+0.5*step*K2)-vt)-u(i)+I(i)+I_syn(i))/C;
         K4=(k*((v(i)+K3*step)-vr)*((v(i)+K3*step)-vt)-u(i)+I(i)+I_syn(i))/C;

         v(i+1)=v(i)+(step/6)*(K1+2*K2+2*K3+K4);
         u(i+1)=u(i)+step*(a*(b*(v(i)-vr)-u(i)));% CARLsim use Euler method for u variable
%          u(i+1)=u(i)+(step/6)*(K1_U+2*K2_U+2*K3_U+K4_U); 
              
           if v(i+1)>= vpeak
              v(i)=vpeak;
              v(i+1)=c;
              u(i+1)=u(i+1)+d;
           end
      end
 end

for i=1:n
    spikes(i)=diracfunc(vpeak,v(i),iteration_times);% single peak
end
