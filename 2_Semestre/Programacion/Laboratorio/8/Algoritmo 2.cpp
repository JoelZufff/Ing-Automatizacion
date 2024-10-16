#include <stdio.h>
#include <stdlib.h>
#include <time.h>
const int T=35;
int main()
{
	int i,B,A[T],cont=0,*c;
	srand(time(NULL));
	
	for(i=0;i<T;i++)
		A[i]=rand() % 11;
	
	printf("El vector con numeros del 0-20 es:\n\n");
	printf("A = (%d",A[0]);
	for(i=1;i<T;i++)
	{
		printf(", %d",A[i]);
	}
	printf(")\n");
	
	do
	{
		printf("\nIngrese el numero que desea buscar en el arreglo:\t");
		scanf("%d",&B);
	}
	while(B<0 || B>10);
	
	printf("\nEl numero se repite en las posiciones:");
	for(i=0;i<T;i++)
	{
		c=&A[i];
		
		if(*c==B)
		{
			printf(" [%d]",i+1);
			cont++;
		}
	}
	
	if(cont==0)
		printf("\n\nEl numero no se encuentra en el arreglo");
	else
		printf("\n\nEL numero se repite %d veces",cont);
}
