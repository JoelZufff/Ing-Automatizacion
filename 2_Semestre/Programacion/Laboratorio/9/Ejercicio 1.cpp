#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int c,f,i,j;
	srand(time(NULL));
	
	printf("Ingrese las filas de la matriz:\t");
	scanf("%d",&f);
	printf("\nIngrese las columas de la matriz: ");
	scanf("%d",&c);
	
	int A[f][c];
	
	for(i=0;i<f;i++)
		for(j=0;j<c;j++)
			A[i][j]=rand()%21;
	
	printf("\nLa matriz generada es:\n\nA =");
	for(i=0;i<f;i++)
	{
		printf("\t");
		for(j=0;j<c;j++)
			printf("%d\t",A[i][j]);
		printf("\n");
	}
	
	printf("\n-----------------------------------------------------------------------------------\n");
	printf("\nLa matriz transpuesta es:\n\nAt =");
	for(i=0;i<c;i++)
	{
		printf("\t");
		for(j=0;j<f;j++)
			printf("%d\t",A[j][i]);
		printf("\n");
	}
}
