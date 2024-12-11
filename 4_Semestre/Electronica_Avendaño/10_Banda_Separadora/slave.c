// --------------- Preprocesadores de microcontrolador -------------- //
#include  <18F4550.h>
#fuses    NOWDT, NOPROTECT, NOLVP, NOMCLR
#use      delay(internal = 500Khz)
#use      rs232(rcv = pin_c7, xmit = pin_c6, baud = 9600, bits = 8, parity = n)

#define     MAX_PWM     625

// ----------------------- Variable Globales ------------------------ //
#define Clicker_X PIN_D0
#define Clicker_Y PIN_D1

#define BLACK         0
#define RED           1
#define GREEN         2
#define BLUE          3

int     color;
int1    movement = FALSE;

const long  torreta_pins[3]   = { PIN_D4, PIN_D5, PIN_D6 };
int1        torreta_state[3]  = { FALSE, FALSE, FALSE };

// -------------------------- Interrupciones ------------------------ //
#INT_RDA
void receive()
{
    
    char data = getc();

    if(data == '*')     // Recibimos un color y activamos movimiento
        color = getch() - 48, movement = TRUE;        
}

// ---------------------------- Funciones -------------------------- //
// brazo: 0b00000011, vertical: 0b00001100, lateral1: 0b00110000, brazovertical: 0b11000000
void colocar_tapa()
{
    //*/
    // Etapa de movimiento //
    torreta_state[1] = TRUE, torreta_state[0] = torreta_state[2] = FALSE;
    
    // Actualizamos estado de torreta
    for(int i = 0; i < 3; i++)
        output_bit(torreta_pins[i], torreta_state[i]);
    
    long time;
    switch (color)
    {
        case GREEN:
            time = 0;
        break;
        case BLACK:
            time = 400;
        break;
        case RED:
            time = 900;
        break;
        case BLUE:
            time = 1600;
        break;
        default: return; break;
    }
    
    // Empujar tapa con servo
    set_pwm1_duty(MAX_PWM * 1 / 100);
    delay_ms(210);
    set_pwm1_duty(MAX_PWM * 8 / 100);

    // Tiempo para que la tapa llegue a su destino
    delay_ms(9500);
    
    // Etapa de colocacion //
    torreta_state[2] = TRUE, torreta_state[0] = torreta_state[1] = FALSE;

    // Actualizamos estado de torreta
    for(int i = 0; i < 3; i++)
        output_bit(torreta_pins[i], torreta_state[i]);

    output_b(0b10000000); // Sube muñeca
    delay_ms(1000);

    output_b(0b00010000); // Se aleja
    delay_ms(1000);

    output_b(0b00010000); // Se aleja a contenedor va en funcion del color
    delay_ms(time);

    output_b(0b01000000); // Baja muñeca
    delay_ms(1400);

    output_b(0b10000000); // Sube muñeca
    delay_ms(1500);

    /*
    // Ejecutamos secuencia para colocar la tapa con brazo
    output_b(0b00000001); // Cierra mano
    delay_ms(330);
      
    output_b(0b00000100); // Se levanta
    delay_ms(2750);
    
    output_b(0b00010000); // Se aleja
    delay_ms(1000);

    output_b(0b00010000); // Se aleja a contenedor va en funcion del color
    delay_ms(time);
    
    output_b(0b00001000);   // Abajo   
    delay_ms(900);
    
    output_b(0b00000010); // Abre mano
    delay_ms(300);

    output_b(0b10000000); // Baja muñeca
    delay_ms(1000);

    output_b(0b01000000); // Sube muñeca
    delay_ms(1130);
    
    output_b(0b00000100);   // Arriba
    delay_ms(950);
    */
    
    // Etapa de escaneo //
    putc('#');      // Activamos proceso de escaneo
    torreta_state[0] = TRUE, torreta_state[1] = torreta_state[2] = FALSE;
    
    // Actualizamos estado de torreta
    for(int i = 0; i < 3; i++)
        output_bit(torreta_pins[i], torreta_state[i]);

    //*/
}

// ------------------------ Codigo Principal ----------------------- //
void main()
{
    enable_interrupts(INT_RDA);
    enable_interrupts(GLOBAL);
    
    // Configuramos PWM de servo
    setup_timer_2( T2_DIV_BY_16, 155, 1 );
    setup_ccp1(CCP_PWM);
    set_pwm1_duty(MAX_PWM * 8 / 100);

    // Actualizamos estado de torreta
    for(int i = 0; i < 3; i++)
        output_bit(torreta_pins[i], torreta_state[i]);

    while (TRUE)
    {   
        /*/
        while(input(Clicker_X))
            output_b(0b00010000);   // Alejar
        
        while(input(Clicker_Y))
            output_b(0b00000100);   // Arriba   
        /*/
        //output_b(0b00000100);   // Arriba
        //output_b(0b10000000); // Arriba muñeca

        //*/
        // Posicionamos la garra en la posicion inicial
        while(!input(Clicker_X))
            output_b(0b00100000);   // Acercar
        while(!input(Clicker_Y))            
            output_b(0b01000000); // Baja muñeca
            //output_b(0b00001000);   // Abajo
        output_b(0);   
        //*/
        
        if(movement)
        {
            movement = FALSE;
            colocar_tapa();
        }
    }
}