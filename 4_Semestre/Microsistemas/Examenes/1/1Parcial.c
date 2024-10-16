// --------------- Preprocesadores de microcontrolador -------------- //
#include    <18f4550.h>                                              // Libreria del Microcontrolador
#fuses      INTRC, CPUDIV1, PLL1, NOWDT, NOPROTECT, NOLVP, NOMCLR    // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 8M)                                        // Configuracion de frecuencia y delay

#BYTE    TRISB    = 0xF93
#BYTE    TRISD    = 0xF95

#BYTE    LATB     = 0xF8A
#BYTE    PORTD    = 0xF83
#BYTE    LATD     = 0xF8C

int     display[10]  = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67 };

void main()
{
   TRISB    = 0b00000000;
   TRISD    = 0b11110000;
   
   int y = 4;
   int x = 4;
   
   LATB = display[0];
   
   while(TRUE)
   {   
      for( int i = 0; i < 3; i++, delay_ms(5) )
      {
         LATD |= 0b00000001 << i;  // Activamos el pin
         LATD &= 0b00000001 << i;  // Desactivamos otros pines sin alterar valor de los 4 BMS
         
         int aux = PORTD & 0b11110000;   // Despreciamos bits de envio
         
         for(int j = 0; j < 3; j++)
         {
            if(aux == (0b00010000 << j))
            {
               x = j+1;
               y = i+1;
               break;
            }
         }
      }
      
      switch(x)
      {
         case 1:
         {
            switch(y)
            {
               case 1:
                  LATB = display[7];
               break;
               case 2:
                  LATB = display[4];
               break;
               case 3:
                  LATB = display[1];
               break;
            }
         }
         break;
         case 2:
         {
            switch(y)
            {
               case 1:
                  LATB = display[8];
               break;
               case 2:
                  LATB = display[5];
               break;
               case 3:
                  LATB = display[2];
               break;
            }
         }
         break;
         case 3:
         {
            switch(y)
            {
               case 1:
                  LATB = display[9];
               break;
               case 2:
                  LATB = display[6];
               break;
               case 3:
                  LATB = display[3];
               break;
            }
         }
         break;
      }
      
   }
}
