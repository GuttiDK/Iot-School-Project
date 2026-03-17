#include "dht_sensor.h"
#include "config.h"
#include "mqtt_handler.h"

DHT dht(DHT_PIN, DHT11);

float lastTemp = 0;
float lastHum = 0;

void setupDHT() {
  dht.begin();
  Serial.println("DHT11 initialized (3.3V!)");
}

bool readAndPublishDHT() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("DHT11 read error");
    return false;
  }

  lastTemp = temp;
  lastHum = hum;

  // Send til MQTT
  mqttPublish(TOPIC_TEMP, temp);
  mqttPublish(TOPIC_HUM, hum);

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print("°C, Humidity: ");
  Serial.print(hum);
  Serial.println("%");

  return true;
}

float getTemperature() {
  return lastTemp;
}

float getHumidity() {
  return lastHum;
}
