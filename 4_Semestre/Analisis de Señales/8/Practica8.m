%% Realizamos muestreo
Fs = 44000; % Sampling frequency
Ts = 1/ Fs ; % Sampling period
Tmax = 5; % Record duration ( seconds )

t =0: Ts : Tmax - Ts ; % Time vector

rec = audiorecorder ( Fs ,16 ,1) ;
recordblocking( rec , Tmax ) ;
xt = getaudiodata ( rec ) ; % Convert audio into a vector

%% Sacamos transformada de fourier
X = fft (xt) ; % Calculate FFT
L = length ( xt ) ;
P1 = abs ( X / L ) ;
xw = P1 (1: L /2+1) ;
xw (2: end -1) = 2* xw (2: end -1) ;
w = Fs *(0:( L /2) ) / L ;

%% Graficamos resultados
figure, plot(t,xt,'b'), xlabel ('Tiempo'), ylabel ('Audio'), title('Time domain');
figure, plot (w , xw ), title ('Frequency domain '), xlim([0 6000]) , xlabel ('Frequency '), ylabel ('X(f)'), grid on;
