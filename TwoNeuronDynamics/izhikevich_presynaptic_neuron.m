function [v,u,spikes,I] = izhikevich_presynaptic_neuron(Integrator,amp,C,vr,vt,k,vpeak,...
a,b,c,d,T,step,PulseStart,PulseEnd)
% Integrator: set integration method. Integrator=1: Euler | Integrator=2: Runge Kutta

% amp: external stimulation current amplitude of presynaptic neuron (pA)
% T: total time of simulation(ms)
% step: time step of stimulation(ms),step=0.2ms is iterate 5 times
% PulseWidth: stimulation pulse width (fraction of total time, 0.9,0.8,...)

n = round(T/step); % simulation time steps
iteration_times = 1/step;

%I = [zeros(1,int32((1-PulseWidth)*n)),amp*ones(1,int32(PulseWidth*n))]; % stimulation current
I = zeros(1,n); 
PulseStartIndex = round(PulseStart/step) + 1; % Index for pulse start
PulseEndIndex = round(PulseEnd/step); % Index for pulse end
I(PulseStartIndex:PulseEndIndex) = amp; % Set pulse amplitude

v = vr*ones(1,n); % initial values of membrane potential
u = zeros(1,n);  % initial values of recovery
spikes = zeros(1,n);  % initial values of spikes 

if Integrator == 1
   
    for i=1:n-1
    v(i+1)=v(i)+step*(k*(v(i)-vr)*(v(i)-vt)-u(i)+I(i))/C;
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
    K1=(k*(v(i)-vr)*(v(i)-vt)-u(i)+I(i))/C;
    K2=(k*((v(i)+(step/2)*K1)-vr)*((v(i)+(step/2)*K1)-vt)-u(i)+I(i))/C;
    K3=(k*((v(i)+(step/2)*K2)-vr)*((v(i)+(step/2)*K2)-vt)-u(i)+I(i))/C;
    K4=(k*((v(i)+step*K3)-vr)*((v(i)+step*K3)-vt)-u(i)+I(i))/C;
 
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

for i=1:n
    spikes(i)=diracfunc(vpeak,v(i),iteration_times);% single peak
end
