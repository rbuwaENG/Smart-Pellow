#include "keypadhandler.h"
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};
byte rowPins[ROWS] = {32, 33, 27, 14};
byte colPins[COLS] = {26, 25, 4, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void initKeypad() {
    // Initialization logic if needed
}

char getKeypadInput() {
    return keypad.getKey();
}

void handleKeyInput(char key, int &alarmHour, int &alarmMinute, bool &alarmSet) {
    static String input = "";

    if (key == 'A') { // Set alarm hour
        if (input.length() > 0) {
            alarmHour = input.toInt();
            input = "";
        }
    } else if (key == 'B') { // Set alarm minute
        if (input.length() > 0) {
            alarmMinute = input.toInt();
            alarmSet = true;
            input = "";
        }
    } else if (key == 'C') { // Clear alarm
        alarmSet = false;
        alarmHour = -1;
        alarmMinute = -1;
    } else if (isdigit(key)) {
        input += key;
    }
}
