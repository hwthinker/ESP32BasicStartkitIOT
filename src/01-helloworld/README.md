### Tutorial: Menampilkan "Hello, World!" pada Serial Monitor dengan Arduino

Pada tutorial ini, kita akan membuat program sederhana di Arduino yang menampilkan pesan **"Hello, World!"** di **Serial Monitor**. Ini adalah langkah pertama yang umum dilakukan saat belajar pemrograman mikrokontroler menggunakan Arduino.

**Prasyarat:**

1. **Arduino Board**: Anda bisa menggunakan board seperti Arduino Uno atau board berbasis ATmega328P lainnya.
2. **Arduino IDE**: Anda perlu menginstal **Arduino IDE** untuk menulis dan mengunggah kode ke board Arduino.
3. **Serial Monitor**: Digunakan untuk memantau output dari board Arduino melalui koneksi USB.

**Langkah-langkah:**

1. **Setup Serial Communication**
   - Program dimulai dengan `Serial.begin(115200);` untuk memulai komunikasi serial dengan kecepatan 115200 baud. Angka 115200 adalah kecepatan baud standar yang digunakan di banyak board Arduino.
2. **Menunggu Koneksi Serial (Opsional untuk Debugging)**
   - `while (!Serial) {;}` adalah bagian opsional yang berguna untuk memastikan bahwa komunikasi serial telah terhubung sepenuhnya sebelum melanjutkan eksekusi program. Ini digunakan terutama pada board seperti **Arduino Leonardo** dan **Arduino Micro**, yang memerlukan waktu untuk menyambung ke komputer.
3. **Menampilkan Pesan "Hello, World!"**
   - `Serial.println("Hello, World!");` digunakan untuk menampilkan pesan **"Hello, World!"** pada **Serial Monitor**. Fungsi `println` digunakan agar teks yang dicetak diikuti dengan baris baru (enter).
4. **Looping Tanpa Aksi**
   - Fungsi `loop()` dibiarkan kosong karena program hanya mencetak pesan sekali pada saat **setup()**. Jika Anda ingin menambahkan lebih banyak perintah yang dijalankan berulang kali, Anda bisa menambahkannya ke dalam fungsi **loop()**.

**Kode Program:**

```c++
#include <Arduino.h>

void setup() {
    // Memulai komunikasi serial dengan kecepatan 115200 baud
    Serial.begin(115200);
    
    // Menunggu koneksi serial (untuk keperluan debugging)
    while (!Serial) {
        ;
    }
    
    // Mencetak pesan "Hello, World!" ke Serial Monitor
    Serial.println("Hello, World!");
}

void loop() {
    // Tidak ada aksi yang dilakukan di sini
}
```

**Langkah-langkah Penggunaan:**

1. **Unggah Program ke Arduino:**
   - Pilih board Arduino yang sesuai di Arduino IDE dan pastikan port serial yang benar telah dipilih.
   - Klik tombol **Upload** untuk mengunggah program ke board Arduino.
2. **Lihat Output di Serial Monitor:**
   - Buka **Serial Monitor** di Arduino IDE (klik ikon kaca pembesar di pojok kanan atas).
   - Anda akan melihat pesan **"Hello, World!"** ditampilkan pada Serial Monitor.

**Kesimpulan:** Tutorial ini memberikan gambaran tentang bagaimana menampilkan output sederhana ke Serial Monitor dengan menggunakan board Arduino. Program ini dapat dikembangkan lebih lanjut untuk membaca input dari pengguna atau sensor, serta memberikan umpan balik dalam bentuk teks melalui serial.