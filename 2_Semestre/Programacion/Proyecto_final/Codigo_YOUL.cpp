// ACTUALIZAR HORAS, RETARDOS Y FALTAS.
// SALARIO MENSUAL
// Restringir 1 mes, para reiniciar todo

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define N 119
#define Nemp 20
#define ESC 27

void Titulo(const char *,int);
int RCOMP();
void Registro();
void SimulacionSem(int);
	int Nuevo_Turno(int, char []);
		int ConteoHoras(char [],int);
		int ConteoRetardos(char [],int);
		int ConteoFaltas(char [],int);
void Estadisticas();

int main()
{	
	int B,Sem,i;
	fflush(stdin);
	srand(time(NULL));
	do
	{
		system("cls");
		Titulo("E N T R A D A  Y  S A L I D A  D E  E M P L E A D O S",sizeof("E N T R A D A  Y  S A L I D A  D E  E M P L E A D O S"));
		
		printf("\n\t\t1. Registro de Empleados\n\n\t\t2. Comenzar Simulacion Mensual\n\n\t\t3. Estadisticas por Empleado");
		printf("\n\n\nPresiones la tecla de la opcion que desee, de lo contrario presione ESC para salir");
		
		do
		{
			B = getch();
			if(B == ESC)
				return 0;
		}
		while (B<49 || B>51);
		
		B-=48;
		
		switch(B)
		{
			case 1:
				Registro();
				B=1;
			break;
			case 2:
				if(RCOMP())
				{
					for(Sem=1;Sem<=4;Sem++)
					{
						SimulacionSem(Sem);
					}
					system("cls");
					for(i=0;i<17;i++)
						putch('\n');
					Titulo("FIN DEL MES, REVISAR ESTADISTICAS EN MENU PRINCIPAL",sizeof("FIN DEL MES, REVISAR ESTADISTICAS EN MENU PRINCIPAL"));
					system("pause>nul");
				}
				else
				{
					system("cls");
					for(i=0;i<17;i++)
						putch('\n');
					Titulo("COMPLETE EL REGISTRO DE EMPLEADOS Y VUELVA",sizeof("COMPLETE EL REGISTRO DE EMPLEADOS Y VUELVA"));
					system("pause>nul");
				}
				B=1;
			break;
			case 3:
				if(RCOMP())
					Estadisticas();
				else
				{
					system("cls");
					for(i=0;i<17;i++)
						putch('\n');
					Titulo("COMPLETE EL REGISTRO DE EMPLEADOS Y VUELVA",sizeof("COMPLETE EL REGISTRO DE EMPLEADOS Y VUELVA"));
					system("pause>nul");
				}
				B=1;
			break;
		}
	}
	while(B);
}

void Titulo(const char *A,int tam)
{
	int i;
	--tam;
	for(i=0;i<N;i++)
		putchar(205);
	putchar('\n');
	for(i=0;i<(N-tam)/2;i++)
		putchar(' ');
	printf("%s\n",A);
	for(i=0;i<N;i++)
		putchar(205);
	putchar('\n');
}

int RCOMP()
{
	FILE *emp;
	int i;
	char NF[6];
	
	for(i=1;i<=Nemp;i++)
	{
		sprintf(NF,"%d.txt",i);
		if((emp = fopen(NF,"r")) == NULL)
		{
			fclose(emp);
			return 0;
		}
	}
	fclose(emp);
	return 1;
}

