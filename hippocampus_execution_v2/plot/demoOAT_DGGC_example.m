clear
clc
close all

% Open this file in MATLAB and click Run.
% Edit these folders if your spike/location files are stored elsewhere.
matlab_dir = fileparts(mfilename('fullpath'));
project_dir = fileparts(matlab_dir);
addpath(matlab_dir);
spike_dir = fullfile(project_dir, 'results');
location_dir = fullfile(project_dir, 'locations');

% This example needs only the two included DGGC files.
location_file = fullfile(location_dir, 'locs_DGGC.dat');
spikes = read_carlsim_spikes(fullfile(spike_dir, 'spk_DG_GC.dat'));
[~, ~, ~, spike_y, spike_time] = AccessLocationData(location_file, spikes);

% Exact active settings from the supplied DG script. The 40 s example covers
% these windows. A 1200 s place-cell run requires separate trajectory analysis.
low = 10000; up = 13000;
frlow = 10000; frhigh = 20000;
bin_ms = 5; spatial_bin_mm = 0.05;
ymin = 0; ymax = 10; max_distance = 10; half_lag_ms = 1500;
downsample_ratio = 20; psd_slices = 200;
firing_rates = calculateFiringRates(spikes, frlow, frhigh);
[~, ~, ~, corr_y, corr_time] = DownSample(location_file, spikes, downsample_ratio);
[correlation, distance, lag] = autocorr2d_pairwise(corr_time, corr_y, ...
    low, up, bin_ms, spatial_bin_mm, ymin, ymax, max_distance, half_lag_ms);
mask = spike_time >= frlow & spike_time <= frhigh;
[population_series, fs] = build_global_pop_timeseries(spike_time(mask), spike_y(mask), ...
    linspace(ymin, ymax, psd_slices+1), bin_ms);
[frequency, psd] = compute_psd(population_series, fs);

figure(7); clf;
set(gcf, 'Color', 'w', 'Position', [100 100 1000 430]);
scatter(spike_time/1000, spike_y, 3, 'k', 'filled');
alpha(0.25);
xlim([low up]/1000); ylim([ymin ymax]);
xlabel('Time (s)'); ylabel('Dorso-ventral position (mm)'); title('DG GC');
figure(8); clf;
set(gcf, 'Color', 'w', 'Position', [100 100 1300 390]);
subplot(1, 3, 1);
histogram(firing_rates, 20, 'FaceColor', [0.7 0.7 0.7], 'EdgeColor', 'none');
xlabel('Firing rate (Hz)'); ylabel('Active neurons');
title(sprintf('Mean %.4f Hz', mean(firing_rates)));
subplot(1, 3, 2);
imagesc(lag, distance, abs(correlation)); axis xy;
allAbs = abs(correlation(:));
allAbs = allAbs(isfinite(allAbs));
cAbs = prctile(allAbs, 99);
if isempty(cAbs) || ~isfinite(cAbs) || cAbs <= 0, cAbs = 1e-3; end
climAbs = [0 cAbs];
caxis(climAbs); xlim([-1500 1500]); ylim([-5 5]);
xlabel('Lag (ms)'); ylabel('Distance (mm)'); title('|Pairwise correlation|'); colorbar;
subplot(1, 3, 3);
mask = frequency > 0 & psd > 0;
loglog(frequency(mask), psd(mask), 'k', 'LineWidth', 0.5);
xlim([0.2 60]); xlabel('Frequency (Hz)'); ylabel('Normalized PSD'); title('DG GC spectrum');


% Results remain in the workspace: firing_rates, correlation, distance, lag,
% frequency, and psd. The firing-rate mean includes active neurons only.
% Optional: save the open figures after inspecting them.
% saveas(figure(7), fullfile(project_dir, 'DGGC_raster.png'));
% saveas(figure(8), fullfile(project_dir, 'DGGC_statistics.png'));
