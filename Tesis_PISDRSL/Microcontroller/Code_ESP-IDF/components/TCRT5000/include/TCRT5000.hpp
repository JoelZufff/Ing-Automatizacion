#ifndef TCRT5000_H
#define TCRT5000_H

// ============================ Librerias =========================== //
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"

// =========================== Constantes =========================== //

// ====================== Prototipos de Clases ====================== //
class TCRT5000_t
{
private:    // CONSTANTES
    inline static const char *TAG = "TCRT5000";   // Etiqueta para el registro de logs

public:     // CAMPOS
    int ADC_data;    // Variable para almacenar el valor leido del ADC
private: 
    inline static adc_oneshot_unit_handle_t ADC_handle = NULL;    // Handle del ADC
    adc_channel_t AO_chann;

public:     // METODOS
    TCRT5000_t();    // Inicializamos el Handle del ADC
    void init(adc_channel_t AO_chann);      // Inicializamos el TCRT5000
    void read_data();                       // Obtiene un valor unico leido del ADC
    void read_data(uint16_t data_num);      // Obtiene un promedio de los data_num valores leidos del ADC 
};

#endif