void Registro()
{
	FILE *emp;
	int i,Nex[Nemp], contnex=0;
	char NF[6],buffer[2];
	
	system("cls");
	Titulo("R E G I S T R O  D E  E M P L E A D O S",sizeof("R E G I S T R O  D E  E M P L E A D O S"));
	
	for(i=1;i<=Nemp;i++)
	{
		sprintf(NF,"%d.txt",i);
		
		if((emp = fopen(NF,"r")) == NULL)
			Nex[contnex++]=i;
		else
		{
			int Bbuffer=0;
			
			printf("\nEmpleado %d:\t",i);
			
			rewind(emp);
			
			while (fgets(buffer, 2, emp) != NULL && *buffer != 9) 
			{
				if (Bbuffer == 1) 
					putchar(*buffer);
				if (*buffer == 58) 
					Bbuffer = 1;
			}

			putchar('\n');
		}
		fclose(emp);
	}
	
	if(contnex == 0)
		printf("\n\n\n\t\t\t\t\tTODOS LOS EMPLEADOS HAN SIDO REGISTRADOS\n\n\n");
	else
	{
		if(contnex!=Nemp)
		{
			putchar('\n');
			for(i=0;i<N;i++)
				putchar(205);
			putchar('\n');
		}
		
		for(i=0;i<contnex;i++)
		{
			char nombre[50];
			fflush(stdin);
			
			printf("\nIngrese el nombre del empleado %d:\t",Nex[i]);
			gets(nombre);
			
			sprintf(NF,"%d.txt",Nex[i]);
			if((emp=fopen(NF,"w")) == NULL)
			{
				perror("\nError en la creacion del archivo");
				exit(1);
			}
			else
			{
				printf("\nArchivo creado exitosamente\n\n");
				fprintf(emp,"Nombre: %s\t\tHoras Trabajadas: __0\t\t\tRetardos: _0\t\t\tFaltas: _0",nombre);
			}
			
			fclose(emp);
		}
	}
		
	system("pause");
}

void SimulacionSem(int Sem)
{
	FILE *emp;
	int i,j,k,tam;
	char Dia[3], NF[6];
	
	system("cls");
	for(i=0;i<20;i++)
		putchar('\n');
	printf("\t\t\t\t\t\tS");
	Sleep(200);
	printf("  E");
	Sleep(200);
	printf("  M");
	Sleep(200);
	printf("  A");
	Sleep(200);
	printf("  N");
	Sleep(200);
	printf("  A");
	Sleep(200);
	printf("\t%d",Sem);
	system("pause>nul");
	
	for(i=1;i<=Nemp;i++) // Separador de Semanas
	{
		sprintf(NF,"%d.txt",i);
		if((emp=fopen(NF,"a")) == NULL)
		{
			perror("\nError en la apertura de archivos");
			exit(1);
		}
		else
		{
			fprintf(emp,"\n\nS E M A N A  #%d",Sem);
			fprintf(emp,"\n\n\t\tDia\t\tHora de Entrada\t\t\tHora de Salida\t\tRetardo\n");
			
			fclose(emp);
		}
	}
	
	for(i=1;i<=6;i++) // Dias
	{
		system("cls");
	
	    if (i == 1)
	    {
	        strcpy(Dia, "LUN");
	        Titulo("L U N E S",sizeof("L U N E S"));
		}
	    else if (i == 2)
	    {
	        strcpy(Dia, "MAR");
	        Titulo("M A R T E S",sizeof("M A R T E S"));
		}
	    else if (i == 3)
	    {
	        strcpy(Dia, "MIE");
	        Titulo("M I E R C O L E S",sizeof("M I E R C O L E S"));
		}
	    else if (i == 4)
	    {
	        strcpy(Dia, "JUE");
	        Titulo("J U E V E S",sizeof("J U E V E S"));
		}
	    else if (i == 5)
	    {
	        strcpy(Dia, "VIE");
	        Titulo("V I E R N E S",sizeof("V I E R N E S"));
		}
	    else if (i == 6)
	    {
	        strcpy(Dia, "SAB");
	        Titulo("S A B A D O",sizeof("S A B A D O"));
		}
	        
		tam = sizeof("M A T U T I N O")-1;
		printf("\n\n");
		for(j=0;j<((N-tam)/2);j++)
			putch(' ');
		printf("M A T U T I N O\n\n\t\tNum. Empleado\t\tHora de Entrada\t\t\tHora de Salida\t\tRetardo\n");
	    
		for(j=1;j<=Nemp;j++) // Generar Turnos de Empleados
		{
			Nuevo_Turno(j,Dia);
			
			if(j == Nemp/2) // Divisor de Vespertino y Matutino
			{
				tam = sizeof("V E S P E R T I N O")-1;
				printf("\n\n");
				for(k=0;k<((N-tam)/2);k++)
					putch(' ');
				printf("V E S P E R T I N O");
				printf("\n\n\t\tNum. Empleado\t\tHora de Entrada\t\t\tHora de Salida\t\tRetardo\n");
			}
			Sleep(150);
		}
		system("pause>nul");
	}
}

