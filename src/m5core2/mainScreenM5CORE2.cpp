#ifdef USEM5_CORE2

#include "mainScreenM5CORE2.h"

#define delay_time 5000

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 7 * 3600;;
const int daylightOffset_sec = 0;

String currentValueTemperature = "";
String currentValueHumidity = "";
String menuButton = "";

// Vẽ biểu tượng nhiệt kế đơn giản (dùng circle + rectangle)
void drawThermometerIcon(int x, int y, uint16_t color) {
    // Vẽ bóng đèn đáy
    M5.Lcd.fillCircle(x + 8, y + 30, 8, color);
    // Vẽ ống thẳng lên
    M5.Lcd.fillRect(x + 6, y + 5, 4, 26, color);
    // Vẽ viền ngoài
    M5.Lcd.drawCircle(x + 8, y + 30, 10, color);
    M5.Lcd.drawRect(x + 5, y + 5, 6, 26, color);
}

// Vẽ giọt nước nhỏ
void drawWaterDropIcon(int x, int y, uint16_t color) {
    M5.Lcd.fillTriangle(x, y, x - 5, y + 10, x + 5, y + 10, color);
    M5.Lcd.fillCircle(x, y + 10, 5, color);
}


//Vẽ nút menu ra màn hình
void drawMenuButtons() {
    String labels[3] = {"Angry Bird", "Direction", "Change Color"};
    for (int i = 0; i < 3; i++) {
        int x = 15;
        int y = 60 + i * 40;
        int w = 180;
        int h = 30;

        M5.Lcd.drawRect(x, y, w, h, WHITE);

        M5.Lcd.setTextSize(2);
        M5.Lcd.setTextColor(WHITE);
        M5.Lcd.setCursor(x + 5, y + 5);
        M5.Lcd.print(labels[i]);
    }
}

//Xử lý menu màn hình
void handleMenuTouch() {
    if (M5.Touch.ispressed()) {
        TouchPoint_t p = M5.Touch.getPressPoint();

        bool touched = false;
        for (int i = 0; i < 3; i++) {
            int x = 15;
            int y = 60 + i * 40;
            int w = 180;
            int h = 30;

            if (p.x >= x && p.x <= x + w && p.y >= y && p.y <= y + h) {
                if (i == 0) {
                    menuButton = "angryBird";
                }
                else if (i == 1) {
                    menuButton = "direction";
                }
                else if (i == 2) {
                    menuButton = "changeColor";
                }
                touched = true;
                break;  // Thoát khỏi vòng lặp sớm vì đã tìm thấy nút
            }
        }
        if (!touched) {
            menuButton = "";
        }
    }
}

void setupMainScreenM5CORE2() {
    //M5.begin();

    M5.Lcd.clear(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setTextColor(YELLOW);
    M5.Lcd.setTextSize(2);

    //Instruction 1: set up the NTP server and time zone
    configTime(gmtOffset_sec, daylightOffset_sec, "pool.ntp.org");

    
    M5.Lcd.drawRect(5, 5, 155, 40, WHITE);
    M5.Lcd.drawRect(165, 5, 150, 40, WHITE);
    
    M5.Lcd.drawRect(5, 50, 200, 130, WHITE);

    M5.Lcd.drawRect(210, 50, 105, 65, WHITE);
    M5.Lcd.drawRect(210, 115, 105, 65, WHITE);

    M5.Lcd.drawRect(5, 185, 310, 45, WHITE);

    //1. Display "ACLAB"
    String label = "ACLAB";
    int labelWidth = M5.Lcd.textWidth(label);
    int x = 165 + (150 - labelWidth) / 2;
    int y = 5 + (40 - 16) / 2;
    M5.Lcd.setCursor(x, y);
    M5.Lcd.print(label);

    //2. Display footer:


    //3. Display menu button
    drawMenuButtons();
}

void loopMainScreenM5CORE2()
{
    //M5.update();
    //3. Display time:
    struct tm timeInformation;

    if (getLocalTime(&timeInformation)) {                                       //Instruction 2: Get the current time
        char timeStr[25];

        strftime(timeStr, sizeof(timeStr), "%d %b %H:%M", &timeInformation);    //Instruction 3: Convert time to char array
        M5.Lcd.fillRect(0, 0, 10, 1, BLACK);

        M5.Lcd.setCursor(8, 15);
        M5.Lcd.print(timeStr);
    }

    //4. Display temperature:
    drawThermometerIcon(220, 55, GREEN);

    String tempTemperature = getTemperature();
    if (tempTemperature != currentValueTemperature) {
        M5.Lcd.setCursor(250, 70);
        M5.Lcd.print(tempTemperature + "\xB0C");
    }

    //5. Display humidity:
    drawWaterDropIcon(230, 135, WHITE);
    String tempHumidity = getHumidity();
    if (tempHumidity != currentValueHumidity) {
        M5.Lcd.setCursor(245, 135);
        M5.Lcd.print(tempHumidity + "%");
    }

    handleColorBoxTouch();
    handleMenuTouch();
    if (menuButton == "angryBird") {
        M5.Lcd.clear(BLACK);
        setupflobbyBird();
        while (true) {
            M5.update();
            reconnectMQTT();
            if (M5.BtnC.pressedFor(3000)) {
                break;
            }
            loopflobbyBird();
        }
        M5.Lcd.clear(BLACK);
        M5.begin();
        menuButton = "";

        setupMainScreenM5CORE2();
    }

    else if (menuButton == "direction") {
        M5.Lcd.clear(BLACK);
        setupArrowButtons();
        while(true) {
            M5.update();
            reconnectMQTT();
            if (M5.BtnC.pressedFor(3000)) {
                break;
            }
            loopArrowButtonTouch();
        }
        M5.Lcd.clear(BLACK);
        M5.begin();
        menuButton = "";
        
        setupMainScreenM5CORE2();
    }

    else if (menuButton == "changeColor") {
        M5.Lcd.clear(BLACK);

        if (drawColorBoxes()) {
            while(true) {
                M5.update();
                reconnectMQTT();
                if (M5.BtnC.pressedFor(3000)) {
                    break;
                }
                handleColorBoxTouch();
            }
        }
        
        M5.Lcd.clear(BLACK);
        M5.begin();
        menuButton = "";
        
        setupMainScreenM5CORE2();
    }
}

#endif