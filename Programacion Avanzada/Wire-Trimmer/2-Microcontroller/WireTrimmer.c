// Preprocesadores de Microcontrolador //
#include    <18f4550.h>                                        // Libreria del Microcontrolador
#device     adc = 10                                           // Resolucion del ADC en bits
#fuses      INTRC, NOWDT, NOPROTECT, NOLVP, CPUDIV1, PLL1      // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 8M)                                  // Configuracion de delay
#use        rs232(rcv = pin_c7, xmit = pin_c6, baud = 9600, bits = 8, parity = n)

#include <stdlib.h>

// Preprocesadores LCD //
#define LCD_ENABLE_PIN  PIN_B2
#define LCD_RS_PIN      PIN_B0
#define LCD_RW_PIN      PIN_B1
#define LCD_DATA4       PIN_B4
#define LCD_DATA5       PIN_B5
#define LCD_DATA6       PIN_B6
#define LCD_DATA7       PIN_B7

#include    <lcd.c>

//  Constantes para mejor entendimiento   //
#define     DownButton     PIN_D6
#define     UpButton       PIN_D5
#define     LeftButton     PIN_D4
#define     RightButton    PIN_D7

#define     In       1
#define     Out      0

const long IndicatorLEDS[5] = {PIN_C0, PIN_C1, PIN_C2, PIN_D0, PIN_D1};

// Macros y variables constantes
#define     MinWireLength     30                      // Valor minimo de carrete disponible
#define     MaxWireLength     10000                   // Valor maximo de carrete disponible

// Estructuras //
struct wire_print_order
{
   long          PeelingLength;             // Longitud de pelado de cable (mm)
   long          Length;                    // Longitud del cable (mm)
   long          Amount;                    // Cantidad
};

struct stepper_motor
{
   long           DirectionPIN;              // Pin para cambiar direccion del motor
   long           StepPIN;                   // Pin para realizar un paso en el motor
};

// Variables globales
long     WireReel          = 0;              // Carrete diponible (mm)
int1     ConectionStatus   = FALSE;          // Booleano de conexion con interfaz grafica
int1     PendingOrderBool  = FALSE;          // Booleano de orden pendiente

struct   wire_print_order ComputerOrder = {0,0,0};

// Configuramos Motores a Pasos
struct stepper_motor ReelMotor               = {PIN_A1, PIN_A2};
struct stepper_motor WireMovementMotor       = {PIN_A3, PIN_A4};

const long           WireCuttingMotor[]      = {PIN_A5, PIN_E0, PIN_E1, PIN_E2};

// Interrupciones //
#int_rda
void ComputerConection()      // Para recibir datos de interfaz grafica
{
   char data = getch();

   switch (data)
   {
      case '+':      // Caracter de conexion
      {
         printf("+%05ld\n", WireReel);     // Enviamos informacion a interfaz grafica
         ConectionStatus = TRUE;
      }
      break;
      case '-':      // Caracter de desconexion
      {
         ConectionStatus = FALSE;
      }
      break;
      case '*':      // Caracter de envio de orden
      {
         // *(2 digitos - longitud de pelado)(5 digitos - longitud del cable)(4 digitos - cantidad de cables)
         char AmountBuffer[5];
         char LenghtBuffer[6];
         char PellingBuffer[3];

         // Recibimos caracteres de cantidad de cables
         for(int i = 0; i < 4; i++)
            AmountBuffer[i] = getch();
         AmountBuffer[4] = '\0';

         // Recibimos caracteres de longitud de cable
         for(int i = 0; i < 5; i++)
            LenghtBuffer[i] = getch();
         LenghtBuffer[5] = '\0';

         // Recibimos caracteres de longitud de pelado de cable
         for(int i = 0; i < 2; i++)
            PellingBuffer[i] = getch();
         PellingBuffer[2] = '\0';

         char *endptr;
         
         // Guardamos la orden para que se realize la impresion
         ComputerOrder.PeelingLength = strtoul(PellingBuffer, &endptr, 10);
         ComputerOrder.Length = strtoul(LenghtBuffer, &endptr, 10);
         ComputerOrder.Amount = strtoul(AmountBuffer, &endptr, 10);

         PendingOrderBool = 1;
      }
      break;
   }
}

//  Prototipos de funcion  //
int1 Number_Select(char Title[16], int16* Number, int16 MinNumber, int16 MaxNumber);                // Funcion para seleccion de numero

void Wire_Recharge();                                                                               // Funcion para recarga de cable
void Wire_Print(struct wire_print_order ActualOrder);                                               // Funcion de impresion de cable
void Wire_Movement(long Length);                                                                    // Funcion para mover el motor ciertos pasos
void Wire_Cut(int1 CuttinBool);

