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

int gps_parse(SoftwareSerial &ser);

char* parse_rmc_time(char gps_str[]);
char parse_rmc_valid(char gps_str[]);
char* parse_rmc_lat(char gps_str[]);

char* parse_rmc_time(char gps_str[])
{
  char waktu[10];
  char *result;
  int c=0;
  int i=0;

  char buff[50];

  for(int j=0;j<10;j++)
  {
    waktu[j] = 0;
  }

  for(;c<150;c++)
  {
    if(gps_str[c] == ',')
      break;
  }
  
  c++;

  while(gps_str[c] != ',')
  {
    waktu[i] = gps_str[c];
    c++;
    i++;
  }

  result = waktu;

  sprintf(buff, " waktu: %s", result);
  Serial.println(buff);
  
  return result;
}

char parse_rmc_valid(char gps_str[])
{
  char validity = 0;
  int c=0;
  int i=0;

  char buff[50];

  for(i=0;i<2;i++)
  {
    while(gps_str[c] != ',')
    {
      c++;
    }

    c++;
  }

  validity = gps_str[c];

  sprintf(buff, " GPS Fix (A=True, V=False): %c", validity);
  Serial.println(buff);

  return validity;
}

char* parse_rmc_lat(char gps_str[])
{
  char lintang[20];
  char *result;
  int c=0;
  int i=0;

  char buff[50];

  for(int j=0;j<20;j++)
  {
    lintang[j] = 0;
  }

  for(i=0;i<20;i++)
  {
    lintang[i] = '\0';
  }

  for(i=0;i<3;i++)
  {
    while(gps_str[c] != ',')
    {
      c++;
    }

    c++;
  }

  i=0;

  while(gps_str[c] != ',')
  {
    lintang[i] = gps_str[c];
    c++;
    i++;
  }

  result = lintang;

  sprintf(buff, " Latitude: %s", lintang);
  Serial.println(buff);
  
  return result;
}

char parse_rmc_NS(char gps_str[])
{
  char ns;
  int c=0;
  int i=0;

  for(i=0;i<4;i++)
  {
    while(gps_str[c] != ',')
    {
      c++;
    }

    c++;
  }

  ns = gps_str[c];

  return ns;
}

int gps_parse(SoftwareSerial &ser)
{
  char rmc[150];
  char temp;
  int c=0;

  char ser_buff[100];

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

  sprintf(ser_buff, "%s", rmc);
  Serial.println(ser_buff);

  parse_rmc_time(rmc);
  parse_rmc_valid(rmc);
  parse_rmc_lat(rmc);
  

  Serial.println(' ');
  
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
