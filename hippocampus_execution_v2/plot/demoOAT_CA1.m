clear
clc
close all

% Open this script in MATLAB and click Run.
% All eight populations require the spike/location pairs listed in README.md.
ca1Names = {'PC','AAC','BC','BCCCK','BisC','OLM','TL','NG'};

plot_dir = fileparts(mfilename('fullpath'));
project_dir = fileparts(plot_dir);
addpath(plot_dir);
spike_dir = fullfile(project_dir, 'results', 'CA1');
location_dir = fullfile(project_dir, 'locations', 'CA1');

%% Settings: time in milliseconds, distance in mm
low = 10000; up = 13000;       % Raster and correlation window
frlow = 10000; frhigh = 20000; % Firing-rate and PSD window
binMS = 5;
sres = 0.05;
twidth = 1500;
ymin = 0; ymax = 10;
maxDist = ymax;
Nslice_psd = 200;
edgesY_psd = linspace(ymin, ymax, Nslice_psd + 1);

sz = 1;
title_size = 18;
num_ticks = 6;
tick_positions = linspace(low, up, num_ticks);
tick_labels = arrayfun(@num2str, linspace(low/1000, up/1000, num_ticks), ...
    'UniformOutput', false);
rasterAlpha = struct('PC',0.35, 'AAC',0.30, 'BC',0.08, 'BCCCK',0.40, ...
    'BisC',0.50, 'OLM',0.10, 'TL',0.90, 'NG',0.45);
nTypes = numel(ca1Names);
ca1FRBins = repmat(20, 1, nTypes);

%% Load and analyze each selected population
% All numerical helpers are the original versions.
ca1SpikeTimes = cell(1, nTypes);
ca1SpikeY = cell(1, nTypes);
ca1FR = cell(1, nTypes);
ca1CC = cell(1, nTypes);
ca1PsdF = cell(1, nTypes);
ca1PsdP = cell(1, nTypes);

for k = 1:nTypes
    name = ca1Names{k};
    location_file = fullfile(location_dir, ['locs_CA1' name '.dat']);
    spikes = read_carlsim_spikes(fullfile(spike_dir, ['spk_CA1_' name '.dat']));
    [~, ~, ~, ca1SpikeY{k}, ca1SpikeTimes{k}] = AccessLocationData(location_file, spikes);
    ca1FR{k} = calculateFiringRates(spikes, frlow, frhigh);

    [ca1CC{k}, distAxis, lagAxis] = autocorr2d_pairwise(ca1SpikeTimes{k}, ca1SpikeY{k}, ...
        low, up, binMS, sres, ymin, ymax, maxDist, twidth);

    % PSD uses the original inclusive time window.
    mask = ca1SpikeTimes{k} >= frlow & ca1SpikeTimes{k} <= frhigh;
    [x_psd, fs_psd] = build_global_pop_timeseries( ...
        ca1SpikeTimes{k}(mask), ca1SpikeY{k}(mask), edgesY_psd, binMS);
    [ca1PsdF{k}, ca1PsdP{k}] = compute_psd(x_psd, fs_psd);
end

% Shared correlation color limits across the selected populations.
allAbs = abs(vertcat(ca1CC{:}));
allAbs = allAbs(isfinite(allAbs));
cAbs = prctile(allAbs, 99);
if isempty(cAbs) || ~isfinite(cAbs) || cAbs <= 0, cAbs = 1e-3; end
climAbs = [0 cAbs];

%% Figure 7: raster (PC spans four rows; each other population spans one)
raster_heights = 1 + 3*strcmp(ca1Names, 'PC');
raster_ends = cumsum(raster_heights);
raster_starts = raster_ends - raster_heights + 1;
figure(7); clf;
set(gcf, 'Units', 'normalized', 'Position', [0.12, 0.05, 0.55, 0.88]);

