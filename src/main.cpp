#include "globals.h"

#define buttonPin 0

unsigned long buttonPressedTime = 0;
bool buttonPressed = false;

void setup()
{
    Serial.begin(115200);
    Serial.println("OK");
    pinMode(buttonPin, INPUT_PULLUP);

    #ifdef USEM5_CORE2
        //Initialize Wifi
        InitWiFi();

        //Initialize connect web
        initMQTT();

        //Initalize M5Core2
        setupM5CORE2();

    #elif USE_YOLO_UNO
        //Initialize Accept-Point
        WiFi.mode(WIFI_AP);
        initAcceptPoint();
        
        //Initialize websocket
        initWebSocket();

    #endif

    //Initialize sensors
    //initSensor();
}

void loop()
{
    if (!Wifi_reconnect()) {
        return;
    }
    
    #ifdef USE_YOLO_UNO
        if (digitalRead(buttonPin) == LOW) {
            if (!buttonPressed) {
                buttonPressed = true;
                buttonPressedTime = millis();
            }
            else {
                if ((millis() - buttonPressedTime >= 3000) && WiFi.getMode() != WIFI_AP) {
                    WiFi.disconnect(true);
                    WiFi.mode(WIFI_AP);
                    initAcceptPoint();
                    setLed(true);
                }
            }
        }
        else {
            buttonPressed = false;
            buttonPressedTime = 0;
        }
        loopWebsocket();
    #endif

    reconnectMQTT();
    
    #ifdef USEM5_CORE2
        loopM5CORE2();
    #endif

    
    //Serial.println(WiFi.getMode());
}

