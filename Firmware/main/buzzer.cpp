#include "buzzer.h"
#include <Arduino.h>
// Define the pin connected to the buzzer
const int buzzerPin = 4;  // Change this pin to your buzzer's pin

// Function to initialize the buzzer
void initBuzzer() {
    pinMode(buzzerPin, OUTPUT);  // Set the buzzer pin as an output
    noTone(buzzerPin);  // Make sure the buzzer is initially off
}

// Function to trigger a sound on the buzzer
void triggerBuzzer(int frequency, int duration) {
    tone(buzzerPin, frequency, duration);  // Generate a tone with the specified frequency and duration
}

// Function to stop the buzzer sound
void stopBuzzer() {
    noTone(buzzerPin);  // Stop the buzzer sound
}
