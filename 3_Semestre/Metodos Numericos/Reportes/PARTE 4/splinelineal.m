function splinelineal
    % Limpiar pantalla
    clc;
    
    % Solicitar datos
    X = input('Introduzca datos del dominio: ');
    Y = input('Introduzca datos del contradominio: ');
    
    n = length(X);
    
    for k = 1:n-1
        disp(['Intervalo [', num2str(X(k)), ', ', num2str(X(k+1)), ']']);
        disp(['Puntos: (', num2str(X(k)), ', ', num2str(Y(k)), '), (', num2str(X(k+1)), ', ', num2str(Y(k+1)), ')']);
        
        m = (Y(k+1) - Y(k)) / (X(k+1) - X(k));
        b = Y(k) - m * X(k);
        
        if b > 0
            fprintf('%fx + %f \t para x en [%.3f, %.3f]\n', m, b, X(k), X(k+1));
        elseif b < 0
            fprintf('%fx - %f \t para x en [%.3f, %.3f]\n', m, abs(b), X(k), X(k+1));
        else
            fprintf('%fx \t para x en [%.3f, %.3f]\n', m, X(k), X(k+1));
        end
    end
    
    % Graficar puntos
    figure;
    plot(X, Y, '*k');
    hold on;
    
    % Graficar líneas entre puntos
    plot(X, Y, '-k');
    title('Splines Lineales');
    xlabel('X');
    ylabel('Y');
    
    hold off;
end
