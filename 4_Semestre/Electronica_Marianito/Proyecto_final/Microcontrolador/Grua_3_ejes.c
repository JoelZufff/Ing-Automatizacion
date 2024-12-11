// --------------- Preprocesadores de microcontrolador -------------- //
#include    <18f4550.h>                                              // Libreria del Microcontrolador
#device     adc = 10                                                 // Preprocesador que indica Bits de resolucion del ADC
#fuses      HS, PLL1, CPUDIV1, NOWDT, NOPROTECT, NOLVP               // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 20MHz)                                     // Configuracion de delay

#use        rs232(rcv = pin_c7, xmit = pin_c6, baud = 115200, bits = 8, parity = n)         // Recibir instrucciones

#include    <stdlib.h>

// --------------------- Direccion de registros --------------------- //
#BYTE       TRISA          = 0xF92
#BYTE       TRISB          = 0xF93
#BYTE       LATB           = 0xF8A
#BYTE       TRISC          = 0xF94
#BYTE       TRISD          = 0xF95
#BIT        status_LED     = 0xF8C.1   // LATD
#BIT        working_LED     = 0xF8C.0   // LATD


#BYTE       T0CON          = 0xFD5
const int16 *TMR0          = 0xFD6;
#BIT        TMR0IP         = 0xFF1.2   // INTCON2

#BYTE       INTCON         = 0xFF2
#BIT        IPEN           = 0xFD0.7   // RCON
#BIT        RCIE           = 0xF9D.5   // PIE1
#BIT        RCIP           = 0xF9F.5   // IPR1

// -------------------------- Estructuras --------------------------- //
struct Stepper_motor_t
{
   long  steps_PIN[4];
   int   step_index;
   int1  dir;

   long  steps;
   int32 requested_steps;
   int1  done;
};

struct bth_conection_t
{
   int1 status;
   int1 new_data;
   int1 check;
};

// ----------------------- Variables Globales ----------------------- //
#define TMR0_value 17309

// Interfaz grafica
struct bth_conection_t PC = { FALSE, FALSE, FALSE };

// Motores a paso
struct Stepper_motor_t X_axis = { { PIN_B7, PIN_B6, PIN_B5, PIN_B4 }, 0, TRUE, 0, 0, TRUE };
struct Stepper_motor_t Z_axis = { { PIN_B3, PIN_B2, PIN_B1, PIN_B0 }, 0, FALSE, 0, 0, TRUE };
struct Stepper_motor_t THETA_axis = { { PIN_A5, PIN_E0, PIN_E1, PIN_E2 }, 0, TRUE , 0, 0, TRUE };

char X_cm[10], Z_cm[10], THETA_angle[10];
char X_dir, Z_dir, THETA_dir;

float temp_sensors[2] = { 0.0, 0.0 };

// -------------------------- Interrupciones ------------------------ //
#INT_RDA
Bluetooth_Interface()
{   
   char data = getc();

   switch (data)
   {
      case '+':      // Recibimos confirmacion de conexion
      {         
         PC.status = PC.check = TRUE;
         break;
      }
      case '*':      // Recibimos datos de movimiento de motores
      {
         // Almacenar datos recibidos
         gets(X_cm);
         X_dir = getch();
         
         gets(Z_cm);
         Z_dir = getch();

         gets(THETA_angle);
         THETA_dir = getch();

         PC.new_data = TRUE;
         break;
      }
      default: break;
   }   
}

#INT_TIMER0                            // Enviamos datos periodicamente
void BTH_connection()
{
   *TMR0 = TMR0_value;

   // Confirmamos conexion
   if(PC.check)                        // Hubo confirmacion de conexion
   {
      status_LED = TRUE;
      PC.check = FALSE;
   }
   else                                // No hubo confirmacion de conexion
   {
      status_LED ^= TRUE;
      PC.status = FALSE;
   }

   // Enviamos datos de sensores
   printf("#%lu %lu | %lu %lu | %lu %lu\n", X_axis.steps, X_axis.requested_steps, Z_axis.steps, Z_axis.requested_steps, THETA_axis.steps, THETA_axis.requested_steps);
   //printf("# 0 1 | 2 3 | 4 5\n");

   set_adc_channel(0);
   delay_us(10);
   printf("+%f\n", read_adc() * 0.97 / 10.0 );
   //printf("+%f\n", 10.0);
   set_adc_channel(1);
   delay_us(10);
   printf("%f\n", read_adc() * 0.97 / 10.0);
   //printf("+%f\n", 11.0);
}

