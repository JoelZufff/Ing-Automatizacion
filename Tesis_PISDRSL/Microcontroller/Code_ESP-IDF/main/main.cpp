// ============================ Librerias =========================== //
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_timer.h"

#include "L298N.hpp"
#include "MPU6050.hpp"

#include "esp_wifi.h"      // Configuración y control del Wi-Fi (iniciar, conectar, modo AP/STA, etc.)
#include "esp_mac.h"       // Manejo de direcciones MAC del ESP32 (útil para identificar el dispositivo en la red)
#include "esp_system.h"    // Información del sistema, reinicio, chip ID, etc. (puede ser indirectamente útil)
#include "esp_event.h"     // Manejo del sistema de eventos, como eventos de conexión Wi-Fi
#include "esp_log.h"       // Registro de logs, útil para depurar funciones relacionadas al Wi-Fi
#include "nvs_flash.h"     // Almacenamiento persistente (para guardar configuración Wi-Fi como credenciales)

#include "lwip/err.h"      // Manejo de errores de la pila TCP/IP (LwIP)
#include "lwip/sockets.h"  // Funciones de sockets para comunicación por red (TCP/UDP)
#include "lwip/sys.h"      // Utilidades del sistema para LwIP
#include <lwip/netdb.h>    // Resolución de DNS, estructuras de sockets


// =========================== Constantes =========================== //
static const char *TAG = "Main";

#define BUF_SIZE 512
#define PACKET_SIZE 9

// ============================= Clases ============================= //
class TCP_server_t
{
private:    // CONSTANTES
    inline static const char *TAG = "TCP_server";   // Etiqueta para el registro de logs

public:     // ESTRUCTURAS
    struct config_s
    {
        uint16_t Port;                  // Puerto por defecto para el servidor TCP
        uint8_t KeepAliveIdle;          // Tiempo en segundos para el KeepAlive
        uint8_t KeepAliveInterval;      // Intervalo en segundos para el KeepAlive
        uint8_t KeepAliveCount;         // Número de intentos para el KeepAlive
    };

private:    // CAMPOS
    inline static config_s config = {0, 0, 0, 0};
    inline static EventGroupHandle_t TcpEventGroup = nullptr;   // Grupo de eventos para manejar eventos de conexión y desconexión de clientes TCP
    
    inline static int connection_sock = 0;              // Socket para manejar la conexión TCP con el cliente

public:     // METODOS
    TCP_server_t() {}

