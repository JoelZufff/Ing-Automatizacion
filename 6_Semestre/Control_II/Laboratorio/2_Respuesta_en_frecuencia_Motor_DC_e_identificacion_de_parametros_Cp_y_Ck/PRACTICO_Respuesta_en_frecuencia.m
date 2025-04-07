% Parametros
Ck = 9.66;
Cp = 0.8;

% Funcion de transferencia de motor DC
G = tf([Ck], [1 Cp]);

% Obtenemos el diagrama de Bode
bode(G);