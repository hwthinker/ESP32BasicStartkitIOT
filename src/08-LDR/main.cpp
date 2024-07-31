#include <Arduino.h>

const int analogPin = 35;  // GPIO35

void setup() {
    Serial.begin(115200);
    // Initialize the analog pin
    analogReadResolution(12); // Set the resolution to 12 bits (0-4095)
}

void loop() {
    int analogValue = analogRead(analogPin);
    Serial.print("Analog value: ");
    Serial.println(analogValue);
    delay(1000); // Delay 1 second
}
