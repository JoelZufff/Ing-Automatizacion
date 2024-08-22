// Preprocesadores de Microcontrolador //
#include    <18f4550.h>                                             // Libreria del Microcontrolador
#fuses      INTRC, CPUDIV1, PLL1, NOWDT, NOPROTECT, NOLVP           // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 8M)                         // Configuracion de frecuencia y delay

// Establecemos direccion de registros
#BYTE       TRISD    = 0xF95
#BYTE       TRISC    = 0xF94

#BYTE       T2CON    = 0xFCA
#BYTE       PR2      = 0xFCB
#BYTE       CCP1CON  = 0xFBD
#BYTE       CCPR1L   = 0xFBE
#BYTE       ECCP1DEL = 0xFB7

void main()
{
   // Creacion de un PWM con su complementario a 1kHz y configurando el dead-band a 1 ciclo de trabajo
   
   //*/
   TRISD = 0;
   TRISC = 0;
   
   T2CON    = 0b00000110;     // Establecemos Timer 2 con preescaler 16
   PR2      = 124;
   ECCP1DEL |= 0b0000001;     // PWM DEAD-BAND DELAY REGISTER, configurado a 1 ciclo de trabajo (7 lsb)
   CCP1CON  = 0b10001100;     // Configuramos PWM como Half-bridge, y que sea complementario con P1A en high

   while (TRUE)
   {
      for(long DutyCicle = 0; DutyCicle < 500; DutyCicle++, delay_ms(10))
         CCPR1L   = DutyCicle >> 2;          // Perdemos los 2 lsb de resolucion
   }
   //*/

   /*/ Con PIC C COMPILER
   setup_timer_2(T2_DIV_BY_16, 124, 1);
   setup_ccp1(CCP_PWM | CCP_PWM_HALF_BRIDGE, 1);

   while (TRUE)
   {
      for(long DutyCicle = 0; DutyCicle < 500; DutyCicle++, delay_ms(10))
         set_pwm1_duty(DutyCicle);
   }
   //*/
}