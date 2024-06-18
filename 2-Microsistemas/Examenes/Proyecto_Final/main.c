// --------------- Preprocesadores de microcontrolador -------------- //
#include    <18f4550.h>                                                 // Libreria del Microcontrolador
#fuses      HS, PLL1, CPUDIV1, NOWDT, NOPROTECT, NOLVP, NOMCLR, CCP2C1  // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 20MHz)                                        // Configuracion de delay
#device     PASS_STRINGS = IN_RAM
#use        rs232(rcv = pin_c7, xmit = pin_c6, baud = 9600, bits = 8, parity = n) 
#use        I2C (MASTER, SCL = PIN_D6, SDA = PIN_D7, FORCE_SW, FAST, stream = SSD1306_STREAM)

#include <PIC18F4550_registers.h>
#include "libraries/SSD1306OLED.c"
#include <stdlib.h>

// --------------------- Direccion de registros --------------------- //
#BIT     PWM1_PORT   = 0xF83.0   // PORTD
#BIT     PWM1_LAT    = 0xF8C.0   // LATD

#BIT     TMR0IE      = 0xFF2.5   // INTCON
#BIT     TMR2IE      = 0xF9D.1   // PIE1
#BIT     CCP1IE      = 0xF9D.2   // PIE1
#BIT     CCP2IE      = 0xFA0.0   // PIE2

#BIT     CCP1EDGE    = 0xFBD.0   // CCP1CON
#BIT     CCP2EDGE    = 0xFBA.0   // CCP2CON

#BIT     TMR0ON      = 0xFD5.0   // T0CON
#BIT     TMR1ON      = 0xFCD.0   // T1CON
#BIT     TMR2ON      = 0xFCA.2   // T2CON

#BIT     GO_DONE     = 0xFC2.1   // ADCON0

// -------------------------- M A C R O S --------------------------- //
#define  PR2_MIN     1         // 4.8 KHz
#define  PR2_MAX     255       // 38 Hz

// Motores a paso
#define  Step_PIN          PIN_B0
#define  Direction_PIN     PIN_B1

// Limit Switch
#define  Limit_Switch_1    PIN_D0
#define  Limit_Switch_2    PIN_D1

#define  get_adc()   (GO_DONE = TRUE, delay_us(10), ADRES)

// -------------------------- Estructuras --------------------------- //
typedef struct
{
   long  trigger_PIN;
   int32 echo_time;     // Tiempo detectado por echo en ciclos de trabajo
   float distance;      // Distancia en cm
   short echo_updated;  // TRUE: El tiempo esta actualizado, FALSE: El tiempo NO esta actualizado
} Ultrasonic_Sensor_t;

// ----------------------- Variables Globales ----------------------- //
// Instrucciones de aplicacion
char     target_str[10];
short    start = FALSE, stop = FALSE;

// Sensores ultrasonicos
Ultrasonic_Sensor_t UltSensor[2] = { { PIN_A4, 0, 0, FALSE }, { PIN_A5, 0, 0, FALSE } };
float    temp = 30.0, actual_distance = 0.0, target_distance = 0.0;

// Contador de pasos de motor a pasos
signed int32    steps    = 0;
short    Stepper_dist_ON = FALSE;

// Para control PID
const float Kp = 4, Ki = 0.1, Kd = 0.1;
short       PID_movement = TRUE;

// -------------------------- Interrupciones ------------------------ //
#INT_RDA
void Bluetooth_App()
{
   char data = getc();

   switch (data)
   {
      case '+':   // Recibimos start y distancia
      {
         gets(target_str);
         start = TRUE;
         break;
      }
      case '-':   // Recibimos stop
      {
         stop = TRUE;
         break;
      }
      default:
         break;
   }
}

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

      CCP2EDGE = UltSensor[1].echo_updated = TRUE;   // Esperamos el siguiente flanco de subida
   }
}

#INT_TIMER2    // Señal PWM de motores a paso
void PWM()
{
   output_toggle(Step_PIN);
   if(PWM1_PORT)
   {
      if(input(Direction_PIN))
         steps++;
      else
         steps--;
   }
}

