#include <stdio.h>
int main(void)
{
	float TOT,AP,RP;
	
	printf("Ingrese la cantidad de alumnos aprobados: ");
	scanf("%f",&AP);
	while (AP<0) {
		printf("\nIngrese una cantidad VALIDA de alumnos aprobados: ");
		scanf("%f",&AP);
	}
	
	printf("\nIngrese la cantidad de alumnos reprobados: ");
	scanf("%f",&RP);
	while (RP<0) {
		printf("\nIngrese una cantidad VALIDA de alumnos reprobados: ");
		scanf("%f",&RP);
	}
	
	TOT=AP+RP;
	AP= (AP/TOT)*100;
	RP= (RP/TOT)*100;
	
	printf("\nEl %.1f%% de alumnos APROBRO \nEl %.1f%% de alumnos REPROBO",AP,RP);
	return 0;
}