void WireReel_ChangeValue(long Length, int1 ResetBool);                                             // Funcion para actualizar valor de carrete
void WireReel_eeprom(long Value);
long WireReel_eeprom();

void main()
{  
   set_tris_a(0);
   
   for(int i = 0 ; i <4; i++)
      output_low(WireCuttingMotor[i]);

   // Configuramos carrete de memoria eeprom
   WireReel = WireReel_eeprom();

   // Desactivamos LEDS para evitar errores
   for(int i = 0; i < 5 ; i++)
      output_low(IndicatorLEDS[i]);
   
   // Activamos Interrupciones
   enable_interrupts(GLOBAL);       enable_interrupts(int_rda);

   // Mensaje Introductorio
   lcd_init();
   printf(lcd_putc,"\f  WIRE TRIMMER\n Prog. Avanzada");
   delay_ms(1000);

   while(true)
   {      
      // Si el cable es insuficiente, PROCESO DE RECARGA
      while(WireReel < MinWireLength || WireReel > MaxWireLength)
      {
         printf(lcd_putc,"\fCarrete Escaso");

         // Animacion
         for (long timer = 0; !input(RightButton); (timer > 1000) ? (timer = 0) : (timer++))
         {
            lcd_gotoxy(1, 2);

            if (timer == 1)
               printf(lcd_putc, "Nuevo Carrete->");
            else if(timer == 500)
               printf(lcd_putc, "               ");

            delay_ms(1);
         }
         while(input(RightButton));

         // Proceso de recarga de cable
         Wire_Recharge();
      }

      // Prendemos LEDS indicadores
      WireReel_ChangeValue(0, FALSE);

      Main:
      // Creacion de orden
      if(ConectionStatus)        // Se utiliza interfaz grafica para realizar ordenes
      {
         // Animacion mientras recibe datos
         printf(lcd_putc, "\f   Recibiendo   ");
         for(int i = 1; !PendingOrderBool; (i > 16) ? (i = 1) : i++ )
         {
            lcd_gotoxy(1,2);     printf(lcd_putc, "                ");
            lcd_gotoxy(i,2);     lcd_putc(0xFF);       delay_ms(100);

            if(!ConectionStatus) // Si hay una desconexion
               goto Main;
         }

         // Informamos orden recibida
         printf(lcd_putc, "\f %4lu Cable(s)  \n %2lu mm %5lu mm ", ComputerOrder.Amount, ComputerOrder.PeelingLength, ComputerOrder.Length);
         delay_ms(1000);

         // Imprimimos orden recibida
         Wire_Print(ComputerOrder);
         
         // Ya no hay orden pendiente y desconectamos conexion con computadora para confirmar conexion
         PendingOrderBool = ConectionStatus = 0;      
         putc('*');
         delay_ms(100);
      }
      else                       // Se utiliza la interfaz fisica para realizar ordenes
      {
         printf(lcd_putc,"\fCable: %5lu mm", WireReel);
         // Animacion
         for (long Timer = 0; !input(RightButton); (Timer > 1000) ? (Timer = 0) : (Timer++))
         {
            lcd_gotoxy(1, 2);

            if (Timer == 1)
               printf(lcd_putc, "Nueva Orden  ->");
            else if(Timer == 500)
               printf(lcd_putc, "               ");

            if(ConectionStatus)
               goto Main;

            delay_ms(1);
         }
         while(input(RightButton));

         // Creamos orden de impresion
         struct wire_print_order PhysicalOrder = {5, 0, 0};

         Peeling:
         // Valor maximo en funcion de longitud de cada cable
         if( Number_Select( (char*) "Pelado (mm):", &PhysicalOrder.PeelingLength, 0, 20) )
            goto Main;
         
         Length:
         // Valor maximo en funcion de: Carrete disponible - 2 veces longitud del pelado
         if( Number_Select( (char*) "Longitud (mm):", &PhysicalOrder.Length, 10 , WireReel - (PhysicalOrder.PeelingLength * 2)) )
            goto Peeling;
         
         Amount:
         // Valor maximo en funcion del carrete disponible y la longitud solicitada
         if( Number_Select( (char*) "Cantidad:", &PhysicalOrder.Amount, 1, WireReel / (PhysicalOrder.Length + (PhysicalOrder.PeelingLength * 2))) )
            goto Length;

         // Mensaje de confirmacion de orden
         printf(lcd_putc, "\f %4lu Cable(s)  \n %2lu mm %5lu mm ", PhysicalOrder.Amount, PhysicalOrder.PeelingLength, PhysicalOrder.Length);
         while(!input(RightButton))
            if(input(LeftButton))   {  while(input(LeftButton));  goto Amount; }
         while(input(RightButton));
         
         // Impresion del orden de cable
         Wire_Print(PhysicalOrder);
      
         printf(lcd_putc,"\fORDEN FINALIZADA\n Vuelva Pronto !");
         delay_ms(2000);
      }
   }
}

