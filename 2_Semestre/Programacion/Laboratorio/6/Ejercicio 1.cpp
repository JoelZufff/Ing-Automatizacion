#include <stdio.h>
int main(void)
{
	int A[20],Cuenta[3]={0},i;
	
	printf("Este programa registra 20 numeros en un arreglo y cuenta los numeros positivos, negativos y ceros de este\n");
	for(i=0;i<20;i++)
	{
		printf("\nIngrese el %d numero del arreglo: ",i+1);
		scanf("%d",&A[i]);
		
		if(A[i]>0)
		{
			Cuenta[0]++;
			printf("Numero positivo agregado\n");
		}
		else if (A[i]<0)
		{
			Cuenta[1]++;
			printf("Numero negativo agregado\n");
		}
		else
		{
			Cuenta[2]++;
			printf("Numero cero agregado\n");
		}
	}
	
	printf("\nUSTED INGRESO: \n%d Numeros positivos\n%d Numeros negativos\n%d Ceros",Cuenta[0],Cuenta[1],Cuenta[2]);
}
