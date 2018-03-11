
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>

#define ONE_WIRE_BUS D4

String apiKey = "IZKOAAHOOOQH3RVP";     
const char *ssid =  "SSGG";     
const char *pass =  "ee45T#p1";
const char* server = "api.thingspeak.com";

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);
WiFiClient client;
 
void setup() 
{
  Serial.begin(115200);
  delay(10);
  sensors.begin();
  
  Serial.print("Connecting: ");
  Serial.println(ssid);

  //WiFi.mode(WiFi_STA);
  //WiFiMulti.addAP(ssid, pass); 오직 1개의 AP만 사용할 것이기에 필요없음.
  WiFi.begin(ssid, pass);
  int cnt = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print("^");
    if(++cnt==40){cnt=0; Serial.println("");}
  }
  Serial.println("\nWiFi connected");
}
 
void loop() 
{
  sensors.requestTemperatures(); 
  float temp = sensors.getTempCByIndex(0);
  if(isnan(temp)){
    Serial.println("There is no value from Ds18b20 sensor.");
    return;
   }

  if (client.connect(server,80))  
  {  
    String postStr = apiKey;
    postStr +="&field1=";
    postStr += String(temp);
    postStr += "\r\n\r\n";
 
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
 
    Serial.print("Temperature(->Thingspeak): ");
    Serial.println(temp);
    client.stop();
    Serial.println("Wait 60 seconds for reflesh Thingspeak.");
    delay(60000);
  }
  else
  {
    Serial.println("cannot connect.");
  }
}

