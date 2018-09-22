%% Deterministic.m
% This Matlab script is meant to plot the deterministic k-function for the opening probability
% of a Ryanodine Receptor.

%% Initialization
n = 2; % Number of ions
numions = 1:14400;
nlen = length(numions);
Ka = 9e-5; % Constant, reaction rate
Kb = 0.5; % Constant, revese reaction rate
Ca = zeros(nlen,1); % Calcium Concentration
p = zeros(nlen,1); % Opening probability

%% Main Algorithm
% Find [Ca2+] and Opening Probabilty

for i = 1:nlen
    
    Ca(i) = (numions(i))/7.2; % Conversion of Ions to Concentration in uM
    p(i) = (Ka*(Ca(i)^n)/(Ka*(Ca(i)^n) + Kb)); % deterministic function
    
end
f = figure('visible', 'off');
plot(Ca,p, 'linewidth', 2, 'Displayname', '^{K_a([Ca^2^+]^2)}/_{(K_a([Ca^2^+]^2) + K_b)}');
axis([0 2000 0 1]);
xlabel('[Ca^2^+] (uM)');
ylabel('Open Probability, P_o');
title('Deterministic k Function');
f_name = 'Testing';
mkdir(f_name);
image = 'Test.png';
%saveas(f,[pwd '/Test/%i.png'], f_name);
saveas(f,[pwd '/' f_name '/' image]);

