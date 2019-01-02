/*
 * 
 */

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Serial1.begin(9600);

  Serial.println(" ");
  Serial.print("Sketch:   ");   Serial.println(__FILE__);
  Serial.print("Uploaded: ");   Serial.println(__DATE__);
  Serial.println(" ");

  digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{
  char c;
  
  if(Serial1.available() > 0)
  {
    c = Serial1.read();

    if((c==10)||(c==13))
      digitalWrite(LED_BUILTIN, LOW);
    else
      digitalWrite(LED_BUILTIN, HIGH);

    Serial.print(c);
  }
}

/*
 * 
 */
