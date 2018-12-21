/*
 * 
 */

#include <math.h>

/*
 * 
 */

char stuff=0;
unsigned short crc=0xffff;
bool nada=0;

const float baud_adj = 1.0;
const float adj_1200 = 1.0 * baud_adj;
const float adj_2400 = 1.0 * baud_adj;
const unsigned int tc1200 = (unsigned int)(0.5 * adj_1200 * 1000000.0 / 1200.0);
const unsigned int tc2400 = (unsigned int)(0.5 * adj_2400 * 1000000.0 / 2400.0);

const char points = 20;
unsigned char phAcc[points];
const char dacRes = 6;
const unsigned char dacAmp = pow(2, dacRes);
const char dacOff = dacAmp / 2;
const unsigned int _tc_1200 = (unsigned int)(adj_1200 * 1000000.0 / (1200.0 * points));
const unsigned int _tc_2400 = (unsigned int)(adj_2400 * 1000000.0 / (2400.0 * points));

/*
 * 
 */

const unsigned char mycall[]={"YD1SDL-1"};
const unsigned char dest[]={"APRS   "};
const unsigned char digi[]={"WIDE2 "};
const char digi_ssid=2;

unsigned char strings[]={" Hello World!"};

/*
 * 
 */

void set_wave(bool _nada);
void init_dac(void);
void set_nada(bool in_nada);
void send_crc(void);
void calc_crc(bool in_bit);
void send_char(unsigned char in_byte);
void send_ax25(void);

/*
 * 
 */

void set_wave(bool state)
{
  digitalWrite(2, state);
  digitalWrite(3, state);
  digitalWrite(4, state);
  digitalWrite(5, state);
  digitalWrite(6, state);
  digitalWrite(7, state);

  if(state)
    delayMicroseconds(tc1200);
  else
    delayMicroseconds(tc2400);
}

void init_dac(void)
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  
  for(int i=0;i<points;i++)
  {
    phAcc[i] = (unsigned char)(dacOff + (0.8 * dacAmp * sin(2 * 3.1415 * i / points)));
  }
}

void set_nada(bool in_nada)
{
  ///*
  if(nada)
  {
    digitalWrite(2, HIGH);
    delayMicroseconds(tc1200);
    digitalWrite(2, LOW);
    delayMicroseconds(tc1200);
  }
  else
  {
    digitalWrite(2, HIGH);
    delayMicroseconds(tc2400);
    digitalWrite(2, LOW);
    delayMicroseconds(tc2400);
    digitalWrite(2, HIGH);
    delayMicroseconds(tc2400);
    digitalWrite(2, LOW);
    delayMicroseconds(tc2400);
  }
  //*/

  //set_wave(in_nada);
}

void send_crc(void)
{
  unsigned char crc_lo = crc ^ 0xff;
  unsigned char crc_hi = (crc >> 8) ^ 0xff;

  send_char(crc_lo);
  send_char(crc_hi);
}

void calc_crc(bool in_bit)
{
  unsigned short xor_in;
  
  xor_in = crc ^ in_bit;
  crc >>= 1;

  if(xor_in & 0x01)
    crc ^= 0x8408;
}

void send_char(unsigned char in_byte)
{
  bool in_bits;

  for(int j=0;j<8;j++)
  {
    in_bits = (in_byte >> j) & 0x01;

    if(in_byte == 0x7e)
      stuff=0;

    else
      calc_crc(in_bits);

    if(in_bits==0)
    {
      nada ^= 1;
      set_nada(nada);
      stuff=0;
    }
    else
    {
      set_nada(nada);
      stuff++;

      if(stuff==5)
      {
        nada ^= 1;
        set_nada(nada);
        stuff=0;
      }
    }
  }
}

void send_ax25(void)
{
  for(int i=0;i<100;i++)
    send_char(0x7e);

  crc = 0xffff;

  for(int i=0;i<7;i++)
    send_char(dest[i] << 1);

  for(int i=0;i<7;i++)
    send_char(mycall[i] << 1);

  for(int i=0;i<6;i++)
    send_char(digi[i] << 1);
  send_char((digi_ssid << 1) + 1);

  send_char(0x03);
  send_char(0xf0);

  for(int i=0;i<sizeof(strings);i++)
    send_char(strings[i]);
  
  send_crc();

  for(int i=0;i<3;i++)
    send_char(0x7e);
}

/*
 * 
 */

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, OUTPUT);

  init_dac();
}

void loop()
{
  delay(2000);
  send_ax25();
  nada ^= 1;
}
