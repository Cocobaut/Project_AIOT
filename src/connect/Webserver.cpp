/*  
  Rui Santos & Sara Santos - Random Nerd Tutorials
  https://RandomNerdTutorials.com/esp32-web-server-beginners-guide/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*/

#include "Webserver.h"

// Assign output variables to GPIO pins
const int outputledBoard = 48;
String outputLED = "UNACTIVE";

int ledColor = 0;
bool automatical = false;

// Create a web server object
WebServer server(80);

// Function to handle turning LED on
void handleLEDACTIVE() {
    outputLED = "ACTIVE";
    digitalWrite(outputledBoard, HIGH);
    handleRoot();
}

// Function to handle turning LED off
void handleLEDUNACTIVE() {
    outputLED = "UNACTIVE";
    digitalWrite(outputledBoard, LOW);
    handleRoot();
}

//Function to turn on Automatical
void handleAutomaticalON() {
    automatical = true;
    set_stateLEDRGB(-1);
    handleRoot();
}

void handleAutomaticalOFF() {
    automatical = false;
    handleRoot();
}

//Function to turn led RGB Red
void handleColorRed() { 
    set_stateLEDRGB(0); 
    handleRoot(); 
}

//Function to turn led RGB Orange
void handleColorOrange() { 
    set_stateLEDRGB(1);
    handleRoot(); 
}

//Function to turn led RGB Yellow
void handleColorYellow() { 
    set_stateLEDRGB(2);
    handleRoot(); 
}

//Function to turn led RGB Green
void handleColorGreen() { 
    set_stateLEDRGB(3);
    handleRoot(); 
}
//Function to turn led RGB Violet
void handleColorIndigo() { 
    set_stateLEDRGB(4);
    handleRoot(); 
}

//Function to turn led RGB Purple
void handleColorPurple() { 
    set_stateLEDRGB(5);
    handleRoot(); 
}

//Function to turn led RGB White
void handleColorWhite() { 
    set_stateLEDRGB(6);
    handleRoot(); 
}
//Function to turn led RGB Black
void handleColorBlack() { 
    set_stateLEDRGB(7);
    handleRoot(); 
}
// Function to handle the root URL and show the current states
void handleRoot() {
    String html = "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
    html += "<link rel=\"icon\" href=\"data:,\">";
    html += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
    html += ".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}";
    html += ".button2 { background-color: #555555; }</style></head>";
    html += "<body><h1>ESP32 Web Server</h1>";

    // Display LED
    html += "<h1> LED </h1>";
    html += "<p>State " + outputLED + "</p>";
    if (outputLED == "UNACTIVE") {
        html += "<p><a href=\"/LED/on\"><button class=\"button\">ACTIVE</button></a></p>";
    } 
    else {
        html += "<p><a href=\"/LED/off\"><button class=\"button button2\">UNACTIVE</button></a></p>";
    }

    //Display ledRGB
    html += "<h1> LED RGB </h1>";

    html += "<h1>Automatical Mode</h1>";
    html += "<p>State: " + String(automatical ? "ON" : "OFF") + "</p>";
    if (!automatical) {
        html += "<p><a href=\"/auto/on\"><button class=\"button\">Enable</button></a></p>";
    } 
    else {
        html += "<p><a href=\"/auto/off\"><button class=\"button button2\">Disable</button></a></p>";
    }

    html += "<h1> LED RGB </h1>";
    html += "<p>Selected Color: " + String(ledColor) + "</p>";

    if (!automatical) {
        html += "<p>";
        html += "<a href=\"/rgb/red\"><button class=\"button\" style=\"background-color:#FF0000\">Red</button></a>";
        html += "<a href=\"/rgb/orange\"><button class=\"button\" style=\"background-color:#FFA500\">Orange</button></a>";
        html += "<a href=\"/rgb/yellow\"><button class=\"button\" style=\"background-color:#FFFF00; color:#000\">Yellow</button></a>";
        html += "<a href=\"/rgb/green\"><button class=\"button\" style=\"background-color:#00FF00\">Green</button></a>";
        html += "<a href=\"/rgb/indigo\"><button class=\"button\" style=\"background-color:#4B0082\">Indigo</button></a>";
        html += "<a href=\"/rgb/purple\"><button class=\"button\" style=\"background-color:#800080\">Purple</button></a>";
        html += "<a href=\"/rgb/white\"><button class=\"button\" style=\"background-color:#FFFFFF; color:#000\">White</button></a>";
        html += "<a href=\"/rgb/black\"><button class=\"button\" style=\"background-color:#000000\">Black</button></a>";
        html += "</p>";
    } 
    else {
        html += "<p><i>Enable Automatical to use color buttons</i></p>";
    }
    
    //Display parameter
    html += "<h1> SENSOR DATA </h1>";
    html += "<p>Temperature: " + getValueTemperature() + "</p>";
    html += "<p>Distance: " + String(getDistance()) + "</p>";
    html += "<p>Light sensor: " + getSensorValue() + "</p>";
    html += "<p>Ground Humidity: " + getGroundHumidityValue() + "</p>";
    html += "</body></html>";
    server.send(200, "text/html", html);
}

void initWebserver() {
    Serial.begin(115200);

    pinMode(outputledBoard, OUTPUT);
    digitalWrite(outputledBoard, LOW);

    // Connect to Wi-Fi network
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    // Set up the web server to handle different routes
    server.on("/", handleRoot);
    server.on("/LED/on", handleLEDACTIVE);
    server.on("/LED/off", handleLEDUNACTIVE);

    server.on("/auto/on", handleAutomaticalON);
    server.on("/auto/off", handleAutomaticalOFF);

    server.on("/rgb/red", handleColorRed);
    server.on("/rgb/orange", handleColorOrange);
    server.on("/rgb/yellow", handleColorYellow);
    server.on("/rgb/green", handleColorGreen);
    server.on("/rgb/indigo", handleColorIndigo);
    server.on("/rgb/purple", handleColorPurple);
    server.on("/rgb/white", handleColorWhite);
    server.on("/rgb/black", handleColorBlack);
    // Start the web server
    server.begin();
    Serial.println("HTTP server started");
}

void webserverConnect() {

    if(WiFi.status() != WL_CONNECTED)
        return;
    server.handleClient();
}