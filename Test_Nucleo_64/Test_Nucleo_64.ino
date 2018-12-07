



int a = pinMap(12); //pinMap(Mapped Pin) - for mapped pin refer the attacted image
int b = pinMap(1);
void setup()
{
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
}

void loop()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  delay(500);
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  delay(500); 
}
