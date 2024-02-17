// --------------- Preprocesadores de microcontrolador -------------- //
#include    <18f4550.h>                                                 // Libreria del Microcontrolador
#fuses      INTRC, CPUDIV1, PLL1, NOWDT, NOPROTECT, NOLVP, NOMCLR       // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 8M)                                           // Configuracion de frecuencia y delay

// --------------------- Direccion de registros --------------------- //  
#BYTE           TRISA       = 0xF92

const int16     *ADRES      = 0xFC3;
#BYTE           ADCON0      = 0xFC2
#BIT            DONE        = 0xFC2.1
#BYTE           ADCON1      = 0xFC1
#BYTE           ADCON2      = 0xFC0

#BYTE           TRISB       = 0xF93
#BYTE           LATB        = 0xF8A
#BIT            PWM1        = 0xF8A.4
#BIT            PWM2        = 0xF8A.5

#BYTE           TRISD       = 0xF95
#BYTE           DISPLAY     = 0xF8C

#BYTE           T0CON       = 0xFD5
#BYTE           TMR0L       = 0xFD6

#BYTE           T1CON       = 0xFCD
#BYTE           TMR1L       = 0xFCE

#BYTE           INTCON      = 0xFF2
#BIT            TMR1IE      = 0xFD9.0

// ----------------------- Variable Globales ------------------------ //
int         catodo[10]  = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D,0x7D,0x07,0x7F,0x67 };
signed int  DC_range    = 0;       // Rango -115 : 115

// ----------------------------- Macros ----------------------------- //
#define set_dutycicle(DutyCicle) (DC_range =  115 - (((int16) DutyCicle) * 230 / 100))

// ---------------------------- Funciones --------------------------- //


// -------------------------- Interrupciones ------------------------ //
#int_TIMER0
void PWM(void)
{
    PWM1 ^= 1, PWM2 ^= 1;
    TMR0L   = 140;

    PWM1 ? (TMR0L += DC_range) : (TMR0L -= DC_range);
}

// ------------------------ Codigo Principal ----------------------- //
void main()
{
    // Configuracion de puertos I/O
    TRISA       = 0b00000011;
    TRISB       = 0b01000000;
    TRISD       = 0b00000000;
    
    PWM2        = 1;            // Para hacerlo complementario

    // Configuracion de TIMERS
    T0CON       = 0b11000010;

    // Activamos interrupciones
    INTCON      = 0b11100100;

    // Configuracion del ADC


    while (TRUE) 
    {
        
    }
}

/*
for(int i = 0; i < 4; i++)
{
    LATB |= ~(0b0001 << i);     // Desactivamos displays que no corresponden 
    LATB &= ~(0b0001 << i);     // Activamos display que corresponde
}
*/
