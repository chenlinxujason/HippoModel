clear;
close all;
clc;

%% neurons type - plotting Izhikevich pattern
% % C Vr Vt k Vpeak a b c d; amp, duration, pattern name
neuron_types = {
    'PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,  455, 337, 'ASP'; % type3
    'BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,    397, 874.857','ASP.SLN';
    'AAC', 165, -57.1, -48.8, 3.96, 27.8, 0.005, 8.68, -73.97, 15,      632,620,'ASP'; 
    'BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,    407,860,'ASP.NASP';
    'BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,  408,475.746,'PSTUT';
    'OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,      292,624,'ASP';
    'TL', 205, -64.64, -56.25, 0.52, 0.17, 0.002, 42.24, -60.62, -19,   395,297.75,'NASP'; % CA1 TL
    'MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,     402, 1080.25,'ASP.NASP';    
};


neuron_names = {'PC','BC','AAC','BCCCK','BisC','OLM','TL','MFA'};

%% CA3 local initial
% Connection_types = {
%     'PC-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,   0.486, 36.2, 47.0, 1.0, 0.97;
%     'PC-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,     1.207, 37.3, 89.4, 1.0, 0.769;
%     'PC-AAC', 165, -57.1, -48.8, 3.96, 27.8, 0.005, 8.68, -73.97, 15,       1.792, 4.4, 79.6, 1.0, 0.769;
%     'PC-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,     2.11, 1.12, 50.1, 1.0, 1.045;%1.045 slow
%     'PC-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,   1.464, 2.62, 78.81, 1.0, 0.81;
%     'PC-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,       0.328, 44.7, 78.0, 1.0, 0.9;
%     'PC-TL', 205, -64.64, -56.25, 0.52, 0.17, 0.002, 42.24, -60.62, -19,    0.337, 19.8, 37.0, 1.0, 1.045;
%     'PC-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,      0.368, 31.7, 48.26, 1.0, 0.81;
%     
%     'BC-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,   3.974, 7.2, 633.2, 1.0, 0.0;
%     'BC-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,     0.0, 0.0, 0.0, 0.0, 0.0;
%     'BC-AAC', 165, -57.1, -48.8, 3.96, 27.8, 0.005, 8.68, -73.97, 15,       10.11, 33.2, 433.2, 1.0, 0.0;
%     'BC-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,     0.0, 0.0, 0.0, 0.0, 0.0;
%     'BC-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,   0.0, 0.0, 0.0, 0.0, 0.0;
%     'BC-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,       0.0, 0.0, 0.0, 0.0, 0.0;
%     'BC-TL', 205, -64.64, -56.25, 0.52, 0.17, 0.002, 42.24, -60.62, -19,    0.0, 0.0, 0.0, 0.0, 0.0;
%     'BC-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,      5.2, 16.1, 417.5, 1.0, 0.0;
%     
%     'AAC-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,  3.974, 7.2, 633.2, 1.0, 0.0;
%     'AAC-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,    0.0, 0.0, 0.0, 0.0, 0.0;
%     'AAC-AAC', 165, -57.1, -48.8, 3.96, 27.8, 0.005, 8.68, -73.97, 15,      0.0, 0.0, 0.0, 0.0, 0.0;
%     'AAC-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,    0.0, 0.0, 0.0, 0.0, 0.0;
%     'AAC-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,  0.0, 0.0, 0.0, 0.0, 0.0;
%     'AAC-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,      0.0, 0.0, 0.0, 0.0, 0.0;
%     'AAC-TL', 205, -64.64, -56.25, 0.52, 0.17, 0.002, 42.24, -60.62, -19,   0.0, 0.0, 0.0, 0.0, 0.0;
%     'AAC-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,     0.0, 0.0, 0.0, 0.0, 0.0;
%     
%     'BCCCK-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138, 3.974, 7.2, 633.2, 1.0, 0.05;
%     'BCCCK-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,   6.43, 45.4, 504.0, 1.0, 0.01;
%     'BCCCK-AAC', 165, -57.1, -48.8, 3.96, 27.8, 0.005, 8.68, -73.97, 15,     10.11, 33.2, 433.2, 1.0, 0.0;
%     'BCCCK-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,   0.0, 0.0, 0.0, 0.0, 0.0;
%     'BCCCK-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19, 0.0, 0.0, 0.0, 0.0, 0.0;
%     'BCCCK-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,     0.0, 0.0, 0.0, 0.0, 0.0;
%     'BCCCK-TL', 205, -64.64, -56.25, 0.52, 0.17, 0.002, 42.24, -60.62, -19,  0.0, 0.0, 0.0, 0.0, 0.0;
%     'BCCCK-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,    5.2, 16.1, 417.5, 1.0, 0.05;
%     
%     'BisC-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,  3.974, 7.2, 633.2, 1.0, 0.0;
%     'BisC-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,    3.28, 45.4, 504.0, 1.0, 0.01;
%     'BisC-AAC', 165, -57.1, -48.8, 3.96, 27.8, 0.005, 8.68, -73.97, 15,      10.11, 33.2, 433.2, 1.0, 0.0;
%     'BisC-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,    4.08, 18.78, 318.1, 1.0, 0.0167;
%     'BisC-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,  9.55, 33.0, 480.9, 1.0, 0.0125;
%     'BisC-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,      2.82, 34.73, 447.5, 1.0, 0.0167;
%     'BisC-TL', 205, -64.64, -56.25, 0.52, 0.17, 0.002, 42.24, -60.62, -19,   0.0, 0.0, 0.0, 0.0, 0.0;
%     'BisC-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,     5.2, 16.1, 417.5, 1.0, 0.0;
%     
%     'OLM-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,   3.974, 7.2, 633.2, 1.0, 0.0;
%     'OLM-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,     3.28, 45.4, 504.0, 1.0, 0.01;
%     'OLM-AAC', 165, -57.1, -48.8, 3.96, 27.8, 0.005, 8.68, -73.97, 15,       10.11, 33.2, 433.2, 1.0, 0.0;
%     'OLM-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,     4.08, 18.78, 318.1, 1.0, 0.0167;
%     'OLM-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,   9.55, 33.0, 480.9, 1.0, 0.0125;
%     'OLM-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,       2.82, 34.73, 447.5, 1.0, 0.0167;
%     'OLM-TL', 205, -64.64, -56.25, 0.52, 0.17, 0.002, 42.24, -60.62, -19,    0.0, 0.0, 0.0, 0.0, 0.0;
%     'OLM-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,      0.0, 0.0, 0.0, 0.0, 0.0;
%     
%     'TL-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,    3.974, 7.2, 633.2, 1.0, 0.0;
%     'TL-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,      3.28, 45.4, 504.0, 1.0, 0.01;
%     'TL-AAC', 165, -57.1, -48.8, 3.96, 27.8, 0.005, 8.68, -73.97, 15,        10.11, 33.2, 433.2, 1.0, 0.0;
%     'TL-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,      4.08, 18.78, 318.1, 1.0, 0.0167;
%     'TL-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,    9.55, 33.0, 480.9, 1.0, 0.0125;
%     'TL-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,        2.82, 34.73, 447.5, 1.0, 0.0167;
%     'TL-TL', 205, -64.64, -56.25, 0.52, 0.17, 0.002, 42.24, -60.62, -19,     0.0, 0.0, 0.0, 0.0, 0.0;
%     'TL-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,       0.0, 0.0, 0.0, 0.0, 0.0;
%     
%     'MFA-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,   3.974, 7.2, 633.2, 1.0, 0.0;
%     'MFA-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,     3.28, 45.4, 504.0, 1.0, 0.01;
%     'MFA-AAC', 165, -57.1, -48.8, 3.96, 27.8, 0.005, 8.68, -73.97, 15,       0.0, 0.0, 0.0, 0.0, 0.0;
%     'MFA-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,     0.0, 0.0, 0.0, 0.0, 0.0;
%     'MFA-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,   9.55, 33.0, 480.9, 1.0, 0.0125;
%     'MFA-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,       0.0, 0.0, 0.0, 0.0, 0.0;
%     'MFA-TL', 205, -64.64, -56.25, 0.52, 0.17, 0.002, 42.24, -60.62, -19,    0.0, 0.0, 0.0, 0.0, 0.0;
%     'MFA-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,      5.2, 16.1, 417.5, 1.0, 0.0;
% };


