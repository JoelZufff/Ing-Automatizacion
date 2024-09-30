#include <stdio.h>
int main()
{
	int N,div=2,exp=0;
	
	printf("Este programa expresa un numero natural como el producto de potencias de sus factores primos\n");
	
	do
	{
		printf("\nIngrese un numero: ");
		scanf("%i",&N);
	}
	while (N<1);
	
	printf("\n%i = ",N);
	if(N==1)
	printf("1^1");
	
	while(N>1)
	{
		while(N%div==0)
		{
			exp++;
			N/=div;
		}
		
		if(exp>0)
		{
			if(N!=1)
				printf("%d^%d * ",div,exp);
			else 
				printf("%d^%d  ",div,exp);		
		}
		
		exp=0;
		div++;
	}
	
	return 0;
}
