#include <stdio.h>
int main()
{
	float N,SUM=0;
	
	printf("Este programa recibe n numeros y calcula la sumatoria de estos, para detener el ingreso de numeros introduzca 0 \n");
	do
	{
		printf("\nIngrese un numero: ");
		scanf("%f",&N);
		SUM+=N;
	}
	while(N!=0);
	printf("\nLa sumatoria es de = %g",SUM);
}
