// Preprocesadores de Microcontrolador //
#include    <18f4550.h>                                             // Libreria del Microcontrolador
#fuses      INTRC, CPUDIV1, PLL1, NOWDT, NOPROTECT, NOLVP, NOMCLR   // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 8M)                                       // Configuracion de frecuencia y delay

// Establecemos direccion de registros
#BYTE       TRISB       = 0xF93           // Configurar Pines
#BYTE       PORTB       = 0xF81
#BYTE       LATB        = 0xF8A           // Output

#BYTE       TRISD       = 0xF95
#BYTE       PORTD       = 0xF83
#BYTE       LATD        = 0xF8C

#BYTE       INTCON      = 0xFF2
#BYTE       INTCON2     = 0xFF1
#BYTE       INTCON3     = 0xFF0

#BIT        IPEN        = 0xFD0.7

long i;

#INT_EXT
void blink()
{
    for(i = 0; i <= 16; i++)
    {
        LATD = i;
        delay_ms(200);
    }
}

#INT_EXT1
void blink2()
{
    for(i = 16; i <= 255; i+=16)
    {
        LATD = i;
        delay_ms(200);
    }
}

#INT_EXT2
void blink3()
{
    LATD = 0xFF;
    delay_ms(500);
    LATD = 0;
    delay_ms(500);
    LATD = 0xFF;
    delay_ms(500);
    LATD = 0;
    delay_ms(500);
    LATD = 0xFF;
    delay_ms(500);
    LATD = 0;
}

void main()
{
    // Configuracion de registros de puertos IO
    TRISB       = 0b00000111;
    TRISD       = 0;
    
    // Configuracion de registros de interrupciones
    INTCON      = 0b11110000;
    INTCON2     = 0b01110000;
    INTCON3     = 0b00011000;
    IPEN        = 1;
    
    while(TRUE)
    {
        for(i = 0b00000001; i <= 0b10000000; i <<= 1)
        {
            LATD = i;
            delay_ms(500);
        }
    }
}


