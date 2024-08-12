%% Señales Originales

figure('Name','Original Signals','NumberTitle','off');
% Variables y funciones
t = -2:10e-3:2;
xt = tripuls(t,1,1);
yt = 0.5*rectpuls(t,1) + 0.5*rectpuls(t-0.25,1/2);

% Graficamos
subplot(1,2,1), plot(t,xt);
title ('x(t)'), xlabel ('t'), ylabel ('x(t)'), ylim ([ -0.1 1.2]);

subplot(1,2,2), plot(t,yt, 'r');
title ('y(t)'), xlabel ('t'), ylabel ('x(t)'), ylim ([ -0.1 1.2]);

%% Time Shifting
% Creamos funciones
xt1 = tripuls(t-0.75,1,1);
xt2 = tripuls(t+0.75,1,1);
yt1 = 0.5*rectpuls(t-0.75,1) + 0.5*rectpuls(t-1,1/2);
yt2 = 0.5*rectpuls(t+0.75,1) + 0.5*rectpuls(t+0.5,1/2);

% Graficamos
figure('Name','Time Shifting','NumberTitle','off');
subplot(1,2,1), plot(t,xt1), hold on, plot(t,xt2, 'r');
title ('Triangular'), xlabel ('t'), ylabel ('Amplitude'), ylim ([ -0.1 1.2]), legend('x( t - 0.75 )', 'x( t + 0.75 )');

subplot(1,2,2), plot(t,yt1), hold on, plot(t, yt2, 'r');
title ('Cuadrada'), xlabel ('t'), ylabel ('Amplitude'), ylim ([ -0.1 1.2]), legend('y( t - 0.75 )', 'y( t + 0.75 )');

%% Time Reversal
% Creamos funciones
xt = tripuls(-t,1,1);
yt = 0.5*rectpuls(t,1) + 0.5*rectpuls(-t-0.25,1/2);

% Graficamos
figure('Name','Time Reversal','NumberTitle','off');
subplot(1,2,1), plot(t,xt);
title ('x(t)'), xlabel ('t'), ylabel ('Amplitude'), ylim ([ -0.1 1.2]);

subplot(1,2,2), plot(t,yt,'r'), hold on;
title ('y(t)'), xlabel ('t'), ylabel ('Amplitude'), ylim ([ -0.1 1.2]);

%%  Time Scalling
% Creamos funciones
xt1 = tripuls(0.5*t,1,1);
xt2 = tripuls(1.5*t,1,1);
yt1 = 0.5*rectpuls(0.5*t,1) + 0.5*rectpuls(0.5 * t - 0.25,1/2);
yt2 = 0.5*rectpuls(1.5*t,1) + 0.5*rectpuls(1.5*t - 0.25,1/2);

% Graficamos
figure('Name','Time Scalling','NumberTitle','off');
subplot(1,2,1), plot(t,xt1), hold on, plot(t,xt2, 'r');
title ('Triangular'), xlabel ('t'), ylabel ('Amplitude'), ylim ([ -0.1 1.2]), legend('x( 0.5t )', 'x( 1.5t )');

subplot(1,2,2), plot(t,yt1), hold on, plot(t, yt2, 'r');
title ('Cuadrada'), xlabel ('t'), ylabel ('Amplitude'), ylim ([ -0.1 1.2]), legend('y( 0.5t )', 'y( 1.5t )');

%% Amplitude Scaling
% Creamos funciones
xt1 = 0.5*tripuls(t,1,1);
xt2 = 1.1*tripuls(t,1,1);
yt1 = 0.5*(0.5*rectpuls(t,1) + 0.5*rectpuls(t - 0.25,1/2));
yt2 = 1.1*(0.5*rectpuls(t,1) + 0.5*rectpuls(t - 0.25,1/2));

% Graficamos
figure('Name','Amplitude Scaling','NumberTitle','off');
subplot(1,2,1), plot(t,xt1), hold on, plot(t,xt2, 'r');
title ('Triangular'), xlabel ('t'), ylabel ('Amplitude'), ylim ([ -0.1 1.2]), legend('0.5x( t )', '1.1x( t )');

subplot(1,2,2), plot(t,yt1), hold on, plot(t, yt2, 'r');
title ('Cuadrada'), xlabel ('t'), ylabel ('Amplitude'), ylim ([ -0.1 1.2]), legend('0.5y( t )', '1.1y( t )');

%% Signal addition and multiplication.
% Creamos funciones
xt = tripuls(t,1,1);
yt = 0.5*rectpuls(t,1) + 0.5*rectpuls(t-0.25,1/2);
zt1 = xt + yt;
zt2 = xt .* yt;

% Graficamos
figure('Name','Signal addition and multiplication','NumberTitle','off');
subplot(1,2,1), plot(t,zt1);
title ('z(t) = x(t) + y(t)'), xlabel ('t'), ylabel ('Amplitude'), ylim ([ -0.1 2.1]);

subplot(1,2,2), plot(t,zt2,'r'), hold on;
title ('z(t) = x(t) * y(t)'), xlabel ('t'), ylabel ('Amplitudes'), ylim ([ -0.1 1.2]);
