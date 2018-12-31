#include <SoftwareSerial.h>

SoftwareSerial gps = SoftwareSerial(8,9);

char temp;
char buff[300];

char rmc[100];
char gga[100];
char gll[100];
char vtg[100];

int buffc=0;

void setup() {
  pinMode(0,INPUT);
  pinMode(1,OUTPUT);

  pinMode(8,INPUT);
  pinMode(9,OUTPUT);
  
  Serial.begin(115200);
  gps.begin(9600);
}

char find_char(char c)
{
  char t;

  while(t != c)
  {
    if(gps.available() > 0)
      t = gps.read();
  }
}

void rx_gps(void)
{
  buffc=0;
  
  if(gps.available() > 0)
  {
    temp = find_char('$');
    buff[buffc] = temp;

    do
    {
      if(gps.available() > 0)
      {
        buffc++;
        temp = gps.read();
        buff[buffc] = temp;
      }
    }
    while((temp != 10)&&(temp != 13));

    //for(int i=1;i<buffc;i++)
    //  Serial.print(buff[i]);
      
    //Serial.println(' ');
  }
  
  /*
   * $GPRMC
   */
  if((buff[1] == '$')&&(buff[2] == 'G')&&(buff[3] == 'P')&&
     (buff[4] == 'R')&&(buff[5] == 'M')&&(buff[6] == 'C'))
  {
    Serial.println("$GPRMC sentence detected !");

    for(int i=1;i<buffc;i++)
    {
      rmc[i-1] = buff[i];
    }

    Serial.println(rmc);
    Serial.println(' ');
  }

  /*
   * $GPGLL
   */
  if((buff[1] == '$')&&(buff[2] == 'G')&&(buff[3] == 'P')&&
     (buff[4] == 'G')&&(buff[5] == 'L')&&(buff[6] == 'L'))
  {
    Serial.println("$GPGLL sentence detected !");

    for(int i=1;i<buffc;i++)
    {
      gll[i-1] = buff[i];
    }

    Serial.println(gll);
    Serial.println(' ');
  }

  /*
   * $GPGGA
   */
  if((buff[1] == '$')&&(buff[2] == 'G')&&(buff[3] == 'P')&&
     (buff[4] == 'G')&&(buff[5] == 'G')&&(buff[6] == 'A'))
  {
    Serial.println("$GPGGA sentence detected !");

    for(int i=1;i<buffc;i++)
    {
      gga[i-1] = buff[i];
    }

    Serial.println(gga);
    Serial.println(' ');
  }

  /*
   * $GPVTG
   */
  if((buff[1] == '$')&&(buff[2] == 'G')&&(buff[3] == 'P')&&
     (buff[4] == 'V')&&(buff[5] == 'T')&&(buff[6] == 'G'))
  {
    Serial.println("$GPVTG sentence detected !");

    for(int i=1;i<buffc;i++)
    {
      vtg[i-1] = buff[i];
    }

    Serial.println(vtg);
    Serial.println(' ');
  }
}

void loop() {
  rx_gps();
}