    void init(config_s cfg) // Inicializa el servidor TCP
    {
        // Asignamos los parámetros de configuración del servidor TCP
        config = cfg;

        // Creamos un Event Group de FreeRTOS para señalizar eventos TCP (p.ej. cliente conectado, datos recibidos)
            TcpEventGroup = xEventGroupCreate();
            if( TcpEventGroup == NULL )            // Si la creacion del evento falló, mostramos un error
            {
                ESP_LOGE(this->TAG, "Fallo la creación del Event Group");
                return;
            }

        // Creamos la tarea del servidor TCP, que se encargará de aceptar conexiones y manejar la comunicación con los clientes.
            xTaskCreate(task_manager, "tcp_server", 4096, (void*)AF_INET, configMAX_PRIORITIES - 2, NULL);
    }
    
private:
    static void task_manager(void *pvParameters)
    {
        char addr_str[128];
        int addr_family = (int)pvParameters;
        int ip_protocol = 0;
        int keepAlive = 1;
        int keepIdle = config.KeepAliveIdle;
        int keepCount = config.KeepAliveCount;
        int keepInterval = config.KeepAliveInterval;
        struct sockaddr_storage dest_addr;

        // Configuramos la dirección IP del servidor para aceptar conexiones en cualquier IP local (INADDR_ANY) y en el puerto definido por PORT.
            if (addr_family == AF_INET)
            {
                struct sockaddr_in *dest_addr_ip4 = (struct sockaddr_in *) &dest_addr;
                dest_addr_ip4->sin_addr.s_addr = htonl(INADDR_ANY);
                dest_addr_ip4->sin_family = AF_INET;
                dest_addr_ip4->sin_port = htons(config.Port);
                ip_protocol = IPPROTO_IP;
            }

        // Creamos un socket TCP para escuchar conexiones entrantes. El socket se configura para IPv4 o IPv6 según la configuración del sistema.
            int listen_sock = socket(addr_family, SOCK_STREAM, ip_protocol);
            if (listen_sock < 0)            // Si falla, se imprime el error y se elimina la tarea
            {
                ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
                vTaskDelete(NULL);
                return;
            }

        // Permitimos reutilizar la dirección local si el socket se cierra y se vuelve a abrir rápidamente (evita el error "address already in use").
            int opt = 1;
            setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
            ESP_LOGI(TAG, "Socket created");

        // Asociamos  el socket a la IP y puerto definidos. 
            int err = bind(listen_sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
            if (err != 0)       // Si falla el bind, imprime error y salta al final para limpiar recursos. 
            {
                ESP_LOGE(TAG, "Socket unable to bind: errno %d", errno);
                ESP_LOGE(TAG, "IPPROTO: %d", addr_family);
                goto CLEAN_UP;
            }
            ESP_LOGI(TAG, "Socket bound, port %d", config.Port);

        // El socket entra en modo de escucha, aceptando 1 conexión a la vez
            err = listen(listen_sock, 1);
            if (err != 0)     // Si falla el listen, imprime error y salta al final para limpiar recursos.
            {
                ESP_LOGE(TAG, "Error occurred during listen: errno %d", errno);
                goto CLEAN_UP;
            }

        while (true)          // El servidor entra en un bucle infinito aceptando conexiones de clientes.
        {
            ESP_LOGI(TAG, "Socket listening");

            // Espera y acepta una nueva conexión entrante.
                struct sockaddr_storage source_addr;
                socklen_t addr_len = sizeof(source_addr);
                int sock = accept(listen_sock, (struct sockaddr *)&source_addr, &addr_len);
                if (sock < 0)                       // Si falla la aceptación de la conexión, imprime error y sale del bucle. 
                {
                    ESP_LOGE(TAG, "Unable to accept connection: errno %d", errno);
                    break;
                }

            // Configura la conexión para que el servidor verifique si el cliente sigue conectado, incluso si no hay datos circulando.
                setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, &keepAlive, sizeof(int));
                setsockopt(sock, IPPROTO_TCP, TCP_KEEPIDLE, &keepIdle, sizeof(int));
                setsockopt(sock, IPPROTO_TCP, TCP_KEEPINTVL, &keepInterval, sizeof(int));
                setsockopt(sock, IPPROTO_TCP, TCP_KEEPCNT, &keepCount, sizeof(int));
            
            // Convierte la IP del cliente a string e imprime la IP.
                if (source_addr.ss_family == PF_INET) {
                    inet_ntoa_r(((struct sockaddr_in *)&source_addr)->sin_addr, addr_str, sizeof(addr_str) - 1);
                }
                ESP_LOGI(TAG, "Socket accepted ip address: %s", addr_str);

            // Procesamos los datos recibidos del cliente
                received_data(sock);

            // Cerramos la conexión con el cliente después de recibir los datos
                shutdown(sock, 0);
                close(sock);
        }

        CLEAN_UP:       // Cierra el socket principal y elimina la tarea si hubo error en alguna parte.
            close(listen_sock);
            vTaskDelete(NULL);
    }

    static void received_data(int sock)
    {
        xEventGroupSetBits( TcpEventGroup, 0x1 );     // Marcamos en un Event Group (mecanismo de sincronización de FreeRTOS) que la conexión TCP está activa.

        connection_sock = sock;
        char rx_buffer[BUF_SIZE];
        
        int len;
        do 
        {
            len = recv(sock, rx_buffer, sizeof(rx_buffer), 0);
            
            if (len < 0)        // Hubo un error al recibir datos, se imprime el error y se apagan los motores (PENDIENTE) 
                ESP_LOGE(TAG, "Error occurred during receiving: errno %d", errno);
            else if (len == 0)  // El cliente cerró la conexión, se imprime un mensaje y se apagan los motores. (PENDIENTE) 
                ESP_LOGW(TAG, "Connection closed");
            else                // Se  recibieron datos 
            {
                // Manejar los datos recibidos
                printf("Longitud: %i\t", len);      // Imprimimos la longitud de los datos recibidos
                
                for(int i = 0; i<len; i++)          // Recorremos el buffer de datos recibidos
                    printf("%i",rx_buffer[i]);

                printf("\r\n");                     // Imprimimos un salto de línea
            }

        } 
        while (len > 0);

        xEventGroupClearBits( TcpEventGroup, 0x1 );
    }
};