// ---------------------------- Funciones --------------------------- //
void stepper_movement(struct Stepper_motor_t *Motor)        // Ocupa un delay despues de ejecutarse
{  
   output_low(Motor->steps_PIN[Motor->step_index]); 

   if (Motor->dir)                        // Derecha
      (Motor->step_index == 3) ? (Motor->step_index = 0) : (Motor->step_index++);
   else                                   // Izquierda
      (Motor->step_index == 0) ? (Motor->step_index = 3) : (Motor->step_index--);

   output_high(Motor->steps_PIN[Motor->step_index]);
   
   Motor->steps++;
}


// ------------------------ Codigo Principal ------------------------ //
void main()
{  
   // Registros para configuracion de puertos I/O
   TRISA    = 0b00001011;
   TRISB    = 0b00000000;
   TRISC    = 0b10000000;
   TRISD    = 0b00000000;

   // Configuracion de ADC's
   setup_adc(adc_clock_div_2);               // Activacion y configuracion del ADC
   setup_adc_ports(AN0_TO_AN1, VSS_VREF);    // ADC's desde GND a voltaje de referencia

   // Interrupcion de timer 0 para comprobar conexion
   T0CON = 0b10000110;     // 5 Hz
   *TMR0 = TMR0_value;

   // Configuracion de Interrupciones
   INTCON   = 0b11100000;
   IPEN = RCIE = RCIP = TRUE;       // Establecemos la interrupcion de recepcion serial como prioridad
   TMR0IP = FALSE;

   // Inicializamos variables
   status_LED = working_LED = FALSE;

   output_high(X_axis.steps_PIN[0]); output_low(X_axis.steps_PIN[1]); output_low(X_axis.steps_PIN[2]); output_low(X_axis.steps_PIN[3]);
   output_high(Z_axis.steps_PIN[0]); output_low(Z_axis.steps_PIN[1]); output_low(Z_axis.steps_PIN[2]); output_low(Z_axis.steps_PIN[3]);
   output_high(THETA_axis.steps_PIN[0]); output_low(THETA_axis.steps_PIN[1]); output_low(THETA_axis.steps_PIN[2]); output_low(THETA_axis.steps_PIN[3]);

   while(TRUE)
   {  
      if(PC.new_data)      // Si se recibio una solicitud de movimiento
      {
         working_LED = TRUE;
         
         // Reiniciamos valores
         X_axis.steps = Z_axis.steps = THETA_axis.steps = 0;
         X_axis.done = Z_axis.done = THETA_axis.done = FALSE;

         // Convertimos valores
         X_axis.requested_steps = atoi32(X_cm) * 1000;
         X_axis.dir = X_dir - 48;

         Z_axis.requested_steps = atoi32(Z_cm) * 900;
         Z_axis.dir = Z_dir - 48;

         THETA_axis.requested_steps = (float) atoi32(THETA_angle) * 3.99;
         THETA_axis.dir = THETA_dir - 48;

         while (!X_axis.done || !Z_axis.done || !THETA_axis.done)
         {
            // Se ejecuta el movimiento de los motores
            if(X_axis.steps < X_axis.requested_steps)          // Si el eje X tiene pasos pendientes
               stepper_movement(&X_axis);
            else
               X_axis.done = TRUE;
            
            if(Z_axis.steps < Z_axis.requested_steps)          // Si el eje Z tiene pasos pendientes
               stepper_movement(&Z_axis);
            else
               Z_axis.done = TRUE;

            if(THETA_axis.steps < THETA_axis.requested_steps)  // Si el eje THETA tiene pasos pendientes
               stepper_movement(&THETA_axis);
            else
               THETA_axis.done = TRUE;

            delay_ms(10);
         }

         PC.new_data = working_LED = FALSE;
      }
   }
}

// El control solo me tiene que decir la direccion y velocidad de los pasos

// Crear un timer que envie la informacion de los sensores de temperatura y progreso de movimiento de motores cada cierto tiempo
   // Este vuelve FALSE un booleano que se llama confirmar conexion, si antes de la siguiente activacion no se vuelve a poner TRUE, confirmamos una desconexion y detenemos el timer de envio de 
   
// Protocolo de funcionamiento de comunicacion
// El pic estara mandando constantemente informacion, 