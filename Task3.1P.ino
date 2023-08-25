
#include <DHT.h>
#include <WiFiNINA.h>
#include <ThingSpeak.h>

#define DHT_PIN 2
#define DHT_TYPE DHT11

char *wifiSSID = "Ekam";     
char *wifiPass = "ekam12345";

unsigned long myChannelID = 2250564;        
const char *myAPIKey = "6X1MTHKWTF3EX2YA";

DHT myDHT(DHT_PIN, DHT_TYPE);

WiFiClient myClient;

unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 30000;  // Update every 30 seconds

void setup() {
  Serial.begin(9600);
  myDHT.begin();
  connectToWiFi();
  ThingSpeak.begin(myClient);
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastUpdateTime >= updateInterval) {
    lastUpdateTime = currentTime;
    
    
    float humid = myDHT.readHumidity();

    if ( !isnan(humid)) {
      sendToThingSpeak( humid);
    } else {
      Serial.println("Can't read Sensor");
    }
  }
}

void connectToWiFi() {
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to WiFi...");
    WiFi.begin(wifiSSID, wifiPass);
    delay(1000);
  }
  Serial.println("Connected to WiFi");
}

void sendToThingSpeak( float humid) {
  ThingSpeak.setField(1, humid);
  
  int statusCode = ThingSpeak.writeFields(myChannelID, myAPIKey);

  if (statusCode == 200) {
    Serial.println("Data sent successfully");
  } else {
    Serial.println("Error sending data");
  }
}
Q1. Provide a brief summary (less than two paragraphs) of your understanding of Webhooks and their usage.
Ans Webhooks are used when we want to know when a certain event is triggered on any kind of website or app, and this data can be sent to another website immediately by the use of webhooks. Webhooks are the ways for the interaction and data transfer between websites.
These can be really useful in cases like when we have to send real time data and work upon it automatically, for example: when someone enters a room, sensor senses it and it sends data to other websites through webhook, then this website can work accordingly.
Q2: Describe the steps you have taken to create this application similar to an instruction manual. Use bullet points and be concise when possible. Your instructions should be enough for another person reading them to recreate what you have done (You might as well opt for creating a video)
Ans    
•	First of all, I created an account on ThingsSpeak, before creating a data channel and setting up the fields, in this case it was just humidity.
•	Now, established the hardware connections between dht11 and Arduino nano
•	Now while writing the software code for sending the data through webhook , first some libraries need to be imported including WifiNina(for setting wifi up), dht.h(for reading humidity) and thingSpeak.h(for setting up connection and sending data between thingSpeak and application).
•	Then, wifiSSID and password should be initialized and connected with Arduino nano 33 iot, before taking readings and sending them
•	Once connected, readings of humidity are taken every 30 seconds and then sent to thingSpeak using the channel Id and apikey (make sure it is the write api key, not the read one).
•	Now you will bee able to see a graph forming on the data channel.

