#include <stdio.h>
int main()
{
	int T,*minIndex,*j,*i,*t;
	
	do
	{
		printf("Ingrese el tamaño del vector del que se sacara el valor minimo: ");
		scanf("%d",&T);
	}
	while (T<2);
	
	int A[T];
	
	for(int k=0;k<T;k++)
	{
		printf("\nIngrese el valor %d del arreglo: ",k+1);
		scanf("%d",&A[k]);
	}
	
	i=&A[0];
	t=&A[T-1];
	minIndex=&A[0];
	
	for(i;i<t;i++)
		for(j=i+1;j<t+1;j++)
		{
			if(*minIndex>*j)
				minIndex=j;
		}
	printf("\nEl valor minimo es %d",*minIndex);
	
	return 0;
}
