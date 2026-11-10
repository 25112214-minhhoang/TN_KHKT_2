#include <Arduino.h>

#define BUTTON_PIN 4
#define LED_PIN 2

volatile int rawEdgeCount = 0;
volatile bool edgeDetected = false;

int debouncedCount = 0;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

int lastReading = HIGH;
int buttonState = HIGH;

// ISR đếm số lần sườn xuống thô (để quan sát hiện tượng dội phím)
void IRAM_ATTR countRawEdge() {
    rawEdgeCount++;
    edgeDetected = true;
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), countRawEdge, FALLING);
}

void loop() {
    int currentReading = digitalRead(BUTTON_PIN);

    // Thuật toán Debounce
    if (currentReading != lastReading) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (currentReading != buttonState) {
            buttonState = currentReading;
            if (buttonState == LOW) {
                debouncedCount++;
                digitalWrite(LED_PIN, !digitalRead(LED_PIN));
                edgeDetected = true; // Kích hoạt in ra kết quả
            }
        }
    }
    lastReading = currentReading;

    // In kết quả định kỳ trong loop(), không in trong ISR
    if (edgeDetected) {
        edgeDetected = false;
        Serial.printf("Raw Edges (Bounces): %d | Debounced Count (Real): %d\n", rawEdgeCount, debouncedCount);
    }
}
