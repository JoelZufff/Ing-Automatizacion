#ifndef MPU6050_H
#define MPU6050_H

// ============================ Librerias =========================== //
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/i2c_master.h"
#include "esp_log.h"

// ====================== Prototipos de Clases ====================== //
class MPU6050_t
{
private:    // CONSTANTES
    inline static const char *TAG = "MPU6050";   // Etiqueta para el registro de logs

// Direcciones de registros del IMU
    // Direcciones I2C
        static constexpr uint8_t ADDRESS        = 0x68;         // Dirección i2c del MPU6050
        static constexpr uint8_t W_DATA         = 0xD0;         // Registro de escritura
        static constexpr uint8_t R_DATA         = 0xD1;         // Registro de lectura

    // Registros de configuración
        static constexpr uint8_t PWR_MGMT_1     = 0x6B;         // Control de gestión de energía del MPU6050
        static constexpr uint8_t PWR_MGMT_2     = 0x6C;         // Controlar los estados de apagado de los sensores
        static constexpr uint8_t SMPRT_DIV      = 0x19;         // Configurar la frecuencia de muestreo
        static constexpr uint8_t CONFIG_R       = 0x1A;         // Configurar el filtro digital
        static constexpr uint8_t GYRO_CONFIG    = 0x1B;         // Configurar el rango del giroscopio
        static constexpr uint8_t ACCEL_CONFIG   = 0x1C;         // Configurar el rango del acelerómetro
    
    // Registros de lectura de datos
        // Acelerometro en X
            static constexpr uint8_t ACCEL_XOUT_H   = 0x3B;         // Parte alta
            static constexpr uint8_t ACCEL_XOUT_L   = 0x3C;         // Parte baja
        // Acelerometro en Y
            static constexpr uint8_t ACCEL_YOUT_H   = 0x3D;         // Parte alta
            static constexpr uint8_t ACCEL_YOUT_L   = 0x3E;         // Parte baja
        // Acelerometro en Z
            static constexpr uint8_t ACCEL_ZOUT_H   = 0x3F;         // Parte alta
            static constexpr uint8_t ACCEL_ZOUT_L   = 0x40;         // Parte baja
        // Temperatura
            static constexpr uint8_t TEMP_OUT_H     = 0x41;         // Parte alta
            static constexpr uint8_t TEMP_OUT_L     = 0x42;         // Parte baja
        // Giroscopio en X
            static constexpr uint8_t GYRO_XOUT_H    = 0x43;         // Parte alta
            static constexpr uint8_t GYRO_XOUT_L    = 0x44;         // Parte baja
        // Giroscopio en Y
            static constexpr uint8_t GYRO_YOUT_H    = 0x45;         // Parte alta
            static constexpr uint8_t GYRO_YOUT_L    = 0x46;         // Parte baja
        // Giroscopio en Z
            static constexpr uint8_t GYRO_ZOUT_H    = 0x47;         // Parte alta
            static constexpr uint8_t GYRO_ZOUT_L    = 0x48;         // Parte baja

public:     // ESTRUCTURAS
    struct config_s
    {
        gpio_num_t SDA_pin;     // Pin de habilitacion del motor
        gpio_num_t SCL_pin;     // Pin de direccion 1 del motor
    };

public:     // CAMPOS
    int a[3];                 // Aceleracion en X, Y y Z
    int g[3];                 // Velocidad angular en X, Y y Z

private:
    i2c_master_dev_handle_t dev_handle;     // Handle del dispositivo I2C    

public:     // METODOS
    MPU6050_t() = default;    // Constructor por defecto
    
    void init(config_s config); // Inicializa el MPU6050
    void read_data();           // Lee los datos del MPU6050
};

#endif