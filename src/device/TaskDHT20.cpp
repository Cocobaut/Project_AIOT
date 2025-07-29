#include "TaskDHT20.h"

#define MY_SCL 11
#define MY_SDA 12

DHT20 dht20;
#define delay_time 10000

String getValueTemperature() {
    return String(dht20.getTemperature());
}

String getValueHumidity() {
    return String(dht20.getHumidity() * 100);
}

void TaskTemperatureHumidity(void *pvParameters)
{
    while (true)
    {
        getValueDHT20();
        vTaskDelay(delay_time / portTICK_PERIOD_MS);
    }
}

void getValueDHT20()
{
    if (dht20.read() == DHT20_OK)
    {
        Serial.println(String(dht20.getTemperature()) + "-" + String(dht20.getHumidity()));
        String data1 = String(dht20.getTemperature());
        String data2 = String(dht20.getHumidity());
        publishData("feed-temperature", data1);
        publishData("feed-humidity", data2);
    }
    else
    {
        Serial.println("Failed to read DHT20 sensor.");
    }
}

void initDHT20()
{
    Wire.begin(MY_SCL, MY_SDA);
    dht20.begin();
    xTaskCreate(TaskTemperatureHumidity, "Task_name", 4096, NULL, 1, NULL);
}
