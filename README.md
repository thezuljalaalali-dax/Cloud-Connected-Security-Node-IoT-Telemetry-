

https://github.com/user-attachments/assets/204f745e-2063-4353-9ea1-2abfe34c6e6b

# Cloud Connected Security Node IoT Telemetry
A real-time IoT security system built with an ESP32. It uses an ultrasonic sensor to act like a radar, measuring the distance of nearby objects, and streams that data live to an Adafruit IO cloud dashboard using Wi-Fi and MQTT.

Description
This project demonstrates how to build a true Internet of Things (IoT) device. Instead of just printing sensor data to a local computer screen, this ESP32 microcontroller connects directly to the internet. 

It constantly pings an HC-SR04 ultrasonic sensor to measure how far away an object (like an intruder) is. Using the **MQTT protocol** (a lightweight messaging system perfect for smart devices), it publishes this distance data to a centralized cloud server. The data is then visualized on a live web dashboard, allowing you to monitor the security node from anywhere in the world.

This project was built and tested using the Wokwi IoT simulator.

---

### 🛠️ Hardware & Components
* **Microcontroller:** ESP32 Development Board
* **Sensor:** HC-SR04 Ultrasonic Distance Sensor
* **Network:** Local Wi-Fi (Simulated via `Wokwi-GUEST`)

### 💻 Software & Libraries
* **Language:** C++ (Arduino Framework)
* **Cloud Platform:** Adafruit IO
* **Libraries Used:** * `WiFi.h` (For internet connection)
* `PubSubClient` (For MQTT telemetry)

---

### 🚀 How It Works
1. **Network Boot:** The ESP32 boots up and connects to the local Wi-Fi network.
2. **Cloud Authentication:** It logs into the Adafruit IO MQTT broker using a secure IO Key.
3. **Data Collection:** The ultrasonic sensor sends out sound waves to calculate the distance of objects in front of it in centimeters.
4. **Telemetry Stream:** Every 3 seconds, the ESP32 packages the distance number into a string and publishes it to the Adafruit cloud feed.
5. **Dashboard Visualization:** The web dashboard catches the data and instantly updates a line graph to show movement.

---

### ⚙️ Setup Instructions
If you want to run this code yourself:
1. Create a free account on [Adafruit IO](https://io.adafruit.com/) and create a new feed named `distance`.
2. Get your Adafruit Username and Active IO Key.
3. Wire the HC-SR04 sensor to the ESP32 (TRIG to `D5`, ECHO to `D18`).
4. Paste the code into your Arduino IDE or Wokwi simulator.
5. **Crucial:** Update the `mqtt_user` and `mqtt_pass` variables in the code with your own Adafruit credentials before running!

DOWNLOAD ZIP
[Cloud-Connected Security Node (IoT  Telemetry).zip](https://github.com/user-attachments/files/29550878/Cloud-Connected.Security.Node.IoT.Telemetry.zip)
