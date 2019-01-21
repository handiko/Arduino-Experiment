/*
 *  Copyright (C) 2018 - Handiko Gesang - www.github.com/handiko
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include <SoftwareSerial.h>

SoftwareSerial gps = SoftwareSerial(8, 9);

struct GPS 
{
  char time_fix[10];
  char valid;
  char lati[12];
  char NS;
  char lon[12];
  char EW;
  char spd[10];
  char cse[10];
  char date_fix[10];
  char magnetic[10];
  char mag_EW;
  char check[5];
};

int parse_rmc_time(char gps_str[])
{
  int c=0;
  int i;

  for(;c<150;c++)
  {
    if(gps_str[c] == ',')
      break;
  }
  
  c++;

  Serial.print(" nilai c: ");
  Serial.println(c);

  while(gps_str[c] != ',')
  {
    GPS.time_fix[i] = gps_str[c];
    c++;
    i++;
  }

  Serial.print(" nilai i: ");
  Serial.println(i);
  
  return i;
}

int gps_parse(SoftwareSerial &ser)
{
  char rmc[150];
  char temp;
  int c=0;

  for(int i=0;i<150;i++)
    rmc[i]='\0';

  do
  {
    if(ser.available()>0)
      temp = ser.read(); 
  }
  while(temp!='$');

  rmc[c] = temp;
  c++;

  do
  {
    if(ser.available()>0)
    {
      temp = ser.read();
      rmc[c] = temp;
      c++;
    }

    if(c==6)
    {
      if(rmc[5]!='C')
      {
        return 0;

        goto esc;
      }
    }
  }
  while((temp!=10)&&(temp!=13));

  c--;

  Serial.println(rmc);
  parse_rmc_time(rmc);
  
  return c;

  esc:
  ;
}

void setup()
{
  Serial.begin(115200);
  
  Serial.println(" ");
  Serial.print("Sketch:   ");   Serial.println(__FILE__);
  Serial.print("Uploaded: ");   Serial.println(__DATE__);
  Serial.println(" ");
  
  Serial.println("GPS Struct Test - Started ! \n");

  gps.begin(9600);
}

void loop()
{
  gps_parse(gps);
}
