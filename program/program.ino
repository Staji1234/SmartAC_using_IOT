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
 float a,b,temp;
 int p;
 p=analogRead(A0);
 temp=0.0009765*p*100;
 Serial.println(temp);
 ThingSpeak.writeField(309969,3,temp,"E9X9ORK1Q5JKRBP6");// writes temperature to thingspek
 
 b=ThingSpeak.readFloatField(309969,2,"3GD5N8JBZJKFHQLI");//auto/man field status
 Serial.println(b);

 if(b==1)//manual 
 {
 a=ThingSpeak.readFloatField(309969,1,"3GD5N8JBZJKFHQLI");//variable a saves the value in thingspeak LED status
 Serial.println(a);
 if(a==1)//if the data send has the word ON then led gets ON
  { 
    digitalWrite(13,HIGH);
  }
  if(a==0)//if the data send has the word OFF then led gets OFF
  { 
    digitalWrite(13,LOW);
  }
 }
 
 if(b==0)//automatic
 { 
 if(temp>37)
 {
  digitalWrite(13,HIGH);
 }
 if(temp<=37)
 {
  digitalWrite(13,LOW);
 }
 }
 //delay(20000);
}
