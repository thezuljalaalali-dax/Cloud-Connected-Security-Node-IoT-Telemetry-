#include <WiFi.h>
#include <PubSubClient.h>

// --- 1. Wi-Fi Settings (Wokwi's Virtual Network) ---
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// --- 2. Adafruit IO Cloud Settings ---
const char* mqtt_server ="io.adafruit.com";
const char* mqtt_user ="WRITE USERNAME"; 
const char* mqtt_pass ="WRITE ACTIVE KEY";   

// The MQTT Topic format for Adafruit IO is: username/feeds/feedname
// Make sure your feed in Adafruit is named exactly "distance"
const char* mqtt_topic = "zuljalaal/feeds/distance"; 

// --- 3. Hardware Pins ---
#define TRIG_PIN 5
#define ECHO_PIN 18

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Connect to Virtual Wi-Fi
  Serial.print("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi Connected!");

  // Setup MQTT Broker connection
  client.setServer(mqtt_server, 1883);
}

void reconnect() {
  // Loop until we're connected to the Cloud
  while (!client.connected()) {
    Serial.print("Connecting to Adafruit IO...");
    
    // Attempt to connect using your specific credentials
    if (client.connect("ESP32SecurityNode", mqtt_user, mqtt_pass)) {
      Serial.println("Connected to Cloud Dashboard!");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); // Keep the MQTT connection alive

  // --- Read the Ultrasonic Sensor ---
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance_cm = duration * 0.034 / 2; // Calculate distance in cm

  Serial.print("Intruder Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  // --- Publish Telemetry to the Cloud ---
  // Convert the float to a string so MQTT can send it
  char dataString[8];
  dtostrf(distance_cm, 1, 2, dataString); 
  
  Serial.print("Publishing to Adafruit IO... ");
  if (client.publish(mqtt_topic, dataString)) {
    Serial.println("Success!");
  } else {
    Serial.println("Failed!");
  }

  // Wait 3 seconds before sending the next reading (Adafruit limits data speed on free accounts)
  delay(3000); 
}