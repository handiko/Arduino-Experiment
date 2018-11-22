#include "pitches.h"

void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  tone(13,NOTE_C6);
  delay(1000);
  noTone(13);
  tone(13,NOTE_B4);
  delay(1000);
  noTone(13);
}
