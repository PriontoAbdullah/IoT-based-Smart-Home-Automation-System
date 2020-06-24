
#include <ESP8266WiFi.h>

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define D1 5 // GPIO5
#define D2 4 // GPIO5
#define D3 0 // GPIO5

String  Request;
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME  "adafruit username"
#define AIO_KEY  "adafruit AIO key"
WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe yourfeedName = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/yourfeedName");
boolean MQTT_connect();

boolean MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) {
    return true;
  }  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) {
    mqtt.disconnect();
    delay(2000);
    retries--;
    if (retries == 0) {
      return false;
    }
  } return true;
}

void setup()
{
  Serial.begin(115200);
  Request = "";

  WiFi.disconnect();
  delay(3000);
  Serial.println("Start IoT");
  WiFi.begin("your wifi name", "your wifi password");
  while ((!(WiFi.status() == WL_CONNECTED))) {
    delay(300);
    Serial.print(".");

  }
  Serial.println("Wifi Connected");
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP().toString()));

  mqtt.subscribe(&"yourfeedName");

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);

  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
}


void loop()
{

  if (MQTT_connect()) {
    Adafruit_MQTT_Subscribe *subscription_name;
    while ((subscription_name = mqtt.readSubscription(5000))) {
      if (subscription_name == &"yourfeedName") {
        Request = ((char *)"yourfeedName".lastread);
        if (Request == "d1on") {
          digitalWrite(D1, LOW);
          Serial.println("Red light turn ON");
        }
        if (Request == "d1off") {
          digitalWrite(D1, HIGH);
          Serial.println("Red light turn OFF");
        }

        if (Request == "d2on") {
          digitalWrite(D2, LOW);
          Serial.println("Blue light turn ON");
        }
        if (Request == "d2off") {
          digitalWrite(D2, HIGH);
          Serial.println("Fan turn OFF");
        }

        if (Request == "d3on") {
          digitalWrite(D3, LOW);
          Serial.println("Blue light turn ON");
        }
        if (Request == "d3off") {
          digitalWrite(D3, HIGH);
          Serial.println("Fan turn OFF");
        }

      }

    }

  }

}
