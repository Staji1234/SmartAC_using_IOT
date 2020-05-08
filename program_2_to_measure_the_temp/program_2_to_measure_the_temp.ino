
#include<ESP8266WiFi.h>
WiFiClient iotclient; //globally declaring client
#include "ThingSpeak.h"//including things speak
void setup() 
{
  Serial.begin(9600);
  ThingSpeak.begin(iotclient);//starting things speak as server
  WiFi.mode(WIFI_STA);//declaring ESP as station 
  WiFi.begin("MBLAZE-AC3633R2-9D45","cinderella");//connecting ESP to the available WiFi device
  while (WiFi.status()!=WL_CONNECTED)//connecting ESP to WiFi
  {
    delay(100);
  }
  Serial.print(WiFi.localIP());
  pinMode(13,OUTPUT); 

}

void loop()
{
 int a;
 float temp;
 a=analogRead(A0);
 temp=0.0009765*a*100;
 Serial.println(temp);
// ThingSpeak.writeField(309969,3,temp,"E9X9ORK1Q5JKRBP6");// writes 'a' to thingspeak
// delay(20000);
}
