#include <Arduino.h>

#define BUTTON_PIN 4
#define LED_PIN 2
volatile bool buttonPressed = false;

void IRAM_ATTR handleInterrupt() {
    buttonPressed = true;
}

void setup() {
    Serial.begin(115200);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    
    // API LEDC chuẩn 2.x
    ledcSetup(0, 5000, 8);
    ledcAttachPin(LED_PIN, 0);
    
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleInterrupt, FALLING);
}

void loop() {
    static int brightness = 0, step = 1;
    
    if (buttonPressed) {
        buttonPressed = false;
        ledcWrite(0, 0); delay(80);   // nháy tắt nhanh
        ledcWrite(0, 255); delay(80); // nháy sáng nhanh
    }
    
    brightness += step;
    if (brightness <= 0 || brightness >= 255) step = -step;
    
    ledcWrite(0, brightness);
    delay(10);
}