%% Definicion de Variables

% Aceleracion
g = 9.807; % m/s^2
% Masa (Kg)
m = 5000;
% Fuerzas (N)
w = m*g;
% Velocidad (m/s)
v = 350*(1/3600)*(1000);
% Angulo (°)
theta = 15;

%% Solucion de la Problematica
syms F_L;   syms a;

F_L = w/cosd(theta);
r = (v^2*m)/(sind(theta)*F_L);

% Display the results
fprintf('\n Radio = %1.4f m', r);
fprintf('\n Fuerza de elevacion L = %1.2f N', F_L);