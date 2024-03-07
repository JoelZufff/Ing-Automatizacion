#include <UbidotsEsp32Mqtt.h>
/*Definimos que el Pin de Datos del sensor estará conectado al pin 23 del ESP32*/

/*Definimos primero el Token que nos brinda la plataforma Ubidots para hacer la conexión*/
const char *UBIDOTS_TOKEN = "BBUS-tmHquEwFfXpDlUPYtG7X6STs3ph5wQ";
/*Definimos SSID y PASSWORD de nuestra red WiFi*/
const char *WIFI_SSID = "SensorTemperatura";     
const char *WIFI_PASS = "sensorsensor";     
/*Definimos el nombre de nuestro dispositivo, el cual aparecerá en la plataforma Ubidots*/
const char *DEVICE_LABEL = "ESP32";
/*Definimos las variables que se medirán y que serán publicadas en la plataforma Ubidots*/
const char *VARIABLE_LABEL_1 = "temp";
/*Definimos la frecuencia de publicación de 5 segundos*/
const int PUBLISH_FREQUENCY = 5000;

const int sensorPIN = 32;
 
/*Definimos unas variables extra, que incluye la librería*/
unsigned long timer; 
/*Definimos que las variables de la librería UBIDOTS trabajarán con el Token*/
Ubidots ubidots(UBIDOTS_TOKEN);

/*Definimos la función Setup() para iniciar nuestro circuito*/
void setup()
{
  /*Iniciamos el terminal Serial a 115200*/
  Serial.begin(115200);     
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setup();
  ubidots.reconnect();

  timer = millis();
  
  /*Imprimimos el siguiente texto para asegurar el encendido del circuito*/
  Serial.println("Medición inciada");
}

/*Iniciamos el bucle de la función Loop()*/
void loop()
{
  /*Definimos que, si no se conecta a la plataforma Ubidots, se pasa la función Reconnect() para volver a establecer la conexión*/
  if (!ubidots.connected())
    ubidots.reconnect();
    
  /*En esta condicional, iniciamos la medición de Temperatura y Humedad del sensor, y la información será enviada a la Plataforma*/
  if (abs(millis() - timer) > PUBLISH_FREQUENCY) 
  {
    /*Hacemos la medición de Temperatura y Humedad del sensor, y lo definimos en variables Float */
    float t = analogRead(sensorPIN) * 33.0 / 4095.0;
    
    /*Definimos que el valor de Temperatura será enviado por la variable 1, a la plataforma Ubidots*/
    ubidots.add(VARIABLE_LABEL_1, t);
    /*Hacemos la publicación de los datos en el dispositivo definido*/
    ubidots.publish(DEVICE_LABEL);
    /*Para mostrar los datos, los imprimimos en el terminal Serial*/
    Serial.println("Enviando los datos a Ubidots: ");
    Serial.println("Temperatura: " + String(t));
    Serial.println("-----------------------------------------");
    timer = millis();
  }
  /*Agregamos un delay de 10 segundos para el envío, y que luego de este tiempo, se proceda a reiniciar el bucle*/
  delay(10000);
  ubidots.loop();
}
