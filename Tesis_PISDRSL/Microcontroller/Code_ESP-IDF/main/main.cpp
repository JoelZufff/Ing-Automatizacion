// ============================ Librerias =========================== //
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_timer.h"

// Comunicacion con interfaz
#include "AccessPoint.hpp"
#include "TCP_server.hpp"

// Componentes fisicos de control y muestreo
#include "TCRT5000.hpp"
#include "MPU6050.hpp"
#include "L298N.hpp"


// =========================== Constantes =========================== //
static const char *TAG = "Main";

/*
struct wheel_t
{
    DC_motor_t  DCmotor;    // Motor del robot
    Encoder_t   Encoder;    // Encoder del motor
    TCRT5000_t  TCRT5000;   // Sensor de linea
};
*/

// ======================= Variables Globales ======================= //
L298N_t         L298N;          // VER SI DESAPAREZCO ESTA CLASE HACIENDO OPERADOR Y TIMER ESTATICOS (PENDIENTE)
MPU6050_t       MPU6050;        // Instancia de la clase MPU6050_t para manejar el MPU6050
TCRT5000_t      TCRT5000[2];    // Instancia de la clase TCRT5000_t para manejar el TCRT5000

// =========================== Funciones ============================ //


// ======================== Codigo Principal ======================== //
extern "C" void app_main(void)
{
//*/ Inicializamos el Access Point
    const AP_config_s AP_config = 
    { 
        .ssid       = "AP_Balancin", 
        .password   = "123456789", 
        .channel    = 1, 
        .maxconn    = 1 
    };
    AP_init(AP_config);
//*/

//*/ Inicializamos el servidor TCP
    const TCP_server_config_s TCP_config = 
    { 
        .Port               = 4545, 
        .KeepAliveIdle      = 5, 
        .KeepAliveInterval  = 5, 
        .KeepAliveCount     = 3 
    };
    TCP_init(TCP_config);   
//*/

//*/ Inicializamos Puente H y Encoder de motor izquierdo
    const DC_motor_t::config_s LeftMotor_cfg = 
    { 
        .EN_pin     = GPIO_NUM_14, 
        .IN1_pin    = GPIO_NUM_5, 
        .IN2_pin    = GPIO_NUM_4 
    };
    L298N.LeftMotor.init(LeftMotor_cfg);

    const Encoder_t::config_s LeftMotor_Encoder_cfg = 
    { 
        .FaseA_pin  = GPIO_NUM_19, 
        .FaseB_pin  = GPIO_NUM_18 
    };
    L298N.LeftMotor.Encoder.init(LeftMotor_Encoder_cfg);
//*/

//*/ Inicializamos Puente H y Encoder de motor derecho
    const DC_motor_t::config_s RightMotor_cfg = 
    { 
        .EN_pin     = GPIO_NUM_27, 
        .IN1_pin    = GPIO_NUM_2, 
        .IN2_pin    = GPIO_NUM_15 
    };
    L298N.RightMotor.init(RightMotor_cfg);

    const Encoder_t::config_s RightMotor_Encoder_cfg = 
    { 
        .FaseA_pin  = GPIO_NUM_33, 
        .FaseB_pin  = GPIO_NUM_32 
    };
    L298N.RightMotor.Encoder.init(RightMotor_Encoder_cfg);
//*/

//*/ Inicializamos el MPU6050
    const MPU6050_t::config_s MPU6050_cfg = 
    { 
        .SDA_pin    = GPIO_NUM_21, 
        .SCL_pin    = GPIO_NUM_22 
    };
    MPU6050.init(MPU6050_cfg);    
//*/

// Inicializamos los sensores de linea TCRT5000
    TCRT5000[0].init(ADC_CHANNEL_7);
    TCRT5000[1].init(ADC_CHANNEL_6);
//*/

// Falta inicializar el sistema de control

/*/ Esperamos a que se conecte el cliente al servidor TCP
    while(!(xEventGroupGetBits(TCP_client->eventGroup) & 0x1))
        vTaskDelay(pdMS_TO_TICKS(10));
//*/

//*/
    while (true)
    {   
        /*/ Muestreo de tiempo
            int64_t start_time = esp_timer_get_time();  // Obtiene el tiempo en microsegundos
            int64_t end_time = esp_timer_get_time();    // Obtiene el tiempo final en microsegundos
            int64_t elapsed_time = end_time - start_time; // Calcula el tiempo transcurrido
            ESP_LOGI(TAG, "Tiempo transcurrido: %lld microsegundos", elapsed_time);
        //*/
        
        // Leemos el valor del MPU6050
        MPU6050.read_data();
        
        // Leemos el valor del TCRT5000
        TCRT5000[0].read_data(1);
        TCRT5000[1].read_data(1);

        // Leemos el valor del encoder
        
        /*/     Probar valores de lectura de sensores
        ESP_LOGI(TAG, "Ax: %d, Ay: %d, Az: %d\r\n", MPU6050.A[0], MPU6050.A[1], MPU6050.A[2]);
        ESP_LOGI(TAG, "Gx: %d, Gy: %d, Gz: %d\r\n", MPU6050.G[0], MPU6050.G[1], MPU6050.G[2]);
        ESP_LOGI(TAG, "TCRT5000[0]: %d, TCRT5000[1]: %d", TCRT5000[0].ADC_data, TCRT5000[1].ADC_data);
        //*/
        
        vTaskDelay(pdMS_TO_TICKS(1000));

        /*
        char data[100];
        int len = sprintf(data, "Ax = %d\r\nGy = %d\r\n", MPU6050.Ax, MPU6050.Gy);
        send(TCP_client->socket, data, len, 0);

        len = sprintf(data, "TCRT5000[0] = %d\r\nTCRT5000[1] = %d\r\n", TCRT5000[0].ADC_data, TCRT5000[1].ADC_data);
        send(TCP_client->socket, data, len, 0);    // Enviamos el valor de Ax al cliente
        */
        

        /*/
        for(uint16_t i = 0; i < MAX_DUTY_CYCLE; i++)
        {
            char data[10];
            sprintf(data, "%1.2f V\r\n", (float) i * 0.0007);

            send(TCP_client->socket, data, strlen(data), 0);
            
            L298N.LeftMotor.set_movement(i, FORWARD);       // Establecemos el movimiento del motor izquierdo
            L298N.RightMotor.set_movement(i, FORWARD);      // Establecemos el movimiento del motor derecho

            vTaskDelay(pdMS_TO_TICKS(5));
        }
        //*/
    }    
//*/
}