class Access_Point_t
{
private:    // CONSTANTES
    //inline static const char *TAG = "WiFi_AP";   // Etiqueta para el registro de logs
    
public:     // ESTRUCTURAS
    struct config_s
    {
        const char* ssid;            // Nombre de la red (SSID)
        const char* password;             // Contraseña de la red
        int channel;                 // Canal de radio (1-13) que usará el AP
        int maxconn;                 // Número máximo de clientes simultáneos que podrán conectarse al AP (1-10)
    };

public:     // CAMPOS
    TCP_server_t TcpServer;                         // Instancia de la clase TCP_server_t para manejar la comunicación TCP

    Access_Point_t() {}

    void init(config_s cfg)     // Inicializamos el Access Point
    {
        esp_err_t ret = nvs_flash_init();                   // Inicializa la NVS (Non-Volatile Storage), para almacenar credenciales de Wi-Fi

        // Si la partición NVS está llena o la versión de NVS ha cambiado, borra la flash con nvs_flash_erase() y vuelve a inicializarla para evitar conflictos
            if(ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
            {
                ESP_ERROR_CHECK(nvs_flash_erase());
                ESP_ERROR_CHECK(nvs_flash_init());
            }

        ESP_ERROR_CHECK(esp_netif_init());                  // Inicializamos la capa de redes esp-netif, que gestiona interfaces de red (Wi-Fi, Ethernet, etc.)        
        ESP_ERROR_CHECK(esp_event_loop_create_default());   // Creamos el loop de eventos por defecto donde se publican/escuchan eventos del sistema (Wi-Fi, IP, etc.).
        esp_netif_create_default_wifi_ap();                 // Creamos la interfaz de red por defecto en modo AP (Access Point). Configura internamente un esp-netif con la pila LwIP.

        // Obtenemos la configuración por defecto para el controlador Wi-Fi y lo inicializa. Aquí se cargan parámetros internos (colas, buffers, etc.)
            wifi_init_config_t defconf = WIFI_INIT_CONFIG_DEFAULT();
            ESP_ERROR_CHECK(esp_wifi_init(&defconf));
        
        // Registramos la función event_handler para manejar todos los eventos del módulo Wi-Fi (llegada de clientes, desconexiones, errores, etc.).
            ESP_ERROR_CHECK(esp_event_handler_instance_register
            (
                WIFI_EVENT,
                ESP_EVENT_ANY_ID,
                &event_handler,
                NULL,
                NULL
            ));

        wifi_config_t wifi_config = {0};

        strcpy((char *)wifi_config.ap.ssid, (const char *) cfg.ssid);        // Asignamos el nombre de red (SSID)
        wifi_config.ap.ssid_len = strlen((const char *) cfg.ssid);           // Asignamos la longitud del nombre de red (SSID)
        wifi_config.ap.channel = cfg.channel;                                // Asignamos el canal de radio (1–13) que usará el AP.
        strcpy((char *)wifi_config.ap.password, (const char *) cfg.password);     // Asignamos el password de la red
        wifi_config.ap.max_connection = cfg.maxconn;                         // Asignamos el número máximo de clientes simultáneos que podrán conectarse al AP (1-10).        

        #ifdef CONFIG_ESP_WIFI_SOFTAP_SAE_SUPPORT                       // Si hay soporte WPA3-SAE, usamos WIFI_AUTH_WPA3_PSK y activa SAE Protected Password Exchange
            wifi_config.ap.authmode = WIFI_AUTH_WPA3_PSK;
            wifi_config.ap.ssid_hidden = false;
            wifi_config.ap.sae_pwe_h2e = WPA3_SAE_PWE_BOTH;
        #else                                                           // Sino usamos el más común WIFI_AUTH_WPA2_PSK
            wifi_config.ap.authmode = WIFI_AUTH_WPA2_PSK;
        #endif

        wifi_config.ap.pmf_cfg.required = true;                         // Activamos PMF (Protected Management Frames) para proteger la señalización de gestión contra ataques.        
        
        // Si la contraseña está vacía, cambiamos a modo abierto (WIFI_AUTH_OPEN)
            if (strlen((const char *) cfg.password)== 0) 
                wifi_config.ap.authmode = WIFI_AUTH_OPEN;

        ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));               // Configuramos el chip Wi-Fi en modo solo Punto de Acceso.        
        ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config)); // Asignamos a la interfaz AP la configuración que acabamos de rellenar en wifi_config 
        ESP_ERROR_CHECK(esp_wifi_start());                              // Iniciamos el controlador Wi-Fi, que comienza a emitir el SSID y espera conexiones de clientes.

        ESP_LOGI(TAG, "Red inicializada -> SSID: %s | Password: %s | Channel: %d", cfg.ssid, cfg.password, cfg.channel);      // Imprimimos por consola los datos de la red
    }

    private:
    static void event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data)  // Funcion para manejar eventos de Wi-Fi (conexiones, desconexiones, errores, etc.)
    {
        if (event_id == WIFI_EVENT_AP_STACONNECTED)                 // Detectamos conexion de usuario al Access Point
        {
            wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
            ESP_LOGI(TAG, "CONEXION de "MACSTR"\nAID = %d", MAC2STR(event->mac), event->aid);
        }
        else if (event_id == WIFI_EVENT_AP_STADISCONNECTED)         // Detectamos desconexion de usuario del Access Point 
        {
            wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
            ESP_LOGI(TAG, "DESCONEXION de "MACSTR"\nAID = %d", MAC2STR(event->mac), event->aid);
            // Apagar motor si se desconecta el cliente
        }
    }
};
// ======================= Variables Globales ======================= //
Access_Point_t  Access_Point;       // Instancia de la clase Access_Point_t para manejar el Access Point
L298N_t         L298N;              // Instancia de la clase L298N_t para manejar los motores DC

