#ifdef USEM5_CORE2

#include "preMainScreenM5CORE2.h"

String input = "";
String password = "0204";

const int buttonWidth = 60;
const int buttonHeight = 50;
const int margin = 10;
bool checkPass = false;

void drawButton() {
    M5.Lcd.fillScreen(BLACK);


    M5.Lcd.setTextColor(CYAN);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.print("Password: ");

    M5.Lcd.setCursor(10, 40);
    M5.Lcd.setTextColor(YELLOW);
    M5.Lcd.setTextSize(2);
    M5.Lcd.print("Input password");
    

    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(3);

    int num = 1;
    for (int i = 1; i <= 9; i++) {
        int row = (i - 1) / 3;
        int col = (i - 1) % 3;
        int x = margin + col * (buttonWidth + margin);
        int y = 60 + row * (buttonHeight + margin);

        M5.Lcd.fillRect(x, y, buttonWidth, buttonHeight, DARKGREY);
        M5.Lcd.setCursor(x + 20, y + 15);
        M5.Lcd.print(num);
        num++;
    }
}

void printInput() {
    M5.Lcd.fillRect(0, 0, 320, 40, BLACK);
    M5.Lcd.setTextColor(CYAN);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.print("Password: ");
    M5.Lcd.print(input);
}

void checkPassword() {
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(250, 70);
    M5.Lcd.setTextColor(YELLOW);
    if (input == password) { 
        checkPass = true;
    } 
    else {
        M5.Lcd.print("WRONG");
        checkPass = false;
    }
}

bool getCheckPassword() {
    return checkPass;
}

void setPassword(String passTmp) {
    password = passTmp;
}

void setCheckPass(bool tmp) {
    checkPass = tmp;
}

void setupPreMainScreenM5CORE2() {
    M5.Lcd.setRotation(1);
    
    drawButton();
}

bool touchHandled = false;

void loopPreMainScreenM5CORE2() {
    M5.update();

    if (M5.Touch.ispressed()) {
        TouchPoint_t p = M5.Touch.getPressPoint();

        if (!touchHandled) {  // Chỉ xử lý nếu chưa handled
            for (int i = 1; i <= 9; i++) {
                int row = (i - 1) / 3;
                int col = (i - 1) % 3;
                int x = margin + col * (buttonWidth + margin);
                int y = 60 + row * (buttonHeight + margin);

                if (p.x > x && p.x < x + buttonWidth &&
                    p.y > y && p.y < y + buttonHeight) {
                    if (input.length() < 4) {
                        input += String(i);
                        printInput();
                    }

                    touchHandled = true;
                    return;
                }
            }
        }
    } 
    else {
        touchHandled = false;
    }

    if (M5.BtnC.wasReleased()) {
        checkPassword();
    }
    else if (M5.BtnB.wasReleased()) {
        if (input.length() < 4) {
            input = input + "0";
            printInput();
        }
    }
    // Xóa 1 ký tự
    else if (M5.BtnA.wasReleased()) {
        if (input.length() > 0) {
            input.remove(input.length() - 1);
            printInput();
        }
    }
}

#endif