#include <ThingSpeak.h>
#include <WiFi.h>

#include <dht11.h>
#define DHT11PIN 5

dht11 DHT11;

char* ssid = "Wifi-SSID"; //enter SSID
char* passphrase = "PASSWORD";//enter password
WiFiServer server(80);
WiFiClient client;

unsigned long myChannelNumber = 1;
const char * myWriteAPIKey = "DO2I813HVUOMCPCR";

unsigned long lastTime = 0;
unsigned long timerDelay = 1000;

void  setup()
{
  Serial.begin(9600); //Initialize serial

Serial.print("Connecting to ");

Serial.println(ssid);

WiFi.begin(ssid, passphrase);

while (WiFi.status() != WL_CONNECTED) {

delay(500);

Serial.print(".");

}

// Print local IP address and start web server

Serial.println("");

Serial.println("WiFi connected.");

Serial.println("IP address: ");

Serial.println(WiFi.localIP());

server.begin();
ThingSpeak.begin(client);
}

void loop()
{
  Serial.println();

  int chk = DHT11.read(DHT11PIN);
  float h = (float)DHT11.humidity;
  float t = (float)DHT11.temperature;

  Serial.print("Humidity (%): ");
  Serial.println(h);

  Serial.print("Temperature  (C): ");
  Serial.println(t);

 delay(2000);
 if(WiFi.status() == WL_CONNECTED){
   Serial.println(WiFi.localIP());

 int value = analogRead(AOUT_PIN); // read the analog value from sensor

  if (value < THRESHOLD)
    Serial.print("The soil is DRY (");
  else
    Serial.print("The soil is WET (");

  Serial.print(value);
  Serial.println(")");


  delay(500);
 }

ThingSpeak.setField(1, t);

ThingSpeak.setField(2, h);
ThingSpeak.setTwitterTweet(3, value)

int x = ThingSpeak.writeFields(myChannelNumber,

myWriteAPIKey);

if(x == 200){

Serial.println("Channel update successful.");

}

else{

Serial.println("Problem updating channel. HTTP error code " + String(x));
}

}