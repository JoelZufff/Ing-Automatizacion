#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int N=130;

void LECTURA(float **A, int o, int a);
void IMPRESION(float **A, int o);
float DETERMINANTE(float **A, int o);

int main()
{
	float **A;
	int o,i,a,b;
	
	do
	{
		system("cls");
		
		printf("\nCONFIGURACIONES INICIALES\n");
		for(i=0;i<N;i++)
			putchar('-');
		
		printf("\n\nIngrese el orden de la matriz:\t");
		scanf("%d",&o);
		
		while(o<2)
		{
			printf("\nIngrese un numero valido del orden de la matriz:\t");
			scanf("%d",&o);
		}
		
		A=(float **)calloc(o,sizeof(float *));
		for(i=0;i<o;i++)
			A[i]=(float *)calloc(o,sizeof(float));
		
		if(A == NULL)
		{
			printf("\nMEMORIA INSUFICIENTE VUELVA A ABRIR EL PROGRAMA");
			return -1;
		}
		
		do
		{
			printf("\n1. Forma Manual\n2. Forma Aleatoria (0-50)\n\nIngrese como quiere rellenar la Matriz:\t");
			scanf("%d", &a);
		}
		while(a<1 || a>2);
		
		LECTURA(A,o,a);
		
		system("cls");
		
		printf("\nLa matriz a OPERAR es:\n\nA =");
		IMPRESION(A,o);
		
		printf("\nLa determinante de la matriz es = %.2f",DETERMINANTE(A,o));
		
		printf("\n\nLa matriz a TRIANGULAR SUPERIOR es:\n\nA =");
		IMPRESION(A,o);
		
		putchar('\n');
		do
		{
			for(i=0;i<N;i++)
				putchar('-');
				
			printf("\n1. CONTINUAR :)\nX. FUGA\n\nIngrese si desea reiniciar la Matriz:\t");
			scanf("%d", &b);
		}
		while(b<1);
		
		free(A);
	}
	while(b==1);
	return 0;
	
}

void LECTURA(float **A, int o, int a)
{
	int i,j;
	srand(time(NULL));
	
	for(i=0;i<o;i++)
	{
		for(j=0;j<o;j++)
		{
			if(a==1)
			{
				printf("\nIngrese el valor del arreglo en la posicion [%d][%d]:\t",i+1,j+1);
				scanf("%f",&A[i][j]);
			}
			else if(a==2)
			{
				A[i][j]=rand()%51;
			}
		}
	}
}

void IMPRESION(float **A, int o)
{
	int i,j;
	
	for(i=0;i<o;i++)
	{
		putchar('\t');
		for(j=0;j<o;j++)
			printf("%.2f\t",A[i][j]);
		putchar('\n');
	}
}

float DETERMINANTE(float **A, int o)
{
	int i,j,k;
	float res, res1, res2, c, det=1;
	
	for(i=0;i<o-1;i++)
	{
		for (k=1;k<=((o-1)-i);k++)
		{
			res1=A[i][i];
			res2=A[i+k][i];
			c=res2/res1;
			
			for(j=0;j<o;j++)
			{
				res = A[i+k][j] - (c*A[i][j]);
				A[i+k][j]=res;
			}
	 	}
	}
	
	for(i=0;i<o;i++)
		det*=A[i][i];
		
	return det;
}
