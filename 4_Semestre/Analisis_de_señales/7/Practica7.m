%% Señal Original
% Definimos variables
Fs = 5000;
Ts = 1/ Fs;
Tmax = 0.1;
t = 0: Ts : Tmax - Ts;

% Creamos funciones
xt = sin (200* pi * t )+ 1.7* sin (140* pi*t );
X = fft (xt);
L = length (xt);
P2 = abs (X / L);
P1 = P2 (1: L /2+1);
P1 (2: end -1) = 2* P1 (2: end -1);
f = Fs *(0:( L /2) ) /L;

% Graficamos en dominio del tiempo
figure;
plot (t ,xt), xlim ([ 0 0.05]), xticks (0:0.01:0.05), ylim ([ -3 3]), xlabel ('t'), ylabel ('Amplitude ');
grid on;

% Graficamos en dominio de la frecuencia
figure;
plot (f ,P1, 'r'), xlabel ('f(Hz)'), ylabel ('Magnitude '), xlim ([0 200]), xticks (0:50:200), ylim ([0 2]), yticks (0:0.5:2) ;
grid on;

%% f_s = f_m
% Definimos variables
Fs = 100;
Ts = 1/ Fs;
Tmax = 0.1;
t = 0: Ts : Tmax - Ts ;

% Creamos funcione
x = sin (200* pi * t )+ 1.7* sin (140* pi*t ) ;
X = fft (x);
L = length ( x ) ;
P2 = abs ( X / L ) ;
P1 = P2 (1: L /2+1) ;
P1 (2: end -1) = 2* P1 (2: end -1) ;
f = Fs *(0:( L /2) ) /L ;

% Graficamos en dominio del tiempo
figure
stem (t ,x);
hold on;
plot (t ,x,':b'), xlim ([ 0 0.05]), xticks (0:0.01:0.05), ylim ([ -3 3]), yticks ( -3:1:3), xlabel ('t'), ylabel ('Amplitude '), legend ('x_s1(nT)','x_s1(t)');
hold off;
grid on;

figure
plot (f , P1 ,'r'), xlabel ('f(Hz)'), ylabel ('Magnitude'), xlim ([0 200]), xticks (0:50:200), ylim ([0 2]), yticks (0:0.5:2);
grid on;

%% f_s = 2f_m
% Definimos variables
Fs = 200;
Ts = 1/ Fs;
Tmax = 0.1;
t = 0: Ts : Tmax - Ts ;

% Creamos funcione
x = sin (200* pi * t )+ 1.7* sin (140* pi*t ) ;
X = fft (x);
L = length ( x ) ;
P2 = abs ( X / L ) ;
P1 = P2 (1: L /2+1) ;
P1 (2: end -1) = 2* P1 (2: end -1) ;
f = Fs *(0:( L /2) ) /L ;

% Graficamos en dominio del tiempo
figure
stem (t ,x);
hold on;
plot (t ,x,':b'), xlim ([ 0 0.05]), xticks (0:0.01:0.05), ylim ([ -3 3]), yticks ( -3:1:3), xlabel ('t'), ylabel ('Amplitude '), legend ('x_s1(nT)','x_s1(t)');
hold off;
grid on;

figure
plot (f , P1 ,'r'), xlabel ('f(Hz)'), ylabel ('Magnitude'), xlim ([0 200]), xticks (0:50:200), ylim ([0 2]), yticks (0:0.5:2);
grid on;

%% f_s = 3f_m
% Definimos variables
Fs = 300;
Ts = 1/ Fs;
Tmax = 0.1;
t = 0: Ts : Tmax - Ts ;

% Creamos funcione
x = sin (200* pi * t )+ 1.7* sin (140* pi*t ) ;
X = fft (x);
L = length ( x ) ;
P2 = abs ( X / L ) ;
P1 = P2 (1: L /2+1) ;
P1 (2: end -1) = 2* P1 (2: end -1) ;
f = Fs *(0:( L /2) ) /L ;

% Graficamos en dominio del tiempo
figure
stem (t ,x);
hold on;
plot (t ,x,':b'), xlim ([ 0 0.05]), xticks (0:0.01:0.05), ylim ([ -3 3]), yticks ( -3:1:3), xlabel ('t'), ylabel ('Amplitude '), legend ('x_s1(nT)','x_s1(t)');
hold off;
grid on;

figure
plot (f , P1 ,'r'), xlabel ('f(Hz)'), ylabel ('Magnitude'), xlim ([0 200]), xticks (0:50:200), ylim ([0 2]), yticks (0:0.5:2);
grid on;    

%% f_s = 20f_m
% Definimos variables
Fs = 2000;
Ts = 1/ Fs;
Tmax = 0.1;
t = 0: Ts : Tmax - Ts ;

% Creamos funcione
x = sin (200* pi * t )+ 1.7* sin (140* pi*t ) ;
X = fft (x);
L = length ( x ) ;
P2 = abs ( X / L ) ;
P1 = P2 (1: L /2+1) ;
P1 (2: end -1) = 2* P1 (2: end -1) ;
f = Fs *(0:( L /2) ) /L ;

% Graficamos en dominio del tiempo
figure
stem (t ,x);
hold on;
plot (t ,x,':b'), xlim ([ 0 0.05]), xticks (0:0.01:0.05), ylim ([ -3 3]), yticks ( -3:1:3), xlabel ('t'), ylabel ('Amplitude '), legend ('x_s1(nT)','x_s1(t)');
hold off;
grid on;

figure
plot (f , P1 ,'r'), xlabel ('f(Hz)'), ylabel ('Magnitude'), xlim ([0 200]), xticks (0:50:200), ylim ([0 2]), yticks (0:0.5:2);
grid on;