
clear all
clc
initOAT;

% init NetworkMonitor
%NM = NetworkMonitor('../results/sim_ca1_test.dat');
%NM.plot;
%GM = GroupMonitor('CA3_QuadD_LM','results/');
%GM.plot

% init ConnectionMonitor
%CM = ConnectionMonitor('input','output','../results/');

%time boundary
I_stim = 600;%pA
low = 0;
up = 10000;
n = 1; %the number of neuron choosen whose waveforms to be plot
sz = 1.2; alp = 0.4;%alpha value
nR_Py = NeuronReader('../results/n_CA1_Pyramidal.dat');
Values_Py = nR_Py.readValues;
current_Py = Values_Py.I;
voltage_Py = Values_Py.v;
recovery_Py = Values_Py.u;

nR_RG = NeuronReader('../results/n_CA1_Radiatum_Giant.dat');
Values_RG = nR_RG.readValues;
voltage_RG = Values_RG.v;
current_RG = Values_RG.I;
recovery_RG = Values_RG.u;

nR_BP = NeuronReader('../results/n_CA1_Back_Projection.dat');
Values_BP = nR_BP.readValues;
voltage_BP = Values_BP.v;
current_BP = Values_BP.I;
recovery_BP = Values_BP.u;


nR_Bi = NeuronReader('../results/n_CA1_Bistratified.dat');
Values_Bi = nR_Bi.readValues;
voltage_Bi = Values_Bi.v;
current_Bi = Values_Bi.I;
recovery_Bi = Values_Bi.u;

nR_Ivy = NeuronReader('../results/n_CA1_Ivy.dat');
Values_Ivy = nR_Ivy.readValues;
voltage_Ivy = Values_Ivy.v;
current_Ivy = Values_Ivy.I;
recovery_Ivy = Values_Ivy.u;

nR_Ng = NeuronReader('../results/n_CA1_Neurogliaform.dat');
Values_Ng = nR_Ng.readValues;
voltage_Ng = Values_Ng.v;
current_Ng = Values_Ng.I;
recovery_Ng = Values_Ng.u;

nR_OLM = NeuronReader('../results/n_CA1_OLM.dat');
Values_OLM = nR_OLM.readValues;
voltage_OLM = Values_OLM.v;
current_OLM = Values_OLM.I;
recovery_OLM = Values_OLM.u;

nR_OLMR = NeuronReader('../results/n_CA1_O_LMR.dat');
Values_OLMR = nR_OLMR.readValues;
voltage_OLMR = Values_OLMR.v;
current_OLMR = Values_OLMR.I;
recovery_OLMR = Values_OLMR.u;

nR_OB = NeuronReader('../results/n_CA1_Oriens_Bistratified.dat');
Values_OB = nR_OB.readValues;
voltage_OB = Values_OB.v;
current_OB = Values_OB.I;
recovery_OB = Values_OB.u;

nR_PPA = NeuronReader('../results/n_CA1_Perforant_Path_Associated.dat');
Values_PPA = nR_PPA.readValues;
voltage_PPA = Values_PPA.v;
current_PPA = Values_PPA.I;
recovery_PPA = Values_PPA.u;

nR_SCA = NeuronReader('../results/n_CA1_Schaffer_Collateral_Associated.dat');
Values_SCA = nR_SCA.readValues;
voltage_SCA = Values_SCA.v;
current_SCA = Values_SCA.I;
recovery_SCA = Values_SCA.u;

nR_SO = NeuronReader('../results/n_CA1_SO_SO.dat');
Values_SO = nR_SO.readValues;
voltage_SO = Values_SO.v;
current_SO = Values_SO.I;
recovery_SO = Values_SO.u;

nR_Tr = NeuronReader('../results/n_CA1_Trilaminar.dat');
Values_Tr = nR_Tr.readValues;
voltage_Tr = Values_Tr.v;
current_Tr = Values_Tr.I;
recovery_Tr = Values_Tr.u;


