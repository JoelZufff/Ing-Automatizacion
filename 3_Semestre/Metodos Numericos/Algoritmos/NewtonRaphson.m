% Método de Newton-Raphson para encontrar raíces de funciones

% Definir la variable simbólica
syms x;

% Ingresar la función y su derivada
fx = input('Introduzca f(x) = ');
dfx = diff(fx);

% Ingresar el valor inicial, número de iteraciones y error máximo
x0 = input('x0 =  ');
i = input('Introduzca el número de iteraciones: ');
maxerror = input('Introduzca el error máximo: ');

% Bucle de iteraciones del método de Newton-Raphson
for k = 1:i
    % Calcular la siguiente aproximación
    x1 = x0 - subs(fx, x0) / subs(dfx, x0);
    
    % Mostrar información sobre la iteración actual
    fprintf('Iteración %d: x%d = %f\n', k, k, x1);
    
    % Verificar la convergencia
    if abs(x1 - x0) < maxerror
        fprintf('Convergencia alcanzada. x%d = %f es una aproximación de una raíz\n', k, x1);
        return
    end
    
    % Actualizar el valor inicial para la próxima iteración
    x0 = x1;
end
