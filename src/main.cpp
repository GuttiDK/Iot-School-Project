// ===== MAIN.CPP =====
// Samler alle moduler

#include <Arduino.h>
#include "config.h"
#include "wifi_handler.h"
#include "mqtt_handler.h"
#include "dht_sensor.h"
#include "actuators.h"

unsigned long lastSensorRead = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Opgave 1: Aktuatorer (LED + Servo)
  setupActuators();

  // Opgave 2: WiFi forbindelse
  setupWiFi();

  // Opgave 3: MQTT forbindelse
  setupMQTT();

  // Opgave 4: DHT11 sensor (3.3V!)
  setupDHT();

  Serial.println("\n=== System Ready ===");
}

void loop() {
  // MQTT kommunikation
  mqttLoop();

  // Læs sensor hver 2. sekund
  if (millis() - lastSensorRead >= SENSOR_INTERVAL) {
    lastSensorRead = millis();
    readAndPublishDHT();
  }
}