### 12: Menggunakan MQTT dengan ESP32 untuk Mengirim Data Suhu dan Kelembaban (simulasi)

Pada tutorial ini, kita akan menggunakan **ESP32** untuk mengirim data suhu dan kelembaban ke **MQTT Broker** menggunakan protokol MQTT. Kami akan menghubungkan ESP32 ke WiFi dan MQTT broker dan mempublikasikan data suhu dan kelembaban dummy.

#### **Alat dan Bahan yang Dibutuhkan:**

- **ESP32** (misalnya ESP32 DevKit V1)
- Koneksi internet (untuk WiFi dan MQTT broker)
- **MQTT Broker** seperti `broker.mqtt-dashboard.com` (untuk testing)
- **Mosquitto Client** (untuk subscribe data di broker MQTT, optional)

#### **Langkah-langkah:**

1. **Persiapan dan Koneksi:**

   - Sambungkan **ESP32** ke komputer menggunakan kabel USB.
   - Pastikan **WiFi** diaktifkan dan terhubung dengan jaringan WiFi yang sesuai.

2. **Kode Program:** Berikut adalah kode untuk menghubungkan ESP32 ke WiFi dan MQTT Broker, serta mengirimkan data suhu dan kelembaban secara berkala.

   ```c++
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
   
   // Inisialisasi WiFi dan MQTT Client
   WiFiClient wifiClient;
   MqttClient mqttClient(wifiClient);
   
   // Deklarasi fungsi
   void connectToWiFi();
   void connectToMqttBroker();
   void publishTemperature(float temperature);
   void publishHumidity(float humidity);
   
   void setup() {
     Serial.begin(115200);
   
     // Koneksi ke WiFi
     connectToWiFi();
   
     // Koneksi ke MQTT Broker
     connectToMqttBroker();
   }
   
   void loop() {
     if (!mqttClient.connected()) {
       connectToMqttBroker();
     }
   
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
   ```

3. **Penjelasan Kode:**

   - WiFi dan MQTT Setup:
     - `ssid` dan `password` digunakan untuk menghubungkan ESP32 ke jaringan WiFi.
     - `broker` berisi alamat MQTT broker yang digunakan untuk mengirim dan menerima pesan.
     - `MqttClient` digunakan untuk berkomunikasi dengan broker MQTT.
   - Fungsi `connectToWiFi`:
     - Fungsi ini menghubungkan ESP32 ke jaringan WiFi yang ditentukan dalam variabel `ssid` dan `password`.
   - Fungsi `connectToMqttBroker`:
     - Fungsi ini menghubungkan ESP32 ke broker MQTT menggunakan alamat broker dan port yang sudah ditentukan.
   - Fungsi `publishTemperature` dan `publishHumidity`:
     - Fungsi ini mengirimkan data suhu dan kelembaban secara berkala ke topik MQTT yang sudah ditentukan (`suhu` dan `kelembapan`).
     - Data suhu dan kelembaban dibuat secara acak menggunakan fungsi `random` untuk simulasi.

4. **Testing dengan Mosquitto Client:** Anda dapat menggunakan **mosquitto-client** untuk **subscribe** ke topik MQTT dan memonitor data yang dipublikasikan oleh ESP32. Jalankan perintah berikut pada terminal:

   - Untuk suhu:

     ```bash
     mosquitto_sub -h broker.mqtt-dashboard.com -t MQTT@ESP32BasicStartKitIOT/suhu
     ```

   - Untuk kelembaban:

     ```bash
     mosquitto_sub -h broker.mqtt-dashboard.com -t MQTT@ESP32BasicStartKitIOT/kelembapan
     ```

5. **Upload dan Monitor Hasil:**

   - Setelah meng-upload kode ke ESP32, buka **Serial Monitor** (dengan baud rate 115200).
   - Anda akan melihat data suhu dan kelembaban yang dipublikasikan secara berkala ke broker MQTT.

#### **Pemecahan Masalah:**

- Jika ESP32 tidak dapat terhubung ke WiFi atau MQTT Broker, periksa kembali konfigurasi jaringan dan pastikan ESP32 terhubung dengan benar.
- Jika tidak ada data yang muncul di **Serial Monitor** atau **mosquitto-client**, periksa apakah topik dan alamat broker sudah benar.

Dengan tutorial ini, Anda dapat menghubungkan ESP32 dengan broker MQTT dan mengirimkan data suhu dan kelembaban secara real-time.