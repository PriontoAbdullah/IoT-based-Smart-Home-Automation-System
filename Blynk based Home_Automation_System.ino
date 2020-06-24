#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

Servo servo;

char auth[] = "aba9f7cdbbe3457ba06f40adf5ca757a";
char ssid[] = "friends hub";
char pass[] = "agetakaden";

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  servo.attach(15); // NodeMCU D8 pin
  
 }
  
void loop()
{
  
  Blynk.run();
  
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
