%Gráfica de control de posición
clc;
clear all;
close all;

%leyendo las muestras tomadas al sistema
fid=fopen('MONIT.TXT','r');
datos=fscanf(fid, '%f', [3 inf]);    % datos tiene 3 renglones
fclose(fid);
t=datos(1,:); 
y=datos(2,:);
u=datos(3,:);

figure(1)
subplot(2,1,1)
plot(t,y);
set(legend('$y[\frac{rad}{s}]$'), 'interpreter', 'latex')

grid on;

subplot(2,1,2)
plot(t,u);
set(legend('$u[V]$'), 'interpreter', 'latex')
xlabel('$t[s]$', 'interpreter', 'latex')
grid on;