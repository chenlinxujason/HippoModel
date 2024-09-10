clear;
close all;
clc;

neuron_names = {'PC','BC','AAC','BCCCK','BisC','OLM','TL','MFA'};

%% CA3 local initial
% Connection_types = {
%     'PC-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,   0.47, 36.2, 47.0, 1.0, 0.68;
%     'PC-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,     1.391, 38.0, 89.4, 1.0, 0.686;
%     'PC-AAC', 165, -57.1, -51.72, 3.96, 27.8, 0.005, 8.68, -73.97, 15,      1.285, 12.0, 78.3, 1.0, 0.686;
%     'PC-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,     1.04, 1.2, 50.1, 1.0, 0.554;%1.045 slow
%     'PC-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,   1.0, 22.0, 78.81, 1.0, 0.81;
%     'PC-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,       0.952, 25.5, 78.0, 1.0, 0.9;
%     'PC-TL', 227, -57.87, -37.93, 2.64, 4.77, 0.009, 3.59, -45.87, 2,       3.02, 1.0, 37.0, 1.0, 0.554;
%     'PC-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,      1.42, 8.3, 48.26, 1.0, 0.81;
%     
%     'BC-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,   0.69, 7.16, 633.2, 1.0, 0.0;
%     'BC-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,     0.0, 0.0, 0.0, 0.0, 0.0;
%     'BC-AAC', 165, -57.1, -51.72, 3.96, 27.8, 0.005, 8.68, -73.97, 15,      5.4, 33.2, 433.2, 1.0, 0.0;
%     'BC-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,     0.0, 0.0, 0.0, 0.0, 0.0;
%     'BC-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,   0.0, 0.0, 0.0, 0.0, 0.0;
%     'BC-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,       0.0, 2.0, 13.2, 1.0, 0.15;
%     'BC-TL', 227, -57.87, -37.93, 2.64, 4.77, 0.009, 3.59, -45.87, 2,       0.0, 0.0, 0.0, 0.0, 0.0;
%     'BC-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,      1.425, 16.1, 417.5, 1.0, 0.0;
%     
%     'AAC-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,  0.69, 7.16, 633.2, 1.0, 0.0;
%     'AAC-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,    0.0, 0.0, 0.0, 0.0, 0.0;
%     'AAC-AAC', 165, -57.1, -51.72, 3.96, 27.8, 0.005, 8.68, -73.97, 15,     0.0, 0.0, 0.0, 0.0, 0.0;
%     'AAC-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,    0.0, 0.0, 0.0, 0.0, 0.0;
%     'AAC-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,  0.0, 0.0, 0.0, 0.0, 0.0;
%     'AAC-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,      0.0, 0.0, 0.0, 0.0, 0.0;
%     'AAC-TL', 227, -57.87, -37.93, 2.64, 4.77, 0.009, 3.59, -45.87, 2,      0.0, 0.0, 0.0, 0.0, 0.0;
%     'AAC-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,     0.0, 0.0, 0.0, 0.0, 0.0;
%     
%     'BCCCK-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138, 0.69, 7.16, 633.2, 1.0, 0.05;
%     'BCCCK-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,   3.28, 45.4, 504.0, 1.0, 0.01;
%     'BCCCK-AAC', 165, -57.1, -51.72, 3.96, 27.8, 0.005, 8.68, -73.97, 15,    5.4, 33.2, 433.2, 1.0, 0.05;
%     'BCCCK-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,   0.0, 0.0, 0.0, 0.0, 0.0;
%     'BCCCK-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19, 0.0, 0.0, 0.0, 0.0, 0.0;
%     'BCCCK-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,     0.0, 0.0, 0.0, 0.0, 0.0;
%     'BCCCK-TL', 227, -57.87, -37.93, 2.64, 4.77, 0.009, 3.59, -45.87, 2,     0.0, 0.0, 0.0, 0.0, 0.0;
%     'BCCCK-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,    1.425, 16.1, 417.5, 1.0, 0.05;
%     
%     'BisC-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,  0.69, 7.16, 633.2, 1.0, 0.0;
%     'BisC-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,    3.28, 45.4, 504.0, 1.0, 0.01;
%     'BisC-AAC', 165, -57.1, -51.72, 3.96, 27.8, 0.005, 8.68, -73.97, 15,     5.4, 33.2, 433.2, 1.0, 0.0;
%     'BisC-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,    1.356, 18.78, 318.1, 1.0, 0.0167;
%     'BisC-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,  3.455, 33.0, 480.9, 1.0, 0.0125;
%     'BisC-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,      1.46, 34.73, 447.5, 1.0, 0.0167;
%     'BisC-TL', 227, -57.87, -37.93, 2.64, 4.77, 0.009, 3.59, -45.87, 2,      0.0, 0.0, 0.0, 0.0, 0.0;
%     'BisC-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,     1.425, 16.1, 417.5, 1.0, 0.0;
%     
%     'OLM-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,   0.69, 7.16, 633.2, 1.0, 0.0;
%     'OLM-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,     3.28, 45.4, 504.0, 1.0, 0.01;
%     'OLM-AAC', 165, -57.1, -51.72, 3.96, 27.8, 0.005, 8.68, -73.97, 15,      5.4, 33.2, 433.2, 1.0, 0.0;
%     'OLM-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,     1.356, 18.78, 318.1, 1.0, 0.0167;
%     'OLM-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,   3.455, 33.0, 480.9, 1.0, 0.0125;
%     'OLM-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,       1.46, 34.73, 447.5, 1.0, 0.0167;
%     'OLM-TL', 227, -57.87, -37.93, 2.64, 4.77, 0.009, 3.59, -45.87, 2,       0.0, 0.0, 0.0, 0.0, 0.0;
%     'OLM-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,      0.0, 0.0, 0.0, 0.0, 0.0;
%     
%     'TL-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,    0.69, 7.16, 633.2, 1.0, 0.0;
%     'TL-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,      3.28, 45.4, 504.0, 1.0, 0.01;
%     'TL-AAC', 165, -57.1, -51.72, 3.96, 27.8, 0.005, 8.68, -73.97, 15,       5.4, 33.2, 433.2, 1.0, 0.0;
%     'TL-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,      1.356, 18.78, 318.1, 1.0, 0.0167;
%     'TL-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,    3.455, 33.0, 480.9, 1.0, 0.0125;
%     'TL-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,        1.46, 34.73, 447.5, 1.0, 0.0167;
%     'TL-TL', 227, -57.87, -37.93, 2.64, 4.77, 0.009, 3.59, -45.87, 2,        0.0, 0.0, 0.0, 0.0, 0.0;
%     'TL-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,       0.0, 0.0, 0.0, 0.0, 0.0;
%     
%     'MFA-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,   0.69, 7.16, 633.2, 1.0, 0.0;
%     'MFA-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,     3.28, 45.4, 504.0, 1.0, 0.01;
%     'MFA-AAC', 165, -57.1, -51.72, 3.96, 27.8, 0.005, 8.68, -73.97, 15,      0.0, 0.0, 0.0, 0.0, 0.0;
%     'MFA-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,     0.0, 0.0, 0.0, 0.0, 0.0;
%     'MFA-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,   3.455, 33.0, 480.9, 1.0, 0.0125;
%     'MFA-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,       0.0, 0.0, 0.0, 0.0, 0.0;
%     'MFA-TL', 227, -57.87, -37.93, 2.64, 4.77, 0.009, 3.59, -45.87, 2,       0.0, 0.0, 0.0, 0.0, 0.0;
%     'MFA-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,      1.425, 16.1, 417.5, 1.0, 0.0;
% };

