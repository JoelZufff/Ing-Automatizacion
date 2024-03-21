// MICROCONTROLADOR PARA IMPRESION A GLCD

// --------------- Preprocesadores de microcontrolador -------------- //
#include    <18f4550.h>                                              // Libreria del Microcontrolador
#fuses      INTRC, CPUDIV1, PLL1, NOWDT, NOPROTECT, NOLVP, NOMCLR    // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 8M)                                        // Configuracion de frecuencia y delay
#use        rs232(rcv = pin_c7, xmit = pin_c6, baud = 9600, bits = 8, parity = n)

#define FAST_GLCD

#include <HDM64GS12.c>
#include <graphics.c>
#include <pixelshapes.c>

// --------------------- Direccion de registros --------------------- //
#BYTE       INTCON      = 0xFF2
#BIT        RCIE        = 0xF9D.5      // PIE1
#BIT        RCIP        = 0xF9F.5      // IPR1
#BIT        IPEN        = 0xFD0.7      // RCON

#BYTE       T0CON       = 0xFD5
const int16 *TMR0       = 0xFD6;

// -------------------------- Estructuras -------------------------- //
struct element
{
   int         size[2];                // Tamaño en 'x' y 'y'
   signed int  position[2];            // Cordenada de posicion actual (Cordenada [0][0] de elemento)
   signed int  printed_position[2];    // Coordenada de ultima posicion de impresion
};

// ----------------------- Variable Globales ------------------------ //
struct element player1, player2;

int1 pause_button = TRUE, player1_button = FALSE, player2_button = FALSE;

// --------------------------- Funciones --------------------------- //
void display_refresh();

void log_settings()     // Configuracion de registros
{
   // Configuracion de registros de interrupciones
   INTCON   = 0b11100000;
   IPEN = RCIE = RCIP = 1;
   // Activamos interrupcion de recepcion EUSART y la hacemos de alta priodidad para evitar perdida de datos de instrucciones
   
   // Configuracion de registros de TIMER 0
   *TMR0    = 48868;
   T0CON    = 0b00000000;
}

void elements_init()
{
   // Configuracion de elementos de tipo jugador
   player1.size[0] = 17, player1.size[1] = 12;    // Tamaño en 'x' y 'y' 
   player1.position[0] = player1.printed_position[0] = 1; 
   player1.position[1] = player1.printed_position[1] = 21;

   player2.size[0] = 17, player2.size[1] = 12;    // Tamaño en 'x' y 'y' 
   player2.position[0] = player2.printed_position[0] = 67; 
   player2.position[1] = player2.printed_position[1] = 21;
}

void pause_animation()
{
   T0CON    = 0b00000000;  // Desactivamos TIMER de actualizacion de pantalla
   
   glcd_fillScreen(OFF);
   
   // Imprimimos rectangulo y letras
   glcd_rect( 0, 0, 127, 63, OFF, ON);
   glcd_text57( 4, 6, (char*) "FLAPPY BIRD", 2, ON);
   
   // Imprimimos marcador PENDIENTE


   // Animacion de espera
   int1 toggle = ON;
   while(pause_button)    // Animacion de espera
   {
      glcd_text57( 4, 48, (char*) "<- Presione START ->", 1, toggle);
      delay_ms(250);
      toggle ^= 1;
      glcd_update();
   }

   // Cuenta regresiva
   display_refresh();      // Mostramos ultimo contenido de juego para hacer cuenta regresiva
   for(char num = '3'; num > '0'; num--, delay_ms(1000))
   {
      char cadena[2];
      cadena[0] = num, cadena[1] = '\0';
      
      glcd_circle( 63, 31, 15, ON, OFF);
      glcd_text57( 58, 24, cadena, 2, ON);
      glcd_update();
   }

   T0CON    = 0b10000000;  // Volvemos a activar TIMER de actualizacion de pantalla
}

void element_print(struct element elemento)
{
   for(int x = 0; x < elemento.size[0]; x++)
      for(int y = 0; y < elemento.size[1]; y++)
         if(bird_pixels[y][x] != 2)             // Si no es un pixel nulo
            glcd_pixel( x + elemento.position[0], y + elemento.position[1], bird_pixels[y][x] );
}

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
   *TMR0    = 48868;      // 30 Hz

   // Borramos contenido de pantalla
   glcd_fillScreen(OFF);
   
   // Impresion de columna de separacion
   glcd_line(63,0,63,63, ON), glcd_line(64,0,64,63, ON);

   // Impresion de pajaros en posicion
   element_print(player1);
   element_print(player2);

   // Impresion de barreras
   
   glcd_update();
}

// ------------------------ Codigo Principal ----------------------- //
void main()
{
   // Configuracion de registros e inicializacion de GLCD
   log_settings();
   glcd_init(ON);
   
   // Inicializamos elementos
   elements_init();

   Pause:
   pause_animation();

   // Ciclo Infinito
   while (TRUE)
   {
      if(pause_button)
         goto Pause;

      player1.position[1] > 0 ? (player1.position[1]--) : (player1.position[1] = 63 - player1.size[1]);
      player2.position[1] > 0 ? (player2.position[1]--) : (player2.position[1] = 63 - player2.size[1]);
      delay_ms(5);
         
      /*/
      // Realizar movimientos
      if(player1_button)
      {
         player1.position[1] > 0 ? (player1.position[1]--) : (player1.position[1] = 63 - player1.size[1]);
         player1_button = FALSE;
      }
      
      if(player2_button)
      {
         player2.position[1] > 0 ? (player2.position[1]--) : (player2.position[1] = 63 - player2.size[1]);
         player2_button = FALSE;
      }
      //*/
   }
}

// Cuando ocurra el cambio de posicion de un elemento se borrara su rastro anterior primero, y luego se pondra el nuevo