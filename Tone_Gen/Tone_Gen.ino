/*  Basically do nothing except to set pin-1 as an input 
    (to ensure hi impedance condition)

    Instructions:
    - Give proper +5V and GND to the GPS module
    - Connect GPS TXD pin to the pin-1 of Arduino UNO
*/

void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //tone(13,1000);
}