for k = 1:nTypes
    subplot(sum(raster_heights), 1, raster_starts(k):raster_ends(k));
    scatter(ca1SpikeTimes{k}, ca1SpikeY{k}, sz, 'k', 'filled');
    alpha(rasterAlpha.(ca1Names{k}));
    xlim([low up]); ylim([ymin ymax]);
    ax = gca;
    ax.Box = 'off';
    ax.FontSize = 12;
    ylabel(ca1Names{k}, 'FontSize', 14, 'FontWeight', 'normal', 'Color', 'k');
    if k < nTypes
        ax.XTick = [];
    else
        xticks(tick_positions);
        xticklabels(tick_labels);
        xlabel('Time (sec)', 'FontSize', 17);
    end
end

%% Figure 8: firing-rate histogram, pairwise correlation, and PSD
figure(8); clf;
set(gcf, 'Units', 'normalized', 'Position', [0.02, 0.05, 0.82, 0.88]);
textStyle = {'Units','normalized', 'Color','k', 'Clipping','off'};
tickStyle = [textStyle, {'HorizontalAlignment','center', ...
    'VerticalAlignment','top', 'FontSize',12}];
labelStyle = [textStyle, {'HorizontalAlignment','center', ...
    'VerticalAlignment','top', 'FontSize',15}];

for k = 1:nTypes
    axFR = subplot(nTypes, 3, (k-1)*3 + 1);
    data = ca1FR{k};
    data = data(isfinite(data));
    if isempty(data)
        meanFR = NaN;
        xlim([0 1]); ylim([0 1]);
    else
        histogram(data, ca1FRBins(k), 'FaceColor', [0.7 0.7 0.7], ...
            'EdgeColor', 'none', 'LineStyle', 'none');
        meanFR = mean(data);
    end
    text(-0.08, 0.5, ca1Names{k}, textStyle{:}, 'Rotation', 90, ...
        'HorizontalAlignment', 'center', 'VerticalAlignment', 'middle', ...
        'FontSize', title_size);
    text(0.88, 0.85, sprintf('%.2f', meanFR), textStyle{:}, ...
        'HorizontalAlignment', 'right', 'VerticalAlignment', 'top', ...
        'FontSize', title_size);

    axCC = subplot(nTypes, 3, (k-1)*3 + 2);
    imagesc(lagAxis, distAxis, abs(ca1CC{k}));
    axis xy;
    caxis(climAbs);
    xlim([-1500 1500]); ylim([-5 5]);

    axPSD = subplot(nTypes, 3, (k-1)*3 + 3);
    validIdx = ca1PsdF{k} > 0 & ca1PsdP{k} > 0;
    loglog(ca1PsdF{k}(validIdx), ca1PsdP{k}(validIdx), 'k', 'LineWidth', 0.5);
    xlim([0.2 60]);
    set([axFR axCC axPSD], 'Box', 'off', 'XColor', 'none', 'YColor', 'none', ...
        'XTick', [], 'YTick', [], 'TickLength', [0 0]);

    if k == 1
        title(axFR, 'FR', 'FontSize', title_size);
        title(axCC, 'Pairwise CC', 'FontSize', title_size);
        title(axPSD, 'PSD', 'FontSize', title_size);
    end
    if k == nTypes
        text(axFR, 0.5, -0.35, 'FR (Hz)', labelStyle{:});
        for t = [-1500 -750 0 750 1500]
            text(axCC, (t+1500)/3000, -0.16, sprintf('%g', t), tickStyle{:});
        end
        text(axCC, 0.5, -0.43, 'Lag (ms)', labelStyle{:});
        for t = [0.2 1 10 60]
            xPosition = (log10(t)-log10(0.2))/(log10(60)-log10(0.2));
            text(axPSD, xPosition, -0.16, sprintf('%g', t), tickStyle{:});
        end
        text(axPSD, 0.5, -0.43, 'Freq (Hz)', labelStyle{:});
    end
end

% Optional: save the open figures after inspecting them.
% saveas(figure(7), fullfile(project_dir, 'CA1_raster.png'));
% saveas(figure(8), fullfile(project_dir, 'CA1_statistics.png'));
