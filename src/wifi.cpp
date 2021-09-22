#include <wifi.hpp>

// WiFi credentials (see platformio.ini)
const char *ssid = WIFI_SSID;
const char *password = WIFI_PASS;

int rssi = 0;
String hostId = "";

/******************************************************************************
*   W I F I   M E T H O D S
******************************************************************************/

void wifiConnect(const char* ssid, const char* pass) {
    Serial.print("-->[WIFI] connecting to ");
    Serial.print(ssid);
    int wifi_retry = 0;
    WiFi.begin(ssid, pass);
    while (!WiFi.isConnected() && wifi_retry++ <= WIFI_RETRY_CONNECTION) {
        Serial.print(".");
        delay(200);  // increment this delay on possible reconnect issues
    }
    delay(500);
    if (WiFi.isConnected()) {
        Serial.println(" done.");
        Serial.print("-->[WIFI] IP: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("fail!\n-->[E][WIFI] disconnected!");
    }
}

void wifiInit() {
    wifiConnect(WIFI_SSID,WIFI_PASS);
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
