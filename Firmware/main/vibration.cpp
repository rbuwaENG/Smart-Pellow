// Vibration.cpp
#include "vibration.h"
#include <Arduino.h>

#define VIBRATOR_PIN 25

void initVibration() {
    pinMode(VIBRATOR_PIN, OUTPUT);
}

void triggerVibration() {
    for (int i = 0; i < 10; i++) {
        digitalWrite(VIBRATOR_PIN, HIGH);
        delay(500);
        digitalWrite(VIBRATOR_PIN, LOW);
        delay(500);
    }
}