// ========================= Interrupciones ========================= //

// =========================== Funciones ============================ //

// ======================== Codigo Principal ======================== //
extern "C" void app_main(void)
{
    // Inicializamos el Access Point
        Access_Point_t::config_s AP_config = 
            { .ssid = "AP_Balancin", .password = "123456789", .channel = 1, .maxconn = 1 };
        Access_Point.init(AP_config);

    /* FALTA CORREGIRLO
    // Inicializamos el servidor TCP
        const TCP_server_t::config_s TCP_config = 
            { .Port = 4545, .KeepAliveIdle = 5, .KeepAliveInterval = 5, .KeepAliveCount = 3 };
        Access_Point.TcpServer.init(TCP_config);
    */

    // Inicializamos Puente H y Encoder de motor izquierdo
        DC_motor_t::config_s LeftMotor_cfg = 
            { .EN_pin = GPIO_NUM_14, .IN1_pin = GPIO_NUM_5, .IN2_pin = GPIO_NUM_4 };
        L298N.LeftMotor.init(LeftMotor_cfg);

        Encoder_t::config_s LeftMotor_Encoder_cfg = 
            { .FaseA_pin = GPIO_NUM_19, .FaseB_pin = GPIO_NUM_18 };
        L298N.LeftMotor.Encoder.init(LeftMotor_Encoder_cfg);

    // Inicializamos Puente H y Encoder de motor derecho
        const DC_motor_t::config_s RightMotor_cfg = 
            { .EN_pin = GPIO_NUM_27, .IN1_pin = GPIO_NUM_2, .IN2_pin = GPIO_NUM_15 };
        L298N.RightMotor.init(RightMotor_cfg);

        Encoder_t::config_s RightMotor_Encoder_cfg = 
            { .FaseA_pin = GPIO_NUM_33, .FaseB_pin = GPIO_NUM_32 };
        L298N.RightMotor.Encoder.init(RightMotor_Encoder_cfg);

    // Falta comunicacion i2c con MPU6050
    // Falta inicializacion de sensores TCRT5000

    while (true)
    {
        //*/
        for(uint16_t i = 0; i < MAX_DUTY_CYCLE; i++)
        {
            L298N.LeftMotor.set_movement(i, FORWARD);       // Establecemos el movimiento del motor izquierdo
            L298N.RightMotor.set_movement(i, FORWARD);      // Establecemos el movimiento del motor derecho

            vTaskDelay(pdMS_TO_TICKS(10));
        }
        //*/
    }    
}