%% CA3 local Fine tune
Connection_types = {
    'PC-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,   0.7, 36.2, 47.0, 1.0, 0.97;
    'PC-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,     0.94, 37.3, 89.4, 1.0, 0.769;
    'PC-AAC', 165, -57.1, -48.8, 3.96, 27.8, 0.005, 8.68, -73.97, 15,       1.2, 4.4, 79.6, 1.0, 0.769;
    'PC-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,     1.3, 1.12, 50.1, 1.0, 1.045;%1.045 slow
    'PC-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,   0.98, 2.62, 78.81, 1.0, 0.81;
    'PC-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,       1.4, 44.7, 78.0, 1.0, 0.9;
    'PC-TL', 205, -64.64, -56.25, 0.52, 0.17, 0.002, 42.24, -60.62, -19,    0.7, 19.8, 37.0, 1.0, 1.045;
    'PC-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,      1.6, 31.7, 48.26, 1.0, 0.81;
    
    'BC-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,   0.12, 7.2, 633.2, 1.0, 0.0;
    'BC-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,     0.0, 0.0, 0.0, 0.0, 0.0;
    'BC-AAC', 165, -57.1, -48.8, 3.96, 27.8, 0.005, 8.68, -73.97, 15,       0.25, 33.2, 433.2, 1.0, 0.0;
    'BC-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,     0.0, 0.0, 0.0, 0.0, 0.0;
    'BC-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,   0.0, 0.0, 0.0, 0.0, 0.0;
    'BC-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,       0.0, 0.0, 0.0, 0.0, 0.0;
    'BC-TL', 205, -64.64, -56.25, 0.52, 0.17, 0.002, 42.24, -60.62, -19,    0.0, 0.0, 0.0, 0.0, 0.0;
    'BC-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,      0.15, 16.1, 417.5, 1.0, 0.0;
    
    'AAC-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,  0.1, 7.2, 633.2, 1.0, 0.0;
    'AAC-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,    0.0, 0.0, 0.0, 0.0, 0.0;
    'AAC-AAC', 165, -57.1, -48.8, 3.96, 27.8, 0.005, 8.68, -73.97, 15,      0.0, 0.0, 0.0, 0.0, 0.0;
    'AAC-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,    0.0, 0.0, 0.0, 0.0, 0.0;
    'AAC-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,  0.0, 0.0, 0.0, 0.0, 0.0;
    'AAC-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,      0.0, 0.0, 0.0, 0.0, 0.0;
    'AAC-TL', 205, -64.64, -56.25, 0.52, 0.17, 0.002, 42.24, -60.62, -19,   0.0, 0.0, 0.0, 0.0, 0.0;
    'AAC-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,     0.0, 0.0, 0.0, 0.0, 0.0;
    
    'BCCCK-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138, 0.1, 7.2, 633.2, 1.0, 0.05;
    'BCCCK-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,   0.3, 45.4, 504.0, 1.0, 0.01;
    'BCCCK-AAC', 165, -57.1, -48.8, 3.96, 27.8, 0.005, 8.68, -73.97, 15,     0.26, 33.2, 433.2, 1.0, 0.0;
    'BCCCK-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,   0.0, 0.0, 0.0, 0.0, 0.0;
    'BCCCK-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19, 0.0, 0.0, 0.0, 0.0, 0.0;
    'BCCCK-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,     0.0, 0.0, 0.0, 0.0, 0.0;
    'BCCCK-TL', 205, -64.64, -56.25, 0.52, 0.17, 0.002, 42.24, -60.62, -19,  0.0, 0.0, 0.0, 0.0, 0.0;
    'BCCCK-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,    0.5, 16.1, 417.5, 1.0, 0.05;
    
    'BisC-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,  0.1, 7.2, 633.2, 1.0, 0.0;
    'BisC-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,    0.1, 45.4, 504.0, 1.0, 0.01;
    'BisC-AAC', 165, -57.1, -48.8, 3.96, 27.8, 0.005, 8.68, -73.97, 15,      0.15, 33.2, 433.2, 1.0, 0.0;
    'BisC-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,    0.8, 18.78, 318.1, 1.0, 0.0167;
    'BisC-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,  0.4, 33.0, 480.9, 1.0, 0.0125;
    'BisC-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,      0.1, 34.73, 447.5, 1.0, 0.0167;
    'BisC-TL', 205, -64.64, -56.25, 0.52, 0.17, 0.002, 42.24, -60.62, -19,   0.0, 0.0, 0.0, 0.0, 0.0;
    'BisC-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,     0.15, 16.1, 417.5, 1.0, 0.0;
    
    'OLM-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,   0.15, 7.2, 633.2, 1.0, 0.0;
    'OLM-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,     0.3, 45.4, 504.0, 1.0, 0.01;
    'OLM-AAC', 165, -57.1, -48.8, 3.96, 27.8, 0.005, 8.68, -73.97, 15,       0.2, 33.2, 433.2, 1.0, 0.0;
    'OLM-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,     1.0, 18.78, 318.1, 1.0, 0.0167;
    'OLM-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,   0.3, 33.0, 480.9, 1.0, 0.0125;
    'OLM-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,       0.14, 34.73, 447.5, 1.0, 0.0167;
    'OLM-TL', 205, -64.64, -56.25, 0.52, 0.17, 0.002, 42.24, -60.62, -19,    0.0, 0.0, 0.0, 0.0, 0.0;
    'OLM-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,      0.0, 0.0, 0.0, 0.0, 0.0;
    
    'TL-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,    0.12, 7.2, 633.2, 1.0, 0.0;
    'TL-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,      0.1, 45.4, 504.0, 1.0, 0.01;
    'TL-AAC', 165, -57.1, -48.8, 3.96, 27.8, 0.005, 8.68, -73.97, 15,        0.3, 33.2, 433.2, 1.0, 0.0;
    'TL-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,      0.6, 18.78, 318.1, 1.0, 0.0167;
    'TL-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,    0.2, 33.0, 480.9, 1.0, 0.0125;
    'TL-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,        0.1, 34.73, 447.5, 1.0, 0.0167;
    'TL-TL', 205, -64.64, -56.25, 0.52, 0.17, 0.002, 42.24, -60.62, -19,     0.0, 0.0, 0.0, 0.0, 0.0;
    'TL-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,       0.0, 0.0, 0.0, 0.0, 0.0;
    
    'MFA-PC', 382, -58.63, -42.74, 0.98, 38.55, 0.008, 12.49, -34.52, 138,   0.16, 7.2, 633.2, 1.0, 0.0;
    'MFA-BC', 45, -57.51, -23.38, 1.0, 18.45, 0.004, 9.26, -47.56, -6.0,     0.1, 45.4, 504.0, 1.0, 0.01;
    'MFA-AAC', 165, -57.1, -48.8, 3.96, 27.8, 0.005, 8.68, -73.97, 15,       0.0, 0.0, 0.0, 0.0, 0.0;
    'MFA-BCCCK', 135, -59, -39.4, 0.58, 18.27, 0.006, -1.24, -42.77, 54,     0.0, 0.0, 0.0, 0.0, 0.0;
    'MFA-BisC', 107, -64.67, -58.74, 3.94, -9.93, 0.002, 16.58, -59.7, 19,   0.4, 33.0, 480.9, 1.0, 0.0125;
    'MFA-OLM', 65, -60.04, -30.87, 0.51, 19.77, 0.01, 2.39, -52.81, 6,       0.0, 0.0, 0.0, 0.0, 0.0;
    'MFA-TL', 205, -64.64, -56.25, 0.52, 0.17, 0.002, 42.24, -60.62, -19,    0.0, 0.0, 0.0, 0.0, 0.0;
    'MFA-MFA', 185, -59.41, -36.59, 0.55, 9.99, 0.003, 3.69, -43.55, 5,      0.3, 16.1, 417.5, 1.0, 0.0;
};

