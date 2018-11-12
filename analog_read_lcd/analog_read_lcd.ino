#include<LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
float freq = 124.31;

void writeFreqLcd(int col, float val)
{
  lcd.setCursor(col,1);
  lcd.print(val);
}

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  freq = analogRead(A0);
  freq = freq + (freq/100);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Baseband (Hz)");
  
  writeFreqLcd(0,freq);

  delay(100);
}
