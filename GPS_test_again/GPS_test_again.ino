/*
 * 
 */
#include <SoftwareSerial.h>

SoftwareSerial gps = SoftwareSerial(8, 9);

char rmc[100];
int rmc_stat;

int parse_gps(void)
{
  char temp;
  int c=0;

  for(int i=0;i<100;i++)
    rmc[i]=0;

  do
  {
    if(gps.available()>0)
      temp = gps.read(); 
  }
  while(temp!='$');

  do
  {
    if(gps.available()>0)
    {
      temp = gps.read();
      rmc[c] = temp;
      c++;
    }

    if(c==6)
    {
      if(rmc[4]!='C')
      {
        return 0;

        goto esc;
      }
    }
  }
  while((temp!=10)&&(temp!=13));

  gps.flush();
  gps.end();

  c--;

  return c;

  esc:
  ;
}

void setup()
{
  Serial.begin(115200);
  gps.begin(9600);
}

void loop()
{
  rmc_stat = parse_gps();

  if(rmc_stat>10)
  {
    Serial.print('$');
    for(int j=0;j<rmc_stat;j++)
      Serial.print(rmc[j]);
    Serial.println(' ');
  
    delay(3456);
  }
  
  gps.begin(9600);
}
