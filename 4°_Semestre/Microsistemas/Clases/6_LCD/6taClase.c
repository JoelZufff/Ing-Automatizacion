// Preprocesadores de Microcontrolador //
#include    <18f4550.h>                                             // Libreria del Microcontrolador
#fuses      INTRC, CPUDIV1, PLL1, NOWDT, NOPROTECT, NOLVP, NOMCLR   // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 8M)                         // Configuracion de frecuencia y delay

#define  LCD_DATA_PORT getenv("SFR:PORTD")
#include <lcd.c>

// Establecemos direccion de registros
#BYTE       TRISB       = 0xF93             // Configurar Pines
#BYTE       PORTB       = 0xF81             // Input
#BYTE       LATB        = 0xF8A             // Output

#BYTE       TRISD       = 0xF96

void main()
{
   TRISD = 0;
   
   lcd_init();
   printf(lcd_putc, "Hola");
  
   while (TRUE)
   {
      
   }
}