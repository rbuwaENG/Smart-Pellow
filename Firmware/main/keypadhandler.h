#ifndef KEYPADHANDLER_H
#define KEYPADHANDLER_H

void initKeypad();
char getKeypadInput();
void handleKeyInput(char key, int &alarmHour, int &alarmMinute, bool &alarmSet);

#endif