// ============================ Librerias =========================== //
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_timer.h"

#include "AccessPoint.hpp"
#include "TCP_server.hpp"
#include "L298N.hpp"
#include "MPU6050.hpp"

// =========================== Constantes =========================== //
static const char *TAG = "Main";

// ============================= Clases ============================= //

// ======================= Variables Globales ======================= //
L298N_t         L298N;              // Instancia de la clase L298N_t para manejar los motores DC

// ========================= Interrupciones ========================= //

// =========================== Funciones ============================ //

// ======================== Codigo Principal ======================== //
extern "C" void app_main(void)
{
    // Inicializamos el Access Point
    AP_config_s AP_config = 
        { .ssid = "AP_Balancin", .password = "123456789", .channel = 1, .maxconn = 1 };
    AP_init(AP_config);

    // Inicializamos el servidor TCP
    const TCP_server_config_s TCP_config = 
        { .Port = 4545, .KeepAliveIdle = 5, .KeepAliveInterval = 5, .KeepAliveCount = 3 };
    TCP_server_init(TCP_config);
        
    // DEBEMOS CONFIRMAR QUE HAY CONEXION EN EL SERVIDOR ANTES DE INICIALIZAR

    // Inicializamos Puente H y Encoder de motor izquierdo
    DC_motor_t::config_s LeftMotor_cfg = 
        { .EN_pin = GPIO_NUM_14, .IN1_pin = GPIO_NUM_5, .IN2_pin = GPIO_NUM_4 };
    L298N.LeftMotor.init(LeftMotor_cfg);

    Encoder_t::config_s LeftMotor_Encoder_cfg = 
        { .FaseA_pin = GPIO_NUM_19, .FaseB_pin = GPIO_NUM_18 };
    L298N.LeftMotor.Encoder.init(LeftMotor_Encoder_cfg);
// Inicializamos Puente H y Encoder de motor derecho
    const DC_motor_t::config_s RightMotor_cfg = 
        { .EN_pin = GPIO_NUM_27, .IN1_pin = GPIO_NUM_2, .IN2_pin = GPIO_NUM_15 };
    L298N.RightMotor.init(RightMotor_cfg);

    Encoder_t::config_s RightMotor_Encoder_cfg = 
        { .FaseA_pin = GPIO_NUM_33, .FaseB_pin = GPIO_NUM_32 };
    L298N.RightMotor.Encoder.init(RightMotor_Encoder_cfg);

    // Falta comunicacion i2c con MPU6050
    // Falta inicializacion de sensores TCRT5000

    while (true)
    {
        vTaskDelay(pdMS_TO_TICKS(10));  // Libera la CPU cada 10ms
        /*/
        for(uint16_t i = 0; i < MAX_DUTY_CYCLE; i++)
        {
            char data[10];
            sprintf(data, "%1.2f V\r\n", (float) i * 0.00033);

            send(Access_Point.TcpServer.connection_sock, data, strlen(data), 0);
            
            L298N.LeftMotor.set_movement(i, FORWARD);       // Establecemos el movimiento del motor izquierdo
            L298N.RightMotor.set_movement(i, FORWARD);      // Establecemos el movimiento del motor derecho

            vTaskDelay(pdMS_TO_TICKS(1));
        }
        //*/
    }    
}