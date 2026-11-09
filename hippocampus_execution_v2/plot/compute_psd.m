function [f, Pxx] = compute_psd(x, fs)
    % Returns frequency vector f (Hz) and power spectral density Pxx.
    % Welch is active by default. FFT method is included but commented out.

    if isempty(x) || numel(x) < 8
        f = []; Pxx = [];
        return;
    end

    x = double(x(:));
    x = x - mean(x);

%     ---------------- Periodogram (manually code it. Don't use MATLAB built-in periodogram function as c++ don't have)
%     n = numel(x);
%     w = hann(n);
%     xw = x .* w;
%     X = fft(xw);
%     P2 = (abs(X).^2) / (fs * sum(w.^2));
%     P1 = P2(1:floor(n/2)+1);
%     P1(2:end-1) = 2*P1(2:end-1);
%     f = fs*(0:floor(n/2)) / n;
%     Pxx = P1;
%     return;

    % ---------------- Welch method (more stable) ----------------
    
    n = numel(x);
    nperseg = min(max(64, floor(n/4)), n);
    noverlap = floor(nperseg/2);
    nfft = 1024; % 1024; match python and c++
    [Pxx, f] = pwelch(x, hann(nperseg), noverlap, nfft, fs);%one-side power

    % -- normalize PSD such that the area under PSD is 1
    area = trapz(f, Pxx);
    if isfinite(area) && area > 0
        Pxx = Pxx / area;
    else
        Pxx(:) = NaN;
    end

end