#include <stdio.h>
#include <math.h>

int main(void)
{
	int t,f;
	double x,R,PI=3.14159265;
	do
	{
		printf("\nFunciones Trigonometricas:\n\n1. Seno\n2. Coseno\n3. Tangente");
		printf("\n\nIngrese el numero de la funcion trigonometrica que desea realizar: ");
		scanf("%d",&t);
	}
	while (t<1 || t>3);
	
	do
	{
	printf("\nFormas de resultado:\n\n1.Grados\n2.Radianes");
	printf("\n\nIngrese el la forma en que desea ingresar el numero: ");
	scanf("%d",&f);	
	}
	while (f<1 || f>2);
	
	printf("\nIngrese el numero a operar: ");
	scanf("%lf",&x);
	
	if(f==1)
		x*=(PI/180.0);
	
	switch (t)
	{
		case 1:
			R=sin(x);
		break;
		case 2:
			R=cos(x);
		break;
		case 3:
			R=tan(x);
		break;
	}
		
	printf("\nEL RESULTADO ES = %lf",R);
	return 0;
}
