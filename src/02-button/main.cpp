#include <Arduino.h>

const int btn1Pin = 16; // Pin where the PIR sensor is connected
const int btn2Pin = 17; // Pin where the PIR sensor is connected

void setup() {
  Serial.begin(115200);
  pinMode(btn1Pin, INPUT);
  pinMode(btn2Pin, INPUT);
}

void loop() {
  int btn1State = digitalRead(btn1Pin);
  int btn2State = digitalRead(btn2Pin);
  
  if (btn1State == LOW) {
    Serial.println("button1 pressed");
  }
  
  if (btn2State == LOW) {
    Serial.println("button2 pressed");
  }
  delay(20); // Delay to avoid serial flooding
}