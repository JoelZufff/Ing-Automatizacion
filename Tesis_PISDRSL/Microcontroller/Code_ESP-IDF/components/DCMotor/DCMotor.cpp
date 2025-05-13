// ============================ Librerias =========================== //
#include "DCMotor.hpp"

// ==================== Definicion de funciones ===================== //
DC_motor_t::DC_motor_t()    // Inicializamos el operador el PWM 
{
    if (tmr == NULL)   // Si el timer no ha sido creado
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
    }

    if (op == NULL)   // Si el operador no ha sido creado
    {
        // Creacion de operador, para coordinar los comparadores y generadores con el timer //
        mcpwm_operator_config_t operator_config = { .group_id = 0, };
        ESP_ERROR_CHECK(mcpwm_new_operator(&operator_config, &op));
        ESP_ERROR_CHECK(mcpwm_operator_connect_timer(op, tmr));
    }
}
    
void DC_motor_t::init(config_s cfg) 
{
    // Configuramos los pines de direccion del motor //
    config = cfg; // Asignamos la configuracion del motor

    // Establecemos IN1_pin como salida y valor 0
    gpio_reset_pin(config.IN1_pin);
    gpio_set_direction(config.IN1_pin, GPIO_MODE_OUTPUT);   // Configuramos el pin como salida
    gpio_set_level(config.IN1_pin, 0);

    // Establecemos IN2_pin como salida y valor 0
    gpio_reset_pin(config.IN2_pin);
    gpio_set_direction(config.IN2_pin, GPIO_MODE_OUTPUT);   // Configuramos el pin como salida
    gpio_set_level(config.IN2_pin, 0);

    // Inicializamos el PWM en EN_pin //
    // Creacion de comparadores, para definir el punto de cambio (duty cycle) de la señal PWM. //
    mcpwm_comparator_config_t compare_config;
    compare_config.flags.update_cmp_on_tez = true;
    compare_config.intr_priority = 0;
    ESP_ERROR_CHECK(mcpwm_new_comparator(op, &compare_config, &comp));
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comp, 0));       // 0% duty cycle

    // Creacion de generador, para generar la señal PWM en el pin seleccionado //
    mcpwm_generator_config_t gen_config; 
    gen_config.gen_gpio_num = config.EN_pin;         // GPIO para la señal PWM
    ESP_ERROR_CHECK(mcpwm_new_generator(op, &gen_config, &gen));

    // Configuracion de la señal PWM //
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(gen,MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)));
    ESP_ERROR_CHECK(mcpwm_generator_set_actions_on_compare_event(gen,MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, comp, MCPWM_GEN_ACTION_LOW)));

    ESP_LOGI(TAG, "IN1_pin = %d | IN2_pin = %d | EN_pin = %d", config.IN1_pin, config.IN2_pin, config.EN_pin);
}

void DC_motor_t::set_movement(uint16_t duty_cycle, bool direction)
{
    // Establecemos la direccion de movimiento del motor //
    gpio_set_level(config.IN1_pin, !direction); // Establecemos IN1_pin en alto
    gpio_set_level(config.IN2_pin, direction);  // Establecemos IN2_pin en bajo

    // Establecemos el duty cycle del PWM //
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comp, duty_cycle)); // Establecemos el duty cycle del PWM
}