/* File WebSocket (thường là một phần trong code ESP32 – viết bằng Arduino hoặc ESP-IDF) có các nhiệm vụ chính sau:
 *
 * 1. Nhận dữ liệu từ trình duyệt (Web → ESP32)
 *
 * 2. Xử lý yêu cầu, lấy dữ liệu cảm biến từ cảm biến thực tế
 *
 * 3. Gửi dữ liệu trở lại cho trình duyệt (ESP32 → Web)
 *
 */

#include "Websocket.h" 

AsyncWebServer serverSocket(80);        // Create AsyncWebServer object on port 80

AsyncWebSocket ws("/ws");               // Create a WebSocket object

JsonDocument readings;                  // Json Variable to Hold Sensor Readings

#define ledPin 45
int ledState = 0;

bool saved = false;
bool AdjustLedState = false;

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;
unsigned long previousBlinkTime = 0;
int blinkState = LOW;
const unsigned long blinkInterval = 500;

void initLittleFS() {
    if (!LittleFS.begin(true)) {
        Serial.println("An error has occurred while mounting LittleFS");
    }
    Serial.println("LittleFS mounted successfully");
}

// Hàm này có nhiệm vụ: Đọc và đóng gói dữ liệu cảm biến (Get Sensor Readings and return JSON object)
String getSensorReadings(){
    readings["temperature"] = getValueTemperature();
    readings["led"] = String(ledState);
    String jsonString;
    serializeJson(readings, jsonString);
    return jsonString;
}

//Hàm này có công dụng: Gửi chuỗi JSON đến tất cả client WebSocket đang kết nối
void notifyClients(String sensorReadings) {
    ws.textAll(sensorReadings);
}

//Hàm này có công dụng dùng để lưu username và password
void saveInformation(const String& username, const String& password) {
    File file = LittleFS.open("/info.dat", "w");
    if (!file) {
        Serial.println("Không thể mở file");
        return;
    }
    file.println(username);
    file.println(password);
    file.close();
    saved = true;
    if (AdjustLedState == true) {
        setLed(false);
    }
    Serial.println("Đã lưu username và password vào littleFs");
}

//Khi client Web gửi "getReadings", hàm này được gọi để:  Đọc dữ liệu cảm biến và Gửi dữ liệu ngược lại cho client qua WebSocket
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
    AwsFrameInfo *info = (AwsFrameInfo*)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
        String message = "";
        for (size_t i = 0; i < len; i++) {
            message += (char)data[i];
        }
        
        if (message == "getReadings") {
            String sensorReadings = getSensorReadings();
            Serial.print(sensorReadings);
            notifyClients(sensorReadings);
        }
        else if (message == "stateLed") {
            
            if (ledState == 0) {
                digitalWrite(ledPin, LOW);
                ledState = 1;
            }
            else {
                digitalWrite(ledPin, HIGH);
                ledState = 0;
            }
            JsonDocument doc;
            doc["led"] = ledState;
            String response;
            serializeJson(doc, response);
            notifyClients(response);
        }
        else {
            JsonDocument doc;
            DeserializationError error = deserializeJson(doc, message);

            if (!error && !doc["username"].isNull() && !doc["password"].isNull()) {
                String user = doc["username"];
                String pass = doc["password"];

                // Ghi vào bộ nhớ flash
                saveInformation(user, pass);

                // Trả kết quả về web
                JsonDocument res;
                res["status"] = "saved";
                String responseMsg;
                serializeJson(res, responseMsg);
                ws.textAll(responseMsg);

                //Resert wifi về chế độ STA
                delay(1000);
                WiFi.mode(WIFI_OFF);
                WiFi.mode(WIFI_STA);
                InitWiFi();
                initMQTT();
            }
        }
    }
}

//Hàm này có công dụng: Bắt các sự kiện WebSocket
void onEvent(AsyncWebSocket *serverSocket, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    switch (type) {
        case WS_EVT_CONNECT:
            Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
            break;
        case WS_EVT_DISCONNECT:
            Serial.printf("WebSocket client #%u disconnected\n", client->id());
            break;
        case WS_EVT_DATA:
            handleWebSocketMessage(arg, data, len);
            break;
        case WS_EVT_PONG:
        case WS_EVT_ERROR:
            break;
    }
}

void initWebSocket() {
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
    ws.onEvent(onEvent);
    serverSocket.addHandler(&ws);

    initLittleFS();

    // Web Server Root URL
    serverSocket.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        if (WiFi.getMode() == WIFI_STA) {
            request->send(LittleFS, "/dashboard.html", "text/html charset=UTF-8");
        } 
        else {
            request->send(LittleFS, "/index.html", "text/html charset=UTF-8");
        }
    });

    serverSocket.serveStatic("/", LittleFS, "/");

    // Start server
    serverSocket.begin();
    ElegantOTA.begin(&serverSocket);
}

void setLed(bool tmp) {
    AdjustLedState = tmp;
}

//Hàm này có công dụng: Gửi dữ liệu định kỳ & duy trì kết nối
void loopWebsocket() {
    if ((millis() - lastTime) > timerDelay) {
        String sensorReadings = getSensorReadings();
        //Serial.print(sensorReadings);
        notifyClients(sensorReadings);
        lastTime = millis();
    }
    if (saved == false || AdjustLedState == true) {
        if (millis() - previousBlinkTime >= blinkInterval) {
            previousBlinkTime = millis();
            blinkState = !blinkState;
            digitalWrite(ledPin, blinkState);
        }
    }

    if (WiFi.getMode() == WIFI_AP) {
        publishData("feed-webserver", WiFi.softAPIP().toString());
    }
    else if (WiFi.getMode() == WIFI_STA) {
        publishData("feed-webserver", WiFi.localIP().toString());
    }
    ws.cleanupClients();
    ElegantOTA.loop();
}