%% Definicion de variables

Con_state = true;       % True: Serie | False: Paralelo

% Parametros fijos del motor

M       = 0.05;     % Ganancia fuerza contraelectromotriz
Ls      = 0.1;      % Inductancia del estator
Lr      = 0.1;      % Resistencia del rotor

if Con_state
    Rs      = 0.5;     % Resistencia del estator
    Rr      = 0.5;     % Resistencia del rotor
else
    Rs      = 10;     % Resistencia del estator
    Rr      = 0.5;     % Resistencia del rotor
end


% Parametros variables de funcionamiento
V       = 180;      % Voltaje inducido
J       = 0.016;    % Inercia (1/2 mr^2)
C0      = 0.05;      % Friccion de rotacion (Baleros)

Tload   = 2;        % Torque de carga