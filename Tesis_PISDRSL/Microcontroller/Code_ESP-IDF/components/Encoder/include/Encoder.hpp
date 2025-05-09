#ifndef ENCODER_H
#define ENCODER_H

// ============================ Librerias =========================== //
#include "driver/gpio.h"
#include "esp_log.h"
#include "driver/pulse_cnt.h"

// =========================== Constantes =========================== //

// ====================== Prototipos de Clases ====================== //
class Encoder_t
{
private:    // CONSTANTES
    inline static const char *TAG = "Encoder";   // Etiqueta para el registro de logs

public:     // ESTRUCTURAS
    struct config_s
    {
        gpio_num_t FaseA_pin;          // Pin de habilitacion del motor
        gpio_num_t FaseB_pin;         // Pin de direccion 1 del motor
    };

private:    // CAMPOS
    config_s config;    // Configuracion del encoder
    pcnt_unit_handle_t pcnt_unit;
    
public:     // METODOS
    Encoder_t() = default; // Constructor vacio

    void init(config_s cfg);        // Inicializa el encoder
    // Hacer funciones para leer valor de encoder
};

#endif