// --------------- Preprocesadores de microcontrolador -------------- //
#include    <18f4550.h>                                              // Libreria del Microcontrolador
#fuses      INTRC, CPUDIV1, PLL1, NOWDT, NOPROTECT, NOLVP, NOMCLR    // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 8M)                                        // Configuracion de frecuencia y delay

#include <HDM64GS12.c>

// --------------------- Direccion de registros --------------------- //

// ----------------------- Variable Globales ------------------------ //

// ------------------------ Codigo Principal ----------------------- //
void main()
{
   glcd_init(ON);
   glcd_fillScreen(OFF);

   while (TRUE)
   {
      
   }
}