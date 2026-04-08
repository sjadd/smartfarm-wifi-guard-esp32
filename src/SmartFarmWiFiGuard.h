#ifndef SMART_FARM_WIFI_GUARD_H
#define SMART_FARM_WIFI_GUARD_H

#include <Arduino.h>
#include <WiFi.h>

class SmartFarmWiFiGuard {
public:
    using EventCallback = void (*)();

    SmartFarmWiFiGuard(const char* ssid, const char* password);

    void begin();
    void update();

    bool isConnected() const;
    String getIPAddress() const;
    int getRSSI() const;
    String getSignalQuality() const;

    void setReconnectInterval(unsigned long intervalMs);
    void setMaxReconnectAttempts(uint8_t maxAttempts);
    void enableAutoRestartOnFailure(bool enable, unsigned long restartTimeoutMs = 300000UL);

    void onConnected(EventCallback callback);
    void onDisconnected(EventCallback callback);
    void onReconnectAttempt(EventCallback callback);

private:
    const char* _ssid;
    const char* _password;

    unsigned long _lastReconnectAttempt;
    unsigned long _reconnectIntervalMs;
    unsigned long _disconnectStartTime;
    unsigned long _restartTimeoutMs;

    uint8_t _reconnectAttempts;
    uint8_t _maxReconnectAttempts;

    bool _autoRestartEnabled;
    bool _wasConnected;

    EventCallback _connectedCallback;
    EventCallback _disconnectedCallback;
    EventCallback _reconnectAttemptCallback;

    void connectWiFi();
    void handleReconnect();
};

#endif  // SMART_FARM_WIFI_GUARD_H
