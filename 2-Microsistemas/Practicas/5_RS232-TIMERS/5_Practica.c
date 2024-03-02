// --------------- Preprocesadores de microcontrolador -------------- //
#include    <18f4550.h>                                                 // Libreria del Microcontrolador
#fuses      INTRC, CPUDIV1, PLL1, NOWDT, NOPROTECT, NOLVP               // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 8M)                                           // Configuracion de frecuencia y delay
//#use        rs232(rcv = pin_c7, xmit = pin_c6, baud = 9600, bits = 8, parity = n)

// --------------------- Direccion de registros --------------------- //
#BYTE       TRISD       = 0xF95
#BYTE       TRISB       = 0xF93
#BYTE       LEDS        = 0xF8C     // LATD

#BYTE       INTCON      = 0xFF2
#BIT        INT0IE      = 0xFF2.4   // INT0 External Interrupt Enable bit
#BIT        INTEDG0     = 0xFF1.6   // Flanco de int_ext
#BIT        TMR2IE      = 0xF9D.1   // Enable de interrupcion Timer 2

#BYTE       T2CON       = 0xFCA
#BIT        TMR2ON      = 0xFCA.2   // Encendido de TIMER 2
#BYTE       PR2         = 0xFCB

// ----------------------- Variable Globales ------------------------ //
int     bit_index = 0b00000001, byte_value = 0b00000000;
short   high_bool = FALSE;

// -------------------------- Interrupciones ------------------------ //
#INT_EXT
void SerialCommunication()
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
void bit_detect()        // Recorrimiento de bit actual 
{ 
    if(bit_index == 0)
    {
        TMR2ON = INTEDG0 = 0;       // Desactivamos timer 2 | Activamos interrupcion externa para flanco de bajada
        //printf("'%c' %u\r\n",byte_value, byte_value);
        return;
    }

    if(high_bool)       // Si se detecto un flanco de subida
        byte_value |= bit_index;

    bit_index <<= 1;    // Recorremos posicion del bit recibido
}

// ------------------------ Codigo Principal ----------------------- //
void main()
{
    // CONFIGURACION DE PUERTOS IO
    TRISD   = 0x00;
    TRISB   = 0b00000001;

    // CONFIGURACION DE INTERRUPCIONES
    INTCON  = 0b11010000;
    TMR2IE  = 1;

    // CONFIGURACION DE TIMERS
    T2CON   = 0b00000011;
    PR2     = 12;       // Para timer 2 a 9600 Hz

    while (TRUE)
        LEDS = byte_value;
}

/*
    * Ocupo mandar 10 bits. 1 bit de start, 8 bits de datos y 1 bit de stop
    * La velocidad sera de 9600 baudios o bits/seg = 9.6KHz | Con un periodo de 104.17 us
    * El transmisor esta en high siempre, y el bit de start es en low, luego siguen los 8 bits de datos, finalizamos con el bit de stop para dejar en high
*/
