// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

float x = -1.0;
float y = 1.0;
float z = 0.0;
float dt = 0.01;

const float a = 1.0;
const float b = 3.0;
const float c = 1.0;
const float d = 5.0;
const float r = 0.0021;
const float s = 4.0;
const float xr = -8.0/5.0;
float I = 3.0;
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
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  I = tomapfloat(sensorValue, 0, 1023, 1.5, 5);




  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  
  i++;
  float x_new, y_new, z_new, f, g, h;

  f = y - a * x*x*x + b * x*x + I - z;
  g = c - d * x*x - y;
  h = r*( s*(x-xr) - z );

  x_new = x + f * dt;
  y_new = y + g * dt;
  z_new = z + h * dt;

  x = x_new;
  y = y_new;
  z = z_new;

  outputValue = mapfloat(x, -3, 3, 0, 255);
  
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);


    // print the results to the Serial Monitor:
  //Serial.print("sensor = ");
  //Serial.print(sensorValue);
  if (i % 10 == 0) {
    //analogWrite(analogOutPin, outputValue);
    /*Serial.println(outputValue);
    delay(1);*/
  }
  
}
