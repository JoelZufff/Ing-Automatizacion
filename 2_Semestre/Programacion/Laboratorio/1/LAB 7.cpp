#include <stdio.h>
int main(void)
{
	int PAG,LEE;
	float PCT;
	
	printf("Ingrese la cantidad de paginas del libro: ");
	scanf("%i",&PAG);
	while (PAG<0) {
	printf("\nIngrese una cantidad VALIDA de paginas del libro: ");
	scanf("%i",&PAG);
	}
	
	printf("\nIngrese cuantas paginas lleva leidas: ");
	scanf("%i",&LEE);
	while (LEE<0 || LEE>PAG) {
	printf("\nIngrese una cantidad VALIDA de paginas leidas: ");
	scanf("%i",&LEE);
	}
	
	PCT=(LEE/(float)PAG)*100;
	printf("\nLleva leido el %.1f%% del libro",PCT);
	return 0;
}
