// ============================ Librerias =========================== //
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

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
MPU6050_t MPU6050;
wheel_s Left_Wheel, Right_Wheel;

// ============================ Funciones =========================== //
static void controlLoop_Timer(void* arg)
{
//*/ Muestreamos la salida del sistema para enviarla al controlador
    // Leemos el valor del MPU6050
        MPU6050.read_data();
    // Leemos el valor del TCRT5000
        Left_Wheel.TCRT5000.read_data(1);
        Right_Wheel.TCRT5000.read_data(1);
    // Leemos el valor de encoders
        Left_Wheel.Encoder.read_data();
        Right_Wheel.Encoder.read_data();

    // Agrupamos los datos de lectura en una estructura
        Control_System_t::Inputs_s In = 
        {
            .aX = MPU6050.a[0],
            .gY = MPU6050.g[1],
            .sL = Left_Wheel.TCRT5000.ADC_data, 
            .sR = Right_Wheel.TCRT5000.ADC_data, 
            .posL = Left_Wheel.Encoder.position,
            .posR = Right_Wheel.Encoder.position,
        };

    /*/ Probar valores de lectura de sensores
        ESP_LOGI(TAG, "Ax: %d, Ay: %d, Az: %d", MPU6050.A[0], MPU6050.A[1], MPU6050.A[2]);
        ESP_LOGI(TAG, "Gx: %d, Gy: %d, Gz: %d", MPU6050.G[0], MPU6050.G[1], MPU6050.G[2]);
        ESP_LOGI(TAG, "LIzq: %d, LDer: %d", Left_Wheel.TCRT5000.ADC_data, Right_Wheel.TCRT5000.ADC_data);
        ESP_LOGI(TAG, "Eizq: %d, EDer: %d\r\n", Left_Wheel.Encoder.position, Right_Wheel.Encoder.position);
    //*/

//*/ Calculamos y ejecutamos compensacion del controlador con la salida del sistema
    Control_System_t::Outputs_s Out = Control_System.controlLoop(In);

    // Ejecutamos el movimiento de los motores
    Left_Wheel.DC_motor.set_movement(Out.movL.dutyCicle, Out.movL.direction);
    Right_Wheel.DC_motor.set_movement(Out.movR.dutyCicle, Out.movR.direction);
//*/

//*/ Enviamos los datos del controlador al cliente para monitoreo PENDIENTE
    
//*/

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
            .pins = 
            {
                .EN_pin     = GPIO_NUM_14, 
                .IN1_pin    = GPIO_NUM_5, 
                .IN2_pin    = GPIO_NUM_4
            },
            .PWM =      // Frecuencia PWM = resolution_hz / (2 * period_ticks) = 1 kHz
            {
                .resolution_hz = 10000000, 
                .period_ticks  = 5000
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
                .period_ticks  = 5000
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
                .omega = 16.0,
                .duty_Cicle = Left_Wheel.DC_motor.get_MAX_DC(), 
                .uN = 5.9, 
                .u = 5.9 
            }
        };
        Control_System.init(Syst_Cfg);
    //*/

// Creamos y configuramos el controlador para balancear en lo que recibimos el cliente
    //*/ Inicializamos controlador
        const Control_System_t::Control_Config_s Ctrl_Wait_cfg = 
        {
            .Ts = 0.01, /*0.01*/
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
                .V_d = 0.0, 
                .theta_d = 0.0 
            }
        };
        Control_System.init(Ctrl_Wait_cfg, controlLoop_Timer);
    //*/

//WAIT_CLIENT:        // Esperamos recepcion de datos para configuracion del sistema de control
    xEventGroupWaitBits(TCP_client->eventGroup, BIT0, pdFALSE, pdTRUE, portMAX_DELAY);
    
    // Esperamos activacion de semaforo, porque el cliente se conecto y presiono start
        // Ejecutamos configuracion de control recibida
        // Activamos el muestreo de datos
    
    // Esperamos desactivacion de semaforo, porque se desconecto el cliente o presiono el boton de stop
        // Sistema de control en modo wait
        // Desactivamos el muestreo de datos
        // Volvemos a la etiqueta WAIT_CLIENT
}