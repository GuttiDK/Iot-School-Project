# MKR1010 IoT Controller

Et Arduino MKR WiFi 1010 projekt der forbinder til en MQTT broker og styrer aktuatorer samt sender sensordata.

## Funktioner

- **WiFi forbindelse** til lokalt netværk
- **MQTT kommunikation** til IoT broker
- **DHT11 sensor** - temperatur og luftfugtighed
- **Servo motor** - styres via MQTT (0°, 90°, 180°)
- **LED kontrol** - tænd/sluk via MQTT

## Hardware

| Komponent | Pin | Bemærkning |
|-----------|-----|------------|
| DHT11 | 2 | **Forsynes med 3,3V!** |
| Servo | 9 | |
| LED | 13 | Onboard LED |

### Tilslutning DHT11
```
DHT11       MKR1010
-----       -------
VCC    -->  3.3V
GND    -->  GND
DATA   -->  Pin 2
```

## Filstruktur

```
src/
├── main.cpp          # Hovedprogram - samler alle moduler
├── config.h          # Alle indstillinger (WiFi, MQTT, pins)
├── wifi_handler.h    # WiFi header
├── wifi_handler.cpp  # WiFi forbindelse
├── mqtt_handler.h    # MQTT header
├── mqtt_handler.cpp  # MQTT kommunikation og callbacks
├── dht_sensor.h      # DHT sensor header
├── dht_sensor.cpp    # Temperatur og humidity læsning
├── actuators.h       # Aktuator header
└── actuators.cpp     # Servo og LED kontrol
```

## Konfiguration

Rediger `config.h` for at ændre indstillinger:

```cpp
// WiFi
const char WIFI_SSID[] = "DitNetværk";
const char WIFI_PASS[] = "DinKode";

// MQTT Broker
const char MQTT_BROKER[] = "10.131.15.72";
const int MQTT_PORT = 1883;
```

## MQTT Topics

| Topic | Retning | Beskrivelse |
|-------|---------|-------------|
| `mkr1010/servoled` | Subscribe | Modtag kommandoer |
| `mkr1010/temperature` | Publish | Sender temperatur (°C) |
| `mkr1010/humidity` | Publish | Sender luftfugtighed (%) |

### Kommandoer (send til `mkr1010/servoled`)

| Kommando | Handling |
|----------|----------|
| `0` | Servo til 0° |
| `90` | Servo til 90° |
| `180` | Servo til 180° |
| `ON` | Tænd LED |
| `OFF` | Sluk LED |

## Dependencies

Tilføj til `platformio.ini`:

```ini
[env:mkrwifi1010]
platform = atmelsam
board = mkrwifi1010
framework = arduino
lib_deps = 
    arduino-libraries/WiFiNINA
    arduino-libraries/ArduinoMqttClient
    adafruit/DHT sensor library
    adafruit/Adafruit Unified Sensor
```

## Upload

```bash
# Via PlatformIO
pio run --target upload

# Åbn Serial Monitor
pio device monitor --baud 9600
```

## Test med MQTT

```bash
# Abonner på sensor data
mosquitto_sub -h 10.131.15.72 -t "mkr1010/#"

# Send kommando
mosquitto_pub -h 10.131.15.72 -t "mkr1010/servoled" -m "ON"
mosquitto_pub -h 10.131.15.72 -t "mkr1010/servoled" -m "180"
```

## Fejlfinding

| Problem | Løsning |
|---------|---------|
| WiFi forbinder ikke | Tjek SSID og password i `config.h` |
| MQTT fejler | Tjek broker IP og at den kører |
| DHT11 read error | Tjek tilslutning og 3,3V forsyning |
| Servo ryster | Tjek strømforsyning |

## Licens

MIT
