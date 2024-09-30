#include <stdio.h>
int main(void)
{
	int H;
	float AH=0,SD;
	
	printf("Ingrese las horas de trabajo: ");
	scanf("%i",&H);
	while (H<0 || H>24)
	{
		printf("Ingrese horas VALIDAS de trabajo: ");
		scanf("%i",&H);
	}
	if (H>8)
	{
		if (H>13)
		{
			SD= 11*8+(H-8)*19.55;
			AH= SD*0.1;
			SD= SD-AH;
		}
		else
		{
			SD= 11*8+(H-8)*19.55;
		}
	}
	else
	{
		SD=11*H;
	}
	printf("\nSalario Total: $%.2f \nSalario: $%.2f \nAhorro: $%.2f",(SD+AH),SD,AH);
	return 0;
}
