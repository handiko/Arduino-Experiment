/*
 * 
 */

#include <Cmd.h>
#include <string.h>

#define OUT_PIN     2

#define CTRL_FIELD  0x03
#define PID         0xf0

#define CRC_INIT_VALUE  0xffff

/*
 * 
 */
float baud_adj_rand;
const float baud_adj = 0.97; //0.97
const float adj_1200 = 1.0 * baud_adj;
const float adj_2400 = 1.0 * baud_adj;
unsigned int tc1200 = (unsigned int)(0.5 * adj_1200 * 1000000.0 / 1200.0);
unsigned int tc2400 = (unsigned int)(0.5 * adj_2400 * 1000000.0 / 2400.0);

char stuff=0;
unsigned short crc = CRC_INIT_VALUE;
bool nada=0;
bool send_aprs=1;

char mycall[8] = {"YB0Z"};
char myssid = 0;
const char dest[8] = {"APRS  0"};
char digi[8] = {"WIDE2"};
char digi_ssid = 1;
char lat[9] = {"0615.52S"};
char lon[10] = {"10643.56E"};
char info[50] = {"!0615.52SH10643.56Ea"};
char comment[256] = {"Arduino APRS Sender"};

int tx_delay = 3000;

/*
 * 
 */
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
  if((random(1,50) % 2) == 0)
    nada = 0;
  else
    nada = 1;

  //baud_adj_rand = 0.01 * random(95, 102);

  //tc1200 = (unsigned int)(0.5 * adj_1200 * baud_adj_rand * 1000000.0 / 1200.0);
  //tc2400 = (unsigned int)(0.5 * adj_2400 * baud_adj_rand * 1000000.0 / 2400.0);
}

void printAX25ByteFrame(void)
{
  for(int i = 0; i < 6; i++)
  {
    if(mycall[i] != '\0')
      Serial.print(mycall[i]);
  }

  Serial.print('-');
  Serial.print(myssid, DEC);
  Serial.print('>');

  for(int i = 0; i < 6; i++)
  {
    if(isAlphaNumeric(dest[i]))
      Serial.print(dest[i]);
  }

  if(dest[6] != '0')
  {
    Serial.print('-');
    Serial.print(dest[6]);
  }
  Serial.print(',');

  for(int i = 0; i < 6; i++)
  {
    if(digi[i] != '\0')
      Serial.print(digi[i]);
  }

  Serial.print('-');
  Serial.print(digi_ssid, DEC);
  Serial.print(':');

  for(int i = 0; i < strlen(info); i++)
    Serial.print(info[i]);
    
  for(int i = 0; i < strlen(comment); i++)
  {
    if(comment[i] == '_')
      comment[i] = ' ';
    Serial.print(comment[i]);
  }
  
  Serial.println(' ');
}

void send_ax25header(void)
{
  int i;
  char mc_len = strlen(mycall);
  char digi_len = strlen(digi);
  
  for(i = 0; i < 100; i++)
    send_char(0x7e);

  crc = CRC_INIT_VALUE;

  for(i = 0; i < 7; i++)
    send_char(dest[i] << 1);

  for(i = 0; i < mc_len; i++)
    send_char(mycall[i] << 1);
  if(mc_len < 6){
    for(i = 0; i < (6 - mc_len); i++){
      send_char(' ' << 1);
    }
  }
  send_char((myssid + '0') << 1);

  for(i = 0; i < digi_len; i++)
    send_char(digi[i] << 1);
  if(digi_len < 6){
    for(i = 0; i < (6 - digi_len); i++){
      send_char(' ' << 1);
    }
  }
  send_char(((digi_ssid + '0') << 1) + 1);

  send_char(CTRL_FIELD);
  send_char(PID);
}

void send_payload(void)
{
  for(int i = 0; i < strlen(info); i++)
    send_char(info[i]);
    
  for(int i = 0; i < strlen(comment); i++)
    send_char(comment[i]);
}

void send_ax25(void)
{
  printAX25ByteFrame();
  
  randomize();
  
  send_ax25header();
  send_payload();
  
  send_crc();

  for(int i=0;i<3;i++)
    send_char(0x7e);
}

/*
 * 
 */
void set_mode(int argc, char **argv)
{
  send_aprs = 0;
  Serial.println("Enter Set Mode");
}

void set_delay(int argc, char **argv)
{
  if(argc > 0)
  {
    tx_delay = cmdStr2Num(argv[1], 10);
  }
  Serial.print("Set TX Delay : ");
  Serial.println(tx_delay);
}

void set_latitude(int argc, char **argv)
{
  if(argc > 0)
  {
    strncpy(lat, argv[1], sizeof(lat) - 1);
    lat[8] = '\0';
  }

  Serial.print("Set Latitude :");
  Serial.println(lat);
  printAX25ByteFrame();
}

void set_longitude(int argc, char **argv)
{
  if(argc > 0)
  {
    strncpy(lon, argv[1], sizeof(lon) - 1);
    lon[9] = '\0';
  }

  Serial.print("Set Longitude :");
  Serial.println(lon);
  printAX25ByteFrame();
}

void set_comment(int argc, char **argv)
{
  if(argc > 0)
  {
    strncpy(comment, argv[1], sizeof(comment) - 1);
    comment[sizeof(comment)] = '\0';
  }

  Serial.print("Set Comment :");
  Serial.println(comment);
  printAX25ByteFrame();
}

void set_run(int argc, char **argv)
{
  send_aprs = 1;
  Serial.println("Exit Set Mode");
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
  cmdAdd("SET", set_mode);
  cmdAdd("SET+DELAY", set_delay);
  cmdAdd("SET+LAT", set_latitude);
  cmdAdd("SET+LON", set_longitude);
  cmdAdd("SET+COMMENT", set_comment);
  cmdAdd("RUN", set_run);
}

void loop()
{
  if(send_aprs)
  {
    delay(tx_delay);
    digitalWrite(LED_BUILTIN, HIGH);
    send_ax25();
    digitalWrite(LED_BUILTIN, LOW);
  }
  
  cmdPoll();
}
