#include 	<iostream>
#include 	<string.h>
#include	<dos.h>
#include 	<windows.h>
#include 	<stdio.h>
#include 	<math.h>
#include 	<conio.h>
#include 	<stdlib.h>

#define Ts      0.01		// Tiempo de muestreo
#define ppr     400.0		// Pulsos por revolucion del encoder
#define pi_     3.141593


#define VM     10.3			// Voltaje de motor
#define VNM    10.0			// Voltaje nominal del motor

unsigned char flagcom=0,flagfile=0,signo_sal,pwm; // de 8 bits
unsigned short int pos;    //de 16 bits
float y,p_1,p,u,pwmf,t=0,esc=pi_/(2*ppr),iTs=1/Ts,escs=127/VM;

using namespace std;
int main()
{
    HANDLE h; /*handler, sera el descriptor del puerto*/
    DCB dcb; /*estructura de configuracion*/
    DWORD dwEventMask; /*mascara de eventos*/
    FILE *fp;
    
    if((fp=fopen("MONIT.txt","w+"))==NULL)
	{
	  printf("No se puede abrir el archivo.\n");
	  exit(1);
	}    
        
        
    /*abrimos el puerto*/
    h=CreateFile("COM1",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
    
    if(h == INVALID_HANDLE_VALUE) 
	{
         /*ocurrio un error al intentar abrir el puerto*/
    }
             
	/*obtenemos la configuracion actual*/
	if(!GetCommState(h, &dcb)) 
	{
         /*error: no se puede obtener la configuracion*/
    }
         
    /*Configuramos el puerto*/
	dcb.BaudRate = 115200;
    dcb.ByteSize = 8;
    dcb.Parity = NOPARITY;
    dcb.StopBits = ONESTOPBIT;
    dcb.fBinary = TRUE;
    dcb.fParity = TRUE;
         
    /* Establecemos la nueva configuracion */
    if(!SetCommState(h, &dcb)) 
	{
        /* Error al configurar el puerto */
    }
                  
    DWORD n;
    char enviar;
    int recibido;
                             
    /* Para que WaitCommEvent espere el evento RXCHAR */
    SetCommMask(h, EV_RXCHAR);
    while(1) 
	{
    	recibido=0;
        /* Enviamos... */
                  
        /* De la llamada a WaitCommEvent solo se retorna cuando ocurra51.		 * el evento seteado con SetCommMask */
        // WaitCommEvent(h, &dwEventMask, NULL);
        /* Recibimos algun dato!*/
        while(1) 
		{
        	ReadFile(h, &recibido, 1/* leemos un byte */, &n, NULL);
            if(!n)
            	break;
            else
			{
            	if(flagcom!=0)
				flagcom++;
				if((recibido==0xAA)&&(flagcom==0))
   				{
        			pos=0;
        			flagcom=1;
   				}
				if(flagcom==2)
   				{
        			pos=recibido;
        			pos=pos<<8;
   				}
				if(flagcom==3)
   				{
        			p_1=p;
        			pos=pos+recibido;
        			p=(signed short int)pos;
        			p=esc*p;
        			if(abs(p-p_1)<60)
                			y=(p-p_1)*iTs;

        			u=2.0+sin(8*t);
        			//u=sin(6.28*t);
        			//u=1.0;

        			if(u>VNM)
                			u=VNM;
        			if(u<-VNM)
                			u=-VNM;
        			pwmf=u;

					//escalamiento de salida a 7 bits m�s 1 bit de signo
        			pwmf=escs*pwmf;
        			pwm=(unsigned char)fabs(pwmf);

        			if(pwmf<0)
                		pwm=pwm+128;

        			//mandando byte con la se�al de control///////////////////////////////////
        			enviar=pwm;
                  	if(!WriteFile(h, &enviar/*puntero al buffer*/, 1/* 1 byte*/, &n, NULL))
					{
                    	/* Error al enviar */ 
                    }
           			//////////////////////////////////////////////////////////////////////////
           			
					//Imprimiendo en pantalla
    				printf("%3.3f\t%3.3f\t%3.3f\n",t,y,u);
        			
					/*escribir algunos datos en el archivo*/
        			fprintf(fp,"%3.3f\t%3.3f\t%3.3f\n",t,y,u);
        			
					flagcom=0;
					
					if(t > 20)
						return 0;
           			
					   t=t+Ts;
   				}     
   			}//cierre del else       
            //printf("%c",recibido);
	    	//cout << recibido; /* mostramos en pantalla */
    	}//CIERRE WHILE()
    }//CIERRE WHILE()
fclose(fp);             
return 0;
}
