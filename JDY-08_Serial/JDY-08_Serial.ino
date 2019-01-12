/*
 * 
 */
 
#include <SoftwareSerial.h>

#define SET     true
#define CLEAR   false

SoftwareSerial BT(8,9);

void BT_sendcmd(SoftwareSerial &ser, String s);
void BT_readback(SoftwareSerial &ser);

void BT_initBT(SoftwareSerial &ser);

void BT_renew(SoftwareSerial &ser);
void BT_reset(SoftwareSerial &ser);
void BT_setname(SoftwareSerial &ser, String s);
void BT_setmaj(SoftwareSerial &ser, int n);
void BT_setmin(SoftwareSerial &ser, int n);
void BT_setibe0(SoftwareSerial &ser, String s);
void BT_setibe1(SoftwareSerial &ser, String s);
void BT_setibe2(SoftwareSerial &ser, String s);
void BT_setibe3(SoftwareSerial &ser, String s);
void BT_setIBeaUUID(SoftwareSerial &ser, String s0, String s1, String s2, String s3);
void BT_setadvIBea(SoftwareSerial &ser);
void BT_setadvint(SoftwareSerial &ser, char n);
void BT_setpower(SoftwareSerial &ser, char n);
void BT_setpwrm(SoftwareSerial &ser, bool c);
void BT_setIBea(SoftwareSerial &ser, bool c);

void BT_sendcmd(SoftwareSerial &ser, String s)
{
  Serial.print("\r\n> sending command :");
  Serial.println(s);
  ser.print(s);
}

void BT_readback(SoftwareSerial &ser)
{
  char s;
  while(ser.available() > 0)
  {
    s = ser.read();
    Serial.print(s);
  }
}

void BT_initBT(SoftwareSerial &ser)
{
  Serial.flush();
  Serial.print("\r\n> sending command : AT \r\n");
  
  for(char i=0;i<5;i++)
  {
    ser.print("AT");
    delay(100);
  }

  BT_readback(ser);
  BT_readback(ser);
  delay(100);
  BT_readback(ser);
}

void BT_reset(SoftwareSerial &ser)
{
  Serial.flush();
  Serial.print("\r\n> sending command : AT+RESET \r\n");
  ser.print("AT+RESET");
  
  BT_readback(ser);
  BT_readback(ser);
  delay(1000);
  BT_readback(ser);
}

void BT_setname(SoftwareSerial &ser, String s)
{
  Serial.flush();
  Serial.print("\r\n> sending command : AT+NAME");
  Serial.println(s);
  ser.print("AT+NAME");
  ser.print(s);
  
  BT_readback(ser);
  BT_readback(ser);
  delay(100);
  BT_readback(ser);
}

void BT_setmaj(SoftwareSerial &ser, int n)
{
  Serial.flush();
  Serial.print("\r\n> sending command : AT+MARJ0x");
  Serial.println(n, HEX);
  ser.print("AT+MARJ0x");
  ser.print(n, HEX);
  
  BT_readback(ser);
  BT_readback(ser);
  delay(100);
  BT_readback(ser);
}

void BT_setmin(SoftwareSerial &ser, int n)
{
  Serial.flush();
  Serial.print("\r\n> sending command : AT+MINO0x");
  Serial.println(n, HEX);
  ser.print("AT+MINO0x");
  ser.print(n, HEX);
  
  BT_readback(ser);
  BT_readback(ser);
  delay(100);
  BT_readback(ser);
}

void BT_setibe0(SoftwareSerial &ser, String s)
{
  Serial.flush();
  Serial.print("\r\n> sending command : AT+IBE0");
  Serial.println(s);
  ser.print("AT+IBE0");
  ser.print(s);
  
  BT_readback(ser);
  BT_readback(ser);
  delay(100);
  BT_readback(ser);
}

void BT_setibe1(SoftwareSerial &ser, String s)
{
  Serial.flush();
  Serial.print("\r\n> sending command : AT+IBE1");
  Serial.println(s);
  ser.print("AT+IBE1");
  ser.print(s);
  
  BT_readback(ser);
  BT_readback(ser);
  delay(100);
  BT_readback(ser);
}

void BT_setibe2(SoftwareSerial &ser, String s)
{
  Serial.flush();
  Serial.print("\r\n> sending command : AT+IBE2");
  Serial.println(s);
  ser.print("AT+IBE2");
  ser.print(s);
  
  BT_readback(ser);
  BT_readback(ser);
  delay(100);
  BT_readback(ser);
}

void BT_setibe3(SoftwareSerial &ser, String s)
{
  Serial.flush();
  Serial.print("\r\n> sending command : AT+IBE3");
  Serial.println(s);
  ser.print("AT+IBE3");
  ser.print(s);
  
  BT_readback(ser);
  BT_readback(ser);
  delay(100);
  BT_readback(ser);
}

void BT_setIBeaUUID(SoftwareSerial &ser, String s0, String s1, String s2, String s3)
{
  BT_setibe0(BT, s0);
  BT_setibe1(BT, s1);
  BT_setibe2(BT, s2);
  BT_setibe3(BT, s3);
}

void BT_setadvIBea(SoftwareSerial &ser)
{
  Serial.flush();
  Serial.print("\r\n> sending command : AT+ADTY");
  Serial.println(3);
  ser.print("AT+ADTY");
  ser.print(3);
  
  BT_readback(ser);
  BT_readback(ser);
  delay(100);
  BT_readback(ser);
}

void BT_setadvint(SoftwareSerial &ser, char n)
{
  if(n > 9)
    n = 9;

  else if(n < 0)
    n = 0;

  Serial.flush();
  Serial.print("\r\n> sending command : AT+ADVI");
  Serial.println(n);
  ser.print("AT+ADVI");
  ser.print(n);
  
  BT_readback(ser);
  BT_readback(ser);
  delay(100);
  BT_readback(ser);
}

void BT_setpower(SoftwareSerial &ser, char n)
{
  if(n > 3)
    n = 3;

  else if(n < 0)
    n = 0;

  Serial.flush();
  Serial.print("\r\n> sending command : AT+POWE");
  Serial.println(n);
  ser.print("AT+POWE");
  ser.print(n);
  
  BT_readback(ser);
  BT_readback(ser);
  delay(100);
  BT_readback(ser);
}

void BT_setpwrm(SoftwareSerial &ser, bool c)
{
  Serial.flush();
  Serial.print("\r\n> sending command : AT+PWRM");
  Serial.println(c);
  ser.print("AT+PWRM");
  ser.print(c);
  
  BT_readback(ser);
  BT_readback(ser);
  delay(100);
  BT_readback(ser);
}

void BT_setIBea(SoftwareSerial &ser, bool c)
{
  Serial.flush();
  Serial.print("\r\n> sending command : AT+IBEA");
  Serial.println(c);
  ser.print("AT+IBEA");
  ser.print(c);
  
  BT_readback(ser);
  BT_readback(ser);
  delay(100);
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
  
  BT_reset(BT);
  
  BT_initBT(BT);

  BT_setname(BT, "handiko");
  BT_setmaj(BT, 12345);
  BT_setmin(BT, 23456);
  BT_setIBeaUUID (BT,
                  "74278BDA",
                  "12345678",
                  "01AB23CD",
                  "0A1B2C3D");
                  
  BT_reset(BT);
}
 
void loop()
{
  BT_readback(BT);
}
