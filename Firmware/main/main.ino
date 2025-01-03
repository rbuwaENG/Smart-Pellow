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
#include "keypadandler.h"

// WiFi credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

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

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    timeClient.begin();
}

void loop() {
    timeClient.update();
    int currentHour = timeClient.getHours();
    int currentMinute = timeClient.getMinutes();

    // Display current time
    displayTime(currentHour, currentMinute, alarmHour, alarmMinute, alarmSet);

    // Check for keypad input
    char key = getKeypadInput();
    if (key) {
        handleKeyInput(key, alarmHour, alarmMinute, alarmSet);
    }

    // Check for alarm
    if (alarmSet && currentHour == alarmHour && currentMinute == alarmMinute) {
        triggerVibration();
    }

    delay(1000);
}
