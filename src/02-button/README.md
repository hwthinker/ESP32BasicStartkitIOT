## 02: Interface button dengan ESP32

Pada tutorial ini, kita akan menghubungkan **push butoong** (Passive Infrared Sensor) ke **ESP32**. push button dikonfigurasi  pada gambar. 

### Alat dan Bahan yang Dibutuhkan:

- **ESP32** (misalnya ESP32 DevKit V1)
- Push Button 
- Kabel jumper
- Breadboard (opsional)

### Langkah-langkah:

1. **Persiapan dan Koneksi:**

   - Push button  ke 1 ke GPIO 17  dan Push botton ke 2 ke GPIO16 dari ESP32  dengan konfigurasi sesuai gambar berikut
   
   ![Premium ESP32 Basic STARTER KIT -premium (2)](./assets/Premium%20ESP32%20Basic%20STARTER%20KIT%20-premium%20(2).png)

2. **Kode Program:**

   ```c++
   #include <Arduino.h>
   
   const int btn1Pin = 16; // 
   const int btn2Pin = 17; // 
   
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
   ```

3. **Penjelasan Kode**

   Mari kita bahas baris per baris:

   1. Pertama-tama kita lihat bagian atas kode:

   ```c++
   #include <Arduino.h>
   ```
   
   Ini seperti memberitahu Arduino bahwa kita akan menggunakan perintah-perintah dasar Arduino. Bayangkan seperti membuka kotak peralatan sebelum mulai bekerja!
   
   2. Kemudian kita tentukan pin untuk tombol:

   ```c++
const int btn1Pin = 16;    // Pin untuk tombol 1
   const int btn2Pin = 17;    // Pin untuk tombol 2
```
   
   Di sini kita memberitahu Arduino bahwa tombol 1 terhubung ke GPIO16 dan tombol 2 ke GPIO17.  
   
   ```c++
void setup() {
       Serial.begin(115200);        // Mulai komunikasi dengan komputer
    pinMode(btn1Pin, INPUT);     // Atur pin tombol 1 sebagai INPUT
       pinMode(btn2Pin, INPUT);     // Atur pin tombol 2 sebagai INPUT
}
   ```
   
   Ini adalah bagian persiapan, seperti menyiapkan alat sebelum memulai. Kita:
   
   - Memulai komunikasi dengan komputer (seperti membuka saluran bicara)
   - Memberitahu Arduino bahwa kedua pin akan digunakan untuk menerima sinyal (INPUT)
   
4. Bagian loop (program utama):
   
```c++
   void loop() {
       int btn1State = digitalRead(btn1Pin);  // Baca status tombol 1
    int btn2State = digitalRead(btn2Pin);  // Baca status tombol 2
       
    if (btn1State == LOW) {               // Jika tombol 1 ditekan
           Serial.println("button1 pressed");
       }
       if (btn2State == LOW) {               // Jika tombol 2 ditekan
           Serial.println("button2 pressed");
       }
       
       delay(20);    // Tunggu sebentar (20 milidetik)
   }
   ```
   
   Ini adalah bagian utama program yang akan terus berulang:
   
   - Arduino akan terus mengecek apakah tombol ditekan
   - Jika tombol 1 ditekan, Arduino akan mengirim pesan "button1 pressed"
   - Jika tombol 2 ditekan, Arduino akan mengirim pesan "button2 pressed"
- Tunggu sebentar sebelum mengecek lagi
   
Cara kerjanya seperti ini:
   
   1. Bayangkan kamu punya dua tombol di depanmu
   2. Setiap kali kamu menekan tombol 1, Arduino akan menulis "button1 pressed" di komputer
   3. Setiap kali kamu menekan tombol 2, Arduino akan menulis "button2 pressed" di komputer
4. Arduino akan terus-menerus mengecek tombol-tombol ini
   
Tips untuk mencoba:
   
   - Pastikan tombol terhubung dengan benar ke pin 16 dan 17
   - Buka Serial Monitor di Arduino IDE untuk melihat pesannya
   - Coba tekan tombol dan lihat apakah pesannya muncul di Serial Monitor


### Pemecahan Masalah:

Jika ada masalah pastikan:

- Apakah kabel tombol terpasang dengan benar?
- Apakah nomor pin sudah sesuai dengan koneksi fisik
- Apakah Serial Monitor sudah dibuka?
- Apakah kecepatan Serial Monitor sudah diatur ke 115200?
