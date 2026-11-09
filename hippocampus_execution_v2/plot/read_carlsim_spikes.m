function spikes = read_carlsim_spikes(filename)
% Read the known CARLsim v0.2 format used by this project's supplied files.
% Little-endian binary: 20-byte header followed by pairs of int32 values.
% Header: int32 signature, float32 version, three int32 grid dimensions.
% Returned rows: [time in milliseconds; zero-based neuron ID].
fid = fopen(filename, 'rb', 'ieee-le');
fseek(fid, 20, 'bof');
spikes = fread(fid, [2 Inf], 'int32=>double');
fclose(fid);
end
