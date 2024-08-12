//*/
// --------------- Preprocesadores de microcontrolador -------------- //
#include    <18F26K22.h>                                                // Libreria del Microcontrolador
#fuses      INTRC, NOWDT, NOPROTECT, NOLVP, NOMCLR                      // Fusibles (Multiplexado de P2B en C0)
#use        delay(internal = 16MHz)                                     // Configuracion de frecuencia y delay
#use        rs232(rcv = pin_c7, xmit = pin_c6, baud = 9600, bits = 8, parity = n, stream = GPS)
#use        rs232(rcv = pin_b7, xmit = pin_b6, baud = 9600, bits = 8, parity = n,  stream = GSM) 

#include <string.h>
#include <stdlib.h>

// --------------------- Direccion de registros --------------------- //
#BYTE       TRISA       = 0xF92
#BIT        LED         = 0xF89.0   // LATA

#BYTE       INTCON      = 0xFF2
#BIT        RC1IE       = 0xF9D.5   // PIE1
#BIT        RC2IE       = 0xFA3.5   // PIE3

// ------------------- Variable Globales y MACROS ------------------- //
//char        number[16];
char        GSM_buffer[50], mode_string[10], time_string[10];
short       GSM_datareceived = FALSE, send_once = TRUE, time_updated = FALSE;
long        time = 5000;
int         mode = 3;   // Modo 0 (No enviar), Modo 1 (Enviar 1 vez), Modo 2 (Enviar cada cierto tiempo), Mode 3 NADA

char        GPS_buffer[80];
int1        GPS_updated = FALSE;
//"$GPRMC,214715.00,A,2035.49683,N,10024.72902,W,0.877,,070324,,,A*61"

// -------------------------- Interrupciones ------------------------ //
#INT_RDA
void GPS_receive()
{
    // Filtros //
    char signal = getch(GPS);

    if(GPS_updated || signal != '$')       return;     // Si no es señal de inicio o ya fue actualizada

    gets(GPS_buffer, GPS);          // Obtiene la linea entera
    
    if(GPS_buffer[2] == 'R' && GPS_buffer[16] == 'A')       // Si es una señal de coordenadas valida
        GPS_updated = TRUE;                           // Activamos bandera de ubicacion actualizada

    //if(GPS_buffer[2] != 'R' || GPS_buffer[16] != 'A')    return;     // Si es una señal de coordenadas valida
    /*
    for(int i = 0; i < 11; i++)     // Guardamos coordenadas
    {
        bufferlon[i] = GPS_buffer[31 + i];
        
        if(i < 10)
            bufferLat[i] = GPS_buffer[18 + i];
    }
    */
}

#INT_RDA2
void GSM_receive()      // Se recibe mensaje del GSM
{
    char data = getc(GSM);

    if(data != '+')       return;     // Si no es señal de inicio o ya fue actualizada

    gets(GSM_buffer, GSM);

    if(GSM_buffer[0] != 'C' || GSM_buffer[1] != 'M' || GSM_buffer[2] != 'T')    return;     // Si no recibimos un mensaje salimos

    // Si recibimos un mensaje valido //
    //getc(GSM);
    gets(GSM_buffer, GSM);

    if(GSM_buffer[1] == '-')    // Recibimos modo
    {
        mode = GSM_buffer[2] - 48;    // Actualizamos el modo
        send_once = TRUE;
    }
    else if(GSM_buffer[1] == '*')   // Recibimos tiempo
    {   
        strncpy(time_string, &GSM_buffer[2], 10);             
        time_updated = TRUE;
    }
}

void send_message(char *Message)
{
    // Mandar mensaje
    //fprintf(GSM, "AT+CMGS=\"+52442\"\r\n");
    fprintf(GSM, "AT+CMGS=\"+524425688661\"\r\n");
    delay_ms(100);

    fprintf(GSM, Message);
    putc('\032', GSM);
}