SR_Py = SpikeReader('../results/spk_CA1_Pyramidal.dat');
spkData_Py = SR_Py.readSpikes(-1); % binWindowMs
%spkData_Py = SR_Py.readSpikes(100); % binWindowMs=100ms

SR_RG = SpikeReader('../results/spk_CA1_Radiatum_Giant.dat');
spkData_RG = SR_RG.readSpikes(-1); % binWindowMs

SR_BP = SpikeReader('../results/spk_CA1_Back_Projection.dat');
spkData_BP = SR_BP.readSpikes(-1); % binWindowMs

SR_Bi = SpikeReader('../results/spk_CA1_Bistratified.dat');
spkData_Bi = SR_Bi.readSpikes(-1); % binWindowMs

SR_Ivy = SpikeReader('../results/spk_CA1_Ivy.dat');
spkData_Ivy = SR_Ivy.readSpikes(-1); % binWindowMs

SR_Ng = SpikeReader('../results/spk_CA1_Neurogliaform.dat');
spkData_Ng = SR_Ng.readSpikes(-1); % binWindowMs

SR_OLM = SpikeReader('../results/spk_CA1_OLM.dat');
spkData_OLM = SR_OLM.readSpikes(-1); % binWindowMs

SR_OLMR = SpikeReader('../results/spk_CA1_O_LMR.dat');
spkData_OLMR = SR_OLMR.readSpikes(-1); % binWindowMs

SR_OB = SpikeReader('../results/spk_CA1_Oriens_Bistratified.dat');
spkData_OB = SR_OB.readSpikes(-1); % binWindowMs

SR_PPA = SpikeReader('../results/spk_CA1_Perforant_Path_Associated.dat');
spkData_PPA = SR_PPA.readSpikes(-1); % binWindowMs

SR_SCA = SpikeReader('../results/spk_CA1_Schaffer_Collateral_Associated.dat');
spkData_SCA = SR_SCA.readSpikes(-1); % binWindowMs

SR_SO = SpikeReader('../results/spk_CA1_SO_SO.dat');
spkData_SO = SR_SO.readSpikes(-1); % binWindowMs
% init ConnectionMonitor

SR_Tr = SpikeReader('../results/spk_CA1_Trilaminar.dat');
spkData_Tr = SR_Tr.readSpikes(-1); % binWindowMs


%%% connection monitor %%%

%CR_AAC_PD = ConnectionReader('../results/conn_CA3_Axo_Axonic_CA3_Pyramidal.dat');
%[allTimestamps, allWeights] = CR_AAC_PD.readWeights();

%figure(1) % connection monitor
%imagesc(reshape(allWeights(1,:), CR_AAC_PD.getNumNeuronsPost(), CR_AAC_PD.getNumNeuronsPre()) );
%xlabel('Axo Axonic neuron ID');
%ylabel('Pyramidal neuron ID');
%title('Axo-Pyra Connection');

%create figure 3
numNeurons = 75000;
[NMsimData] = readNMsim('/home/song/CARLsim/projects/snn_test/results',numNeurons);
analysisCut = 1;
tf = 10000;

%className = PC;
fileOutLoc = 'D:\snn_ca1_test_results';

createFigure3Plots(NMsimData,analysisCut,tf,fileOutLoc)

fig = figure;

%sgtitle('CA1 spike trains','FontSize', 15);
stim = [zeros(1,100),I_stim*ones(1,1000),zeros(1,9000)];
subplot(7,2,1)
plot(stim,'r','LineWidth',1.5);
title('Current on CA1 Pyramidal','FontSize',14);
xlim([low,up]);
%xlabel('Time(ms)');
%ylabel('Current(pA)');
legend('Current(pA)');

subplot(7,2,2)
scatter(spkData_Py(1,:), spkData_Py(2,:),1,'k','filled');
alpha(0.4);
title('CA1 Pyramidal','FontSize',14);
xlim([low,up]);
%ylim([0,500]);
%xlabel('Time(ms)');
%ylabel('Neuron ID');

