#include "keypadhandler.h"
#include <Keypad.h>

const byte ROWS = 4;  // 4 rows for a 4x3 keypad
const byte COLS = 3;  // 3 columns for a 4x3 keypad
char keys[ROWS][COLS] = {
    {'1','2','3'},  // Row 1
    {'4','5','6'},  // Row 2
    {'7','8','9'},  // Row 3
    {'*','0','#'}   // Row 4
};
byte rowPins[ROWS] = {13, 12, 14, 27};  // Row pins
byte colPins[COLS] = {26, 25, 33};  // Column pins
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void initKeypad() {
    // Initialization logic if needed
}

char getKeypadInput() {
    return keypad.getKey();
}

void handleKeyInput(char key, int &alarmHour, int &alarmMinute, bool &alarmSet) {
    static String input = "";
    static bool lastStarPressed = false;  // Track if the last key pressed was '*'

    if (key == '#') {  // Set alarm hour
        if (input.length() > 0 && input.length() < 3) {
            alarmHour = input.toInt();
            input = "";  // Clear input after setting hour
        }
    } else if (key == '*') {  // Set alarm minute or clear alarm if pressed twice
        if (lastStarPressed) {
            // If two '*' are pressed consecutively, clear the alarm
            alarmSet = false;
            alarmHour = -1;
            alarmMinute = -1;
            input = "";  // Clear input as well
            lastStarPressed = false;  // Reset the flag
            Serial.println("Alarm Cleared!");
        } else {
            // Otherwise, continue to set alarm minute
            if (input.length() > 0 && input.length() < 3) {
                alarmMinute = input.toInt();
                alarmSet = true;  // Mark alarm as set
                input = "";  // Clear input after setting minute
            }
            lastStarPressed = true;  // Remember that '*' was pressed
        }
    } else if (key == '0') {  // `0` is not a control key, so treat it as a number
        input += key;  // Append `0` to input
    } else if (isdigit(key)) {  // If a digit key is pressed, add to the input
        input += key;
        lastStarPressed = false;  // Reset double '*' flag
    }
}

