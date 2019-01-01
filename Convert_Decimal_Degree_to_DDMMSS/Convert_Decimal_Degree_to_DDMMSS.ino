/*
 * 
 */

float dd = -6.25875711;

int d, m, s;

void setup()
{
  Serial.begin(115200);

  d = (int) dd;
  m = (int)(abs(dd - d) * 60);
  s = abs(dd - d - m/60) * 3600;

  Serial.print(dd, 6);
  Serial.print('\t');

  Serial.print(d);
  Serial.print(' ');
  Serial.print(m);
  Serial.print(' ');
  Serial.print(s);
  Serial.print('\n');
}

void loop()
{
  
}
