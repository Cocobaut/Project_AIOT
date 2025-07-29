#include "TaskLCD.h"


#define DISPLAY_TIME 5000 // Thời gian hiển thị 5s

#define TRIG_PIN 18     // GPIO18 (D9)
#define ECHO_PIN 21     // GPIO21 (D10)
#define DELAY_TIME 1000 // Đọc mỗi 1 giây
#define TIMEOUT 30000   // Timeout 30ms (~5m)
#define MY_SCL 11
#define MY_SDA 12


#define ADC_A0 1  // GPIO1
#define ADC_A1 2  // GPIO2
#define ADC_A2 3  // GPIO3
#define ADC_A3 4  // GPIO4
LiquidCrystal_I2C LCD(33, 16, 2);
extern DHT20 dht20;
extern float distance; 

int adcValues[4] = {0, 0, 0, 0};

void TaskLCD(void *pvParameters)
{
    int displayMode = 0;
    while (true)
    {
        if (displayMode == 0) {
            displayTempHumidity();
        }
        else if (displayMode == 1) {
            displayADCValues();
        }
        else {
            displayDistance();
        }
        displayMode = (displayMode + 1) % 3;
        vTaskDelay(DISPLAY_TIME / portTICK_PERIOD_MS);
    }
}

void displayTempHumidity() {
    if (dht20.read() == DHT20_OK) {
        float temperature = dht20.getTemperature();
        float humidity = dht20.getHumidity();

        LCD.clear();

        LCD.setCursor(0, 0);
        LCD.print("Temp: ");
        LCD.print(temperature, 1);
        LCD.print((char)223);       
        LCD.print("C");
        
        LCD.setCursor(0, 1);
        LCD.print("Humidity: ");
        LCD.print(humidity, 1);
        LCD.print("%");
        
    }
    else
    {
        LCD.clear();
        LCD.setCursor(0, 0);
        LCD.print("DHT20 Error!");
    }
}

void displayADCValues() 
{
    adcValues[0] = analogRead(ADC_A0);
    adcValues[1] = analogRead(ADC_A1);
    adcValues[2] = analogRead(ADC_A2);
    adcValues[3] = analogRead(ADC_A3);

    LCD.clear();
    
    LCD.setCursor(0, 0);
    LCD.print("A0:");
    LCD.print(adcValues[0]);
    LCD.setCursor(8, 0);
    LCD.print("A1:");
    LCD.print(adcValues[1]);
    
    LCD.setCursor(0, 1);
    LCD.print("A2:");
    LCD.print(adcValues[2]);
    LCD.setCursor(8, 1);
    LCD.print("A3:");
    LCD.print(adcValues[3]);
}

void displayDistance()
{
    LCD.clear();
    
    LCD.setCursor(0, 0);
    LCD.print("Distance:");
    
    LCD.setCursor(0, 1);
    if (distance > 0) {
        LCD.print(distance, 1);
        LCD.print(" cm");
        
    } else {
        LCD.print("Out of range");
    }
}



void initLCD()
{
    LCD.begin();

    
    // Bật đèn nền
    LCD.backlight();
        
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print("System Starting");
    LCD.setCursor(0, 1);
    LCD.print("Test Mode");
        
    delay(2000);
        
    // Cấu hình các chân ADC
    pinMode(ADC_A0, INPUT);
    pinMode(ADC_A1, INPUT);
    pinMode(ADC_A2, INPUT);
    pinMode(ADC_A3, INPUT);
    analogReadResolution(12);  // 12-bit (0-4095)

    xTaskCreate(TaskLCD, "Task_LCD", 4096, NULL, 1, NULL);
}