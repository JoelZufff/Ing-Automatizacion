#include "interface.c"
#include "motors.c"
//#include <math.h>

#define  WireSensor_PIN    PIN_B0

// --------------------- Direccion de registros --------------------- //
#BYTE    TRISB             = 0xF93
#BYTE    TRISC             = 0xF94
#BYTE    INTCON            = 0xFF2
#BIT     RC1IE             = 0xFD9.5   // PIE1    
#BIT     INT0IE            = 0xFF2.4   // INTCON
#BIT     INTEDG0           = 0xFF1.6   // INTCON2

// -------------------------- Estructuras --------------------------- //

typedef struct
{
   short       HasPeeling;    // Booleano que especifica que el cable va pelado
   variable_t  amount;        // Cantidad
   variable_t  length;        // Longitud del cable (mm)
} wire_print_order;

// ----------------------- Variables Globales ----------------------- //
stepper_motor  INMOTOR, OUTMOTOR;
wire_print_order Bluetooth_Order;

// ----------------------------- MACROS ----------------------------- //


// -------------------------- Interrupciones ------------------------ //
#INT_RDA
void bluetooth_receive()      // Para recibir datos de interfaz grafica, hacerlo de maxima prioridad
{
   char data = getc();

   // PENDIENTE
}

#INT_EXT
void wiresensor_change()
{
   // PENDIENTE
   // Se dejo de detectar cable, por lo que hasta que se vuelva a detectar habra indicacion
   // Si se deja de detectar en medio de una orden, se activa un booleano
   // Si se deja de detectar sin orden, se solicita ingreso de cable
}

// ---------------------------- Funciones --------------------------- //
void wiresensor_init()
{
   // Configuracion de puertos I/O
   TRISB    |= 0b00000001;

   // Configuracion de interrupcion
   INTCON   |= 110000000;
   INT0IE   = TRUE;

   // Si detecta un rising edge significa que se dejo de detectar el cable
   INTEDG0  = TRUE;    // Rising edge
}

void bluetooth_init()
{
   // Configuracion de puertos I/O
   TRISC |= 0b00000001, TRISC &= 0b11111101;

   // Configuracion de interrupcion
   INTCON   |= 110000000;
   RC1IE    = TRUE;
}

void WireStation_init()
{
   // Interfaz grafica
   interface_init();
   
   // Comunicacion Bluetooth
   bluetooth_init();
   
   // Sensores y controles
   wiresensor_init();
   
   // Motores o Actuadores
   servo_init();
   stepper_init(&INMOTOR, PIN_A5, PIN_E0);
   stepper_init(&OUTMOTOR, PIN_E1, PIN_E2);
}

void order_print(wire_print_order *Order)
{
   Load:
   SSD1306_ClearDisplay();
   SSD1306_DrawText( (SSD1306_LCDWIDTH - (strlen("INTRODUZCA\0") * 12)) / 2, 14, "INTRODUZCA\0", 2);
   SSD1306_DrawText( (SSD1306_LCDWIDTH - (strlen("CABLE\0") * 12)) / 2, 34, "CABLE\0", 2);
   SSD1306_Display();

   INMOTOR.Direction = TRUE;     // Hacia adelante

   // El motor de entrada se movera por 5 segundos hasta detectar cable en el sensor
   while(input(WireSensor_PIN))
      stepper_movement(&INMOTOR);    // 4 us

   for(long wire = 1; wire <= Order->amount.Value; wire++)     // Impresion de cada cable
   {  
      SSD1306_ClearDisplay();
      SSD1306_DrawText( (SSD1306_LCDWIDTH - (strlen("CABLE\0") * 12)) / 2, 14, "CABLE\0", 2);
      
      char string[22];
      sprintf( string, "%4lu / %4ld", wire, Order->amount.Value);
      SSD1306_DrawText( (SSD1306_LCDWIDTH - (strlen(string) * 12)) / 2, 34, string, 1);
      SSD1306_Display();

      // Conversion de mm de pedido a pasos del motor (Hacer macro para conversion PENDIENTE)
   }
        
}

void WireStation_physicalorder()
{
   wire_print_order actual_order = { TRUE, { 1, 1, 100 }, { 80, 80, 10000 }};
      
      Main:
   
      Amount:
      if(variable_set(&actual_order.amount, "Cantidad\0"))
         goto Main;
      
      Length:
      if(variable_set(&actual_order.length, "Longitud (mm)\0"))
         goto Amount;
      
      Resume:
      if(order_resume(actual_order.length.Value, actual_order.amount.Value))
         goto Length;

      // Impresion de orden
      order_print(&actual_order);
}
/*
#INT_RDA:   Recepcion de datos bluetooth
#INT_EXT:   Cambio en sensor de presencia de cable
#INT_EXT1:  Recepcion de instrucciones de encoder codificador
*/