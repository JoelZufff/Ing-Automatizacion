#ifndef TCP_SERVER_H
#define TCP_SERVER_H

// ============================ Librerias =========================== //
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_log.h"

#include "lwip/err.h"      // Manejo de errores de la pila TCP/IP (LwIP)
#include "lwip/sockets.h"  // Funciones de sockets para comunicación por red (TCP/UDP)
#include "lwip/sys.h"      // Utilidades del sistema para LwIP
#include <lwip/netdb.h>    // Resolución de DNS, estructuras de sockets

namespace TCP
{
    inline EventGroupHandle_t eventGroup = NULL;    // Grupo de eventos para manejar eventos de conexión y desconexión del cliente TCP

    struct config_s
    {
        uint16_t Port;                                      // Puerto por defecto para el servidor TCP        
        void (*ProcessData_func)(uint8_t * Data, int length);  // Funcion para procesar los datos recibidos por el cliente
        
        struct KeepAlive_s
        {
            int enabled;            // Activar el KeepAlive (0 = desactivado, 1 = activado)
            int idle;               // Tiempo en segundos para el KeepAlive
            int interval;           // Intervalo en segundos para el KeepAlive
            int count;              // Número de intentos para el KeepAlive
        } KeepAlive;
    };

    namespace Server
    {
        void init(config_s cfg);         // Inicializa el servidor TCP
        static void task(void *pvParameters);       // Tarea principal del servidor TCP
    }

    namespace Client
    {
        inline int socket = 0;      // Socket para manejar la conexión TCP con el cliente
        
        void init(sockaddr_storage address, socklen_t addr_len);    // Inicializa el cliente TCP
        void deinit();              // Destruye el cliente TCP
        void dataReception();                                       // Maneja los datos recibidos del cliente
    }
}
#endif