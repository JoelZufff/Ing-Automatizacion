t = [0:1:10];
x1 = cos(t);
y1 = t.^2 +(0.01*t.^3);
z1 = 2 + (0.001*t.^3);

plot3(x1,y1,z1,'g--');
title('Grafica 1');
figure;

x2 = -sin(t);
y2 = (2*t)+(0.03*t.^2);
z2= (0.003*t.^2);
plot3(x2,y2,z2,'r--');
title('Grafica 2');
figure;

x3 = -cos(t);
y3 = (2+(0.06*t));
z3 = (0.006*t);
plot3(x3,y3,z3,'b--');
title('Grafica 3');