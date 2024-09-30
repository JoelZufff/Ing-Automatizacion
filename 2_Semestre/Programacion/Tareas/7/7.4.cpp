#include <stdio.h>
int main()
{
	int N,imp=1;
	
	printf("Este programa recibe un numero entero positivo y pone n numeros primos\n");
	do
	{
		printf("\nIngrese un numero: ");
		scanf("%i",&N);
	}
	while (N<=0);
	
	printf("\n1");
	for(int N1=2;imp<N;N1++)
	{
		int i=2;
		for(i;N1%i!=0;i++);
		if (i==N1)
		{
			printf("\n%i",N1);
			imp++;
		}
	}
	
	return 0;
}
