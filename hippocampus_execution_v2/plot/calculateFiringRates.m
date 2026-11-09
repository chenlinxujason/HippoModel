function FiringRates = calculateFiringRates(spkData, low, up)
    % spkData: [2 x N], row1=time(ms), row2=neuronID (0-based, CARLsim style)
    % Computes firing rate (Hz) per neuron within [low, up).
    % FIXED: denominator uses (up-low), not (lastSpike-firstSpike).
    % Default behavior: keep ACTIVE neurons only.

    if isempty(spkData)
        FiringRates = [];
        return;
    end

    % restrict window
    mask   = (spkData(1,:) >= low) & (spkData(1,:) < up);
    spkWin = spkData(:, mask);

    % If no spikes in window, then there are no active neurons.
    if isempty(spkWin)
        FiringRates = [];
        return;
    end

    % correct observation period in seconds
    Tsec = (up - low) / 1000;
    if Tsec <= 0
        error('calculateFiringRates: invalid window (up must be > low).');
    end
    invT = 1 / Tsec;

    % count spikes per neuron efficiently
    ids = spkWin(2,:);
    
%     maxID = max(ids);% old looks correct but might wrong
    maxID = max(spkData(2,:));

    counts = accumarray(ids(:) + 1, 1, [maxID + 1, 1], @sum, 0);  % includes IDs 0..maxID

    FiringRates = counts * invT;          % Hz, includes silent=0 for IDs present in 0..maxID
    
    FiringRates = FiringRates(FiringRates > 0);   % ACTIVE neurons only

    % ---- To INCLUDE silent neurons (comment OUT the line above) ----
    % FiringRates = FiringRates;  % keep zeros (silent neurons) as well
end
