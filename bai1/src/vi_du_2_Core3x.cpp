#include <Arduino.h>

#define BUTTON_PIN 4
#define LED_PIN 2

volatile int isrCount = 0;
volatile bool newPress = false;

// ISR CỰC KỲ NGẮN GỌN, biến volatile
void IRAM_ATTR handleButtonInterrupt() {
    isrCount++;
    newPress = true;
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleButtonInterrupt, FALLING);
}

void loop() {
    // Xử lý in Serial trong loop()
    if (newPress) {
        newPress = false;
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
        Serial.printf("Interrupt occurred! Count: %d\n", isrCount);
    }
}
