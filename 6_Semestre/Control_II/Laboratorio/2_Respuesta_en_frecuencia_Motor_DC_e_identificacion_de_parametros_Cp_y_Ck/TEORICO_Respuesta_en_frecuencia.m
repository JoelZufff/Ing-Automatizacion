% Parametros
Ck = 13.55;
Cp = 0.8;

% Ganancias
Kp = 0.15;
Ki = 1;
Kd = 0;

% Funcion de transferencia
G = tf([Ck], [1 Cp]);               % Sistema sin compensar
%G = tf([Kp*Ck Ki*Ck], [1 Cp 0]);    % Sistema compensado
%G = tf([Kp Ki], [1 0]);    % Compensador

% Obtenemos el diagrama de Bode
bode(G);
margin(G);