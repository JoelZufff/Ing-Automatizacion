// --------------- Preprocesadores de microcontrolador -------------- //
#include    <18f4550.h>                                              // Libreria del Microcontrolador
#fuses      HS, CPUDIV1, PLL1, NOWDT, NOPROTECT, NOLVP, NOMCLR    // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 48M)                                        // Configuracion de frecuencia y delay
#use        rs232(rcv = pin_c7, xmit = pin_c6, baud = 9600, bits = 8, parity = n)

#define     FAST_GLCD
#define     obst_num    2
#define     obst_space  55

#include <stdlib.h>
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
struct pipeline
{
   int            size[2];                // Tamaño en 'x' y 'y'
   signed int16   position[2][2];         // Cordenada de la esquina superior izquierda del elemento
   int            pipeline_index;         // Diseño de tuberia seleccionado
   int1           infront;                // Booleano para saber si la tuberia esta despues del personaje
};

struct character
{
   int            size[2];                // Tamaño en 'x' y 'y'
   signed int16   position[2][2];         // Cordenadas de la esquina superior izquierda del elemento
   int            jump_time;              // Temporizador de tiempo en salto
   int1           alive;                  // Booleano para saber si esta vivo el jugador 
};

struct game
{
   struct character  player;
   struct pipeline   obstacles[obst_num];
   int               coordinates[2][2];      // Coordenadas de las 2 esquinas del display
   int               score;                  // Puntuacion del juego
};

// ----------------------- Variable Globales ------------------------ //
struct game       displays[2];
int1              pause_button = TRUE;

// --------------------------- Funciones --------------------------- //
void log_settings()     // Configuracion de registros
{
   // Configuracion de registros de interrupciones
   INTCON   = 0b11000000;
   IPEN = RCIE = RCIP = 1;
   // Activamos interrupcion de recepcion EUSART y la hacemos de alta priodidad para evitar perdida de datos de instrucciones

   // Configuracion de registros de TIMER 0
   *TMR0    = 18660;
   T0CON    = 0b10000011;
}

void elements_init()
{
   pause_button = TRUE;

   // Establecemos coordenadas de la pantalla de jugador 1
   displays[0].coordinates[0][0] = 0,     displays[0].coordinates[0][1] = 0;      // Superior izquierda 
   displays[0].coordinates[1][0] = 62,    displays[0].coordinates[1][1] = 63;    // Inferior derecha

   // Establecemos coordenadas de la pantalla de jugador 2
   displays[1].coordinates[0][0] = 65,    displays[1].coordinates[0][1] = 0;      // Superior izquierda 
   displays[1].coordinates[1][0] = 127,   displays[1].coordinates[1][1] = 63;    // Inferior derecha

   // Inicializamos a los elementos de cada partida
   for(int i = 0; i < 2; i++)
   {
      displays[i].score = 0;

      // Inicializamos personaje
      displays[i].player.size[0] = 13, displays[i].player.size[1] = 9;                       // Tamaño en 'x' y 'y' 
      // Posicion Inicial (Esquina superior izquierda)
      displays[i].player.position[0][0] = 3 + displays[i].coordinates[0][0];
      displays[i].player.position[0][1] = 28;    
      // Posicion Inicial (Esquina inferior derecha)
      displays[i].player.position[1][0] = displays[i].player.position[0][0] + displays[i].player.size[0];
      displays[i].player.position[1][1] = displays[i].player.position[0][1] + displays[i].player.size[1];

      displays[i].player.alive = TRUE;
      displays[i].player.jump_time = 0;
      
      // Inicializamos obstaculos
      for(int j = 0; j < obst_num; j++)    // Configuramos las tuberias de cada partida
      {
         srand(*TMR0), displays[i].obstacles[j].pipeline_index = rand() % 3;     // Escogemos un diseño aleatorio para la tuberia
         displays[i].obstacles[j].size[0] = 13, displays[i].obstacles[j].size[1] = 64;
         // Posicion Inicial (Esquina superior izquierda)
         displays[i].obstacles[j].position[0][0] = 30 + (obst_space * j) + displays[i].coordinates[0][0];
         displays[i].obstacles[j].position[0][1] = 0;
         // Posicion Inicial (Esquina inferior derecha)
         displays[i].obstacles[j].position[1][0] = displays[i].obstacles[j].position[0][0] + displays[i].obstacles[j].size[0];
         displays[i].obstacles[j].position[1][1] = displays[i].obstacles[j].position[0][1] + displays[i].obstacles[j].size[1];
         
         displays[i].obstacles[j].infront = TRUE;
      }
   }

}

