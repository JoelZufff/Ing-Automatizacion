#include <stdio.h>
int n=15;
int main(void)
{
	int A[n],i,c=0;
	
	printf("Este programa registra 15 numeros enteros positivos y negativos en un arreglo y calcula numero de valores pares y positivos \n");
	
	for(i=0;i<n;i++)
	{
		printf("\nIngrese el %d numero del arreglo (Diferente a 0): ",i+1);
		scanf("%d",&A[i]);
		
		while(A[i]==0)
		{
			printf("\nIngrese de nuevo el %d numero del arreglo (DIFERENTE A 0): ",i+1);
			scanf("%d",&A[i]);
		}
		
		if(A[i]>0 && A[i]%2==0)
			c++;
	}
	
	printf("\nUSTED INGRESO: %d Numeros pares positivos",c);
}
