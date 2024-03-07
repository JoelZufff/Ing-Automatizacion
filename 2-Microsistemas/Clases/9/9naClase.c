// --------------- Preprocesadores de microcontrolador -------------- //
#include    <18f4550.h>                                              // Libreria del Microcontrolador
#fuses      INTRC, CPUDIV1, PLL1, NOWDT, NOPROTECT, NOLVP, NOMCLR    // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 8M)                                        // Configuracion de frecuencia y delay

#include <glcd.c>    // Ampire 128x64

// --------------------- Direccion de registros --------------------- //

// ----------------------- Variable Globales ------------------------ //
const int1 PRUEBA[10][10] = 
{
   1,1,1,1,1,1,1,1,1,1,
   1,1,1,1,1,1,1,1,1,1,
   1,1,1,1,1,1,1,1,1,1,
   1,1,1,1,1,1,1,1,1,1,
   1,1,1,1,0,0,1,1,1,1,
   1,1,1,1,0,0,1,1,1,1,
   1,1,1,1,1,1,1,1,1,1,
   1,1,1,1,1,1,1,1,1,1,
   1,1,1,1,1,1,1,1,1,1,
   1,1,1,1,1,1,1,1,1,1,
};

// ------------------------ Codigo Principal ----------------------- //
void main()
{
   glcd_init(ON);
   glcd_fillScreen(OFF);
   
   while (TRUE)
   {
      for (int j = 0; j < 64; j++)
         for (int i = 0; i < 64; i++, delay_ms(100))
            glcd_pixel( i , j , ON);
      

      /*for(long y = 0; y < 10; y++)
         for(int x = 0; x < 10; x++, delay_ms(100))
            glcd_pixel( x, y, PRUEBA[x][y] );*/
   }
}