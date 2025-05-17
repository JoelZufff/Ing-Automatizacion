// ============================ Librerias =========================== //
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "string.h"

// Sistema de control
#include "Control_System.hpp"

// Comunicacion con interfaz
#include "AccessPoint.hpp"
#include "TCP_server.hpp"

// Componentes fisicos de control y muestreo
#include "MPU6050.hpp"
#include "DCMotor.hpp"
#include "Encoder.hpp"
#include "TCRT5000.hpp"

// =========================== Constantes =========================== //
const char *TAG = "Main";

// =========================== Estructuras ========================== //
struct wheel_s      // Cada rueda tiene motor, encoder y sensor de linea
{
    DC_motor_t  DC_motor;    // Motor del robot
    Encoder_t   Encoder;    // Encoder del motor
    TCRT5000_t  TCRT5000;   // Sensor de linea
};

// ======================= Variables Globales ======================= //
Control_System_t Control_System;
Control_System_t::Control_Config_s Interface_cfg;       // Configuracion enviada desde la interfaz

MPU6050_t MPU6050;
wheel_s Left_Wheel, Right_Wheel;

// ============================ Funciones =========================== //
static void controlLoop_Timer(void* arg)
{
//*/ Muestreamos la salida del sistema para enviarla al controlador
        MPU6050.read_data();
        
        Left_Wheel.TCRT5000.read_data();
        Right_Wheel.TCRT5000.read_data();
        
        Left_Wheel.Encoder.read_data();
        Right_Wheel.Encoder.read_data();

        Control_System_t::Inputs_s In = 
        {
            .aX = MPU6050.a[0],
            .gY = MPU6050.g[1],
            .sL = Left_Wheel.TCRT5000.ADC_data, 
            .sR = Right_Wheel.TCRT5000.ADC_data, 
            .posL = Left_Wheel.Encoder.position,
            .posR = Right_Wheel.Encoder.position,
        };
//*/
    /*/ Probar valores de lectura de sensores
        ESP_LOGI(TAG, "Ax: %d, Ay: %d, Az: %d", MPU6050.A[0], MPU6050.A[1], MPU6050.A[2]);
        ESP_LOGI(TAG, "Gx: %d, Gy: %d, Gz: %d", MPU6050.G[0], MPU6050.G[1], MPU6050.G[2]);
        ESP_LOGI(TAG, "LIzq: %d, LDer: %d", Left_Wheel.TCRT5000.ADC_data, Right_Wheel.TCRT5000.ADC_data);
        ESP_LOGI(TAG, "Eizq: %d, EDer: %d\r\n", Left_Wheel.Encoder.position, Right_Wheel.Encoder.position);
    //*/

//*/ Calculamos y ejecutamos compensacion del controlador con la salida del sistema
    Control_System_t::Outputs_s Out = Control_System.controlLoop(In);
    
    Left_Wheel.DC_motor.set_movement(Out.movL.dutyCicle, Out.movL.direction);
    Right_Wheel.DC_motor.set_movement(Out.movR.dutyCicle, Out.movR.direction);
    
    //ESP_LOGI(TAG, "OutL: %lu, OutR: %lu", Out.movL.dutyCicle, Out.movR.dutyCicle);
//*/

//*/ Enviamos los datos del controlador al cliente para monitoreo
    if(xEventGroupGetBits(TCP::eventGroup) & BIT0)          // Se una prueba de controlador activa
    {
        uint8_t data[8][4];    // 8 datos de 4 bytes
        
        memcpy(data[0], &Out.monit_Data.vd, sizeof(float));
        memcpy(data[1], &Out.monit_Data.v, sizeof(float));
        memcpy(data[2], &Out.monit_Data.theta, sizeof(float));
        memcpy(data[3], &Out.monit_Data.alpha, sizeof(float));
        memcpy(data[4], &Out.monit_Data.omegaL, sizeof(float));
        memcpy(data[5], &Out.monit_Data.uL, sizeof(float));
        memcpy(data[6], &Out.monit_Data.omegaR, sizeof(float));
        memcpy(data[7], &Out.monit_Data.uR, sizeof(float));
        
        send(TCP::Client::socket, data, sizeof(data), 0);       // Enviamos los datos al cliente   
    }
//*/

    /*/ Muestreo de tiempo
    int64_t start_time  = esp_timer_get_time();
    int64_t end_time;
    end_time = esp_timer_get_time();    // Obtiene el tiempo final en microsegundos
    ESP_LOGW("Tiempo", "%lld us", end_time - start_time);
//*/
}

