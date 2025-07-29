#ifdef USEM5_CORE2

#include <M5Core2.h>

void setupBasic() {
    //Instruction 1: Init M5Core2
    M5.begin(true, true, true, false, kMBusModeInput, false);

    //Instruction 2: Print text on the screen
    M5.Lcd.print("Hello, world");

    //Instruction 3: Set the scren background color
    M5.Lcd.fillScreen(WHITE);
    delay(500);

    M5.Lcd.fillScreen(RED);
    delay(500);

    M5.Lcd.fillScreen(GREEN);
    delay(500);
    
    M5.Lcd.fillScreen(BLUE);
    delay(500);

    M5.Lcd.fillScreen(BLACK);
    delay(500);

    //Intruction 4: Move the cursor position to (x, y) = (10, 10)
    M5.Lcd.setCursor(10, 10);

    //Instruction 5: Set the font color to white
    M5.Lcd.setTextColor(0xFFFFCC);
    M5.Lcd.setTextSize(5);
    M5.Lcd.printf("ACLAB IOT");

    delay(1000);

    //Instruction 6: Draw graphic
    M5.Lcd.drawRect(100, 100, 50, 50, RED);                     //Draw a 50x50 red rectangle wireframe at (100,100)
    M5.Lcd.fillRect(100, 100, 40, 40, GREEN);                   //Draw a green rectangle 40x40 at (100,100)

    delay(1000);

    M5.Lcd.drawCircle(100, 100, 30, BLUE);                      //Draw a blue circle with radius 30 at 100x100
    M5.Lcd.fillCircle(100, 100, 20, YELLOW);                    //Draw a yellow circle with radius 20 at 100x100

    delay(1000);

    M5.Lcd.drawLine(0, 0, 240, 240, WHITE);                     //Draw a white line from (0,0) to (240,240)

    delay(1000);
    M5.Lcd.drawTriangle(30, 30, 180, 100, 80, 150, YELLOW);     //Draw a yellow triangle with vertices at (30,30), (180,100), (80,150)
    M5.Lcd.fillTriangle(30, 30, 180, 100, 80, 150, RED);        //Fill the triangle with red color

    //Instruction 7: Clear the screen and set white to the background color
    M5.Lcd.clear(BLACK);

    M5.Lcd.setCursor(0, 0);
}

void loopBasic() {
    //Instruction 8: Read the press state of the key (This function is necessary to update the display and handle touch events)
    M5.update();

    /*Instruction about putton:
     *
     *  Instruction 9: isPressed(): Trả về true nếu nút đang được nhấn
     * 
     *  Instruction 10: wasReleased(): Trả về true nếu nút vừa được thả ra
     * 
     *  Instruction 11: pressedFor(uint32_t ms): Trả về true nếu nút đang được giữ trên thời gian ms xác định
     * 
     *  Instruction 12: releasedFor(uint32_t ms): Trả về true nếu nút đang được thả trên thời gian ms xác định
     * 
     */ 

    //Note: BtnA, BtnB, BtnC are the buttons on the bottom of the screen

    if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 200)) {
        M5.Lcd.print('A');
    } 
    else if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(1000, 200)) {
        M5.Lcd.print('B');
    } 
    else if (M5.BtnC.wasReleased() || M5.BtnC.pressedFor(1000, 200)) {
        M5.Lcd.print('C');
    } 
    else if (M5.BtnB.wasReleasefor(700)) {
        M5.Lcd.clear(WHITE);
        M5.Lcd.setCursor(0, 0);
    }
}

#endif