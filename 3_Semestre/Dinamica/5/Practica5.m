time = 0:20;
velocity = [0,1,4,8,14,21,28,35,43,51,58,64,69,73,75,75,73,68,60,49,35];

% Adaptamos los datos a una ecuacion de 2do grado

f2 = inline('x(1)*t.^2+x(2)*t+x(3)','x','t');
x2 = nlinfit(time,velocity,f2,[0 0 0]);
v2 = x2(1)*time.^2 + x2(2)*time + x2(3);

% No se adapto bien, por lo que adaptamos los datos a una ecuacion de 3er grado

f3 = inline('x(1)*t.^3+x(2)*t.^2+x(3)*t+x(4)','x','t');
x3 = nlinfit(time,velocity,f3,[0 0 0 0]);
v3 = x3(1)*time.^3+x3(2)*time.^2+x3(3)*time+x3(4);

% Encaja perfercto por lo que ya tenemos la ecuacion

syms t;
v = x3(1)*t.^3+x3(2)*t.^2+x3(3)*t+x3(4);

% Calculamos funcion posicion y aceleracion

s = int(v,t);

a = diff(v,t);

% Graficamos

subplot(3,1,1);
fplot(s, [0 20], 'g');
hold on;
grid on;
title('Funcion de Posicion');
xlabel('Posicion');
ylabel('Tiempo');

subplot(3,1,2);
fplot(v, [0 20], 'r');
hold on;
grid on;
title('Funcion de Velocidad');
xlabel('Velocidad');
ylabel('Tiempo');

subplot(3,1,3);
fplot(a, [0 20], 'b');
hold on;
grid on;
title('Funcion de Aceleracion');
xlabel('Aceleracion');
ylabel('Tiempo');
