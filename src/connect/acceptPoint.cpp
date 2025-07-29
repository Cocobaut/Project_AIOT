#include "acceptPoint.h"

// const char* ssid     = "ESP32-Access-Point -QK";
// const char* password = "123456789";

void initAcceptPoint() {
    Serial.print("Setting AP (Access Point)…");

    WiFi.softAP(MY_BOARD);
    Serial.println("✅ Access Point started!");
    Serial.print("📡 IP Address: ");
    Serial.println(WiFi.softAPIP());
}

void loopAcceptPoint(){
    Serial.println("Client disconnected.");
    Serial.println("");
}
