#include "TaskGroundHumidity.h"

#define MY_SCL 11
#define MY_SDA 12

#define groundHumidity_PIN 1

int groundHumidity_Value = 0;

#define delay_time 5000

String getGroundHumidityValue() {
    return String(groundHumidity_Value);
}

void taskGroundHumidity(void *pvParameters)
{
    
    while (true)
    {
        groundHumidity_Value = analogRead(groundHumidity_PIN);
        publishData("feed-groundhumidity-sensor", String(groundHumidity_Value));
        vTaskDelay(delay_time / portTICK_PERIOD_MS);
    }
}

void initGroundHumidity()
{
    Wire.begin(MY_SCL, MY_SDA);
    
    xTaskCreate(taskGroundHumidity, "Task_name", 4096, NULL, 1, NULL);
}
