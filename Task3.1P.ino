
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

