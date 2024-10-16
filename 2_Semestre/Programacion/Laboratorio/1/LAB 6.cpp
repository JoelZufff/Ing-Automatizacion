#include <stdio.h>
int main(void)
{
	int OP,OUT=1;
	float N1,N2,ANS;
	
	while(OUT!=0) {
	printf("\n1. Suma \n2. Resta \n3. Multiplicacion \n4. Division \n\nIngrese el numero de la operacion a realizar: ");
	scanf("%i",&OP);
	while (OP>4 || OP<1)
	{
		printf("\nIngresa un numero VALIDO: ");
		scanf("%i",&OP);
	}
	
	printf("\nIngrese 2 numeros en el orden que quiere que sean operados: ");
	scanf("%f %f",&N1,&N2);
	
	if(OP==1) {
		ANS=N1+N2;
	}
	else {
		if(OP==2) {
			ANS=N1-N2;
		}
		else {
			if(OP==3){
			ANS=N1*N2;
			}
			else {
				if(OP==4 && N2!=0) {
					ANS=N1/N2;
				}
				else
				while (N2==0){
					printf("\nIngresa otro numero para el denominador diferente a 0: ");
					scanf("%f",&N2);
					ANS=N1/N2;
				}
			}
		}
	}
	printf("\nEl resultado es %.2f",ANS);
	
	printf("\n\nSi quiere dejar de operar presione 0 sino presione otro numero: ");
	scanf("%i",&OUT);
}
return 0;
}
