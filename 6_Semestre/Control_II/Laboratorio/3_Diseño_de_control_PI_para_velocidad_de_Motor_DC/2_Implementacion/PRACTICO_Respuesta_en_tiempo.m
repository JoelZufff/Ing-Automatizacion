%Gráfica de control de posición
clc;
clear all;
close all;
%leyendo las muestras tomadas al sistema
fid=fopen('MONIT.TXT','r');
datos=fscanf(fid, '%f', [5 inf]);    % datos tiene 5 renglones
fclose(fid);
t=datos(1,:); 
r=datos(2,:);
y=datos(3,:);
u=datos(4,:);
e=datos(5,:);

figure(1)
subplot(3,1,1)
plot(t,r,t,y);
set(legend('$r[\frac{rad}{s}]$','$y[\frac{rad}{s}]$'), 'interpreter', 'latex')
grid on;

subplot(3,1,2)
plot(t,e);
set(legend('$e[\frac{rad}{s}]$'), 'interpreter', 'latex')
grid on;

subplot(3,1,3)
plot(t,u);
set(legend('$u[V]$'), 'interpreter', 'latex')
xlabel('$t[s]$', 'interpreter', 'latex')
grid on;