int Nuevo_Turno(int NE, char Dia[])
{
	FILE *emp;
	char NF[6];
	int H,HE, ME, SE, HS, MS=0, SS=0, retardo=0, falta=0,HTrab = 0;
	
	if((rand() % 61) == (rand() % 61))
		falta++;
	
	if(!falta)
	{
		if(NE<=(Nemp/2))
		{
			H = 6;
			HS = 15;
		}
		else if(NE>(Nemp/2))
		{
			H = 14;
			HS = 23;
		}
		
		HE = H + rand()%2; // Hora de entrada entre 6 y 7 o 14 y 15
		if(HE == H)
			ME = rand()%10+50; // Minuto de entrada entre 50-59
		else if(HE == H+1)
		{
			ME = rand()%13; // Minutro de entrada entre 0-12
			if(ME > 10)
				retardo++;
		}
		SE = rand() % 60; // Segundos de 0-59
		
		HTrab = 8;
	}
	else
		H = HE = ME = SE = HS = HTrab = 0;
	
	fflush(stdin);
	sprintf(NF,"%d.txt",NE);
	if((emp = fopen(NF,"a+")) == NULL)
	{
		perror("\nError en la apertura de archivos");
	}
	else
	{
		printf("\t\t%d\t\t\t",NE);
		fprintf(emp,"\n\t\t%s\t\t",Dia);
		
		if(HE<10)
		{
			printf("0%i:",HE);
			fprintf(emp,"0%i:",HE);
		}
		else
		{
			printf("%i:",HE);
			fprintf(emp,"%i:",HE);
		}
			
		if(ME<10)
		{
			printf("0%i:",ME);
			fprintf(emp,"0%i:",ME);
		}
		else
		{
			printf("%i:",ME);
			fprintf(emp,"%i:",ME);
		}
		
		if(SE<10)
		{
			printf("0%i\t\t",SE);
			fprintf(emp,"0%i\t\t",SE);
		}
		else
		{
			printf("%i\t\t",SE);
			fprintf(emp,"%i\t\t",SE);
		}
				
		if(HS < 10)
		{
			printf("\t0%i:",HS);
			fprintf(emp,"\t0%i:",HS);
		}
		else
		{
			printf("\t%i:",HS);
			fprintf(emp,"\t%i:",HS);
		}
		printf("0%i:",MS);
		fprintf(emp,"0%i:",MS);
		printf("0%i\t\t",SS);
		fprintf(emp,"0%i\t\t",SS);
	
		if(retardo == 1)
		{
			printf("%c\n",254);
			fprintf(emp,"%c",254);
		}
		else
			putch('\n');
			
		fclose(emp);
		ConteoHoras(NF,HTrab);
		ConteoRetardos(NF,retardo);
		ConteoFaltas(NF,falta);
	}
	
	fclose(emp);
	return 0;
}

int ConteoHoras(char NF[],int HTrab)
{
	FILE *emp;
	char Buffer[2], ES[5];
	int i=0;
	long pos;
	
	if((emp = fopen(NF,"r+")) == NULL)
	{
		perror("\nError en la apertura de archivos");
	}
	else
	{
		rewind(emp);
		while(fgets(Buffer, sizeof(Buffer), emp) != NULL)
		{
			if(i == 2)
			{
				pos = ftell(emp);
						
				char BufferAux[4];
				fgets(BufferAux,sizeof(BufferAux), emp);
						
				if(BufferAux[0] != 95)
					HTrab += (BufferAux[0]-48)*100;
				if(BufferAux[1] != 95)
					HTrab += (BufferAux[1]-48)*10;
				if(BufferAux[2] != 95)
					HTrab += (BufferAux[2]-48);
						
				if(HTrab >= 100)
					sprintf(ES,"%d",HTrab);
				if(HTrab < 100)
					sprintf(ES,"_%d",HTrab);
				if (HTrab < 10)
					sprintf(ES,"__%d",HTrab);
						
				if(fseek(emp,pos,SEEK_SET) != 0)
				{
				    printf("\nError al desplazar el puntero");
				    fclose(emp);
				    return 0;
				}
				    	
				fwrite(ES, sizeof(char), sizeof(ES) - 1, emp);
				fclose(emp);
				return 1;
			}
					
			if(Buffer[0] == 58) // Caracter por caracter hasta encontrar 2 puntos
				i++;
		}
	}
	
}