// ---------------------------- Funciones --------------------------- //
void log_init()
{
   // Registros para puertos I/O
   TRISA    = 0b00000001;
   TRISB    = 0b00000000;
   TRISC    = 0b10000110;
   TRISD    = 0b00000011;
   
   // Registros para obtener temperatura de LM35
   ADCON0   = 0b00000011;
   ADCON1   = 0b00001110;
   ADCON2   = 0b10000000;

   // Registros para PWM de motores a paso
   INTCON   |= 0b11000000;
   TMR2IE   = TRUE;
   T2CON    = 0b01111010;     // Preescaler 16
   PR2      = PR2_MIN;
   TMR2ON   = TRUE;

   // Registros para ejecucion de sistema de control PID
   *TMR0    = 0;
   T0CON    = 0b00010100;  //  Cuenta maximo 40 ms

   // Registros para muestreo de distancia de sensores ultrasonicos
   *TMR3    = 0;
   T3CON    = 0b11001001;              // Configuramos timer 3 para ambos CCP
   CCP1CON = CCP2CON = 0b00000101;     // En modo captura flanco de subida
   CCP1IE = CCP2IE = TRUE;

   // Inicializamos OLED
   SSD1306_Begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
}

void Control_PID()
{
   TMR0ON = FALSE;
   float dt = *TMR0 / 156250.0;
   
   static float et_ant = 0, integral = 0;    // Las variables que se resetean

   // Control PID con datos actualizados
   float et = target_distance - actual_distance;      // ERROR CUANDO TARGET DISTANCE NO HA SIDO DEFINIDO
   
   // Parte Proporcional
   float P = Kp * et;

   // Parte Integral
   integral += et * dt;   // Error * dt
   float I = Ki * integral;

   // Parte Differencial
   float D = (et - et_ant) / dt;    // (ErrorAct - ErrorAnt) / dt 
   float output = (Kp * P) + (Ki * I) + (Kd * D);

   if(PID_movement)
   {
      if(output > PR2_MAX)
         output = PR2_MAX;
      else if(output < -PR2_MAX)
         output = -PR2_MAX;
      else if(output < PR2_MIN)
         output = PR2_MIN;
      else if(output > -PR2_MIN)
         output = -PR2_MIN;

      SSD1306_ClearDisplay();
      char string[21];
      sprintf(string, "dt=%f| et=%f\0", dt, et);
      SSD1306_DrawText(0, 0, string, 1);
      sprintf(string, "O=%f\0", output);
      SSD1306_DrawText(0, 40, string, 2);
      SSD1306_Display();
      delay_ms(2000);

      if(output > 0)    // Hay que avanzar
      {
         output = PR2_MAX - output;
         
         output_bit(Direction_PIN, FALSE);
         PR2 = abs(output);
         TMR2ON = TRUE;
      }
      else if(output < 0)     // Hay que retroceder
      {
         output = output + PR2_MAX;

         output_bit(Direction_PIN, TRUE);
         PR2 = abs(output);
         TMR2ON = TRUE;
      }
      else
         TMR2ON = FALSE;      // Si la salida es 0, ya no hay movimiento
   }
   
   *TMR0 = 0;
   TMR0ON = TRUE;    // Arranco timer 0 para dt de siguiente ciclo
}

void UltraSonic_Trigger()
{
   float dist[2] = { 0, 0 }, sound_speed = 33100 + (60 * temp);     // Velocidad del sonido en cm
   
   const int prom = 20;
   for(int i = 0; i < prom; i++)
   {
      // Enviamos señal trigger a sensores ultrasonicos
      output_high(UltSensor[0].trigger_PIN), output_high(UltSensor[1].trigger_PIN);
      delay_us(10);
      output_low(UltSensor[0].trigger_PIN), output_low(UltSensor[1].trigger_PIN);

      //while(!UltSensor[0].echo_updated || !UltSensor[1].echo_updated);
      for(int time = 0; (!UltSensor[0].echo_updated || !UltSensor[1].echo_updated); time++, delay_ms(1))
      {
         if(time > 25)
            break;
      }
      UltSensor[0].echo_updated = UltSensor[1].echo_updated = FALSE;

      dist[0] += (float) (UltSensor[0].echo_time * sound_speed / 10000000);
      dist[1] += (float) (UltSensor[1].echo_time * sound_speed / 10000000);
   }

   // Sacamos distancia promedio de mediciones
   UltSensor[0].distance = dist[0] / prom;
   UltSensor[1].distance = dist[1] / prom;
}

