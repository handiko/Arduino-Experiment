/*
 * 
 */
 
int sum=0;
int last_millis;
int count;
bool rise = false;

void setup()
{
  analogReadResolution(12);
  Serial.begin(115200);

  last_millis = millis();
}

void loop()
{
  sum = analogRead(A0);

  if((sum > 2000) && (rise == false))
  {
    rise = true;
    count++;
    Serial.println(count);
  }

  if((sum < 2000) && (rise == true))
  {
    rise = false;
  }

  if((millis() - last_millis) > 100)
  {
    
    //Serial.println(sum);
    count = 0;
  }

  if((millis() - last_millis) < 0)
  {
    last_millis = millis();
  }
}
