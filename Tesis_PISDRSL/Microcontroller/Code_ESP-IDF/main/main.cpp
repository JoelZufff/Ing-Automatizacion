// CODIGO PARA GENERAR UNA SEÑAL PWM EN ESP32 CON MCPWM

// ======================== Preprocesadores ========================= //
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#include "esp_timer.h"
#include "driver/mcpwm_prelude.h"
#include "driver/pulse_cnt.h"

// =========================== Constantes =========================== //
static const char *TAG = "Main";

#define FORWARD           1           // Direccion de movimiento del motor
#define BACKWARD          0           // Direccion de movimiento del motor

#define MAX_DUTY_CYCLE     1000        // 1000 ticks para el ciclo de trabajo, 10 MHz/1000 = 10 KHz Timer

// ============================= Clases ============================= //
// Hacer una clase que se llama puente H, se creara la clase motor que tendra la clase encoder en su interior

class L298N_t
{
    // CLASES //
    class DC_motor_t
    {
        friend class L298N_t; // Para acceder a los campos privados de la clase L298N_t

        // CLASES //
        class encoder_t
        {
            // CAMPOS //
            private:
            pcnt_unit_handle_t pcnt_unit;
            
            public: 
            // METODOS //
            encoder_t() {}

            void init(gpio_num_t FaseA_pin, gpio_num_t FaseB_pin)
            {
                // Configurar unidad de conteo con límites (opcional)
                pcnt_unit_config_t unit_config =
                {
                    .low_limit = -32768,
                    .high_limit = 32767,
                    .intr_priority = 0,
                };
                ESP_ERROR_CHECK(pcnt_new_unit(&unit_config, &pcnt_unit));

                pcnt_chan_config_t chan_config = 
                {
                    .edge_gpio_num = FaseA_pin, 
                    .level_gpio_num = FaseB_pin, // Señal B como nivel
                    .flags = 
                    {
                        .invert_edge_input = 0,
                        .invert_level_input = 0
                    },
                };
                pcnt_channel_handle_t chan;
                ESP_ERROR_CHECK(pcnt_new_channel(pcnt_unit, &chan_config, &chan));

                // Configuramos la unidad de conteo para que aumente el contador con flancos de subida
                ESP_ERROR_CHECK(pcnt_channel_set_edge_action(chan, PCNT_CHANNEL_EDGE_ACTION_INCREASE, PCNT_CHANNEL_EDGE_ACTION_HOLD));

                // Configuramos la accion del level_gpio_num para que modifique la direccion de giro cuando hay un desfase entre las señales A y B (PENDIENTE CONFIGURAR)
                ESP_ERROR_CHECK(pcnt_channel_set_level_action(chan, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));

                // Cofiguramos el filtro de ruido para la señal de conteo (PENDIENTE CALIBRAR EN FUNCION DE VELOCIDAD MAXIMA DE MOTOR)
                pcnt_glitch_filter_config_t filter_config = { .max_glitch_ns = 1000, };
                ESP_ERROR_CHECK(pcnt_unit_set_glitch_filter(pcnt_unit, &filter_config)); // Configuramos el filtro de ruido
            }

            // Hacer funciones para leer valor de encoder
        };
        
        public:
        encoder_t Encoder;         // Encoder del motor
        
        // CAMPOS //
        private:
        gpio_num_t IN1_pin;
        gpio_num_t IN2_pin;
        
        // Variables para generacion de PWM
        mcpwm_oper_handle_t *op;            // Operador para el timer
        mcpwm_cmpr_handle_t comp;           // Comparador para el operador
        mcpwm_gen_handle_t gen;             // Generador para el operador

        public:
        // METODOS //
        DC_motor_t() {}
        
        void init(gpio_num_t EN_pin, gpio_num_t IN1_pin, gpio_num_t IN2_pin)
        {
            // Configuramos los pines de direccion del motor //
            this->IN1_pin = IN1_pin;
            this->IN2_pin = IN2_pin;

            // Establecemos IN1_pin como salida y valor 0
            gpio_reset_pin(IN1_pin);
            gpio_set_direction(IN1_pin, GPIO_MODE_OUTPUT);   // Configuramos el pin como salida
            gpio_set_level(IN1_pin, 0);

            // Establecemos IN2_pin como salida y valor 0
            gpio_reset_pin(IN2_pin);
            gpio_set_direction(IN2_pin, GPIO_MODE_OUTPUT);   // Configuramos el pin como salida
            gpio_set_level(IN2_pin, 0);

            // Inicializamos el PWM en EN_pin //
            // Creacion de comparadores, para definir el punto de cambio (duty cycle) de la señal PWM. //
            mcpwm_comparator_config_t compare_config;
            compare_config.flags.update_cmp_on_tez = true;
            compare_config.intr_priority = 0;
            ESP_ERROR_CHECK(mcpwm_new_comparator(*op, &compare_config, &comp));
            ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comp, 0));       // 0% duty cycle

