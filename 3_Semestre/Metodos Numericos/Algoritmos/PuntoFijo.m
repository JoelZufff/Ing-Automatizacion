function puntoFijo
    
    % Entrada de la función como función anónima
    f_str = input('Escriba la función: ', 's');
    fx = inline(f_str);
    x0 = input('Introduzca el valor x0 = ');
    imax = input('Introduzca el número de iteraciones: ');
    maxerror = input('Introduzca el error maximo = ');
    
    % Inicialización
    i = 1;
    
    % Bucle de iteraciones
    while i <= imax
        % Calcular la siguiente aproximación
        x1 = fx(x0);
        
        % Verificar la convergencia
        if abs(x1 - x0) < maxerror
            fprintf('Convergencia alcanzada \nx = %f\tIteración %d.\n', x1,i);
            return;
        end
        
        % Actualizar la aproximación para la siguiente iteración
        x0 = x1;
        
        % Incrementar el contador de iteraciones
        i = i + 1;
    end
    
    % Si no se alcanza la convergencia en el número máximo de iteraciones
    disp('El método de punto fijo no convergió en el número máximo de iteraciones.');
end
