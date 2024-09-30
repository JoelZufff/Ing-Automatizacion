#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libreriayoul.h"

int N=130;
int main()
{
	int A[100][100], B[100][100], C[100][100];
	int i,f,c,fb,cb,a,OP;
	srand(time(NULL));
	
	do
	{
		system("cls");
		printf("CALCULADORA DE MATRICES\n\n1. SUMA\n2. RESTA\n3. TRANSPUESTA\n4. MULTIPLICACION\n5. DETERMINANTE 2X2\n6. DETERMINANTE 3X3");
		printf("\n\nIngrese la operacion a realizar:\t");
		scanf("%d",&OP);
	}
	while (OP<1 || OP>6);
	
	system("cls");
	printf("\nCONFIGURACIONES INICIALES\n");
	for(i=0;i<N;i++)
		putchar('-');
		
	switch(OP)
	{
		case 1:
		case 2:
		{
			do
			{
				printf("\n\nIngrese las FILAS que tendran las matrices:\t");
				scanf("%d",&f);
			}
			while(f<0 || f>100);
			
			do
			{
				printf("\nIngrese las COLUMNAS que tendran la matrices:\t");
				scanf("%d",&c);
			}
			while(c<0 || c>100);
			
			do
			{
				printf("\n1. Forma Manual\n2. Forma Aleatoria (0-20)\n\nIngrese como quiere rellenar la Matriz:\t");
				scanf("%d", &a);
			}
			while(a<1 || a>2);
	
			system("cls");
			printf("\LLENADO DE MATRIZ\n");
	 	
			for(i=0;i<N;i++)
				putchar('-');
			
			printf("\nIngrese los valores de la matriz A:\n");
			LECTURA(A,f,c,a);
			
			printf("\nIngrese los valores de la matriz B:\n");
			LECTURA(B,f,c,a);
		
			if(OP==1)
				SUMA(A,B,C,f,c);
			else if(OP==2)
				RESTA(A,B,C,f,c);
				
			system("cls");
			printf("\IMPRESION DE MATRICES\n");
	 	
			for(i=0;i<N;i++)
				putchar('-');
				
			printf("\n\nLas matrices ingresadas son:\n\nA =");
			IMPRESION(A,f,c);
			printf("\nB =");
			IMPRESION(B,f,c);
			
			printf("\nLas matriz resultado es:\n\nC =");
			IMPRESION(C,f,c);
		}
		break;
		
		case 3:
		{
			do
			{
				printf("\n\nIngrese las FILAS que tendra la matriz:\t\t");
				scanf("%d",&f);
			}
			while(f<0 || f>100);
			
			do
			{
				printf("\nIngrese las COLUMNAS que tendra la matriz:\t");
				scanf("%d",&c);
			}
			while(c<0 || c>100);
			
			do
			{
				printf("\n1. Forma Manual\n2. Forma Aleatoria (0-20)\n\nIngrese como quiere rellenar la Matriz:\t");
				scanf("%d", &a);
			}
			while(a<1 || a>2);
	
			system("cls");
			printf("\LLENADO DE MATRIZ\n");
	 	
			for(i=0;i<N;i++)
				putchar('-');
			
			printf("\nIngrese los valores de la matriz A:\n");
			LECTURA(A,f,c,a);
			
			TRANSPUESTA(A,C,f,c);
			
			system("cls");
			printf("\IMPRESION DE MATRICES\n");
	 	
			for(i=0;i<N;i++)
				putchar('-');
				
			printf("\n\nLas matriz ingresada fue:\n\nA =");
			IMPRESION(A,f,c);
			
			printf("\nLas matriz resultado es:\n\nC =");
			IMPRESION(C,c,f);
		}
		break;
		
		case 4:
		{
			do
			{
				printf("\n\nIngrese las FILAS que tendra la matriz A:\t");
				scanf("%d",&f);
			}
			while(f<0 || f>100);
			
			do
			{
				printf("\nIngrese las COLUMNAS que tendra la matriz A:\t");
				scanf("%d",&c);
			}
			while(c<0 || c>100);
			
			printf("\n\nIngrese las FILAS que tendra la matriz B:\t");
				scanf("%d",&fb);
			while(fb!=c)
			{
				printf("\n\nLAS MATRICES NO SON CONFORMES\n\nReingrese las filas que tendra la matriz B:\t");
				scanf("%d",&fb);
			}
			do
			{
				printf("\nIngrese las COLUMNAS que tendra la matriz B:\t");
				scanf("%d",&cb);
			}
			while(cb<0 || cb>100);
			
			do
			{
				printf("\n1. Forma Manual\n2. Forma Aleatoria (0-20)\n\nIngrese como quiere rellenar la Matriz:\t");
				scanf("%d", &a);
			}
			while(a<1 || a>2);
			
			system("cls");
			printf("\LLENADO DE MATRIZ\n");
	 	
			for(i=0;i<N;i++)
				putchar('-');
			
			printf("\nIngrese los valores de la matriz A:\n");
			LECTURA(A,f,c,a);
			
			printf("\nIngrese los valores de la matriz B:\n");
			LECTURA(B,fb,cb,a);
		
			MULTIPLICACION(A,B,C,f,c,cb);
				
			system("cls");
			printf("\IMPRESION DE MATRICES\n");
	 	
			for(i=0;i<N;i++)
				putchar('-');
				
			printf("\n\nLas matrices ingresadas son:\n\nA =");
			IMPRESION(A,f,c);
			printf("\nB =");
			IMPRESION(B,fb,cb);
			
			printf("\nLas matriz resultado es:\n\nC =");
			IMPRESION(C,f,cb);
		}
		break;
		
		case 5:
		{
			do
			{
				printf("\n1. Forma Manual\n2. Forma Aleatoria (0-20)\n\nIngrese como quiere rellenar la Matriz:\t");
				scanf("%d", &a);
			}
			while(a<1 || a>2);
	
			system("cls");
			printf("\LLENADO DE MATRIZ\n");
	 	
			for(i=0;i<N;i++)
				putchar('-');
			
			printf("\nIngrese los valores de la matriz A:\n");
			LECTURA(A,2,2,a);
			
			system("cls");
			printf("\IMPRESION DE MATRIZ\n");
	 	
			for(i=0;i<N;i++)
				putchar('-');
				
			printf("\n\nLas matriz ingresada fue:\n\nA =");
			IMPRESION(A,2,2);
			
			printf("\nLa determinante de la matriz es = %d",DETERMINANTE2X2(A));
		}
		break;
		
		case 6:
		{
			do
			{
				printf("\n1. Forma Manual\n2. Forma Aleatoria (0-20)\n\nIngrese como quiere rellenar la Matriz:\t");
				scanf("%d", &a);
			}
			while(a<1 || a>2);
	
			system("cls");
			printf("\LLENADO DE MATRIZ\n");
	 	
			for(i=0;i<N;i++)
				putchar('-');
			
			printf("\nIngrese los valores de la matriz A:\n");
			LECTURA(A,3,3,a);
			
			system("cls");
			printf("\IMPRESION DE MATRIZ\n");
	 	
			for(i=0;i<N;i++)
				putchar('-');
				
			printf("\n\nLas matriz ingresada fue:\n\nA =");
			IMPRESION(A,3,3);
			
			printf("\nLa determinante de la matriz es = %d",DETERMINANTE3X3(A));
		}
		break;
		
		default:
		break;
	}
	return 0;
}
