// --------------- Preprocesadores de microcontrolador -------------- //
#include    <18f4550.h>                                              // Libreria del Microcontrolador
#fuses      INTRC, CPUDIV1, PLL1, NOWDT, NOPROTECT, NOLVP, NOMCLR    // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 8M)                                        // Configuracion de frecuencia y delay
#use        rs232(rcv = pin_c7, xmit = pin_c6, baud = 9600, bits = 8, parity = n)

#include <HDM64GS12.c>
#include <graphics.c>
#include <pixelshapes.c>

// --------------------- Direccion de registros --------------------- //
//#BYTE       TRISA       = 0xF92

#BYTE       INTCON      = 0xFF2
#BIT        RCIE        = 0xF9D.5      // PIE1
#BIT        RCIP        = 0xF9F.5      // IPR1
#BIT        IPEN        = 0xFD0.7      // RCON

#BYTE       T0CON       = 0xFD5
const int16 *TMR0       = 0xFD6;

// ----------------------- Variable Globales ------------------------ //
int1 pause_button = FALSE, player1_button = FALSE, player2_button = FALSE, printbool = FALSE;
int z = 0;

// -------------------------- Estructuras -------------------------- //
struct bird
{
   int coordenates[2][4];     // 4 Coordenadas con la posicion actual 
};

// --------------------------- Funciones --------------------------- //


// ------------------------- Interrupciones ------------------------ //
#int_rda
void receive() 
{
   char buffer = getchar();

   switch (buffer)
   {
      case 'C':
      // Se presiono el boton de start/pausa
      {
         pause_button ^= TRUE;
         break;
      }
      case '1':
      // Se presiono el boton del jugador 1
      {
         if(!pause_button)
            player1_button = TRUE;
         break;
      }
      case '2':
      // Se presiono el boton del jugador 2
      {
         if(!pause_button)
            player2_button = TRUE;
         break;
      }
      default: break;
   } 
}

#int_timer0
void display_refresh()     // Refresca el contenido de la pantalla a 30 Hz
{
   *TMR0    = 53035;      // 30 Hz
   glcd_fillScreen(OFF);

   // Impresion de columna de separacion
   glcd_line(62,0,62,63, ON);
   glcd_line(63,0,63,63, ON);
   glcd_line(64,0,64,63, ON);
   glcd_line(65,0,65,63, ON);

   // Impresion de pajaro en posicion
   for(int x = 0; x < 17; x++)
      for(int y = 0; y < 12; y++)
         glcd_pixel( x + z, y, bird_pixels[y][x] );

   // Impresion de barreras
}

// ------------------------ Codigo Principal ----------------------- //
void main()
{
   // Configuracion inicial de GLCD;
   glcd_init(ON);

   // Configuracion de registros de pines I/O
   //TRISA    = 0b00000000;

   // Configuracion de registros de interrupciones
   INTCON   = 0b11100000;
   IPEN = RCIE = RCIP = 1;
   // Activamos interrupcion de recepcion EUSART y la hacemos de alta priodidad para evitar perdida de datos de instrucciones
   
   // Configuracion de registros de TIMER 0
   *TMR0    = 53035;
   T0CON    = 0b10000100;

   // Ciclo Infinito
   while (TRUE)
   {

   }
}