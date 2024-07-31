# Modul ESP32 doit esp32
![](https://github.com/hwthinker/ESP32BasicStartkitIOT/blob/main/picture/ESP32-DOIT-DEV-KIT-v1-pinout-mischianti.png)


# Note ESP32
- Pada ESP32, ADC2 digunakan oleh modul Wi-Fi untuk keperluan internal, yang dapat memengaruhi pembacaan dari beberapa channel ADC2. Secara khusus, channel ADC2 yang digunakan oleh Wi-Fi adalah:
   - ADC2_CHANNEL_0 (GPIO4)
   - ADC2_CHANNEL_2 (GPIO2)
   - ADC2_CHANNEL_4 (GPIO13)
   - ADC2_CHANNEL_5 (GPIO12)
   - ADC2_CHANNEL_6 (GPIO14)

- Pada ESP32 DOIT Devkit V1, beberapa pin tidak bisa digunakan sebagai GPIO output karena memiliki fungsi khusus atau dibatasi oleh desain perangkat keras. Selain VCC dan GND, pin-pinnya yang tidak dapat digunakan sebagai GPIO output meliputi:

  - GPIO1 (TX0) dan GPIO3 (RX0): Digunakan sebagai pin TX dan RX untuk komunikasi serial (UART0). Mengubah fungsi GPIO mereka dapat mengganggu komunikasi serial, terutama saat boot.
  - GPIO6 hingga GPIO11: Digunakan sebagai pin untuk jalur bus SPI flash. Mereka terhubung ke memori flash dan tidak dapat digunakan sebagai GPIO output.
  - GPIO16 dan GPIO17: Biasanya digunakan untuk fungsionalitas yang terkait dengan Wi-Fi dan Bluetooth serta digunakan untuk komunikasi internal dan pemrograman. Mereka juga tidak selalu dapat digunakan sebagai GPIO output.
  - GPIO34, GPIO35, GPIO36, dan GPIO39: Biasanya digunakan sebagai input ADC. Walaupun beberapa dari pin ini bisa diprogram sebagai GPIO input, mereka seringkali tidak dapat digunakan sebagai GPIO output atau memiliki batasan dalam penggunaannya.