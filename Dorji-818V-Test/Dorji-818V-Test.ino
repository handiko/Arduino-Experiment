/*
 * 
 */
#include <SoftwareSerial.h>

#define DRJ_TXD 10
#define DRJ_RXD 11

SoftwareSerial dorji(DRJ_RXD, DRJ_TXD);

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
  pinMode(DRJ_RXD, INPUT);
  pinMode(DRJ_TXD, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(12, OUTPUT);

  digitalWrite(7, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(5, LOW);
  
  Serial.begin(115200);
  dorji.begin(9600);

  Serial.println("Starting \n");

  delay(250);
  
  dorji_init(dorji);
  dorji_readback(dorji);

  delay(1000);
  
  dorji_setfreq(144.390, 144.390, dorji);
  dorji_readback(dorji);

  for(;;)
  {
    delay(1500);
    digitalWrite(7,HIGH);
    for(int i=0;i<500;i++)
    {
      digitalWrite(12,HIGH);
      delay(1);
      digitalWrite(12,LOW);
      delay(1);
    }
    digitalWrite(7, LOW);
  }
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
