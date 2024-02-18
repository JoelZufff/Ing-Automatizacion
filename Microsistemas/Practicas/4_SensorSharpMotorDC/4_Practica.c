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
#BIT            VCFG1       = 0xFC1.5
#BIT            VCFG0       = 0xFC1.4
#BYTE           ADCON2      = 0xFC0

#BYTE           TRISB       = 0xF93
#BYTE           LATB        = 0xF8A
#BIT            PWM1        = 0xF8A.4
#BIT            PWM2        = 0xF8A.5
#BIT            BUTTON      = 0xF81.6

#BYTE           TRISD       = 0xF95
#BYTE           DISPLAY     = 0xF8C

#BYTE           INTCON      = 0xFF2

#BYTE           T0CON       = 0xFD5
#BYTE           TMR0L       = 0xFD6


// ----------------------- Variable Globales ------------------------ //
int         catodo[10]      = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D,0x7D,0x07,0x7F,0x67 };
signed int  DC_range        = 0;       // Rango -115 : 115
int         actual_distance = 0;
int         next_distance   = 0;

// ----------------------------- Macros ----------------------------- //
#define dutycicle(DutyCicle)    (DC_range =  115 - (((int16) DutyCicle) * 230 / 100))
#define set_sharpsensor()       (ADCON0 &= 0b11000011, VCFG0 = VCFG1 = 1)           // Selecciono canal y activo vref
#define set_potenciometer()     (ADCON0 |= 0b00000100 , VCFG0 = VCFG1 = 0)          // Selecciono canal y desactivo vref

// ---------------------------- Funciones --------------------------- //
long get_adc() { long data = *ADRES; DONE = 1; delay_us(5); return data; }
void display_print(float number);


// -------------------------- Interrupciones ------------------------ //
#int_TIMER0
void PWM(void)
{
    PWM1 ^= 1, PWM2 ^= 1;           // Aplicamos toggle a pines PWM
    TMR0L   = 140;                  // Es el valor para la frecuencia requerida

    PWM1 ? (TMR0L += DC_range) : (TMR0L -= DC_range);   // Si se requiere un duty_cicle
}

// ------------------------ Codigo Principal ----------------------- //
void main()
{
    // Configuracion de puertos I/O
    TRISA       = 0b00000011;
    TRISB       = 0b01000000;
    TRISD       = 0b00000000;
    PWM2        = 1;            // Para hacerlo complementario

    // Configuracion del ADC
    ADCON0      = 0b00000111;
    ADCON1      = 0b00001101;
    ADCON2      = 0b10000000;

    // Configuracion de TIMER 0
    T0CON       = 0b11000010;

    // Activamos interrupcion de TIMER 0
    INTCON      = 0b11100100;

    while (TRUE) 
    {
        // En ciclo infinito calcular las 2 distancias y mostrarlas en display
        // Si se presiona boton de acoplamiento activar flag para activar el movimiento del motor
    }
}

void display_print(float number) // Tarda 15 ms
{ 
    int16   integer;
    int     point;

    // Convertir el número a un entero y establecer la posición del punto decimal
    if (number < 10)
        integer = number * 1000, point = 3;
    else if (number < 100)
        integer = number * 100, point = 2;
    else if (number < 1000)
        integer = number * 10, point = 1;
    else
        integer = number, point = 0;

    // Imprimir numeros en digitos del display con multiplexado
    for(int i = 0; i < 4; i++, integer /= 10, delay_ms(5))
    {
        LATB |= ~(0b1000 >> i);     // Desactivamos displays que no corresponden 
        LATB &= ~(0b1000 >> i);     // Activamos display que corresponde

        if(i == point && point > 0)
            DISPLAY = catodo[integer % 10] | 0b10000000;
        else
            DISPLAY = catodo[integer % 10];
    }
}

// Calcular distancia actual y distancia de potenciometro y mostrarlo en pantalla
// Al detectar boton ocurrira el acoplamiento hasta que las 2 distancias sean iguales