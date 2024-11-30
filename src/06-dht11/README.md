### 06: Tutorial Membaca Suhu dan Kelembapan dengan DHT11 menggunakan ESP32**

Pada tutorial kali ini, kita akan menggunakan **sensor DHT11** untuk membaca data suhu dan kelembapan. Data tersebut akan dibaca oleh ESP32 dan ditampilkan melalui **Serial Monitor**.

#### **Alat dan Bahan yang Dibutuhkan:**

- **ESP32** (misalnya ESP32 DevKit V1)
- **Sensor DHT11**
- Kabel jumper
- Breadboard

#### **Langkah-langkah:**

1. **Persiapan dan Koneksi:**

   - Sambungkan pin **VCC** pada sensor DHT11 ke pin **3.3V** pada ESP32.
   - Sambungkan pin **GND** pada sensor DHT11 ke **GND** pada ESP32.
   - Sambungkan pin **DATA** pada sensor DHT11 ke **GPIO4** pada ESP32 (pin ini akan kita gunakan untuk membaca data dari sensor).

   **Catatan:** Pastikan sambungan sudah benar, dan periksa kembali apakah sensor DHT11 yang Anda gunakan memiliki pinout yang sesuai dengan yang dijelaskan.

   ![DHT11](./assets/DHT11.png)

2. **Kode Program:**

   ```c++
   #include <Arduino.h>
   #include <DHT.h>
   
   #define DHTPIN 4     // Pin tempat DHT11 terhubung
   #define DHTTYPE DHT11   // Jenis sensor DHT (DHT11)
   
   DHT dht(DHTPIN, DHTTYPE);
   
   void setup() {
     Serial.begin(115200);  // Inisialisasi komunikasi serial
     dht.begin();           // Inisialisasi sensor DHT11
   }
   
   void loop() {
     delay(2000);  // Tunggu beberapa detik antar pengukuran
   
     float humidity = dht.readHumidity();  // Membaca kelembapan
     float temperature = dht.readTemperature();  // Membaca suhu dalam celcius
   
     // Cek jika pembacaan gagal
     if (isnan(humidity) || isnan(temperature)) {
       Serial.println("Gagal membaca dari sensor DHT!");
       return;
     }
   
     // Menampilkan hasil pembacaan suhu dan kelembapan
     Serial.print("Kelembapan: ");
     Serial.print(humidity);
     Serial.print(" %\t");
     Serial.print("Suhu: ");
     Serial.print(temperature);
     Serial.println(" *C");
   }
   ```

3. **Penjelasan Kode:**

   - **`#define DHTPIN 4`**: Menetapkan pin GPIO4 pada ESP32 sebagai tempat sensor DHT11 terhubung.
   - **`#define DHTTYPE DHT11`**: Menentukan jenis sensor yang digunakan adalah **DHT11**.
   - **`DHT dht(DHTPIN, DHTTYPE)`**: Membuat objek **dht** untuk berkomunikasi dengan sensor DHT11.
   - **`dht.begin()`**: Inisialisasi sensor DHT11 pada pin yang sudah ditentukan.
   - **`dht.readHumidity()`**: Membaca nilai kelembapan dari sensor DHT11.
   - **`dht.readTemperature()`**: Membaca nilai suhu dalam derajat Celcius.
   - **`isnan(humidity) || isnan(temperature)`**: Memeriksa apakah pembacaan sensor gagal. Jika gagal, akan mencetak pesan kesalahan.
   - **`Serial.print()` dan `Serial.println()`**: Digunakan untuk menampilkan nilai kelembapan dan suhu ke **Serial Monitor**.

4. **Upload dan Monitor Hasil:** Setelah Anda meng-upload kode ke ESP32, buka **Serial Monitor** di Arduino IDE. Anda akan melihat nilai kelembapan dan suhu yang terbaca dari sensor DHT11 muncul setiap 2 detik (interval `delay(2000)`), yang menampilkan data dalam format berikut:

   ```yaml
   Kelembapan: 60.00 %    Suhu: 25.00 *C
   ```

#### **Pemecahan Masalah:**

- Jika tidak ada data yang muncul atau nilai yang terbaca salah (misalnya NaN), pastikan kabel sudah terhubung dengan benar, terutama kabel **DATA** pada pin yang tepat.
- Jika pesan "Gagal membaca dari sensor DHT!" muncul, pastikan sensor dalam kondisi baik dan terhubung dengan benar.

Dengan tutorial ini, Anda dapat mulai menggunakan sensor DHT11 untuk mengukur suhu dan kelembapan dengan ESP32, yang bisa diaplikasikan pada berbagai proyek IoT seperti monitoring cuaca, rumah pintar, atau aplikasi otomatisasi.