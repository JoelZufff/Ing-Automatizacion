#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int n=20;

int main(void)
{
	int A[n],i,c=0,P[n];
	srand(time(NULL));
	printf("Este programa crea 20 numeros aleatorios del 0-50 y al finalizar cuenta los mayores que 30 y en que posicion estan\n");
	
	for(i=0;i<n;i++) //Repite el proceso en funcion al tamaño del arreglo
	{
		A[i]=rand() % 51; //Genera un numero aleatorio del 0-50
		
		if(A[i]>30) //Checa si el numero es mayor que 30
		{
			P[c]=i; // En el arreglo P se guarda la posicion del numero en el arreglo
			c++; //Se suma 1 a la cantidad de numeros que cumplen la condicion
		}
	}
	
	if(c>0) //Si hay numeros mayores que 30
	{
		printf("\nHay %d numero mayores que 30 y ocupan las posiciones en el arreglo: \n",c);
		for(i=0;i<c;i++)
		printf("%d\n",P[i]);
	}
	else
		printf("No hay numeros mayores que 30");
}
