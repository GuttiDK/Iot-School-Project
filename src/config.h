#ifndef CONFIG_H
#define CONFIG_H

// ===== WIFI KONFIGURATION =====
const char WIFI_SSID[] = "SibirienAP";
const char WIFI_PASS[] = "Siberia51244";

// ===== MQTT KONFIGURATION =====
//const char MQTT_BROKER[] = "10.131.15.72";
const char MQTT_BROKER[] = "10.112.148.146";
const int MQTT_PORT = 1883;

// MQTT Topics
const char TOPIC_CONTROL[] = "mkr1010/servoled";
const char TOPIC_TEMP[] = "mkr1010/temperature";
const char TOPIC_HUM[] = "mkr1010/humidity";

// ===== PIN KONFIGURATION =====
const int LED_PIN = 13;
const int SERVO_PIN = 9;
const int DHT_PIN = 2;

// ===== SENSOR INDSTILLINGER =====
const unsigned long SENSOR_INTERVAL = 2000; // ms mellem aflæsninger

#endif // CONFIG_H