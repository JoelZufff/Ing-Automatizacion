#include <stdio.h>
int main()
{
	int C,I,M,Mult;
	
	do
	{
		printf("Ingrese la cantidad de numeros que quiere ver: ");
		scanf("%i",&C);
	}
	while (C<=0);
	
	do
	{
		printf("\nIngrese el indice: ");
		scanf("%i",&I);
	}
	while (I<=0);
	
		printf("\nIngrese el multiplo: ");
		scanf("%i",&M);
	
	printf("\nMultiplos:");
	for(int i=I;(i-I)!=C;i++)
	{
		Mult=i*M;
		printf("\n%i = %i",i,Mult);
	}
	
	return 0;
}
