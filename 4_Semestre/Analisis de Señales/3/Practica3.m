t = -3*pi:10e-3:3*pi;
N = 100;

T = 2*pi; A = 1; w = 2*pi/T;
%% Funcion cuadrada antisimetrica
xt = A*square(w*t);

% Serie exponencial de Fourier
exp_yt = 0;
cn = zeros(2*N+1,1);
index = 1;

% Sumatoria
for n = -N : N
    % Calculo valor de Cn
    if(mod(n,2))
        % Par
        cn(index) = (-j)*(2*A)/(pi*n);
    else
        % Impar
        cn(index) = 0;
    end
    
    % Calculo valor de serie de fourier
    exp_yt = exp_yt + cn(index)*exp(j*n*w*t);
    
    % Aumento el indice
    index = index+1;
end

% Calculo valores de magnitud y angulo de Cn
n = -N : N;
cmag = abs(cn);
cph = angle(cn);

% Grafico funciones
figure;
plot(t,xt,'--'), xlim ([ -3*pi 3*pi ]), ylim([-1.4 1.4]), xlabel ('t'), ylabel ('f(x)'), title('Exponencial de Fourier');
hold on, plot(t,exp_yt), legend('x(t)','y(t)');

% Grafico magnitud y angulo de Cn
figure;
subplot(2,1,1), stem(n,cmag),ylim ([ -0.2 0.8]), xlabel ('n'), ylabel ('C mag'), title('Amplitude');
subplot(2,1,2), stem(n,cph, 'r'), ylim ([ -2 2]), xlabel ('n'), ylabel ('Angle'), title('Angle');

% Serie trigonometrica de Fourier
tri_yt = 0;
an = zeros(N,1);
bn = zeros(N,1);

index = 2;

an(1) = 0;
bn(1) = 0;

% Sumatoria
for n = 1 : N
    % Calculo valor de an y bn
    if(mod(n,2))
        % Par
        an(index) = 0;
        bn(index) = 4/(n*pi);
    else
        % Impar
        an(index) = 0;
        bn(index) = 0;
    end
    
    % Calculo valor de serie de fourier
    tri_yt = tri_yt + an(index)*cos(n*w*t) + bn(index)*sin(n*w*t);
    
    % Aumento el indice
    index = index+1;
end

n = 0 : N;

% Grafico funciones
figure;
plot(t,xt,'--'), xlim ([ -3*pi 3*pi ]), ylim([-1.4 1.4]), xlabel ('t'), ylabel ('f(x)'), title('Trigonometrica de fourier');
hold on, plot(t,tri_yt), legend('x(t)','y(t)');

% Grafico de an y bn
figure;
subplot(2,1,1), stem(n,an),ylim ([ -0.2 0.8]), xlabel ('n'), ylabel ('a_n'), title('a_n');
subplot(2,1,2), stem(n,bn, 'r'), ylim ([ -0.2 1.5]), xlabel ('n'), ylabel ('b_n'), title('b_n');

%% Funcion dientes de sierra
xt = A*sawtooth(w*t - pi).*(A/2*square(w*t) + 0.5);

% Serie exponencial de Fourier
exp_yt = 0;
cn = zeros(2*N+1,1);
index = 1;

% Sumatoria
for n = -N : N
    % Calculo valor de Cn
    if(mod(n,2))
        % Par
        cn(index) = (-j)*(2*A)/(pi*n);
    else
        % Impar
        cn(index) = 0;
    end
    
    % Calculo valor de serie de fourier
    exp_yt = exp_yt + cn(index)*exp(j*n*w*t);
    
    % Aumento el indice
    index = index+1;
end

% Calculo valores de magnitud y angulo de Cn
n = -N : N;
cmag = abs(cn);
cph = angle(cn);

% Grafico funciones
figure;
plot(t,xt,'--'), xlim ([ -3*pi 3*pi ]), ylim([-1.4 1.4]), xlabel ('t'), ylabel ('f(x)'), title('Exponencial de Fourier');
hold on, plot(t,exp_yt), legend('x(t)','y(t)');

% Grafico magnitud y angulo de Cn
figure;
subplot(2,1,1), stem(n,cmag),ylim ([ -0.2 0.8]), xlabel ('n'), ylabel ('C mag'), title('Amplitude');
subplot(2,1,2), stem(n,cph, 'r'), ylim ([ -2 2]), xlabel ('n'), ylabel ('Angle'), title('Angle');

% Serie trigonometrica de Fourier
tri_yt = 0;
an = zeros(N,1);
bn = zeros(N,1);

index = 2;

an(1) = 0;
bn(1) = 0;

% Sumatoria
for n = 1 : N
    % Calculo valor de an y bn
    if(mod(n,2))
        % Par
        an(index) = 0;
        bn(index) = 4/(n*pi);
    else
        % Impar
        an(index) = 0;
        bn(index) = 0;
    end
    
    % Calculo valor de serie de fourier
    tri_yt = tri_yt + an(index)*cos(n*w*t) + bn(index)*sin(n*w*t);
    
    % Aumento el indice
    index = index+1;
end

n = 0 : N;

% Grafico funciones
figure;
plot(t,xt,'--'), xlim ([ -3*pi 3*pi ]), ylim([-1.4 1.4]), xlabel ('t'), ylabel ('f(x)'), title('Trigonometrica de fourier');
hold on, plot(t,tri_yt), legend('x(t)','y(t)');

% Grafico de an y bn
figure;
subplot(2,1,1), stem(n,an),ylim ([ -0.2 0.8]), xlabel ('n'), ylabel ('a_n'), title('a_n');
subplot(2,1,2), stem(n,bn, 'r'), ylim ([ -0.2 1.5]), xlabel ('n'), ylabel ('b_n'), title('b_n');