// ============================ Librerias =========================== //
#include "TCP_server.hpp"

// =========================== Constantes =========================== //
static const char *TAG = "TCP_server";  // Etiqueta para el registro de logs
static TCP_server_config_s config;      // Configuración del servidor TCP
TCP_client_t* TCP_client = NULL;        // Objeto cliente para manejar la conexión con el cliente


// ==================== Definicion de funciones ===================== //
void TCP_init(TCP_server_config_s cfg) // Inicializa el servidor TCP
{
    config = cfg;   // Asignamos la configuración del servidor TCP

    // Creamos el grupo de eventos para manejar eventos de conexión y desconexión del cliente TCP.
    TCP_client_t::eventGroup = xEventGroupCreate();
    if( TCP_client_t::eventGroup == NULL )            // Si la creacion del evento falló, mostramos un error
    {
        ESP_LOGE(TAG, "Fallo la creación del Event Group");
        return;
    }
    
    // Creamos la tarea del servidor TCP, que se encargará de aceptar conexiones y manejar la comunicación con los clientes.
    xTaskCreate(TCP_task, "TCP_server", 4096, (void*)AF_INET, 2, NULL);
    vTaskDelay(pdMS_TO_TICKS(10));       // Esperamos un poco para asegurarnos de que la tarea se haya creado correctamente
}

static void TCP_task(void *pvParameters)
{
    int ip_protocol = 0;
    int addr_family = (int)pvParameters;
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

    // Creamos un socket de escucha para aceptar conexiones de clientes.
        int listen_sock = socket(addr_family, SOCK_STREAM, ip_protocol);
        if (listen_sock < 0)            // Si falla, se imprime el error y se elimina la tarea
        {
            ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
            vTaskDelete(NULL);
        }
        int opt = 1;
        setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));       // Permitimos reutilizar la dirección local si el socket se cierra y se vuelve a abrir rápidamente (evita el error "address already in use").   

    // Asociamos al socket a la direccion ip y el puerto. 
        int err = bind(listen_sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
        if (err != 0)       // Si falla el bind, imprime error y salta al final para limpiar recursos. 
        {
            ESP_LOGE(TAG, "Socket unable to bind: errno %d", errno);
            ESP_LOGE(TAG, "IPPROTO: %d", addr_family);
            goto CLEAN_UP;
        }

    // El socket se prepara para escuchar conexiones entrantes en el puerto definido por PORT.
        err = listen(listen_sock, 1);
        if (err != 0)     // Si falla el listen, imprime error y salta al final para limpiar recursos.
        {
            ESP_LOGE(TAG, "Error occurred during listen: errno %d", errno);
            goto CLEAN_UP;
        }
    
    while (true)          // El servidor entra en un bucle infinito esperando conexiones de clientes.
    {
        ESP_LOGI(TAG, "Esperando conexiones -> PUERTO: %d", config.Port);
        
        sockaddr_storage source_addr;               // Large enough for both IPv4 or IPv6
        socklen_t addr_len = sizeof(source_addr);
        
        // Se detiene el codigo hasta detectar la llegada de un cliente. Al aceptar la conexion, se crea un nuevo socket para manejar la comunicacion con el.
        int socket = accept(listen_sock, (struct sockaddr *)&source_addr, &addr_len);
        if (socket < 0)       // Si falla la conexion con el cliente, imprime error y salta al final para limpiar recursos.
        {
            ESP_LOGE(TAG, "Unable to accept connection: errno %d", errno);
            break;
        }

        // Se crea un nuevo objeto cliente para manejar la comunicacion con el cliente.
        TCP_client = new TCP_client_t(socket, source_addr, addr_len);
        
        // Se entra en un bucle esperando datos del cliente
        TCP_client->dataReception();

        // Apagamos el socket de conexión y lo cerramos. Depues de la desconexión del cliente.
        delete TCP_client;                          // Liberamos la memoria del objeto cliente.
    }

CLEAN_UP:       // Cierra el socket de escucha y elimina la tarea si hubo error en alguna parte.
    close(listen_sock);
    vTaskDelete(NULL);
}

TCP_client_t::TCP_client_t(int socket, sockaddr_storage address, socklen_t addr_len) : socket(socket) // Constructor de la clase TCP_client
{       
    int keepAlive = 1;
    int keepIdle = config.KeepAliveIdle;
    int keepCount = config.KeepAliveCount;
    int keepInterval = config.KeepAliveInterval;

    // Se concreto la conexion con el cliente, se configura para que el servidor verifique si el cliente sigue conectado, incluso si no hay datos circulando.
    setsockopt(socket, SOL_SOCKET, SO_KEEPALIVE, &keepAlive, sizeof(int));
    setsockopt(socket, IPPROTO_TCP, TCP_KEEPIDLE, &keepIdle, sizeof(int));
    setsockopt(socket, IPPROTO_TCP, TCP_KEEPINTVL, &keepInterval, sizeof(int));
    setsockopt(socket, IPPROTO_TCP, TCP_KEEPCNT, &keepCount, sizeof(int));

    // Convierte la IP del cliente a string e imprime la IP.
    char addr_str[128];
    if (address.ss_family == PF_INET)
        inet_ntoa_r(((struct sockaddr_in *)&address)->sin_addr, addr_str, sizeof(addr_str) - 1);
    ESP_LOGI(TAG, "Conexion establecida en socket con IP: %s", addr_str);
}

TCP_client_t::~TCP_client_t()       // Apagamos el socket de conexión y lo cerramos.
{
    shutdown(socket, 0);
    close(socket);
}

void TCP_client_t::dataReception()
{
    // Comunicamos la conexion del cliente al grupo de eventos
    xEventGroupSetBits( eventGroup, 0x1 );

    // Se asigna el socket de conexión a la variable global para su uso posterior
    char rx_buffer[BUF_SIZE];
    
    // Ciclo para recibir datos del cliente
    int data_length;
    do
    {
        // Se bloquea el código hasta recibir datos del cliente.
        data_length = recv(socket, rx_buffer, sizeof(rx_buffer), 0);

        if (data_length > 0)       // Se recibieron datos validos
        {
            rx_buffer[data_length] = 0; // Null-terminate whatever is received and treat it like a string
            ESP_LOGI(TAG, "Received %d bytes: %s", data_length, rx_buffer);
        }
        else if (data_length == 0)  // El cliente cerró la conexión, se imprime un mensaje y se apagan los motores. (PENDIENTE) 
            ESP_LOGW(TAG, "Connection closed");
        else                // Error en la recepción de datos, se imprime un mensaje de error. 
            ESP_LOGE(TAG, "Error occurred during receiving: errno %d", errno);

    } 
    while (data_length > 0);        // Mientras haya datos validos y no se haya cerrado la conexión

    // Comunicamos la desconexion del cliente al grupo de eventos
    xEventGroupClearBits( eventGroup, 0x1 );
}
