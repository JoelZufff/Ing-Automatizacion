% EJERCICIO 12.6
syms t;
x1 = t^2;
x2 = 20*t-100;

x = piecewise(0 <= t < 10, x1, 10 <= t <= 20,x2);

figure;
subplot(3,1,1);
fplot(x,[0,20],'r');
title('Funcion de Posicion');
xlabel('Posicion');
ylabel('Tiempo');

v = diff(x,t);

subplot(3,1,2);
fplot(v,[0,20],'b');
title('Funcion de Velocidad');
xlabel('Velocidad');
ylabel('Tiempo');

a = diff(v,t);

subplot(3,1,3);
fplot(a,[0,20],'g');
title('Funcion de Aceleracion');
xlabel('Aceleracion');
ylabel('Tiempo');


% EJERCICIO 12.8
syms s;
v1 = 0.2*s+10;
v2 = 50;

v = piecewise(0 <= s < 200, v1, 200 <= s <= 400,v2);

figure;
subplot(2,1,1);
fplot(v,[0,400],'r');
title('Funcion de Velocidad/Posicion');
xlabel('Velocidad');
ylabel('Posicion');

a = diff(v,s);

subplot(2,1,2);
fplot(a,[0,400],'b');
title('Funcion de Aceleracion/Posicion');
xlabel('Aceleracion');
ylabel('Posicion');

% EJERCICIO 12.62
a1 = -0.02*s+6;
a2 = -4;

a = piecewise(0 <= s < 150, a1, 150 <= s <= 400,a2);

figure;
subplot(2,1,1);
fplot(a,[0,400],'r');
title('Funcion de Aceleracion/Posicion');
xlabel('Posicion');
ylabel('Aceleracion');

v = int(a,s);

subplot(2,1,2);
fplot(v,[0,400],'b');
title('Funcion de Velocidad/Posicion');
xlabel('Posicion');
ylabel('Velocidad');

disp('Distancia antes de detenerse es de 150 metros');
disp('Velocidad Maxima es de 675');

% EJERCICIO 12.63
a1 = sqrt(36*t);
a2 = 4*t-18;

a = piecewise(0 <= t < 9, a1, 9 <= t <= 14,a2);

figure;
subplot(3,1,1);
fplot(a,[0,14],'r');
title('Funcion de Aceleracion');
xlabel('Tiempo');
ylabel('Aceleracion');

v = int(a,t);

subplot(3,1,2);
fplot(v,[0,14],'g');
title('Funcion de Velocidad');
xlabel('Tiempo');
ylabel('Velocidad');

s = int(v,t);

subplot(3,1,3);
fplot(s,[0,14],'b');
title('Funcion de Posicion');
xlabel('Tiempo');
ylabel('Posicion');