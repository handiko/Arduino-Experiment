
int iter=50;

unsigned int val=0;

float getValue(void)
{
  int temp;
  for(int i=0;i<iter;i++)
  {
    val=val+analogRead(A0);
  }
  temp=val/iter;
  val=0;
  return temp;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
  float adc = getValue();
  
  Serial.println(adc);
  delay(10);
}
