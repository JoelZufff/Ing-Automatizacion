// Preprocesadores de Microcontrolador //
#include    <18f4550.h>                                             // Libreria del Microcontrolador
#fuses      XT, NOWDT, NOPROTECT, NOLVP, NOMCLR                     // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 4M, crystal = 4M)                         // Configuracion de frecuencia y delay

// Establecemos direccion de registros
#BYTE       TRISB       = 0xF93             // Configurar Pines
#BYTE       PORTB       = 0xF81             // Input
#BYTE       LATB        = 0xF8A             // Output

int16       *ADRES      = 0xFC3
#BYTE       ADCON0      = 0xFC2
#BIT        DONE        = 0xFC2.1
#BYTE       ADCON1      = 0xFC1
#BYTE       ADCON2      = 0xFC0

void main()
{
   // Funcion read_adc()
   DONE  = 1;
   delay_us(10);
   int16 ADC = *ADRES;
}