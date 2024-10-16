// --------------- Preprocesadores de microcontrolador -------------- //
#include    <18f4550.h>                                                 // Libreria del Microcontrolador
#fuses      INTRC, CPUDIV1, PLL1, NOWDT, NOPROTECT, NOLVP               // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 8M)                                           // Configuracion de frecuencia y delay
#use        rs232(rcv = pin_c7, xmit = pin_c6, baud = 9600, bits = 8, parity = n)

#include <stdlib.h>

// --------------------- Direccion de registros --------------------- //
#BYTE       TRISB       = 0xF93
#BIT        BUTTON      = 0xF81.0   // PORTB
#BIT        LED         = 0xF8A.1   // LATB

#BYTE       INTCON      = 0xFF2
#BIT        RCIE        = 0xF9D.5   // PIE1

#BYTE       RCREG       = 0xFAE;

// ----------------------- Variable Globales ------------------------ //
int1        flag = FALSE;
char        hemisphere[2], bufferLat[11], bufferLon[12];
//"$GPRMC,214715.00,A,2035.49683,N,10024.72902,W,0.877,,070324,,,A*61"

// -------------------------- Interrupciones ------------------------ //
#int_rda    // Se desactiva el flag RCIF cuando se lee RCREG
void ReceptGPS()
{
    // Filtros //
    char signal = getch();

    if(signal != '$')       return;     // Si no es señal de inicio sale

    char buffer[80];        // Del tamaño maximo de linea
    gets(buffer);           // Obtiene la linea entera
    
    if(buffer[2] != 'R' || buffer[16] != 'A')    return;     // Si es una señal de coordenadas valida

    // Almacenar coordenadas //
    hemisphere[0] = buffer[29], hemisphere[1] = buffer[43];  // Guardamos direccion de coordenadas

    for(int i = 0; i < 11; i++)     // Guardamos coordenadas
    {
        bufferlon[i] = buffer[31 + i];
        
        if(i < 10)
            bufferLat[i] = buffer[18 + i];
    }
    bufferLon[11] = bufferLat[10] = '\0';

    flag = LED = TRUE;        // Activamos bandera de ubicacion actualizada
}

// ------------------------ Codigo Principal ----------------------- //
void main()
{
    float auxf, latitude, longitude;    int auxi;   char auxc[3];
    
    // Configuracion de puertos I/O
    TRISB   = 0b00000001; 

    // Configuracion de Interrupciones
    INTCON  = 0b11000000;
    RCIE    = 1;
    
    printf("Bienvenido, presione el boton para obtener la ubicacion actual\r\n\r\n");

    while (TRUE)
    {
        if(BUTTON)
        {
            while (BUTTON);
            
            if(!flag)
            {
                printf("No hay nueva lectura disponible\r\n\r\n");
                continue;
            }

            auxc[1] = bufferLat[0];    auxc[2] = bufferLat[1];
            auxi = atoi(&auxc[1]);         auxf = atoe(&bufferlat[2]);
            
            latitude = auxi + (auxf / 60.0);
            
            auxc[0] = bufferLon[0];    auxc[1] = bufferLon[1];    auxc[2] = bufferLon[2];
            auxi = atoi(auxc);         auxf = atoe(&bufferLon[3]);
            
            longitude = auxi + (auxf / 60.0);

            // Imprime la ubicacion
            printf("Coordenadas para gmaps:\r\n%.5f %c  %.5f %c\r\n\r\n", latitude, hemisphere[0], longitude, hemisphere[1]);

            // Convertimos coordenadas a numeros e imprimimos
            flag = LED = FALSE;
        }
    }
}


/*
$GPRMC,230428.00,A,2035.48334,N,10024.69991,W,0.286,,110324,,,A*61
$GPVTG,,T,,M,0.286,N,0.530,K,A*29
$GPGGA,230428.00,2035.48334,N,10024.69991,W,1,05,2.79,1847.3,M,-9.0,M,,*60
$GPGSA,A,3,12,20,05,24,11,,,,,,,,6.72,2.79,6.12*0A
$GPGSV,3,1,10,05,48,186,31,09,,,10,11,52,007,25,12,60,317,27*44
$GPGSV,3,2,10,13,,,09,17,,,23,20,77,108,28,22,13,144,18*7E
$GPGSV,3,3,10,24,19,224,20,46,50,237,37*75
$GPGLL,2035.48334,N,10024.69991,W,230428.00,A,A*71

*/