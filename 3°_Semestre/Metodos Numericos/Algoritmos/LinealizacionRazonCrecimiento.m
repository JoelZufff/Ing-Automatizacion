function [a, b, Y, T] = LinealizacionRazonCrecimiento()
clear all
clc;
    % Solicitar al usuario que ingrese los valores de x y y por separado
    x_input = input('Ingrese los valores de x separados por espacio: ', 's');
    y_input = input('Ingrese los valores de y separados por espacio: ', 's');
    disp('________________________________________________________________________')
    % Convertir los valores ingresados en vectores
    x = str2num(x_input);
    y = str2num(y_input);
    
    % Validar si los vectores son numéricos y si tienen la misma longitud
    if isempty(x) || isempty(y) || length(x) ~= length(y)
        error('Por favor, ingrese valores numéricos para x e y y asegúrese de que tengan la misma longitud.');
    end
    
    % Verificar si todos los valores en x y y son positivos
    if any(x <= 0) || any(y <= 0)
        error('Todos los valores en x y y deben ser positivos para la linealización por razón de crecimiento.');
    end

    % Realizar la transformación logarítmica
    Y = log(y);
    X = x;
    
    % Calcular los coeficientes de la regresión linealizada
    coeficientes = polyfit(X, Y, 1);%se utiliza para ajustar un polinomio a un conjunto de datos mediante el método de mínimos cuadrados.
    b = coeficientes(1); % Tasa de crecimiento
    A = coeficientes(2); % ln(a), donde 'a' es la constante de crecimiento
    
    % Calcular los valores de a y b
    a = exp(A); % Constante de crecimiento
    Y_estimado = a * exp(b * X); % Estimación de y utilizando el modelo de razón de crecimiento
    
    % Calcular el error estándar del estimado
    Sr = sum((y - Y_estimado).^2);
    n = length(x);
    es = sqrt(Sr / (n - 2));

    % Calcular el coeficiente de determinación (R^2)
    St = sum((y - mean(y)).^2);
    cdet = 1 - Sr / St;

    % Calcular el coeficiente de correlación (r)
    ccor = sqrt(cdet);

    % Almacenar los resultados en una tabla
    disp('________________________________________________________________________')
    E1 = {'Error_estandar', 'Suma_total', 'Error_estandar_del_estimado', 'Coeficiente_de_determinacion', 'Coeficiente_de_correlacion'};
    E2 = [Sr; St; es; cdet; ccor];
    T = table(E2(1), E2(2), E2(3), E2(4), E2(5), 'VariableNames', E1);
    disp('________________________________________________________________________')
    % Mostrar los coeficientes de la regresión linealizada
    disp('Coeficientes de la regresión linealizada:');
    disp(['y = ', num2str(a), ' * exp(', num2str(b), ' * x)']); % Mostrar el modelo de razón de crecimiento
    disp('________________________________________________________________________')
    % Mostrar la tabla de resultados
    disp('Tabla de resultados:');
    disp(T);
    disp('________________________________________________________________________')
    % Graficar los datos y la regresión linealizada
    scatter(x, y, 'LineWidth', 1, 'MarkerEdgeColor', 'b');
    hold on;
    fplot(@(x) a * exp(b * x), [min(x), max(x)], 'LineWidth', 2, 'Color', 'k');
    grid on;
    xlabel('Eje X');
    ylabel('Eje Y');
    title('Linealización de Sistemas No Lineales por Razón de Crecimiento');
    legend('Datos', 'Regresión Linealizada', 'Location', 'Best');
    disp(['Y = ', num2str(a), ' + (x / (', num2str(1/b), ' + x))']);

end
