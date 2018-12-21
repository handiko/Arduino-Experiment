/*
 * 
 */

unsigned short crc=0xffff;
bool enable_print = 1;

/*
 * 
 */

void send_crc(void);
void calc_crc(bool in_bit);
void send_char(unsigned char in_byte);
void send_ax25(void);

/*
 * 
 */

void send_crc(void)
{
  unsigned char crc_lo;
  unsigned char crc_hi;

  crc = ~crc;

  crc_lo = crc & 0xff;
  crc_hi = (crc >> 8) & 0xff;

  send_char(crc_lo);
  send_char(crc_hi);
}

void calc_crc(bool in_bit)
{
  if((crc & 0x01) ^ in_bit)
    crc = (crc >> 1) ^ 0x8408;
  else
    crc >>= 1;
}

void send_char(unsigned char in_byte)
{
  bool in_bits;

  for(int j=0;j<8;j++)
  {
    in_bits = (in_byte >> j) & 0x01;

    calc_crc(in_bits);

    if(in_bits==0)
    {
      if(enable_print)
        Serial.print(0);
    }
    else
    {
      if(enable_print)
        Serial.print(1);
    }
  }
}

void send_ax25(void)
{
  enable_print = 0;

  crc = 0xffff;
  
  send_char('A'<<1);  
  send_char('P'<<1); 
  send_char('Z'<<1); 
  send_char('T'<<1);
  send_char('2'<<1); 
  send_char('3'<<1);
  send_char('p'<<1);

  send_char('L'<<1);
  send_char('S'<<1);
  send_char('S'<<1);
  send_char('T'<<1); 
  send_char('T'<<1);
  send_char('F'<<1);
  send_char('9'<<1);

  send_char('W'<<1);
  send_char('I'<<1); 
  send_char('D'<<1);
  send_char('E'<<1);
  send_char('2'<<1);
  send_char(' '<<1);
  send_char((2<<1) + 1);

  send_char(0x03);
  send_char(0xf0);

  send_char('.');
  //send_char('T');
  //send_char('E');
  //send_char('S');
  //send_char('T');

  enable_print = 1;

  send_crc();
}

/*
 * 
 */

void setup()
{
  pinMode(LED_BUILTIN, HIGH);
  pinMode(2, HIGH);
  
  Serial.begin(115200);

  delay(2000);
  Serial.println("Printing CRC16-CCITT bit-stream");
  Serial.println(' ');
  send_ax25();
  Serial.println(" (Calculated)");
  Serial.println("1100111110110111 (Desired)");
  Serial.println(' ');
  Serial.println("Printing stopped");
  Serial.println(' ');
}

void loop()
{
  
}
