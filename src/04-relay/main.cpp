#include <Arduino.h>

#define RLY1 25
#define RLY2 26
#define LED 23
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(RLY1, OUTPUT);
   pinMode(RLY2, OUTPUT);
  pinMode(LED, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(RLY1, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(RLY1, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);    

  digitalWrite(RLY2, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(RLY2, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);   
  
  digitalWrite(LED, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                   // wait for a second
}
