# MKR1010 IoT Controller

Et Arduino MKR WiFi 1010 projekt der forbinder til en MQTT broker og styrer aktuatorer samt sender sensordata.

## Funktioner

- **WiFi forbindelse** til lokalt netværk (kun 2.4GHz)
- **MQTT kommunikation** til IoT broker
- **DHT11 sensor** - temperatur og luftfugtighed
- **Servo motor** - styres via MQTT slider (0°-180°)
- **LED kontrol** - tænd/sluk via MQTT
- **Request/Response** - anmod om sensordata on-demand

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
├── wifi_handler.cpp  # WiFi forbindelse med debugging
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

// MQTT Broker (shiftr.io)
const char MQTT_BROKER[] = "broker.shiftr.io";
const int MQTT_PORT = 1883;
```

## MQTT Topics

| Topic | Retning | Beskrivelse |
|-------|---------|-------------|
| `mkr1010/servoled` | Subscribe | Modtag kommandoer (servo/LED) |
| `mkr1010/request` | Subscribe | Modtag data requests |
| `mkr1010/response` | Publish | Svar på requests |

### Servo/LED Kommandoer (send til `mkr1010/servoled`)

| Kommando | Handling |
|----------|----------|
| `servo:X` | Servo til X° (0-180, til slider) |
| `ON` | Tænd LED |
| `OFF` | Sluk LED |

### Data Requests (send til `mkr1010/request`)

| Kommando | Svar på `mkr1010/response` |
|----------|----------------------------|
| `GET` | `temp:22.5,hum:45.0` |
| `temp` | `temp:22.5` |
| `hum` | `hum:45.0` |

## Test med shiftr.io

Brug shiftr.io's web interface til at:
- Subscribe på `mkr1010/response` for at se svar
- Publish til `mkr1010/request` med `GET`, `temp` eller `hum`
- Publish til `mkr1010/servoled` med `servo:90` eller `ON`/`OFF`

## WiFi Fejlfinding

Serial Monitor viser WiFi status koder:
- `0` = Idle
- `1` = SSID ikke fundet (2.4GHz netværk?)
- `3` = Forbundet
- `4` = Forbindelse fejlede (forkert password eller WPA3)
- `6` = Afbrudt

**Bemærk:** MKR1010 understøtter **kun 2.4GHz WiFi** og WPA2.

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

## Fejlfinding

| Problem | Løsning |
|---------|---------|
| WiFi forbinder ikke | Tjek SSID og password i `config.h` |
| MQTT fejler | Tjek broker IP og at den kører |
| DHT11 read error | Tjek tilslutning og 3,3V forsyning |
| Servo ryster | Tjek strømforsyning |

## Licens

MIT
