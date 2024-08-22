% Calcular la regresión lineal por mínimos cuadrados
function [a, Y, T] = MC(x, y)
    % Limpiar el espacio de trabajo y la pantalla de comandos
    clear all
    clc;

    % Solicitar al usuario que ingrese los valores de x y y separados por espacio
    x_input = input('Ingrese los valores de x separados por espacio: ', 's');
    y_input = input('Ingrese los valores de y separados por espacio: ', 's');

    % Mostrar una línea divisoria para mejorar la legibilidad
    disp('________________________________________________________________________')

    % Convertir los valores ingresados en vectores
    x = str2num(x_input);
    y = str2num(y_input);

    % Calcular la regresión lineal por mínimos cuadrados
    n = length(x);
    sigmaX = sum(x);
    sigmaX2 = sum(x.^2);
    sigmaY = sum(y);
    sigmaXY = sum(x.*y);

    A = [n, sigmaX; sigmaX, sigmaX2];
    B = [sigmaY; sigmaXY];
    a = A\B;

    % Calcular las sumas de los cuadrados para el análisis de regresión
    Sr = sum((y - a(1) - a(2).*x).^2);
    St = sum((y - sigmaY/n).^2);
    es = sqrt(Sr/(n-2));
    cdet = (St - Sr)/St;
    ccor = sqrt(cdet);

    % Mostrar otra línea divisoria
    disp('________________________________________________________________________')

    % Crear una tabla de resultados para mostrar los cálculos
    E1 = {'Sr'; 'St'; 'Error_estandar_del_estimado';...
          'Coeficiente_de_determinacion'; 'Coeficiente_de_correlacion'};
    E2 = [Sr; St; es; cdet; ccor];
    T = table(E1, E2, 'VariableNames', {'ValoresCalculados','Resultados'});

    % Mostrar los coeficientes de la regresión lineal
    disp('________________________________________________________________________')
    disp('Coeficientes de la regresión lineal:');
    disp(['a0 (independiente): ', num2str(a(1))]);
    disp(['a1 (pendiente): ', num2str(a(2))]);
    disp('________________________________________________________________________')

    % Mostrar los resultados de la regresión lineal para los datos de entrada
    disp('Resultados de la regresión lineal para los datos de entrada:');
    Y = a(1) + a(2) * x; % Calcular los valores estimados de y
    disp(['Y: ', num2str(Y)]);
    disp('________________________________________________________________________')

    % Mostrar la tabla de resultados
    disp('Tabla de resultados:');
    disp(T);
    disp('________________________________________________________________________')

    % Graficar los datos y la regresión lineal
    scatter(x, y, 'LineWidth', 1, 'MarkerEdgeColor', 'r');
    hold on;

    % Graficar la línea de regresión
    modelo = poly2sym(flipud(a)); % Crear la ecuación de la línea de regresión
    f = matlabFunction(modelo); % Convertir la ecuación en una función
    fplot(f, [min(x), max(x)], 'LineWidth', 2, 'Color', 'k'); % Graficar la línea de regresión en negro

    grid on;
    xlabel('Eje X'); % Etiqueta del eje X
    ylabel('Eje Y'); % Etiqueta del eje Y
    title('Regresión Lineal por Mínimos Cuadrados'); % Título del gráfico

    % Asegurar que la leyenda se ajuste correctamente
    legend('Datos', 'Regresión Lineal', 'Location', 'Best');

    % Establecer la posición de la figura
    h = gcf;
    h.Position(1:2) = [765, 90];

    % Mostrar los coeficientes de la regresión linealizada
    disp('Coeficientes de la regresión linealizada:');
    if (num2str(a(1)) >= 0)
        disp(['y = ', num2str(a(2)), ' * x + ', num2str(a(1))]); % Mostrar el formato y = a*x+b
    else
        disp(['y = ', num2str(a(2)), ' * x ', num2str(a(1))]); % Mostrar el formato y = a*x+b   
    end
end
