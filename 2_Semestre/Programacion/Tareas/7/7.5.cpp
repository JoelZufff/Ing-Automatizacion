#include <stdio.h>
int main()
{
	float N1,N2,MA;
	printf("Este programa recibe n numeros y detecta cual es el mayor, para dejar de ingresar numeros ingrese 0\n");
	printf("\nIngrese un numero: ");
	scanf("%f",&N1);
	
	do
	{
		printf("\nIngrese otro numero: ");
		scanf("%f",&N2);
		N1=N1>N2?N1:N2;
	}
	while(N2!=0);
	printf("\nEl numero mayor es: %g",N1);
	return 0;
}
