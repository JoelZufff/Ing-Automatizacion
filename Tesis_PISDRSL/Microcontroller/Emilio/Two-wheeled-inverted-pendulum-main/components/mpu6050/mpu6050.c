#include <stdio.h>
#include "mpu6050.h"
#include "esp_log.h"

void init_mpu6050()
{
    // Declaramos bus I2C como maestro
    i2c_master_bus_config_t i2c_mst_config = 
    {
        .clk_source = I2C_CLK_SRC_DEFAULT,      // Fuente de reloj por defecto
        .i2c_port = I2C_NUM_0,                  // Puerto I2C 0
        .scl_io_num = PIN_I2C_SCL,              // Pin SCL
        .sda_io_num = PIN_I2C_SDA,              // Pin SDA
        .glitch_ignore_cnt = 7,                 // Ignora hasta 7 ciclos de reloj de ruido
        .flags.enable_internal_pullup = true,   // Habilita resistencias pullup internas
    };
    i2c_master_bus_handle_t bus_handle;
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, &bus_handle));

    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = 0x68,
        .scl_speed_hz = 400000,
    };
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_cfg, &dev_handle));


    ESP_LOGI(mpu_tag, "Registering I2C device");
    ESP_LOGI(mpu_tag, "Configuring mpu6050 registers");
    
    //*/
    data_wr[0] = 0x1A;  // Registro CONFIG (filtro DLPF)
    data_wr[1] = 0x2;   // Configura DLPF en 2 (aprox 94 Hz)
    ESP_ERROR_CHECK(i2c_master_transmit(dev_handle, data_wr, 2, 100));

    data_wr[0] = 0x6B;  // Registro PWR_MGMT_1
    data_wr[1] = 0x0;   // Despierta el dispositivo (quita bit SLEEP)
    ESP_ERROR_CHECK(i2c_master_transmit(dev_handle, data_wr, 2, 100));

    data_wr[0] = 0x6C;  // PWR_MGMT_2
    data_wr[1] = 0x0;   // Enciende todos los sensores
    ESP_ERROR_CHECK(i2c_master_transmit(dev_handle, data_wr, 2, 100));

    data_wr[0] = 0x1A;
    data_wr[1] = 0x1;   // DLPF = 1, diferente valor (quizás sobrescribe lo anterior)
    ESP_ERROR_CHECK(i2c_master_transmit(dev_handle, data_wr, 2, 100));

    data_wr[0] = 0x1B;  // Registro GYRO_CONFIG
    data_wr[1] = 0x0;   // Rango de ±250 °/s
    ESP_ERROR_CHECK(i2c_master_transmit(dev_handle, data_wr, 2, 100));
    /*/
    
    data_wr[0] = 0x6B;
    data_wr[1] = 0x80;
    ESP_ERROR_CHECK(i2c_master_transmit(dev_handle, data_wr, 2, 100));
    data_wr[0] = 0x6B;
    data_wr[1] = 0x00;
    ESP_ERROR_CHECK(i2c_master_transmit(dev_handle, data_wr, 2, 100));
    data_wr[0] = 0x1A;
    data_wr[1] = 0x01;
    ESP_ERROR_CHECK(i2c_master_transmit(dev_handle, data_wr, 2, 100));
    data_wr[0] = 0x1B;
    data_wr[1] = 0x00;
    ESP_ERROR_CHECK(i2c_master_transmit(dev_handle, data_wr, 2, 100));
    //*/
    ESP_LOGI(mpu_tag, "MPU initialized");
}

void read_mpu6050(uint8_t data[14])
{
    data_wr[0] = 0x3B;
    i2c_master_transmit_receive(dev_handle, data_wr, 1, data, 14, 2);
}