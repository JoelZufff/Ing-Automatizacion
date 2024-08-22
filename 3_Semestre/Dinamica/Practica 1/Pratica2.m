syms t;
a = 4*t^2+5*t;
fplot(t,a);
v = int(a,t);
fplot(t,v);