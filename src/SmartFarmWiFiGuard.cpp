#include "SmartFarmWiFiGuard.h"

SmartFarmWiFiGuard::SmartFarmWiFiGuard(const char* ssid, const char* password)
    : _ssid(ssid),
      _password(password),
      _lastReconnectAttempt(0),
      _reconnectIntervalMs(10000UL),
      _disconnectStartTime(0),
      _restartTimeoutMs(300000UL),
      _reconnectAttempts(0),
      _maxReconnectAttempts(10),
      _autoRestartEnabled(false),
      _wasConnected(false),
      _connectedCallback(nullptr),
      _disconnectedCallback(nullptr),
      _reconnectAttemptCallback(nullptr) {}

void SmartFarmWiFiGuard::begin() {
    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false);
    WiFi.setAutoReconnect(false);
    WiFi.persistent(false);

    connectWiFi();
}

void SmartFarmWiFiGuard::update() {
    const bool currentlyConnected = (WiFi.status() == WL_CONNECTED);

    if (currentlyConnected) {
        if (!_wasConnected) {
            _wasConnected = true;
            _reconnectAttempts = 0;
            _disconnectStartTime = 0;

            if (_connectedCallback != nullptr) {
                _connectedCallback();
            }
        }
        return;
    }

    if (_wasConnected) {
        _wasConnected = false;
        _disconnectStartTime = millis();

        if (_disconnectedCallback != nullptr) {
            _disconnectedCallback();
        }
    }

    handleReconnect();

    if (_autoRestartEnabled && _disconnectStartTime > 0) {
        const unsigned long outageDuration = millis() - _disconnectStartTime;
        if (outageDuration >= _restartTimeoutMs) {
            ESP.restart();
        }
    }
}

bool SmartFarmWiFiGuard::isConnected() const {
    return WiFi.status() == WL_CONNECTED;
}

String SmartFarmWiFiGuard::getIPAddress() const {
    if (WiFi.status() == WL_CONNECTED) {
        return WiFi.localIP().toString();
    }
    return "0.0.0.0";
}

int SmartFarmWiFiGuard::getRSSI() const {
    if (WiFi.status() == WL_CONNECTED) {
        return WiFi.RSSI();
    }
    return -999;
}

String SmartFarmWiFiGuard::getSignalQuality() const {
    const int rssi = getRSSI();

    if (rssi >= -60) return "Excellent";
    if (rssi >= -70) return "Good";
    if (rssi >= -80) return "Fair";
    if (rssi >= -90) return "Weak";
    return "Very Weak";
}

void SmartFarmWiFiGuard::setReconnectInterval(unsigned long intervalMs) {
    _reconnectIntervalMs = intervalMs;
}

void SmartFarmWiFiGuard::setMaxReconnectAttempts(uint8_t maxAttempts) {
    _maxReconnectAttempts = maxAttempts;
}

void SmartFarmWiFiGuard::enableAutoRestartOnFailure(bool enable, unsigned long restartTimeoutMs) {
    _autoRestartEnabled = enable;
    _restartTimeoutMs = restartTimeoutMs;
}

void SmartFarmWiFiGuard::onConnected(EventCallback callback) {
    _connectedCallback = callback;
}

void SmartFarmWiFiGuard::onDisconnected(EventCallback callback) {
    _disconnectedCallback = callback;
}

void SmartFarmWiFiGuard::onReconnectAttempt(EventCallback callback) {
    _reconnectAttemptCallback = callback;
}

void SmartFarmWiFiGuard::connectWiFi() {
    WiFi.begin(_ssid, _password);
}

void SmartFarmWiFiGuard::handleReconnect() {
    const unsigned long currentMillis = millis();

    if (currentMillis - _lastReconnectAttempt < _reconnectIntervalMs) {
        return;
    }

    _lastReconnectAttempt = currentMillis;

    if (_reconnectAttempts >= _maxReconnectAttempts) {
        return;
    }

    _reconnectAttempts++;

    if (_reconnectAttemptCallback != nullptr) {
        _reconnectAttemptCallback();
    }

    WiFi.disconnect(true, false);
    delay(300);
    WiFi.begin(_ssid, _password);
}
