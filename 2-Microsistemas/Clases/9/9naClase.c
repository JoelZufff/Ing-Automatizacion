// --------------- Preprocesadores de microcontrolador -------------- //
#include    <18f4550.h>                                              // Libreria del Microcontrolador
#fuses      INTRC, CPUDIV1, PLL1, NOWDT, NOPROTECT, NOLVP, NOMCLR    // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 8M)                                        // Configuracion de frecuencia y delay

#define     LCD_DATA_PORT getenv("SFR:PORTD")
#include    <lcd.c>

// --------------------- Direccion de registros --------------------- //
#byte       TRISD    = 0xF96

// ------------------------ Codigo Principal ----------------------- //
void main()
{
   TRISD = 0;
   
   lcd_init();
   printf(lcd_putc, "SIUUUUU");

   while (TRUE)
   {
      
   }
}