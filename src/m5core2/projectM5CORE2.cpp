#ifdef USEM5_CORE2

#include "projectM5CORE2.h"

unsigned long lastTouchTime = 0;
bool catRunning = false;

void drawCat(int x, int y) {

    // Đầu mèo
    M5.Lcd.fillCircle(x + 20, y + 20, 20, YELLOW);

    // Tai
    M5.Lcd.fillTriangle(x + 5, y + 10, x + 10, y - 10, x + 15, y + 10, YELLOW);
    M5.Lcd.fillTriangle(x + 25, y + 10, x + 30, y - 10, x + 35, y + 10, YELLOW);

    // Mắt
    M5.Lcd.fillCircle(x + 13, y + 20, 2, BLACK);
    M5.Lcd.fillCircle(x + 27, y + 20, 2, BLACK);

}

void runCat() {
    int y = 160;  

    for (int x = -40; x < 320; x += 4) {
        drawCat(x, y);
        delay(20);
        M5.Lcd.fillRect(x, y - 20, 60, 60, BLACK);
    }

    // Sau khi chạy xong, vẽ lại màn hình
    setupMainScreenM5CORE2();
}

void setupM5CORE2() {
    M5.begin();
    setupPreMainScreenM5CORE2();
    while (getCheckPassword() == false) {
        loopPreMainScreenM5CORE2();
    }
    M5.Lcd.clear(BLACK);
    setupMainScreenM5CORE2();
}

void loopM5CORE2()
{
    M5.update();
    loopMainScreenM5CORE2();

    if (M5.Touch.ispressed()) {
        lastTouchTime = millis();
    }

    if (millis() - lastTouchTime > 20000 && !catRunning) {
        catRunning = true;
        runCat();
        catRunning = false;
        lastTouchTime = millis();
    }

    if (M5.BtnA.pressedFor(3000)) {
        M5.Lcd.clear(BLACK);
        setupChangePassword();

        while(getFlag() == false) {
            loopChangePassword();
        }

        setPassword(getPasswordChanged());

        M5.Lcd.clear(BLACK);
        setupPreMainScreenM5CORE2();
        setCheckPass(false);
        while (getCheckPassword() == false) {
            loopPreMainScreenM5CORE2();
            delay(10);
        }
        M5.Lcd.clear(BLACK);
        setupMainScreenM5CORE2();
    }
}

#endif