function [Y, NewtonPol, M] = NewtonInt()
    clear all
    clc;

    % Solicitar datos al usuario
    x = input('Ingrese el vector de coordenadas en x: ');
    y = input('Ingrese el vector de coordenadas en y: ');
    n = input('Ingrese el grado del polinomio a crear: ');

    % Construir la matriz de diferencias divididas finitas
    ddf = zeros(length(x), length(y));  % Inicializar la matriz de diferencias divididas
    ddf(:, 1) = y;  % La primera columna de ddf es igual al vector y
    for j = 2:n + 1
        for i = 1:(n + 1) - (j - 1)
            % Calcular las diferencias divididas finitas
            ddf(i, j) = (ddf(i + 1, j - 1) - ddf(i, j - 1)) / (x(i + j - 1) - x(i));
        end
    end

    % Interpolación de Newton
    xterm = 1; yint = ddf(1, 1); yacum = 0;  % Inicializar términos y acumuladores
    for i = 2:n + 1
        % Calcular términos para la interpolación de Newton
        xterm = xterm * (x(i - 1));
        yint(i) = ddf(1, i) * xterm;
        yacum(i) = yacum(i - 1) + yint(i);  % Acumular valores interpolados
        ea(i) = yacum(i) - yacum(i - 1);  % Calcular errores aproximados
    end
    Y = sum(yint);  % Sumar los términos interpolados para obtener el valor Y

    % Construir el polinomio de Newton como un string
    pol{1, 1} = num2str(ddf(1, 1));
    if n == 0
        NewtonPol = cell2mat(pol);
    else
        NewtonPol = pol{1, 1};
        for i = 2:n + 1
            term = '';
            for j = 1:i-1
                % Construir términos (x - xi) o (x + xi)
                if x(j) >= 0
                    sign_str = '-';
                else
                    sign_str = '+';
                end
                term = [term, '*(x ', sign_str, ' ', num2str(abs(x(j))), ')'];
            end
            
            % Concatenar términos al polinomio
            if ddf(1, i) >= 0
                NewtonPol = [NewtonPol, ' + ', num2str(ddf(1, i)), term];
            else
                NewtonPol = [NewtonPol, ' - ', num2str(abs(ddf(1, i))), term];
            end
        end
    end

    % Resumen en una tabla
    disp('Resumen:');
    vn = 0:n;
    Encabezado = {'Grado', 'P(x)', 'Error'};
    Datos = num2cell([vn', yacum', ea']);  % Crear matriz de datos
    M = [Encabezado; Datos];  % Combinar encabezado y datos en una matriz

    % Gráfica
    fs = str2sym(NewtonPol);  % Convierte el polinomio a función simbólica
    fplot(fs, [min(x) - 1, max(x) + 1], 'k-', 'LineWidth', 2);  % Graficar polinomio
    title(['P(x) = ', NewtonPol]);
    hold on
    x2 = sort(x);
    y2 = sort(y);
    plot(x2, y2, 'm--', 'LineWidth', 1.5);  % Graficar datos de entrada
    hold on
    scatter(x, y, 'LineWidth', 2, 'MarkerEdgeColor', 'b');  % Graficar puntos
    grid on
    h = gcf;
    h.Position(1:2) = [750, 90];
    
    % Imprimir el polinomio
    disp(['Polinomio de Newton: P(x) = ', NewtonPol]);

    % Solicitar al usuario un punto para evaluar el polinomio
    punto_evaluar = input('Ingrese el punto a evaluar: ');
    resultado_evaluacion = eval(subs(fs, punto_evaluar));
    disp(['Resultado de evaluar el polinomio en ', num2str(punto_evaluar), ': ', num2str(resultado_evaluacion)]);
end
