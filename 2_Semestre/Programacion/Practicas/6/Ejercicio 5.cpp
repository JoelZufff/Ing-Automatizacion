#include <stdio.h>
int n=20;
int main(void)
{
	float A[n],max;
	int I,i,p;
	
	printf("Este programa registra 20 numeros reales en un arreglo y calcula el valor maximo y su posicion \n");
	
	for(I=0;I<n;I++)
	{
		printf("\nIngrese el %d numero real del arreglo: ",I+1);
		scanf("%f",&A[I]);
		
		if(I>0 && A[I]>max)
		{
			max=A[I];
			p=I;
		}
		else if (I==0)
		{
			max=A[I];
			p=I;
		}
	}
	
	printf("\nEl valor maximo ingresado fue: %.2f\nY ocupo la posicion: %d",max,p+1);
	return 0;
}
