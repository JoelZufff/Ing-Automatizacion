// MICROCONTROLADOR PARA RECEPCION E INTERPRETACION DE INSTRUCCIONES

// --------------- Preprocesadores de microcontrolador -------------- //
#include    <18f4550.h>                                              // Libreria del Microcontrolador
#fuses      INTRC, CPUDIV1, PLL1, NOWDT, NOPROTECT, NOLVP, NOMCLR    // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 8M)                                        // Configuracion de frecuencia y delay
#use        rs232(rcv = pin_c7, xmit = pin_c6, baud = 9600, bits = 8, parity = n)


// --------------------- Direccion de registros --------------------- //
#BYTE       INTCON         = 0xFF2
#BIT        RCIE           = 0xF9D.5      // PIE1

#BYTE       TRISA          = 0xF92

#BYTE       TRISB          = 0xF93
#BIT        START_PAUSE    = 0xF81.0   // PORTB
#BIT        PLAYER1        = 0xF81.1   // PORTB
#BIT        PLAYER2        = 0xF81.2   // PORTB

// ----------------------- Variable Globales ------------------------ //


// -------------------------- Estructuras -------------------------- //


// --------------------------- Funciones --------------------------- //


// ------------------------- Interrupciones ------------------------ //
#int_rda
void receive() 
{
   // Recibir instrucciones de estatus de display
   char buffer = getchar();

   switch (buffer)
   {
      case 'C':

         break;
      case '1':

         break;
      case '2':

         break;
      default: break;
   }
}

// ------------------------ Codigo Principal ----------------------- //
void main()
{
   // Configuracion de registros de pines I/O
   TRISB    = 0b00000111;
   TRISA    = 0b00000000;

   // Configuracion de registros de interrupciones
   INTCON   = 0b11000000;
   RCIE     = 1;

   // Ciclo Infinito
   while (TRUE)
   {
      // Posible calculo de posiciones de pajaros y columnas
      // Los botones los manejamos en interrupciones
      
      if(START_PAUSE)
      {
         while (START_PAUSE);
         putc('C');
      }
      
      // Convertir estos en interrupciones de la misma prioridad, para que se ejecuten uno detras de otro si se presionan al mismo tiempo
      if(PLAYER1)
      {
         while (PLAYER1);
         putc('1');
      }

      if(PLAYER2)
      {
         while (PLAYER2);
         putc('2');
      }
   }
}