void ProcessData(uint8_t *Data, int length)       // Funcion para procesar los datos recibidos por el cliente
{
    switch (Data[0])            // Analizamos el primer byte del paquete
    {
    case 0xAA:                  // Se presiono start y se mando configuracion de control
        if(length == 33)        // Recibimos los 33 bytes de configuracion
        {
            float* fData = (float*) &Data[1];    // Reconvertimos los valores a float de 4 bytes
            
        // Alamcenamos el valor de las ganancias
            Interface_cfg.Gains.k1 = fData[0];
            Interface_cfg.Gains.k2 = fData[1];
            Interface_cfg.Gains.k3 = fData[2];
            Interface_cfg.Gains.k4 = fData[3];
            Interface_cfg.Gains.kp = fData[4];
            Interface_cfg.Gains.kv = fData[5];
        
        // Almacenamos los valores de referencia y configuracion
            Interface_cfg.Ts = fData[6];
            Interface_cfg.References.V_d = fData[7];
            Interface_cfg.References.theta_d = 0;       // Ver si recibir tmb

            xEventGroupSetBits(TCP::eventGroup, BIT0);  // Indicamos que comienze la prueba de controlador
        }
        break;
    case 0xAB:          // Se presiono STOP
        xEventGroupClearBits(TCP::eventGroup, BIT0);    // Indicamos que se detenga la prueba de controlador
        break;
    default: break;
    }
}

