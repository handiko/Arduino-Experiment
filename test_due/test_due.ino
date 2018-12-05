

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  Serial.println("Hello World");  
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
