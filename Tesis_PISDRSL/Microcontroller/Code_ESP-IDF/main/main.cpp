// CODIGO PARA GENERAR UNA SEÑAL PWM EN ESP32 CON MCPWM

// ======================== Preprocesadores ========================= //
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#include "driver/mcpwm_prelude.h"

// =========================== Constantes =========================== //
static const char *TAG = "Main";

#define MAX_DUTY_CYCLE     1000        // 1000 ticks para el ciclo de trabajo, 10 MHz/1000 = 10 KHz Timer

// ============================= Clases ============================= //
class DC_motor_t            // Clase para un motor DC con encoder
{
    //*/
    // CLASES //
    class encoder_t
    {
        // CAMPOS //
            
        public: 
        // METODOS //
        encoder_t(uint8_t FaseA_pin, uint8_t FaseB_pin)         // Constructor
        {
            // Configurar lectura de encoder
        }
    };
    //*/

    class HBridge_t
    {
        // CAMPOS //
        public:         
        private:
        // Variables para generacion de PWM
        static mcpwm_timer_handle_t tmr;            // Timer para el PWM
        static mcpwm_oper_handle_t op;              // Operador para el timer
        mcpwm_cmpr_handle_t comp;                   // Comparador para el operador
        mcpwm_gen_handle_t gen;                     // Generador para el operador

        // METODOS //
        public: 
        HBridge_t(uint8_t EN_pin, uint8_t IN1_pin, uint8_t IN2_pin)         // Constructor
        {            
            if(tmr == nullptr)
            {
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
            }

            if(op == nullptr)
            {
                // Creacion de operador, para coordinar los comparadores y generadores con el timer //
                mcpwm_operator_config_t operator_config = { .group_id = 0, };
                ESP_ERROR_CHECK(mcpwm_new_operator(&operator_config, &op));
                ESP_ERROR_CHECK(mcpwm_operator_connect_timer(op, tmr));
            }

            // Creacion de comparadores, para definir el punto de cambio (duty cycle) de la señal PWM. //
            mcpwm_comparator_config_t compare_config;
            compare_config.flags.update_cmp_on_tez = true;
            compare_config.intr_priority = 0;
            ESP_ERROR_CHECK(mcpwm_new_comparator(op, &compare_config, &comp));
            ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comp, 0));       // 0% duty cycle

            // Creacion de generador, para generar la señal PWM en el pin seleccionado //
            mcpwm_generator_config_t gen_config; 
            gen_config.gen_gpio_num = EN_pin;         // GPIO para la señal PWM
            ESP_ERROR_CHECK(mcpwm_new_generator(op, &gen_config, &gen));

            // Configuracion de la señal PWM //
            ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(gen,MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)));
            ESP_ERROR_CHECK(mcpwm_generator_set_actions_on_compare_event(gen,MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, comp, MCPWM_GEN_ACTION_LOW)));
        }

        void set_dutycicle(uint16_t duty_cycle)     // Recibe un valor entre 0 y 1000 y actualiza el duty cycle del PWM
        {
            ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comp, duty_cycle)); 
        }
    };

    // CAMPOS //
    public:
    HBridge_t H_bridge;       // PWM para el motor
    encoder_t Encoder;      // Encoder para el motor

    // METODOS //
    DC_motor_t(uint8_t EN_pin, uint8_t IN1_pin, uint8_t IN2_pin, uint8_t FaseA_pin, uint8_t FaseB_pin) : H_bridge(EN_pin, IN1_pin, IN2_pin), Encoder(FaseA_pin, FaseB_pin)      // Constructor 
    {
        ESP_LOGI(TAG, "Puente H registrado - EN: %d IN1: %d IN2: %d", EN_pin, IN1_pin, IN2_pin);
        ESP_LOGI(TAG, "Encoder registrado - Fase A: %d Fase B: %d", FaseA_pin, FaseB_pin);
    }
};

mcpwm_timer_handle_t DC_motor_t::HBridge_t::tmr = nullptr;                   // Timer para el PWM
mcpwm_oper_handle_t DC_motor_t::HBridge_t::op = nullptr;                     // Operador para el timer

// ======================= Variables Globales ======================= //

// ========================= Interrupciones ========================= //

// =========================== Funciones ============================ //

// ======================== Codigo Principal ======================== //
extern "C" void app_main(void)
{
    DC_motor_t Motor1(2, 3, 4, 5, 6);      // Motor 1 en GPIO 18
    DC_motor_t Motor2(18, 19, 20, 21, 22);  // Motor 1 en GPIO 188
    
    while (true)
    {
        //vTaskDelay(pdMS_TO_TICKS(1000));
        //*/
        for(uint16_t i = 0; i < MAX_DUTY_CYCLE; i++)
        {
            //ESP_LOGI(TAG, "Voltage %f",(float) 3.3 * i / DC_motor_t::MAX_DUTY_CYCLE);
            Motor1.H_bridge.set_dutycicle(i);
            Motor2.H_bridge.set_dutycicle(MAX_DUTY_CYCLE - i);
            
            vTaskDelay(pdMS_TO_TICKS(10));
        }
        //*/
    }    
}