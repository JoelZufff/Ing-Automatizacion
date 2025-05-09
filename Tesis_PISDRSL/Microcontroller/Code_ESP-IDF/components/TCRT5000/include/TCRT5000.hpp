// ============================ Librerias =========================== //
#include "driver/gpio.h"

// =========================== Constantes =========================== //

// ====================== Prototipos de Clases ====================== //
class TCRT5000_t
{
    // CAMPOS
    public:

    TCRT5000_t() = default; // Constructor por defecto
    void init(gpio_num_t AO_pin);
};