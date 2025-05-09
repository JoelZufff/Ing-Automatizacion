// ============================ Librerias =========================== //
#include "L298N.hpp"

// ==================== Definicion de funciones ===================== //
L298N_t::L298N_t() : LeftMotor(&op), RightMotor(&op)                           // Constructor vacio
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
}