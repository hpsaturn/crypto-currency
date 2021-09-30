#include <wifi.hpp>

// WiFi credentials (see platformio.ini)
const char *ssid = WIFI_SSID;
const char *password = WIFI_PASS;

int rssi = 0;

/******************************************************************************
*   W I F I   M E T H O D S
******************************************************************************/

void otaMessageCb(voidMessageCbFn cb) {
    ota.setOnUpdateMessageCb(cb);
}

void otaLoop() {
    if (WiFi.isConnected()) {
        ota.loop();
        ota.checkRemoteOTA();
    }
}

void otaInit() {
    ota.setup("EPD47ESP32", "epd47esp32");
}

bool wifiConnect(const char* ssid, const char* pass) {
    Serial.printf("-->[WIFI] connecting to %s\n",ssid);
    int wifi_retry = 0;
    WiFi.begin(ssid, pass);
    while (!WiFi.isConnected() && wifi_retry++ <= WIFI_RETRY_CONNECTION) {
        delay(250);  // increment this delay on possible reconnect issues
    }
    delay(100);
    if (WiFi.isConnected()) {
        Serial.print("-->[WIFI] IP: ");
        Serial.println(WiFi.localIP());
        otaInit();
        return true;
    } else {
        Serial.println("-->[WIFI] disconnected!");
        return false;
    }
}

bool wifiInit() {
    return wifiConnect(WIFI_SSID,WIFI_PASS);
}

void wifiStop() {
    Serial.println("-->[WIFI] Disconnecting..");
    WiFi.disconnect(true);
    delay(100);
}

void wifiRestart() {
    wifiStop();
    wifiInit();
}

int getWifiRSSI() {
    if (WiFi.isConnected()) return WiFi.RSSI();
    else return 0;
}

