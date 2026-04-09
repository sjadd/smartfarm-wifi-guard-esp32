# SmartFarmWiFiGuard for ESP32

SmartFarmWiFiGuard is an Arduino ESP32 library designed to improve Wi-Fi reliability in smart farming and remote IoT deployments.

It provides a clean and lightweight interface for:
- automatic Wi-Fi reconnection
- signal strength monitoring
- signal quality classification
- reconnect event callbacks
- optional device restart after extended connectivity failure

This library was developed with smart agriculture scenarios in mind, where IoT devices may be deployed in greenhouses, open fields, or remote farm environments with unstable wireless conditions.

<img width="1376" height="768" alt="canvas-image-1-1775714467585" src="https://github.com/user-attachments/assets/e40a3b3c-4284-42eb-a7df-5b33e254ea23" />


## Why this project matters

In smart farming applications, stable communication is essential for sensor data transmission, remote monitoring, alerting systems, and cloud synchronization. Standard Wi-Fi examples often connect once and assume the network remains stable. In real agricultural deployments, that assumption is not always valid.

SmartFarmWiFiGuard addresses that gap with a practical connectivity layer for field-ready prototypes and production-oriented ESP32 systems.

## Features

- Reliable Wi-Fi reconnection logic
- RSSI monitoring
- Human-readable signal quality reporting
- Event callbacks for connection lifecycle
- Optional auto-restart after long outages
- ESP32 Arduino compatible

## Use cases

- Smart irrigation controllers
- Greenhouse environmental monitoring
- Soil and weather sensing nodes
- Solar-powered farm data loggers
- Remote agricultural telemetry systems

## Installation

1. Clone or download this repository.
2. Copy the project folder into your Arduino `libraries` directory.
3. Restart the Arduino IDE.
4. Open the example sketch:
   `examples/BasicReconnect/BasicReconnect.ino`

## Quick start

```cpp
#include <SmartFarmWiFiGuard.h>

const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

SmartFarmWiFiGuard wifiGuard(WIFI_SSID, WIFI_PASSWORD);

void setup() {
    Serial.begin(115200);
    wifiGuard.begin();
}

void loop() {
    wifiGuard.update();
}
```

## API overview

### Constructor

```cpp
SmartFarmWiFiGuard(const char* ssid, const char* password);
```

### Core methods

```cpp
void begin();
void update();
bool isConnected() const;
String getIPAddress() const;
int getRSSI() const;
String getSignalQuality() const;
```

### Configuration

```cpp
void setReconnectInterval(unsigned long intervalMs);
void setMaxReconnectAttempts(uint8_t maxAttempts);
void enableAutoRestartOnFailure(bool enable, unsigned long restartTimeoutMs = 300000);
```

### Event callbacks

```cpp
void onConnected(EventCallback callback);
void onDisconnected(EventCallback callback);
void onReconnectAttempt(EventCallback callback);
```

## Example output

```text
[WiFi] Connected successfully.
[WiFi] IP address: 192.168.1.20
[Status] Connected: Yes
[Status] RSSI: -57
[Status] Signal Quality: Excellent
```

## Professional positioning

This repository is suitable as a public portfolio project for embedded systems, IoT, and smart agriculture work. It demonstrates:

- practical C++ library design for Arduino/ESP32
- field-oriented engineering thinking
- clean documentation and reusable code structure
- direct relevance to agricultural IoT deployments

## Roadmap

- MQTT watchdog support
- Offline data buffering
- Multi-network failover support
- Captive portal onboarding
- Integration examples with soil moisture and environmental sensors

## Suggested GitHub topics

`arduino` `esp32` `wifi` `iot` `smart-farming` `agriculture` `embedded-systems` `precision-agriculture` `remote-monitoring`

## License

MIT License
