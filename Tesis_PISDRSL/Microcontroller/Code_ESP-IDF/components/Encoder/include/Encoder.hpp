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

// Variables de configuracion del encoder
    inline static constexpr int PCNT_HIGH_LIMIT = 32000;
    inline static constexpr int PCNT_LOW_LIMIT  = -32000;

public:     // ESTRUCTURAS
    struct config_s
    {
        gpio_num_t FaseA_pin;           // Pin de habilitacion del motor
        gpio_num_t FaseB_pin;           // Pin de direccion 1 del motor
    };

public:    // CAMPOS
    int position;                          // Contador del encoder

private:
    config_s config;    // Configuracion del encoder
    pcnt_unit_handle_t      pcnt_unit;  // Handle de la unidad de conteo
    pcnt_channel_handle_t   pcnt_chan;  // Handle del canal de conteo
    
public:     // METODOS
    Encoder_t() = default; // Constructor vacio

    void init(config_s cfg);        // Inicializa el encoder
    // Hacer funciones para leer valor de encoder
    void read_data();               // Lee el valor del encoder
};

#endif