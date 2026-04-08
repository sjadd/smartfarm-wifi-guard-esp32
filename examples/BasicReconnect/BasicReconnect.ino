#include <SmartFarmWiFiGuard.h>

const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

SmartFarmWiFiGuard wifiGuard(WIFI_SSID, WIFI_PASSWORD);

void onConnected() {
    Serial.println("[WiFi] Connected successfully.");
    Serial.print("[WiFi] IP address: ");
    Serial.println(wifiGuard.getIPAddress());
}

void onDisconnected() {
    Serial.println("[WiFi] Connection lost.");
}

void onReconnectAttempt() {
    Serial.println("[WiFi] Attempting reconnection...");
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    wifiGuard.onConnected(onConnected);
    wifiGuard.onDisconnected(onDisconnected);
    wifiGuard.onReconnectAttempt(onReconnectAttempt);

    wifiGuard.setReconnectInterval(10000);
    wifiGuard.setMaxReconnectAttempts(20);
    wifiGuard.enableAutoRestartOnFailure(true, 180000);

    wifiGuard.begin();
}

void loop() {
    wifiGuard.update();

    static unsigned long lastPrint = 0;
    if (millis() - lastPrint > 5000) {
        lastPrint = millis();

        Serial.print("[Status] Connected: ");
        Serial.println(wifiGuard.isConnected() ? "Yes" : "No");

        Serial.print("[Status] RSSI: ");
        Serial.println(wifiGuard.getRSSI());

        Serial.print("[Status] Signal Quality: ");
        Serial.println(wifiGuard.getSignalQuality());

        Serial.println("-----------------------------");
    }
}
