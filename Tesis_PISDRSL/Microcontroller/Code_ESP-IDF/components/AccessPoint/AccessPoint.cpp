// ============================ Librerias =========================== //
#include "AccessPoint.hpp"

// =========================== Constantes =========================== //
static const char *TAG = "AccessPoint";   // Etiqueta para el registro de logs

// ==================== Definicion de funciones ===================== //
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

void AP_init(AP_config_s cfg)     // Inicializamos el Access Point
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