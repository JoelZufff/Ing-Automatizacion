// --------------- Preprocesadores de microcontrolador -------------- //
#include    <18f4550.h>                                                 // Libreria del Microcontrolador
#fuses      INTRC, CPUDIV1, PLL1, NOWDT, NOPROTECT, NOLVP               // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 8M)                                           // Configuracion de frecuencia y delay

// --------------------- Direccion de registros --------------------- //  
const int16     *ADRES      = 0xFC3;
//#define         ADRES       (int16*) 0xFC3
#BYTE           ADCON0      = 0xFC2
#BIT            DONE        = 0xFC2.1
#BYTE           ADCON1      = 0xFC1
#BIT            VCFG1       = 0xFC1.5
#BIT            VCFG0       = 0xFC1.4
#BYTE           ADCON2      = 0xFC0

#BYTE           TRISA       = 0xF92
#BIT            PWM1        = 0xF89.4
#BIT            PWM2        = 0xF89.5

#BYTE           TRISB       = 0xF93
#BYTE           DISPLAY     = 0xF8A
#BIT            BUTTON      = 0xF81.4
#BIT            LED         = 0xF8A.5

#BYTE           TRISD       = 0xF95
#BYTE           DIGIT       = 0xF8C

#BYTE           INTCON      = 0xFF2

#BYTE           T0CON       = 0xFD5
#BYTE           TMR0L       = 0xFD6

// ---------------------- Variable Constantes ----------------------- //
const int       catodo[10]      = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67 };
signed int      DutyCicle       = 0;       // Rango -115 : 115

const int       min_distance = 10, max_distance = 32;
const long      bits_value[max_distance - min_distance + 1] = 
                {   
                    1020, 892, 762, 687, 605, 548, 488, 421, 406, 358,
                    315, 280, 250, 218, 196, 168, 141, 117, 102, 83,
                    73, 48, 42
                };

// ----------------------------- Macros ----------------------------- //
#define set_sharpsensor()           (ADCON0 &= 0b11000011, VCFG0 = VCFG1 = 1)           // Selecciono canal y activo vref
#define set_potenciometer()         (ADCON0 |= 0b00000100, VCFG0 = VCFG1 = 0)           // Selecciono canal y desactivo vref
#define get_adc()                   (DONE = 1, delay_us(10), *ADRES)                    // Solicito actualizacion y la registro

// ---------------------------- Funciones --------------------------- //
void    display_print( int actual, int next );
int     distance_interpolation( long actual_bits );
//void    display_print(float number);

// -------------------------- Interrupciones ------------------------ //
#int_TIMER0
void PWM(void)
{
    PWM1 ^= 1, PWM2 ^= 1;           // Aplicamos toggle a pines PWM
    TMR0L   = 140;                  // Es el valor para la frecuencia requerida

    TMR0L += PWM1 ? (DutyCicle) : (-DutyCicle);   // Si se requiere un duty_cicle
    
    // Agregamos o quitamos cuentas del timer a la parte positiva o negativa sin modificar el valor total de cuentas entre las 2 por lo que conservamos la frecuencia
}

// ------------------------ Codigo Principal ----------------------- //
void main()
{
    // Configuracion de puertos I/O
    TRISA       = 0b00001111;
    TRISB       = 0b00010000;
    TRISD       = 0b00000000;

    LED         = 0;
    PWM2        = 1;            // Para hacerlo complementario

    // Configuracion de TIMER 0
    T0CON       = 0b11000010;

    // Activamos interrupcion de TIMER 0
    INTCON      = 0b11100100;
    
    // Configuracion del ADC
    ADCON0      = 0b00000111;
    ADCON1      = 0b00001101;
    ADCON2      = 0b10000000;

    int         next_distance, actual_distance, target_distance = 10, data_index = 0;

    while (TRUE)
    {   
        //*/    DETECCION DE DISTANCIA REAL Y DISTANCIA PROXIMA
        set_potenciometer();
        next_distance =     get_adc() * (max_distance - min_distance - 7) / 1023 + min_distance;
        
        set_sharpsensor();
        actual_distance =   distance_interpolation(get_adc());

        // PROCESO DE ACOPLAMIENTO
        if(BUTTON)
        {
            while (BUTTON);
            target_distance = next_distance;    // Establecer distancia objetivo
        }      

        // Modulara el duty cicle en funcion de la diferencial de distancia
        if(actual_distance != target_distance)
        {
            DutyCicle   = ((signed int16) actual_distance - target_distance) * 40 / (max_distance - min_distance) + (actual_distance < target_distance ? -75 : 75);
            LED         = 1;
        }
        else    
            DutyCicle = LED = 0;

        // IMPRESION DE DISTANCIAS EN DISPLAYS
        display_print(actual_distance, next_distance);
        //*/

        /*/     Para obtener bits de calibracion
        long average = 0;
        
        for(int i = 0; i < 64; i++, delay_ms(31))     // Obtiene 10 valores del ADC
            average += get_adc();
        
        for(int i = 0; i < 50; i++)     // Obtiene 10 valores del ADC
            display_print(average / 64);    // Imprimimos el promedio
        //*/
    }
}

int distance_interpolation( long actual_bits )
{
    for(int cm = 0; cm < (max_distance - min_distance + 1); cm++) 
        if(actual_bits >= bits_value[cm])
            return cm + min_distance;
}

//*/
void display_print( int actual, int next )
{
    int numbers[4];
    numbers[0] = actual / 10,   numbers[1] = actual % 10;
    numbers[2] = next / 10,     numbers[3] = next % 10;

    for(int i = 0; i < 4; i++, delay_ms(5))
    {
        DISPLAY |= ~(0b00000001 << i) & 0b00001111;     // Desactivamos displays que no corresponden 
        DISPLAY &= ~(0b00000001 << i);                  // Activamos display que corresponde

        DIGIT = catodo[numbers[i]];
    }
}
//*/

/*/
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
        DISPLAY |= ~(0b00001000 >> i) & 0b00001111;     // Desactivamos displays que no corresponden 
        DISPLAY &= ~(0b00001000 >> i);                  // Activamos display que corresponde

        if(i == point && point > 0)
            DIGIT = catodo[integer % 10] | 0b10000000;
        else
            DIGIT = catodo[integer % 10];
    }
}
//*/