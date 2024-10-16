#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
int n=20;

int main()
{
	float A[n],U[n],Na=0,Nu=0,*a,*u;
	int i;
	srand(time(NULL));
	
	for(i=0;i<n;i++) //Cargare los arreglos con numeros aleatorios del 0-50
	{
		A[i]=rand() % 51;
		
		a=&A[i];
		Na+=pow(*a,2);
	}
	
	Na=sqrt(Na);
	
	for(i=0;i<n;i++)
	{
		u=&U[i];
		*u=A[i]/Na;
		
		Nu+=pow(*u,2);
	}
	
	Nu=sqrt(Nu);
	
	printf("El vector es: \n\nA[%d] = (%g",n,A[0]);
	for(i=1;i<n;i++)
		printf(", %g",A[i]);
	printf(")");
	
	printf("\n\nEl vector unitaro de este es: \n\nU[%d] = (%g",n,U[0]);
	for(i=1;i<n;i++)
		printf(", %g",U[i]);
	printf(")");
	
	printf("\n\nLa norma del vector unitario es = %g",Nu);
}
