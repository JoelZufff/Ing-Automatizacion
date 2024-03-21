// --------------- Preprocesadores de microcontrolador -------------- //
#include    <18f4550.h>                                              // Libreria del Microcontrolador
#fuses      INTRC, NOWDT, NOPROTECT, NOLVP, PUT, NOBROWNOUT          // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 4M, crystal = 4M)                          // Configuracion de frecuencia y delay

#define     SLAVE1   PIN_B0
#define     SLAVE2   PIN_B1

// --------------------- Direccion de registros --------------------- //


// ----------------------- Variable Globales ------------------------ //


// ------------------------ Codigo Principal ----------------------- //
void main()
{
   setup_spi(SPI_SLAVE | SPI_L_TO_H);
   // setup_spi(Maestro-Esclavo | Flanco de Subida | Frecuencia de trabajo (Si es maestro));

   // Activar, mandar dato y desactivar esclavo
   
   output_low(SLAVE1);
   spi_write('1');
   output_high(SLAVE1);

   delay_ms(100);
   
   output_low(SLAVE1);
   spi_read(0);            // Leemos primer valor del bus
   output_high(SLAVE1);

   while (TRUE)
   {
      
   }
}