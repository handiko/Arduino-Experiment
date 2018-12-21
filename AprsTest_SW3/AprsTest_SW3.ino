/*
 * 
 */

#include <math.h>

const float baudAdj=1.0;
const float adj1200=1.0;
const float adj2400=1.0;
const float tc1200=baudAdj*adj1200*1000000.0/1200.0;
const float tc2400=baudAdj*adj2400*1000000.0/2400.0;
const unsigned int delay_1200=(unsigned int)(0.5*tc1200);
const unsigned int delay_2400=(unsigned int)(0.5*tc2400);

bool last_sent_bit=0;

char aprs_bits[700];

const char dest[]={"APRS"};
const char dest_ssid=0;
const char source[]={"YD1SDL"};
const char source_ssid=0;
const char digi[]={"WIDE2"};
const char digi_ssid=2;

const char ctrl=0x03;
const unsigned char pid=0xf0;

const char info[]={"Test"};

bool crc[16]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
char bit_stuff=0;
bool last_bit=0;

int bit_counter=0;

/***************************************************************/

void calc_crc(bool in_crc)
{
  bool xor_in = crc[15] ^ in_crc;

  crc[15]=crc[14];
  crc[14]=crc[13];
  crc[13]=crc[12];
  crc[12]=crc[11] ^ xor_in;

  crc[11]=crc[10];
  crc[10]=crc[9];
  crc[9]=crc[8];
  crc[8]=crc[7];
  
  crc[7]=crc[6];
  crc[6]=crc[5];
  crc[5]=crc[4] ^ xor_in;
  crc[4]=crc[3];

  crc[3]=crc[2]; 
  crc[2]=crc[1]; 
  crc[1]=crc[0]; 
  crc[0]=xor_in;
}

void set_bits_lsb_first(int pos,unsigned char in_byte)
{
  bit_counter=pos;
  for(int i=0;i<8;i++)
  {
    calc_crc(in_byte & 0x01);

    if(in_byte & 0x01)
    {
      aprs_bits[bit_counter]=last_bit;
      bit_counter++;

      bit_stuff++;

      if(bit_stuff==5)
      {
        last_bit ^= 1;
        aprs_bits[bit_counter]=last_bit;
        bit_counter++;

        bit_stuff=0;
      }
    }
    else
    {
      last_bit ^= 1;
      aprs_bits[bit_counter]=last_bit;
      bit_counter++;
      
      bit_stuff=0;
    }
    
    in_byte>>=1;
  }
}

void generate_addr(void)
{
  char temp=sizeof(dest);
  for(int j=0;j<temp;j++)
  {
    set_bits_lsb_first(bit_counter, (dest[j]<<1));
  }
  if(temp<6)
  {
    for(int j=0;j<(6-temp);j++)
    {
      set_bits_lsb_first(bit_counter, 0x40);
    }
  }
  set_bits_lsb_first(bit_counter, ((dest_ssid+'0')<<1));



  temp=sizeof(source);
  for(int j=0;j<temp;j++)
  {
    set_bits_lsb_first(bit_counter, (source[j]<<1));
  }
  if(temp<6)
  {
    for(int j=0;j<(6-temp);j++)
    {
      set_bits_lsb_first(bit_counter, 0x40);
    }
  }
  set_bits_lsb_first(bit_counter, ((source_ssid+'0')<<1));



  temp=sizeof(digi);
  for(int j=0;j<temp;j++)
  {
    set_bits_lsb_first(bit_counter, (digi[j]<<1));
  }
  if(temp<6)
  {
    for(int j=0;j<(6-temp);j++)
    {
      set_bits_lsb_first(bit_counter, 0x40);
    }
  }
  set_bits_lsb_first(bit_counter, ((digi_ssid+'0')<<1)+1);
}

void generate_info(void)
{
  set_bits_lsb_first(bit_counter, ctrl);
  set_bits_lsb_first(bit_counter, pid);
  
  for(int j=0;j<sizeof(info);j++)
  {
    set_bits_lsb_first(bit_counter, info[j]);
  }
}

void generate_fcs(void)
{
  bool temp=0;
  
  for(int j=15;j>0;j--)
  {
    temp=crc[j];

    if(temp)
    {
      aprs_bits[bit_counter]=last_bit;
      bit_counter++;

      bit_stuff++;

      if(bit_stuff==5)
      {
        last_bit ^= 1;
        aprs_bits[bit_counter]=last_bit;
        bit_counter++;

        bit_stuff=0;
      }
    }
    else
    {
      last_bit ^= 1;
      aprs_bits[bit_counter]=last_bit;
      bit_counter++;
      
      bit_stuff=0;
    }
  }
}

void generate_msg(void)
{
  generate_addr();
  generate_info();
  generate_fcs();
}

/***************************************************************/

void set_wave_1200(void)
{
  digitalWrite(2, HIGH);
  delayMicroseconds(delay_1200);
  digitalWrite(2, LOW);
  delayMicroseconds(delay_1200);
}

void set_wave_2400(void)
{
  digitalWrite(2, HIGH);
  delayMicroseconds(delay_2400);
  digitalWrite(2, LOW);
  delayMicroseconds(delay_2400);
  digitalWrite(2, HIGH);
  delayMicroseconds(delay_2400);
  digitalWrite(2, LOW);
  delayMicroseconds(delay_2400);
}

void send_aprs_bits(void)
{
  for(int m=0;m<100;m++)
  {
    for(int n=0;n<7;n++)
      set_wave_1200();
    set_wave_2400();
  }

  for(int m=0;m<bit_counter;m++)
  {
    if(aprs_bits[m]==0)
      set_wave_1200();
    else if(aprs_bits[m]==1)
      set_wave_2400();
  }

  for(int m=0;m<3;m++)
  {
    for(int n=0;n<7;n++)
      set_wave_1200();
    set_wave_2400();
  }
}

/***************************************************************/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, OUTPUT);
  
  Serial.begin(9600);

  bit_counter=0;
  generate_msg();
}

void loop() {
  delay(1000);
  send_aprs_bits();
}
