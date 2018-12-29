/*
 * 
 */

#include <math.h>
#include <Cmd.h>

#define UNO     1
#define DUE     2
#define esp     3

#define BOARD   UNO

/*
 * 
 */

char stuff=0;
unsigned short crc=0xffff;
bool nada=0;

#ifdef BOARD
  #if BOARD == 1
    const float baud_adj = 0.97; //0.97
    #define OUT_PIN 2
  #elif BOARD == 2
    const float baud_adj = 1.01;
    #define OUT_PIN 3
  #elif BOARD == 3
    const float baud_adj = 1.000;
    #define OUT_PIN 14
  #endif
#endif

const float adj_1200 = 1.0 * baud_adj;
const float adj_2400 = 1.0 * baud_adj;
unsigned int tc1200 = (unsigned int)(0.5 * adj_1200 * 1000000.0 / 1200.0);
unsigned int tc2400 = (unsigned int)(0.5 * adj_2400 * 1000000.0 / 2400.0);

/*
 * 
 */

const unsigned char mycall[]={"YD1SDL "};
const unsigned char dest[]={"APRS   "};
const unsigned char digi[]={"WIDE2 2"};

PROGMEM const char strings[860]={
"b0NWtAXLKj0Sn8WRsakzQS8JN25zAAf3md5ILaYty6jvZHrq1QU1CWfC6tKOMY7cFCopla9sn0bn26zcd9qRHFWflqMcmMwx9ZDmzxrs4cfjiMox4R0pNCB0fm26gDVc\
dMCZcVOnovLDWUlFHL0m2ULj3SVJonE4swIlemv2miVFJ3hjETh54cubpJhefhHtOGlwwtd64PigxsjzB3oXI6tJR3sCd84sheQis2DrnBZPd4pYdZvv6nx01hDeQNiU\
YGilAHb7cdqlEIMwhHVaqIgn43JOwQzSMGOWvAbFdSxLyoUd8rYeyVWHxW3tyJS7wjWjsr1UV3RCkPBL4XhMpceV3z0zu6y9rQGWxBwVAbBliOo630lkdmwRkuMB0INN\
cS4CjELYzsVQnEnX5OMCryDdbFEGwCpDEiFPETlP4EeqsYI6ACIRsM9A8buf1eecrwBKgkT3Ty0mHlOjc4ibBiJCJB5vTzvEbQdfgsLGubfPL1Y8Vb5PAzwCGVotWxUP\
UPamGgBezXZ4JbOAbUfXGEM1ppuRtam8zk4ePExs1ccD4qumNt0pvfEWyCiIrVuLAK1TGoOG9rE0U0wCaLILlmLiTu1UtPMSTm1sZzEAdunENMmMrHH4bO5W3dL36Njo\
q7fCVyFGiIurYBcmamYRWHFas3f6DCN7IpOiKo0PM1EIf7eeVegEB4lQZ5EVSXJ4HpGodk4h903bu4KIfm2VilJUUtjiy9lMqTXGliafDss5zBGpL8S7yh1z2NdgD8Tr\
RGXR4EJ9gSiJTCBiGoSe1uzoeqPNV1pMM7ld7bKbTriOlBNyTCm7lx7cM8J5IsO4iegCSjG0OzwiQEhed7hvS2b78Qu"
};

int string_len;
int string_word;
int tx_delay = 1000;
float baud_adj_rand;

/*
 * 
 */

void set_wave(bool state, bool _nada);
void init_dac(void);
void set_nada(bool in_nada);
void send_crc(void);
void calc_crc(bool in_bit);
void send_char(unsigned char in_byte);
void randomize(void);
void send_ax25(void);

/*
 * 
 */

void set_nada(bool in_nada)
{
  if(nada)
  {
    digitalWrite(OUT_PIN, HIGH);
    delayMicroseconds(tc1200);
    digitalWrite(OUT_PIN, LOW);
    delayMicroseconds(tc1200);
  }
  else
  {
    digitalWrite(OUT_PIN, HIGH);
    delayMicroseconds(tc2400);
    digitalWrite(OUT_PIN, LOW);
    delayMicroseconds(tc2400);
    digitalWrite(OUT_PIN, HIGH);
    delayMicroseconds(tc2400);
    digitalWrite(OUT_PIN, LOW);
    delayMicroseconds(tc2400);
  }
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

    if((in_byte == 0x7e)||(in_byte == 255))
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

void randomize(void)
{
  string_len = random(1, 256);
  string_word = random(0, 600);
  //tx_delay = random(1, 3500);

  if((random(1,50) % 2) == 0)
    nada = 0;
  else
    nada = 1;

  baud_adj_rand = 0.01 * random(95, 102);

  tc1200 = (unsigned int)(0.5 * adj_1200 * 1000000.0 / 1200.0);
  tc2400 = (unsigned int)(0.5 * adj_2400 * 1000000.0 / 2400.0);
}

void send_ax25(void)
{
  randomize();
  
  for(int i=0;i<65;i++)
    send_char(0x7e);

  crc = 0xffff;

  for(int i=0;i<7;i++)
    send_char(dest[i] << 1);

  for(int i=0;i<7;i++)
    send_char(mycall[i] << 1);

  for(int i=0;i<6;i++)
    send_char(digi[i] << 1);
  send_char((digi[6] << 1) + 1);

  send_char(0x03);
  send_char(0xf0);

  send_char(',');
  for(int i=0;i<string_len;i++)
    send_char(strings[i + string_word]);
  
  send_crc();

  for(int i=0;i<3;i++)
    send_char(0x7e);
}

/*
 * 
 */

void set_delay(int argc, char **argv)
{
  if(argc > 0)
  {
    tx_delay = cmdStr2Num(argv[1], 10);
  }
}

/*
 * 
 */

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(OUT_PIN, OUTPUT);

  Serial.begin(9600);
  
  cmdInit(&Serial);
  cmdAdd("SETDELAY", set_delay);
}

void loop()
{
  delay(tx_delay);
  digitalWrite(LED_BUILTIN, HIGH);
  send_ax25();
  digitalWrite(LED_BUILTIN, LOW);

  cmdPoll();
}
