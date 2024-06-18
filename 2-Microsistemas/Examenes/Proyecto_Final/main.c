// --------------- Preprocesadores de microcontrolador -------------- //
#include    <18f4550.h>                                                 // Libreria del Microcontrolador
#fuses      HS, PLL1, CPUDIV1, NOWDT, NOPROTECT, NOLVP, NOMCLR, CCP2C1  // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 20MHz)                                        // Configuracion de delay
#device     PASS_STRINGS = IN_RAM
//#use        rs232(rcv = pin_c7, xmit = pin_c6, baud = 9600, bits = 8, parity = n) 
#use        I2C (MASTER, SCL = PIN_D6, SDA = PIN_D7, FORCE_SW, FAST, stream = SSD1306_STREAM)

#include <PIC18F4550_registers.h>
#include "libraries/SSD1306OLED.c"

// --------------------- Direccion de registros --------------------- //
#BIT     PWM1_PORT   = 0xF83.0   // PORTD
#BIT     PWM1_LAT    = 0xF8C.0   // LATD

#BIT     TMR2IE      = 0xF9D.1   // PIE1
#BIT     CCP1IE      = 0xF9D.2   // PIE1
#BIT     CCP2IE      = 0xFA0.0   // PIE2

#BIT     CCP1EDGE    = 0xFBD.0   // CCP1CON
#BIT     CCP2EDGE    = 0xFBA.0   // CCP2CON

#BIT     TMR2ON      = 0xFCA.2   // T2CON
#BIT     TMR1ON      = 0xFCD.0   // T1CON

#BIT     GO_DONE     = 0xFC2.1   // ADCON0

// -------------------------- M A C R O S --------------------------- //
#define  PR2_MIN     7         // 25.38 KHz
#define  PR2_MAX     255       // 610 Hz

// Motores a paso
#define  Step_PIN          PIN_B0
#define  Direction_PIN1    PIN_B1   // Llanta izquierda
#define  Direction_PIN2    PIN_B2   // Llanta derecha

#define  get_adc()   (GO_DONE = TRUE, delay_us(10), ADRES)

// -------------------------- Estructuras --------------------------- //
typedef struct
{
   long  trigger_PIN;
   int32 echo_time;     // Tiempo detectado por echo en us
   int   measure_cont;  // Contador de mediciones para promedio
   float distance;      // Distancia en mm
   short echo_updated;  // TRUE: El tiempo esta actualizado, FALSE: El tiempo NO esta actualizado
} Ultrasonic_Sensor_t;

// ----------------------- Variables Globales ----------------------- //
Ultrasonic_Sensor_t UltSensor[2] = { { PIN_A4, 0, 0, FALSE }, { PIN_A5, 0, 0, FALSE } };
int32    steps    = 0;

// -------------------------- Interrupciones ------------------------ //
/*
#INT_RDA
void Bluetooth_App()
{
   char data = getc();
}
*/

#INT_CCP1
void ECHO_signal_1()    // Recibir y medir tiempo de señal echo de sensores ultrasonicos
{
   static long init_time = 0;
   
   if(CCP1EDGE)    // Detecto flanco de subida
   {
      init_time   = *CCPR1;
      CCP1EDGE    = FALSE;             // Esperamos el flanco de bajada
   }
   else           // Detecto flanco de bajada
   {
      if((*CCPR1) < init_time)     // Se desbordo el timer 1
         UltSensor[0].echo_time = (65535 - init_time) + (*CCPR1);
      else
         UltSensor[0].echo_time = (*CCPR1) - init_time;

      UltSensor[0].distance = (float) UltSensor[0].echo_time * 343 / 100000;
      
      CCP1EDGE = UltSensor[0].echo_updated = TRUE;   // Esperamos el siguiente flanco de subida
   }
}

#INT_CCP2
void ECHO_signal_2()
{
   static long init_time = 0;

   if(CCP2EDGE)    // Detecto flanco de subida
   {
      init_time   = *CCPR2;
      CCP2EDGE    = FALSE;             // Esperamos el flanco de bajada
   }
   else           // Detecto flanco de bajada
   {
      if((*CCPR2) < init_time)     // Se desbordo el timer 1
         UltSensor[1].echo_time = (65535 - init_time) + (*CCPR2);
      else
         UltSensor[1].echo_time = (*CCPR2) - init_time;

      UltSensor[1].distance = (float) UltSensor[1].echo_time * 343 / 100000;

      CCP2EDGE = UltSensor[1].echo_updated = TRUE;   // Esperamos el siguiente flanco de subida
   }
}

