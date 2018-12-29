/*
 * 
 */
 
#include <Cmd.h>

char string[100];
char str_len;
int var = 0;

void debug(int arg_cnt, char **args)
{
  Serial.println("Hello World !");
  if(arg_cnt > 0)
  {
    var = cmdStr2Num(args[1], 10);
    Serial.print(var, DEC);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(9600);
  
  cmdInit(&Serial);
  cmdAdd("DEBUG", debug);
}

void loop() {
  // put your main code here, to run repeatedly:
  cmdPoll();

  analogWrite(LED_BUILTIN, var);
}
