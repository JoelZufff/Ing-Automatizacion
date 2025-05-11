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

class TCP_client_t
{
private:    // CONSTANTES
    inline static const char *TAG = "TCP_client";   // Etiqueta para el registro de logs
    inline static const int BUF_SIZE = 512;         // Tamaño del buffer para recibir datos
    inline static const int PACKET_SIZE = 9;        // Tamaño del paquete de datos a enviar

public:    // CAMPOS
    inline static EventGroupHandle_t eventGroup = NULL;   // Grupo de eventos para manejar eventos de conexión y desconexión de clientes TCP
    int socket;                          // Socket para manejar la conexión TCP con el cliente

public:     // METODOS
    TCP_client_t(int socket, sockaddr_storage address, socklen_t addr_len);          // Constructor de la clase TCP_client
    ~TCP_client_t();            // Destructor de la clase TCP_client
    void dataReception();       // Maneja los datos recibidos del cliente
};

// =========================== Variables ============================ //
extern TCP_client_t* TCP_client;                        // Objeto cliente para manejar la conexión con el cliente

// ===================== Prototipos de funcion ====================== //
void TCP_init(TCP_server_config_s cfg);          // Inicializa el servidor TCP
//static void handleClientData(int sock);               // Maneja los datos recibidos del cliente
static void TCP_task(void *pvParameters);          // Tarea principal del servidor TCP

#endif