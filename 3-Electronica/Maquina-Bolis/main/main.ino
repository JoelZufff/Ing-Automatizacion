/* CONEXION CON UBIDOTS 
#include <UbidotsEsp32Mqtt.h>

const char *UBIDOTS_TOKEN = "BBUS-tmHquEwFfXpDlUPYtG7X6STs3ph5wQ";

const char *WIFI_SSID = "ALEXA";     
const char *WIFI_PASS = "1152227193_ZF";     

const char *DEVICE_LABEL = "ESP32";

const char *VARIABLE_LABEL_1 = "diode_temp";
const char *VARIABLE_LABEL_2 = "lm35_temp";

const unsigned int PUBLISH_FREQUENCY = 60000;

unsigned long web_timer = 0; 
Ubidots ubidots(UBIDOTS_TOKEN);

*/
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

const int solenoide_PIN = 12, pump_PIN = 4, led_PIN = 2;


/* -------------------- Configuraciones Inciales ------------------- */
void setup()
{
  /*Iniciamos el terminal Serial a 115200 baudios*/
  Serial.begin(115200);

  // Imprimimos el siguiente texto para asegurar el encendido del circuito
  Serial.println("MAQUINA DE BOLIS");
  
  pinMode(solenoide_PIN, OUTPUT);
  pinMode(pump_PIN, OUTPUT);
  pinMode(led_PIN, OUTPUT);
  
  //lcd.begin(20, 4, 1);
  lcd.backlight();
  lcd.clear();

  lcd.print("DISPENSADOR DE BONICE");
  
  digitalWrite(solenoide_PIN, HIGH);
  digitalWrite(led_PIN, HIGH);
  delay(7000);
  digitalWrite(solenoide_PIN, LOW);
  digitalWrite(led_PIN, LOW);

  digitalWrite(pump_PIN, HIGH);
  delay(5000);
  digitalWrite(pump_PIN, LOW);
  
  digitalWrite(solenoide_PIN, HIGH);
  digitalWrite(led_PIN, HIGH);
  delay(7000);
  digitalWrite(solenoide_PIN, LOW);
  digitalWrite(led_PIN, LOW);
  
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
