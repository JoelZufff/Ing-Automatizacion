// --------------- Preprocesadores de microcontrolador -------------- //
#include    <18f4550.h>                                                 // Libreria del Microcontrolador
#fuses      HS, PLL1, CPUDIV1, NOWDT, NOPROTECT, NOLVP, NOMCLR, CCP2C1  // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 20MHz)                                        // Configuracion de delay
#device     PASS_STRINGS = IN_RAM
#use        rs232(rcv = pin_c7, xmit = pin_c6, baud = 9600, bits = 8, parity = n) 
#use        I2C (MASTER, SCL = PIN_D6, SDA = PIN_D7, FORCE_SW, FAST, stream = SSD1306_STREAM)
#device     HIGH_INTS = TRUE

#include <PIC18F4550_registers.h>
#include "libraries/SSD1306OLED.c"
#include <string.h>
#include <stdlib.h>

// --------------------- Direccion de registros --------------------- //
#BIT     TMR0IE      = 0xFF2.5   // INTCON
#BIT     TMR2IE      = 0xF9D.1   // PIE1
#BIT     CCP1IE      = 0xF9D.2   // PIE1
#BIT     CCP2IE      = 0xFA0.0   // PIE2
#BIT     RCIE        = 0xF9D.5   // PIE1

#BIT     CCP1EDGE    = 0xFBD.0   // CCP1CON
#BIT     CCP2EDGE    = 0xFBA.0   // CCP2CON

#BIT     TMR0ON      = 0xFD5.0   // T0CON
//#BIT     TMR2ON      = 0xFCA.2   // T2CON

#BIT     PWM1_PORT   = 0xF81.0   // PORTB
#BIT     PWM1_LAT    = 0xF8A.0   // LATB
#BIT     DIR_PIN_O   = 0xF8A.1   // LATB
#BIT     DIR_PIN_I   = 0xF81.1   // LATB

//#BIT     GO_DONE     = 0xFC2.1   // ADCON0

// -------------------------- M A C R O S --------------------------- //
#define  PR2_MIN     1         // 4.8 KHz
#define  PR2_MAX     255       // 38 Hz

// Motores a paso
#define  STEP_PIN       PIN_B0
#define  DIR_PIN        PIN_B1

// Limit Switch
#define  Limit_Switch_1    PIN_D0
#define  Limit_Switch_2    PIN_D1

#define  steps_to_mm(steps)   (0.0324 * ((steps) + 24.6234) + 0.2022)
#define  mm_to_steps(mm)      ((((mm) - 0.2022) / 0.0324) - 24.6234)
//#define  get_adc()   (GO_DONE = TRUE, delay_us(10), ADRES)

// -------------------------- Estructuras --------------------------- //
typedef struct
{
   long  trigger_PIN;         // Posicion del PIN de trigger
   long  echo_time;           // Tiempo detectado por echo en ciclos de trabajo
   float distance;            // Distancia en mm
} Ultrasonic_Sensor_t;

// ----------------------- Variables Globales ----------------------- //
// Instrucciones de aplicacion
char     target_str[10];
short    target_updated = FALSE, movement_ON = FALSE, calibration_ON = FALSE;

// Medicion de distancia
Ultrasonic_Sensor_t UltSensor[2] = { { PIN_A4, 0, 0 }, { PIN_A5, 0, 0 } };

// Contador de pasos de motor a pasos
signed int32   actual_steps = 0;       // Posicion actual en pasos
signed int32   target_steps = 0;       // Distancia objetivo en pasos 

signed int32   stepper_steps = 0;      // Distancia recorida por motores a paso

short          stepper_valid = FALSE, US_valid = TRUE;

// Variables para el control PID
//const float Kp = 0.05, Kd = 0.001, Ki = 0.007, dt = 0.1048576;       // La QUE MAS JALA
//const float Kp = 0.02, Kd = 0.01, Ki = 0.06, dt = 0.1048576;       // La QUE MAS JALA
const float Kp = 0.05, Kd = 0.001, Ki = 0.005, dt = 0.1048576;       // La QUE MAS JALA
float et;

