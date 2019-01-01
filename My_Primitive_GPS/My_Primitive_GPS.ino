

void setup()
{
  Serial.begin(115200);
  Serial.println(' ');
  Serial.println("Started ! \n");
  Serial.end();
}

void loop()
{
  Serial.begin(9600);

  if((Serial.available()>0)&&(Serial.read()=='$')) {
    if((Serial.available()>0)&&(Serial.read()=='G')) {
      if((Serial.available()>0)&&(Serial.read()=='P')) {
        if((Serial.available()>0)&&(Serial.read()=='R')) {
          if((Serial.available()>0)&&(Serial.read()=='M')) {
            if((Serial.available()>0)&&(Serial.read()=='C')) {
              Serial.end();
              Serial.begin(115200);

              Serial.println("$GPRMC detected !");
            }
          }
        }
      }
    }
  }
  
  Serial.end();
}