// ======================== Codigo Principal ======================== //
extern "C" void app_main(void)
{
// Inicializamos comunicacion con interfaz
    //*/ Wifi Access Point
    const AP::config_s AP_config = 
    { 
        .ssid       = "AP_Balancin", 
        .password   = "123456789", 
        .channel    = 1, 
        .maxconn    = 1 
    };
    AP::init(AP_config);
    //*/

    //*/ Servidor TCP
    const TCP::config_s TCP_config = 
    { 
        .Port               = 4545,
        .ProcessData_func   = ProcessData,
        .KeepAlive  = 
        {
            .enabled    = 1,
            .idle       = 5,
            .interval   = 5,
            .count      = 3
        },
    };
    TCP::Server::init(TCP_config);
    //*/

// Inicializamos componentes
    //*/ Rueda izquierda
    const DC_motor_t::config_s LMotor_cfg = 
    { 
        .pins = 
        {
            .EN_pin     = GPIO_NUM_14, 
            .IN1_pin    = GPIO_NUM_5, 
            .IN2_pin    = GPIO_NUM_4
        },
        .PWM =      // Frecuencia PWM = resolution_hz / period_ticks = 1 kHz
        {
            .resolution_hz = 10000000, 
            .period_ticks  = 10000
        }
    };
    Left_Wheel.DC_motor.init(LMotor_cfg);

    const Encoder_t::config_s LEncoder_cfg =    // Nota: Voltee las fases por la rotacion contraria entre los motores 
    { 
        .FaseA_pin  = GPIO_NUM_18, 
        .FaseB_pin  = GPIO_NUM_19
    };
    Left_Wheel.Encoder.init(LEncoder_cfg);

    Left_Wheel.TCRT5000.init(ADC_CHANNEL_7);
    //*/

    //*/ Rueda derecha
    const DC_motor_t::config_s RMotor_cfg = 
    { 
        .pins = 
        {
            .EN_pin     = GPIO_NUM_27, 
            .IN1_pin    = GPIO_NUM_2, 
            .IN2_pin    = GPIO_NUM_15 
        },
        .PWM =      // Frecuencia PWM = resolution_hz / (2 * period_ticks) = 1 kHz
        {
            .resolution_hz = 10000000, 
            .period_ticks  = 10000
        }
    };
    Right_Wheel.DC_motor.init(RMotor_cfg);
    
    const Encoder_t::config_s REncoder_cfg = 
    { 
        .FaseA_pin  = GPIO_NUM_33, 
        .FaseB_pin  = GPIO_NUM_32 
    };
    Right_Wheel.Encoder.init(REncoder_cfg);
    
    Right_Wheel.TCRT5000.init(ADC_CHANNEL_6);
    //*/

    //*/ MPU6050
    const MPU6050_t::config_s MPU6050_cfg = 
    { 
        .SDA_pin    = GPIO_NUM_21, 
        .SCL_pin    = GPIO_NUM_22
    };
    MPU6050.init(MPU6050_cfg);    
    //*/

// Inicializamos sistema de control para balancear sin avance traslacional en lo que recibimos informacion del cliente
    //*/ Inicializamos sistema
    const Control_System_t::System_Config_s Syst_Cfg = 
    {
        .Encoder = 
        { 
            .PPR = 12.0, 
            .NR = 44.0 
        },
        .DC_motor = 
        { 
            .Ra = 3.0, 
            .k_m = 0.0008
        },
        .Geometry = 
        { 
            .R = 0.034, 
            .b = 0.0965 
        },
        .Max_Values = 
        {
            .tau = 0.3, 
            .alpha = 1.4, 
            .omega = 10.05,
            .duty_Cicle = Left_Wheel.DC_motor.get_MAX_DC(), 
            .uN = 5.9,
            .u = 5.9 
        }
    };
    Control_System.init(Syst_Cfg);
    //*/

//*/ Inicializamos controlador en modo balanceo en espera de cliente
    const Control_System_t::Control_Config_s Ctrl_Wait_cfg = 
    {
        .Ts = 0.01,
        .Gains = 
        { 
            .k1 = 0.020,    // 0.019
            .k2 = 1.5,     // 1.94
            .k3 = 0.9,      // 0.9
            .k4 = 2.57,     // 2.57
            .kp = 0.0,      // 0.08
            .kv = 0.0       // 0.008
        },
        .References = 
        {
            .V_d = 0.0,   // 0.075 
            .theta_d = 0.0 
        }
    };
    Control_System.init(Ctrl_Wait_cfg, controlLoop_Timer);
    //*/

WAIT_START:     // Esperamos solicitud de prueba de controlador
    xEventGroupWaitBits(TCP::eventGroup, BIT0, pdFALSE, pdTRUE, portMAX_DELAY);
    
    Control_System.init(Interface_cfg, controlLoop_Timer);         // Aplicamos configuracion recibida por el maestro
    
    xEventGroupWaitBits(TCP::eventGroup, BIT1, pdFALSE, pdTRUE, portMAX_DELAY);     // Esperamos a que el cliente nos indique se concluyo la prueba de controlador
    xEventGroupClearBits(TCP::eventGroup, BIT1);    // Limpiamos el bit de finalizacion de prueba
    goto WAIT_START;    // Esperamos nueva configuracion de control


    // Esperamos activacion de semaforo, porque el cliente se conecto y presiono start
        // Ejecutamos configuracion de control recibida
        // Activamos el muestreo de datos
    
    // Esperamos desactivacion de semaforo, porque se desconecto el cliente o presiono el boton de stop
        // Sistema de control en modo wait
        // Desactivamos el muestreo de datos
        // Volvemos a la etiqueta WAIT_CLIENT
}