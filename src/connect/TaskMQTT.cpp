#include "TaskMQTT.h"

#define MQTT_SERVER "io.adafruit.com"
#define MQTT_PORT 1883

WiFiClient espClient;
PubSubClient client(espClient);

String temperature = "25";
String humidity = "100";

void loadInformation() {
    File file = LittleFS.open("/info.dat", "r");
    if (!file) {
        Serial.println("Không thể mở file để đọc");
        return;
    }

    if (file.available()) {
        String tmpUsername = file.readStringUntil('\n');
        tmpUsername.trim();
        if (tmpUsername.length() > 0) {
            IO_USERNAME = tmpUsername;
        }
    }
    if (file.available()) {
        String tmpKey = file.readStringUntil('\n');
        tmpKey.trim();
        if (tmpKey.length() > 0) {
            IO_KEY = tmpKey;
        }
    }
    file.close();
}

String getTemperature() {
    return temperature;
}

String getHumidity() {
    return humidity;
}

//Hàm này dùng để lấy dữ liệu từ adafruit về máy
void callback(char *topic, byte *payload, unsigned int length)
{
    String message;
    for (unsigned int i = 0; i < length; i++)
    {
        message += (char)payload[i];
    }
    if (strcmp(topic, (String(IO_USERNAME) + "/feeds/feed-temperature").c_str()) == 0)
    {
        temperature = message;
        Serial.println(message);
    }
    else if (strcmp(topic, (String(IO_USERNAME) + "/feeds/feed-humidity").c_str()) == 0)
    {
        humidity = message;
        Serial.println(message);
    }
}

void publishData(String feed, String data)
{
    String topic = String(IO_USERNAME) + "/feeds/" + feed;
    if (client.connected())
    {
        client.publish(topic.c_str(), data.c_str());
    }
}

void InitMQTT()
{
    Serial.println("Connecting to MQTT...");
    //loadInformation();
    String clientId = "ESP32Client" + String(random(0, 1000));
    if (client.connect(clientId.c_str(), IO_USERNAME.c_str(), IO_KEY.c_str()))
    {
        Serial.println("MQTT Connected");
        client.subscribe((String(IO_USERNAME) + "/feeds/feed-temperature").c_str());
        client.subscribe((String(IO_USERNAME) + "/feeds/feed-humidity").c_str());

        String data = "Completely connected";
        publishData("feed_1", data);
        publishData("feed-webserver", WiFi.softAPIP().toString());
        Serial.println("Start");
    }
    else
    {
        Serial.print("MQTT connection failed, rc=");
        Serial.println(client.state());
        delay(1000);
    }
}

void reconnectMQTT()
{
    if (client.connected())
    {
        client.loop();
    }
    else
    {
        InitMQTT();
    }
}

void initMQTT()
{
    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setCallback(callback);
}