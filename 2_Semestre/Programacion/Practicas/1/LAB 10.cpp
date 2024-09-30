#include <stdio.h>
int main(void)
{
	float N1,N2,N3,N4,N5,N6,N7,N8,SUM;
	
	printf("Ingrese 8 numeros para la sumatoria: ");
	scanf("%f %f %f %f %f %f %f %f",&N1,&N2,&N3,&N4,&N5,&N6,&N7,&N8);
	
	SUM=(N1*N2)+(N3*N4)+(N5*N6)+(N7*N8);
	
	printf("\nEl resultado de la sumatoria es %.2f",SUM);
	return 0;
}
