#include <Arduino.h>

const int pirPin = 19; // Pin where the PIR sensor is connected

void setup() {
  Serial.begin(115200);
  pinMode(pirPin, INPUT);
}

void loop() {
  int pirState = digitalRead(pirPin);
  
  if (pirState == HIGH) {
    Serial.println("Object detected");
  }
  
  delay(1000); // Delay to avoid serial flooding
}