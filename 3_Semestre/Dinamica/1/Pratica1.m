t = [0:0.25:30];

a = (6*t+2);
subplot(3,1,1);
plot(t,a)
xlabel('Tiempo');
ylabel('Aceleracion');
grid on;


v = (3*t.^2)+(2*t);
subplot(3,1,2);
plot(t,v,'r')
xlabel('Tiempo');
ylabel('Velocidad');
grid on;


s = (t.^3)+(t.^2);
subplot(3,1,3);
plot(t,s,'g')
xlabel('Tiempo');
ylabel('Posicion');
grid on;