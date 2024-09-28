%% Ingreso de datos y declaracion de variables
syms x;
 
% Entrada de datos
fx = input('Ingrese la función f(x): ');
xl = input('Ingrese el valor inferior: ');
xu = input('Ingrese el valor superior: ');
 
% Entrada de error estimado e iteraciones
errorest = input('Ingrese el error estimado: ');
imax = input('Número de iteraciones: ');
 
disp('--------------------------------------------------------');
 
% Para la gráfica
xio = xl - 0.5;
xuo = xu + 0.5;
 
% Variables para la gráfica
vxr = [];
vfxr = [];
 
% Evaluación de fxl y fxu
fxl = subs(fx, x, xl);
fxu = subs(fx, x, xu);
 
met = fxl * fxu;
 
%% Comprobacion de compatibilidad
if met >= 0
    error('No cumple con las condiciones para llevarse a cabo.');
end
 
%% Bucle principal de Falsa Poscion Modificada
 
erroraprox = 100;
i = 0;
xro = 0;
 
while (erroraprox > errorest) && (i < imax)
    i = i + 1;
    xr = (xl * subs(fx, x, xu) - xu * subs(fx, x, xl)) / (subs(fx, x, xu) - subs(fx, x, xl));
    erroraprox = (abs((xr - xro) / xr)) * 100;
    xro = xr;
 
    % Mostrar información de la iteración
    fprintf('Iteración %i: \n', i)
    fprintf('xl = %2.6f   xu = %2.6f  xr = %2.6f \n', xl, xu, xr)
    fprintf('Ea = %.6f \n', erroraprox)
    disp('--------------------------------------------------------');
 
    % Evaluar fxr y almacenar valores para la gráfica
    fxr = subs(fx, x, xr);
    vxr(i) = xr;
    vfxr(i) = fxr;
 
    % Actualizar xl y xu
    if (fxl * fxr) < 0
        xu = xr;
    elseif (fxl * fxr) > 0
        xl = xr;
    end
 
    % Actualizar fxl y fxu
    fxl = subs(fx, x, xl);
    fxu = subs(fx, x, xu);
end
 
%% Graficado
ezplot(fx, [xio, xuo])
hold on
plot(vxr, vfxr, 'm*', 'LineWidth', 2)
hold on
stem(xr, fxr, 'filled')
xlabel('Eje x');
ylabel('Eje y');