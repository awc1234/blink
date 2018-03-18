#include <OneWire.h> 
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
 #include <TimeLib.h>
#define ONE_WIRE_BUS D4
#define DEF_IFTTT
//#define DEF_THINGSPEAK

const char *ssid =  "ssid";     // replace with your wifi ssid and wpa2 key
const char *pass =  "pass";

#ifdef DEF_IFTTT
#define IFTTT_KEY "IFTTT_KEY"
#define IFTTT_EVENT "IFTTT_EVENT"
#define IFTTT_HOST "maker.ifttt.com"
const char* server = "maker.ifttt.com";
#else
String apiKey = "apiKey";     //  Enter your Write API key from ThingSpeak
const char* server = "api.thingspeak.com";
#endif

OneWire oneWire(ONE_WIRE_BUS);
/* Pass 'our oneWire reference' to Dallas Temperature. */
DallasTemperature sensors(&oneWire);
WiFiClient client;
 
void setup() 
{
  Serial.begin(115200);
  delay(10);
  sensors.begin();
  
  Serial.print("Connecting: ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, pass);
  int cnt = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print("^");
    if(++cnt==40){cnt=0; Serial.println("");}
  }
  Serial.println("\nWiFi connected");
  setTime(10,30,00,18, 3, 2018);
}
String find_time()
{
    time_t t = now();
    return String(year(t))+"-"+String(month(t))+"-"+String(day(t));
}
#ifdef DEF_THINGSPEAK
void f_thingspeak(float temp)
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
}
#endif

#ifdef DEF_IFTTT
void f_ifttt(float temp)
{
    String postStr = "{\"value1\":\""+String(temp)+"\","
                   + "\"value2\":\"" +find_time()+"\","
                   + "\"value3\":\"" + "from my room"
                   + "\"}";  
    /* trigger/ds18b20/with/key/Key*/
    String url = "POST /trigger/"+String(IFTTT_EVENT)+"/with/key/"+String(IFTTT_KEY)
               + " HTTP/1.1\r\n"+"Host: "+String(IFTTT_HOST)+"\r\n"
               + "Content-Type: application/json\r\n"+"Content-Length: "
               + String(postStr.length())+"\n\n"; 
    client.print(url+postStr);  
}
#endif
void loop() 
{
  sensors.requestTemperatures(); 
  float temp = sensors.getTempCByIndex(0);
  if(isnan(temp)){
    Serial.println("There is no value from Ds18b20 sensor.");
    return;
   }

  if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
  { 
    #ifdef DEF_IFTTT
      f_ifttt(temp);
    #else
      f_thingspeak(temp);
    #endif
    Serial.print("Temperature(->Webhook or Thingspeak): ");
    Serial.println(temp);
    client.stop();
    Serial.println("Wait 5 seconds for reflesh Thingspeak.");
    delay(5000);/*60000*/
  }
  else
  {
    Serial.println("cannot connect.");
  }
}
