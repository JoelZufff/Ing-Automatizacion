// Microcontrolador encargado de recibir las señales del sensor de color, mostrar las etapas en torreta y LCD, y mandar las instrucciones a los actuadores controlador por el otro PIC
// --------------- Preprocesadores de microcontrolador -------------- //
#include  <18F4550.h>
#fuses    INTRC, NOWDT, NOPROTECT, NOLVP, CPUDIV1, PLL1, NOMCLR, CCP2C1
#use      delay(clock = 8Mhz)
#use      rs232(rcv = pin_c7, xmit = pin_c6, baud = 9600, bits = 8, parity = n)

#include  "lcd.c"

// ----------------------- Variable Globales ------------------------ //
#define S2            PIN_E1
#define S3            PIN_E2
#define Start_Button  PIN_A0

#define BLACK         0
#define RED           1
#define GREEN         2
#define BLUE          3

long        rise, fall, period;
int         contador_tapas[4] = { 0, 0, 0, 0 }, color;

int1        escan_mode = TRUE, lcd_print = TRUE;

// -------------------------- Interrupciones ------------------------ //
#INT_CCP2
void isr()      // Mide periodo en High
{
  fall = CCP_2;  
  rise = CCP_1;

  period = fall - rise;  
}  

#INT_RDA
void receive()
{
  char data = getc();

  if(data == '#')
    escan_mode = TRUE;
}

// ---------------------------- Funciones -------------------------- //
int color_detect()
{
  float colors[3];        // 0 RED | 1 BLUE | 2 GREEN

  for(int color_index = 0; color_index < 3; color_index++)
  {
    float color_freq = 0;

    switch (color_index)
    {
      case 0:
      {
        output_low(S2);
        output_low(S3);
        break;
      }
      case 1:
      {
        output_low(S2);
        output_high(S3);
        break;
      }
      case 2:
      {
        output_high(S2);
        output_high(S3);
        break;
      }
      default: break;
    }
    
    enable_interrupts(INT_CCP2);
    for(int i = 0; i < 50; i++)
      color_freq  += 1.0 / ( period * 0.000001 );
    disable_interrupts(INT_CCP2);
    
    colors[color_index] = color_freq / 50.0;
  }
    
  //printf("R = %f | G = %f | B = %f \r\n", colors[0], colors[2], colors[1])
  if(colors[0] <= 500 && colors[1] <= 560 && colors[2] <= 500)
    return BLACK;
  else if (colors[0] > colors[1] && colors[0] > colors[2])
    return RED;
  else if (colors[1] > colors[0] && colors[1] > colors[2])
    return BLUE;
  else if (colors[2] > colors[0] && colors[2] > colors[1])
    return GREEN;
}

// ------------------------ Codigo Principal ----------------------- //
void main()
{
  setup_ccp1(CCP_CAPTURE_RE);
  setup_ccp2(CCP_CAPTURE_FE);
  setup_timer_1(T1_INTERNAL);

  enable_interrupts(INT_CCP2);
  enable_interrupts(INT_RDA);
  enable_interrupts(GLOBAL);
   
  lcd_init();
  
  //*/
  // Animacion de INICIO  
  printf(lcd_putc,"\fBANDA SEPARADORA");
  int16 time = 0;
  for (int1 flag = TRUE; !input(Start_Button); time >= 200 ? (flag ^= 1, (time = 0)) : time++)
  {
    lcd_gotoxy(1, 2);

    if (flag)
        printf(lcd_putc, "Comenzar    -->");
    else
        printf(lcd_putc, "               ");

    delay_ms(1);
  }
  while(input(Start_Button));

  // Ciclo infinito
  while(TRUE) 
  {
    if(lcd_print)
    {
      // Actualizamos valor de contador en LCD
      printf(lcd_putc, "\fB: %4u| R: %4u", contador_tapas[BLACK], contador_tapas[RED]);
      printf(lcd_putc, "\nG: %4u| B: %4u", contador_tapas[GREEN], contador_tapas[BLUE]);
      
      lcd_print = FALSE;
    }

    if(escan_mode)    // Si estamos en etapa de escaneo otra vez
    {
      escan_mode = FALSE;
      // Esaneamos color
      color = color_detect();
      
      // Comenzamos etapa de movimiento
      printf("*%c", color + 48);   // Avisamos que comienza etapa de movimiento y mandamos color
      
      lcd_print = TRUE;
      contador_tapas[color]++;

      // Imprimir color en display
      char color_string[16];
      
      switch (color)
      {
          case BLACK:
            sprintf(color_string, "\fColor: Negro\0");
            break;
          case RED:
            sprintf(color_string, "\fColor: Rojo\0");
            break;
          case GREEN:
            sprintf(color_string, "\fColor: Verde\0");
            break;
          case BLUE:
            sprintf(color_string, "\fColor: Azul\0");
            break;
          default: return; break;
      }

      printf(lcd_putc, color_string);
      delay_ms(1000);
    }
  }
  //*/

  /*/
  while (TRUE)
  {
    char color[16];

    switch (color_detect())
    {
        case WHITE:
          sprintf(color, "\fColor: Blanco\0");
          break;
        case BLACK:
          sprintf(color, "\fColor: Negro\0");
          break;
        case RED:
          sprintf(color, "\fColor: Rojo\0");
          break;
        case GREEN:
          sprintf(color, "\fColor: Verde\0");
          break;
        case BLUE:
          sprintf(color, "\fColor: Azul\0");
          break;
        default: return; break;
    }

    printf(lcd_putc, color);
  }
  //*/
}

/*
Hay 4 etapas de funcionamiento
* Escaneo
* Movimiento
* Colocacion
* Listo
*/