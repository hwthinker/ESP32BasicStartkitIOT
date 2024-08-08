#include <Arduino.h>

const int lineSensorPin = 5; // Pin yang digunakan untuk sensor garis

void setup() {
  // Inisialisasi Serial untuk komunikasi
  Serial.begin(115200);
  
  // Mengatur pin sensor garis sebagai input
  pinMode(lineSensorPin, INPUT);
}

void loop() {
  // Membaca status dari sensor garis
  int sensorValue = digitalRead(lineSensorPin);

  // Jika terdeteksi garis (asumsi low saat garis terdeteksi)
  if (sensorValue == LOW) {
    Serial.println("Garis terdeteksi!");
  } else {
    Serial.println("Tidak ada garis.");
  }

  // Tunggu sebentar sebelum membaca lagi
  delay(100);
}
