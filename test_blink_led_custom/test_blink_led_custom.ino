int time_delay = 250;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);
  delay(time_delay);
  digitalWrite(LED_BUILTIN, LOW);
  delay(time_delay);
}
