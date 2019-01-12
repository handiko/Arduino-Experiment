/*
 * 
 */
 
#include <AltSoftSerial.h>

AltSoftSerial btSerial;
char c = ' ';
bool NL = true;

void serReadBack(AltSoftSerial &serial);

void serReadBack(AltSoftSerial &serial)
{
  char s;
  if (serial.available())
  {
    s = serial.read();
    Serial.write(s);
  }
}
 
void setup() 
{
    Serial.begin(115200);
    Serial.print("Sketch:   ");   Serial.println(__FILE__);
    Serial.print("Uploaded: ");   Serial.println(__DATE__);
    Serial.println(" ");
 
    btSerial.begin(9600);  
    Serial.print("BTserial started at ");
    Serial.println(9600);
}
 
void loop()
{
    /*if (btSerial.available())
    {
        c = btSerial.read();
        Serial.write(c);
    }*/

    serReadBack(btSerial);
 
 
    if (Serial.available())
    {
        c = Serial.read();
 
        if ((c!=10) & (c!=13)) 
        {  
             btSerial.write(c);
        }
 
        if (NL)
        {
          Serial.print("\r\n>");  
          NL = false; 
        }
        
        Serial.write(c);
        if (c==10) 
        { 
          NL = true; 
        }
    }
}
