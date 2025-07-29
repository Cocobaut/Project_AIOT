
#include "TaskLightSensor.h"

#define sensorPin 2
#define delay_time 5000

#define MY_SCL 11
#define MY_SDA 12

int sensorValue = 0;
int lightPercentage = 0;

String getSensorValue() {
    return String(sensorValue) + " " + String(lightPercentage);
}

void taskLightSensor(void *pvParameters)
{
    while (true)
    {
        sensorValue = analogRead(sensorPin);
        lightPercentage = (sensorValue * 100.0) / 4095;
        String data = String(lightPercentage, 1) + "%";
        publishData("feed-light", String(sensorValue));

        if (lightPercentage < 20) {
            publishData("feed-light", "Status: Very Dark");
        } 
        else if (lightPercentage < 40) {
            publishData("feed-light", "Status: Dark");
        } 
        else if (lightPercentage < 60) {
            publishData("feed-light", "Status: Normal");
        } 
        else if (lightPercentage < 80) {
            publishData("feed-light", "Status: Bright");
        } 
        else {
            publishData("feed-light", "Status: Very bright");
        }
        vTaskDelay(delay_time / portTICK_PERIOD_MS);
    }
}

void initLightSensor() {
    Wire.begin(MY_SCL, MY_SDA);

    pinMode(sensorPin, INPUT);
    analogReadResolution(12);

    xTaskCreate(taskLightSensor, "Task_name", 4096, NULL, 1, NULL);
}