%% CA3 local Fine tune
Connection_types = {
    'PC-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,   0.75, 36.2, 47.0, 1.0, 0.68;
    'PC-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,     0.7, 38.0, 89.4, 1.0, 0.686;
    'PC-AAC', 165, -57.1, -51.72, 3.96, 27.8, 0.005, 8.68, -73.97, 15,      0.57, 12.0, 78.3, 1.0, 0.686;
    'PC-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,     2.96, 1.2, 50.1, 1.0, 0.554;%1.045 slow
    'PC-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,   0.8, 22.0, 78.81, 1.0, 0.81;
    'PC-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,       1.8, 25.5, 78.0, 1.0, 0.9;
    'PC-TL', 227, -57.87, -37.93, 2.64, 4.77, 0.009, 3.59, -45.87, 2,       0.45, 1.0, 37.0, 1.0, 0.554;
    'PC-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,      2.8, 8.3, 48.26, 1.0, 0.81;
    
    'BC-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,   0.1, 7.16, 633.2, 1.0, 0.0;
    'BC-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,     0.0, 0.0, 0.0, 0.0, 0.0;
    'BC-AAC', 165, -57.1, -51.72, 3.96, 27.8, 0.005, 8.68, -73.97, 15,      1.0, 33.2, 433.2, 1.0, 0.0;
    'BC-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,     0.0, 0.0, 0.0, 0.0, 0.0;
    'BC-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,   0.0, 0.0, 0.0, 0.0, 0.0;
    'BC-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,       0.0, 2.0, 13.2, 1.0, 0.15;
    'BC-TL', 227, -57.87, -37.93, 2.64, 4.77, 0.009, 3.59, -45.87, 2,       0.0, 0.0, 0.0, 0.0, 0.0;
    'BC-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,      0.3, 16.1, 417.5, 1.0, 0.0;
    
    'AAC-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,  0.1, 7.16, 633.2, 1.0, 0.0;
    'AAC-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,    0.0, 0.0, 0.0, 0.0, 0.0;
    'AAC-AAC', 165, -57.1, -51.72, 3.96, 27.8, 0.005, 8.68, -73.97, 15,     0.0, 0.0, 0.0, 0.0, 0.0;
    'AAC-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,    0.0, 0.0, 0.0, 0.0, 0.0;
    'AAC-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,  0.0, 0.0, 0.0, 0.0, 0.0;
    'AAC-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,      0.0, 0.0, 0.0, 0.0, 0.0;
    'AAC-TL', 227, -57.87, -37.93, 2.64, 4.77, 0.009, 3.59, -45.87, 2,      0.0, 0.0, 0.0, 0.0, 0.0;
    'AAC-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,     0.0, 0.0, 0.0, 0.0, 0.0;
    
    'BCCCK-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138, 0.12, 7.16, 633.2, 1.0, 0.05;
    'BCCCK-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,   0.8, 45.4, 504.0, 1.0, 0.01;
    'BCCCK-AAC', 165, -57.1, -51.72, 3.96, 27.8, 0.005, 8.68, -73.97, 15,    0.9, 33.2, 433.2, 1.0, 0.05;
    'BCCCK-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,   0.0, 0.0, 0.0, 0.0, 0.0;
    'BCCCK-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19, 0.0, 0.0, 0.0, 0.0, 0.0;
    'BCCCK-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,     0.0, 0.0, 0.0, 0.0, 0.0;
    'BCCCK-TL', 227, -57.87, -37.93, 2.64, 4.77, 0.009, 3.59, -45.87, 2,     0.0, 0.0, 0.0, 0.0, 0.0;
    'BCCCK-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,    0.5, 16.1, 417.5, 1.0, 0.05;
    
    'BisC-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,  0.1, 7.16, 633.2, 1.0, 0.0;
    'BisC-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,    1.0, 45.4, 504.0, 1.0, 0.01;
    'BisC-AAC', 165, -57.1, -51.72, 3.96, 27.8, 0.005, 8.68, -73.97, 15,     0.5, 33.2, 433.2, 1.0, 0.0;
    'BisC-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,    0.5, 18.78, 318.1, 1.0, 0.0167;
    'BisC-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,  0.57, 33.0, 480.9, 1.0, 0.0125;
    'BisC-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,      0.12, 34.73, 447.5, 1.0, 0.0167;
    'BisC-TL', 227, -57.87, -37.93, 2.64, 4.77, 0.009, 3.59, -45.87, 2,      0.0, 0.0, 0.0, 0.0, 0.0;
    'BisC-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,     0.3, 16.1, 417.5, 1.0, 0.0;
    
    'OLM-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,   0.1, 7.16, 633.2, 1.0, 0.0;
    'OLM-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,     1.0, 45.4, 504.0, 1.0, 0.01;
    'OLM-AAC', 165, -57.1, -51.72, 3.96, 27.8, 0.005, 8.68, -73.97, 15,      0.7, 33.2, 433.2, 1.0, 0.0;
    'OLM-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,     0.4, 18.78, 318.1, 1.0, 0.0167;
    'OLM-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,   0.3, 33.0, 480.9, 1.0, 0.0125;
    'OLM-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,       0.12, 34.73, 447.5, 1.0, 0.0167;
    'OLM-TL', 227, -57.87, -37.93, 2.64, 4.77, 0.009, 3.59, -45.87, 2,       0.0, 0.0, 0.0, 0.0, 0.0;
    'OLM-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,      0.0, 0.0, 0.0, 0.0, 0.0;
    
    'TL-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,    0.05, 7.16, 633.2, 1.0, 0.0;
    'TL-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,      0.5, 45.4, 504.0, 1.0, 0.01;
    'TL-AAC', 165, -57.1, -51.72, 3.96, 27.8, 0.005, 8.68, -73.97, 15,       0.3, 33.2, 433.2, 1.0, 0.0;
    'TL-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,      0.4, 18.78, 318.1, 1.0, 0.0167;
    'TL-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,    0.12, 33.0, 480.9, 1.0, 0.0125;
    'TL-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,        0.1, 34.73, 447.5, 1.0, 0.0167;
    'TL-TL', 227, -57.87, -37.93, 2.64, 4.77, 0.009, 3.59, -45.87, 2,        0.0, 0.0, 0.0, 0.0, 0.0;
    'TL-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,       0.0, 0.0, 0.0, 0.0, 0.0;
    
    'MFA-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,   0.1, 7.16, 633.2, 1.0, 0.0;
    'MFA-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,     0.5, 45.4, 504.0, 1.0, 0.01;
    'MFA-AAC', 165, -57.1, -51.72, 3.96, 27.8, 0.005, 8.68, -73.97, 15,      0.0, 0.0, 0.0, 0.0, 0.0;
    'MFA-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,     0.0, 0.0, 0.0, 0.0, 0.0;
    'MFA-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,   0.4, 33.0, 480.9, 1.0, 0.0125;
    'MFA-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,       0.0, 0.0, 0.0, 0.0, 0.0;
    'MFA-TL', 227, -57.87, -37.93, 2.64, 4.77, 0.009, 3.59, -45.87, 2,       0.0, 0.0, 0.0, 0.0, 0.0;
    'MFA-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,      0.3, 16.1, 417.5, 1.0, 0.0;
};



