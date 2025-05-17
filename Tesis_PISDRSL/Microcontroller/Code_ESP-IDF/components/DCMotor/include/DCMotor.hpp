#ifndef DCMOTOR_H
#define DCMOTOR_H

// ============================ Librerias =========================== //
#include "driver/mcpwm_prelude.h"
#include "driver/gpio.h"
#include "esp_log.h"

// =========================== Constantes =========================== //
#define FORWARD             1           // Direccion de movimiento del motor
#define BACKWARD            0           // Direccion de movimiento del motor

// ====================== Prototipos de Clases ====================== //
class DC_motor_t
{
private:    // CONSTANTES
    inline static const char *TAG = "DC_motor";   // Etiqueta para el registro de logs

public:     // ESTRUCTURAS
    struct config_s
    {
        struct pins_s
        {
            gpio_num_t EN_pin;          // Pin de habilitacion del motor
            gpio_num_t IN1_pin;         // Pin de direccion 1 del motor
            gpio_num_t IN2_pin;         // Pin de direccion 2 del motor
        } pins;
        struct PWM_s
        {
            uint32_t resolution_hz;     // Resolucion del PWM
            uint32_t period_ticks;      // Valor maximo del ciclo de trabajo
        } PWM;
    };

private:
    config_s config;    // Configuracion del motor
    
    // Variables para generacion de PWM
    inline static mcpwm_timer_handle_t tmr = NULL;  // Timer para el PWM
    inline static mcpwm_oper_handle_t op = NULL;    // Operador para el timer
    mcpwm_cmpr_handle_t comp;                       // Comparador para el operador
    mcpwm_gen_handle_t gen;                         // Generador para el operador

public:     // METODOS
    DC_motor_t() = default;
    void init(config_s cfg);                                // Inicializa pines de GPIO y PWM para el movimiento del motor
    uint32_t get_MAX_DC();                                  // Devuelve el valor maximo del ciclo de trabajo
    void set_movement(uint32_t duty_cycle, bool direction); // Realiza un movimiento a la velocidad y direccion deseada
};

#endif