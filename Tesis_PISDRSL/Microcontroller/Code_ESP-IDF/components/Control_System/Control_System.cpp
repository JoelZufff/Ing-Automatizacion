// ============================ Librerias =========================== //
#include "Control_System.hpp"

// ==================== Definicion de funciones ===================== //
void Control_System_t::init(System_Config_s Syst_cfg) { Syst_Config = Syst_cfg; }

void Control_System_t::init(Control_Config_s Ctrl_cfg, esp_timer_cb_t Tmr_handle)
{
    if(timer_handle == nullptr)     // Se inicializo el timer por primera vez
    {
        
    }
    

// Almacenamos configuracion recibida
    Ctrl_Config = Ctrl_cfg;

// Creamos el timer periodico para la rutina de control
    const esp_timer_create_args_t timer_args =
    {
        .callback = Tmr_handle,
        .name = "Control_Loop"
    };
    ESP_ERROR_CHECK(esp_timer_create(&timer_args, &timer_handle));

    // Iniciamos el timer
    ESP_ERROR_CHECK(esp_timer_start_periodic(timer_handle, Ctrl_Config.Ts * 1000000));

    // El timer se ha inicializado
    ESP_LOGI(TAG, "Controlador inicializado con los siguientes valores:");
    ESP_LOGI(TAG, "k1 = %.3f | k2 = %.2f | k3 = %.2f | k4 =  %.2f | kp =  %.2f | kv = %.3f", Ctrl_cfg.Gains.k1, Ctrl_cfg.Gains.k2, Ctrl_cfg.Gains.k3, Ctrl_cfg.Gains.k4, Ctrl_cfg.Gains.kp, Ctrl_cfg.Gains.kv);
    ESP_LOGI(TAG, "Ts = %.3f | vd = %.3f", Ctrl_cfg.Ts, Ctrl_cfg.References.V_d);
}

