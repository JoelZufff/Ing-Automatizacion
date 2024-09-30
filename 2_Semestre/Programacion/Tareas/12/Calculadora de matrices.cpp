#include <stdio.h>
#include <stdlib.h>
#include <time.h>
const int MAXFIL=100,MAXCOL=100;

void LECTURA(float [MAXFIL][MAXCOL], int, int, int);
void SUMA(float [MAXFIL][MAXCOL],float [MAXFIL][MAXCOL],float [MAXFIL][MAXCOL], int, int);
void RESTA(float [MAXFIL][MAXCOL],float [MAXFIL][MAXCOL],float [MAXFIL][MAXCOL], int, int);
void MULTIPLICACION(float [MAXFIL][MAXCOL],float [MAXFIL][MAXCOL],float [MAXFIL][MAXCOL], int, int, int);
void IMPRESION(float [MAXFIL][MAXCOL], int, int);

int main()
{
	int OP,f,c,fb,cb,a;
	float A[MAXFIL][MAXCOL], B[MAXFIL][MAXCOL], C[MAXFIL][MAXCOL];
	srand(time(NULL));
	
	do
	{
		system("cls");
		printf("CALCULADORA DE MATRICES\n\n1. SUMA\n2. RESTA\n3. MULTIPLICACION\n");
		printf("\nIngrese la operacion a realizar:\t");
		scanf("%d",&OP);
	}
	while (OP<1 || OP>3);
		
	printf("\n-----------------------------------------------------------------------------------\n");
	if(OP==1 || OP==2)
	{
		printf("\nIngrese las filas que tendran las matrices:\t");
		scanf("%d",&f);
		printf("\nIngrese las columnas que tendran las matrices:\t");
		scanf("%d",&c);
	}
	else if(OP==3)
	{
		printf("\nIngrese las filas que tendra la matriz A:\t");
		scanf("%d",&f);
		printf("\nIngrese las columnas que tendra la matriz A:\t");
		scanf("%d",&c);
		
		printf("\n\nIngrese las filas que tendra la matriz B:\t");
			scanf("%d",&fb);
		while(fb!=c)
		{
			printf("\n\nLAS MATRICES NO SON CONFORMES\nReingrese las filas que tendra la matriz B:\t");
			scanf("%d",&fb);
		}
		printf("\nIngrese las columnas que tendra la matriz B:\t");
		scanf("%d",&cb);
	}
	
	printf("\n-----------------------------------------------------------------------------------\n");
	printf("\n1. FORMA MANUAL\n2. FORMA ALEATORIA\n\nIngrese como quiere rellenar la matriz:\t");
	scanf("%d",&a);
	
	while(a>2 || a<1)
	{
		printf("\nIngrese una opcion VALIDA de como quiere rellenar la matriz:\t");
		scanf("%d",&a);
	}
	
	if(a==1)
		printf("\n\nIngrese los valores de la matriz A:\n");
	LECTURA(A,f,c,a);
			
	if(a==1)
		printf("\n\nIngrese los valores de la matriz B:\n");
	if(OP==1 || OP==2)
		LECTURA(B,f,c,a);
	else if (OP==3)
		LECTURA(B,fb,cb,a);
	
	if(OP==1)
		SUMA(A,B,C,f,c);
	else if (OP==2)
		RESTA(A,B,C,f,c);
	else if(OP==3)
		MULTIPLICACION(A,B,C,f,c,cb);
		
	system("cls");
	printf("\nLas matriz o matrices ingresadas son:\n\nA =");
	IMPRESION(A,f,c);
	
	printf("\nB =");
	IMPRESION(B,f,c);
	printf("\nLas matriz resultado es:\n\nC =");
	IMPRESION(C,f,c);

	system("pause");
}

void LECTURA(float A[MAXFIL][MAXCOL], int f, int c, int a)
{
	int i,j;
	
	for(i=0;i<f;i++)
	{
		for(j=0;j<c;j++)
		{
			if(a==1)
			{
				printf("\nIngrese el valor del vector en la posicion [%d][%d]:\t",i+1,j+1);
				scanf("%f",&A[i][j]);
			}
			else if(a==2)
			{
				A[i][j]=rand()%21;
			}
		}
	}
}

void SUMA(float A[MAXFIL][MAXCOL],float B[MAXFIL][MAXCOL],float C[MAXFIL][MAXCOL], int f, int c)
{
	int i,j;
	
	for(i=0;i<f;i++)
	{
		for(j=0;j<c;j++)
		{
			C[i][j]=A[i][j]+B[i][j];
		}
	}
}

void RESTA(float A[MAXFIL][MAXCOL],float B[MAXFIL][MAXCOL],float C[MAXFIL][MAXCOL], int f, int c)
{
	int i,j;
	
	for(i=0;i<f;i++)
	{
		for(j=0;j<c;j++)
		{
			C[i][j]=A[i][j]-B[i][j];
		}
	}
}

void MULTIPLICACION(float A[MAXFIL][MAXCOL],float B[MAXFIL][MAXCOL],float C[MAXFIL][MAXCOL], int f, int c, int cb)
{
	int i,j,k,sum;
	
	for(i=0;i<f;i++)
	{
		for(j=0;j<cb;j++)
		{
			sum=0;
			for(k=0;k<c;k++)
			{
				sum+=(A[i][k])*(B[k][j]);	
			}
			C[i][j]=sum;
		}
	}
}

void IMPRESION(float A[MAXFIL][MAXCOL], int f, int c)
{
	int i,j;
	
	for(i=0;i<f;i++)
	{
		printf("\t");
		for(j=0;j<c;j++)
			printf("%g\t",A[i][j]);
		printf("\n");
	}
}
