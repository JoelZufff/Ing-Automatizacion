#include <stdio.h>
int main ()
{	
	float a, b, c, inc, x1, x2,fx,A,B;
	
	printf("Ingrese los valores de la funcion a,b,c: ");
	scanf("%f %f %f", &a, &b, &c);
	 
	printf("\nLa fucion es: %gx^2 + %gx + %g",a,b,c);
	
	do
	{
		printf("\n\nIngrese el incremento: ");
		scanf("%f",&inc);
	}
	while (inc<=0 || inc>1);
	
	do{
		printf("\nIngrese el intervalo: [x1, x2]: ");
		scanf("%f %f",&x1,&x2);
	}
	while(x1>x2);
	
	do
	{
		A=a*(x1*x1);
		B=b*x1;
		fx=A+B+c;
		
		printf("\nf(%.2f) = %.2f", x1, fx);
		x1+=inc;
	}
	while (x1<=x2);
	
	if(x1-inc!=x2)
	{
	A=a*(x2*x2);
	B=b*x2;
	fx=A+B+c;
	
	printf("\nf(%.2f) = %.2f", x2, fx);
	}

	return 0;
}
