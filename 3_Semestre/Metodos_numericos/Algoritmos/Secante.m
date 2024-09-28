
% Entrada de la función como función anónima
f_str = input('Escriba la función: ', 's');
f = inline(f_str);

% Valores iniciales y criterio de convergencia
x1 = input('Introduzca el valor x0 = ');
x2 = input('Introduzca el valor x1 = ');
maxerror = input('Introduzca el error maximo = ');

% Gráfico de la función
ezplot(f);
grid on;

% Inicialización de variables
ea = 100;
i = 0;

fprintf('Iteración\tRaíz\n');

% Bucle de iteraciones
while ea > maxerror
    xi = x2 - ((f(x2) * (x1 - x2)) / (f(x1) - f(x2)));
    ea = abs((xi - x2) / xi);
    
    % Impresión de resultados
    fprintf('%d\t\t%8.4f\n', i, xi);
    
    % Actualización de valores para la siguiente iteración
    x1 = x2;
    x2 = xi;
    i = i + 1;
end

fprintf('\nLa raíz de la función: %8.4f\nCalculada en %d iteraciones\n', xi, i);