// -------------------------- Interrupciones ------------------------ //
#INT_RDA HIGH
void Bluetooth_App()
{
   char data = getc();

   switch (data)
   {
      case '+':   // Recibimos start y distancia
      {
         gets(target_str);

         // Activamos modo de calibracion de pasos
         US_valid = TRUE;
         stepper_valid = FALSE;
         target_steps = 0;       // Distancia objetivo

         calibration_ON = TRUE;
         movement_ON = TRUE;
         break;
      }
      case '-':   // Recibimos stop
      {
         movement_ON = FALSE;
         break;
      }
      default:
         break;
   }
}

#INT_TIMER2 HIGH        // Señal PWM de motores a paso
void PWM()              // Ejecucion de PWM
{
   output_toggle(STEP_PIN);
   if(PWM1_PORT)     // Ver si agregar start position aqui
   {
      if(DIR_PIN_I)   // TRUE: ATRAS | FALSE: ADELANTE
         stepper_steps++;
      else
         stepper_steps--;
      
      // De nada me sirve calcular el error aqui si nos basamos en los sensores, solo consumire ciclos maquina a lo wey
      if(stepper_valid && !calibration_ON)
      {
         et = (float) target_steps - stepper_steps;

         if(et == 0)          // Con los pasos si puede haber error 0
            TMR2IE = FALSE;
      }
   }
}

#INT_CCP1
void ECHO_signal_1()    // Recepcion de señal ECHO (Sensor 1)
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

      CCP1EDGE = TRUE;       // Esperamos el siguiente flanco de subida

      delay_ms(10);
      output_high(UltSensor[1].trigger_PIN), delay_us(10), output_low(UltSensor[1].trigger_PIN);
   }
}

#INT_CCP2
void ECHO_signal_2()    // Recepcion de señal ECHO (Sensor 2)
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
      
      CCP2EDGE = TRUE;           // Esperamos el siguiente flanco de subida
   }
}

#INT_TIMER0
void PID_Control()
{  
   // DISTANCIA DE SENSORES ULTRASONICOS
   UltSensor[0].distance         = (0.0343 * UltSensor[0].echo_time) + 0.8589;   // Distancia en mm
   UltSensor[1].distance         = (0.0336 * UltSensor[1].echo_time) - 2.8107;   // Distancia en mm

   float US_distance       = (UltSensor[0].distance + UltSensor[1].distance) / 2;   // Sacamos el promedio

   if(stepper_valid && US_valid)
   {
      actual_steps = stepper_steps;
      
      if(((steps_to_mm(stepper_steps) < US_distance-5) || (steps_to_mm(stepper_steps) > US_distance+5)))  // Si la diferencia de distancia es mayor a +-5mm
      {
         actual_steps = mm_to_steps(US_distance);
         stepper_valid = FALSE;
      }
   }
   else if(stepper_valid && !US_valid)    // Si los pasos son validos
   {
      actual_steps = stepper_steps;

      if(steps_to_mm(stepper_steps) >= 50)     // Si es mayor a 50
         US_valid = TRUE;
   }
   else if(!stepper_valid && US_valid)
   {
      actual_steps = mm_to_steps(US_distance);

      if(US_distance < 30)     // Si es menor a 50
      {
         stepper_steps = mm_to_steps(US_distance + 15);
         stepper_valid = TRUE;
         US_valid = FALSE;
      }
      else if(((steps_to_mm(stepper_steps) >= US_distance-5) && (steps_to_mm(stepper_steps) <= US_distance+5)))  // Si la diferencia de distancia es mayor a +-5mm
      {
         actual_steps = stepper_steps;
         stepper_valid = TRUE;
         US_valid = FALSE;
      }
   }
      
   // CONTROL PID
   et = (float) target_steps - actual_steps;    // Posicion deseada - Posicion actual

   static float last_et = 0;
   static float I = 0;

   if((abs(et - last_et) > mm_to_steps(500)) && !calibration_ON)
      et = last_et;

   float P = Kp * et;                        // Parte PROPORCIONAL
   float D = Kd * ((et - last_et) / dt);     // Parte DIFERENCIAL
   I += Ki * (et*dt);                        // Parte INTEGRAL

   if(I > 150)
      I = 150;
   else if(I < -150)
      I = -150;

   last_et = et;     // Guardamos el error pasado

   long output = abs(P + I + D);       // La salida del sistema es la sumatoria
   
   // Establecer limites de saturacion de salida
   if(output > 255)
      output = 255;

   // Enviamos salida a PR2 y a sentido de giro dependiendo el signo del error
   output = PR2_MAX - output + PR2_MIN;

   if(calibration_ON && (output >= 10))
      output = 10;

   if(calibration_ON)
      DIR_PIN_O = FALSE;
   else
      DIR_PIN_O = !(et < 0);     // TRUE: ATRAS | FALSE: ADELANTE 
   
   PR2 = output;

   // Condiciones para ver si hay movimiento
   if((et == 0) || (!movement_ON))        // Si el movimiento esta desactivado
      TMR2IE = FALSE;
   else if((et != 0) && (movement_ON))    // Si el error es diferente de 0 y el movimiento esta activado
      TMR2IE = TRUE;
   
   // Enviamos señal trigger de primer sensor para muestreo de datos
   output_high(UltSensor[0].trigger_PIN), delay_us(10), output_low(UltSensor[0].trigger_PIN);
}

