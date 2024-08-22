function p = interpolacionlagrange()
    % Solicitar datos al usuario
    x = input('Ingrese el vector de coordenadas en x: ');
    f = input('Ingrese el vector de coordenadas en f: ');
    a = input('Ingrese el valor a evaluar: ');
    %Se inseta en forma de vector.
    % Número de puntos de interpolación
    n = numel(x);

    % Variable simbólica
    syms t;

    % Inicializar la suma del polinomio interpolador
    p = 0;

    % Gráfico de los puntos dados
    plot(x, f, '*');
    hold on;
    grid on;

    % Calcular el polinomio interpolador de Lagrange
    for i = 1:n
        % Inicializar el factor de Lagrange
        L = 1;

        % Calcular el factor de Lagrange
        for j = 1:n
            if i ~= j
                L = L * (t - x(j)) / (x(i) - x(j));
            end
        end

        % Acumular el término del polinomio interpolador
        p = p + L * f(i);
    end

    % Mostrar el polinomio interpolador
    disp('Polinomio de Lagrange:');
    p = simplify(p); % Simplificar la expresión
    disp(p);

    % Graficar el polinomio interpolador
    ezplot(p, [min(x) - 1, max(x) + 1]);

    % Graficar el punto a evaluar
    scatter(a, eval(subs(p, t, a)), 'r', 'filled');
    legend('Puntos dados', 'Polinomio de Lagrange', 'Punto a Evaluar');

    % Etiquetas y título del gráfico
    xlabel('x');
    ylabel('f(x)');
    title('Interpolación de Lagrange');

    % Evaluar el polinomio en el punto a
    p = eval(subs(p, t, a));
end