Control_System_t::Outputs_s Control_System_t::controlLoop(Inputs_s In)
{
// Calculo angulo theta de error de seguimiento de linea
    float theta = In.sR - In.sL;

    // Saturación del ángulo theta para mantenerlo dentro del rango [-160, 160]
    if (theta > 160.0)
        theta = 160.0;
    else if (theta < -160.0)
        theta = -160.0;

    theta = -0.3 * theta / 160.0;   // ?? REVISAR

// Calculo de velocidad angular de cada rueda
    static float PULSE_to_RAD = pi / (2.0 * Syst_Config.Encoder.PPR * Syst_Config.Encoder.NR);  // Constante para convertir de pulsos de encoder a radianes
    
    float omegaL = (float) (In.posL * PULSE_to_RAD) / Ctrl_Config.Ts;       
    float omegaR = (float) (In.posR * PULSE_to_RAD) / Ctrl_Config.Ts;

// Calculo de angulo alpha
    // Escalamos los valores de MPU6050
        float Xa = -(In.aX) * accel_factor;         // Xa en rango de -1 a 1
        float Yg = In.gY * gyro_factor * deg_2_rad; // [rad/s]

    // Filtro complementario para estimar el angulo alpha a partir de la aceleracion en x y velocidad angular en y
        static float angulox_1 = 0.0;       // Valor anterior de angulo x_1

        float accelx = Xa * pi_2;                                               // Inclinacion en rango de -pi/2 a pi/2 [rad]
        float angulox = c1 * (angulox_1 + Yg * Ctrl_Config.Ts) + c2 * accelx;   // Ecuacion del filtro complementario
        angulox_1 = angulox;                                                    // Respaldando valor pasado
        float alpha = -angulox;
        alpha = alpha - calpha;                                                 // Compensaci�n de alineacion del MPU

    // Saturación de valores de angulo alpha
        if(alpha >= Syst_Config.Max_Values.alpha)
            alpha = Syst_Config.Max_Values.alpha;
        if(alpha <= (-Syst_Config.Max_Values.alpha))
            alpha = -Syst_Config.Max_Values.alpha;

// Calculo de velocidad traslacional
    float v = (omegaL + omegaR) * Syst_Config.Geometry.R / 2.0;     // Promedio de velocidad de las 2 ruedas por el radio   
      
// Calculo de theta punto
    float thetap = (omegaR - omegaL) * Syst_Config.Geometry.R / (2.0 * Syst_Config.Geometry.b);     
    static float alpha_1 = 0.0;         // Valor anterior de alpha

    float thetatil = theta - Ctrl_Config.References.theta_d;    // Se calcula theta tilde
    float alphap = (alpha - alpha_1) / Ctrl_Config.Ts;          // Se calcula alpha punto (Derivada sucia de alpha)
    alpha_1 = alpha;                                            // Almacenamos alpha anterior
    
    float vtil = v - Ctrl_Config.References.V_d;                // Se calcula v tilde

    static float intvtil = 0.0;                 // Integral de v tilde
    static float v2tauM = 2.0 * Syst_Config.Max_Values.tau;

    if( (intvtil < v2tauM) && (intvtil > (-v2tauM)))        // Integral de v tilde
        intvtil = intvtil + Ctrl_Config.Ts * vtil;
    else    // Saturacion
    {
        if(intvtil >= v2tauM)
            intvtil = 0.95 * v2tauM;
        if(intvtil <= (-v2tauM))
            intvtil = -0.95 * v2tauM; 
    }

// Calculo de esfuerzo de control
    float taua = (-Ctrl_Config.Gains.kv * thetap - Ctrl_Config.Gains.kp * thetatil) * 2.0 * Syst_Config.Geometry.b / Syst_Config.Geometry.R;
    float u = (Ctrl_Config.Gains.k1 * alphap) + (Ctrl_Config.Gains.k2 * alpha) + (Ctrl_Config.Gains.k3 * vtil) + (Ctrl_Config.Gains.k4 * intvtil);

    // Parece ser un PD para controlar el angulo alpha y un PI para controlar la velocidad traslacional
    
    // Saturación de voltaje de salida
        if(u >= v2tauM)
            u = v2tauM;
        if(u <= (-v2tauM))
            u = -v2tauM; 
                           
    // Calculo de pares por rueda      
        float tauL = (-taua + u) / 2.0;     // par izquierdo
        float tauR = (taua + u) / 2.0;      // par derecho
                           
// Calculo de voltaje de rueda izquierda
    static float Rasnkm = Syst_Config.DC_motor.Ra / (Syst_Config.Encoder.NR * Syst_Config.DC_motor.k_m);
    static float nkm = Syst_Config.Encoder.NR * Syst_Config.DC_motor.k_m;

    float uL = (tauL * Rasnkm) + (nkm * omegaL);   
    //ul=uNM*sin(0.314*t);

    // Saturacion de voltaje para que no exceda el voltaje nominal
        if(uL >= Syst_Config.Max_Values.uN)
            uL = Syst_Config.Max_Values.uN;
        if(uL <= (-Syst_Config.Max_Values.uN))
            uL = -Syst_Config.Max_Values.uN;
  
// Calculo de voltaje de rueda derecha
    float uR = (tauR * Rasnkm) + (nkm * omegaR);
    //ur=uNM*cos(0.314*t);

    // Saturacion de voltaje para que no exceda el voltaje nominal
        if(uR >= Syst_Config.Max_Values.uN)
            uR = Syst_Config.Max_Values.uN;
        if(uR <= (-Syst_Config.Max_Values.uN))
            uR = -Syst_Config.Max_Values.uN;

// Salida del sistema de control
    static float V_to_DC = Syst_Config.Max_Values.duty_Cicle / Syst_Config.Max_Values.uN;   // Constante para convertir voltaje a duty cicle

    Outputs_s Out = 
    {
        .movL = 
        {
            .dutyCicle = (uint32_t) fabsf(uL * V_to_DC),
            .direction = (uL >= 0)
        },
        .movR = 
        {
            .dutyCicle = (uint32_t) fabsf(uR * V_to_DC),
            .direction = (uR >= 0)
        },
        .monit_Data = 
        {
            .vd = Ctrl_Config.References.V_d,
            .v = v,
            .theta = theta,
            .alpha = alpha,
            .omegaL = omegaL,
            .uL = uL,
            .omegaR = omegaR,
            .uR = uR
        }
    };

    return Out;
}