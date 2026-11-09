function [dist_cc, distAxis, lagAxis] = autocorr2d_pairwise(spkT, spkY, low, up, tres, sres, ymin, ymax, maxDist, twidth)
% Python code logic (pair-based normalization):
%   - bin spikes into yMat(ybin, tbin) counts
%   - for each pair of spatial bins (i<j):
%       x = yMat(i,:) - mean(x);  y = yMat(j,:) - mean(y)
%       cc = xcorr(x,y,'same') / (N * std(x) * std(y))
%   - accumulate cc by distance bin, then average

    % Restrict time window
    m = (spkT >= low) & (spkT <= up);
    spkT = spkT(m);
    spkY = spkY(m);

    % distance bins
    snum = round(maxDist / sres);
    distAxis = ((-snum):(snum-1)) * sres;

    % time bins (fixed to [low, up])
    t0 = low;
    t1 = up;
    edgesT = t0:tres:(t1+tres);
    tnum = numel(edgesT) - 1;              % N in python (len(x))
    lagAxisFull = ((-floor(tnum/2)):(ceil(tnum/2)-1)) * tres;

    % outputs init
    dist_cc = zeros(2*snum, tnum);
    dist_nn = zeros(2*snum, 1);

    % if empty
    if isempty(spkT)
        if ~isempty(twidth) && twidth > 0 && twidth < (tnum*tres/2)
            keep = (lagAxisFull >= -twidth) & (lagAxisFull <= twidth);
            dist_cc = dist_cc(:, keep);
            lagAxis = lagAxisFull(keep);
        else
            lagAxis = lagAxisFull;
        end
        return;
    end

    % spatial bins
    edgesY = ymin:sres:ymax;
    if edgesY(end) < ymax
        edgesY(end+1) = ymax;
    end
    nY = numel(edgesY) - 1;
    yCenters = 0.5 * (edgesY(1:end-1) + edgesY(2:end));   % mm

    % build binned count matrix yMat [nY x tnum]
    yMat = zeros(nY, tnum);

    ybin = discretize(spkY, edgesY);
    tbin = discretize(spkT, edgesT);
    valid = ~isnan(ybin) & ~isnan(tbin);
    ybin = ybin(valid);
    tbin = tbin(valid);

    idx = sub2ind([nY, tnum], ybin(:), tbin(:));
    yMat(:) = accumarray(idx, 1, [nY*tnum, 1], @sum, 0);

    % precompute demeaned signals + std for each row (python does per-pair,
    % but std(x) is independent of pair once demeaned)
    xDemean = yMat - mean(yMat, 2);      % [nY x tnum]
    xStd    = std(xDemean, 0, 2);        % [nY x 1]

    goodRow = (xStd > 0) & isfinite(xStd);

    % FFT prep for cross-corr (linear)
    nfft = 2^nextpow2(2*tnum - 1);

    % Precompute FFTs of demeaned rows (faster; normalization still pair-based)
    XF = zeros(nY, nfft);
    for i = 1:nY
        if ~goodRow(i), continue; end
        XF(i,:) = fft(double(xDemean(i,:)), nfft);
    end

    % indices for "same" extraction consistent with your lagAxisFull definition
    % Full linear xcorr length = 2*tnum-1, with zero-lag at index tnum
    left  = floor(tnum/2);
    right = ceil(tnum/2)-1;
    same_idx = (tnum-left) : (tnum+right);   % length tnum

    for i = 1:nY-1
        if ~goodRow(i), continue; end
        for j = (i+1):nY
            if ~goodRow(j), continue; end

            dist = yCenters(i) - yCenters(j);
            if abs(dist) > maxDist
                continue;
            end

            % linear cross-correlation via FFT:
            % r_xy = ifft( FFT(x) * conj(FFT(y)) )
            r_circ = real(ifft( XF(i,:) .* conj(XF(j,:)) ));

            % convert to linear xcorr sequence length 2*tnum-1:
            % r_lin = [negative lags, zero..positive lags]
            r_pos = r_circ(1:tnum);                 % lags 0..tnum-1
            r_neg = r_circ(nfft-(tnum-2):nfft);     % lags -(tnum-2)..-1
            r_lin = [r_neg, r_pos];                 % length 2*tnum-1

            % take "same" window (length tnum), centered
            cc_same = r_lin(same_idx);

            % --- Python-like normalization ---
            % cc / len(x) / (std_x * std_y)
            cc = cc_same / (tnum * xStd(i) * xStd(j));

            % accumulate into distance bin
            k = floor((dist + maxDist) / sres) + 1;   % 1..2*snum
            if k >= 1 && k <= 2*snum
                dist_cc(k,:) = dist_cc(k,:) + cc;
                dist_nn(k) = dist_nn(k) + 1;

                % symmetric update
                k2 = floor((-dist + maxDist) / sres) + 1;
                if k2 >= 1 && k2 <= 2*snum
                    dist_cc(k2,:) = dist_cc(k2,:) + cc;
                    dist_nn(k2) = dist_nn(k2) + 1;
                end
            end
        end
    end

    % average
    for k = 1:(2*snum)
        if dist_nn(k) > 0
            dist_cc(k,:) = dist_cc(k,:) / dist_nn(k);
        end
    end

    % crop lag window to +/-twidth if requested
    if ~isempty(twidth) && twidth > 0 && twidth < (tnum*tres/2)
        keep = (lagAxisFull >= -twidth) & (lagAxisFull <= twidth);
        dist_cc = dist_cc(:, keep);
        lagAxis = lagAxisFull(keep);
    else
        lagAxis = lagAxisFull;
    end
end