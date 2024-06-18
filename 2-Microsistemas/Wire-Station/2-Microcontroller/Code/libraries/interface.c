#include <string.h>
#include "SSD1306OLED.c"

#define Buzzer_PIN  PIN_A2  

// --------------------- Direccion de registros --------------------- //
#BYTE    TRISB             = 0xF93
#BYTE    INTCON            = 0xFF2
#BIT     INT1IE            = 0xFF0.3   // INTCON3
#BIT     INTEDG1           = 0xFF1.5   // INTCON2

// -------------------------- Estructuras --------------------------- //
typedef struct
{
   signed long long  Value;                   // Valor actual
   signed long long  MIN_Value;               // Valor minimo
   signed long long  MAX_Value;               // Valor maximo
} variable_t;

typedef struct
{
    long        DT_PIN;
    long        button_PIN;
    variable_t  *variable;      // Direccion de variable a modificar
    short       mode;           // TRUE: Giro Horario suma | FALSE: Giro Horario resta
    short       update;         // TRUE: Se actualizo valor | FALSE: No se actualizo valor
} encoder_t;

// ----------------------- Variables Globales ----------------------- //
encoder_t       encoder;

// -------------------------- Interrupciones ------------------------ //
#INT_EXT1
void encoder_signal()      // Recibimos flanco de bajada de encoder, comprobamos estado del otro pin para saber direccion de giro y modificamos variable de menu
{
    if(input(encoder.DT_PIN))     // Giro Horario
    {
        if(encoder.mode)
            encoder.variable->Value += (encoder.variable->Value == encoder.variable->MAX_Value) ? 0 : 1;
        else
            encoder.variable->Value -= (encoder.variable->Value == encoder.variable->MIN_Value) ? 0 : 1;
    }
    else           // Giro Antihorario
    {
        if(encoder.mode)
            encoder.variable->Value -= (encoder.variable->Value == encoder.variable->MIN_Value) ? 0 : 1;
        else
            encoder.variable->Value += (encoder.variable->Value == encoder.variable->MAX_Value) ? 0 : 1;
    }

    encoder.update = TRUE;
    delay_ms(30);
}

// ---------------------------- Funciones --------------------------- //
void interface_init()
{
    // Pantalla OLED
    SSD1306_Begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
    
    // Encoder
    encoder.mode         = TRUE;
    encoder.DT_PIN       = PIN_B3;
    encoder.button_PIN   = PIN_B4;
    encoder.update       = FALSE;
    
    // Configuracion de puertos I/O
    TRISB |= 0b00011010;

    // Configuracion de interrupcion
    INTCON   |= 110000000;
    INT1IE   = FALSE;    // Encoder esta desactivado hasta que se ocupa
    INTEDG1  = FALSE;    // Falling edge
}

