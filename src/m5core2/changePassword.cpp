#ifdef USEM5_CORE2

#include "changePassword.h"

String Input = "";
String PASSWORD = "";

const int buttonWidth = 60;
const int buttonHeight = 50;
const int margin = 10;
bool flag = false;

bool getFlag() {
    return flag;
}

String getPasswordChanged() {
    return PASSWORD;
}

void drawButton_Change() {
    M5.Lcd.fillScreen(BLACK);

    M5.Lcd.setTextColor(CYAN);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.print("Password: ");

    M5.Lcd.setCursor(10, 40);
    M5.Lcd.setTextColor(YELLOW);
    M5.Lcd.setTextSize(2);
    M5.Lcd.print("Change password");

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

void printInput_Change() {
    M5.Lcd.fillRect(0, 0, 320, 40, BLACK);
    M5.Lcd.setTextColor(CYAN);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.print("Password: ");
    M5.Lcd.print(Input);
}

void change() {
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(267, 10);
    M5.Lcd.setTextColor(YELLOW);
    if (Input.length() <= 4 && Input.length() > 0) {
        PASSWORD = Input;
        flag = true;
        M5.Lcd.print("Ok, change");
    }
    else {
        flag = false;
        M5.Lcd.print("WRONG");
    }
}

void setupChangePassword() {
    flag = false;
    drawButton_Change();
}

bool touchHandled_Change = false;

void loopChangePassword() {
    M5.update();

    if (M5.Touch.ispressed()) {
        TouchPoint_t p = M5.Touch.getPressPoint();

        if (!touchHandled_Change) {  // Chỉ xử lý nếu chưa handled
            for (int i = 1; i <= 9; i++) {
                int row = (i - 1) / 3;
                int col = (i - 1) % 3;
                int x = margin + col * (buttonWidth + margin);
                int y = 60 + row * (buttonHeight + margin);

                if (p.x > x && p.x < x + buttonWidth &&
                    p.y > y && p.y < y + buttonHeight) {
                    if (Input.length() < 4) {
                        Input += String(i);
                        printInput_Change();
                    }

                    touchHandled_Change = true;
                    return;
                }
            }
        }
    } 
    else {
        touchHandled_Change = false;
    }

    if (M5.BtnC.wasReleased()) {
        change();
    }

    if (M5.BtnB.wasReleased()) {
        if (Input.length() < 4) {
            Input = Input + "0";
            printInput_Change();
        }
    }

    // Xóa 1 ký tự
    if (M5.BtnA.wasReleased()) {
        if (Input.length() > 0) {
            Input.remove(Input.length() - 1);
            printInput_Change();
        }
    }
}
#endif