%% CA1 local initial

%% CA1 local Fine tune


%% Parameters common to all neurons
Integrator = 2; % RK method
T = 1200; %1000ms
step = 0.1; % ms (0.2ms - iterate 5 times; 0.1ms - iterate 10 times)
n = round(T/step); % simulation time steps
PulseStart = 100; % Pulse start time in ms
%PulseEnd = 600; % Pulse end time in ms, must < T
TTP = PulseStart/1000; %time to peak (sec)
t = step*(1:n);%correct!
STP_U = 0.45; % 0.45(STD,only Pyramidal) or 0.15(STF)
STP_tau_u = 50; % 50ms(STD,only Pyramidal) or 750ms(STF),tau_f,facilitation time constant
STP_tau_x = 750;  %750 ms(STD,only Pyramidal) or 50ms(STF),tau_d,depression time constant
amp2 = 0; %external current at postsynaptic neuron, pA
I2 = amp2*t;

%% Figure
figure;
num_connections = size(Connection_types, 1);
num_neurons = length(neuron_names); % Get number of neuron names

% Loop over all subplots
for i = 1:num_neurons
    
    % First column: Izhikevich patterns
    izhi_subplot_index = (i-1)*10+[1,2]; % 1,9,17,etc
    izhi_ax = subplot(8,10,izhi_subplot_index);  % Create subplot for the Izhikevich pattern and capture axis handle

    C1 = neuron_types{i, 2};
    vr1 = neuron_types{i, 3};
    vt1 = neuron_types{i, 4};
    k1 = neuron_types{i, 5};
    vpeak1 = neuron_types{i, 6};
    a1 = neuron_types{i, 7};
    b1 = neuron_types{i, 8};
    c1 = neuron_types{i, 9};
    d1 = neuron_types{i, 10};
    amp1 = neuron_types{i, 11};
    PulseEnd = neuron_types{i, 12};
    pattern_name = neuron_types{i, 13};

    current = vr1*ones(1,n); 
    PulseStartIndex = round(PulseStart/step) + 1; % Index for pulse start
    PulseEndIndex = round(PulseEnd/step); % Index for pulse end
    current(PulseStartIndex:PulseEndIndex) = amp1;
    
    [v1,u1,spike_trains1,I1] = ...
        izhikevich_presynaptic_neuron(Integrator,amp1,C1,vr1,vt1,k1,...
        vpeak1,a1,b1,c1,d1,T,step,PulseStart,PulseEnd);

    plot(t, v1, 'k', 'LineWidth', 0.8);  % Plot the Izhikevich pattern
    hold on;
    plot(t, current/10, 'LineWidth', 1.5);  % Plot the scaled current
    title(neuron_names{i}, 'FontWeight', 'bold');
    set(izhi_ax, 'XTick', [], 'YTick', []);  % Remove tick marks and labels
    
    lgd = legend(pattern_name);
    lgd.FontSize = 5.2;  % Adjust the legend font size to make it smaller

    %% Connection plots in the remaining 8 columns (8x8 grid)
    for j = 1:8
        connection_subplot_index=(i-1)*10+(j+2);  % Shift by +1 to skip first column
        ax = subplot(8,10,connection_subplot_index);  % Create a subplot for each connection
        
        C2 = Connection_types{(i-1)*8 + j, 2};  % Adjust to ensure connection mapping per neuron
        vr2 = Connection_types{(i-1)*8 + j, 3};
        vt2 = Connection_types{(i-1)*8 + j, 4};
        k2 = Connection_types{(i-1)*8 + j, 5};
        vpeak2 = Connection_types{(i-1)*8 + j, 6};
        a2 = Connection_types{(i-1)*8 + j, 7};
        b2 = Connection_types{(i-1)*8 + j, 8};
        c2 = Connection_types{(i-1)*8 + j, 9};
        d2 = Connection_types{(i-1)*8 + j, 10};
        Wt = Connection_types{(i-1)*8 + j, 11};
        tau_fast = Connection_types{(i-1)*8 + j, 12};
        tau_slow = Connection_types{(i-1)*8 + j, 13};
        fast_gain = Connection_types{(i-1)*8 + j, 14};
        slow_gain = Connection_types{(i-1)*8 + j, 15};
    
        % Set connection-specific parameters
        connection_name = Connection_types{(i-1)*8 + j, 1};
        if any(strcmp(connection_name, {'PC-PC', 'PC-BC', 'PC-AAC', 'PC-BCCCK', 'PC-BisC', 'PC-OLM', 'PC-TL', 'PC-MFA'}))
            conn_type = 1; % Excitatory
            V_rev_fast = 0;
            V_rev_slow = 0;
        else
            conn_type = 2; % Inhibitory
            V_rev_fast = -70;
            V_rev_slow = -90;
        end
        
        % Execute the neuron model 
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
        
        if conn_type == 1 % Excitatory
            %ylim([vr2-0.6, vr2+3.0]);% initial
            ylim([vr2-1.2, vr2+10.5]);% fine tune
