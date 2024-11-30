### Tutorial: Menggunakan MQTT dengan ESP32 untuk Kontrol Perangkat dan Feedback Status

Pada tutorial ini, kita akan menghubungkan ESP32 ke broker MQTT untuk mengontrol beberapa perangkat seperti lampu, jendela, pintu, dan pompa. Selain itu, kita juga akan menerima dan mengirimkan data sensor, seperti suhu dan kelembaban, menggunakan MQTT.

**Prasyarat:**

1. **ESP32**: Digunakan untuk mengontrol perangkat dan membaca data sensor.
2. **WiFi**: ESP32 terhubung ke WiFi untuk dapat mengakses broker MQTT.
3. **Broker MQTT**: Menggunakan broker publik seperti `broker.mqtt-dashboard.com` untuk komunikasi data.
4. **Mosquitto**: Digunakan untuk mengirimkan dan menerima pesan melalui MQTT dari terminal.

**Langkah-langkah:**

1. **Persiapkan Hardware dan Koneksi**
   - Sambungkan ESP32 ke WiFi dengan memasukkan SSID dan password di kode.
   - Sambungkan perangkat yang ingin Anda kontrol (misalnya lampu) ke pin output ESP32.
2. **Konfigurasi MQTT**
   - Menggunakan topik MQTT untuk mengontrol perangkat, seperti lampu, dan mendapatkan data status perangkat lainnya.
   - Kode ini mengirimkan data suhu dan kelembaban secara periodik ke broker MQTT.
3. **Pengendalian Perangkat**
   - Dengan menggunakan perintah MQTT, Anda bisa menghidupkan atau mematikan perangkat seperti lampu melalui topik MQTT yang telah didefinisikan.
   - Misalnya, perintah `mosquitto_pub -h broker.mqtt-dashboard.com -t MQTT@ESP32BasicStartKitIOT/lamp1 -m "on"` akan menyalakan lampu yang terhubung ke ESP32.
4. **Feedback Status**
   - ESP32 juga dapat mengirimkan status perangkat lainnya, seperti jendela, pintu, dan pompa, melalui topik tertentu seperti `windowStatus`, `doorStatus`, dan `pumpStatus`.
   - Anda dapat meminta status perangkat menggunakan perintah seperti `mosquitto_pub -h broker.mqtt-dashboard.com -t MQTT@ESP32BasicStartKitIOT/requestWindowStatus -m "window1"`, dan ESP32 akan mengirimkan status apakah jendela terbuka atau tertutup.
5. **Monitor Data Sensor**
   - Data suhu dan kelembaban dipublikasikan ke topik `MQTT@ESP32BasicStartKitIOT/suhu` dan `MQTT@ESP32BasicStartKitIOT/kelembapan`. Anda dapat memantau data ini dengan menggunakan perintah `mosquitto_sub`.

**Contoh Penggunaan:**

- **Mengontrol Lampu**:
  - Gunakan perintah untuk menyalakan atau mematikan lampu dengan mengirimkan perintah ke topik `lamp1` dan `lamp2`.
  - Contoh: `mosquitto_pub -h broker.mqtt-dashboard.com -t MQTT@ESP32BasicStartKitIOT/lamp1 -m "on"`
- **Mendapatkan Status Perangkat**:
  - Anda bisa meminta status perangkat seperti jendela atau pompa dengan mengirimkan permintaan ke topik yang sesuai, dan ESP32 akan memberikan feedback status perangkat tersebut.
  - Contoh: `mosquitto_pub -h broker.mqtt-dashboard.com -t MQTT@ESP32BasicStartKitIOT/requestWindowStatus -m "window1"`

**Keuntungan:**

- **Kontrol Jarak Jauh**: Menggunakan MQTT, Anda dapat mengontrol perangkat dari jarak jauh menggunakan aplikasi atau terminal MQTT.
- **Pemantauan Status**: Anda bisa mendapatkan feedback status perangkat secara real-time.
- **Data Sensor**: Anda dapat memonitor data suhu dan kelembaban di rumah atau ruangan.



Berikut adalah kode yang telah disesuaikan untuk sistem MQTT dengan feedback untuk kontrol perangkat seperti lampu, jendela, pintu, dan pompa, serta pengiriman status suhu dan kelembaban:

### Penjelasan Kode:

1. **WiFi dan MQTT Setup**:
   - Menghubungkan ESP32 ke WiFi dan broker MQTT menggunakan `WiFi` dan `MqttClient` libraries.
   - Menggunakan broker MQTT publik (`broker.mqtt-dashboard.com`).
2. **Kontrol Lampu**:
   - Menggunakan topik `lamp1Topic` dan `lamp2Topic` untuk mengontrol status lampu (ON/OFF).
   - Setiap pesan "on" atau "off" yang diterima akan mengubah status LED yang terhubung ke pin ESP32.
3. **Permintaan Status**:
   - ESP32 menerima permintaan status untuk perangkat lain seperti jendela, pintu, dan pompa melalui topik seperti `requestWindowStatusTopic`, `requestDoorStatusTopic`, dan `requestPumpStatusTopic`.
   - Sistem mengirimkan status acak "ON"/"OFF" atau status perangkat tertentu (misal jendela terbuka/tertutup) melalui topik feedback seperti `windowStatusTopic`, `doorStatusTopic`, dan `pumpStatusTopic`.
4. **Pengukuran Suhu dan Kelembaban**:
   - Mengirimkan data suhu dan kelembaban dummy setiap 5 detik ke topik `suhu` dan `kelembapan`.
5. **Feedback**:
   - Mengirimkan status perangkat melalui fungsi `sendStatusFeedback()` jika menerima permintaan status dari klien MQTT.

### Kode Lengkap:

```c++
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

```

### Penjelasan Fungsi-Fungsi:

1. **`connectToWiFi()`**: Menghubungkan ESP32 ke jaringan WiFi.
2. **`connectToMqttBroker()`**: Menghubungkan ESP32 ke broker MQTT.
3. **`publishTemperature()` dan `publishHumidity()`**: Mengirimkan data suhu dan kelembaban ke topik MQTT.
4. **`messageReceived()`**: Menangani pesan yang diterima, seperti mengubah status LED atau mengirimkan status perangkat (jendela, pintu, pompa).
5. **`sendStatusFeedback()`**: Mengirimkan status perangkat ke topik yang sesuai.
6. **`getRandomStatus()`**: Menghasilkan status acak (ON/OFF).

Anda dapat menggunakan `mosquitto_pub` dan `mosquitto_sub` untuk mengirim dan menerima pesan pada topik yang telah ditentukan.



**Kesimpulan:** Tutorial ini memberikan gambaran dasar tentang bagaimana menggunakan MQTT untuk mengontrol perangkat IoT dengan ESP32, serta mendapatkan dan memberikan feedback status perangkat. MQTT memungkinkan komunikasi yang efisien untuk proyek IoT Anda, terutama ketika perangkat Anda terhubung melalui jaringan WiFi.