// Preprocesadores de Microcontrolador //
#include    <18f4550.h>                                                 // Libreria del Microcontrolador
#fuses      INTRC, CPUDIV1, PLL1, NOWDT, NOPROTECT, NOLVP, NOMCLR       // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 8M)                                           // Configuracion de frecuencia y delay
//#use        rs232(rcv = pin_c7, xmit = pin_c6, baud = 9600, bits = 8, parity = n)

// Establecemos direccion de registros
#BYTE       TRISD       = 0xF95
#BYTE       LATD        = 0xF8C

#BYTE       TRISB       = 0xF93

#BYTE       INTCON      = 0xFF2

// Arreglos de letras para impresion
int hearth[8] = { 0b00001110, 0b00111111, 0b01111111, 0b11111110, 0b11111110, 0b01111111, 0b00111111, 0b00001110 };

void animation();

int16       timer = 0, period = 0;
int1        flag = FALSE;

#int_ext
void LEDS()
{
    period          = timer;
    timer           = 0;

    flag            = TRUE;
}


void main()
{   
    // Configuracion de puertos I/O
    TRISB = 0b00000001;                 // 0 Salida | 1 Entrada
    TRISD = 0b00000000;                 // 0 Salida | 1 Entrada

    // Configuracion de Interrupciones
    INTCON = 0b11010000;

    while(TRUE)
    {   
        if(flag)
            animation();
        else
        {
            delay_ms(1);
            timer++;
        }
    }
}

void animation()
{
    flag = FALSE;
    
    for(int frame = 0; frame < 8 && !flag; frame++)                          // Reproduccion del caracter por frames
        for(int ms = 0; ms < (period / 12 / 8) && !flag; ms++, timer++)
        {
            LATD = hearth[frame];
            delay_ms(1);
        }

    LATD = 0;
}

// Maximo 16 caracteres

// La cantidad de LEDS en encendidos es la altura de la figura
// Tiempo encendido del LED se traduce como la anchura de la figura
// Dependiendo la velocidad del ventilador un mismo periodo se puede traducir como mas o menos anchura de la figura
// Lo que debe variar es el periodo de vuelta pero la anchura de las figuras debe de ser constante

// Vamos a colocar el iman mirando hacia nosotros pues el el punto de inicio de la imagen
