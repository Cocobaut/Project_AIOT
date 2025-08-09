#ifdef USEM5_CORE2

#include "donateM5CORE2.h"

const char* NtpServer = "pool.ntp.org";
const long GmtOffset_sec = 7 * 3600;
const int DaylightOffset_sec = 0;

bool showQRScreen = false;
bool isTouchHandled = false;

unsigned long previousMillis = 0;

void drawPattern(int x, int y) {
    // Các đoạn dọc
    M5.Lcd.drawLine(x, y, x, y+8, WHITE);         // đường giữa trên
    M5.Lcd.drawLine(x+9, y+4, x+9, y+13, WHITE);  // phải 1
    M5.Lcd.drawLine(x+9, y+13, x+9, y+22, WHITE); // phải 2
    M5.Lcd.drawLine(x+18, y+18, x+18, y+27, WHITE); // phải 3
    M5.Lcd.drawLine(x-9, y+4, x-9, y+13, WHITE);  // trái 1
    M5.Lcd.drawLine(x-9, y+13, x-9, y+22, WHITE); // trái 2
    M5.Lcd.drawLine(x-18, y+18, x-18, y+27, WHITE); // trái 3

    // Các đường xiên phải
    M5.Lcd.drawLine(x, y, x+9, y+4, WHITE);
    M5.Lcd.drawLine(x, y+8, x+9, y+13, WHITE);
    M5.Lcd.drawLine(x+9, y+13, x+18, y+18, WHITE);
    M5.Lcd.drawLine(x+9, y+22, x+18, y+27, WHITE);
    M5.Lcd.drawLine(x, y+27, x+9, y+32, WHITE);
    M5.Lcd.drawLine(x-9, y+22, x, y+27, WHITE);
    M5.Lcd.drawLine(x-18, y+27, x-9, y+32, WHITE);

    // Các đường xiên trái
    M5.Lcd.drawLine(x, y, x-9, y+4, WHITE);
    M5.Lcd.drawLine(x, y+8, x-9, y+13, WHITE);
    M5.Lcd.drawLine(x-9, y+13, x-18, y+18, WHITE);
    M5.Lcd.drawLine(x-9, y+22, x-18, y+27, WHITE);
    M5.Lcd.drawLine(x, y+27, x-9, y+32, WHITE);
    M5.Lcd.drawLine(x+9, y+22, x, y+27, WHITE);
    M5.Lcd.drawLine(x+18, y+27, x+9, y+32, WHITE);

    //BK
    M5.Lcd.setTextColor(WHITE); // Màu chữ 
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(x-5,y+14);  
    M5.Lcd.println("BK");

    //0x042B92 xanh đậm
}


void showQRCode() 
{
    M5.Lcd.qrcode("https://docs.google.com/forms/d/e/1FAIpQLSf3AoaFwQhUMa2xq6tNYCXMgbm3UaEgaLUqUjKF8q4bSd41TA/viewform", 40, 0, 240,6);
}

void showMainScreen() 
{
    drawPattern(80, 30);
    M5.Lcd.setCursor(110, 40);
    M5.Lcd.setTextSize(2); 
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.print("ACLAB HCMUT");

    struct tm timeInformation;

    if (getLocalTime(&timeInformation)) {                                       //Instruction 2: Get the current time
        char timeStr[25];

        strftime(timeStr, sizeof(timeStr), "%H:%M:%S %d %b %Y", &timeInformation);    //Instruction 3: Convert time to char array
        M5.Lcd.fillRect(0, 0, 10, 1, BLACK);

        M5.Lcd.setCursor(40, 120);
        M5.Lcd.setTextSize(2); 
        M5.Lcd.print(timeStr);
    }
}

void setupDonateScreen() 
{
    M5.begin();

    //Instruction 1: set up the NTP server and time zone
    configTime(GmtOffset_sec, DaylightOffset_sec, "pool.ntp.org");

    showMainScreen();
}

void loopDonateScreen()
{
    M5.update();

    unsigned long currentMillis = millis(); 

    if (currentMillis - previousMillis >= 15000) {
        previousMillis = currentMillis;

        if (showQRScreen) {
            M5.Lcd.clear(BLACK);
            showMainScreen();
            showQRScreen = false;
        }
        else {
            M5.Lcd.clear(BLACK);
            showQRCode();
            showQRScreen = true;
        }
    }

    if (M5.Touch.ispressed()) {
        if (!isTouchHandled) {
            isTouchHandled = true; 

            if (showQRScreen) {
                M5.Lcd.clear(BLACK);  
                showMainScreen();     
                showQRScreen = false;
            } else {
                M5.Lcd.clear(BLACK); 
                showQRCode();        
                showQRScreen = true;
            }

            previousMillis = currentMillis;
        }
    } 
    else {
        isTouchHandled = false;
    }
}



#endif