#include <Arduino.h>

#define BUTTON_PIN 4
#define LED_PIN 2

void setup() {
    Serial.begin(115200);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    
    // API LEDC chuẩn 2.x
    ledcSetup(0, 5000, 8);
    ledcAttachPin(LED_PIN, 0);
}

void loop() {
    for (int b = 0; b <= 255; b++) {
        ledcWrite(0, b);
        if (digitalRead(BUTTON_PIN) == LOW) {
            Serial.println("button pressed (Polling)");
        }
        delay(10);
    }
    for (int b = 255; b >= 0; b--) {
        ledcWrite(0, b);
        if (digitalRead(BUTTON_PIN) == LOW) {
            Serial.println("button pressed (Polling)");
        }
        delay(10);
    }
}