//*/
short variable_set(variable_t *variable, char *name)
{
    // Para el nombre usare tamaño de letra 1, por lo que caben 21 caracteres.
    // Para los numeros usare tamaño de letra 3, por lo que caben 7 caracteres. 5 numeros MAX
   
    Value_set:

    variable_t exponent;
    exponent.MIN_Value = -1;    // Para que se pueda desbordar
    exponent.MAX_Value = exponent.Value = 0;
    // Agregar error si el exponente es mayor que 4

    // Creamos arreglo de numeros para descomponer la variable actual
    variable_t  numbers[5];
    // Descomponemos el numero en un arreglo, y contamos los exponentes de 10
    for( long long num = 1; num <= variable->MAX_Value && exponent.MAX_Value < 5; num *= 10, exponent.MAX_Value++)
    {
        numbers[exponent.MAX_Value].MAX_Value = 9; 
        numbers[exponent.MAX_Value].MIN_Value = 0; 
        numbers[exponent.MAX_Value].Value = (variable->Value / num) % 10;
    }
    // MAX_Value queda con un valor +1 mayor, que nos servira para desbordarnos y salir de la seleccion
    exponent.Value = exponent.MAX_Value - 1;

    // Imprimimos nombre centrado de variable a modificar
    SSD1306_ClearDisplay();
    SSD1306_DrawText( (SSD1306_LCDWIDTH - (strlen(name) * 6)) / 2, 0, name, 1);
    for(signed int exp = exponent.MAX_Value - 1, x = (SSD1306_LCDWIDTH - (exponent.MAX_Value * 17)) / 2; exp >= 0; exp--, x += 17)
       SSD1306_DrawChar(x, 22, numbers[exp].Value + 48, 3);
    char string[22];
    sprintf(string, "(%ld <-> %ld)\0", variable->MIN_Value, variable->MAX_Value);
    SSD1306_DrawText( (SSD1306_LCDWIDTH - (strlen(string) * 6)) / 2, 57, string, 1);
    
    // Activamos encoder
    INT1IE = TRUE;                      // Activamos interrupcion de encoder
    encoder.variable = &exponent;       // Apuntamos variable a modificar
    encoder.mode     = FALSE;

    // Variables para animacion de seleccion
    short       mode = TRUE;                // TRUE: Cambio de posicion | FALSE: Cambio de valor
    short       print_flag = TRUE;          // Bandera para ejecutar animacion
    short       Buzzer_flag = FALSE;
    int         Buzzer_time = 0;
    
    for(long time = 0; ((exponent.Value >= exponent.MIN_Value + 1) && (exponent.Value <= exponent.MAX_Value - 1)); (time < 65500) ? (time++) : (time = 0))
    {
        if(!input(encoder.button_PIN))     // Si detectamos presion de boton de cambio de estado
        {
            mode ^= TRUE;   // Cambiamos el modo
            encoder.mode = !mode;       // Cuando vamos en sentido horario en modo posicion, queremos que el horario reste

            time = 0;
            print_flag = FALSE;     // Para mostrar modo seleccionado
            
            Buzzer_time = 0, Buzzer_flag = TRUE;        // Activamos sonido de buzzer

            // Actualizamos variable a modificar en funcion del modo
            encoder.variable = mode ? &exponent : &numbers[exponent.Value];  

            while(!input(encoder.button_PIN));
        }

        if(Buzzer_flag)
        {
            if(Buzzer_time < 25)
            {
                output_high(Buzzer_PIN);
                Buzzer_time++;
            }
            else
            {
                output_low(Buzzer_PIN);
                Buzzer_flag = FALSE;
            }
        }

        if(encoder.update)                  // Se recibio un cambio de valor
        {
            // Reiniciamos animacion
            time = 0;
            print_flag = !mode;

            for(signed int exp = exponent.MAX_Value - 1, x = (SSD1306_LCDWIDTH - (exponent.MAX_Value * 17)) / 2; exp >= 0; exp--, x += 17)
                    SSD1306_DrawChar(x, 22, numbers[exp].Value + 48, 3);

            Buzzer_time = 0, Buzzer_flag = TRUE;        // Activamos sonido de buzzer

            encoder.update = FALSE;
        }

        if(!(time % 500))                   // Cada 200 ms ejecutamos animacion
        {
            int x = ((SSD1306_LCDWIDTH - (exponent.MAX_Value * 17)) / 2) + (17 * ((exponent.MAX_Value - 1) - exponent.Value));
            
            if(print_flag)
                SSD1306_DrawChar(x, 22, numbers[exponent.Value].Value + 48, 3);
            else
            {
                SSD1306_FillRect(x, 22, 17, 21, FALSE);

                if(mode)        // Si esta en modo posicion
                    SSD1306_DrawChar(x, 22, '-', 3);
                else            // Si esta en modo valor
                    SSD1306_DrawChar(x, 22, '_', 3);
            }

            SSD1306_Display();
            print_flag ^= TRUE;
        }

        delay_ms(1);
    }

    INT1IE = FALSE;                     // Desactivamos interrupcion de encoder

    output_low(Buzzer_PIN);

    // Revisamos si el numero ingresado es valido

    signed long long value = 0, exp_num = 1;
    for(int exp = 0; exp < exponent.MAX_Value; exp_num*=10, exp++)
        value += numbers[exp].Value * exp_num;

    if(value > variable->MAX_Value || value < variable->MIN_Value)  // Numero invalido
    {
        SSD1306_ClearDisplay();
        SSD1306_DrawText( (SSD1306_LCDWIDTH - (strlen("NUMERO\0") * 12)) / 2, 14, "NUMERO\0", 2);
        SSD1306_DrawText( (SSD1306_LCDWIDTH - (strlen("INVALIDO\0") * 12)) / 2, 34, "INVALIDO\0", 2);
        SSD1306_Display();
        delay_ms(1000);
        
        goto Value_set;
    }

    // Si es valido, lo guardamos y 
    variable->Value = value;

    if (exponent.Value == exponent.MAX_Value ) // Se desbordo por la derecha AVANZAR
        return TRUE;
    else if(exponent.Value == exponent.MIN_Value)    // Se desbordo por la izquierda VOLVER
        return FALSE;
}
//*/
short order_resume(signed long long length, signed long long amount)
{
    char string[22];

    SSD1306_ClearDisplay();
    SSD1306_DrawText( (SSD1306_LCDWIDTH - (strlen("ORDEN\0") * 12)) / 2, 4, "ORDEN\0", 2);
    
    sprintf(string, "Longitud: %ld mm\0", length);
    SSD1306_DrawText( (SSD1306_LCDWIDTH - (strlen(string) * 6)) / 2, 26, string, 1);
    
    sprintf(string, "Cantidad: %ld\0", amount);
    SSD1306_DrawText( (SSD1306_LCDWIDTH - (strlen(string) * 6)) / 2, 42, string, 1);

    SSD1306_Display();
    
    variable_t position = { 1, 0, 1};
    
    INT1IE = TRUE;                      // Activamos interrupcion de encoder
    encoder.variable = &position;       // Apuntamos variable a modificar
    encoder.mode     = TRUE;            // Sentido horario
    short print_flag = TRUE;

    for(long time = 0; position.Value == 1; (time < 65500) ? (time++) : (time = 0), delay_ms(1))
    {
        if(!(time % 500)) // Cada 200 ms
        {
            int x = (SSD1306_LCDWIDTH - (strlen("Presione el boton\0") * 6)) / 2;
            if(print_flag)
                SSD1306_DrawText( x, 57, "Presione el boton\0", 1);
            else
                SSD1306_FillRect( x, 57, strlen("Presione el boton\0") * 6, 8, FALSE);
            
            SSD1306_Display();

            print_flag = !print_flag;
        }
        
        if(!input(encoder.button_PIN))
        {
            INT1IE = FALSE;
            while(!input(encoder.button_PIN));

            return FALSE;        // Continuar con la impresion
        }
    }

    INT1IE = FALSE;
    return TRUE;       // Volver al menu anterior
}