#include<LiquidCrystal.h>
#include<math.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

unsigned long htime=0;
unsigned long ltime=0;
unsigned long ttime=0;

float freq=0;

void countTime(float last_freq)
{
  int mag = 3*(floor(last_freq/100));

  htime=pulseIn(9,HIGH);
  ltime=pulseIn(9,LOW);

  if(mag>1)
  {
    for(int i=0;i<(mag-1);i++)
    {
      htime=htime+pulseIn(9,HIGH);
      ltime=ltime+pulseIn(9,LOW);
    }
    htime=htime/mag;
    ltime=ltime/mag;
  }
}

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  countTime(freq);
  
  ttime=htime+ltime;

  freq=1000000.0/(ttime);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(freq);
  
  delay(1);
}
