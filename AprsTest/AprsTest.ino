/*
 * 
 */

#include <math.h>

const char points=20;
const char dacBits=6;
char dacPins[dacBits];
const char dacPinOffset=2;
const float baudAdj=1.0;
const float dacAdj_1200=0.6280*baudAdj;
const float dacAdj_2400=0.3678*baudAdj;
const unsigned int dacDelay1200=(unsigned int)(dacAdj_1200*1000000.0/(1200.0*points));
const unsigned int dacDelay2400=(unsigned int)(dacAdj_2400*1000000.0/(2400.0*points));
unsigned char phAcc[points];

const unsigned char lorem[]=
{"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. \
Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. \
Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. \
Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."};

unsigned char flag=0x7e;
unsigned char dest[]={"APRS"};
unsigned char source[]={"KR2Q"};
unsigned char source_ssid=0;
unsigned char digi[]={"WIDE2"};
unsigned char digi_ssid=2;
unsigned char ctrl=0x03;
unsigned char pid=0xf0;
unsigned char info[]={"Hello"};

bool nada=1;
char bit_stuff=0;
unsigned int bit_counter=0;

unsigned short crc;

void calc_phAcc(char samples, char bits)
{
  int ampl = pow(2, bits);
  for(int i=0;i<samples;i++)
  {
    phAcc[i]=(unsigned char)(0.5*ampl*(1 + 0.9*sin(2 * 3.1415 * i/samples)));
  }
}

void init_dac(char dac_pin_off, char samples, char bits)
{
  for(int i=0;i<dacBits;i++)
  {
    pinMode(i+dac_pin_off,OUTPUT);
    dacPins[i]=i+dac_pin_off;
  }

  calc_phAcc(samples,bits);
}

void set_dac(unsigned char sample,char bits)
{
  for(int i=0;i<bits;i++)
  {
    digitalWrite(dacPins[i],(sample & 0x01));
    sample >>= 1;
  }
}

void set_wave_1200(char samples,char bits)
{
  for(int i=0;i<samples;i++)
  {
    set_dac(phAcc[i],bits);
    delayMicroseconds(dacDelay1200);
  }
}

void set_wave_2400(char samples,char bits)
{
  for(int i=0;i<samples;i++)
  {
    set_dac(phAcc[i],bits);
    delayMicroseconds(dacDelay2400);
  }
}

void send_char(unsigned char bytes)
{
  for(int j=0;j<8;j++)
  {
    if(bytes & 0x01)
    {
      set_wave_1200(points,dacBits);
    }
    else
    {
      set_wave_2400(points,dacBits);
      set_wave_2400(points,dacBits);
    }

    bytes >>= 1;
  }
}

void send_nada(bool in)
{
  if(in)
    set_wave_1200(points,dacBits);
  else
  {
    set_wave_2400(points,dacBits);
    set_wave_2400(points,dacBits);
  }
}

void hitung_crc(bool in_crc)
{
  static unsigned short xor_in;

  xor_in = crc ^ in_crc;
  crc >>= 1;

  if(xor_in & 0x01)
    crc ^= 0x8408;
}

void send_aprs_char(unsigned char input)
{
  unsigned char buff=input;
  for(int m=0;m<8;m++)
  {
    if(input & 0x01)
    {
      send_nada(nada);
      bit_stuff++;
      
      if(buff==0x7e)
        bit_stuff=0;
      else
        hitung_crc(input & 0x01);
        
      bit_counter++;
      
      if(bit_stuff==5)
      {
        nada^=1;
        send_nada(nada);
        bit_stuff=0;
        bit_counter++;
      }
    }
    else
    {
      nada^=1;
      send_nada(nada);
      bit_stuff=0;
      bit_counter++;
    }

    input >>=1;
  }
}

void send_aprs_string(void)
{
  char temp=0;
  static unsigned char crc_lo;
  static unsigned char crc_hi;

  // FLAGS
  for(int n=0;n<150;n++)
    send_aprs_char(flag);

  crc = 0xffff;

  // DESTINATION
  temp=sizeof(dest);
  for(int n=0;n<temp;n++)
    send_aprs_char(dest[n]<<1);

  if(temp<6)
  {
    for(int n=0;n<(6-temp);n++)
      send_aprs_char(' '<<1);
  }

  // SOURCE
  temp=sizeof(source);
  for(int n=0;n<temp;n++)
    send_aprs_char(source[n]<<1);

  if(temp<6)
  {
    for(int n=0;n<(6-temp);n++)
      send_aprs_char(' '<<1);
  }

  send_aprs_char((source_ssid+'0')<<1);

  // DIGI(S)
  temp=sizeof(digi);
  for(int n=0;n<temp;n++)
    send_aprs_char(digi[n]<<1);

  if(temp<6)
  {
    for(int n=0;n<(6-temp);n++)
      send_aprs_char(' '<<1);
  }

  send_aprs_char(((digi_ssid+'0')<<1)+1);

  // CONTROL FIELD
  send_aprs_char(ctrl);

  // PID
  send_aprs_char(pid);

  // INFO
  for(int n=0;n<sizeof(info);n++)
  {
    send_aprs_char(info[n]);
  }

  // CRC
  crc_lo=crc^0xff;
  crc_hi=(crc>>8)^0xff;

  //send_aprs_char(crc_lo);
  //send_aprs_char(crc_hi);
  
  // FLAGS
  for(int n=0;n<5;n++)
    send_aprs_char(flag);
}

void send_lorem(void)
{
  for(int k=0;k<sizeof(lorem);k++)
  {
    send_char(lorem[k]);
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  
  init_dac(dacPinOffset,points,dacBits);
}

void loop() {
  send_lorem();
  delay(1000);
  send_aprs_string();
  delay(1000);
  Serial.println(bit_counter);
  bit_counter=0;
  nada^=1;
}
