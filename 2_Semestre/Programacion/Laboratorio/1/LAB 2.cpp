#include <stdio.h>
int main(void)
{
	int N1,N2;
		
	printf("Ingrese el primer numero: ");
	scanf("%i",&N1);
	printf("\nIngrese el segundo numero (Menor que el primero) Y diferente a 0: ");
	scanf("%i",&N2);
	while (N2==0 || N2>N1) {
	printf("\nIngrese el segundo numero (MENOR que el primero) Y DIFERENTE A 0: ");
	scanf("%i",&N2);
	}
	if (N1%N2==0)
	{
		printf("\nSI ES DIVISIBLE");
	}
	else
	{
		printf("\nNO ES DIVISIBLE");
	}
	return 0;
}
