%Gráfica de control de posición
clc;
clear all;
close all;
%leyendo las muestras tomadas al sistema
fid=fopen('datos.TXT','r');
datos=fscanf(fid, '%f', [9 inf]);    % datos tiene 9 renglones
fclose(fid);
t=datos(1,:); 
alpha=datos(2,:);
theta=datos(3,:);
v=datos(4,:);
vd=datos(5,:);
omegal=datos(6,:); 
omegar=datos(7,:);
ul=datos(8,:);
ur=datos(9,:);

figure(1)
subplot(5,1,1)
plot(t,vd,t,v);
ylim([-0.5 0.5]);
set(legend('$v_d[\frac{m}{s}]$','$v[\frac{m}{s}]$'), 'interpreter', 'latex')
grid on;

subplot(5,1,2)
plot(t,theta);
%ylim([-0.015 0.015]);
set(legend('$\theta[rad]$'), 'interpreter', 'latex')
grid on;

subplot(5,1,3)
plot(t,alpha);
%ylim([-20 20]);
set(legend('$\alpha[rad]$'), 'interpreter', 'latex')
grid on;

subplot(5,1,4)
plot(t,omegal,t,ul);
%ylim([-20 20]);
set(legend('$\omega_l[\frac{rad}{s}]$','$u_l[V]$'), 'interpreter', 'latex')
grid on;

subplot(5,1,5)
plot(t,omegar,t,ur);
%ylim([-20 20]);
set(legend('$\omega_r[\frac{rad}{s}]$','$u_r[V]$'), 'interpreter', 'latex')
xlabel('$t[s]$', 'interpreter', 'latex')
grid on;

