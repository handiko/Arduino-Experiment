#include <AltSoftSerial.h>

// AltSoftSerial always uses these pins:
//
// Board          Transmit  Receive   PWM Unusable
// -----          --------  -------   ------------
// Teensy 3.0 & 3.1  21        20         22
// Teensy 2.0         9        10       (none)
// Teensy++ 2.0      25         4       26, 27
// Arduino Uno        9         8         10
// Arduino Leonardo   5        13       (none)
// Arduino Mega      46        48       44, 45
// Wiring-S           5         6          4
// Sanguino          13        14         12

// This example code is in the public domain.

AltSoftSerial altSerial;

char buff[100];
int bc = 0;

bool pref=false;
bool term=false;

char rmcbuff[100];
char rmc[100];
char sec, l_sec;

ISR(TIMER1_COMPA_vect)
{
  clear_timer1();
  
  Serial.println("Timer 1 goes off !");

  set_timer1();
}

void set_timer1(void)
{
  TCCR1A = 0x00;
  TCCR1B = 0x00;
  TCNT1 = 0x00;

  OCR1A = 65500;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS10);
  TCCR1B |= (0 << CS11);
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << OCIE1A);
}

void clear_timer1(void)
{
  TCCR1B = 0;
  TIMSK1 = 0;
}

void print_rmc(void)
{
  altSerial.end();
  Serial.println(rmc);
  altSerial.begin(9600);
}

void find_rmc(void)
{
  char c;
  
  if (altSerial.available()) {
    c = altSerial.read();
    //Serial.print(c);

    if(!pref)
    {
      if(c=='$')
      {
        pref=true;
      }
    }

    if((c==10)||(c==13))
    {
      pref=false;
      term=true;
    }

    if((pref)&&(!term))
    {
      buff[bc++]=c;
    }

    if(term)
    {
      if((buff[0]=='$')&&(buff[1]=='G')&&(buff[2]=='P')&&
         (buff[3]=='R')&&(buff[4]=='M')&&(buff[5]=='C'))
      {
        for(int j=0;j<bc;j++)
        {
          rmcbuff[j]=buff[j];
        }
      }

      bc=0;
      
      //Serial.println(rmc);
        
      term=false;
      pref=false;

      for(int j=0;j<100;j++)
      {
        buff[j]='\0';
        rmc[j] = rmcbuff[j];
      }
    }
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("AltSoftSerial Test Begin");
  altSerial.begin(9600);
}

void loop() {
  find_rmc();
}
