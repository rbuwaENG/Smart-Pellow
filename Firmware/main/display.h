#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

void initDisplay();
void displayTime(int hour, int minute, int alarmHour, int alarmMinute, bool alarmSet);

#endif
