function [Locs_x,Locs_y,Spk_x,Spk_y,spkTimes] = AccessLocationData(filename,spkData)

%% filename: location data. Example: locsMEC = 'locs_MEC.dat';

%% Read location data
 fileID = fopen(filename, 'rb');

 % Check if file opening succeeded
 if fileID == -1
     error('Failed to open file: %s', filename);
 end
    
 % Read the data as single precision floats
 locsData = fread(fileID, '*single');

 % Reshape the data. Since each (x,y) is consecutive, we split them accordingly.
 % locs file need to be: [x1, y1, x2, y2, x3, y3, ...] in float32
 numPoints = length(locsData) / 2; % Total number of points (each point has an x and a y)
 locs = reshape(locsData, 2, numPoints); % Reshape data into a 2-row matrix
 Locs_x = locs(1,:);
 Locs_y = locs(2,:);

 fclose(fileID);% Close the file

%% Seperate location data
spkIndices = spkData(2,:) + 1;%REMOVE 0
validIndices = spkIndices > 0 & spkIndices <= numPoints;
validSpkIndices = spkIndices(validIndices);
spkTimes = spkData(1, validIndices);
Spk_x = Locs_x(validSpkIndices);
Spk_y = Locs_y(validSpkIndices);