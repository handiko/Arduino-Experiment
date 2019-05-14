#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>

#include <PubSubClient.h>

ESP8266WiFiMulti wifiMulti;
WiFiClient espClient;
PubSubClient client(espClient);

const char* brokerUser = "handikogesang@gmail.com";
const char* brokerPass = "45f02257";
const char* broker = "mqtt.dioty.co";
const char* outTopic = "/handikogesang@gmail.com/out";
const char* inTopic = "/handikogesang@gmail.com/in";

long currentTime, lastTime;
//int count = 0;
char messages[50];
bool enADC = false;

void setupWiFi()
{
  delay(100);
  
  wifiMulti.addAP("YC1SDL", "Metallica");
  wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2");
  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");

  Serial.println("Connecting ...");

  digitalWrite(LED_BUILTIN, LOW);

  while (wifiMulti.run() != WL_CONNECTED) 
  {
    delay(250);
    Serial.print('.');
  }

  digitalWrite(LED_BUILTIN, HIGH);
  
  Serial.println('\n');
  Serial.print("Connected to:\t");
  Serial.println(WiFi.SSID());
  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
}

void reconnect()
{
  while(!client.connected())
  {
    Serial.print("\nConnecting to ");
    Serial.println(broker);

    if(client.connect("WimosD1", brokerUser, brokerPass))
    {
      Serial.print("\nConnected to ");
      Serial.println(broker);
      client.subscribe(inTopic);
    }
    else
    {
      Serial.println("Connecting");
      delay(2500);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int len)
{
  Serial.print("Received messages: ");
  Serial.println(topic);
  for(unsigned int i=0; i<len; i++)
  {
    Serial.print((char) payload[i]);

    if(len == 1 && payload[0] == '1')
    {
      digitalWrite(LED_BUILTIN, LOW);
      enADC = true;
    }
    else if(len == 1 && payload[0] == '0')
    {
      digitalWrite(LED_BUILTIN, HIGH);
      enADC = false;
    }
  }
  Serial.println();
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A0,INPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  
  Serial.begin(115200);
  setupWiFi();
  client.setServer(broker, 1883);
  client.setCallback(callback);
}

void loop()
{
  int adcValue;
  
  if(!client.connected())
  {
    reconnect();
  }

  client.loop();

  currentTime = millis();
  if(currentTime - lastTime > 2000)
  {
    //count++;
    //snprintf(messages, 75, "Count: %d", count);

    if(enADC)
    {
      adcValue = analogRead(A0);
      snprintf(messages, 75, "ADC Value: %d", adcValue);
    }
    else
    {
      snprintf(messages, 50, "ADC is not enabled");
    }

    if(client.connected())
    {
      Serial.print("Still Connected, ");
    }
    Serial.print("Sending messages:\t");
    Serial.println(messages);
    
    client.publish(outTopic, messages);
    
    lastTime = millis();
  }
}
