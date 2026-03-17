#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

#include <WiFiNINA.h>

// Opretter forbindelse til WiFi
void setupWiFi();

// Returnerer WiFi status
bool isWiFiConnected();

#endif
