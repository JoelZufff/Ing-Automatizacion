// ============================ Librerias =========================== //
#include "TCRT5000.hpp"

// ==================== Definicion de funciones ===================== //
TCRT5000_t::TCRT5000_t()        // Inicializamos el Handle del ADC
{
    if(ADC_handle == NULL)    // Si el handle del ADC no ha sido inicializado
    {
        adc_oneshot_unit_init_cfg_t config = 
        {
            .unit_id = ADC_UNIT_1,                  // Seleccionamos el ADC1 por el uso de wifi
        };
        ESP_ERROR_CHECK(adc_oneshot_new_unit(&config, &ADC_handle));
    }
}

void TCRT5000_t::init(adc_channel_t AO_chann)
{
    this->AO_chann = AO_chann;    // Guardamos el canal del ADC
    
    adc_oneshot_chan_cfg_t config = 
    {
        .atten = ADC_ATTEN_DB_12,               // Configuramos la atenuacion de 12 dB para leer hasta 3.6V 
        .bitwidth = ADC_BITWIDTH_DEFAULT,       // Configuramos el bitwidth a 13 bits de resolucion para lleer hasta 8192
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(ADC_handle, AO_chann, &config));

    ESP_LOGI(TAG, "ADC: A%d", AO_chann);
}

void TCRT5000_t::read_data()           // Obtiene un promedio de los data_num valores leidos del ADC 
{        
    ESP_ERROR_CHECK(adc_oneshot_read(ADC_handle, AO_chann, &this->ADC_data));    // Leemos el valor del ADC    
}

void TCRT5000_t::read_data(uint16_t data_num)           // Obtiene un promedio de los data_num valores leidos del ADC 
{        
    uint32_t ADC_sum = 0;                   // Variable para almacenar la suma de los i valores leidos del ADC
    for(uint8_t i = 0; i < data_num; i++)
    {
        int ADC_data = 0;    // Variable para almacenar el valor leido del ADC
        ESP_ERROR_CHECK(adc_oneshot_read(ADC_handle, AO_chann, &ADC_data));    // Leemos el valor del ADC
        ADC_sum += ADC_data;    // Sumamos el valor leido del ADC
    }
    
    this->ADC_data = ADC_sum / data_num;    // Obtenemos el promedio de los i valores leidos del ADC
}