#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>


SoftwareSerial s(12, 14);
char auth[] = ".....";
char ssid[] = ".....";
char pass[] = ".....";

void setup() {
  Serial.begin(115200);
  // Initialize Serial port
  s.begin(115200);
  Blynk.begin(auth, ssid, pass);
}

void loop() {

  Blynk.run();

  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
  if (root == JsonObject::invalid())
    return;

  Serial.print("Temp:");
  float  data1 = root["Temp"];
  Blynk.virtualWrite(V0, data1);
  Serial.println(data1, 1);
  data1 = 0;

}
