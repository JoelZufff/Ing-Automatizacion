#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define ren 50
#define col 180

void REGLAS(int, int, int, int);
int VECINOS(int, int, int, int);
void ACTMATRIZ(int, int);
void IMPRESION(int A[ren][col], int, int);

int A[ren][col]= {0}, B[ren][col];

int main()
{
	int i,j,k,G,P,f,c,x,y,cont;
	srand(time(NULL));

	printf("BIENVENIDO AL JUEGO DE LA VIDA\n\nPara comenzar presione F11 para poner pantalla completa\n\n");
	for(i=0;i<120;i++)
		printf("-");
	printf("\n\nCONFIGURACION INICIAL\n");
	
	do
	{
		printf("\nIngrese el numero de generaciones que desea correr:\t\t");
		scanf("%d",&G);
	}
	while (G<1);
	
	do
	{
		printf("\nIngrese el numero de filas que tendra el juego (1-50):\t\t");
		scanf("%d",&f);
	}
	while(f<1 || f>50);
	
	do
	{
		printf("\nIngrese el numero de columnas que tendra el juego (1-180):\t");
		scanf("%d",&c);
	}
	while(c<1 || c>180);	
	
	putchar('\n');
	for(i=0;i<120;i++)
			printf("-");
			
	printf("\n\n1. Rellenar de forma aleatoria\n2. Rellenar de forma manual\n\nIngrese como quiere rellenar su malla:\t");
	scanf("%d",&j);
	
	if(j<1 || j>2)
	{
		do
		{
			printf("\nIngrese un numero VALIDO de como como quiere rellenar su malla:\t");
			scanf("%d",&j);
		}
		while(j<1 || j>2);
	}
	
	if(j==1)
	{
		do
		{
			printf("\nIngrese hasta %d puntos aleatorios que desee agregar:\t\t",f*c);
			scanf("%d",&P);
		}
		while(P<1 || P>(f*c));
		
		for(i=0;i<P;i++)
		{
			do
			{
				x = rand() % f;
				y = rand() % c;
			}
			while (A[x][y] == 1);
			
			A[x][y]=1;
		}
	}
	else if(j==2)
	{
		system("cls");
		printf("\nINGRESO DE COORDENADAS MANUALES (Ingrese 0 para terminar)\n");
		cont=1;
		do
		{
			for(i=0;i<120;i++)
			printf("-");
			
			printf("\nCoordenadas del punto %d\n",cont);
			do
			{
				printf("\nIngrese una coordenada entre (1-%d) para x:\t",f);
				scanf("%d",&x);
				
				printf("\nIngrese una coordenada entre (1-%d) para y:\t",c);
				scanf("%d",&y);
			}
			while((x<0 || x>f) || (y<0 || y>c) || A[x-1][y-1]==1);
			printf("\n Se agrego una vida en el punto [%d][%d]\n\n",x,y);
			cont++;
			
			if(x!=0 && y!=0)
				A[x-1][y-1]=1;
		}
		while(x!=0 && y!=0);
	}
		
	system("cls");
	printf("PUNTO DE PARTIDA:\n");
	IMPRESION(A,f,c);

	system("pause");
	
	for(k=0;k<G;k++)
	{	
		system("cls");
		printf("Generacion Numero: %d\n",k+1);
		cont=0;
		for(i=0;i<f;i++)
			for(j=0;j<c;j++)
			{
				REGLAS(i,j,f,c);
				cont+=B[i][j];
			}
			
		ACTMATRIZ(f,c);
		IMPRESION(A,f,c);
		
		if(cont==0)
		{
			printf("\nOCURRIO UNA EXTINCION MASIVA EN LA GENERACION %d HASTA PRONTO\n",k+1);
			k=G;
		}
		
		Beep(1000,300);
		Sleep(400);	
	}
	Beep(1500,1000);
}

void IMPRESION(int A[ren][col], int f, int c)
{
	int i,j;
	
	printf("\n");
	for(i=0;i<f;i++)
	{
		printf("\t |");
		for(j=0;j<c;j++)
		{
			if(A[i][j]==0)
				printf("%c",176);
			else if(A[i][j]==1)
				printf("%c",219);
		}
		printf("|\n");
	}
}

void ACTMATRIZ(int f, int c)
{
	int i,j;
	
	for(i=0; i<f; i++)
	{
		for(j=0;j<c;j++)
		{
			A[i][j]=B[i][j];
			B[i][j]=0;
		}
	}
}

void REGLAS(int x, int y, int f, int c)
{
	int aux = VECINOS(x,y,f,c);
	if(A[x][y]==1)
	{
		if(aux<=1)
			B[x][y]=0;
		else if(aux==2 || aux==3)
			B[x][y]=1;
		else if(aux>3)
			B[x][y]=0;
	}
	else if (A[x][y]==0)
	{
		if(aux==3)
			B[x][y]=1;
	}
}

int VECINOS(int x, int y, int f, int c)
{
		int cont=0;
	
	if((x-1>=0 && x-1<f) && (y-1>=0 && y-1<c))
		if(A[x-1][y-1]==1)
			cont++;
	
	if((x-1>=0 && x-1<f) && (y>=0 && y<c))	
		if(A[x-1][y]==1)
			cont++;
	
	if((x-1>=0 && x-1<f) && (y+1>=0 && y+1<c))	
		if(A[x-1][y+1]==1)
			cont++;
		
	if((x>=0 && x<f) && (y+1>=0 && y+1<c))
		if(A[x][y+1]==1)
			cont++;
		
	if((x+1>=0 && x+1<f) && (y+1>=0 && y+1<c))
		if(A[x+1][y+1]==1)
			cont++;
		
	if((x+1>=0 && x+1<f) && (y>=0 && y<c))
		if(A[x+1][y]==1)
			cont++;
		
	if((x+1>=0 && x+1<f) && (y-1>=0 && y-1<c))
		if(A[x+1][y-1]==1)
			cont++;
		
	if((x>=0 && x<f) && (y-1>=0 && y-1<c))
		if(A[x][y-1]==1)
			cont++;
	
	return cont;
}
