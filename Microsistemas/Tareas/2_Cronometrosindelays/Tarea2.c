// Preprocesadores de Microcontrolador //
#include    <18f4550.h>                                             // Libreria del Microcontrolador
#fuses      INTRC, CPUDIV1, PLL1, NOWDT, NOPROTECT, NOLVP           // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 8M)                                       // Configuracion de frecuencia y delay

// Establecemos direccion de registros
#BYTE TRISB       = 0xF93             // Configurar Pines
#BYTE PORTB       = 0xF81             // Input
#BYTE LATB        = 0xF8A             // Output

#BYTE TRISD       = 0xF95
#BYTE PORTD       = 0xF83
#BYTE LATD        = 0xF8C

int catodo[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D,0x7D,0x07,0x7F,0x67 };         // Catodo
//int anodo[10] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90 };         // Anodo

/* 
    1 ciclo de reloj = 1 / 8 MHz = 125 ns
    1 ciclo maquina  = 4 * 125 ns = 500 ns

    Se ocupan 30 ciclos maquina por cada ciclo = 15 us

    1 s / 15 us = 1,000,000 de veces
*/


void main()
{
    // Configuracion de registros de puertos IO
    TRISB       = 0b00000000;
    TRISD       = 0;

    while (TRUE)
    {
        for( int num = 0; num < 10; num++ )
            for( int32 reps = 0; reps < 50000; reps++ )
                LATD = catodo[num];
    }
    
}
