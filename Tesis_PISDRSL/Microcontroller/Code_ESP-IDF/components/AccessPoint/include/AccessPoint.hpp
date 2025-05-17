#ifndef AP_H
#define AP_H

// ============================ Librerias =========================== //
#include "esp_wifi.h"       // Configuración y control del Wi-Fi (iniciar, conectar, modo AP/STA, etc.)
#include "esp_mac.h"        // Manejo de direcciones MAC del ESP32 (útil para identificar el dispositivo en la red)
#include "esp_system.h"     // Información del sistema, reinicio, chip ID, etc. (puede ser indirectamente útil)
#include "esp_event.h"      // Manejo del sistema de eventos, como eventos de conexión Wi-Fi
#include "esp_log.h"        // Registro de logs, útil para depurar funciones relacionadas al Wi-Fi
#include "nvs_flash.h"      // Almacenamiento persistente (para guardar configuración Wi-Fi como credenciales)
#include "string.h"         // Funciones de manipulación de cadenas, como strcpy y strlen

// =========================== Estructuras ========================== //
namespace AP
{
    struct config_s
    {
        const char* ssid;            // Nombre de la red (SSID)
        const char* password;             // Contraseña de la red
        int channel;                 // Canal de radio (1-13) que usará el AP
        int maxconn;                 // Número máximo de clientes simultáneos que podrán conectarse al AP (1-10)
    };

    void init(config_s cfg);      // Inicializamos el Access Point
    static void event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);  // Funcion para manejar eventos de Wi-Fi (conexiones, desconexiones, errores, etc.)
}
#endif
