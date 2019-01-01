/*
 * 
 */

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

void setup()
{
  Serial.begin(115200);

  set_timer1();
}

void loop()
{
  
}
