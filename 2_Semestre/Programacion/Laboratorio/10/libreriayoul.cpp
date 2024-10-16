#include "libreriayoul.h"

void IMPRESION(int A[100][100], int f, int c)
{
	int i,j;
	
	for(i=0;i<f;i++)
	{
		putchar('\t');
		for(j=0;j<c;j++)
			printf("%d\t",A[i][j]);
		putchar('\n');
	}
}

void LECTURA(int A[100][100], int f, int c, int a)
{
	int i,j;
	
	for(i=0;i<f;i++)
	{
		for(j=0;j<c;j++)
		{
			if(a==1)
			{
				printf("\nIngrese el valor del arreglo en la posicion [%d][%d]:\t",i+1,j+1);
				scanf("%d",&A[i][j]);
			}
			else if(a==2)
			{
				A[i][j]=rand()%21;
			}
		}
	}
}

void SUMA(int A[100][100],int B[100][100],int C[100][100], int f, int c)
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

void RESTA(int A[100][100],int B[100][100],int C[100][100], int f, int c)
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

void MULTIPLICACION(int A[100][100],int B[100][100],int C[100][100], int f, int c, int cb)
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

void TRANSPUESTA(int A[100][100],int C[100][100], int f, int c)
{
	int i,j;
	
	for(i=0;i<c;i++)
	{
		for(j=0;j<f;j++)
			C[i][j]=A[j][i];
	}
}

int DETERMINANTE2X2(int A[100][100])
{
	int det;
	
	det=A[0][0]*A[1][1]-A[0][1]*A[1][0];
	
	return det;
}

int DETERMINANTE3X3(int A[100][100])
{
	int det;
	
	det=A[0][0]*(A[1][1]*A[2][2]-A[1][2]*A[2][1]);
	det-=A[0][1]*(A[1][0]*A[2][2]-A[2][0]*A[1][2]);
	det+=A[0][2]*(A[1][0]*A[2][1]-A[2][0]*A[1][1]);
	
	return det;
}
