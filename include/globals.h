#ifndef GLOBALS_H
#define GLOBALS_H

// include libraries
#include <Wire.h>
#include <WiFi.h>
#include <DHT20.h>
#include <PubSubClient.h>
#include <Ultrasonic.h>
#include <string.h>
#include <WebServer.h>
#include <Adafruit_NeoPixel.h>
#include <PIR.h>
#include <LiquidCrystal_I2C.h>
#include <ElegantOTA.h>
#include <EEPROM.h>

//Username and password
#include "common/config.h"

//Websocket
#include <ArduinoJson.h>
#include "LittleFS.h"
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>

// Connect
#include "../src/connect/TaskWifi.h"
#include "../src/connect/TaskMQTT.h"
//#include "../src/connect/Webserver.h"
#include "../src/connect/Websocket.h"
#include "../src/connect/acceptPoint.h"

// Device
#include "../src/device/TaskDHT20.h"
#include "../src/device/TaskDistance.h"
#include "../src/device/TaskLedRGB.h"
#include "../src/device/TaskMiniMotor.h"
#include "../src/device/TaskGroundHumidity.h"
#include "../src/device/TaskLightSensor.h"
#include "../src/device/TaskRelay.h"
#include "../src/device/TaskLCD.h"
#include "../src/device/initSensor.h"
#include "../src/device/TaskRelayCH.h"

//M5CORE2
#ifdef USEM5_CORE2
#include <M5Core2.h>
#include "../src/m5core2/projectM5CORE2.h"
#include "../src/m5core2/mainScreenM5CORE2.h"
#include "../src/m5core2/preMainScreenM5CORE2.h"
#include "../src/m5core2/changePassword.h"
#include "../src/m5core2/flobbyBirdM5CORE2.h"
#include "../src/m5core2/directionM5CORE2.h"
#include "../src/m5core2/changeColorM5CORE2.h"
#include "../src/m5core2/donateM5CORE2.h"
#endif

//ESP32-C3
#ifdef USEESP32_C3
#include "../src/ESP32C3/basicESP32C3.h"
#endif

#endif