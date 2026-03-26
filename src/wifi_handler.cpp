#include "wifi_handler.h"
#include "config.h"

void setupWiFi() {
  // Tjek WiFi modul
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("WiFi module not found!");
    while (1);
  }

  // Vis firmware version
  String fv = WiFi.firmwareVersion();
  Serial.print("WiFi firmware: ");
  Serial.println(fv);

  Serial.print("Connecting to: ");
  Serial.println(WIFI_SSID);
  
  int attempts = 0;
  int status = WL_IDLE_STATUS;
  
  while (status != WL_CONNECTED && attempts < 10) {
    Serial.print("Attempt ");
    Serial.print(attempts + 1);
    Serial.print("...");
    
    status = WiFi.begin(WIFI_SSID, WIFI_PASS);
    
    Serial.print(" Status: ");
    Serial.println(status);
    // 0=IDLE, 1=NO_SSID_AVAIL, 3=CONNECTED, 4=CONNECT_FAILED, 6=DISCONNECTED
    
    if (status != WL_CONNECTED) {
      delay(3000);
      attempts++;
    }
  }
  
  if (status != WL_CONNECTED) {
    Serial.println("WiFi connection FAILED!");
    while (1);
  }
  
  Serial.println("Connected to WiFi!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

bool isWiFiConnected() {
  return WiFi.status() == WL_CONNECTED;
}
