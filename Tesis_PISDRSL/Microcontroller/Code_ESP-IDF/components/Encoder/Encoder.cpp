// ============================ Librerias =========================== //
#include "Encoder.hpp"

// ==================== Definicion de funciones ===================== //
void Encoder_t::init(config_s cfg)
{
    config = cfg; // Guardamos la configuracion del encoder

    // Configurar unidad de conteo con límites (opcional)
        pcnt_unit_config_t unit_config =
        {
            .low_limit = -32768,
            .high_limit = 32767,
            .intr_priority = 0,
            .flags = { .accum_count = 0, }, // No acumulamos el conteo
        };
        ESP_ERROR_CHECK(pcnt_new_unit(&unit_config, &pcnt_unit));

        pcnt_chan_config_t chan_config = 
        {
            .edge_gpio_num = config.FaseA_pin, 
            .level_gpio_num = config.FaseB_pin, // Señal B como nivel
            .flags = 
            {
                .invert_edge_input = 0,
                .invert_level_input = 0,
                .virt_edge_io_level = 0,
                .virt_level_io_level = 0,
                .io_loop_back = 0
            },
        };
        pcnt_channel_handle_t chan;
        ESP_ERROR_CHECK(pcnt_new_channel(pcnt_unit, &chan_config, &chan));

    // Configuramos la unidad de conteo para que aumente el contador con flancos de subida
        ESP_ERROR_CHECK(pcnt_channel_set_edge_action(chan, PCNT_CHANNEL_EDGE_ACTION_INCREASE, PCNT_CHANNEL_EDGE_ACTION_HOLD));

    // Configuramos la accion del level_gpio_num para que modifique la direccion de giro cuando hay un desfase entre las señales A y B (PENDIENTE CONFIGURAR)
        ESP_ERROR_CHECK(pcnt_channel_set_level_action(chan, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));

    // Cofiguramos el filtro de ruido para la señal de conteo (PENDIENTE CALIBRAR EN FUNCION DE VELOCIDAD MAXIMA DE MOTOR)
        pcnt_glitch_filter_config_t filter_config = { .max_glitch_ns = 1000, };
        ESP_ERROR_CHECK(pcnt_unit_set_glitch_filter(pcnt_unit, &filter_config)); // Configuramos el filtro de ruido
}