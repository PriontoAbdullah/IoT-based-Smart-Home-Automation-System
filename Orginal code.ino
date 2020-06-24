#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>


#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define D1 5 // GPIO5
#define D2 4 // GPIO5
#define D3 0 // GPIO5
#define D4 2 // GPIO5

Servo servo;


char auth[] = "aba9f7cdbbe3457ba06f40adf5ca757a";
char ssid[] = "friends hub";
char pass[] = "agetakaden";


String  Request;
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME  "CreativeIoT"
#define AIO_KEY  "84e007aaa0cf4e9790a637a2f23c6afc"
WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe homefeed = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/homefeed");
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
  Serial.begin(9600);
  Request = "";

  Blynk.begin(auth, ssid, pass);

  servo.attach(15); // NodeMCU D8 pin

  WiFi.disconnect();
  delay(3000);
  Serial.println("Start IoT");
  WiFi.begin("friends hub", "agetakaden");
  while ((!(WiFi.status() == WL_CONNECTED))) {
    delay(300);
    Serial.print(".");

  }
  Serial.println("Wifi Connected");
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP().toString()));

  mqtt.subscribe(&homefeed);

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
   pinMode(D4, OUTPUT);

  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
}


void loop()
{

  Blynk.run();


  if (MQTT_connect()) {
    Adafruit_MQTT_Subscribe *subscription_name;
    while ((subscription_name = mqtt.readSubscription(5000))) {
      if (subscription_name == &homefeed) {
        Request = ((char *)homefeed.lastread);
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
          Serial.println("Blue light turn OFF");
        }
        if (Request == "d4on") {
          digitalWrite(D4, LOW);
          Serial.println("LED ON");
        }
        if (Request == "d4off") {
          digitalWrite(D4, HIGH);
          Serial.println("LED OFF");
        }

      }

    }

  }

}

BLYNK_WRITE(V1)
{
  servo.write(45);
}

BLYNK_WRITE(V2)
{
  servo.write(90);
}

BLYNK_WRITE(V3)
{
  servo.write(135);
}

BLYNK_WRITE(V4)
{
  servo.write(180);
}