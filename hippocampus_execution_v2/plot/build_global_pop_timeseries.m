function [x_global, fs] = build_global_pop_timeseries(spkT, spkY, edgesY, binMS)
    % Build slice population counts per bin, then sum across slices.
    % Uses the SAME binning style as correlation code.

    if isempty(spkT)
        x_global = [];
        fs = 1000 / binMS;
        return;
    end

    N = numel(edgesY) - 1;
    t0 = min(spkT);
    t1 = max(spkT);

    edgesT = t0:binMS:(t1+binMS);
    nbins  = numel(edgesT) - 1;

    X = zeros(N, nbins);
    for s = 1:N
        inSlice = (spkY >= edgesY(s)) & (spkY < edgesY(s+1));
        ti = spkT(inSlice);
        if isempty(ti), continue; end
        ti = ti(ti >= edgesT(1) & ti < edgesT(end));
        if isempty(ti), continue; end
        X(s,:) = histcounts(ti, edgesT);
    end

    x_global = sum(X, 1);        % 1 x nbins
    fs = 1000 / binMS;           % Hz
end

