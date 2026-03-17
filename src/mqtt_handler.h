#ifndef MQTT_HANDLER_H
#define MQTT_HANDLER_H

#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>

// Initialiserer MQTT forbindelse
void setupMQTT();

// Skal kaldes i loop() for at holde forbindelsen
void mqttLoop();

// Publicer en besked til et topic
void mqttPublish(const char* topic, float value);
void mqttPublish(const char* topic, const char* message);

// Callback funktion til indkommende beskeder
void onMqttMessage(int messageSize);

// Giver adgang til MQTT client
extern MqttClient mqttClient;

#endif
