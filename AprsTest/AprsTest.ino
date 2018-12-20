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

void send_lorem(void)
{
  for(int k=0;k<sizeof(lorem);k++)
  {
    send_char(lorem[k]);
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  init_dac(dacPinOffset,points,dacBits);
}

void loop() {
  send_lorem();
}