subplot(7,2,3)
%plot(spkData_RG(1,:), spkData_RG(2,:), '.k');
title('CA1 Radiatum Giant','FontSize',14);
xlim([low,up]);
%xlabel('Time(ms)');
%ylabel('Neuron ID');

subplot(7,2,4)
scatter(spkData_BP(1,:), spkData_BP(2,:),sz,'k','filled');
alpha(alp);
title('CA1 Back Projection','FontSize',14);
xlim([low,up]);
%xlabel('Time(ms)');
%ylabel('Neuron ID');

subplot(7,2,5)
scatter(spkData_Bi(1,:), spkData_Bi(2,:),sz,'k','filled');
alpha(alp);
title('CA1 Bistratified','FontSize',14);
xlim([low,up]);
%xlabel('Time(ms)');
%ylabel('Neuron ID');

subplot(7,2,6)
scatter(spkData_Ivy(1,:), spkData_Ivy(2,:),sz,'k','filled');
alpha(alp);
title('CA1 Ivy','FontSize',14);
xlim([low,up]);
%xlabel('Time(ms)');
%ylabel('Neuron ID');

subplot(7,2,7)
%scatter(spkData_Ng(1,:), spkData_Ng(2,:),sz,'k','filled');
%alpha(alp);
%plot(spkData_Ng(1,:), '.','MarkerSize',sz);
title('CA1 Neurogliaform','FontSize',14);
xlim([low,up]);
%xlabel('Time(ms)');
%ylabel('Neuron ID');

subplot(7,2,8)
scatter(spkData_OLM(1,:), spkData_OLM(2,:),sz,'k','filled');
alpha(alp);
title('CA1 OLM','FontSize',14);
xlim([low,up]);
%xlabel('Time(ms)');
%ylabel('Neuron ID');

subplot(7,2,9)
scatter(spkData_OLMR(1,:), spkData_OLMR(2,:),sz,'k','filled');
alpha(alp);
title('CA1 OLMR','FontSize',14);
xlim([low,up]);
%xlabel('Time(ms)');
%ylabel('Neuron ID');

subplot(7,2,10)
scatter(spkData_OB(1,:), spkData_OB(2,:),sz,'k','filled');
alpha(alp);
title('CA1 Oriens-Bistratified','FontSize',14);
xlim([low,up]);
%xlabel('Time(ms)');
%ylabel('Neuron ID');

subplot(7,2,11)
%scatter(spkData_PPA(1,:), spkData_PPA(2,:),sz,'k','filled');
%alpha(alp);
%plot(spkData_PPA(1,:),'.','MarkerSize',sz);
title('CA1 Perforant Path-Associated','FontSize',14);
xlim([low,up]);
%xlabel('Time(ms)');
%ylabel('Neuron ID');

subplot(7,2,12)
%plot(spkData_SCA(1,:), spkData_SCA(2,:),'.','MarkerSize',sz);
%scatter(spkData_SCA(1,:), spkData_SCA(2,:),'.','MarkerSize',sz,'k','filled');
%alpha(alp);
title('Schaffer Collateral-Associated','FontSize',14);
xlim([low,up]);
%xlabel('Time(ms)');
%ylabel('Neuron ID');

subplot(7,2,13)
scatter(spkData_SO(1,:), spkData_SO(2,:),sz,'k','filled');
alpha(alp);
title('CA1 SO-SO','FontSize',14);
xlim([low,up]);
%xlabel('Time(ms)');
%ylabel('Neuron ID');

subplot(7,2,14)
scatter(spkData_Tr(1,:), spkData_Tr(2,:),sz,'k','filled');
alpha(alp);
title('CA1 Trilaminar','FontSize',14);
xlim([low,up]);
%xlabel('Time(ms)');
%ylabel('Neuron ID');

sgtitle('CA1 Spike train','FontSize',14);
han=axes(fig,'visible','off'); 
han.Title.Visible='on';
han.XLabel.Visible='on';
han.YLabel.Visible='on';
ylabel(han,'Neuron ID','FontSize',15);
xlabel(han,'Time(ms)','FontSize',15);
%title(han,'CA1 Spike train','FontSize',16);