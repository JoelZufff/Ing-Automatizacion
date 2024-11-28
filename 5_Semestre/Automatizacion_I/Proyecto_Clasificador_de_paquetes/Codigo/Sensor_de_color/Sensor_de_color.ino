// SENSOR DE COLOR
#define S0 2		      // S0 a pin 4
#define S1 4		      // S1 a pin 5
#define S2 16		      // S2 a pin 6
#define S3 17		      // S3 a pin 7
#define color_signal 5	  // color_signal a pin 8

// Señales de salida
#define BLACK 22       // BLACK a pin 9
#define WHITE 23      // WHITE a pin 10

void setup()
{
  // Configuramos entradas y salidas de sensor de color
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(color_signal, INPUT);

  // Configuramos entradas y salidas para PLC
  pinMode(BLACK, OUTPUT);
  pinMode(WHITE, OUTPUT);
  
  // Establecemos frecuencia de salida al 20% (Divide por 5)
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  Serial.begin(115200);		// Inicializamos monitor seriial a 9600 bauds
}

void loop() 
{
  
  // VER FORMA DE REDUCIR DELAYS, ver valores maximos valores de cada color

  // Filtro rojo
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);

  int red = pulseIn(color_signal, LOW);	// obtiene duracion de pulso de salida del sensor
  delay(200);				// demora de 200 mseg
  
  // Filtro verde
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);

  int green = pulseIn(color_signal, LOW);	// obtiene duracion de pulso de salida del sensor
  delay(200);				// demora de 200 mseg
  
  // Filtro azul
  digitalWrite(S2,LOW);			// establece fotodiodos
  digitalWrite(S3,HIGH);		// con filtro azul
  
  int blue = pulseIn(color_signal, LOW);	// obtiene duracion de pulso de salida del sensor
  delay(200);				// demora de 200 mseg

  // Ya tenemos los valores de cada color

  if(red < 300 && green < 300 && blue < 300)
  {
    digitalWrite(WHITE,HIGH);
    digitalWrite(BLACK,LOW);
    Serial.println("BLANCO");			// muestra valor de variable blue
  }
  else
  {
    digitalWrite(BLACK,HIGH);
    digitalWrite(WHITE,LOW);
    Serial.println("NEGRO");			// muestra valor de variable blue
  }
  /*
  Serial.print("R:");			// muestra texto
  Serial.print(red);			// muestra valor de variable red

  Serial.print("\t");			// espacio de tabulacion

  Serial.print("G:");			// muestra texto
  Serial.print(green);			// muestra valor de variable green

  Serial.print("\t");			// espacio de tabulacion

  Serial.print("B:");			// muestra texto
  Serial.println(blue);			// muestra valor de variable blue
  */
}