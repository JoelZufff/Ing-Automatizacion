#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int c,f,i,j,k,*maxIndex;
	srand(time(NULL));
	
	printf("Ingrese las filas de la matriz:\t");
	scanf("%d",&f);
	printf("\nIngrese las columas de la matriz: ");
	scanf("%d",&c);
	
	int A[f][c];
	
	for(i=0;i<f;i++)
		for(j=0;j<c;j++)
			A[i][j]=rand()%100;
	
	printf("\nLa matriz generada es:\n\nA =");
	for(i=0;i<f;i++)
	{
		printf("\t");
		for(j=0;j<c;j++)
			printf("%d\t",A[i][j]);
		printf("\n");
	}
	
	printf("\nEl valor maximo de cada fila es:\n");
	for(k=0;k<f;k++)
	{
		maxIndex=&A[k][0];
		for(i=0;i<c-1;i++)
			for(j=i+1;j<c;j++)
			{
				if(*maxIndex<A[k][j])
					maxIndex=&A[k][j];
			}
		printf("\nFila [%d] =\t%d",k+1,*maxIndex);
	}
	
	printf("\n\nEl valor maximo de cada columna es:\n");
	for(k=0;k<c;k++)
	{
		maxIndex=&A[0][k];
		for(i=0;i<f-1;i++)
			for(j=i+1;j<f;j++)
			{
				if(*maxIndex<A[j][k])
					maxIndex=&A[j][k];
			}
		printf("\nColumna [%d] =\t%d",k+1,*maxIndex);
	}
	
	maxIndex=&A[0][0];
	for(k=0;k<f;k++)
	{
		for(i=0;i<c-1;i++)
			for(j=i+1;j<c;j++)
			{
				if(*maxIndex<A[k][j])
					maxIndex=&A[k][j];
			}
	}
	printf("\n\nValor maximo de la matriz = %d",*maxIndex);
}
