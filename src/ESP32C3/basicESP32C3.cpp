#ifdef USEESP32_C3

#include "basicESP32C3.h"

#define BUTTON1 2
#define BUTTON2 3
#define BUTTON3 4
#define BUTTON4 5

#define LED1 6
#define LED2 7
#define LED3 8
#define LED4 9

// WiFi
const char* ssid = "ESP32-C3_4IN4OUT";
const char* password = "12345678";

WebServer server1(80);

// State
bool state_LED1 = false;
bool state_LED2 = false;
bool state_LED3 = false;
bool state_LED4 = false;

void handleRoot1() {
  String html = "<html><h1>ESP32-C3 4IN4OUT Control</h1>";
  html += "<p><button onclick=\"location.href='/toggleLED1'\">Toggle LED 1</button></p>";
  html += "<p><button onclick=\"location.href='/toggleLED2'\">Toggle LED 2</button></p>";
  html += "<p><button onclick=\"location.href='/toggleLED3'\">Toggle LED 3</button></p>";
  html += "<p><button onclick=\"location.href='/toggleLED4'\">Toggle LED 4</button></p>";
  
  int button1State = digitalRead(BUTTON1);
  int button2State = digitalRead(BUTTON2);
  int button3State = digitalRead(BUTTON3);
  int button4State = digitalRead(BUTTON4);

  html += "<p>Button 1 State: " + String(button1State == LOW ? "Pressed" : "Released") + "</button></p>";
  html += "<p>Button 2 State: " + String(button2State == LOW ? "Pressed" : "Released") + "</button></p>";
  html += "<p>Button 3 State: " + String(button3State == LOW ? "Pressed" : "Released") + "</button></p>";
  html += "<p>Button 4 State: " + String(button4State == LOW ? "Pressed" : "Released") + "</button></p>";
  
  html += "</html>";
  server1.send(200, "text/html", html);
}

void toggleLED1() {  
  state_LED1 = !state_LED1;                         
  digitalWrite(LED1, state_LED1 ? HIGH : LOW);      
  server1.send(200, "text/plain", "LED1 toggled!");  
}

void toggleLED2() {  
  state_LED2 = !state_LED2;                         
  digitalWrite(LED2, state_LED2 ? HIGH : LOW);      
  server1.send(200, "text/plain", "LED2 toggled!");
}

void toggleLED3() {  
  state_LED3 = !state_LED3;                         
  digitalWrite(LED3, state_LED3 ? HIGH : LOW);      
  server1.send(200, "text/plain", "LED3 toggled!");
}

void toggleLED4() {  
  state_LED4 = !state_LED4;                         
  digitalWrite(LED4, state_LED4 ? HIGH : LOW);      
  server1.send(200, "text/plain", "LED4 toggled!");
}


void setupESP32C3() {
  Serial.begin(115200);

  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  pinMode(BUTTON4, INPUT_PULLUP);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);

  initAcceptPoint();

  server1.on("/", handleRoot1);
  server1.on("/toggleLED1", toggleLED1);
  server1.on("/toggleLED2", toggleLED2);
  server1.on("/toggleLED3", toggleLED3);
  server1.on("/toggleLED4", toggleLED4);

  server1.begin();
}

void loopESP32C3() {
  server1.handleClient();
}

#endif