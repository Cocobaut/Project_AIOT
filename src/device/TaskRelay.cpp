#include "TaskRelay.h"

#define MY_SCL 11
#define MY_SDA 12


#define delay_time 5000

int relayPin = 8;

void taskRelay(void *pvParameters)
{
    pinMode(relayPin, OUTPUT);
    while (true)
    {    
        digitalWrite(relayPin, HIGH);
        delay(2000);
        digitalWrite(relayPin, LOW);
        delay(2000);
        vTaskDelay(delay_time / portTICK_PERIOD_MS);
    }
}

void initRelay()
{
    Wire.begin(MY_SCL, MY_SDA);
    
    xTaskCreate(taskRelay, "Task_name", 4096, NULL, 1, NULL);
}
