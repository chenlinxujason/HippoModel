
clear 
clc
close all;
initOAT;

% init NetworkMonitor
NM = NetworkMonitor('../results/sim_ca3_test.dat');
%NM.plot;
%GM = GroupMonitor('CA3_QuadD_LM','results/');
%GM.plot

% init ConnectionMonitor
%CM = ConnectionMonitor('input','output','../results/');

%time boundary
I_stim = 600;%pA
low = 0;
up = 1000;
n = 1; %the number of neuron choosen whose waveforms to be plot
sz = 2; alp = 0.7;%alpha value

nR_AAC = NeuronReader('../results/n_CA3_Axo_Axonic.dat');
Values_AAC = nR_AAC.readValues;
current_AAC = Values_AAC.I;
voltage_AAC = Values_AAC.v;
recovery_AAC = Values_AAC.u;

nR_BC = NeuronReader('../results/n_CA3_Basket.dat');
Values_BC = nR_BC.readValues;
voltage_BC = Values_BC.v;
current_BC = Values_BC.I;
recovery_BC = Values_BC.u;

nR_BC_CCK = NeuronReader('../results/n_CA3_BC_CCK.dat');
Values_BC_CCK = nR_BC_CCK.readValues;
voltage_BC_CCK = Values_BC_CCK.v;
current_BC_CCK = Values_BC_CCK.I;
recovery_BC_CCK = Values_BC_CCK.u;

nR_Bis = NeuronReader('../results/n_CA3_Bistratified.dat');
Values_Bis = nR_Bis.readValues;
voltage_Bis = Values_Bis.v;
current_Bis = Values_Bis.I;
recovery_Bis = Values_Bis.u;

nR_BC_CCK = NeuronReader('../results/n_CA3_Basket.dat');
Values_BC = nR_BC_CCK.readValues;
voltage_BC = Values_BC.v;
current_BC = Values_BC.I;
recovery_BC = Values_BC.u;

nR_Ivy = NeuronReader('../results/n_CA3_Ivy.dat');
Values_Ivy = nR_Ivy.readValues;
voltage_Ivy = Values_Ivy.v;
current_Ivy = Values_Ivy.I;
recovery_Ivy = Values_Ivy.u;

nR_MFA = NeuronReader('../results/n_CA3_MFA_ORDEN.dat');
Values_MFA = nR_MFA.readValues;
voltage_MFA = Values_MFA.v;
current_MFA = Values_MFA.I;
recovery_MFA = Values_MFA.u;

nR_PC = NeuronReader('../results/n_CA3_Pyramidal.dat');
Values_PC = nR_PC.readValues;
voltage_PC = Values_PC.v;
current_PC = Values_PC.I;
recovery_PC = Values_PC.u;

nR_Quad = NeuronReader('../results/n_CA3_QuadD_LM.dat');
Values_Quad = nR_Quad.readValues;
voltage_Quad = Values_Quad.v;
current_Quad = Values_Quad.I;
recovery_Quad = Values_Quad.u;


SR_AAC = SpikeReader('../results/spk_CA3_Axo_Axonic.dat');
spkData_AAC = SR_AAC.readSpikes(-1); % binWindowMs

SR_BC = SpikeReader('../results/spk_CA3_Basket.dat');
spkData_BC = SR_BC.readSpikes(-1); % binWindowMs

SR_BC_CCK = SpikeReader('../results/spk_CA3_BC_CCK.dat');
spkData_BC_CCK = SR_BC_CCK.readSpikes(-1); % binWindowMs

SR_Bis = SpikeReader('../results/spk_CA3_Bistratified.dat');
spkData_Bis = SR_Bis.readSpikes(-1); % binWindowMs

SR_Ivy = SpikeReader('../results/spk_CA3_Ivy.dat');
spkData_Ivy = SR_Ivy.readSpikes(-1); % binWindowMs

SR_MFA = SpikeReader('../results/spk_CA3_MFA_ORDEN.dat');
spkData_MFA = SR_MFA.readSpikes(-1); % binWindowMs

SR_Py = SpikeReader('../results/spk_CA3_Pyramidal.dat');
spkData_Py = SR_Py.readSpikes(-1); % binWindowMs

SR_Quad = SpikeReader('../results/spk_CA3_QuadD_LM.dat');
spkData_Quad = SR_Quad.readSpikes(-1); % binWindowMs


%% init ConnectionMonitor

% CR_AAC_PD = ConnectionReader('../results/conn_CA3_Axo_Axonic_CA3_Pyramidal.dat');
% [allTimestamps, allWeights] = CR_AAC_PD.readWeights();

%% %create figure 3
% numNeurons = 75000;
% [NMsimData] = readNMsim('/home/song/CARLsim/projects/ca3_example_net/results',numNeurons);
% analysisCut = 1;
% tf = 10000;

% %className = PC;
% fileOutLoc = 'D:\baseline_results';
% createFigure3Plots(NMsimData,analysisCut,tf,fileOutLoc)

