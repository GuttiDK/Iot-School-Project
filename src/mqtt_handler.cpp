#include "mqtt_handler.h"
#include "config.h"
#include "actuators.h"

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

  Serial.print("Subscribed to: ");
  Serial.println(TOPIC_CONTROL);
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
  String payload = mqttClient.readString();

  Serial.print("Message received: ");
  Serial.println(payload);

  // Servo kontrol
  if (payload == "180") {
    setServo(180);
  } else if (payload == "90") {
    setServo(90);
  } else if (payload == "0") {
    setServo(0);
  }
  
  // LED kontrol
  if (payload == "ON") {
    setLED(true);
  } else if (payload == "OFF") {
    setLED(false);
  }
}
