#include <stdio.h>
#include <math.h>

int main()
{
	float x1,y1,x2,y2,D;
	
	printf("Este programa recibe las coordenadas de 2 puntos en el plano cartesiano y calcula la distancia entre ellos");
	printf("\n\nIngrese las 2 coordenadas del primer punto A(x,y): ");
	scanf("%f %f",&x1,&y1);
	printf("\nIngrese las 2 coordenadas del punto B(x,y): ");
	scanf("%f %f",&x2,&y2);
	
	D=sqrt(pow(x2-x1,2)+pow(y2-y1,2));
	
	printf("\nLA DISTANCIA ENTRE LOS 2 PUNTOS ES DE = %f",D);
	return 0;
}
