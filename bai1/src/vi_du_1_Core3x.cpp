#include <Arduino.h>

#define BUTTON_PIN 4
#define LED_PIN 2

int pressCount = 0;
int lastButtonState = HIGH;

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
    int currentButtonState = digitalRead(BUTTON_PIN);
    if (lastButtonState == HIGH && currentButtonState == LOW) {
        pressCount++;
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
        Serial.printf("Button pressed (Polling)! Count: %d\n", pressCount);
        delay(200); // Delay đơn giản chống dội
    }
    lastButtonState = currentButtonState;
}
