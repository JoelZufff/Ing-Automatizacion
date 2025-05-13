// ============================ Librerias =========================== //
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "math.h"

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
static const char *TAG = "Main";

// =========================== Estructuras ========================== //
struct wheel_s      // Cada rueda tiene motor, encoder y sensor de linea
{
    DC_motor_t  DC_motor;    // Motor del robot
    Encoder_t   Encoder;    // Encoder del motor
    TCRT5000_t  TCRT5000;   // Sensor de linea
};

// ======================= Variables Globales ======================= //
Control_System_t Control_System;

MPU6050_t MPU6050;
wheel_s Left_Wheel, Right_Wheel;

// ============================ Funciones =========================== //
static void controlLoop_Timer(void* arg)
{
    int64_t start_time  = esp_timer_get_time();

// Muestreo de variables
    // Leemos el valor del MPU6050
    MPU6050.read_data();

    // Leemos el valor del TCRT5000
    Left_Wheel.TCRT5000.read_data(1);
    Right_Wheel.TCRT5000.read_data(1);

    // Leemos el valor de encoders
    Left_Wheel.Encoder.read_data();
    Right_Wheel.Encoder.read_data();

    /*/ Probar valores de lectura de sensores
        ESP_LOGI(TAG, "Ax: %d, Ay: %d, Az: %d", MPU6050.A[0], MPU6050.A[1], MPU6050.A[2]);
        ESP_LOGI(TAG, "Gx: %d, Gy: %d, Gz: %d", MPU6050.G[0], MPU6050.G[1], MPU6050.G[2]);
        ESP_LOGI(TAG, "LIzq: %d, LDer: %d", Left_Wheel.TCRT5000.ADC_data, Right_Wheel.TCRT5000.ADC_data);
        ESP_LOGI(TAG, "Eizq: %d, EDer: %d\r\n", Left_Wheel.Encoder.position, Right_Wheel.Encoder.position);
    //*/

// Ejecutamos sistema de control
    Control_System_t::Inputs_s In = 
    {
        .aX = MPU6050.A[0],
        .gY = MPU6050.G[1],
        .sL = Left_Wheel.TCRT5000.ADC_data, 
        .sR = Right_Wheel.TCRT5000.ADC_data, 
        .posL = Left_Wheel.Encoder.position,
        .posR = Right_Wheel.Encoder.position,
    };

// Calculo de sistema de control
    Control_System_t::Outputs_s Out;
    Out = Control_System.controlLoop(In);

    // Convertimos el voltaje obtenindo a un valor valido del PWM
    static float escs = DC_motor_t::MAX_DUTY_CYCLE / Control_System.Syst_Config.Max_Values.uN;

    Left_Wheel.DC_motor.set_movement(fabs(Out.uL * escs), (Out.uL < 0) ? BACKWARD : FORWARD);
    Right_Wheel.DC_motor.set_movement(fabs(Out.uL * escs), (Out.uR < 0) ? BACKWARD : FORWARD);

    int64_t end_time = esp_timer_get_time();
    ESP_LOGW(TAG, "Tiempo: %lld us\r\n", end_time - start_time);

    /*/ Muestreo de tiempo
    int64_t start_time  = esp_timer_get_time();
    int64_t end_time;
    end_time = esp_timer_get_time();    // Obtiene el tiempo final en microsegundos
    ESP_LOGW("Encoder", "%lld us", end_time - start_time);
//*/
}

// ======================== Codigo Principal ======================== //
extern "C" void app_main(void)
{
// Inicializamos comunicacion con interfaz
    //*/ Wifi Access Point
        const AP_config_s AP_config = 
        { 
            .ssid       = "AP_Balancin", 
            .password   = "123456789", 
            .channel    = 1, 
            .maxconn    = 1 
        };
        AP_init(AP_config);
    //*/

    //*/ Servidor TCP
        const TCP_server_config_s TCP_config = 
        { 
            .Port               = 4545, 
            .KeepAliveIdle      = 5, 
            .KeepAliveInterval  = 5, 
            .KeepAliveCount     = 3 
        };
        TCP_init(TCP_config);   
    //*/

// Inicializamos componentes
    //*/ Rueda izquierda
        const DC_motor_t::config_s LMotor_cfg = 
        { 
            .EN_pin     = GPIO_NUM_14, 
            .IN1_pin    = GPIO_NUM_5, 
            .IN2_pin    = GPIO_NUM_4 
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
            .EN_pin     = GPIO_NUM_27, 
            .IN1_pin    = GPIO_NUM_2, 
            .IN2_pin    = GPIO_NUM_15 
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

//*/ Inicializamos sistema de control
    
    const Control_System_t::Control_Config_s Ctrl_Cfg = 
    {
        .Ts = 0.01,
        .Gains = 
        { 
            .k1 = 0.019, 
            .k2 = 1.94, 
            .k3 = 0.9, 
            .k4 = 2.57, 
            .kp = 0.08, 
            .kv = 0.008 
        },
        .References = 
        { 
            .V_d = 0.0 /*0.075*/, 
            .theta_d = 0.0 
        }
    };

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
            .omega = 16.0, 
            .uN = 5.9, 
            .u = 5.9 
        }
    };

    Control_System.init(Syst_Cfg, Ctrl_Cfg, controlLoop_Timer);
//*/

    xEventGroupWaitBits(TCP_client->eventGroup, 0x1, pdFALSE, pdFALSE, portMAX_DELAY);
    // Mientras se espera un cliente el PISDRSL se mantiene balanceandose sin realizar avance traslacional
    // Esto sera ciclico entonces si se detecta una desconexion, se espera una nueva conexion
}