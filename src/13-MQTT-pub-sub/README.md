## 13: Menggunakan MQTT dengan ESP32 MQTT publisher dan subscriber dengan node-red

### MQTT Publisher (ESP32)

Publisher ini mengirimkan data suhu dan kelembapan secara periodik ke broker MQTT. Selain itu, publisher ini juga mendengarkan perintah untuk menghidupkan atau mematikan lampu dengan menggunakan tombol MQTT.

**Code untuk Publisher di ESP32 (Arduino):**

```c++
#include <WiFi.h>
#include <ArduinoMqttClient.h>

// WiFi settings
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// MQTT broker settings
const char* broker = "broker.mqtt-dashboard.com";
int port = 1883;
const char* temperatureTopic = "MQTT@ESP32BasicStartKitIOT/suhu";
const char* humidityTopic = "MQTT@ESP32BasicStartKitIOT/kelembapan";
const char* lamp1Topic = "MQTT@ESP32BasicStartKitIOT/lamp1";
const char* lamp2Topic = "MQTT@ESP32BasicStartKitIOT/lamp2";

// WiFi and MQTT clients
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

// LED pins
const int led1Pin = 23;
const int led2Pin = 5;

void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  Serial.println(" connected.");
}

void connectToMqttBroker() {
  Serial.print("Connecting to MQTT broker");
  while (!mqttClient.connect(broker, port)) {
    delay(1000);
  }
  Serial.println(" connected.");
}

void publishTemperature(float temperature) {
  mqttClient.beginMessage(temperatureTopic);
  mqttClient.print(temperature);
  mqttClient.endMessage();
  Serial.print("Published temperature: ");
  Serial.println(temperature);
}

void publishHumidity(float humidity) {
  mqttClient.beginMessage(humidityTopic);
  mqttClient.print(humidity);
  mqttClient.endMessage();
  Serial.print("Published humidity: ");
  Serial.println(humidity);
}

void messageReceived(int messageSize) {
  String topic = mqttClient.messageTopic();
  String message;
  while (mqttClient.available()) {
    message += (char)mqttClient.read();
  }

  // Control LED based on received message
  if (topic == lamp1Topic) {
    if (message == "on") {
      digitalWrite(led1Pin, HIGH);
    } else if (message == "off") {
      digitalWrite(led1Pin, LOW);
    }
  }
  if (topic == lamp2Topic) {
    if (message == "on") {
      digitalWrite(led2Pin, HIGH);
    } else if (message == "off") {
      digitalWrite(led2Pin, LOW);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);

  connectToWiFi();
  connectToMqttBroker();
  
  mqttClient.onMessage(messageReceived);
  mqttClient.subscribe(lamp1Topic);
  mqttClient.subscribe(lamp2Topic);
}

void loop() {
  if (!mqttClient.connected()) {
    connectToMqttBroker();
  }
  mqttClient.poll();

  // Publish dummy data for temperature and humidity
  float dummyTemperature = 25.0 + random(0, 100) / 10.0;
  float dummyHumidity = 50.0 + random(0, 100) / 10.0;
  
  publishTemperature(dummyTemperature);
  publishHumidity(dummyHumidity);

  delay(5000); // Delay for 5 seconds
}
```

### MQTT Subscriber (Node-RED)

Node-RED digunakan untuk menerima data dari broker MQTT dan menampilkannya di antarmuka pengguna menggunakan `ui_gauge`. Ini juga dapat mengontrol perangkat (seperti lampu) menggunakan tombol.

**Node-RED Flow:**

1. **MQTT In Nodes**: Berlangganan ke topik MQTT untuk suhu (`MQTT@ESP32BasicStartKitIOT/suhu`) dan kelembapan (`MQTT@ESP32BasicStartKitIOT/kelembapan`).
2. **Debug Nodes**: Menampilkan data suhu dan kelembapan yang diterima pada sidebar.
3. **UI Gauge Nodes**: Menampilkan data suhu dan kelembapan di antarmuka pengguna Node-RED.
4. **UI Button Nodes**: Mengirimkan perintah untuk menghidupkan/mematikan lampu.