#INT_TIMER2    // Señal PWM de motores a paso
void PWM()
{
   output_toggle(Step_PIN);
   if(PWM1_PORT) 
      steps++;
}

// ---------------------------- Funciones --------------------------- //
void log_init()
{
   // Configuracion de puertos I/O
   TRISA    = 0b00000001;
   TRISB    = 0b00000000;
   TRISC    = 0b10000110;
   TRISD    = 0b00000011;
   
   // Configuracion para PWM de motores (TIMER 2, interrupcion)
   INTCON   = 0b11000000;
   TMR2IE   = TRUE;
   T2CON    = 0b00001010;     // Preescaler 16

   // Para activar motores, establecemos direccion con direction_PIN, establecemos velocidad con PR2 y encendemos timer
   PR2      = PR2_MAX;
   TMR2ON   = FALSE;

   *TMR3    = 0;            // Reiniciamos valor de timer 1
   T3CON    = 0b11001001;   // Configuramos timer 1 para ambos CCP
   //T1CON    = 0b11001001;   // Configuramos timer 1 preescaler 1

   // Configuracion de modulo CCP en modo captura, para sensores ultrasonicos
   CCP1CON  = 0b00000101;   // En modo captura flanco de subida
   CCP1IE   = TRUE;         // Activamos interrupcion
   CCP2CON  = 0b00000101;   // En modo captura flanco de subida
   CCP2IE   = TRUE;         // Activamos interrupcion
}

void US_get_distance()
{
   // Enviamos señal trigger a sensores ultrasonicos
   output_high(UltSensor[0].trigger_PIN), output_high(UltSensor[1].trigger_PIN);
   delay_us(10);
   output_low(UltSensor[0].trigger_PIN), output_low(UltSensor[1].trigger_PIN);
   
   delay_ms(40);
   
   SSD1306_ClearDisplay();
   SSD1306_DrawText( 0, 0, "SENSOR 1:", 2 );
   if(UltSensor[0].echo_updated)
   {      
      char string[21];
      sprintf(string, "%f\0", UltSensor[0].distance);
      //sprintf(string, "%lu\0", UltSensor[0].echo_time);
      SSD1306_DrawText( 0, 16, string, 2 );

      UltSensor[0].echo_updated = FALSE;
   }

   SSD1306_DrawText( 0, 32, "SENSOR 2:", 2 );
   if(UltSensor[1].echo_updated)
   {
      UltSensor[1].distance = (float) UltSensor[1].echo_time * 350 / 100000;

      char string[21];
      sprintf(string, "%f\0", UltSensor[1].distance);
      //sprintf(string, "%lu\0", UltSensor[1].echo_time);
      SSD1306_DrawText( 0, 48, string, 2 );

      UltSensor[1].echo_updated = FALSE;
   }

   SSD1306_Display();
}

// ------------------------ Codigo Principal ------------------------ //
void main()
{
   log_init();

   // Configuracion de pantalla OLED
   SSD1306_Begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);

   SSD1306_ClearDisplay();
   SSD1306_DrawText( 0, 0, "ESPERANDO\0", 2 );
   SSD1306_Display();

   delay_ms(500);

   //while(steps < 50000);
   //TMR2ON = PWM1_LAT = FALSE;
   //const long delay = 10;
   
   while(TRUE)
   {
      US_get_distance();
      /*
      if(UltSensor[0].echo_updated)
      {
         char string[21];
         //sprintf(string1, "%lu\0", UltSensor[0].distance);
         sprintf(string, "%lu\0", UltSensor[0].echo_time);

         SSD1306_ClearDisplay();
         SSD1306_DrawText( 0, 40, string, 2 );
         SSD1306_Display();

         UltSensor[0].echo_updated = FALSE;
      }
      else
      {
         SSD1306_ClearDisplay();
         SSD1306_DrawText( 0, 40, "NO PULSO", 2 );
         SSD1306_Display();
      }
      */
      
      /*/
      char string[21];
      sprintf(string, "%lu\0", steps);

      SSD1306_ClearDisplay();
      SSD1306_DrawText( 0, 0, "Pasos:", 2 );
      SSD1306_DrawText( 0, 18, string, 2 );
      SSD1306_Display();
      //*/

      /*/
      for(int i = PR2_MIN; i < PR2_MAX; i++, delay_ms(delay))
         PR2 = i;
      
      for(int i = PR2_MAX; i >= PR2_MIN; i--, delay_ms(delay))
         PR2 = i;
      //*/
   }
}

/*
* INSTRUMENTACION
Aplicar filtro de kaltman para obtener una medicion precisa de las 3 mediciones

* Control
Aplicar control PID para mover los motores en funcion de la distancia actual y la deseada
*/