#include "fsr.h"
#include <Arduino.h>

#define FSR_PIN 34

void initFSR() {
    pinMode(FSR_PIN, INPUT);
}

int readFSR() {
    return analogRead(FSR_PIN);
}