%% figure1 - connection
% figure(1)
% imagesc(reshape(allWeights(1,:), CR_AAC_PD.getNumNeuronsPost(), CR_AAC_PD.getNumNeuronsPre()) );
% xlabel('Axo Axonic neuron ID');
% ylabel('Pyramidal neuron ID');
% title('Axo-Pyra Connection');

%% figure2 - spike trains
fig2 = figure(2);
subplot_size = 9.5;
stim = [zeros(1,100),I_stim*ones(1,1000),zeros(1,9000)];
subplot(9,1,1)
%axes('Position', [0.1, 0.9, 0.8, 0.07]);
plot(stim,'r','LineWidth',1.5);
title('Injected current on CA3 Pyramidal','FontSize',subplot_size);
%xlabel('Time(ms)');
xlim([low,up]);
set(gca,'XAxisLocation','top');set(gca,'xtick',[]);

%ylabel('Current(pA)');
%legend('Current(pA)');

subplot(9,1,2)
%axes('Position', [0.1, 0.75, 0.8, 0.1]);
scatter(spkData_Py(1,:), spkData_Py(2,:),sz,'k','filled');
alpha(alp);
title('CA3 Pyramidal','FontSize',subplot_size);
xlim([low,up]);
set(gca,'XAxisLocation','top');set(gca,'xtick',[]);
%xlabel('Time(ms)');
%ylabel('Neuron ID');

subplot(9,1,3)
%plot(spkData_BC, '.k');
%axes('Position', [0.1, 0.6, 0.8, 0.1]);
scatter(spkData_BC(1,:), spkData_BC(2,:),sz,'k','filled');
alpha(alp);
title('CA3 Basket','FontSize',subplot_size);
xlim([low,up]);
set(gca,'XAxisLocation','top');set(gca,'xtick',[]);
%xlabel('Time(ms)');
%ylabel('Neuron ID');

subplot(9,1,4)
%plot(spkData_BC_CCK, '.k');
%axes('Position', [0.1, 0.45, 0.8, 0.1]);
scatter(spkData_BC_CCK(1,:), spkData_BC_CCK(2,:),sz,'k','filled');
alpha(alp);
title('CA3 BC CCK','FontSize',subplot_size);
xlim([low,up]);
set(gca,'XAxisLocation','top');set(gca,'xtick',[]);
%xlabel('Time(ms)');
%ylabel('Neuron ID');

subplot(9,1,5)
%plot(spkData_Bis, '.k');
%axes('Position', [0.1, 0.3, 0.8, 0.1]);
scatter(spkData_Bis(1,:), spkData_Bis(2,:),sz,'k','filled');
alpha(alp);
title('CA3 Bistratified','FontSize',subplot_size);
xlim([low,up]);
set(gca,'XAxisLocation','top');set(gca,'xtick',[]);
%xlabel('Time(ms)');
%ylabel('Neuron ID');

subplot(9,1,6)
%plot(spkData_Ivy(1,:), spkData_Ivy(2,:), '.k');
%axes('Position', [0.1, 0.15, 0.8, 0.1]);
scatter(spkData_Ivy(1,:), spkData_Ivy(2,:),sz,'k','filled');
alpha(alp);
title('CA3 Ivy','FontSize',subplot_size);
xlim([low,up]);
set(gca,'XAxisLocation','top');set(gca,'xtick',[]);
%xlabel('Time(ms)');
%ylabel('Neuron ID');

subplot(9,1,7)
%plot(spkData_MFA(1,:), '.k');
%axes('Position', [0.1, 0.3, 0.8, 0.1]);
scatter(spkData_MFA(1,:), spkData_MFA(2,:),sz,'k','filled');
alpha(alp);
title('CA3 MFA ORDEN','FontSize',subplot_size);
xlim([low,up]);
set(gca,'XAxisLocation','top');set(gca,'xtick',[]);
%xlabel('Time(ms)');
%ylabel('Neuron ID');

subplot(9,1,8)
%axes('Position', [0.1, 0.2, 0.8, 0.1]);
scatter(spkData_AAC(1,:), spkData_AAC(2,:),sz,'k','filled');
alpha(alp);
title('CA3 Axo axonic','FontSize',subplot_size);
xlim([low,up]);
set(gca,'XAxisLocation','top');set(gca,'xtick',[]);
%xlabel('Time(ms)');
%ylabel('Neuron ID');

subplot(9,1,9)
%plot(spkData_Quad, '.k');
%axes('Position', [0.1, 0.1, 0.8, 0.1]);
scatter(spkData_Quad(1,:), spkData_Quad(2,:),sz,'k','filled');
alpha(alp);
title('CA3 QuadD LM','FontSize',subplot_size);
xlim([low,up]);
%xlabel('Time(ms)');
%ylabel('Neuron ID');

%sgtitle('CA3 Spike train','FontSize',14);
han=axes(fig2,'visible','off'); 
han.Title.Visible='on';
han.XLabel.Visible='on';
han.YLabel.Visible='on';
ylabel(han,'Neuron ID','FontSize',12);
xlabel(han,'Time(ms)','FontSize',12);
%title(han,'CA3 Spike train','FontSize',14);