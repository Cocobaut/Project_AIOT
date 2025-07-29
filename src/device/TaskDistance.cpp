#include "TaskDistance.h"

#define MY_SCL 11
#define MY_SDA 12

#define trig 18
#define echo 21

// Ultrasonic ultrasonic(6, 7);
#define delay_time 5000

float distance = 0;

float getDistance() {
    return distance;
}

void TaskDistance(void *pvParameters)
{
    while (true)
    {
        unsigned long duration; // biến đo thời gian
        
        digitalWrite(trig, 0);   // tắt chân trig
        delayMicroseconds(2);
        digitalWrite(trig, 1);   // phát xung từ chân trig
        delayMicroseconds(5);   // xung có độ dài 5 microSeconds
        digitalWrite(trig, 0);   // tắt chân trig
        
        duration = pulseIn(echo,HIGH);      // Đo độ rộng xung HIGH ở chân echo
        
        distance = int(duration/2/29.412);  // Tính khoảng cách đến vật.
        
        Serial.println(distance);
        publishData("feed-distance", String(distance) + "cm");
        vTaskDelay(delay_time / portTICK_PERIOD_MS);
    }
}

void initUltrasonic()
{
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    xTaskCreate(TaskDistance, "Task_Ultrasonic", 4096, NULL, 1, NULL);
}