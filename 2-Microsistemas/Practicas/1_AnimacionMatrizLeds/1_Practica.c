// Preprocesadores de Microcontrolador //
#include    <18f4550.h>                                        // Libreria del Microcontrolador
#fuses      INTRC, CPUDIV1, PLL1, NOWDT, NOPROTECT, NOLVP         // Fusibles (Configuraciones del microcontrolador)
#use        delay(clock = 8M)                                  // Configuracion de frecuencia y delay

// Establecemos direccion de registros
#BYTE       TRISA       = 0xF92
#BIT        PORTA0      = 0xF80.0

#BYTE       TRISB       = 0xF93
#BYTE       ROWS_LATB   = 0xF8A

#BYTE       TRISD       = 0xF95
#BYTE       COLS_LATD   = 0xF8C

#define total_time      20000

void walk_animation(long time);

// Fila 6 columna 3, 5

int frames[7][8] =
{
    {   
        0b00011000, 
        0b00111100, 
        0b00011000, 
        0b00111000, 
        0b01011000, 
        0b00101000, 
        0b01000100, 
        0b10001000  
    },

    {   
        0b00011000, 
        0b00111100, 
        0b00011000, 
        0b00111100, 
        0b01011100, 
        0b00011000, 
        0b00100100, 
        0b01001000
    },

    {   
        0b00011000, 
        0b00111100, 
        0b00011000, 
        0b00111100, 
        0b00111100, 
        0b00011000, 
        0b00011000, 
        0b00101000 
    },
    
    {   
        0b00011000, 
        0b00111100, 
        0b00011000, 
        0b00111100, 
        0b01011010, 
        0b00011000, 
        0b00011000, 
        0b00011000 
    },

    {   
        0b00011000, 
        0b00111100, 
        0b00011000, 
        0b00111100, 
        0b00111100, 
        0b00011000, 
        0b00011000, 
        0b00010100 
    },

    {   
        0b00011000, 
        0b00111100, 
        0b00011000, 
        0b00111100, 
        0b00111010, 
        0b00011000, 
        0b00100100, 
        0b00010010
    },

    {   0b00011000, 
        0b00111100, 
        0b00011000, 
        0b00011100, 
        0b00011010, 
        0b00010100, 
        0b00100010, 
        0b00010001  
    }
};

void main()
{
    TRISA = 0b11111111;                  // 0 Salida | 1 Entrada
    TRISB = 0;
    TRISD = 0;
    
    while (true)
    {    
        // Animacion estatica de STOP
        
        for(int i = 0, j = 0b00000001; i < 8; i++, j <<= 1) // Reproduccion de cada fila del frame // 8 ms
        {
            ROWS_LATB = 0b11111111 - j;                     // Activamos fila correspondiente
            COLS_LATD = frames[3][i];                       // Activamos columnas activas de esa fila
            delay_ms(1);
        }

        // Definir un tiempo y reproducir la animacion mas rapido mientras mas tiempo haya pasado
        signed long time = total_time;

        if(PORTA0)
            while(time > 0)
            {
                walk_animation(time / 8 + 200);
                time -= time / 8 + 200;
            }
    }
}

void walk_animation(long time)
{
    time = time/7/8;                                            // time / numero de frames / tiempo de cada frame
    
    for(int i = 0; i < 7; i++)                                  // Reproduccion de cada frame
        for(int j = 0; j < time; j++)                           // Repeticion del frame para cumplir tiempo
            for(int k = 0, l = 0b00000001; k < 8; k++, l <<= 1) // Reproduccion de cada fila del frame // 8 ms
            {
                ROWS_LATB = 0b11111111 - l;                     // Activamos fila correspondiente
                COLS_LATD = frames[i][k];                       // Activamos columnas activas de esa fila
                delay_ms(1);
            }
        
    COLS_LATD = 0;
}