void game_print(struct game display)
{
   // Imprimimos el personaje en su posicion
   for(int x = 0; x < display.player.size[0]; x++)
      for(int y = 0; y < display.player.size[1]; y++)
         if(character_bitmap[y][x] != 2)             // Si no es un pixel nulo
            glcd_pixel( x + display.player.position[0][0], y + display.player.position[0][1], character_bitmap[y][x] );

   // Imprimimos los obstaculos visibles
   for(int i = 0; i < obst_num; i++)
   {
      // Establecemos valores maximos y minimos de la impresion del eje x, dependiendo si se sale del marco
      int xlim[2];   // Valores maximos y minimos de x y y para impresion
      
      if(display.obstacles[i].position[1][0] > display.coordinates[1][0]) // Si se sale del borde derecho
      {
         if(display.obstacles[i].position[0][0] > display.coordinates[1][0])  // Si se salio del borde derecho completamente
            continue;

         // Si se salio parciamente del borde derecho
         xlim[0] = 0, xlim[1] = display.coordinates[1][0] - display.obstacles[i].position[0][0];
      }
      else if(display.obstacles[i].position[0][0] < display.coordinates[0][0])     // Si se sale del borde izquierdo
      {
         if (display.obstacles[i].position[1][0] < display.coordinates[0][0]) // Si se salio del borde izquierdo completamente
            continue;
         
         // Si se salio parcialmente del borde izquierdo
         xlim[0] = display.coordinates[0][0] - display.obstacles[i].position[0][0], xlim[1] = display.obstacles[i].size[0];
      }
      else
         xlim[0] = 0, xlim[1] = display.obstacles[i].size[0];        // Impresion completa

      for(int x = xlim[0]; x < xlim[1]; x++)
         for(int y = 0; y < display.obstacles[i].size[1]; y++)
            if(pipelines_bitmap[display.obstacles[i].pipeline_index][y][x] != 2)    // Si no es un pixel nulo
               glcd_pixel( x + display.obstacles[i].position[0][0], y + display.obstacles[i].position[0][1], pipelines_bitmap[display.obstacles[i].pipeline_index][y][x] );
   }
}

void pause_animation()
{
   INTCON   &= 0b11011111;  // Desactivamos interrupcion timer 0 para movimiento de elementos
   
   glcd_fillScreen(OFF);
   
   // Imprimimos rectangulo y letras
   glcd_rect( 0, 0, 127, 63, OFF, ON);
   glcd_text57( 4, 6, (char*) "FLAPPY BIRD", 2, ON);
   
   for( int i = 0; i < 2; i++)
   {
      char string_score[5];
      itoa(displays[i].score, 10, string_score);
      glcd_text57( 25 + (displays[i].coordinates[0][0]), 27, string_score, 2, ON);
   }

   // Animacion de espera
   int1 toggle = ON;
   while(pause_button)    // Animacion de espera
   {
      glcd_text57( 4, 48, (char*) "<- Presione START ->", 1, toggle);
      delay_ms(250);
      toggle ^= 1;
      glcd_update();
   }

   // Mostramos ultimo contenido de juego para hacer cuenta regresiva
   
   glcd_fillScreen(OFF);
   // Impresion de columna de separacion
   glcd_line(63,0,63,63, ON), glcd_line(64,0,64,63, ON);
   // Impresion de cada pantalla de partida
   game_print(displays[0]);
   game_print(displays[1]);
   glcd_update();
   
   // Cuenta regresiva
   for(char num = '3'; num > '0'; num--, delay_ms(600))
   {
      char cadena[2];
      cadena[0] = num, cadena[1] = '\0';
      
      glcd_circle( 63, 31, 15, ON, OFF);
      glcd_text57( 58, 24, cadena, 2, ON);
      glcd_update();
   }
   
   INTCON   |= 0b00100000;  // Activamos interrupcion de timer 0 para movimiento de elementos
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
         if(!pause_button && displays[0].player.alive)
            displays[0].player.jump_time += 3;
         break;
      }
      case '2':
      // Se presiono el boton del jugador 2
      {
         if(!pause_button && displays[1].player.alive)
            displays[1].player.jump_time += 3;
         break;
      }
      default: break;
   } 
}

