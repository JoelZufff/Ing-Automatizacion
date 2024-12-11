#include <WiFi.h>

const char* ssid = "Hola";
const char* password = "123456789";

WiFiServer server(80);

#define LED2  2    // LED en terminal 2
#define SENSOR_X_PIN 34 // Pin ADC para LM35 X
#define SENSOR_THETA_PIN 35 // Pin ADC para LM35 Theta

String X_temp = "";
String THETA_temp = "";

void setup() 
{
  Serial.begin(115200);
  pinMode(LED2, OUTPUT);

  // Conecta a la red wifi.
  Serial.println();
  Serial.print("Conectando con ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("Conectado con WiFi.");
 
  // Inicio del Servidor web.
  server.begin();
  Serial.println("Servidor web iniciado.");

  // Esta es la IP
  Serial.print("Esta es la IP para conectar: ");
  Serial.print("http://");
  Serial.println(WiFi.localIP());
}
 
void loop() 
{
  // Leer sensores LM35
  float temp_X  = analogRead(SENSOR_X_PIN) / 10.0; // Convertir a voltaje
  float temp_THETA = analogRead(SENSOR_THETA_PIN) / 10.0; // Convertir a voltaje
  
  X_temp = String(temp_X, 1) + " °C";
  THETA_temp = String(temp_THETA, 1) + " °C";

  // Consulta si se ha conectado algún cliente.
  WiFiClient client = server.available();
  if (!client)
    return;
   
  Serial.print("Nuevo cliente: ");
  Serial.println(client.remoteIP());
   
  // Espera hasta que se reciban datos.
  delay(1000);
  
  // Leer entradas ADC y modificar variables 

  //////////////////////////////////////////////
  // Página WEB. ////////////////////////////

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); // Importante.
  client.println("<!DOCTYPE html>");
  client.println("<html>");
  client.println("<head><meta charset='UTF-8'>");
  client.println("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
  client.println("<title>Monitor de temperatura</title>");
  client.println("<style>");
  client.println("body {");
  client.println("font-family: Arial, sans-serif;");
  client.println("display: flex;");
  client.println("justify-content: center;");
  client.println("align-items: center;");
  client.println("height: 100vh;");
  client.println("margin: 0;");
  client.println("}");
  client.println(".container {");
  client.println("display: grid;");
  client.println("grid-template-columns: 1fr 1fr;");
  client.println("gap: 20px;");
  client.println("width: 80%;");
  client.println("max-width: 600px;");
  client.println("text-align: center;");
  client.println("}");
  client.println(".box {");
  client.println("padding: 20px;");
  client.println("background-color: #f3f3f3;");
  client.println("border: 1px solid #ccc;");
  client.println("border-radius: 8px;");
  client.println("}");
  client.println(".box h2 {");
  client.println("margin: 0 0 10px;");
  client.println("font-size: 24px;");
  client.println("}");
  client.println(".box p {");
  client.println("margin: 0;");
  client.println("font-size: 18px;");
  client.println("}");
  client.println("</style>");
  client.println("</head>");
  client.println("<body>");
  client.println("<div class='container'>");
  client.println("<div class='box'>");
  client.println("<h2>Temperatura X</h2>");
  client.println("<p>" + X_temp + "</p>");
  client.println("</div>");
  client.println("<div class='box'>");
  client.println("<h2>Temperatura Theta</h2>");
  client.println("<p>" + THETA_temp + "</p>");
  client.println("</div>");
  client.println("</div>");
  client.println("</body>");
  client.println("</html>");


  Serial.print("Cliente desconectado: ");
  Serial.println(client.remoteIP());
  client.flush();
  client.stop();
}
