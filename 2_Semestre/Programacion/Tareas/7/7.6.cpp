#include <stdio.h>
int main()
{
	int i,imen;
	float N=1,MEN=1e15;
	printf("Este programa recibe n numeros y detecta cual es el menor y su posicion, para dejar de ingresar numeros ingrese 0\n");
	
	for(i=1;N!=0;i++)
	{
		printf("\nIngrese un numero: ");
		scanf("%f",&N);
		if(N<MEN && N!=0)
		{
			MEN=N;
			imen=i;
		}
	}
	printf("\nEl numero menor es: %g\nFue el %i numero ingresado",MEN,imen);
	return 0;
}