#int_timer0
void movements()
{
   *TMR0    = 30000;

   // Movimiento de personaje y obstaculos 
   for(int i = 0; i < 2; i++)       // Por cada display
   {
      if(!displays[i].player.alive)
         continue;
      
      // Movimiento del personaje
      if(displays[i].player.jump_time > 0)
      {
         displays[i].player.position[0][1] -= 2;
         displays[i].player.position[1][1] -= 2;
         displays[i].player.jump_time--;
      }
      else if(displays[i].player.position[1][1] < displays[i].coordinates[1][1])
         displays[i].player.position[0][1]++, displays[i].player.position[1][1]++;
      
      // Movimiento de obstaculos
      for(int j = 0; j < obst_num; j++)
      {
         if (displays[i].obstacles[j].position[1][0] < displays[i].coordinates[0][0]) // Si se salio del borde izquierdo completamente
         {
            srand(*TMR0 * j),  displays[i].obstacles[j].pipeline_index = rand() % 3;        // Escogemos un diseño aleatorio para la tuberia
            
            int previous = (j == 0) ? obst_num-1 : j-1;
            displays[i].obstacles[j].position[0][0] = displays[i].obstacles[previous].position[0][0] + obst_space;
            displays[i].obstacles[j].position[1][0] = displays[i].obstacles[j].position[0][0] + displays[i].obstacles[j].size[0];

            displays[i].obstacles[j].infront = TRUE;
            continue;
         }
         displays[i].obstacles[j].position[0][0]--;
         displays[i].obstacles[j].position[1][0]--;

         if(displays[i].player.position[1][0] >= displays[i].obstacles[j].position[0][0] && displays[i].obstacles[j].infront)  // El personaje esta o ya paso la tuberia
         {
            // Si el personaje ya paso el obstaculo
            if(displays[i].player.position[0][0] > displays[i].obstacles[j].position[1][0])
            {
               displays[i].score++;
               displays[i].obstacles[j].infront = FALSE;
               continue;
            }

            // El personaje esta dentro del obstaculo
            int xlim[2];            // Analizaremos que columnas coinciden entre los 2
            int xmin_obs;

            if(displays[i].player.position[0][0] < displays[i].obstacles[j].position[0][0])  // Esta entrando
            {
               xlim[0] = displays[i].obstacles[j].position[0][0] - displays[i].player.position[0][0];
               xlim[1] = displays[i].player.size[0];
               xmin_obs = 0;
            }
            else if(displays[i].player.position[1][0] > displays[i].obstacles[j].position[1][0])   // Esta saliendo
            {
               xlim[0] = 0;
               xlim[1] = displays[i].player.position[1][0] - displays[i].obstacles[j].position[1][0];
               xmin_obs = displays[i].player.position[0][0] - displays[i].obstacles[j].position[0][0];
            }
            else
            {
               xlim[0] = 0;
               xlim[1] = displays[i].player.size[0];
               xmin_obs = 0;
            }

            for(int x = xlim[0], x_obs = xmin_obs; x < xlim[1] && displays[i].player.alive ; x++, x_obs++)     // Si no hubo colision
               for(int y = 0; y < displays[i].player.size[1]; y++)
                  if((character_bitmap[y][x] != 2) && (pipelines_bitmap[displays[i].obstacles[j].pipeline_index][y + displays[i].player.position[0][1]][x_obs] != 2))     
                  // Si no son pixeles nulos en los 2 arreglos, hay una colision 
                  {
                     displays[i].player.alive = FALSE;
                     putc('m');
                     break;
                  }
         }
      }
   }  
};

// ------------------------ Codigo Principal ----------------------- //
void main()
{
   // Configuracion de registros e inicializacion de GLCD
   log_settings();
   glcd_init(ON);
   
   restart:
   // Inicializamos elementos
   elements_init();

   pause:
   pause_animation();

   // Ciclo Infinito
   while (TRUE)
   {
      if(pause_button)
         goto pause;

      
      // Borramos contenido de pantalla
      glcd_fillScreen(OFF);

      // Impresion de columna de separacion
      glcd_line(63,0,63,63, ON), glcd_line(64,0,64,63, ON);

      // Impresion de score
      for( int i = 0; i < 2; i++)
      {
         char string_score[5];
         itoa(displays[i].score, 10, string_score);
         glcd_text57( 1 + (displays[i].coordinates[0][0]), 2, string_score, 1, ON);
      }

      // Impresion de cada pantalla de partida si el jugador esta vivo
      game_print(displays[0]);
      game_print(displays[1]);

      glcd_update();

      // Si ya murieron los 2 pajaros
      if(!displays[0].player.alive && !displays[1].player.alive)
      {
         glcd_fillScreen(ON);
         char *result;

         if(displays[0].score > displays[1].score)
         {
            char aux[] = "PLAYER 1";
            result = aux;
         }
         else if(displays[0].score < displays[1].score)
         {
            char aux[] = "PLAYER 2";
            result = aux;
         }
         else
         {
            char aux[] = " EMPATE ";
            result = aux;
         }

         glcd_text57( 15, 25, result, 2, OFF);
         glcd_update();

         pause_button = TRUE;
         while (pause_button);
         
         goto restart;
      }

   }
}

// Cuando ocurra el cambio de posicion de un elemento se borrara su rastro anterior primero, y luego se pondra el nuevo