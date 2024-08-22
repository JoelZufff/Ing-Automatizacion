// --------------- Preprocesadores de microcontrolador -------------- //
#include    <18f4550.h>                                              // Libreria del Microcontrolador
#fuses      INTRC, NOWDT, NOPROTECT, NOLVP, PUT, NOBROWNOUT          // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 4M, crystal = 4M)                          // Configuracion de frecuencia y delay

// --------------------- Direccion de registros --------------------- //
#BYTE       SSPBUF = 0xFC9

// ----------------------- Variable Globales ------------------------ //

// ------------------------ Codigo Principal ----------------------- //
void main()
{  
   setup_spi(SPI_MASTER | SPI_L_TO_H | SPI_CLK_DIV_4);
   // setup_spi(Maestro-Esclavo | Flanco de Subida | Frecuencia de trabajo (Si es maestro));

   enable_interrupts(GLOBAL);
   enable_interrupts(INT_SSP);

   while (TRUE)
   {
      
   }
}