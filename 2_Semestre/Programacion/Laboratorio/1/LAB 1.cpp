#include <stdio.h>
int main(void)
{
	float C1,C2,C3,PROM;
	
	printf("Ingresa las 3 calificaciones: ");
	scanf("%f %f %f",&C1,&C2,&C3);
	
	while ((C1>100 || C1<0) || (C3>100 || C3<0) || (C3>100 || C3<0))
	{
		printf("Ingresa 3 calificaciones VALIDAS: ");
		scanf("%f %f %f",&C1,&C2,&C3);
	}
	PROM=(C1+C2+C3)/3;
	if (PROM>=70)
	{
		printf("\nEl alumno SI aprobo con %f",PROM);
	}
	else
	{
		printf("\nEl alumno NO aprobo con %f",PROM);
	}
	return 0;
}
