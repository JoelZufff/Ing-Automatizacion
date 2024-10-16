#include <stdio.h>
int main(void)
{
	int N1,N2,N3;
	printf("Ingrese 3 numeros enteros diferentes: ");
	scanf("%i %i %i",&N1,&N2,&N3);
	if (N1>N2)
	{
		if (N1>N3)
		{
			printf("\n%i ES EL MAYOR",N1);
		}
		
	}
	else
	{
		if (N2>N3)
		{
			printf("\n%i ES EL MAYOR",N2);
		}
		else
		{
			printf("\n%i ES EL MAYOR",N3);
		}
	}
	return 0;
}
