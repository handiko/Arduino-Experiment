/*
 * 
 */

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) ^ 1);

  delay(500);
}

/*
 * 
 */
