#include <stdio.h>
int n=15;

int main(void)
{
	int A[n],i;
	printf("Este programa guarda 15 numeros enteros en un arreglo y al finalizar los imprime en orden inverso\n");
	
	for(i=0;i<n;i++)
	{
		printf("\nIngrese el %d numero entero del arreglo: ",i+1);
		scanf("%d",&A[i]);
	}
	
	printf("Los numero ingresados en orden inverso son: ");
	for(i=n-1;i>=0;i--)
		printf("\n A[%d]= %d",i,A[i]);
}
