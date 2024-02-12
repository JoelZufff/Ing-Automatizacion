// Preprocesadores de Microcontrolador //
#include    <18f4550.h>                                        // Libreria del Microcontrolador
#fuses      INTRC, NOWDT, NOPROTECT, NOLVP, CPUDIV1, PLL1      // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 8M)                                  // Configuracion de delay

// Establecemos direccion de registros
#BYTE       TRISB = 0xF93
#BYTE       PORTB = 0xF81
#BYTE       LATB  = 0xF8A

// Un microcontrolador de 8 bits, realiza una operacion de 8 bits en un ciclo de reloj

// Menor consumo de compuertas logicas -> menor latencia
// 1 / (8 Mhz) = 125 ns cada ciclo de trabajo

void main()
{
    // EJEMPLO CON REGISTROS
    TRISB = 0;                  // Establecemos pines del puerto B como salida
   
    while (true)                // 2 us | 16 ciclos de reloj
    {
        LATB = 0b00000001;      // output_high | 0.5 us | 4 Ciclos de reloj
        LATB = 0;               // output_low  | 0.5 us | 4 Ciclos de reloj
    }
    
    /* EJEMPLO CON FUNCIONES DE PIC C
    while(true)                  // 1.5 us | 12 Ciclos de reloj
    {
        output_high(PIN_B0);     // 1 us | 8 Ciclos de reloj
        output_low(PIN_B0);      // 1 us | 8 Ciclos de reloj
    }*/

    // Con registros la instruccion ocupa la mitad de ciclos de reloj
}