// Funciones //
int1 Number_Select(char Title[16], int16 *Number, int16 MinNumber, int16 MaxNumber)
{  
   // Declaramos e inicializamos variables que ocuparemos
   int1 PrintBool = 1;     int1 PositionChar = 0;    signed int MaxExponent = 0;   signed int Exponent = 0;
   
   // Correccion de posible error en numero
   (*Number < MinNumber) ? (*Number = MinNumber) : (*Number > MaxNumber ? (*Number = MaxNumber) : 0);

   // Sacamos el exponente del numero maximo posible que puede tomar el numero
   for(int16 aux = MaxNumber; aux >= 10; aux /= 10, MaxExponent++, Exponent++);

   // Impresion de titulo y espacio para numeros
   printf(lcd_putc, "\f%s\n", Title);

   long timer = 0;

   // Ciclo que se ejecuta el tiempo que se modifique el numero
   while((Exponent >= 0) && (Exponent <= MaxExponent))
   {
      long aux = 1;

      // Timer para animacion de seleccion
      delay_ms(1);
      (++timer == 1) ? (PrintBool = 1) : (timer == 500 ? (PositionChar = 1) : (timer == 1000) ? (timer = 0) : 0);
      
      // Impresion en LCD
      if(PrintBool)
      {
         lcd_gotoxy(6,2);
         printf(lcd_putc,"%06lu", *Number);     
         PrintBool = 0;    
      }
      else if(PositionChar)
      { 
         lcd_gotoxy(11-Exponent,2);    
         lcd_putc('_');    
         PositionChar = 0; 
      }
      
      // Modificacion de variable
      if(input(RightButton) || input(LeftButton))
      {
         input(RightButton) ? Exponent-- : Exponent++;
         timer = 0;

         while (input(RightButton) || input(LeftButton));
      }
      else if(input(UpButton) || input(DownButton))
      {
         // Calculo de potencia de 10 a sumar
         for(int i = 0; i < Exponent; i++, aux *= 10);

         if(input(DownButton))
            (((signed int32) *Number - aux) >= MinNumber) ? (*Number -= aux) : (*Number = MinNumber);
            // Si no se hace negativo, le restamos el numero
         else if(input(UpButton))
            ((*Number + aux) <= MaxNumber) ? (*Number += aux) : (*Number = MaxNumber);
            // Si no se hace mayor que el numero maximo, se lo sumamos

         timer = 0;

         while (input(DownButton) || input(UpButton));
      }
   } 

   // Si el exponente es mayor a MaxExponent significa que se presiono back desde el primer numero
   if(Exponent > MaxExponent)
      return true;
   else
      return false;
}

