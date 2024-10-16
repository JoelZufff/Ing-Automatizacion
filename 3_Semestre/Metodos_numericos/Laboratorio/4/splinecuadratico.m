function splinecuadratico
    % Limpiar pantalla
    clc;
    
    % Solicitar datos
    X = input('Introduzca datos del dominio: ');
    Y = input('Introduzca datos del contradominio: ');
    
    n = length(X);
    
    for k = 1:n-1
        disp(['Intervalo [', num2str(X(k)), ', ', num2str(X(k+1)), ']']);
        disp(['Puntos: (', num2str(X(k)), ', ', num2str(Y(k)), '), (', num2str(X(k+1)), ', ', num2str(Y(k+1)), ')']);
        
        % Coeficientes del spline cuadrático
        a = Y(k);
        b = (Y(k+1) - Y(k)) / (X(k+1) - X(k));
        c = (Y(k+1) - Y(k) - b * (X(k+1) - X(k))) / ((X(k+1) - X(k))^2);
        
        fprintf('%gx^2 + %gx + %g \t para x en [%.3f, %.3f]\n', c, b, a, X(k), X(k+1));
    end
    
    % Graficar puntos
    figure;
    plot(X, Y, '*k');
    hold on;
    
    % Graficar spline cuadrático
    for k = 1:n-1
        x_interval = linspace(X(k), X(k+1), 100);
        y_interval = c * (x_interval - X(k)).^2 + b * (x_interval - X(k)) + a;
        plot(x_interval, y_interval, '-r');
    end
    
    title('Splines Cuadráticos');
    xlabel('X');
    ylabel('Y');
    
    hold off;
end