%Inicializar gravedad
g = 9.81;

% CASO 30°
Vx = 10*cosd(30);
Vy = 10*sind(30);
t = (2*Vy)/g;

disp('Valor de Vx:');
disp(Vx);
disp('Valor de Vy:');
disp(Vy);
disp('Valor del tiempo:');
disp(t);

x = Vx*t;
y = Vy*t-((1/2)*g)*t^2;
disp('Distancia:');
disp(x);
disp('Altura máxima:');
disp(y);
time = [0:0.01:t];
x1=Vx*time;
y1=Vy*time-(1/2)*(g)*(time.^2);
plot(x1,y1,'r');
xlabel('Distancia');
ylabel('Altura');
hold on;

% CASO 45°
Vx = 10*cosd(45);
Vy = 10*sind(45);
t = (2*Vy)/g;

disp('Vx: ');
disp(Vx);
disp('Vy:');
disp(Vy);
disp('Tiempo:');
disp(t);

x = Vx*t;
y = Vy*t-((1/2)*g)*t^2;
disp('Distancia:');
disp(x);
disp('Altura máxima:');
disp(y);
time = [0 : 0.01 : t];
x1 = Vx*time;
y1 = Vy*time-(1/2)*(g)*(time.^2);

plot(x1,y1,'g');

title('TIRO PARABOLICO');
xlabel('Distancia');
ylabel('Altura');
hold on

% CASO 60°
Vx =10*cosd(60);
Vy = 10*sind(60);
t = (2*Vy)/g;
disp('Valor de Vx:');
disp(Vx);
disp('Valor de Vy:');
disp(Vy);
disp('Valor del tiempo:');
disp(t);

x = Vx*t;
y = Vy*t-((1/2)*g)*t.^2;
disp('Distancia:');
disp(x);
disp('Altura máxima:');
disp(y);

time = [0:0.01:t];
x1 = Vx*time;
y1 = Vy*time-(1/2)*(g)*(time.^2);
plot(x1,y1,'b');
xlabel('Distancia');
ylabel('Altura');
legend("45°","30°","60°");