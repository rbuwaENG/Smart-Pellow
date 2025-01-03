#include "display.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void initDisplay() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    display.clearDisplay();
    display.display();

    // Initialization animation
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 10);
    display.println("Welcome to");
    display.setCursor(10, 25);
    display.setTextSize(2);
    display.println("Smart Pillow");
    display.display();
    delay(2000);

    for (int i = 0; i < SCREEN_WIDTH; i += 4) {
        display.clearDisplay();
        display.drawRect(0, 0, i, SCREEN_HEIGHT, SSD1306_WHITE);
        display.display();
        delay(50);
    }

    display.clearDisplay();
    display.display();
}

void displayTime(int hour, int minute, int alarmHour, int alarmMinute, bool alarmSet) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 10);
    display.printf("Time: %02d:%02d", hour, minute);

    if (alarmSet) {
        display.setCursor(0, 40);
        display.printf("Alarm: %02d:%02d", alarmHour, alarmMinute);
    }

    display.display();
}