%             ylim([min(v2)-0.6, max(v2)+0.6]);% fine tune
        
        else % Inhibitory
            %ylim([vr2-2.9, vr2+0.6]);% initial
            %ylim([vr2-0.6, vr2+0.6]);% fine tune
            ylim([min(v2)-0.12, max(v2)+0.03]);% fine tune
        end

     % Add the bar plot for each subplot as a custom "legend" if Wt is not 0
        if Wt ~= 0
            % Get the position of the current subplot
            pos = get(ax, 'Position');

            % Define the size of the custom bar plot legend
            legend_width = pos(3) * 0.25;  % Make the total legend width 40% of subplot width
            legend_height = pos(4) * 0.15; % Reduce height to make the bar shorter (10% of subplot height)

            % Define the position of the custom legend
            legend_x = pos(1) + pos(3) * 0.65;  % Position it slightly to the right
            legend_y = pos(2) + pos(4) * 0.49;  % Position it near the top(close to 1)

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

    % Set the title for the first row (subplots 3 to 10)
        if i == 1
            title(neuron_names{j}, 'FontWeight', 'bold');
        end

        % Set y-label for the third column (subplots in column 3)
        if j == 1
            ylabel(neuron_names{i}, 'FontWeight', 'bold');
        end

    set(gca, 'XTick', [], 'YTick', []);  % Removes tick marks on x and y axis
    set(gca, 'XTickLabel', []);  % Removes labels on x and y axis

    clear v2
    end
end