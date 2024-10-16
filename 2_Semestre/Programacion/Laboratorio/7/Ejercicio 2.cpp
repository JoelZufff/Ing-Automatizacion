#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int n=20;

int main()
{
	float A[n],B[n],R[n],*a,*b,*c;
	int i;
	srand(time(NULL));
	
	for(i=0;i<n;i++) //Cargare los arreglos con numeros aleatorios del 0-50
	{
		A[i]=rand() % 51;
		B[i]=rand() % 51;
		
		a=&A[i];
		b=&B[i];
		c=&R[i];
		*c=*a-*b;
	}
	
	printf("Los 2 vectores por restar son: \n\nA[%d] = (%g",n,A[0]);
	for(i=1;i<n;i++)
		printf(", %g",A[i]);
	printf(")\nB[%d] = (%g",n,B[0]);
	for(i=1;i<n;i++)
		printf(", %g",B[i]);
	printf(")\n");

	printf("\nEl vector resultante de la resta de los 2 vectores es: \n\nR[%d] = (%g",n,R[0]);
	for(i=1;i<n;i++)
		printf(", %g",R[i]);
	printf(")");
}