// ---------------------------- Funciones --------------------------- //
void log_init()
{
   // Registros para puertos I/O
   TRISA    = 0b00000001;
   TRISB    = 0b00000000;
   TRISC    = 0b10000110;
   TRISD    = 0b00000011;

   // Registros para PWM de motores a paso
   TMR2IE   = FALSE;
   INTCON   |= 0b11000000;
   T2CON    = 0b01111110;     // Preescaler 16
   PR2      = PR2_MAX;

   RCIE = TRUE;

   // Registros para muestreo de distancia
   CCP1IE = CCP2IE = TRUE;
   *TMR3    = 0;
   T3CON    = 0b11001001;              // Configuramos timer 3 para ambos CCP
   CCP1CON = CCP2CON = 0b00000101;     // En modo captura flanco de subida

   TMR0IE   = TRUE;                    // Activamos interrupcion de timer 0
   *TMR0    = 0;
   T0CON    = 0b10000010;              // Timer 0 (10 Hz)

   // Inicializamos OLED
   SSD1306_Begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
}

// ------------------------ Codigo Principal ------------------------ //
void main()
{
   log_init();

   SSD1306_ClearDisplay();
   SSD1306_DrawText(21, 21, "SCADA\0", 3);
   SSD1306_Display();
   delay_ms(1000);

   while (TRUE)
   {  
      // Impresion de distancia actual
      SSD1306_ClearDisplay();
      char string[20];
      if(movement_ON)
         sprintf(string, "ON\0");
      else 
         sprintf(string, "OFF\0"); 
      SSD1306_DrawText((128 - (12 * strlen(string))) / 2, 1, string, 2);
      sprintf(string, "%.1f cm\0", steps_to_mm(actual_steps) / 10.0); 
      SSD1306_DrawText((128 - (17 * strlen(string))) / 2, 23, string, 3);
      if(stepper_valid)
         sprintf(string, "Sensor: Pasos\0");
      else
         sprintf(string, "Sensor: Ultrasonico\0");
      SSD1306_DrawText((128 - (6 * strlen(string))) / 2, 55, string, 1);
      SSD1306_Display();

      delay_ms(10);
      
      if((input(Limit_Switch_1) || input(Limit_Switch_2)) && movement_ON && calibration_ON)
      {
         while(!input(Limit_Switch_1) || !input(Limit_Switch_2));   // Hasta que no se presionen los 2         
         TMR0IE = TMR2IE = FALSE;      // Desactivamos PID | Desactivamos el movimiento
         delay_ms(500);

         stepper_valid = TRUE;
         US_valid = FALSE;
         stepper_steps = 0;

         target_steps = mm_to_steps(atof(target_str) * 10);   // Distancia objetivo
         calibration_ON = FALSE;

         TMR0IE = TRUE;      // Desactivamos PID | Desactivamos el movimiento

         while(input(Limit_Switch_1) || input(Limit_Switch_2));   // Hasta que no se presionen desactiven los 2 limit
      }
   }
}

// Nuestro rango de distancias va desde 0 -> 50 cm

// Tamaño 1: 6 x 8   | 21 caracteres por fila
// Tamaño 2: 12 x 16 | 10 caracteres por fila
// Tamaño 3: 17 x 21 | 7 caracteres por fila
// Tamaño 3: 24 x 32 | 5 caracteres por fila