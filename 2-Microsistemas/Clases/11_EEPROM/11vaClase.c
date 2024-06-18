// --------------- Preprocesadores de microcontrolador -------------- //
#include    <18f4550.h>                                              // Libreria del Microcontrolador
#fuses      NOWDT, NOPROTECT, NOLVP, NOMCLR                          // Fusibles (Configuraciones del microcontrolador)
#use        delay(internal = 8Mhz)                                   // Configuracion de frecuencia y delay

// --------------------- Direccion de registros --------------------- //
#BYTE       EECON1   = 0xFA6
#BYTE       EECON2   = 0xFA7
#BYTE       EEDATA   = 0xFA8
#BYTE       EEADR    = 0xFA9

// ----------------------- Variable Globales ------------------------ //


// ------------------------ Codigo Principal ------------------------ //
void main()
{
   
   while (TRUE)
   {
      
   }
}
/*
* Tarda aproximadamente 4 ms en leer y escribir en la eeprom
* Existen 4 modos de direccionamiento
   Inherente: 
   Literal:
   Directo:
   Indirecto:
*/
