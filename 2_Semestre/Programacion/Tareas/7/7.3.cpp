#include <stdio.h>
int main()
{
	int N,i=2;
	
	printf("Este programa recibe un numero entero positivo y detecta si es un numero primo o no\n");
	do
	{
		printf("\nIngrese un numero: ");
		scanf("%i",&N);
	}
	while (N<=0);
	/* Checar si N es divisible con algun numero menora a el*/
	i=N==1?1:i;
	for(i;N%i!=0;i++);
	
	if (i==N)
		printf("\n%i es un numero PRIMO",N);
	else
		printf("\n%i NO es un numero PRIMO",N);
	
	return 0;
}
