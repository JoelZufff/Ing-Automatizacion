#include <stdio.h>
#include <math.h>

int main (void)
{
	float v,a,d,altmax,t,tmax,vx,vy;
	float g=9.81,PI=3.14159265;
	
	printf("Programa que calcula el tiro parabólico en el eje x-y\n");
	
	printf("\nIngrese la velocidad inicial en m/s:");
	scanf("%f",&v);
	while(v<0)
	{
		printf("\nIngrese una velocidad inicial VALIDA en m/s:");
		scanf("%f",&v);
	}
	
	printf("\nIngrese el angulo del lanzamiento en grados: ");
	scanf("%f",&a);
	while(a<0)
	{
		printf("\nIngrese un angulo del lanzamiento VALIDO en grados: ");
		scanf("%f",&a);
	}
	
	printf("\nIngrese la distancia total del recorrido en metros: ");
	scanf("%f",&d);
	while(d<0)
	{
		printf("\nIngrese un angulo del lanzamiento VALIDO en grados: ");
		scanf("%f",&d);
	}

	a*=(PI/180.0);
	vx=v*(cos(a));
	vy=v*(sin(a));
	
	altmax= (pow(vy,2))/(2*g);
	t=(2*vy)/g;
	tmax=(-vy)/(-g);
	
	printf("\nResultados: \nAltura Maxima = %f metros\nPunto en el eje horizontal donde la altura es cero = %f\nTiempo en el aire = %f segundos\nTiempo hasta altura maxima = %f segundos\n",altmax,t,t,tmax);
}

