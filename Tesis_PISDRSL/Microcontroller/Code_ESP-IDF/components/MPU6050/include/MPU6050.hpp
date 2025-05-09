// ============================ Librerias =========================== //
#include "driver/gpio.h"

// =========================== Constantes =========================== //

// ====================== Prototipos de Clases ====================== //
class MPU6050_t
{
    // CAMPOS
    public:

    MPU6050_t() = default;
    void init(gpio_num_t SDA_pin, gpio_num_t SCL_pin);
};