% Parameters common to all neurons
amp1 = 440; %external current at presynaptic neuron, pA
amp2 = 0; %external current at postsynaptic neuron, pA
Integrator = 2; % RK method
T = 1000; %1000ms
step = 0.1; % ms (0.2ms - iterate 5 times; 0.1ms - iterate 10 times)
n = round(T/step); % simulation time steps
PulseWidth = 0.9;
TTP = 0.1; %time to peak (sec) 0.1: TTP = 100ms; 0.0332: TTP = 33.2ms;0.011 - 11ms
t = step*(1:n);%correct!
STP_U = 0.45; % 0.45(STD,only Pyramidal) or 0.15(STF)
STP_tau_u = 50; % 50ms(STD,only Pyramidal) or 750ms(STF),tau_f,facilitation time constant
STP_tau_x = 750;  %750 ms(STD,only Pyramidal) or 50ms(STF),tau_d,depression time constant
I2 = amp2*t;
% fast_gain = 1.0;
% slow_gain = 1.0;
%
%% Use presynaptic spike as postsynaptic input
% pre_neuron =  CA1_Pyramidal;
% C1 = 334; vr1 = -69.36; vt1 = -53.22; k1 = 1.56; vpeak1 = 25.46;
% a1 = 0; b1 = -17.25; c1 = -60.22; d1 = 16;
% 
% [v1,u1,spike_trains1,I1] = ...
% izhikevich_presynaptic_neuron(Integrator,amp1,C1,vr1,vt1,k1,...
% vpeak1,a1,b1,c1,d1,T,step,PulseWidth);

