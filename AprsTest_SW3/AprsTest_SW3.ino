/*
 * 
 */

unsigned char send_bytes[]={
  0x86, 0xA2, 0x40, 0x40, 0x40, 0x40, 0x60, 0xAE, 0x64, 0x8C, 0xA6,
  0x40, 0x40, 0x68, 0xA4, 0x8A, 0x98, 0x82, 0xB2, 0x40, 0x61, 0x03,
  0xF0, 0x54, 0x65, 0x73, 0x74};

char stuff=0;
unsigned short crc=0xffff;
bool nada=0;

/*
 * 
 */

void set_nada(bool in_nada);
void send_char(unsigned char in_byte);
void send_ax25(void);

/*
 * 
 */

void send_char(unsigned char in_byte)
{
  if(in_byte == 0x7e)
  {
    for(int j=0;j<8;j++)
    {
      if(in_byte & 0x01)
        set_nada(nada);
      else
      {
        nada^=1;
        set_nada(nada);
      }
    }
    crc = 0xffff;
    stuff = 0;
  }

  else
  {
    for(int j=0;j<8;j++)
    {
      if(in_byte & 0x01)
      {
        set_nada(nada);
        stuff++;

        if(stuff == 5)
        {
          nada^=1;
          set_nada(nada);
          stuff=0;
        }
      }
      else
      {
        nada^=1;
        set_nada(nada);
        stuff=0;
      }
    }
  }

  in_byte >>= 1;
}

void send_ax25(void)
{
  for(int i=0;i<100;i++)
    send_char(0x7e);
    
  send_char(0x86);  //  C
  send_char(0xa2);  //  Q
  send_char(0x40);  //  sp
  send_char(0x40);  //  sp
  send_char(0x40);  //  sp
  send_char(0x40);  //  sp
  send_char(0x60);  //  0

  send_char(0xae);  //  W
  send_char(0x64);  //  2
  send_char(0x8c);  //  F
  send_char(0xa6);  //  S
  send_char(0x40);  //  sp
  send_char(0x40);  //  sp
  send_char(0x68);  //  4

  send_char(0xa4);  //  R
  send_char(0x8a);  //  E
  send_char(0x98);  //  L
  send_char(0x8a);  //  A
  send_char(0xb2);  //  Y
  send_char(0x40);  //  sp
  send_char(0x61);  //  0

  send_char(0x03);  //  crtl
  send_char(0xf0);  //  pid

  send_char(0x54);  //  T
  send_char(0x65);  //  e
  send_char(0x73);  //  s
  send_char(0x74);  //  t

  for(int i=0;i<3;i++)
    send_char(0x7e);
}

/*
 * 
 */

void setup()
{
  pinMode(LED_BUILTIN, HIGH);
  pinMode(2, HIGH);
}

void loop()
{
  
}
