/*
 * 
 */
#include <SoftwareSerial.h>

SoftwareSerial dorji(8,9);

void dorji_init(SoftwareSerial &ser);
void dorji_reset(SoftwareSerial &ser);
void dorji_setfreq(float txf, float rxf, SoftwareSerial &ser);
void dorji_readback(SoftwareSerial &ser);

void dorji_init(SoftwareSerial &ser)
{
  ser.println("AT+DMOCONNECT");
}

void dorji_reset(SoftwareSerial &ser)
{
  for(char i=0;i<3;i++)
    ser.println("AT+DMOCONNECT");
}

void dorji_setfreq(float txf, float rxf, SoftwareSerial &ser)
{
  ser.print("AT+DMOSETGROUP=0,");
  ser.print(txf, 4);
  ser.print(',');
  ser.print(rxf, 4);
  ser.println(",0000,0,0000");
}

void dorji_readback(SoftwareSerial &ser)
{
  String d;
  
  while(ser.available() < 1);
  if(ser.available() > 0)
  {
    d = ser.readString();
    Serial.print(d);
  }
}

void setup()
{
  Serial.begin(115200);
  dorji.begin(9600);

  dorji_reset(dorji);
  delay(100);
  dorji_setfreq(144.390, 144.390, dorji);
  dorji_readback(dorji);
}

void loop()
{
  String s;
  String d;
  
  if(Serial.available() > 0)
  {
    s = Serial.readString();
    dorji.print(s);
  }

  if(dorji.available() > 0)
  {
    d = dorji.readString();
    Serial.print(d);
  }
}

/*
 * 
 */
