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
public:     
    inline static const uint16_t MAX_DUTY_CYCLE = 10000;   // 10000 ticks para el ciclo de trabajo, 10 MHz/10000 = 1 KHz Timer

public:     // ESTRUCTURAS
    struct config_s
    {
        gpio_num_t EN_pin;          // Pin de habilitacion del motor
        gpio_num_t IN1_pin;         // Pin de direccion 1 del motor
        gpio_num_t IN2_pin;         // Pin de direccion 2 del motor
    };
    
private:    // CAMPOS
    config_s config;    // Configuracion del motor
    
    // Variables para generacion de PWM
    inline static mcpwm_timer_handle_t tmr = NULL;  // Timer para el PWM
    inline static mcpwm_oper_handle_t op = NULL;    // Operador para el timer
    mcpwm_cmpr_handle_t comp;                       // Comparador para el operador
    mcpwm_gen_handle_t gen;                         // Generador para el operador

public:     // METODOS
    DC_motor_t();  // Inicializamos el operador el PWM 
    
    void init(config_s cfg); // Inicializa el motor DC

    void set_movement(uint16_t duty_cycle, bool direction);
};

#endif