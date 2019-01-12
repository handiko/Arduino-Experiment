/*
 * 
 */
 
#include <SoftwareSerial.h>

SoftwareSerial BT(8,9);

void BT_sendcmd(SoftwareSerial &ser, String s);
char BT_readback(SoftwareSerial &ser);

void BT_initBT(SoftwareSerial &ser);

void BT_renew(SoftwareSerial &ser);
void BT_reset(SoftwareSerial &ser);
void BT_setname(SoftwareSerial &ser, String s);

void BT_sendcmd(SoftwareSerial &ser, String s)
{
  Serial.print("\r\n> sending command :");
  Serial.println(s);
  ser.print(s);
}

char BT_readback(SoftwareSerial &ser)
{
  char s;
  while(ser.available() > 0)
  {
    s = ser.read();
    Serial.print(s);
  }
  return s;
}

void BT_initBT(SoftwareSerial &ser)
{
  for(char i=0;i<5;i++)
  {
    ser.print("AT");
    delay(100);
  }
}

void BT_reset(SoftwareSerial &ser)
{
  Serial.print("\r\n> sending command : AT+RESET");
  ser.print("AT+RESET");
  BT_readback(ser);
}

void BT_setname(SoftwareSerial &ser, String s)
{
  Serial.print("\r\n> sending command : AT+NAME");
  Serial.println(s);
  ser.print("AT+NAME");
  ser.print(s);
  BT_readback(ser);
}
 
void setup() 
{
  Serial.begin(115200);
  Serial.print("Sketch:   "); Serial.println(__FILE__);
  Serial.print("Uploaded: "); Serial.println(__DATE__);
  Serial.println(" ");
  
  BT.begin(9600);
  Serial.print("BTserial started at ");
  Serial.println(9600);
  
  BT_initBT(BT);
  BT_readback(BT);

  BT_reset(BT);
  BT_setname(BT, "handiko");
}
 
void loop()
{
  BT_readback(BT);
}
