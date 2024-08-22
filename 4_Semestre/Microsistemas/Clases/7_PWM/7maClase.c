// Preprocesadores de Microcontrolador //
#include    <18f4550.h>                                             // Libreria del Microcontrolador
#fuses      INTRC, CPUDIV1, PLL1, NOWDT, NOPROTECT, NOLVP           // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 8M)                         // Configuracion de frecuencia y delay

// Establecemos direccion de registros
#BYTE       TRISB    = 0xF93
#BYTE       TRISC    = 0xF94

#BYTE       T2CON    = 0xFCA
#BYTE       PR2      = 0xFCB
#BYTE       CCP1CON  = 0xFBD
#BYTE       CCP2CON  = 0xFBA
#BYTE       CCPR1L   = 0xFBE
#BYTE       CCPR2L   = 0xFBB

void main()
{
   TRISB = 0;
   TRISC = 0;
   
   T2CON    = 0b00000110;     // Establecemos Timer 2 con preescaler 16
   PR2      = 124;
   CCP1CON  |= 0b00001100;
   CCP2CON  |= 0b00001100;
   
   while (TRUE)
   {
      for(int16 DutyCicle = 0; DutyCicle <= 500; DutyCicle++, delay_ms(1))
      {
         CCPR1L = DutyCicle >> 2;
         //CCPR2L = (500-DutyCicle) >> 2;
      }
   }
   

   /* Con PIC C COMPILER
   setup_timer_2(T2_DIV_BY_16, 124, 1);
   setup_ccp1(0x0C);

   while (TRUE)
   {
      set_pwm1_duty(62);
   }
   */  
}