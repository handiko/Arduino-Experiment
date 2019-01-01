#include <TinyGPS++.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps;
SoftwareSerial ss = SoftwareSerial(8, 9);

void setup() {
  pinMode(0, INPUT);
  pinMode(1, OUTPUT);

  pinMode(8, INPUT);
  pinMode(9, OUTPUT);

  Serial.begin(115200);
  ss.begin(9600);

  Serial.println("GPS Receiver started !\n");
}

void loop() {
  while(ss.available() > 0)
  {
    if(gps.encode(ss.read()))
    {
      disp();
    }
  }

  delay(500);
}

void DegreesToDegMinSec(float x)
{
  bool isPositive;

  int degree, minutes, seconds;

  if(x > 0)
    isPositive = 1;
  else
    isPositive = 0;

  x = abs(x);

  minutes = (x * 3600) / 60;
  seconds = (int)(x * 3600) % 60;

  degree = minutes / 60;
  minutes = minutes % 60;

  if(!isPositive)
    degree *= -1;

  Serial.print(degree);
  Serial.print(' ');
  Serial.print(minutes);
  Serial.print(' ');
  Serial.print(seconds);
  Serial.print(' ');
}


void disp(void)
{
  int dd;
  int mm;
  float sec;

  float f;
  float mm_remainder;
  
  if(gps.location.isValid())
  {
    f = gps.location.lat();
    
    Serial.print(f, 8);
    Serial.print(' ');
  }

  Serial.print(' ');
  
  if(gps.altitude.isValid())
  {
    Serial.print(gps.altitude.meters());
  }

  Serial.println(' ');
}
