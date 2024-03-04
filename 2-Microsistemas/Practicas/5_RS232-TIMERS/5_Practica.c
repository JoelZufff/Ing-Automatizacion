// --------------- Preprocesadores de microcontrolador -------------- //
#include    <18f4550.h>                                                 // Libreria del Microcontrolador
#fuses      INTRC, CPUDIV1, PLL1, NOWDT, NOPROTECT, NOLVP, NOMCLR       // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 8M)                                           // Configuracion de frecuencia y delay

// --------------------- Direccion de registros --------------------- //
#BYTE       TRISD       = 0xF95
#BYTE       TRISB       = 0xF93
#BYTE       LEDS        = 0xF8C     // LATD
#BIT        SENDWORD    = 0xF81.2   // PORTB
#BIT        TXPIN       = 0xF8A.1   // LATB

#BYTE       INTCON      = 0xFF2
#BIT        INT0IE      = 0xFF2.4   // INT0 External Interrupt Enable bit
#BIT        INTEDG0     = 0xFF1.6   // Flanco de int_ext
#BIT        TMR2IE      = 0xF9D.1   // Enable de interrupcion Timer 2

#BYTE       T2CON       = 0xFCA
#BIT        TMR2ON      = 0xFCA.2   // Encendido de TIMER 2
#BYTE       PR2         = 0xFCB

// ----------------------- Variable Globales ------------------------ //
int     bit_index = 0b00000001, byte_value = 0b00000000;
int1    high_bool = FALSE, send_bool = FALSE, bit_value = 0;
//int1    bits[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

// -------------------------- Interrupciones ------------------------ //
#INT_EXT
void bit_detect()
{
    // SI DETECTAMOS VALOR DE UN BIT
    if(TMR2ON)
    {   
        if(INTEDG0)     // Si detectamos flanco de subida
            high_bool = TRUE, INTEDG0 = 0;
        else            // Si detectamos flanco de bajada
            high_bool = FALSE, INTEDG0 = 1;
        return;
    }
    
    // SI DETECTAMOS BIT DE START
    // Reiniciamos variables
    bit_index = 0b00000001;
    high_bool = byte_value = 0;

    // Activamos timer 2 para recorrimiento de bits | Lo configuramos en rising edge para detectar siguiente bit
    delay_us(50);               // Delay para comenzar en mitad de ciclo
    TMR2ON = 1, INTEDG0 = 1;
}

#INT_TIMER2
void bit_clock()        // Recorrimiento de bit actual 
{ 
    if(send_bool)                   // Si estamos mandando informacion
    {
        TXPIN = bit_value;
        send_bool = FALSE;
        return;
    }
    
    if(bit_index == 0)
    {
        TMR2ON = INTEDG0 = 0;       // Desactivamos timer 2 | Activamos interrupcion externa para flanco de bajada
        LEDS = byte_value;
        bit_index = 1;
        return;
    }

    if(high_bool)       // Si se detecto un flanco de subida
        byte_value |= bit_index;

    bit_index <<= 1;    // Recorremos posicion del bit recibido
}

// ---------------------------- Funciones -------------------------- //
void putchafa(char C)
{
    if(TMR2ON)          // Si esta recibiendo datos no mandamos nada (Se podria resolver usando otro timer)
        return;

    // Separamos valor de cada bit
    int bits[8];
    for( int i = 0; i < 8; i++ )
        bits[i] = (C>>i) & 0b00000001;

    // Bit de start y encendemos timer con frecuencia 9600 baudios
    bit_value = 0;
    send_bool = TMR2ON = 1;
    while(send_bool);

    // 8 bits de caracter
    for( int i = 0 ; i < 8; i++ )
    {
        // Enviamos bit en el periodo correspondiente
        bit_value = bits[i];
        send_bool = TRUE;
        while(send_bool);
    }

    // Bit de stop
    bit_value = send_bool = 1;
    while(send_bool);
    TMR2ON  = 0;            // Desactivamos timer 2
}

// ------------------------ Codigo Principal ----------------------- //
void main()
{
    // CONFIGURACION DE PUERTOS IO
    TRISD   = 0x00;
    TRISB   = 0b00000101;
    TXPIN   = 1;

    // CONFIGURACION DE INTERRUPCIONES
    INTCON  = 0b11010000;
    TMR2IE  = 1;

    // CONFIGURACION DE TIMERS
    T2CON   = 0b00000011;
    PR2     = 12;       // Para timer 2 a 9600 Hz

    while (TRUE)
    {
        if(SENDWORD)
        {
            while(SENDWORD);
            putchafa(byte_value);
            //printf(putchafa, "Caracter recibido --> %c\r\n", byte_value);
        }
    }
}

/*
    * Ocupo mandar 10 bits. 1 bit de start, 8 bits de datos y 1 bit de stop
    * La velocidad sera de 9600 baudios o bits/seg = 9.6KHz | Con un periodo de 104.17 us
    * El transmisor esta en high siempre, y el bit de start es en low, luego siguen los 8 bits de datos, finalizamos con el bit de stop para dejar en high
*/
