#include<LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
float freq = 124.31;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Baseband (Hz)");
  lcd.setCursor(0,1);
  lcd.print(freq);

  delay(500);
}
