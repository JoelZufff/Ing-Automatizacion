// Preprocesadores de Microcontrolador //
#include    <18f4550.h>                                             // Libreria del Microcontrolador
#fuses      XT, NOWDT, NOPROTECT, NOLVP, NOMCLR                     // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 4M, crystal = 4M)                         // Configuracion de frecuencia y delay

// Establecemos direccion de registros
#BYTE       TRISB       = 0xF93             // Configurar Pines
#BYTE       PORTB       = 0xF81             // Input
#BYTE       LATB        = 0xF8A             // Output

#BYTE       INTCON      = 0xFF2
#BYTE       TMR0L       = 0xFD6
#BIT        TMR0IP      = 0xFF1.2

#BYTE       T0CON       = 0xFD5

#int_TIMER0
void TIMER0_isr(void) 
{
   LATB ^= 1;
   TMR0L = 33;
}

void main()
{  
   // Configuracion de puertos I/O
   TRISB    = 0b00000000;                   // 0 Salida | 1 Entrada
   
   // Configuracion de interrupciones
   INTCON   = 0b11100100;
   
   // Configuracion de timer
   T0CON    = 0b11000000;
   TMR0L    = 33;
   TMR0IP   = 1;
   
   while (true)
   {

   }
}