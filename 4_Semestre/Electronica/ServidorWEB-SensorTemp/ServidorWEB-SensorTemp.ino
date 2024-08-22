/* CONEXION CON UBIDOTS 
#include <UbidotsEsp32Mqtt.h>

const char *UBIDOTS_TOKEN = "BBUS-tmHquEwFfXpDlUPYtG7X6STs3ph5wQ";

const char *WIFI_SSID = "ALEXA";     
const char *WIFI_PASS = "1152227193_ZF";     

const char *DEVICE_LABEL = "ESP32";

const char *VARIABLE_LABEL_1 = "diode_temp";
const char *VARIABLE_LABEL_2 = "lm35_temp";

const unsigned int PUBLISH_FREQUENCY = 60000;

unsigned long timer; 
Ubidots ubidots(UBIDOTS_TOKEN);

*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int flowmeter_pin = 27;

/* -------------------- Configuraciones Inciales ------------------- */
void setup()
{
  attachInterrupt(flowmeter_pin, flowmeter_function, RISING);
  
  /*Iniciamos el terminal Serial a 115200 baudios*/
  Serial.begin(115200);

  /*Imprimimos el siguiente texto para asegurar el encendido del circuito*/
  Serial.println("MAQUINA DE BOLIS");

  /*
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setup();
  ubidots.reconnect();
  timer = millis();
   */
}

/* ------------------------- Bucle Infinito ------------------------ */
void loop()
{
  
  /* CONEXION CON UBIDOTS
  /*Definimos que, si no se conecta a la plataforma Ubidots, se pasa la función Reconnect() para volver a establecer la conexión
  if (!ubidots.connected())
    ubidots.reconnect();
    
  if (abs(millis() - timer) > PUBLISH_FREQUENCY) 
  {
    /* Accion que se realizara a cada PUBLISH_FREQUENCY ms

    /*VER SI JALA AQUI ADENTRO Agregamos un delay de 10 segundos para el envío, y que luego de este tiempo, se proceda a reiniciar el bucle
    delay(10000);
    ubidots.loop();
  }
  */
}
