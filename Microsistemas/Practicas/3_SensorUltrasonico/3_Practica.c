// --------------- Preprocesadores de microcontrolador -------------- //
#include    <18f4550.h>                                                 // Libreria del Microcontrolador
#fuses      INTRC, CPUDIV1, PLL1, NOWDT, NOPROTECT, NOLVP, NOMCLR       // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 8M)                                           // Configuracion de frecuencia y delay
#use        rs232(rcv = pin_c7, xmit = pin_c6, baud = 9600, bits = 8, parity = n) 
// rs232(rcp = (Pin receptor), xmit = (pin transmisor), baud = (Velocidad de transferencia), bits = 8, parity = n)

// --------------------- Direccion de registros --------------------- //  
#BYTE       TRISB       = 0xF93
#BIT        ECHO        = 0xF81.0
#BIT        TRIGGER     = 0xF8A.1
#BIT        D1          = 0xF8A.2
#BIT        D2          = 0xF8A.3
#BIT        D3          = 0xF8A.4

#BYTE       TRISD       = 0xF95
#BYTE       DISPLAY     = 0xF8C

#BYTE       T0CON       = 0xFD5
#BYTE       TMR0H       = 0xFF7
#BYTE       TMR0L       = 0xFD6
#BIT        TMR0ON      = 0xFD5.7

#BYTE       INTCON      = 0xFF2
#BIT        TMR0IP      = 0xFF1.2

// ---------------------------- Funciones --------------------------- //
void display_print(float);

int     catodo[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D,0x7D,0x07,0x7F,0x67 };
float   distance = 0.0;

// ------------------------- Interrupciones ------------------------ //
#int_timer0
void get_distance()
{
    // Enviamos seÃ±al de inicio
    TRIGGER = 1;
    delay_us(10);
    TRIGGER = 0;

    // Reinicio y desactivacion TIMER 0
    TMR0ON = 0;
    TMR0L = TMR0H = 0;

    while(!ECHO);    // Final de señal Echo
    TMR0ON  = 1;    // Desactivo TIMER0
    while(ECHO);    // Final de señal Echo
    TMR0ON  = 0;    // Desactivo TIMER0

    printf("Timer 0 = %lu\r\n", get_timer0());
    
    // Reinicio y activacion TIMER 0
    TMR0L = TMR0H = 0;
    TMR0ON  = 1;
}

// ------------------------ Codigo Principal ----------------------- //
void main()
{
    // --------------------- Configuracion de puertos I/O --------------------- //
    TRISB       = 0b00000001;
    TRISD       = 0b00000000;

    // -------------------- Configuracion de Interrupciones ------------------- //
    INTCON      = 0b11100000;
    TMR0IP      = 1;
    // Interrupcion INT0, interrupcion timer0 y activamos flag de interrupcion timer 0

    // ----------------------- Configuracion de TIMER 0 ----------------------- //
    T0CON       = 0b10000000;
    // Inicializamos timer 0 a 16 bit

    // ---------------------------- Ciclo Infinito ---------------------------- //
    while(TRUE)
        display_print(distance);
}

void display_print(float number) // Tarda 15 ms
{ 
    if(number > 1000)   return;
    
    int16 integer;
    int n1, n2, n3;

    // --------------------- Descomponemos en 3 numeros --------------------- // 

    (number < 10) ? (integer = number * 100) : ((number < 100) ? (integer = number * 10) : ((number < 1000) ? (integer = number) : 0));
    // number < 10 ? Se pasan 2 decimales a parte entera | number < 100 ? Se pasa 1 decimal a parte entera | number < 1000 ? Se queda igual

    n3          = integer % 10;
    integer     /= 10;
    n2          = integer % 10;
    integer     /= 10;
    n1          = integer % 10;

    // ---- Los 3 numeros se distribuyen en el display con multiplexado ---- //
    
    // Encendemos primer display
    D2 = D3 = 1;
    D1 = 0;
    
    // Un digito y 2 decimales
    (number < 10) ? (DISPLAY = catodo[n1] | 0b10000000) : (DISPLAY = catodo[n1]);
    delay_ms(5);
    
    // Encendemos segundo display
    D1 = D3 = 1;
    D2 = 0;
    
    // 2 digitos y un decimal
    ((number < 100) && !(number < 10)) ? (DISPLAY = catodo[n2] | 0b10000000) : (DISPLAY = catodo[n2]);
    delay_ms(5);
    
    // Encendemos tercer display
    D1 = D2 = 1;
    D3 = 0;

    DISPLAY = catodo[n3];
    delay_ms(5);
}