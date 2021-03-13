#include <SoftwareSerial.h>
#include <ArduinoJson.h>


SoftwareSerial portOne(10, 11);
SoftwareSerial portTwo(5, 6);

String inputString     = "";
boolean stringComplete = false;

int HexInt = 0;
String HexString = "00";

void setup() {
  Serial.begin(115200);

  portOne.begin(115200);
  portTwo.begin(115200);
  inputString.reserve(200);
  delay(500);
}

void loop() {
  portOne.listen();
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  // while there is data coming in, read it
  // and send to the hardware serial port:

  serialEvent();
  if (stringComplete) {
    HexInt = inputString.toInt();
    HexString = String(HexInt, HEX);
    if (HexInt < 16) HexString = "0" + HexString ;
    HexString.toUpperCase();
    Serial.println(inputString);
    if (inputString.indexOf("WEAK LOW") > 0) {
      
      root["Temp"] = inputString.substring(9, 16).toFloat();
      Serial.println(inputString.substring(9, 16).toFloat());
      while (portOne.available())
      {
        Serial.println(inputString.substring(9, 16).toFloat());
        root.printTo(portTwo);
        break;
      }
    }
    stringComplete = false;
    inputString = "";
  }
}

void serialEvent() {
  while (portOne.available()) {
    char inChar = (char)portOne.read();
    if (inChar == '\n') continue;
    if (inChar == '\r') {
      stringComplete = true;
      if (inputString == "") inputString = "NULL";
      inputString.toUpperCase();
      continue;
    }
    inputString += inChar;
  }
}
