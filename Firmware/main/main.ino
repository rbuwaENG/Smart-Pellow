// main.ino
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "vibration.h"
#include "fsr.h"
#include "display.h"
#include "keypadhandler.h"
#include "buzzer.h"

// WiFi credentials
const char* ssid = "Pixel 6";
const char* password = "21472147";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 0, 60000);

int alarmHour = -1;
int alarmMinute = -1;
bool alarmSet = false;

void setup() {
    Serial.begin(115200);

    // Initialize components
    initDisplay();
    initVibration();
    initFSR();
    initKeypad();
    initBuzzer();

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    timeClient.begin();
    timeClient.setTimeOffset(19800);
}

void loop() {
    timeClient.update();
    int currentHour = timeClient.getHours();
    int currentMinute = timeClient.getMinutes();

    // Display current time
    displayTime(currentHour, currentMinute, alarmHour, alarmMinute, alarmSet);

    // Check for keypad input
    char key = getKeypadInput();
    Serial.println(key);
    if (key) {
        handleKeyInput(key, alarmHour, alarmMinute, alarmSet);
    }

    // Check if alarm is set and the time has reached
    static bool alarmTriggered = false;  // To avoid triggering the alarm multiple times
    if (alarmSet && currentHour == alarmHour && currentMinute == alarmMinute && !alarmTriggered) {
        triggerVibration();  // Trigger vibration when alarm time matches
        triggerBuzzer(100,10);
        Serial.println("Alarm triggered!");
        alarmTriggered = true;  // Set to true to avoid multiple triggers
    }

    // Reset the alarmTriggered flag if the time has passed
    if (currentHour != alarmHour) {
        alarmTriggered = false;  // Allow the alarm to be triggered again the next day
    }

    delay(10);
}

