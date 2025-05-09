#ifndef EDCMOTOR_H
#define EDCMOTOR_H

// ============================ Librerias =========================== //
#include "driver/mcpwm_prelude.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "Encoder.hpp"

// =========================== Constantes =========================== //

// ====================== Prototipos de Clases ====================== //
class DC_motor_t
{
private:    // CONSTANTES
    inline static const char *TAG = "DC_motor";   // Etiqueta para el registro de logs

public:     // ESTRUCTURAS
    struct config_s
    {
        gpio_num_t EN_pin;          // Pin de habilitacion del motor
        gpio_num_t IN1_pin;         // Pin de direccion 1 del motor
        gpio_num_t IN2_pin;         // Pin de direccion 2 del motor
    };
    
public:    // CAMPOS
    Encoder_t Encoder;                  // Encoder del motor
private:
    config_s config;    // Configuracion del motor
    
    // Variables para generacion de PWM
    mcpwm_oper_handle_t *op;            // Operador para el timer
    mcpwm_cmpr_handle_t comp;           // Comparador para el operador
    mcpwm_gen_handle_t gen;             // Generador para el operador

public:     // METODOS
    DC_motor_t(mcpwm_oper_handle_t *op);  // Inicializamos el operador el PWM 
    
    void init(config_s cfg); // Inicializa el motor DC

    void set_movement(uint16_t duty_cycle, bool direction);
};

#endif