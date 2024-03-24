// --------------- Preprocesadores de microcontrolador -------------- //
#include    <18f4550.h>                                              // Libreria del Microcontrolador
#fuses      INTRC, CPUDIV1, PLL1, NOWDT, NOPROTECT, NOLVP, NOMCLR    // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 8M)                                        // Configuracion de frecuencia y delay
#use        rs232(rcv = pin_c7, xmit = pin_c6, baud = 9600, bits = 8, parity = n)


// --------------------- Direccion de registros --------------------- //
#BYTE       INTCON      = 0xFF2
#BYTE       INTCON3     = 0xFF0
#BIT        IPEN        = 0xFD0.7      // RCON
#BIT        RCIE        = 0xF9D.5      // PIE1
#BIT        RCIP        = 0xF9F.5      // IPR1

#BYTE       TRISA       = 0xF92

#BYTE       TRISB       = 0xF93
#BIT        START_PAUSE = 0xF81.0   // PORTB
#BIT        PLAYER1     = 0xF81.1   // PORTB
#BIT        PLAYER2     = 0xF81.2   // PORTB
#BIT        MOTOR       = 0xF8A.3   // LATB

// ----------------------- Variable Globales ------------------------ //
int1        vibration = FALSE;

// ------------------------- Interrupciones ------------------------ //
#int_rda
void receive() 
{
   // Recibir instrucciones de estatus de display
   char buffer = getchar();

   if(buffer == 'm')
      MOTOR = TRUE;
}

// Boton de pausa es de mayor prioridad, es decir que puede interrumpir a un boton de jugador
#int_ext
void pause_button() { putc('C'); }

// Botones se activan en flanco de subida, y son de la misma prioridad, es decir que se ejecuta uno despues de otro
#int_ext1
void player1_button() { putc('1'); }

#int_ext2
void player2_button() { putc('2'); }

// ------------------------ Codigo Principal ----------------------- //
void main()
{
   // Configuracion de registros de pines I/O
   TRISB    = 0b00000111;
   TRISA    = 0b00000000;

   // Configuracion de registros de interrupciones
   INTCON   = 0b11010000;
   INTCON3  = 0b00011000;

   // Activamos interrupcion de recepcion EUSART y la hacemos de alta priodidad para evitar perdida de datos de instrucciones
   IPEN = RCIE = RCIP = 1;

   int16 timer[3] = { 0, 0, 0 };

   // Ciclo Infinito
   while (TRUE)
   {
      // Si detectamos una presion mandamos señal cada 200 ms
      
      PLAYER1  ? (timer[0]++) : (timer[0] = 0);
      PLAYER2  ? (timer[1]++) : (timer[1] = 0);
      MOTOR    ? (timer[2]++) : (timer[2] = 0);


      if(timer[0] == 200)
         putc('1'), timer[0] = 0;
      
      if(timer[1] == 200)
         putc('2'), timer[1] = 0;

      if(timer[2] == 2000)
         MOTOR = FALSE, timer[2] = 0;

      delay_ms(1);
   }
}