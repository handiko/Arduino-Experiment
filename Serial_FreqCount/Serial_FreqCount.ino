// period of pulse accumulation and serial output, milliseconds
#define MainPeriod 10
long previousMillis = 0; // will store last time of the cycle end
volatile unsigned long duration=0; // accumulates pulse width
volatile unsigned int pulsecount=0;
volatile unsigned long previousMicros=0;

float freq1,freq2=0,freq3=0,freq4=0,freq5=0,freq6=0,freq7=0,freq8=0,freq9=0,freq10=0;

void setup()
{
  Serial.begin(19200); 
  attachInterrupt(digitalPinToInterrupt(3), myinthandler, RISING);
}

void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= MainPeriod) 
  {
    previousMillis = currentMillis;   
    // need to bufferize to avoid glitches
    unsigned long _duration = duration;
    unsigned long _pulsecount = pulsecount;
    duration = 0; // clear counters
    pulsecount = 0;
    float Freq = 1e6 / float(_duration);
    Freq *= _pulsecount; // calculate F
    // output time and frequency data to RS232
    freq1=freq2;
    freq2=freq3;
    freq3=freq4;
    freq4=freq5;
    freq5=freq6;
    freq6=freq7;
    freq7=freq8;
    freq8=freq9;
    freq9=freq10;
    freq10=Freq;

    Freq=(freq1+freq2+freq3+freq4+freq5+freq6+freq7+freq8+freq9+freq10)/10;
    
    //Serial.print(currentMillis);
    //Serial.print(" "); // separator!
    Serial.println(Freq);
    //Serial.print(" "); 
    //Serial.print(_pulsecount);
    //Serial.print(" ");
    //Serial.println(_duration);
  }
}

void myinthandler() // interrupt handler
{
  unsigned long currentMicros = micros();
  duration += currentMicros - previousMicros;
  previousMicros = currentMicros;
  pulsecount++;
}
