% Declaramos variables
syms t;
syms w;

%% Funcion 1
% Declaramos funciones
xt = exp(-0.5*t) * heaviside(t);
xw = fourier(xt);
xwmag = abs(xw);
xwph = angle(xw);

% Graficamos funciones
figure;
fplot(t,xt,'b', [-1 10]), xlim ([ -1 10 ]), ylim([-0.1 1.1]), xlabel ('t'), ylabel ('x(t)'), title('Time domain');

figure;
subplot(2,1,1), fplot(w,xwmag,'r', [-10 10]), xlim ([ -10 10 ]), ylim([-0.1 2.1]), xlabel ('w(rad/s)'), ylabel ('|X(w)|'), title('Magnitude');
subplot(2,1,2), fplot(w,xwph,'g', [-10 10]), xlim ([ -10 10 ]), ylim([-1.6 1.6]), xlabel ('w(rad/s)'), ylabel ('<X(w)'), title('Angle');
%% Funcion 2
% Declaramos funciones
xt = rectangularPulse( -0.5, 0.5, t);
xw = fourier(xt);
xwmag = abs(xw);
xwph = angle(xw);

% Graficamos funciones
figure;
fplot(t,xt,'b', [-1 1]), xlim ([ -1 1 ]), ylim([-0.1 1.1]), xlabel ('t'), ylabel ('x(t)'), title('Time domain');

figure;
subplot(2,1,1), fplot(w,xwmag,'r', [-25 25]), xlim ([-25 25]), ylim([-0.1 1.1]), xlabel ('w(rad/s)'), ylabel ('|X(w)|'), title('Magnitude');
subplot(2,1,2), fplot(w,xwph,'g', [-25 25]), xlim ([-25 25]), ylim([-0.1 3.4]), xlabel ('w(rad/s)'), ylabel ('<X(w)'), title('Angle');
%% Funcion 3
% Declaramos funciones
xt = sinc(t);
xw = fourier(xt);
xwmag = abs(xw);
xwph = angle(xw);

% Graficamos funciones
figure;
fplot(t,xt,'b', [-10 10]), xlim ([ -10 10 ]), ylim([-0.3 1.1]), xlabel ('t'), ylabel ('x(t)'), title('Time domain');

figure;
subplot(2,1,1), fplot(w,xwmag,'r', [-10 10]), xlim ([ -10 10 ]), ylim([-0.1 1.1]), xlabel ('w(rad/s)'), ylabel ('|X(w)|'), title('Magnitude');
subplot(2,1,2), fplot(w,xwph,'g', [-10 10]), xlim ([ -10 10 ]), ylim([-0.5 0.5]), xlabel ('w(rad/s)'), ylabel ('<X(w)'), title('Angle');

%% Funcion 4
% Declaramos funciones
xt = exp(-0.5*abs(t));
xw = fourier(xt);
xwmag = abs(xw);
xwph = angle(xw);

% Graficamos funciones
figure;
fplot(t,xt,'b', [-10 10]), xlim ([ -10 10 ]), ylim([-0.1 1.1]), xlabel ('t'), ylabel ('x(t)'), title('Time domain');

figure;
subplot(2,1,1), fplot(w,xwmag,'r', [ -5 5 ]), xlim ([ -5 5 ]), ylim([-0.1 4.2]), xlabel ('w(rad/s)'), ylabel ('|X(w)|'), title('Magnitude');
subplot(2,1,2), fplot(w,xwph,'g', [ -5 5 ]), xlim ([ -5 5 ]), ylim([-1.6 1.6]), xlabel ('w(rad/s)'), ylabel ('<X(w)'), title('Angle');

%% Funcion 5
% Declaramos funciones
xt = exp(-2*t)*cos(5*t)*heaviside(t);
xw = fourier(xt);
xwmag = abs(xw);
xwph = angle(xw);

% Graficamos funciones
figure;
fplot(t,xt,'b', [-0.1 3]), xlim ([ -0.1 3 ]), ylim([-0.4 1.1]), xlabel ('t'), ylabel ('x(t)'), title('Time domain');

figure;
subplot(2,1,1), fplot(w,xwmag,'r', [ -100 100 ]), xlim ([ -100 100 ]), ylim([-0.1 0.4]), xlabel ('w(rad/s)'), ylabel ('|X(w)|'), title('Magnitude');
subplot(2,1,2), fplot(w,xwph,'g', [ -100 100 ]), xlim ([ -100 100 ]), ylim([-2 2]), xlabel ('w(rad/s)'), ylabel ('<X(w)'), title('Angle');

%% Funcion 6
% Declaramos funciones
xt = t*exp(-0.5*t)*heaviside(t);
xw = fourier(xt);
xwmag = abs(xw);
xwph = angle(xw);

% Graficamos funciones
figure;
fplot(t,xt,'b', [-0.5 20]), xlim ([ -0.5 20 ]), ylim([-0.1 0.8]), xlabel ('t'), ylabel ('x(t)'), title('Time domain');

figure;
subplot(2,1,1), fplot(w,xwmag,'r', [ -8 8 ]), xlim ([ -8 8 ]), ylim([-0.1 4.5]), xlabel ('w(rad/s)'), ylabel ('|X(w)|'), title('Magnitude');
subplot(2,1,2), fplot(w,xwph,'g', [ -8 8 ]), xlim ([ -8 8 ]), ylim([-4.5 4.5]), xlabel ('w(rad/s)'), ylabel ('<X(w)'), title('Angle');
