// ============================================= STEPPER MOTOR ============================================= //

// -------------------------- Estructuras --------------------------- //
typedef struct
{
   long           DirectionPIN;  // Pin para cambiar direccion del motor
   long           StepPIN;       // Pin para realizar un paso en el motor
   short          Direction;      // TRUE: Adelante | FALSE: Atras
} stepper_motor;

// ---------------------------- Funciones --------------------------- //
void stepper_init(stepper_motor *Motor, long DirectionPIN, long StepPIN)
{
   Motor->DirectionPIN = DirectionPIN;
   Motor->StepPIN = StepPIN;
   Motor->Direction = TRUE;
}

void stepper_movement(stepper_motor *Motor)
{
   output_bit(Motor->DirectionPIN, Motor->Direction);

   output_high(Motor->StepPIN);
   output_low(Motor->StepPIN);
   delay_us(4);
}

// ============================================== SERVO MOTOR ============================================== //

// --------------------- Direccion de registros --------------------- //
#BYTE       TRISD          = 0xF95
#BIT        OUT_ServoPWM   = 0xF8C.0      // LATD
#BIT        IN_ServoPWM    = 0xF83.0      // PORTD

#BYTE       T0CON          = 0xFD5
const long  *TMR0          = 0xFD6;

#BYTE       INTCON         = 0xFF2

// ----------------------- Variables Globales ----------------------- //
unsigned long T0_dutyCicle = 6400;
// 2800 | 6400

// ----------------------------- MACROS ----------------------------- //
#define  set_servo(bool) (T0_dutyCicle = (bool) ? 6400 : 2800)
#define  T0_minvalue    15535
// Valor minimo 15535, valor maximo 65535 | Diferencia: 50000

// -------------------------- Interrupciones ------------------------ //
#INT_TIMER0
void ServoMotorPWM()
{
   if(IN_ServoPWM)   // Si se desbordo estando en alto
   {
      OUT_ServoPWM = FALSE;   // Lo ponemos en bajo
      set_timer0(T0_minvalue + T0_dutyCicle);
   }
   else
   {
      OUT_ServoPWM = TRUE;   // Lo ponemos en alto
      set_timer0(T0_minvalue + 50000 - T0_dutyCicle);
   }
}

// ---------------------------- Funciones --------------------------- //
void servo_init()
{
   // Configuracion de puertos I/O
   TRISD          &= 0b11111110;
   
   // Configuracion de TIMER 0
   T0CON = 0b10000000;     // Timer 0 Preescaler 2, a 50 Hz 
   OUT_ServoPWM   = TRUE;
   *TMR0 = T0_minvalue + 50000 - 2500;

   // Configuracion interrupcion de TIMER 0
   INTCON |= 0b10100000;   // Activamos interrupcion
}