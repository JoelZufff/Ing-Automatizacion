#ifndef L298N_H
#define L298N_H

// ============================ Librerias =========================== //
#include "driver/mcpwm_prelude.h"
#include "driver/pulse_cnt.h"
#include "DCMotor.hpp"

// =========================== Constantes =========================== //
#define FORWARD             1           // Direccion de movimiento del motor
#define BACKWARD            0           // Direccion de movimiento del motor
#define MAX_DUTY_CYCLE      10000       // 10000 ticks para el ciclo de trabajo, 10 MHz/10000 = 1 KHz Timer

// ====================== Prototipos de Clases ====================== //
class L298N_t
{
public:     // CAMPOS //
    DC_motor_t LeftMotor, RightMotor;   // Motores DC
    
    // Timer y operador, para las 2 señales PWM con misma frecuencia pero duty cycle diferente //
private:
    mcpwm_timer_handle_t tmr;           // Timer para el PWM
    mcpwm_oper_handle_t op;             // Operador para el timer

public:     // METODOS //
    L298N_t();
};

#endif