void Actual_Position()
{  
   UltraSonic_Trigger();      // Envio y confirmacion de señal trigger

   float Ultrasonic_dist = (UltSensor[0].distance + UltSensor[1].distance) / 2.0;
   float Stepper_dist = steps * 0.0033379;

   if(!Stepper_dist_ON)    // Si aun no llegamos a punto 0
   {
      actual_distance = Ultrasonic_dist;
      return;
   }

   // Si estamos a menos de 4 cm nos quedamos con la distancia de los pasos
   if(Stepper_dist < 4)
   {
      actual_distance = Stepper_dist;
      return;
   }

   // Si varia mucho la distancia, nos fiamos del ultrasonico
   if((Stepper_dist < (Ultrasonic_dist + 2)) && (Stepper_dist > (Ultrasonic_dist - 2)))   // Si varian mucho las distancias
   {
      actual_distance = Ultrasonic_dist;
      return;
   }

   actual_distance = Stepper_dist;
}

// ------------------------ Codigo Principal ------------------------ //
void main()
{
   log_init();

   output_bit(Direction_PIN, FALSE);
   PR2 = 5;
   TMR2ON = TRUE;    // Activamos movimiento de motor
   while(!input(Limit_Switch_1) || !input(Limit_Switch_2));
   TMR2ON = FALSE;   // Desactivamos moviemiento de motor

   steps = 0;
   Stepper_dist_ON = TRUE;
   target_distance = 15;

   // Realizar primer acople con objeto
   // Confirmamos que el objeto esta enfrente con sensores ultrasonicos, en caso de que no, o este fuera de rango, avisar en pantalla
   // Esperamos boton de start para acoplarnos al objeto
   // 

   SSD1306_ClearDisplay();
   SSD1306_DrawText(21, 21, "SCADA\0", 3);
   SSD1306_Display();
   delay_ms(1000);

   while (TRUE)
   {  
      Actual_Position();      // Obtenemos posicion actual de objeto
      Control_PID();          // Ejecutamos control PID

      // Mostrar distancia actual y temperatura en pantalla OLED
      char distance_str[9], distance2_str[9], temp_str[9];
      sprintf(temp_str, "%2.2f C\0", temp);
      //sprintf(distance_str, "%3.1f cm\0", UltSensor[0].distance);
      //sprintf(distance2_str, "%3.1f cm\0", UltSensor[1].distance);
      sprintf(distance_str, "%3.1f cm\0", actual_distance);

      SSD1306_ClearDisplay();
      SSD1306_DrawText(5, 5, temp_str, 1);
      SSD1306_DrawText( 16, 24, distance_str, 2);
      //SSD1306_DrawText( 16, 24, distance_str, 2);
      //SSD1306_DrawText( 16, 42, distance2_str, 2);
      SSD1306_Display();

      if(start)   // Recibimos distancia y movimiento de control PID
      {
         target_distance = atof(target_str);
         
         PR2 = (PR2_MAX - PR2_MIN) / 2 + PR2_MIN;
         TMR2ON = TRUE;    // Activamos movimiento de motor
         while(!input(Limit_Switch_1) || !input(Limit_Switch_2));
         TMR2ON = FALSE;   // Desactivamos moviemiento de motor
         
         PID_movement = TRUE;
         start = FALSE;
      }

      if(stop)       // Se solicito detenerse
         TMR2ON = PID_movement = FALSE;      // Desactivamos control PID y movimiento del motor
      
         
      /*/
      for(int i = PR2_MIN; i < PR2_MAX; i++, delay_ms(delay))
         PR2 = i;
      
      for(int i = PR2_MAX; i >= PR2_MIN; i--, delay_ms(delay))
         PR2 = i;
      //*/
   }
}

// Nuestro rango de distancias va desde 5 -> 50 cm

// Crear un timer que calcule la salida del sistema y solicite lectura para siguiente salida de sistema