// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

float x = -47;
float y = 0.02;
float dt = 0.1;

const float a = 0.02;
const float b = 0.2;
const float c = -50.0;
const float d = 2.0;
float I = 10;
int i = 0;

int mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
 return (int)((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

float tomapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // Lectura del pin del potenciometro
  sensorValue = analogRead(analogInPin);
  // Tranformación para obtener el valor real leido del potenciometro
  I = tomapfloat(sensorValue, 0, 1023, 0, 20);

  // Integracion del modelo
  
  i++;
  float x_new, y_new, f, g;

  f = 0.04*x*x + 5*x + 140 - y + I;
  g = a*(b*x - y);
  
  x_new = x + f * dt;
  y_new = y + g * dt;

  if(x_new >= 30){
    x_new = c;
    y_new = y_new + d;
  }
  
  x = x_new;
  y = y_new;

   //Serial.println(x); // Para comprobar validez del valor de la variable

  // Tranformación para pin de salida
  outputValue = mapfloat(x, -90, 45, 0, 255);
 
  // Escritura al pin de salida
  analogWrite(analogOutPin, outputValue);

  // Espera al siguiente periodo de calculo. 5 ms
  delay(5);  
}
