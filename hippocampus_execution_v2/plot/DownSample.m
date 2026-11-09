function [selected_Locs_x, selected_Locs_y, spk_x, spk_y, spkTimes, spkIds] = DownSample(locs, spkData, ratio)% DOWNSAMPLE  Evenly samples neurons across the dorsal-ventral axis,
%             including silent neurons by default.
%
%   locs      - filename (e.g., 'locs_LEC.dat') containing x,y positions
%   spkData   - 2×N matrix of spike events [time; neuronIndex]
%   ratio     - reduction factor (e.g., ratio=100 means ~1/100 neurons sampled)
%
% NOTE:
%   By default, we include all neurons.
%
%   Uncomment the following line to exclude neurons that never fired:
%       all_neuron_indices = intersect(all_neuron_indices, unique(spkData(2,:)));
%
%   Uncomment the following line to perform purely random sampling:
%       sampled_neuron_indices = randsample(all_neuron_indices, num_to_sample);

    %% 1) Read the full location data for all neurons
    fileID = fopen(locs, 'rb');
    if fileID == -1
        error('Failed to open file: %s', locs);
    end
    locsData = fread(fileID, '*single');
    fclose(fileID);

    % Reshape into 2 x N array: row 1 = x-coords, row 2 = y-coords
    numPoints = length(locsData) / 2;
    locsData  = reshape(locsData, 2, numPoints);
    all_Locs_x = locsData(1, :);
    all_Locs_y = locsData(2, :);

    %% 2) Define the full set of neuron indices (including silent)
    % CARLsim uses 0-based indices (0 to numPoints-1)
    all_neuron_indices = 0 : (numPoints - 1);

    %% Option: Uncomment to exclude neurons that never fired:
    % all_neuron_indices = intersect(all_neuron_indices, unique(spkData(2,:)));

    %% 3) Sort neurons by dorsal-ventral coordinate (all_Locs_y)
    [~, sortedIdx] = sort(all_Locs_y);  % ascending order of DV position
    sortedNeurons = all_neuron_indices(sortedIdx);

    %% 4) Evenly pick ~ (numPoints / ratio) neurons using linspace
    num_to_sample = max(1, round(numPoints / ratio));
    % Evenly spaced indices (as positions in the sorted list)
    even_indices = round(linspace(1, numel(sortedNeurons), num_to_sample));
    sampled_neuron_indices = sortedNeurons(even_indices);

    %% Option: Uncomment to perform purely random sampling instead of even sampling:
    % sampled_neuron_indices = randsample(all_neuron_indices, num_to_sample);

   %% 5) Filter the original spkData
    mask = ismember(spkData(2, :), sampled_neuron_indices);
    filtered_spkData = spkData(:, mask);
    
    % NEW: Extract IDs (1-based for MATLAB consistency)
    spkIds = filtered_spkData(2, :) + 1; 

    %% 6) Use AccessLocationData
    [selected_Locs_x, selected_Locs_y, spk_x, spk_y, spkTimes] = ...
        AccessLocationData(locs, filtered_spkData);

end
