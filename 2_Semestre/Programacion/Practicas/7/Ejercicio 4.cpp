#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int n=20;

int main()
{
	float A[n],R[n],E,*a,*r;
	int i;
	srand(time(NULL));
	
	for(i=0;i<n;i++) //Cargare los arreglos con numeros aleatorios del 0-50
		A[i]=rand() % 51;
	
	printf("El vector por operar es: \n\nA[%d] = (%g",n,A[0]);
	for(i=1;i<n;i++)
		printf(", %g",A[i]);
	printf(")");
	
	printf("\n\nIngrese el escalar por el que va a multiplicar el vector: ");
	scanf("%f",&E);

	for(i=0;i<n;i++)
	{
		a=&A[i];
		r=&R[i];
		*r=(*a)*E;	
	}
	
	printf("\nEl vector resultante es: \n\nR[%d] = (%g",n,R[0]);
	for(i=1;i<n;i++)
		printf(", %g",R[i]);
	printf(")");
}
