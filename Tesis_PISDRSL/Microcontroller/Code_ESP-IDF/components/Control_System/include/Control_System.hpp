#ifndef CTRL_SYST_H
#define CTRL_SYST_H

// ============================ Librerias =========================== //
#include "esp_timer.h"
#include "esp_log.h"
#include "math.h"

// ====================== Prototipos de clase ======================= //
class Control_System_t
{
private:    // CONSTANTES
    inline static const char *TAG = "Control_System";

    static constexpr float pi = 3.141593;       // Valor de PI
    static constexpr float pi_2 = 1.570796;     // Valor de PI/2
    
// Factores de conversion
    static constexpr float deg_2_rad = 0.0174533;
    static constexpr float rad_2_deg = 57.29578;
    static constexpr float accel_div_factor = 16384.0;
    static constexpr float gyro_div_factor = 131.0;
    static constexpr float accel_factor = 0.0000610352;
    static constexpr float gyro_factor = 0.0076336;
 
    static constexpr float c1 = 0.995; //0.993
    static constexpr float c2 = 1.0 - c1;// ??

    static constexpr float calpha  = 0.145;   // Compensación del ángulo del IMU [rad]

public:     // ESTRUCTURAS
    
    struct System_Config_s
    {
        struct Encoder_s
        {
            float PPR;      // Pulsos por revolucion
            float NR;       // Relacion de transmision
        } Encoder;

        struct DC_motor_s
        {
            float Ra;           // Resistencia de bobinas [Ohms]
            float k_m;          // Constante de torque-corriente [Nm/A]
        } DC_motor;

        struct Geometry_s
        {
            float R;        // Radio de la rueda [m]
            float b;        // Distancia entre ruedas [m]
        } Geometry;

        struct Max_Values_s
        {
            float tau;              // Torque máximo por rueda [Nm]
            float alpha;            // Ángulo máximo de inclinación [rad]
            float omega;            // Velocidad angular máxima [rad/s]
            uint32_t duty_Cicle;    // Valor maximo del Duty Cicle del PWM
            float uN;               // Voltaje nominal máximo [V]
            float u;                // Voltaje máximo [V]
        } Max_Values;
    };

    struct Control_Config_s
    {
        float Ts;           // Tiempo de muestreo [s]
        
        struct Gains_s
        {
            float k1;       // Ganancia k1
            float k2;       // Ganancia k2
            float k3;       // Ganancia k3
            float k4;       // Ganancia k4
            float kp;       // Ganancia kp
            float kv;       // Ganancia kv
        } Gains;

        struct References_s
        {
            float V_d;      // Velocidad traslacional deseada [m/s]
            float theta_d;  // Angulo theta deseado
        } References;
    };

    struct Inputs_s
    {
        // MPU6050
        int aX;         // Aceleracion en X [m/s^2]
        int gY;         // Velocidad angular en Y [°/s]
        // TCRT5000
        int sL;         // ADC de seguidor de linea izquierdo [12 bits]
        int sR;         // ADC de seguidor de linea izquierdo [12 bits]
        // Encoder
        int posL;       // Cuenta de enconder de posicion de motor
        int posR;       // Cuenta de enconder de posicion de motor
    };

    struct Outputs_s
    {
        struct Motor_movement_s         // Salida del compensador para el movimiento de los motores
        {
            uint32_t dutyCicle; // Valor del duty cicle para rueda izquierda
            bool direction;     // Direccion de giro de la rueda
        } movL, movR;

        struct Monitor_Data_s           // Variables del compensador para monitoreo
        {
            float vd;        // Velocidad traslacional deseada [m/s]
            float v;         // Velocidad traslacional [m/s]
            float theta;     // Angulo theta [rad]
            float alpha;     // Angulo alpha [rad]
            float omegaL;    // Velocidad angular llanta izquierda [rad/s]
            float uL;        // Voltaje de salida llanta izquierda [V]
            float omegaR;    // Velocidad angular llanta izquierda [rad/s]
            float uR;        // Voltaje de salida llanta izquierda [V]
        } monit_Data;
    };

private:    // CAMPOS
// Variables de configuracion
    System_Config_s Syst_Config;                    // Configuracion del sistema
    Control_Config_s Ctrl_Config;                   // Configuracion del controlador

// Variables para timer de ciclo de control
    esp_timer_handle_t timer_handle = nullptr;      // Handle del timer

    /*      // Ver por si ocupamos reiniciar, y resetear integrales
    // Variables para integrales
    float angPrev_      = 0.0f;
    float alphaPrev_    = 0.0f;
    float thetaPrev_    = 0.0f;
    float intVtilPrev_  = 0.0f;
    */

public:     // METODOS
    Control_System_t() = default;
    void init(System_Config_s Syst_cfg);                                // Inicializar sistema
    void init(Control_Config_s Ctrl_cfg, esp_timer_cb_t Tmr_handle);    // Inicializar controlador
    Outputs_s controlLoop(Inputs_s Inputs);                             // Ciclo de control
};

#endif
