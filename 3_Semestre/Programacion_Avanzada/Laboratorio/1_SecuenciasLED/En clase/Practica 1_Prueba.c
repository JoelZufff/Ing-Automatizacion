#include <18f4550.h>   // Libreria del Microcontrolador
#fuses INTRC, NOWDT, NOPROTECT, NOLVP, CPUDIV1, PLL1, NOMCLR // Fusibles (Configuraciones del microcontrolador)
#use delay(clock = 8M)  // 4M es 4 millones. Establecemos la velocidad va a operar el micro

void main()
{
   int16 i=0; // Los enteros tienen 1 byte le ponemos int16 para evitar eso
   int b;
   while(true)
   { 
      
   }
}
