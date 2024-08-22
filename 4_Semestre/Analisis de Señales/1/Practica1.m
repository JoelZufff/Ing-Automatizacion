%% ESCALON UNITARIO
t =- 5:0.001:5;
y=(t>=0);
figure;
plot(t,y, 'r'), grid on;
xlabel('Time'), ylabel ( 'Amplitude');
ylim([-2 2]), xlim([ -5 5]);
title( 'Escalon Unitario');

%% RAMPA UNITARIA
t =- 5:0.01:5;
r=(t>=0)
h=t .* r;
figure;
plot(t,h, 'b'), grid on;
xlabel('Time'), ylabel('Amplitude');
ylim([-2 5]), xlim([-5 5]);
title( 'Rampa Unitaria');

%% PARABOLA UNITARIA

t =- 5:0.01:5;
r=(t>=0)
h=t .* r .* t;
figure;
plot(t,h, 'g'), grid on;
xlabel('Time'), ylabel('Amplitude');
ylim([-2 5]), xlim([-5 5]);
title( 'Parabola Unitaria');

%% IMPULSO UNITARIO

t =- 5:0.01:5;
r=(t == 0)
figure
plot(t,r,'y'), grid on;
xlabel( 'Time'), ylabel('Amplitude');
ylim([-2 5]), xlim([ -5 5]);
title( 'Impulso Unitario');

%% SINUSOIDAL

t = 0:0.01:6*pi;
frequency = 1;
amplitude = 1;
phase = 0;
sinusoid = amplitude * sin(2*pi*frequency*t + phase);
plot(t, sinusoid), grid on;
xlabel('Time (s)'), ylabel('Amplitude');
title( 'Funcion Sinusoidal');

%% SINC

x = -10:0.1:10;
y = sinc(x);
plot(x, y, 'b'), grid on;
xlabel('x'), ylabel('sinc(x)');
title( 'Funcion Sinc');

%% Funcion Cuadrada

t = 0:0.01:4*pi;
frequency = 1;
duty_cycle = 50;
square_wave = square(2*pi*frequency*t, duty_cycle);
plot(t, square_wave, 'r'), grid on;
xlabel('Time (s)'), ylabel('Amplitude');
title( 'Funcion Cuadrada');
ylim([-1.2, 1.2]);

%% Funcion Triangular

t = 0:0.01:4*pi;
frequency = 1;
triangular_wave = sawtooth(2*pi*frequency*t, 0.5);
plot(t, triangular_wave, 'y'), grid on;
xlabel('Time (s)'), ylabel('Amplitude');
title('Funcion Triangular');
ylim([-1.2, 1.2]);

%% Diente de sierra

t = 0:0.01:4*pi;
frequency = 1;
sawtooth_wave = sawtooth(2*pi*frequency*t);
plot(t, sawtooth_wave, 'b'), grid on;
xlabel('Time (s)'), ylabel ( 'Amplitude');
title( 'Diente de sierra');
ylim([-1.2, 1.2]);

%% Real Exponencial

t = -5:0.01:5;
alpha_pos = 0.5;
alpha_neg = -0.5;
exponential_pos = exp(alpha_pos * t);
exponential_neg = exp(alpha_neg * t);
plot(t, exponential_pos, 'b'), grid on;;
hold on;
plot(t, exponential_neg, 'r'), grid on;
hold off;
xlabel('Time'), ylabel('Amplitude');
title( 'Real Exponencial');
legend('\alpha > 0', '\alpha < 0');

%% Exponencial Compleja

t = 0:0.01:10*pi;
alpha = 0.5;
commplex_exp = exp(1i * alpha * t);
figure;
plot(t, real(commplex_exp), 'b');
xlabel('Time'), ylabel('Real Part');
title( 'Parte Real');
figure;
plot(t, imag(commplex_exp), 'r');
xlabel('Time'), ylabel('Imaginary Part');
title( 'Parte imaginaria');
figure;
plot(real(commplex_exp), imag(commplex_exp), 'k'), grid on;
xlabel('Parte real'), ylabel('Parte Imaginaria');
title( 'Representacion del plano complejo');
axis equal;
