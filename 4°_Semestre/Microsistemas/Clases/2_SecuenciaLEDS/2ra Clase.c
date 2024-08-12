// Preprocesadores de Microcontrolador //
#include    <18f4550.h>                                        // Libreria del Microcontrolador
#fuses      INTRC, CPUDIV1, PLL1, NOWDT, NOPROTECT, NOLVP         // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 8M)                                  // Configuracion de frecuencia y delay

// Establecemos direccion de registros
#BYTE       TRISB = 0xF93           // Configurar Pines
#BYTE       LATB  = 0xF8A           // Output

#BYTE       TRISD = 0xF95
#BYTE       PORTD = 0xF83

void main()
{
    int secuencia = 0, leds = 0;
    
    TRISB = 0;                  // 0 Salida | 1 Entrada
    TRISD = 0b00001111;
   
    while (true)
    {   
        LATB = 0;

        // Establecemos nuevo valor de leds
        switch (secuencia)
        {
            case 1:
                leds != 0b11111111 ? (leds++) : (leds = 0b00000001);
            break;
            case 2:
                leds >= 0b00000001 ? (leds--) : (leds = 0b11111111);
            break;
            case 3:
                leds != 0b10000000 ? (leds <<= 1) : (leds = 0b00000001);
            break;
            case 4:
                leds != 0b00000001 ? (leds >>= 1) : (leds = 0b10000000);
            break;
        }
        
        // Reproducimos secuencia
        switch (PORTD)
        {
            case 1:
                secuencia = 1;
                leds = 0b00000001;
            break;
            case 2:
                secuencia = 2;
                leds = 0b11111111;
            break;
            case 4:
                secuencia = 3;
                leds = 0b00000001;
            break;
            case 8:
                secuencia = 4;
                leds = 0b10000000;
            break;
        }
        while(PORTD);

        // Ejecutamos secuencia
        LATB = leds;
        delay_ms(200);
    }
}


