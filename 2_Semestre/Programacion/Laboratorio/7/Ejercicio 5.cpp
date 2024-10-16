#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
int n=20;

int main()
{
	float A[n],Norma=0,*a;
	int i;
	srand(time(NULL));
	
	for(i=0;i<n;i++) //Cargare los arreglos con numeros aleatorios del 0-50
	{
		A[i]=rand() % 51;
		
		a=&A[i];
		Norma+=pow(*a,2);
	}
	
	Norma=sqrt(Norma);
	
	printf("El vector por sacar la norma es: \n\nA[%d] = (%g",n,A[0]);
	for(i=1;i<n;i++)
		printf(", %g",A[i]);
	printf(")");
	
	printf("\n\nLa norma del vector es = %g",Norma);
}
