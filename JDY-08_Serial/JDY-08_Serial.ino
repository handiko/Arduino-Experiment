/*
 * 
 */
 
#include <AltSoftSerial.h>

AltSoftSerial BT(8,9);

void BT_sendcmd(AltSoftSerial &ser, String s);
void BT_readback(AltSoftSerial &ser);

void BT_initBT(AltSoftSerial &ser);

void BT_renew(AltSoftSerial &ser);
void BT_reset(AltSoftSerial &ser);
void BT_setname(AltSoftSerial &ser, String s);
void BT_setmaj(AltSoftSerial &ser, int n);

void BT_sendcmd(AltSoftSerial &ser, String s)
{
  Serial.print("\r\n> sending command :");
  Serial.println(s);
  ser.print(s);
}

void BT_readback(AltSoftSerial &ser)
{
  char s;
  while(ser.available() > 0)
  {
    s = ser.read();
    Serial.print(s);
  }
}

void BT_initBT(AltSoftSerial &ser)
{
  Serial.flush();
  Serial.print("\r\n> sending command : AT \r\n");
  
  for(char i=0;i<5;i++)
  {
    ser.print("AT");
    delay(100);
  }

  BT_readback(ser);
}

void BT_reset(AltSoftSerial &ser)
{
  Serial.flush();
  Serial.print("\r\n> sending command : AT+RESET \r\n");
  ser.print("AT+RESET");
  BT_readback(ser);
}

void BT_setname(AltSoftSerial &ser, String s)
{
  Serial.flush();
  Serial.print("\r\n> sending command : AT+NAME");
  Serial.println(s);
  ser.print("AT+NAME");
  ser.print(s);
  BT_readback(ser);
}

void BT_setmaj(AltSoftSerial &ser, int n)
{
  Serial.flush();
  Serial.print("\r\n> sending command : AT+MARJ0x");
  Serial.println(n, HEX);
  //ser.print("AT+NAME");
  //ser.print(s);
  //BT_readback(ser);
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
  
  BT_initBT(BT);              delay(100);
  
  BT_reset(BT);

  delay(500);
  
  BT_initBT(BT);              delay(100);
  BT_setname(BT, "handiko");  delay(100);
  BT_setmaj(BT, 12345);       delay(100);
}
 
void loop()
{
  BT_readback(BT);
}
