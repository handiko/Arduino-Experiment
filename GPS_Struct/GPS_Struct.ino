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
char parse_rmc_NS(char gps_str[]);
char* parse_rmc_lon(char gps_str[]);
char parse_rmc_EW(char gps_str[]);
char* parse_rmc_spd(char gps_str[]);
char* parse_rmc_cse(char gps_str[]);
char* parse_rmc_date(char gps_str[]);

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
  char ns=0;
  int c=0;
  int i=0;

  char buff[50];

  for(i=0;i<4;i++)
  {
    while(gps_str[c] != ',')
    {
      c++;
    }

    c++;
  }

  if(gps_str[c]!=',')
    ns = gps_str[c];

  sprintf(buff, " N/S: %c", ns);
  Serial.println(buff);

  return ns;
}

char* parse_rmc_lon(char gps_str[])
{
  char bujur[20];
  char *result;
  int c=0;
  int i=0;

  char buff[50];

  for(int j=0;j<20;j++)
  {
    bujur[j] = 0;
  }

  for(i=0;i<5;i++)
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
    bujur[i] = gps_str[c];
    c++;
    i++;
  }

  result = bujur;

  sprintf(buff, " Longitude: %s", bujur);
  Serial.println(buff);
  
  return result;
}

char parse_rmc_EW(char gps_str[])
{
  char ew=0;
  int c=0;
  int i=0;

  char buff[50];

  for(i=0;i<6;i++)
  {
    while(gps_str[c] != ',')
    {
      c++;
    }

    c++;
  }

  if(gps_str[c]!=',')
    ew = gps_str[c];

  sprintf(buff, " E/W: %c", ew);
  Serial.println(buff);

  return ew;
}

char* parse_rmc_spd(char gps_str[])
{
  char spd[10];
  char *result;
  int c=0;
  int i=0;

  char buff[50];

  for(int j=0;j<10;j++)
  {
    spd[j] = 0;
  }

  for(i=0;i<7;i++)
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
    spd[i] = gps_str[c];
    c++;
    i++;
  }

  result = spd;

  sprintf(buff, " Speed (knots): %s", spd);
  Serial.println(buff);
  
  return result;
}

char* parse_rmc_cse(char gps_str[])
{
  char cse[10];
  char *result;
  int c=0;
  int i=0;

  char buff[50];

  for(int j=0;j<10;j++)
  {
    cse[j] = 0;
  }

  for(i=0;i<8;i++)
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
    cse[i] = gps_str[c];
    c++;
    i++;
  }

  result = cse;

  sprintf(buff, " Course (degree): %s", cse);
  Serial.println(buff);
  
  return result;
}

char* parse_rmc_date(char gps_str[])
{
  char gps_date[10];
  char *result;
  int c=0;
  int i=0;

  char buff[50];

  for(int j=0;j<10;j++)
  {
    gps_date[j] = 0;
  }

  for(i=0;i<9;i++)
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
    gps_date[i] = gps_str[c];
    c++;
    i++;
  }

  result = gps_date;

  sprintf(buff, " Date: %s", gps_date);
  Serial.println(buff);
  
  return result;
}

int gps_parse(SoftwareSerial &ser)
{
  char rmc[150];
  char temp;
  int c=0;

  char ser_buff[100];

  struct Gps {
    char gps_time[10];
    char gps_valid;
    char gps_lat[15];
    char gps_ns;
    char gps_lon[15];
    char gps_ew;
    char gps_spd[10];
    char gps_cse[10];
    char gps_date[10];
  } GPS;

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

  strcpy(GPS.gps_time, parse_rmc_time(rmc));
  GPS.gps_valid = parse_rmc_valid(rmc);
  strcpy(GPS.gps_lat, parse_rmc_lat(rmc));
  GPS.gps_ns = parse_rmc_NS(rmc);
  strcpy(GPS.gps_lon, parse_rmc_lon(rmc));
  GPS.gps_ew = parse_rmc_EW(rmc);
  strcpy(GPS.gps_spd, parse_rmc_spd(rmc));
  strcpy(GPS.gps_cse, parse_rmc_cse(rmc));
  strcpy(GPS.gps_date, parse_rmc_date(rmc));

  Serial.println(' ');

  Serial.println(GPS.gps_time);
  Serial.println(GPS.gps_valid);
  Serial.println(GPS.gps_lat);
  Serial.println(GPS.gps_ns);
  Serial.println(GPS.gps_lon);
  Serial.println(GPS.gps_ew);
  Serial.println(GPS.gps_spd);
  Serial.println(GPS.gps_cse);
  Serial.println(GPS.gps_date);

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
