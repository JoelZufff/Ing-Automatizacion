// ============================ Librerias =========================== //
#include "Encoder.hpp"

// ==================== Definicion de funciones ===================== //
void Encoder_t::init(config_s cfg)
{
    config = cfg; // Guardamos la configuracion del encoder

    // Configurar unidad de conteo con límites (opcional)
        pcnt_unit_config_t unit_config =
        {
            .low_limit = PCNT_LOW_LIMIT,
            .high_limit = PCNT_HIGH_LIMIT,
            .intr_priority = 0,
            //.flags = { .accum_count = 0, }, // No acumulamos el conteo
        };
        ESP_ERROR_CHECK(pcnt_new_unit(&unit_config, &pcnt_unit));

        pcnt_chan_config_t chan_config = 
        {
            .edge_gpio_num = config.FaseA_pin, 
            .level_gpio_num = config.FaseB_pin,
            .flags = 
            {
                .invert_edge_input = 0,
                .invert_level_input = 0,
                .virt_edge_io_level = 0,
                .virt_level_io_level = 0,
                .io_loop_back = 0
            },
        };
        ESP_ERROR_CHECK(pcnt_new_channel(pcnt_unit, &chan_config, &pcnt_chan));

    // Configuramos la unidad de conteo para que aumente el contador con flancos de subida
        ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan, PCNT_CHANNEL_EDGE_ACTION_DECREASE, PCNT_CHANNEL_EDGE_ACTION_INCREASE));

    // Configuramos la accion del level_gpio_num para que modifique la direccion de giro cuando hay un desfase entre las señales A y B (PENDIENTE CONFIGURAR)
        ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));

    /*/ Cofiguramos el filtro de ruido para la señal de conteo (PENDIENTE VER SI UTILIZAR)
        pcnt_glitch_filter_config_t filter_config = { .max_glitch_ns = 1000, };
        ESP_ERROR_CHECK(pcnt_unit_set_glitch_filter(pcnt_unit, &filter_config)); // Configuramos el filtro de ruido
    //*/

    // Iniciamos la unidad de conteo
    ESP_ERROR_CHECK(pcnt_unit_enable(pcnt_unit));
    ESP_ERROR_CHECK(pcnt_unit_start(pcnt_unit));

    ESP_LOGI(TAG, "FASE_A: %d, FASE_B: %d", config.FaseA_pin, config.FaseB_pin);
}

void Encoder_t::read_data()
{
    pcnt_unit_get_count(pcnt_unit, &position);
    pcnt_unit_clear_count(pcnt_unit);
}