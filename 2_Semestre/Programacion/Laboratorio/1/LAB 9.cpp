#include <stdio.h>
int main(void)
{
	int N,CONT=2;
	double SUM,A=0,B=1;
	
	do
	{
	printf("\nIngrese la cantidad de numeros que deseas: ");
	scanf("%i",&N);
	}
	while (N<=0);
	
	if (N>=3)
	{
		printf("\n0 \n1 \n");
		for(CONT;CONT<N;CONT++)
		{
			SUM= A+B;
			A=B;
			B=SUM;
			printf("%.0f \n",SUM);
		}
	}
	else if (N==2)
	{
		printf("0 \n1");
	}
	else
	{
		printf("0");
	}
	return 0;
}
