#ifdef USEM5_CORE2

#include "changeColorM5CORE2.h"

const char* colorNames[15] = {
    "Coral Red",       // (255, 102, 102)
    "Orange",          // (255, 178, 102)
    "Sunny Yellow",    // (255, 255, 102)
    "Lime Yellow",     // (178, 255, 102)
    "Fresh Green",     // (102, 255, 102)

    "Light Coral",     // (255, 153, 153)
    "Peach",           // (255, 204, 153)
    "Pastel Yellow",   // (255, 255, 153)
    "Light Lime",      // (204, 255, 153)
    "Mint Green",      // (153, 255, 153)

    "Pink",            // (255, 204, 204)
    "Champagne",       // (255, 229, 204)
    "Lemon Cream",     // (255, 255, 204)
    "Light Avocado",   // (229, 255, 204)
    "Pale Green"       // (204, 255, 204)
};

uint16_t colorValues[15] {
    M5.Lcd.color565(255, 102, 102), 
    M5.Lcd.color565(255, 178, 102), 
    M5.Lcd.color565(255, 255, 102),  
    M5.Lcd.color565(178, 255, 102),  
    M5.Lcd.color565(102, 255, 102), 
    
    M5.Lcd.color565(255, 153, 153), 
    M5.Lcd.color565(255, 204, 153),  
    M5.Lcd.color565(255, 255, 153), 
    M5.Lcd.color565(204, 255, 153),  
    M5.Lcd.color565(153, 255, 153),  

    M5.Lcd.color565(255, 204, 204), 
    M5.Lcd.color565(255, 229, 204),  
    M5.Lcd.color565(255, 255, 204), 
    M5.Lcd.color565(229, 255, 204),    
    M5.Lcd.color565(204, 255, 204), 
};

//Vẽ 7 ô màu nằm ngang (footer)
bool drawColorBoxes() {
    int boxWidth = 50;
    int boxHeight = 40;
    int spacing = 8;

    int cols = 5;  // mỗi dòng có 5 ô
    int rows = 3;  // tổng cộng 3 dòng
    int startX = 10;
    int startY = 60;

    int colorIndex = 0;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (colorIndex >= 15) break;  

            int x = startX + col * (boxWidth + spacing);
            int y = startY + row * (boxHeight + spacing);

            M5.Lcd.fillRect(x, y, boxWidth, boxHeight, colorValues[colorIndex]);
            M5.Lcd.drawRect(x, y, boxWidth, boxHeight, WHITE);

            colorIndex++;
        }
    }
    return true;
}

//Xử lý chạm, đổi màu biến color
void handleColorBoxTouch() {
    if (M5.Touch.ispressed()) {
        TouchPoint_t p = M5.Touch.getPressPoint();

        int boxWidth = 50;
        int boxHeight = 40;
        int spacing = 8;

        int cols = 5;  // số ô trong 1 dòng
        int rows = 3;  // số dòng
        int startX = 10;
        int startY = 60;

        int colorIndex = 0;

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (colorIndex >= 15) return;

                int x = startX + col * (boxWidth + spacing);
                int y = startY + row * (boxHeight + spacing);

                if (p.x >= x && p.x <= x + boxWidth &&
                    p.y >= y && p.y <= y + boxHeight) {

                    // Xóa dòng cũ
                    M5.Lcd.fillRect(0, 10, 320, 30, BLACK); 

                    // Hiển thị thông tin màu
                    M5.Lcd.setTextColor(CYAN);
                    M5.Lcd.setTextSize(2);
                    M5.Lcd.setCursor(10, 15);
                    M5.Lcd.print("Color: ");
                    M5.Lcd.print(String(colorNames[colorIndex]));

                    // Gửi dữ liệu nếu cần
                    publishData("feed-color", String(colorNames[colorIndex]));
                    delay(200);
                    return;
                }

                colorIndex++;
            }
        }
    }
}

#endif