**Berikut adalah Node-RED flow JSON:**

```json
[
    {
        "id": "ac7ae654d45e2bd8",
        "type": "debug",
        "z": "82edf446f47f8e8b",
        "name": "debug 1",
        "active": true,
        "tosidebar": true,
        "console": false,
        "tostatus": false,
        "complete": "false",
        "statusVal": "",
        "statusType": "auto",
        "x": 680,
        "y": 240,
        "wires": []
    },
    {
        "id": "165af8860686e330",
        "type": "mqtt in",
        "z": "82edf446f47f8e8b",
        "name": "",
        "topic": "MQTT@ESP32BasicStartKitIOT/suhu",
        "qos": "2",
        "datatype": "auto-detect",
        "broker": "8598583caf00dc7f",
        "nl": false,
        "rap": true,
        "rh": 0,
        "inputs": 0,
        "x": 310,
        "y": 260,
        "wires": [
            [
                "ac7ae654d45e2bd8",
                "fc1931b5ca5b8017"
            ]
        ]
    },
    {
        "id": "d84ebe97549f84d6",
        "type": "mqtt in",
        "z": "82edf446f47f8e8b",
        "name": "",
        "topic": "MQTT@ESP32BasicStartKitIOT/kelembapan",
        "qos": "2",
        "datatype": "auto-detect",
        "broker": "8598583caf00dc7f",
        "nl": false,
        "rap": true,
        "rh": 0,
        "inputs": 0,
        "x": 330,
        "y": 340,
        "wires": [
            [
                "fb9bf71b8e001a47",
                "917546a82f40de33"
            ]
        ]
    },
    {
        "id": "fb9bf71b8e001a47",
        "type": "debug",
        "z": "82edf446f47f8e8b",
        "name": "debug 2",
        "active": true,
        "tosidebar": true,
        "console": false,
        "tostatus": false,
        "complete": "false",
        "statusVal": "",
        "statusType": "auto",
        "x": 680,
        "y": 340,
        "wires": []
    },
    {
        "id": "fc1931b5ca5b8017",
        "type": "ui_gauge",
        "z": "82edf446f47f8e8b",
        "name": "Suhu",
        "group": "3f5edb2d212efb90",
        "order": 0,
        "width": 0,
        "height": 0,
        "gtype": "gage",
        "title": "Suhu",
        "label": "C",
        "format": "{{value}}",
        "min": "20",
        "max": "50",
        "colors": [
            "#00b500",
            "#e6e600",
            "#ca3838"
        ],
        "seg1": "",
        "seg2": "",
        "diff": false,
        "className": "",
        "x": 670,
        "y": 180,
        "wires": []
    },
    {
        "id": "917546a82f40de33",
        "type": "ui_gauge",
        "z": "82edf446f47f8e8b",
        "name": "Kelembapan",
        "group": "3f5edb2d212efb90",
        "order": 0,
        "width": 0,
        "height": 0,
        "gtype": "gage",
        "title": "Kelembapan",
        "label": "%",
        "format": "{{value}}",
        "min": "50",
        "max": "100",
        "colors": [
            "#00b500",
            "#e6e600",
            "#ca3838"
        ],
        "seg1": "",
        "seg2": "",
        "diff": false,
        "className": "",
        "x": 690,
        "y": 400,
        "wires": []
    }
]
```

**Penjelasan:**

- **MQTT In Nodes** digunakan untuk subscribe pada topik suhu dan kelembapan.
- **UI Gauge** menampilkan data suhu dan kelembapan secara visual pada dashboard.
- **Debug Nodes** digunakan untuk menampilkan data pada sidebar debug.

### **Kesimpulan**

Dengan menggunakan kombinasi publisher di ESP32 dan subscriber di Node-RED, Anda dapat membuat sistem monitoring suhu dan kelembapan yang dapat diakses melalui dashboard. Anda juga dapat mengontrol perangkat lain seperti lampu menggunakan MQTT commands