void Wire_Print(struct wire_print_order ActualOrder)
{
   for(int16 wire = 1; wire <= ActualOrder.Amount; wire++)     // Impresion de cada cable
   {  
      printf(lcd_putc,"\fCable %4lu /%4lu\n", wire, ActualOrder.Amount);

      // Conversion de mm de pedido a pasos del motor (Hacer macro para conversion PENDIENTE)
      
      printf(lcd_putc, "===");
      Wire_Movement(ActualOrder.PeelingLength);
      Wire_Cut(FALSE);

      printf(lcd_putc, "%c%c%c%c%c%c%c%c%c%c", 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
      Wire_Movement(ActualOrder.Length);
      Wire_Cut(FALSE);
      // Realizamos corte de pelado (Usar macro para conversion PENDIENTE

      printf(lcd_putc, "===");
      Wire_Movement(ActualOrder.PeelingLength);
      Wire_Cut(TRUE);

      WireReel_ChangeValue( (2 * ActualOrder.PeelingLength) + ActualOrder.Length, FALSE);
   }
   
}

// Error para cable menor al minwirelength o mayor al maxwirelength
void Wire_Recharge()
{  
   WireReel = 0;     // Reiniciamos la cantidad del carrete
   
   int32    Steps = 0;              // Contador de pasos del motor
   
   RechargingProcess:

   printf(lcd_putc, "\fMODO DE RECARGA\nEnrollar      ->");

   // Establecemos direccion de motores
   output_bit(ReelMotor.DirectionPIN, In);   
   output_bit(WireMovementMotor.DirectionPIN, In);

   int1     MovementBool = FALSE;       // Booleano para control de movimiento
   long     Timer = 0;              // Timer para movimiento de motores

   // Se enrollara el cable mientras el usuario lo desee
   for(Timer = 1; !input(UpButton) ; (Timer >= 30000 || (!MovementBool && !input(DownButton))) ? (Timer = 1) : (Timer++))
   {
      if(input(RightButton))
         MovementBool = TRUE;
      else if (input(LeftButton))
      {
         MovementBool = FALSE;
         lcd_gotoxy(1,2);
         printf(lcd_putc, "Enrollar      ->");
      }

      if((Timer % 4) == 0)    // Cada 5 ms
      {
         output_high(ReelMotor.StepPIN);
         output_low(ReelMotor.StepPIN);

         lcd_gotoxy(1,1);
         printf(lcd_putc, "    %5lu mm    ", ++Steps * 780 / 951);
         lcd_gotoxy(1,2);
         printf(lcd_putc, "Detener       <-");
      }

      if((Timer % 3) == 0)          // Cada 2 ms
      {
         output_high(WireMovementMotor.StepPIN);
         output_low(WireMovementMotor.StepPIN);
      }

      delay_ms(1);
   }
   while(input(UpButton));

   printf(lcd_putc, "\fVolver        <-\nFinalizar     ->");
   
   while(!input(RightButton))
   {
      if(input(LeftButton))
      {
         while(input(LeftButton));
         goto RechargingProcess;
      }
   }
   while(input(RightButton));
   
   // Usar macro para convertir los pasos a mm PENDIENTE

   WireReel_ChangeValue(Steps * 780 / 951, TRUE);
}

void Wire_Movement(long Length)
{
   // Convertir la longitud a pasos del motor
   int32 Steps = (int32) Length * 951 / 780;
   int32 ActualStep;
   
   // Establecemos direccion a los motores
   output_bit(ReelMotor.DirectionPIN, Out);
   output_bit(WireMovementMotor.DirectionPIN, Out);
   
   
   for(long Timer = 1, ActualStep = 0; ActualStep < Steps ; (Timer >= 30000) ? (Timer = 0) : (Timer++))
   {
      if((Timer % 20) == 0)    // Si pasaron 100 ms
      {
         output_high(ReelMotor.StepPIN);
         output_low(ReelMotor.StepPIN);
         ActualStep++;
      }
      
      if((Timer % 9) == 0)          // Si pasaron 50 ms 
      {
         output_high(WireMovementMotor.StepPIN);
         output_low(WireMovementMotor.StepPIN);
      }

      delay_ms(1);
   }
}

void Wire_Cut(int1 CuttinBool)
{
   int i = 0, j = 1;
   
   int MaxStep = CuttinBool ? 145 : 60;
   
   for(int Steps = 0; Steps < MaxStep; Steps++, (i == 3) ? (i = 0) : (i++), (j == 3) ? (j = 0) : (j++))
   {
      output_high(WireCuttingMotor[i]);
      output_high(WireCuttingMotor[j]);
      delay_ms(5);
      output_low(WireCuttingMotor[i]);
      output_low(WireCuttingMotor[j]);
   }

   // Reducimos las variables 2 veces
   (i == 0) ? (i = 3) : (i--);
   (i == 0) ? (i = 3) : (i--);

   (j == 0) ? (j = 3) : (j--);
   (j == 0) ? (j = 3) : (j--);


   for(int Steps = 0; Steps < MaxStep; Steps++, (i == 0) ? (i = 3) : (i--), (j == 0) ? (j = 3) : (j--))
   {
      output_high(WireCuttingMotor[i]);
      output_high(WireCuttingMotor[j]);
      delay_ms(5);
      output_low(WireCuttingMotor[i]);
      output_low(WireCuttingMotor[j]);
   }
}

void WireReel_ChangeValue(long Length, int1 RestetBool)
{  
   if (Length > 0)
   {
      if(RestetBool)
         WireReel = Length;
      else
         WireReel -= Length;
   
      // Acutalizar memoria eeprom
      WireReel_eeprom(WireReel);
   }
   
   // Prendemos los leds indicadores de longitud de carrete
   for(int i = 0; i < 5; i++)
   {
      if(i < ( WireReel * 5 / MaxWireLength ))
         output_high(IndicatorLEDS[i]);
      else
         output_low(IndicatorLEDS[i]);
   }
}

void WireReel_eeprom(long Value)
{
   int *Down, *Top;

   // Dividimos el long en 2 int
   Down = (int *) &Value;
   Top = Down + 1;

   // Guardamos el long en 2 localidades int de la memoria eeprom
   write_eeprom(0, *Down);
   write_eeprom(1, *Top);
}

long WireReel_eeprom()
{
   // Obtenemos la parte alta y baja del long
   int Down = read_eeprom(0);
   int Top = read_eeprom(1);

   // Regresamos el long obtenido
   return (((long) Top << 8) | Down);
}

// PENDIENTES:
// Poner cantidad maxima de recarga y Posible cambio de velocidad aprentando up y low
// Crear interrupcion de timer para revisar constantemente el sensor de cable
// Corregir posible error cuando haya poco carrete en pelado
