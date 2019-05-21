#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include "Webpage.h"

#define MTR_RLY D0
#define LED D1
#define BUZZ D4

const char* deviceName = "autoplantwatering";

//On board LED Connected to GPIO2
//#define LED 2

//SSID and Password of your WiFi router
const char* ssid = "Damden212";
const char* password = "9739520911";

String req;
unsigned char states = 0;
unsigned int time_count = 0;
String on_off = "OFF";
int count=0;
int i =0;
bool out = 0;
int client_available = 0;

WiFiServer server(80);

void SSID_IP_show(void)
{
  unsigned char s = 0; 
  char temp[16];
  memset(temp, 0x00, sizeof(temp));
  for(s = 0; s < 10; s++)
  {
    Serial.print(temp[s]);
  }

  for(s = 0; s < 16; s++)
  {
    Serial.print(temp[s]);
  }
  delay(200);
}
void WiFi_details(void)
{

  Serial.print("WiFi connected");
 
  server.begin();
  Serial.print("Server Started");
  delay(4000);

  SSID_IP_show();
  delay(6000);

  WiFi.hostname("espfi");
  MDNS.begin("espfi"); 
}


void WiFi_setup(void)
{
  char s = 15;

  //digitalWrite(D1, HIGH);
  WiFi.mode(WIFI_STA);
  delay(1000);

  WiFi.begin("Damden212","9739520911");

  digitalWrite(LED, LOW);
  
  while(s > 0)
  {
      Serial.print("Connecting WiFi.");

      digitalWrite(LED, HIGH);
      delay(200);
      digitalWrite(LED, LOW);
      delay(200);
       
      Serial.print(".");
      s--;
  };

  
  if(WiFi.status() != WL_CONNECTED) 
  {
      //digitalWrite(LED, HIGH);

      Serial.print("Attempting WPS.");
      
      WiFi.beginWPSConfig();
      digitalWrite(LED, LOW);
      delay(4000);
      
      if (WiFi.status() == WL_CONNECTED) 
      {       
        digitalWrite(LED, HIGH);
        WiFi_details(); 
      }
      else 
      {
        digitalWrite(LED, LOW);

        Serial.print("Connection");

        Serial.print("Failed");
        delay(1000);

        Serial.print("Retrying");  
        delay(1000);    
        //ESP.restart();
      }
  }
  else 
  {
    digitalWrite(LED, LOW);

    Serial.print("Connection");
    Serial.print("Established!");
    delay(1600);
    
    WiFi_details(); 
  }
}

void setup() 
{
  Serial.begin(9600);
  pinMode(D0, OUTPUT); 
  pinMode(D1, OUTPUT);
  pinMode(D4, OUTPUT);
  digitalWrite(MTR_RLY, HIGH);
  
  WiFi_setup();
  delay(3000);
  Serial.print(WiFi.localIP());
  count = 0;

  digitalWrite(MTR_RLY, LOW);
  //digitalWrite(BUZZ, HIGH);
  delay(3000);
  //digitalWrite(BUZZ, LOW);
  delay(2000);
  digitalWrite(MTR_RLY, HIGH);


//  WiFi.config(staticIP, subnet, gateway, dns);
  
}

void loop() 
{
    WiFiClient client = server.available();

    digitalWrite(LED, LOW);
    delay(500);
    digitalWrite(LED, HIGH);
    delay(500);
    
    if(client == 0) 
    { 
      Serial.print("Client is 0   ");
    //  return;
    }
    else
    {
      Serial.print("Client is 1   "); 
    }
  
    //while
    if(!client.available())
    {
      time_count++;
      Serial.print("Time Count = :");
      Serial.print(time_count);
      delay(1);
      client_available = 0;  
    }
    else
    {
      client_available = 1; 
    }

    //client_available = 1;
/*
    if (client_available)
    {
      Serial.print("Client Avalable.......... ");
      client.flush();
      client.print(file);
      client.print("<p align=center> <font color=Yellow> Motor  :  ");
      client.print(on_off);
      client.print("\nCount = : ");
      client.print(count);    
    }

*/


    req = client.readStringUntil('\r');

    delay(1000);
    count = count + 1;
    Serial.print("Count = :");
    Serial.print(count);
        
    //client.flush();    
    
    // one count = ~2sec
    // 70 secs. = 11
    // 2hr      = 1135
    if((req.indexOf("ON0") != -1)|| ( count > 1134 && count < 1138 ))
    {
      digitalWrite(MTR_RLY, LOW);
      states |= 0x01;
      on_off = "ON";

      digitalWrite(BUZZ, HIGH);
      delay(3000);
      digitalWrite(BUZZ, LOW);
      delay (7000);
      digitalWrite(MTR_RLY, HIGH);
      count = 0;
      on_off = "OFF";
      
      if (client_available)
      {
        Serial.print("Client Avalable.......... ");
        client.flush();
        client.print(file);
        client.print("<p align=center> <font color=Yellow> Motor  :  ");
        client.print(on_off);
        client.print("\nCount = : ");
        client.print(count);    
      }
    }
    else if(req.indexOf("OFF0") != -1) 
    {
      digitalWrite(MTR_RLY, HIGH);
      states &= ~0x01;
      on_off = "OFF";
    }

    if (client_available)
    {
      Serial.print("Client Avalable.......... ");
      client.flush();
      client.print(file);
      client.print("<p align=center> <font color=Yellow> Motor  :  ");
      client.print(on_off);
      client.print("\nCount = : ");
      client.print(count);    
    }
 
    SSID_IP_show();
}
