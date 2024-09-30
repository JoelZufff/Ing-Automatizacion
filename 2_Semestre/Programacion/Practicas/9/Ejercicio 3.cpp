#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int o,i,j,det;
	
	do
	{
		system("cls");
		printf("Ingrese el orden de la matriz (2 o 3):\t");
		scanf("%d",&o);
	}
	while (o>3 || o<2);
	
	int A[o][o];
	
	for(i=0;i<o;i++)
		for(j=0;j<o;j++)
			A[i][j]=rand()%100;
	
	printf("\nLa matriz generada es:\n\nA =");
	for(i=0;i<o;i++)
	{
		printf("\t");
		for(j=0;j<o;j++)
			printf("%d\t",A[i][j]);
		printf("\n");
	}
	
	if(o==2)
	{
		det=A[0][0]*A[1][1]-A[0][1]*A[1][0];
	}
	else
	{
		det=A[0][0]*(A[1][1]*A[2][2]-A[1][2]*A[2][1]);
		det-=A[0][1]*(A[1][0]*A[2][2]-A[2][0]*A[1][2]);
		det+=A[0][2]*(A[1][0]*A[2][1]-A[2][0]*A[1][1]);
	}
	
	printf("\nLa determinante de la matriz es = %d",det);
}
