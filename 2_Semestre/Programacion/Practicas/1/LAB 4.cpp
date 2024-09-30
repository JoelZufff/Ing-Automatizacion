#include <stdio.h>
int main(void)
{
	float N1,N2,N3, MAYOR, MEDIANO, MENOR;
	
	printf("Ingresa 3 numeros distintos: ");
	scanf("%f %f %f",&N1,&N2,&N3);
	if (N1>N2)
	{
		if (N1>N3)
		{
			MAYOR=N1;
			if (N2>N3)
			{
				MEDIANO=N2;
				MENOR=N3;
			}
			else
			{
				MEDIANO=N3;
				MENOR=N2;
			}
		}
		else
		{
			MAYOR=N3;
			MEDIANO=N1;
			MENOR=N2;
		}
	}
	else
	{
		if (N1>N3)
		{
			MAYOR=N2;
			MEDIANO=N1;
			MENOR=N3;
		}
		else
		{
			if (N2>N3)
			{
				MAYOR=N2;
				MEDIANO=N3;
				MENOR=N1;
			}
			else
			{
				MAYOR=N3;
				MEDIANO=N2;
				MENOR=N1;
			}
		}
	}
	printf("De mayor a menor: %.2f, %.2f, %.2f",MAYOR,MEDIANO,MENOR);
	return 0;
}
