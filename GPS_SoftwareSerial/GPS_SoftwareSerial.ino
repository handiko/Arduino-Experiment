/*  Basically do nothing except to set pin-1 as an input 
    (to ensure hi impedance condition)

    Instructions:
    - Give proper +5V and GND to the GPS module
    - Connect GPS TXD pin to the pin-1 of Arduino UNO
*/
#include <SoftwareSerial.h>

SoftwareSerial gps(8,9);

void setup() {
  Serial.begin(115200); 
  gps.begin(9600);
}

void loop() {
  if (gps.available())
    Serial.write(gps.read());
}
