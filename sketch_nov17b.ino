void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

// 1. Replace these three lines with your Blynk Device Info
#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// 2. Replace with your Wi-Fi credentials
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";

// 3. DHT22 Configuration
#define DHTPIN 4          // GPIO 4 connected to DHT22 Data pin
#define DHTTYPE DHT22     // Specify DHT22 (AM2302)

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// Function to read sensor data and send to Blynk
void sendSensorData() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Use dht.readTemperature(true) for Fahrenheit

  // Check if any reads failed and exit early to try again
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT22 sensor!");
    return;
  }

  // Print values to Serial Monitor for debugging
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C | Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Send values to Blynk Virtual Pins
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
}

void setup() {
  Serial.begin(115200);
  
  dht.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Read and send data every 2 seconds (2000 ms)
  // Note: DHT22 has a slow sampling rate; do not poll faster than once every 2 seconds
  timer.setInterval(2000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}