            // Creacion de generador, para generar la señal PWM en el pin seleccionado //
            mcpwm_generator_config_t gen_config; 
            gen_config.gen_gpio_num = EN_pin;         // GPIO para la señal PWM
            ESP_ERROR_CHECK(mcpwm_new_generator(*op, &gen_config, &gen));

            // Configuracion de la señal PWM //
            ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(gen,MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)));
            ESP_ERROR_CHECK(mcpwm_generator_set_actions_on_compare_event(gen,MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, comp, MCPWM_GEN_ACTION_LOW)));

        }

        void set_movement(uint16_t duty_cycle, bool direction)
        {
            // Establecemos la direccion de movimiento del motor //
            gpio_set_level(IN1_pin, !direction); // Establecemos IN1_pin en alto
            gpio_set_level(IN2_pin, direction);  // Establecemos IN2_pin en bajo

            // Establecemos el duty cycle del PWM //
            ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comp, duty_cycle)); // Establecemos el duty cycle del PWM
        }
    };

    // CAMPOS //
    public:
    DC_motor_t LeftMotor, RigthMotor;   // Motores DC
    
    // Timer y operador, para las 2 señales PWM con misma frecuencia pero duty cycle diferente //
    private:
    mcpwm_timer_handle_t tmr;           // Timer para el PWM
    mcpwm_oper_handle_t op;             // Operador para el timer

    public:
    // METODOS //
    L298N_t()                           // Constructor vacio
    {
        // Configuramos timer y operador de las señales PWM de los 2 motores //
        mcpwm_timer_config_t timer_config = 
        {
            .group_id = 0,
            .clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT,         // PLL Clock 240 MHz
            .resolution_hz = 10000000,                      // 10 MHz Prescaler, 0.1us/ticks
            .count_mode = MCPWM_TIMER_COUNT_MODE_UP,
            .period_ticks = MAX_DUTY_CYCLE,                 // 1000 ticks for 1 cycle, 10 MHz/1000 = 10 KHz Timer
            .intr_priority = 0,                             // Low priority
        };
        ESP_ERROR_CHECK(mcpwm_new_timer(&timer_config, &tmr));
        
        ESP_ERROR_CHECK(mcpwm_timer_enable(tmr));
        ESP_ERROR_CHECK(mcpwm_timer_start_stop(tmr, MCPWM_TIMER_START_NO_STOP));

        // Creacion de operador, para coordinar los comparadores y generadores con el timer //
        mcpwm_operator_config_t operator_config = { .group_id = 0, };
        ESP_ERROR_CHECK(mcpwm_new_operator(&operator_config, &op));
        ESP_ERROR_CHECK(mcpwm_operator_connect_timer(op, tmr));

        LeftMotor.op = &op;         // Asignamos el operador al motor izquierdo
        RigthMotor.op = &op;        // Asignamos el operador al motor derecho
    }
};

class MPU6050_t
{
    // CAMPOS
    public:

    MPU6050_t() {}

    void init(gpio_num_t SDA_pin, gpio_num_t SCL_pin)
    {
        
    }
};

// ======================= Variables Globales ======================= //
L298N_t L298N;

// ========================= Interrupciones ========================= //

// =========================== Funciones ============================ //

// ======================== Codigo Principal ======================== //
extern "C" void app_main(void)
{   
    // Inicializamos motor izquierdo
    L298N.LeftMotor.init(GPIO_NUM_14, GPIO_NUM_5, GPIO_NUM_4);
    L298N.LeftMotor.Encoder.init(GPIO_NUM_19, GPIO_NUM_18);       // Inicializamos el encoder

    // Inicializamos motor derecho
    L298N.RigthMotor.init(GPIO_NUM_27, GPIO_NUM_2, GPIO_NUM_15);
    L298N.RigthMotor.Encoder.init(GPIO_NUM_33, GPIO_NUM_32);      // Inicializamos el encoder

    // Falta comunicacion Bluetooth con la interfaz
    // Falta comunicacion i2c con MPU6050
    // Falta inicializacion de sensores TCRT5000

    while (true)
    {
        //*/
        for(uint16_t i = 0; i < MAX_DUTY_CYCLE; i++)
        {
            L298N.LeftMotor.set_movement(i, FORWARD);  // Establecemos el movimiento del motor izquierdo
            L298N.RigthMotor.set_movement(i, FORWARD); // Establecemos el movimiento del motor derecho

            vTaskDelay(pdMS_TO_TICKS(10));
        }
        //*/
    }    
}