%% Use single spike as postsynaptic input
% spike_amp = (1/step)+0.45; % spike modify 
% spike_trains1 = [zeros(1,(int32(TTP*n)-1)),spike_amp,...
%     zeros(1,int32(n-(TTP)*n))];


% Prepare the figure
figure;
num_connections = size(Connection_types, 1);
num_neurons = length(neuron_names); % Get number of neuron names

% Loop over all subplots
for i = 1:num_connections
    % Determine the subplot index
    subplot_index = i; % Each subplot corresponds to a different connection type
    
    % Subplot placement assuming 8 rows and as many columns as needed up to 6
    ax = subplot(8, 8, subplot_index);  % Capture the axis handle for later use
    C2 = Connection_types{i, 2};
    vr2 = Connection_types{i, 3};
    vt2 = Connection_types{i, 4};
    k2 = Connection_types{i, 5};
    vpeak2 = Connection_types{i, 6};
    a2 = Connection_types{i, 7};
    b2 = Connection_types{i, 8};
    c2 = Connection_types{i, 9};
    d2 = Connection_types{i, 10};
    Wt = Connection_types{i, 11};
    tau_fast = Connection_types{i, 12};
    tau_slow = Connection_types{i, 13};
    fast_gain = Connection_types{i, 14};
    slow_gain = Connection_types{i, 15};
    
    % Set connection-specific parameters
    connection_name = Connection_types{i, 1};
    if any(strcmp(connection_name, {'PC-PC', 'PC-BC', 'PC-AAC', 'PC-BCCCK', 'PC-BisC', 'PC-OLM', 'PC-TL', 'PC-MFA'}))
        conn_type = 1; % Excitatory
        V_rev_fast = 0;
        V_rev_slow = 0;
    else
        conn_type = 2; % Inhibitory
        V_rev_fast = -70;
        V_rev_slow = -90;
    end
    
    % Execute the neuron model (assuming izhikevich_postsynaptic_neuron function is defined)
    spike_amp = (1/step)+0.39; % spike modify 
    spike_trains1 = [zeros(1,(int32(TTP*n)-1)),spike_amp, zeros(1,int32(n-(TTP)*n))];

    w_fast = Wt*fast_gain;
    w_slow = Wt*slow_gain;

    [v2,u2,U,x,g_fast,g_slow,g_syn,I_fast,I_slow,I_syn,spike_trains2] = ...
    izhikevich_postsynaptic_neuron(Integrator,conn_type,spike_trains1,...
    STP_U,STP_tau_u,STP_tau_x,V_rev_fast,V_rev_slow,tau_fast,...
    tau_slow,w_fast,w_slow,C2,vr2,vt2,k2,vpeak2,a2,b2,c2,d2,T,step,I2);

    % Plotting
    if Wt == 0
        % Draw a horizontal line at y = 0 with given plot settings
        plot(t, zeros(size(t)), 'k', 'LineWidth', 3);  % Dashed black line at y = 0
        xlim([80, 280]); 
        ylim([-1, 1]);  % Set the y limits to keep the horizontal line visible
    else
        if any(strcmp(connection_name, {'PC-PC', 'PC-BC', 'PC-AAC', 'PC-BCCCK', 'PC-BisC', 'PC-OLM', 'PC-TL', 'PC-MFA'}))
            plot_color = 'r';  % Red color for excitatory
            line_width = 1.4;  % Standard line
        else
            plot_color = 'b';  % Blue color for inhibitory
            line_width = 1.4;  % Standard line
        end

        plot(t, v2, plot_color, 'LineWidth', line_width); 
        xlim([80, 280]); 
        ylim([min(v2)-0.15, max(v2)+0.15]);

     % Add the bar plot for each subplot as a custom "legend" if Wt is not 0
        if Wt ~= 0
            % Get the position of the current subplot
            pos = get(ax, 'Position');

            % Define the size of the custom bar plot legend
            legend_width = pos(3) * 0.25;  % Make the total legend width 40% of subplot width
            legend_height = pos(4) * 0.15; % Reduce height to make the bar shorter (10% of subplot height)

            % Define the lower-left corner position for the custom legend
            legend_x = pos(1) + pos(3) * 0.65;  % Position it slightly to the right
            legend_y = pos(2) + pos(4) * 0.4;   % Position it near the top(close to 1)

            % Standardize the total length of the bar (use the total of fast_gain + slow_gain)
            total_gain = fast_gain + slow_gain;
            fast_proportion = fast_gain / total_gain;  % Proportion of fast_gain
            slow_proportion = slow_gain / total_gain;  % Proportion of slow_gain

           small_threshold = 0.067;  % Set a threshold to define what "small" means. Larger allowing more small values to be considered "small"
           scaling_factor = 3.5;  % Linear scaling factor to make small values more visible
           min_slow_gain_width = 0.025;  % Minimum width to ensure slow_gain visibility

           if slow_proportion < small_threshold
              slow_proportion = slow_proportion * scaling_factor; % Scale up the slow_proportion but keep the relative differences
    
              if slow_proportion < min_slow_gain_width && slow_gain ~= 0
                 slow_proportion = min_slow_gain_width;  % Ensure the scaled slow_proportion meets the minimum width
              end
              
              fast_proportion = 1 - slow_proportion;% Adjust fast proportion
           end
               
            % Change the colors to black for fast_gain and lighter grey for slow_gain
            annotation('rectangle', [legend_x, legend_y, legend_width * fast_proportion, legend_height], 'FaceColor', [0.8,0.8,0.8], 'EdgeColor', 'none');% grey fast
            annotation('rectangle', [legend_x + legend_width * fast_proportion, legend_y, legend_width * slow_proportion, legend_height], 'FaceColor', 'k', 'EdgeColor', 'none');% black slow
        end
    end

    % Set ylabel for the first column and make it bold
    if mod(subplot_index - 1, 8) == 0
        ylabel(neuron_names{ceil(subplot_index / 8)}, 'FontWeight', 'bold');
    end

    % Set the title for the first row and make it bold
    if subplot_index <= 8
        title(neuron_names{subplot_index}, 'FontWeight', 'bold');
    end

    set(gca, 'XTick', [], 'YTick', []);  % Removes tick marks on x and y axis
    set(gca, 'XTickLabel', []);  % Removes labels on x and y axis

    clear v2
end