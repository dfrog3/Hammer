//
// Created by David Kaschub on 2021/07/11.
//


#include "HammerDisplay.h"
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define DISPLAY_ADDRESS 0x3C

Adafruit_SSD1306 display(128, 32);

HammerDisplay::HammerDisplay() {
    delay(1000);
    if (!display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS)) {
        Serial.println("SSD1306 allocation failed");
        for (;;);
    }

    display.display();
    display.setRotation(3);
}

void HammerDisplay::WriteText(String txt) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println(txt);
    display.display();

}

void HammerDisplay::WriteBool(bool v) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    if (v) {

        display.println("true");
    } else {
        display.println("false");

    }
    display.display();
}

void HammerDisplay::WriteRotaryState(RotaryState state) {

    switch (state) {

        case Up:
            WriteText("up");
            break;
        case Down:
            WriteText("Down");
            break;
        case Nothing:
            WriteText("Nothing");
            break;
    }
}
