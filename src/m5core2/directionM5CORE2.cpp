#ifdef USEM5_CORE2

#include "directionM5CORE2.h"

const int buttonSize = 40;          // Tăng kích thước nút
const int centerX = 160;            // Center màn hình theo chiều ngang (320 / 2)
const int centerY = 120;            // Center màn hình theo chiều dọc (240 / 2)

//Hàm hiện thị giá trị nút bấm 
void showDirection(const char* direction) {
    M5.Lcd.fillRect(12, 212, 296, 21, BLACK);
    
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(WHITE, BLACK);
    int textWidth = strlen(direction) * 12;
    int x = (320 - textWidth) / 2;
    M5.Lcd.setCursor(x, 218);
    M5.Lcd.print(direction);
}

// Vẽ các nút điều hướng
void setupArrowButtons() {

    // Nút UP
    M5.Lcd.drawRect(centerX - buttonSize / 2, centerY - buttonSize - 20, buttonSize, buttonSize, WHITE);
    M5.Lcd.setCursor(centerX - 8, centerY - buttonSize - 20 + 5);
    M5.Lcd.print("^");

    // Nút DOWN
    M5.Lcd.drawRect(centerX - buttonSize / 2, centerY + 20, buttonSize, buttonSize, WHITE);
    M5.Lcd.setCursor(centerX - 6, centerY + 20 + 12);
    M5.Lcd.print("v");

    // Nút LEFT
    M5.Lcd.drawRect(centerX - buttonSize - 20, centerY - buttonSize / 2, buttonSize, buttonSize, WHITE);
    M5.Lcd.setCursor(centerX - buttonSize - 20 + 12, centerY - 8);
    M5.Lcd.print("<");

    // Nút RIGHT
    M5.Lcd.drawRect(centerX + 20, centerY - buttonSize / 2, buttonSize, buttonSize, WHITE);
    M5.Lcd.setCursor(centerX + 20 + 12, centerY - 8);
    M5.Lcd.print(">");

    //Vẽ khung footer dưới mà hình
    M5.Lcd.drawRect(10, 210, 300, 25, WHITE);
}

// Hàm xử lý chạm nút
void loopArrowButtonTouch() {
    if (M5.Touch.ispressed()) {
        TouchPoint_t p = M5.Touch.getPressPoint();

        // Nút UP
        if (p.x >= centerX - buttonSize / 2 && p.x <= centerX + buttonSize / 2 &&
            p.y >= centerY - buttonSize - 20 && p.y <= centerY - 20) {
            publishData("feed-direction", "UP");
            showDirection("UP");
        }

        // Nút DOWN
        else if (p.x >= centerX - buttonSize / 2 && p.x <= centerX + buttonSize / 2 &&
                 p.y >= centerY + 20 && p.y <= centerY + buttonSize + 20) {
            publishData("feed-direction", "DOWN");
            showDirection("DOWN");
        }

        // Nút LEFT
        else if (p.x >= centerX - buttonSize - 20 && p.x <= centerX - 20 &&
                 p.y >= centerY - buttonSize / 2 && p.y <= centerY + buttonSize / 2) {
            publishData("feed-direction", "LEFT");
            showDirection("LEFT");
        }

        // Nút RIGHT
        else if (p.x >= centerX + 20 && p.x <= centerX + buttonSize + 20 &&
                 p.y >= centerY - buttonSize / 2 && p.y <= centerY + buttonSize / 2) {
            publishData("feed-direction", "RIGHT");
            showDirection("RIGHT");
        }
    }
}

#endif