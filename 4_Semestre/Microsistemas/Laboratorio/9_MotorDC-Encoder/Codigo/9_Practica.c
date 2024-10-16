// --------------- Preprocesadores de microcontrolador -------------- //
#include    <18f4550.h>                                                 // Libreria del Microcontrolador
#fuses      INTRC, CPUDIV1, PLL1, NOWDT, NOPROTECT, NOLVP, NOMCLR       // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 8M)                                           // Configuracion de frecuencia y delay

#define LCD_ENABLE_PIN  PIN_D2
#define LCD_RS_PIN      PIN_D3
#define LCD_RW_PIN      PIN_D4
#define LCD_DATA4       PIN_B4
#define LCD_DATA5       PIN_B5
#define LCD_DATA6       PIN_B6
#define LCD_DATA7       PIN_B7

#include  "lcd.c"

// --------------------- Direccion de registros --------------------- //
#BYTE       TRISA       = 0xF92
#BYTE       TRISB       = 0xF93
#BYTE       TRISC       = 0xF94
#BYTE       TRISD       = 0xF95
#BIT        CH_A        = 0xF81.0   // PORTB
#BIT        CH_B        = 0xF81.1   // PORTB

const int16 *ADRES      = 0xFC3;
#BYTE       ADCON0      = 0xFC2
#BYTE       ADCON1      = 0xFC1
#BYTE       ADCON2      = 0xFC0
#BIT        DONE        = 0xFC2.1

#BYTE       INTCON      = 0xFF2
#BIT        INT0IE      = 0xFF2.4   // INTCON
#BIT        INTEDG0     = 0xFF1.6   // INTCON2

#BYTE       CCP1L       = 0xFBE
#BYTE       CCP1CON     = 0xFBD
#BYTE       T2CON       = 0xFCA
#BYTE       PR2         = 0xFCB


// ----------------------------- Macros ---------------------------- //
#define get_adc()       (DONE = 1, delay_us(10), *ADRES)        // Solicito actualizacion y la registro
#define max_duty_cicle  500
#define resolution      1200     // Pulsos por revolucion

// ----------------------- Variable Globales ------------------------ //
int32   pulsos = 0;

char    right[] = "Derecha ->\0";
char    left[] = "Izquierda <-\0";
char    *direction = left;

// -------------------------- Interrupciones ------------------------ //
#INT_EXT
void signal()
{
    pulsos++;

    if(CH_A)      // Flanco de subida
    {
        INTEDG0 = FALSE;     // Detectamos flanco de bajada
        if(CH_B)
            direction = right;
    }
    else
    {
        INTEDG0 = TRUE;     // Detectamos flanco de subida
        if(CH_B)
            direction = left;
    }
}

// ------------------------ Codigo Principal ----------------------- //
void main()
{
    // Configuracion de puertos IO
    TRISA   = 0b00000001;
    TRISB   = 0b00000011;
    TRISC   = 0b00000000;
    TRISD   = 0b00000000;
    
    // Configuracion ADC
    ADCON0  = 0b00000011;
    ADCON1  = 0b00001110;
    ADCON2  = 0b10000000;

    // Configuacion PWM
    T2CON   = 0b00000111;   // Preescaler 16, ON
    PR2     = 124;          // 1000 Hz
    CCP1CON = 0b10001100;   // Half Bridge

    // Configuracion de interrupciones
    INTCON  = 0b11010000;       // Activamos las interrupciones
    INT0IE = INTEDG0 = TRUE;    // Activamos interrupciones externas 0 y lo colocamos en flanco de subida

    lcd_init();

    output_high(PIN_A1);

    for(long time = 0; TRUE; time++, delay_ms(1))
    {
        // Configuramos PWM en funcion de potenciometro
        long CCP1 = ((get_adc() / 1023.0) * max_duty_cicle); 
        CCP1L = CCP1 >> 2;

        // Actualizamos valor de RPM en funcion de pulsos detectados
        if(time == 1000)
        {
            long RPM = pulsos * 60 / resolution;
            pulsos = 0;

            printf(lcd_putc, "\fRPM = %lu\n", RPM);
            printf(lcd_putc, direction);

            time = 0;
        }
    }
}