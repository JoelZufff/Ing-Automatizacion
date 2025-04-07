%% Parametros
a = 4.1;
k = 102;
c = 3.1;
%% Ganancias
% Esclavo (Control PD)
Kpc = 4.405;
Kic = 0;
Kdc = 0.1242;
% Maestro (Control PD)
Kp = 8.8105;
Ki = 0;
Kd = 2.1899;
%% Lazo Esclavo
Gc = tf([k], [1 a 0]);              % Sistema sin compensar
%Gc = tf([1 1],[1]);                 % Compensador normalizado
Gc = tf([Kdc Kpc], 1) * Gc;     % Sistema compensado
%% Lazo Maestro
%G = feedback(Gc, -1) * tf([c], [1 0 0]);           % Sistema sin compensar
%G = tf([1 1],[1]);                         % Compensador normalizado
G = tf([Kd Kp], 1) * G;

% Obtenemos el diagrama de Bode
bode(G);
margin(G);
grid on;