char * get_ubication()
{   
    char Message[50];

    if(!GPS_updated)        // Si no fue actualizada la ubiacion
    {
        sprintf(Message, "No hay ubicacion disponible\0");
        return Message;
    }
    /*
    sprintf(Message, "SIUUUU\0");
    return Message;
    */
    
    // Si fue actualizada la ubicacion, la calculamos //

    // Separamos cadenas de caracteres
    char bufferLat[11], bufferLon[12], hemisphere[2];
    
    hemisphere[0] = GPS_buffer[29], hemisphere[1] = GPS_buffer[43];  // Guardamos direccion de coordenadas

    strncpy(bufferLon, &GPS_buffer[31], 10);
    strncpy(bufferLat, &GPS_buffer[18], 9);
    bufferLon[11] = bufferLat[10] = '\0';
    
    // Convertimos datos a enteros
    int auxi;       float auxf, latitude, longitude;        char auxc[3]; 

    // Convertimos coordenadas a numeros
    auxc[1] = bufferLat[0];    auxc[2] = bufferLat[1];
    auxi = atoi(&auxc[1]);     auxf = atoe(&bufferlat[2]);
    
    latitude = auxi + (auxf / 60.0);
    
    auxc[0] = bufferLon[0];    auxc[1] = bufferLon[1];    auxc[2] = bufferLon[2];
    auxi = atoi(auxc);         auxf = atoe(&bufferLon[3]);
    
    longitude = auxi + (auxf / 60.0);

    // Devolvemos mensaje de ubicacion
    sprintf(Message, "Coordenadas:\r\n%.5f %c  %.5f %c\0", latitude, hemisphere[0], longitude, hemisphere[1]);
    
    GPS_updated = FALSE;
    
    return Message;
}

void main()
{
    enable_interrupts(GLOBAL);
    enable_interrupts(INT_RDA2);
    
    enable_interrupts(INT_RDA);
    disable_interrupts(INT_RDA);
    
    //while(!GPS_updated);
    /*INTCON  = 0b11000000;
    RC1IE = RC2IE = TRUE;*/

    // Configuracion de puertos I/O
    TRISA   = 0b00000000;
    LED     = FALSE;

    // Configuracion de GSM
    fprintf(GSM, "ATE0\r\n");                     // Desactivamos el ECO
    delay_ms(100);
    
    fprintf(GSM, "AT+CMGF=1\r\n");                // Activamos modo mensaje
    delay_ms(100);
    
    fprintf(GSM, "AT+CNMI=2,2,0,0,0\r\n");        // Recibimos mensajes
    delay_ms(100);

    send_message((char *) "\"0\" para no recibir\r\n\"1\" para recibir una vez\r\n\"2\" para recibir cada x segundos");

    while (TRUE)
    {   
        if(time_updated)     // Se recibio una actualizacion de tiempo
        {
            time = atoi(time_string);   
            time_updated = FALSE;
        }
        
        switch (mode)
        {
            case 0:
                send_message((char *) "Establecido en modo no recibir\0");
                mode = 3, time = 0;
                LED = FALSE;
                break;
            case 1:
                send_message(get_ubication());
                mode = 3, time = 0;
                LED = TRUE;
                break;
            case 2:
                send_message(get_ubication());
                time = 5000;
                LED = FALSE;
                break;
            default:    break;
        }

        delay_ms(time);
        /*for( int i = 0; i < time; i++, delay_ms(1))
            if((i % 500) == 0)
                LED ^= TRUE;*/
    }
}
//*/

// Enviar modo: -(Numero)
// Enviar tiempo: *()


/*/
// --------------- Preprocesadores de microcontrolador -------------- //
#include    <18f4550.h>                                                 // Libreria del Microcontrolador
#fuses      INTRC, CPUDIV1, PLL1, NOWDT, NOPROTECT, NOLVP, NOMCLR       // Fusibles (Configuraciones del microcontrolador)
#use        delay(internal = 8Mhz)                                      // Configuracion de frecuencia y delay
#use        rs232(rcv = pin_c7, xmit = pin_c6, baud = 9600, bits = 8, parity = n)

#include <stdlib.h>

// --------------------- Direccion de registros --------------------- //
#BYTE       TRISB       = 0xF93
#BIT        LED         = 0xF8A.1   // LATB

#BYTE       INTCON      = 0xFF2
#BIT        RCIE        = 0xF9D.5   // PIE1

#BYTE       RCREG       = 0xFAE

// ----------------------- Variable Globales ------------------------ //
int1        update = FALSE;
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

    update = LED = TRUE;        // Activamos bandera de ubicacion actualizada
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
    
    printf("Bienvenido, recibira la ubicacion actual cada 5 seg\r\n\r\n");

    while (TRUE)
    {
        if(!update)
            continue;

        // Convertimos coordenadas a numeros
        auxc[1] = bufferLat[0];    auxc[2] = bufferLat[1];
        auxi = atoi(&auxc[1]);     auxf = atoe(&bufferlat[2]);
        
        latitude = auxi + (auxf / 60.0);
        
        auxc[0] = bufferLon[0];    auxc[1] = bufferLon[1];    auxc[2] = bufferLon[2];
        auxi = atoi(auxc);         auxf = atoe(&bufferLon[3]);
        
        longitude = auxi + (auxf / 60.0);

        // Imprime la ubicacion
        printf("Coordenadas para gmaps:\r\n%.5f %c  %.5f %c\r\n\r\n", latitude, hemisphere[0], longitude, hemisphere[1]);

        update = LED = FALSE;

        delay_ms(5000);
    }
}
//*/

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