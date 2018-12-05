
unsigned int counter=0;
unsigned long reg;

bool secondPassed()
{
  static long lastTick = 0;
  long now = millis();

  if (now <= lastTick + 1000)
    return false;

  lastTick = now;
  return true;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  //REG_ADC_MR=0x10380100;
  //analogReadResolution(12);
  analogWriteResolution(12);
  reg=REG_ADC_MR;
  Serial.begin(9600);
}

void loop()
{
  //analogRead(A0);
  analogWrite(DAC0,100);
  counter++;
  if (secondPassed())
  {
    Serial.print(counter);
    Serial.print(" conversions per second, REG_ADC_MR = ");
    Serial.println(reg, HEX);
    counter = 0;
  }
}
