#include <stdio.h>
int main()
{
	int i=-1;
	float N,SUM=0,PRO;
	
	printf("Este programa recibe n numeros y calcula el promedio de estos, para detener el ingreso de numeros introduzca 0 \n");
	
	do
	{
		printf("\nIngrese un numero: ");
		scanf("%f",&N);
		SUM+=N;
		i++;
	}
	while(N!=0);
	
	PRO=SUM==0?0:SUM/i;
	printf("\nEl promedio es de = %g",PRO);
	
	return 0;
}
