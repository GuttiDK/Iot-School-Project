#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include <DHT.h>

// Initialiserer DHT11 sensor - forsynes med 3,3V!
void setupDHT();

// Læser og sender sensor data via MQTT
// Returnerer true hvis læsning lykkedes
bool readAndPublishDHT();

// Henter sidste temperatur værdi
float getTemperature();

// Henter sidste humidity værdi
float getHumidity();

#endif
