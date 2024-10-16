#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
	int i,N,x1,x2,c;
	srand(time(NULL));
	
	printf("Este programa recibe un intervalo y genera N numeros aleatorios, despues los ordena de menor a mayor\n");
	
	do 
	{
		printf("\nIngrese la cantidad de numeros aleatorios a generar: ");
		scanf("%d",&N);
	}
	while (N<=0);
	
	int a[N];
	
	do 
	{
		printf("\nIngrese el intervalo de los numeros [x1,x2]: ");
		scanf("%d %d",&x1,&x2);
	}
	while (x1>=x2);
	
	for(i=0;i<N;i++)
		a[i]= rand() % (x2-x1+1)+x1;
	
	
	for(int j=N-1;j>0;j--) 
	{
		for(i=0;i<j;i++) 
		{
			if(a[i]>a[i+1]) 
			{
				c=a[i];
				a[i]=a[i+1];
				a[i+1]=c;
			}
		}
	}
	
	printf("\nDe menor a mayor:\n");
	for(i=0;i<N;i++)
	printf("\nNumero aleatorio %d =\t%d",i+1,a[i]);
}
