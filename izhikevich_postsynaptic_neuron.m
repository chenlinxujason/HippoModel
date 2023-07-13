function [v,u,U,x,g_fast,g_slow,g_syn,I_fast,I_slow,I_syn,spikes,I] = ...
izhikevich_postsynaptic_neuron(Integrator,conn_type,spike_trains,STP_U,STP_tau_u,...
STP_tau_x,V_rev_fast,V_rev_slow, tau_fast,tau_slow,w,amp,...
C,vr,vt,k,vpeak,a,b,c,d,T,step,PulseWidth)

% Integrator: set integration method. Integrator=1: Euler | Integrator=2: Runge Kutta
% conn_type: set connection type. conn_type=1: excitatory | conn_type=2: inhibitory

% amp: external stimulation current magnitude of postsynaptic neuron (pA)
% w: synaptic connection weight, relatively component of fast neurotransmitter
% T: total time of simulation(ms)
% PulseWidth: stimulation pulse width (fraction of total time, 0.9,0.8,...)
% step: time step of stimulation(ms),step=0.2ms is iterate 5 times
% tau_fast: fast conductance (AMPA or GABAa)(ms)
% tau_slow: slow conductance (NMDA or GABAb)(ms)
% V_rev_fast: reversal potential of fast neurotransmitter receptor(0 for AMPA, -70mV for GABAa)
% V_rev_slow: reversal potential of slow neurotransmitter receptor(0 for NMDA, -90mV for GABAb)
    
n = round(T/step); % simulation time steps
iteration_times = 1/step;
v = vr*ones(1,n); % initial values of membrane potential
I = [zeros(1,int32((1-PulseWidth)*n)),amp*ones(1,int32(PulseWidth*n))]; % stimulation current
A = 1/STP_U;
u = 0*vr;  % initial values of recovery
U = 0*vr; % fraction of neurotransmitter before spike
U1 = 0*vr;% fraction of neurotransmitter after spike
x = 0*vr;% fraction of neurotransmitter remain in the synaptic cleft
x(1) = 1;
g_fast = 0*vr; % fast neurotransmitter conductance
g_slow = 0*vr; % slow neurotransmitter conductance
g_syn = 0*vr; % g_AMPA + g_NMDA or g_GABAa + g_GABAb
I_fast = 0*vr;% fast neurotransmitter current
I_slow = 0*vr;% slow neurotransmitter current
I_syn = 0*vr; % post-synaptic synaptic current

 for i=1:n-1
   % Find STP
   U(i+1)=U(i)+step*((-U(i)/STP_tau_u)+STP_U*(1-U(i))*spike_trains(i+1));
   U1(i+1)=U(i)+STP_U*(1-U(i));
   x(i+1)=x(i)+step*(((1-x(i))/STP_tau_x)-U1(i+1)*x(i)*spike_trains(i+1));
   g_fast(i+1)=g_fast(i)+step*(((-g_fast(i)/tau_fast))+w*A*U1(i+1)*x(i)*spike_trains(i+1));%synaptic weight w=1
   g_slow(i+1)=g_slow(i)+step*(((-g_slow(i)/tau_slow))+w*A*U1(i+1)*x(i)*spike_trains(i+1));%synaptic weight w=1
   g_syn(i+1)=g_fast(i+1)+g_slow(i+1); 
 end
 
 
 if Integrator == 1
      for i=1:n-1
          v(i+1)=v(i)+step*(k*(v(i)-vr)*(v(i)-vt)-u(i)+I(i)-g_fast(i)*(v(i)-V_rev_fast)-g_slow(i)*(v(i)-V_rev_slow))/C;
          u(i+1)=u(i)+step*a*(b*(v(i)-vr)-u(i));
          
          if v(i+1)>= vpeak 
              v(i)=vpeak;
              v(i+1)=c;
              u(i+1)=u(i+1)+d;
          end
      end
 end
 
 if Integrator == 2
     for i=1:n-1
         K1=(k*(v(i)-vr)*(v(i)-vt)-u(i)+I(i)-g_fast(i)*(v(i)-V_rev_fast)-g_slow(i)*(v(i)-V_rev_slow))/C;
         K2=(k*((v(i)+(step/2)*K1)-vr)*((v(i)+(step/2)*K1)-vt)-u(i)+I(i)-g_fast(i)*(v(i)-V_rev_fast)-g_slow(i)*(v(i)-V_rev_slow))/C;
         K3=(k*((v(i)+(step/2)*K2)-vr)*((v(i)+(step/2)*K2)-vt)-u(i)+I(i)-g_fast(i)*(v(i)-V_rev_fast)-g_slow(i)*(v(i)-V_rev_slow))/C;
         K4=(k*((v(i)+step*K3)-vr)*((v(i)+step*K3)-vt)-u(i)+I(i)-g_fast(i)*(v(i)-V_rev_fast)-g_slow(i)*(v(i)-V_rev_slow))/C;
              
        %K1_U = a*(b*(v(i)-vr)-u(i));
        %K2_U = a*(b*(v(i)-vr)-(u(i)+(step/2)*K1_U));
        %K3_U = a*(b*(v(i)-vr)-(u(i)+(step/2)*K2_U));
        %K4_U = a*(b*(v(i)-vr)-(u(i)+h*K3_U));

         v(i+1)=v(i)+(step/6)*(K1+2*K2+2*K3+K4);
         u(i+1)=u(i)+step*(a*(b*(v(i)-vr)-u(i)));
         %u(i+1)=u(i)+(step/6)*(K1_U+2*K2_U+2*K3_U+K4_U); 
              
           if v(i+1)>= vpeak
              v(i)=vpeak;
              v(i+1)=c;
              u(i+1)=u(i+1)+d;
           end
        end
    end
                  
                  

 if conn_type == 1 % excitatory current
     for i=1:n-1
         I_fast(i+1)=g_fast(i+1)*(v(i+1)-V_rev_fast);
         I_slow(i+1)=g_slow(i+1)*(v(i+1)-V_rev_slow)*(((v(i+1)+80)/60)^2)/(1+(((v(i+1)+80)/60)^2));
         I_syn(i+1)= -(I_fast(i+1)+I_slow(i+1));
     end
 end
     
 if conn_type == 2 % inhibitory current
     for i=1:n-1
         I_fast(i+1)=g_fast(i+1)*(v(i+1)-V_rev_fast);
         I_slow(i+1)=g_slow(i+1)*(v(i+1)-V_rev_slow);
         I_syn(i+1)= -(I_fast(i+1)+I_slow(i+1));
     end
 end


for i=1:n
    spikes(i)=diracfunc(vpeak,v(i),iteration_times);% single peak
end
