#include "mqtt_handler.h"
#include "config.h"
#include "actuators.h"
#include "dht_sensor.h"

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

void setupMQTT() {
  if (!mqttClient.connect(MQTT_BROKER, MQTT_PORT)) {
    Serial.print("MQTT connection failed: ");
    Serial.println(mqttClient.connectError());
    while (1);
  }

  Serial.println("Connected to MQTT broker");

  mqttClient.onMessage(onMqttMessage);
  mqttClient.subscribe(TOPIC_CONTROL);
  mqttClient.subscribe(TOPIC_REQUEST);

  Serial.print("Subscribed to: ");
  Serial.print(TOPIC_CONTROL);
  Serial.print(" and ");
  Serial.println(TOPIC_REQUEST);
}

void mqttLoop() {
  mqttClient.poll();
}

void mqttPublish(const char* topic, float value) {
  mqttClient.beginMessage(topic);
  mqttClient.print(value);
  mqttClient.endMessage();
}

void mqttPublish(const char* topic, const char* message) {
  mqttClient.beginMessage(topic);
  mqttClient.print(message);
  mqttClient.endMessage();
}

void onMqttMessage(int messageSize) {
  // Hent topic navnet
  String topic = mqttClient.messageTopic();
  String payload = mqttClient.readString();

  Serial.print("Message on ");
  Serial.print(topic);
  Serial.print(": ");
  Serial.println(payload);

  // Request for sensordata
  if (topic == TOPIC_REQUEST) {
    // Læs frisk sensor data
    readAndPublishDHT();
    
    if (payload == "GET") {
      Serial.println("All sensor data requested");
      float temp = getTemperature();
      float hum = getHumidity();
      char response[100];
      sprintf(response, "temp:%.1f,hum:%.1f", temp, hum);
      mqttPublish(TOPIC_RESPONSE, response);
      return;
    }
    if (payload == "temp") {
      Serial.println("Temperature requested");
      float temp = getTemperature();
      char response[50];
      sprintf(response, "temp:%.1f", temp);
      mqttPublish(TOPIC_RESPONSE, response);
      return;
    }
    if (payload == "hum") {
      Serial.println("Humidity requested");
      float hum = getHumidity();
      char response[50];
      sprintf(response, "hum:%.1f", hum);
      mqttPublish(TOPIC_RESPONSE, response);
      return;
    }
  }

  // Servo kontrol - accepterer værdi 0-180 fra slider
  if (topic == TOPIC_CONTROL && payload.startsWith("servo:")) {
    int angle = payload.substring(6).toInt();
    if (angle >= 0 && angle <= 180) {
      setServo(angle);
      Serial.print("Servo set to: ");
      Serial.println(angle);
    }
  }
  
  // LED kontrol
  if (payload == "ON") {
    setLED(true);
  } else if (payload == "OFF") {
    setLED(false);
  }
}
