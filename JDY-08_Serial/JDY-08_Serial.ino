/*
 * 
 */
 
#include <SoftwareSerial.h>

SoftwareSerial BT(8,9);

char BT_readback(SoftwareSerial &ser);

char BT_readback(SoftwareSerial &ser)
{
  char s;
  if (ser.available() > 0)
  {
    s = ser.read();
    Serial.print(s);
  }

  return s;
}
 
void setup() 
{
    Serial.begin(115200);
    Serial.print("Sketch:   ");   Serial.println(__FILE__);
    Serial.print("Uploaded: ");   Serial.println(__DATE__);
    Serial.println(" ");
 
    BT.begin(9600);  
    Serial.print("BTserial started at ");
    Serial.println(9600);

    
}
 
void loop()
{
   
}