int ConteoRetardos(char NF[],int HTrab)
{
	FILE *emp;
	char Buffer[2], ES[5];
	int i=0;
	long pos;
	
	if((emp = fopen(NF,"r+")) == NULL)
	{
		perror("\nError en la apertura de archivos");
	}
	else
	{
		rewind(emp);
		while(fgets(Buffer, sizeof(Buffer), emp) != NULL)
		{
			if(i == 3)
			{
				pos = ftell(emp);
						
				char BufferAux[3];
				fgets(BufferAux,sizeof(BufferAux), emp);
						
				if(BufferAux[0] != 95)
					HTrab += (BufferAux[0]-48)*10;
				if(BufferAux[1] != 95)
					HTrab += (BufferAux[1]-48);
						
				if(HTrab < 100)
					sprintf(ES,"%d",HTrab);
				if (HTrab < 10)
					sprintf(ES,"_%d",HTrab);
						
				if(fseek(emp,pos,SEEK_SET) != 0)
				{
				    printf("\nError al desplazar el puntero");
				    fclose(emp);
				    return 0;
				}
				    	
				fwrite(ES, sizeof(char), sizeof(ES) - 1, emp);
				fclose(emp);
				return 1;
			}
					
			if(Buffer[0] == 58) // Caracter por caracter hasta encontrar 2 puntos
				i++;
		}
	}
	
}

int ConteoFaltas(char NF[],int HTrab)
{
	FILE *emp;
	char Buffer[2], ES[5];
	int i=0;
	long pos;
	
	if((emp = fopen(NF,"r+")) == NULL)
	{
		perror("\nError en la apertura de archivos");
	}
	else
	{
		rewind(emp);
		while(fgets(Buffer, sizeof(Buffer), emp) != NULL)
		{
			if(i == 4)
			{
				pos = ftell(emp);
						
				char BufferAux[3];
				fgets(BufferAux,sizeof(BufferAux), emp);
						
				if(BufferAux[0] != 95)
					HTrab += (BufferAux[0]-48)*10;
				if(BufferAux[1] != 95)
					HTrab += (BufferAux[1]-48);
						
				if(HTrab < 100)
					sprintf(ES,"%d",HTrab);
				if (HTrab < 10)
					sprintf(ES,"_%d",HTrab);
						
				if(fseek(emp,pos,SEEK_SET) != 0)
				{
				    printf("\nError al desplazar el puntero");
				    fclose(emp);
				    return 0;
				}
				    	
				fwrite(ES, sizeof(char), sizeof(ES) - 1, emp);
				fclose(emp);
				return 1;
			}
					
			if(Buffer[0] == 58) // Caracter por caracter hasta encontrar 2 puntos
				i++;
		}
	}
	
}

void Estadisticas()
{
	system("cls");
	Titulo("E S T A D I S T I C A S", sizeof("E S T A D I S T I C A S"));
	
	FILE *emp;
	char caracter,NF[6];
	int i=0, num;
		
	printf("\nNumero del empleado del 1 al %i:\t\t",Nemp);
	scanf("%d",&num);
	
	sprintf(NF,"%d.txt",num);
	
	emp = fopen(NF,"r");
	if(emp==NULL)
	{
		printf("\nEl archivo %s no existe",NF);
	}
	else
	{
		printf("\n\n");
		while(!ferror(emp) && !feof(emp))
		{
			caracter = fgetc(emp);
			putchar(caracter);
		}
		
		if(ferror(emp))
			perror("Error durante la lectura");
	}

	fclose(emp);
	printf("\n\n");
	system("pause");
}
