//test menggunakan mosuitto dengan cara:

//mosquitto_pub -h broker.mqtt-dashboard.com -t MQTT@ESP32BasicStartKitIOT/lamp2 -m "off"
// mosquitto_pub -h broker.mqtt-dashboard.com -t MQTT@ESP32BasicStartKitIOT/lamp2 -m "on"
// mosquitto_pub -h broker.mqtt-dashboard.com -t MQTT@ESP32BasicStartKitIOT/lamp1 -m "on"
// mosquitto_pub -h broker.mqtt-dashboard.com -t MQTT@ESP32BasicStartKitIOT/lamp1 -m "off"
//mosquitto_pub -h broker.mqtt-dashboard.com -t MQTT@ESP32BasicStartKitIOT/requestWindowStatus -m "window1"

//cek suhu dengan perintah
// mosquitto_sub -h broker.mqtt-dashboard.com -t MQTT@ESP32BasicStartKitIOT/suhu
// mosquitto_sub -h broker.mqtt-dashboard.com -t MQTT@ESP32BasicStartKitIOT/kelembapan
//mosquitto_sub -h broker.mqtt-dashboard.com -t MQTT@ESP32BasicStartKitIOT/windowStatus



#include <WiFi.h>
#include <ArduinoMqttClient.h>

// Pengaturan WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Pengaturan MQTT Broker
const char* broker = "broker.mqtt-dashboard.com";
int port = 1883;
const char* temperatureTopic = "MQTT@ESP32BasicStartKitIOT/suhu";
const char* humidityTopic = "MQTT@ESP32BasicStartKitIOT/kelembapan";
const char* lamp1Topic = "MQTT@ESP32BasicStartKitIOT/lamp1";
const char* lamp2Topic = "MQTT@ESP32BasicStartKitIOT/lamp2";

// Topik untuk permintaan dan umpan balik status
const char* requestWindowStatusTopic = "MQTT@ESP32BasicStartKitIOT/requestWindowStatus";
const char* requestDoorStatusTopic = "MQTT@ESP32BasicStartKitIOT/requestDoorStatus";
const char* requestPumpStatusTopic = "MQTT@ESP32BasicStartKitIOT/requestPumpStatus";

const char* windowStatusTopic = "MQTT@ESP32BasicStartKitIOT/windowStatus";
const char* doorStatusTopic = "MQTT@ESP32BasicStartKitIOT/doorStatus";
const char* pumpStatusTopic = "MQTT@ESP32BasicStartKitIOT/pumpStatus";

// Inisialisasi WiFi dan MQTT Client
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

// Pin LED
const int led1Pin = 23; // Pin LED1, bisa diganti sesuai dengan konfigurasi
const int led2Pin = 5;  // Pin LED2, bisa diganti sesuai dengan konfigurasi

// Deklarasi fungsi
void connectToWiFi();
void connectToMqttBroker();
void publishTemperature(float temperature);
void publishHumidity(float humidity);
void messageReceived(int messageSize);
void sendStatusFeedback(const char* topic, const char* status);
bool getRandomStatus();  // Tambahkan deklarasi fungsi ini di sini

void setup() {
  Serial.begin(115200);

  // Konfigurasi pin LED sebagai output
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);

  // Koneksi ke WiFi
  connectToWiFi();

  // Koneksi ke MQTT Broker
  connectToMqttBroker();

  // Subscribe ke topik lampu dan permintaan status
  mqttClient.onMessage(messageReceived);
  mqttClient.subscribe(lamp1Topic);
  mqttClient.subscribe(lamp2Topic);
  mqttClient.subscribe(requestWindowStatusTopic);
  mqttClient.subscribe(requestDoorStatusTopic);
  mqttClient.subscribe(requestPumpStatusTopic);

  // Inisialisasi random seed
  randomSeed(analogRead(0));
}

void loop() {
  if (!mqttClient.connected()) {
    connectToMqttBroker();
  }

  mqttClient.poll();

  // Publikasi data suhu dan kelembaban dummies
  float dummyTemperature = 25.0 + random(0, 100) / 10.0; // Suhu dummies antara 25.0 hingga 34.9
  float dummyHumidity = 50.0 + random(0, 100) / 10.0;    // Kelembaban dummies antara 50.0 hingga 59.9

  publishTemperature(dummyTemperature);
  publishHumidity(dummyHumidity);

  // Delay sebelum mengirim data berikutnya
  delay(5000); // Mengirim data setiap 5 detik
}

void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println(" connected.");
}

void connectToMqttBroker() {
  Serial.print("Connecting to MQTT broker");
  while (!mqttClient.connect(broker, port)) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println(" connected.");
}

void publishTemperature(float temperature) {
  if (mqttClient.beginMessage(temperatureTopic)) {
    mqttClient.print(temperature);
    mqttClient.endMessage();
    Serial.print("Published temperature: ");
    Serial.println(temperature);
  } else {
    Serial.println("Failed to publish temperature");
  }
}

void publishHumidity(float humidity) {
  if (mqttClient.beginMessage(humidityTopic)) {
    mqttClient.print(humidity);
    mqttClient.endMessage();
    Serial.print("Published humidity: ");
    Serial.println(humidity);
  } else {
    Serial.println("Failed to publish humidity");
  }
}

void messageReceived(int messageSize) {
  String topic = mqttClient.messageTopic();
  Serial.print("Received a message on topic: ");
  Serial.println(topic);

  String message;
  while (mqttClient.available()) {
    message += (char)mqttClient.read();
  }
  Serial.print("Message: ");
  Serial.println(message);

  // Kontrol LED berdasarkan pesan yang diterima
  if (topic == lamp1Topic) {
    if (message == "on") {
      digitalWrite(led1Pin, HIGH);
      Serial.println("LED1 turned on");
    } else if (message == "off") {
      digitalWrite(led1Pin, LOW);
      Serial.println("LED1 turned off");
    }
  } else if (topic == lamp2Topic) {
    if (message == "on") {
      digitalWrite(led2Pin, HIGH);
      Serial.println("LED2 turned on");
    } else if (message == "off") {
      digitalWrite(led2Pin, LOW);
      Serial.println("LED2 turned off");
    }
  }

  // Menangani permintaan status
  if (topic == requestWindowStatusTopic) {
    if (message == "window1") {
      const char* windowStatus = getRandomStatus() ? "window1 open" : "window1 close";
      sendStatusFeedback(windowStatusTopic, windowStatus);
    }
  } else if (topic == requestDoorStatusTopic) {
    const char* doorStatus = getRandomStatus() ? "ON" : "OFF";
    sendStatusFeedback(doorStatusTopic, doorStatus);
  } else if (topic == requestPumpStatusTopic) {
    const char* pumpStatus = getRandomStatus() ? "ON" : "OFF";
    sendStatusFeedback(pumpStatusTopic, pumpStatus);
  }
}

void sendStatusFeedback(const char* topic, const char* status) {
  if (mqttClient.beginMessage(topic)) {
    mqttClient.print(status);
    mqttClient.endMessage();
    Serial.print("Sent status feedback: ");
    Serial.print(topic);
    Serial.print(" - ");
    Serial.println(status);
  } else {
    Serial.println("Failed to send status feedback");
  }
}

bool getRandomStatus() {
  return random(0, 2) == 1; // Menghasilkan true (ON) atau false (OFF) secara acak
}
