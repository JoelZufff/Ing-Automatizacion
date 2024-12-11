// --------------- Preprocesadores de microcontrolador -------------- //
#include    <18f4550.h>                                             // Libreria del Microcontrolador
#fuses      INTRC, PLL1, CPUDIV1, NOWDT, NOPROTECT, NOLVP, NOMCLR    // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 8MHz)                                    // Configuracion de delay
//#use        rs232(rcv = pin_c7, xmit = pin_c6, baud = 9600, bits = 8, parity = n) 
//#use        I2C (MASTER, SCL = PIN_D6, SDA = PIN_D7, FORCE_SW, FAST, stream = SSD1306_STREAM)

// --------------------- Direccion de registros --------------------- //

// -------------------------- Estructuras --------------------------- //

// ----------------------- Variables Globales ----------------------- //

// -------------------------- Interrupciones ------------------------ //

// ---------------------------- Funciones --------------------------- //

// ------------------------ Codigo Principal ------------------------ //
void main()
{  

   while(true)
   {
     
   }
}