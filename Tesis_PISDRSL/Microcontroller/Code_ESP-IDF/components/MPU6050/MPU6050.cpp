// ============================ Librerias =========================== //
#include "MPU6050.hpp"

// ==================== Definicion de funciones ===================== //
void MPU6050_t::init(config_s config)
{
// Declaramos bus I2C como maestro
    i2c_master_bus_config_t i2c_mst_config;
        i2c_mst_config.clk_source = I2C_CLK_SRC_DEFAULT;     // Fuente de reloj por defecto
        i2c_mst_config.i2c_port = I2C_NUM_0;                 // Puerto I2C 0
        i2c_mst_config.scl_io_num = config.SCL_pin;          // Pin SCL
        i2c_mst_config.sda_io_num = config.SDA_pin;          // Pin SDA
        i2c_mst_config.glitch_ignore_cnt = 7;                // Ignora hasta 7 ciclos de reloj de ruido
        i2c_mst_config.flags.enable_internal_pullup = true;  // Habilita resistencias pull-up internas
        i2c_mst_config.intr_priority = 1;   // Prioridad de interrupción válida
    i2c_master_bus_handle_t bus_handle;
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, &bus_handle));
    
// Creamos un nuevo bus maestro I2C con la configuración dada y guardamos el handle en bus_handle.
    i2c_device_config_t dev_cfg =
    {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,          // Longitud de la dirección del dispositivo
        .device_address = ADDRESS,                      // Dirección del dispositivo (MPU6050)
        .scl_speed_hz = 400000,                         // Velocidad del reloj SCL
    };
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_cfg, &dev_handle));

    uint8_t write_buffer[2];

// Configuramos el MPU6050
    // Reseteamos el MPU6050
        write_buffer[0] = PWR_MGMT_1;
        write_buffer[1] = 0x80;             // Reseteamos el MPU6050
        ESP_ERROR_CHECK(i2c_master_transmit(dev_handle, write_buffer, 2, 100));

    vTaskDelay(pdMS_TO_TICKS(100));         // Esperamos 100 ms para que el MPU6050 se reinicie

    // Encendemos el MPU6050 y configuramos el reloj interno
        write_buffer[0] = PWR_MGMT_1;
        write_buffer[1] = 0x01;             // Usa el giroscopio X como referencia de reloj
        ESP_ERROR_CHECK(i2c_master_transmit(dev_handle, write_buffer, 2, 100));
        
    // Configuramos filtro digital (DLPF)
        write_buffer[0] = CONFIG_R;
        write_buffer[1] = 0x01;             // Configura el filtro digital (DLPF - Digital Low Pass Filter)
        ESP_ERROR_CHECK(i2c_master_transmit(dev_handle, write_buffer, 2, 100));

    // Configuramos rango del giroscopio
        write_buffer[0] = GYRO_CONFIG;
        write_buffer[1] = 0x00;             // Rango de ±250 °/s
        ESP_ERROR_CHECK(i2c_master_transmit(dev_handle, write_buffer, 2, 100));

    // Configuramos rango del acelerometro
        write_buffer[0] = ACCEL_CONFIG;
        write_buffer[1] = 0x00;             // ±2g (valor por defecto)
        ESP_ERROR_CHECK(i2c_master_transmit(dev_handle, write_buffer, 2, 100));

    // Configuramos el rango de muestreo
        write_buffer[0] = SMPRT_DIV;
        write_buffer[1] = 0x00;             // Tasa de muestreo a 1 kHz
        ESP_ERROR_CHECK(i2c_master_transmit(dev_handle, write_buffer, 2, 100));

    vTaskDelay(pdMS_TO_TICKS(200));  // Espera un poco para asegurar la estabilización

    ESP_LOGI(TAG, "SDA: %d | SCL: %d", config.SDA_pin, config.SCL_pin);
}

void MPU6050_t::read_data()
{
    uint8_t read_buffer[14];        // Buffer para leer datos del MPU6050
    uint8_t write_buffer[2];        // Buffer para escribir datos al MPU6050

    // Leemos los datos de todos los registros a la vez
    write_buffer[0] = ACCEL_XOUT_H; // Registro de inicio para leer datos
    i2c_master_transmit_receive(dev_handle, write_buffer, 1, read_buffer, 14, 1);

    // Convertimos los datos leidos a enteros de 16 bits
    A[0] = (int16_t)((read_buffer[0] << 8) | read_buffer[1]);       // Acelerómetro X
    A[1] = (int16_t)((read_buffer[2] << 8) | read_buffer[3]);       // Acelerómetro Y
    A[2] = (int16_t)((read_buffer[4] << 8) | read_buffer[5]);       // Acelerómetro Z

    G[0] = (int16_t)((read_buffer[8] << 8) | read_buffer[9]);       // Giroscopio X
    G[1] = (int16_t)((read_buffer[10] << 8) | read_buffer[11]);     // Giroscopio Y
    G[2] = (int16_t)((read_buffer[12] << 8) | read_buffer[13]);     // Giroscopio Z
}