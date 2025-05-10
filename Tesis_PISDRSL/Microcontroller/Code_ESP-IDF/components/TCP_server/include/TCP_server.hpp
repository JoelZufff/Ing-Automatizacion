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

// =========================== Estructuras ========================== //
struct TCP_server_config_s
{
    uint16_t Port;                  // Puerto por defecto para el servidor TCP
    int KeepAliveIdle;          // Tiempo en segundos para el KeepAlive
    int KeepAliveInterval;      // Intervalo en segundos para el KeepAlive
    int KeepAliveCount;         // Número de intentos para el KeepAlive
};

// ===================== Prototipos de funcion ====================== //
void TCP_server_init(TCP_server_config_s cfg);          // Inicializa el servidor TCP
static void handleClientData(int sock);                 // Maneja los datos recibidos del cliente
static void TCPServerTask(void *pvParameters);          // Tarea principal del servidor TCP

#endif