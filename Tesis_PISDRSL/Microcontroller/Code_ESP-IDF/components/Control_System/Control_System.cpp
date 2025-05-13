// ============================ Librerias =========================== //
#include "Control_System.hpp"

// ==================== Definicion de funciones ===================== //

void Control_System_t::init(System_Config_s Syst_cfg, Control_Config_s Ctrl_cfg, esp_timer_cb_t Tmr_handle)
{
// Almacenamos configuracion recibida
    this->Syst_Config = Syst_cfg;
    this->Ctrl_Config = Ctrl_cfg;

// Creamos el timer periodico para la rutina de control
    const esp_timer_create_args_t timer_args =
    {
        .callback = Tmr_handle,
        .name = "Control_Loop"
    };
    ESP_ERROR_CHECK(esp_timer_create(&timer_args, &control_Timer));

    // Iniciamos el timer
    ESP_ERROR_CHECK(esp_timer_start_periodic(control_Timer, Ctrl_cfg.Ts * 1000000));

    // El timer se ha inicializado
    ESP_LOGI(TAG, "Timer de lazo de control iniciado correctamente");
}

Control_System_t::Outputs_s Control_System_t::controlLoop(Inputs_s In)
{
// Calculo de error de seguimiento de linea
    float theta = In.sR - In.sL;

    // Saturación del ángulo theta para mantenerlo dentro del rango [-160, 160] grados
    if (theta > 160.0)
        theta = 160.0;
    else if (theta < -160.0)
        theta = -160.0;

    // Convertimos el error de seguimiento a radianes
    theta = -0.3 * theta / 160.0;

// Calculo de velocidad angular de rueda derecha en radidanes (REVISAR)
    static float esc = pi / (2.0 * Syst_Config.Encoder.PPR * Syst_Config.Encoder.NR);  // Pulsos de encoder a radianes

    float omegaL = (float) (In.posL * esc) / Ctrl_Config.Ts;
    float omegaR = (float) (In.posR * esc) * Ctrl_Config.Ts;

// Escalamos los valores de MPU6050
    float Xa = -(In.aX) * accel_factor;         // Xa en rango de -1 a 1
    float Yg = In.gY * gyro_factor * deg_2_rad; // [rad/s]

// Calculo del filtro complementario
    static float angulox_1 = 0.0;       // Valor anterior de angulo x_1

    float accelx = Xa * pi_2;                                               // Inclinacion en rango de -pi/2 a pi/2 [rad]
    float angulox = c1 * (angulox_1 + Yg * Ctrl_Config.Ts) + c2 * accelx;  // Ecuacion del filtro complementario
    angulox_1 = angulox;                                                    // Respaldando valor pasado
    float alpha = -angulox;
    alpha = alpha - calpha;                                                 // Compensaci�n de alineacion del MPU

    // Saturación de valores de angulo alpha
    if(alpha >= Syst_Config.Max_Values.alpha)
        alpha = Syst_Config.Max_Values.alpha;
    if(alpha <= (-Syst_Config.Max_Values.alpha))
        alpha = -Syst_Config.Max_Values.alpha;

// Calculo de velocidad traslacional
    float v = (omegaL + omegaR) * Syst_Config.Geometry.R / 2.0;   
      
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

// Calculo de esfuerzos de control   
    float taua = (-Ctrl_Config.Gains.kv * thetap - Ctrl_Config.Gains.kp * thetatil) * 2.0 * Syst_Config.Geometry.b / Syst_Config.Geometry.R;
    float u = (Ctrl_Config.Gains.k1 * alphap) + (Ctrl_Config.Gains.k2 * alpha) + (Ctrl_Config.Gains.k3 * vtil) + (Ctrl_Config.Gains.k4 * intvtil);
    
    // Saturación de voltaje de salida
    if(u >= v2tauM)
        u = v2tauM;
    if(u <= (-v2tauM))
        u =- v2tauM; 
                           
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

    /* Convertimos el voltaje en un valor valido para el Duty Cicle
    uWl = escs * fabs(ul); 
    */
  
// Calculo de voltaje de rueda derecha
    float uR = (tauR * Rasnkm) + (nkm * omegaR);
    //ur=uNM*cos(0.314*t);

    // Saturacion de voltaje para que no exceda el voltaje nominal
    if(uR >= Syst_Config.Max_Values.uN)
        uR = Syst_Config.Max_Values.uN;
    if(uR <= (-Syst_Config.Max_Values.uN))
        uR = -Syst_Config.Max_Values.uN;
        
    /*
    // Convertimos el voltaje en un valor valido para el Duty Cicle
    uWr = escs * fabs(uR);
    */
   
    return { uL, uR };
}