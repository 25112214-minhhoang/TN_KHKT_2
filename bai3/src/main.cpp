#include <Arduino.h>

#define POT_PIN 34
#define LED_PIN 18

// --- CHUẨN API LEDC 2.x ---
const int pwmChannel = 0;
const int pwmFreq = 5000;
const int pwmResolution = 8; // Phân giải 8-bit (0-255)

// --- BIẾN LỌC MOVING AVERAGE ---
const int numReadings = 10;
int readings[numReadings];
int readIndex = 0;
long total = 0;
int average = 0;

unsigned long lastPrintTime = 0;

void setup() {
    Serial.begin(115200);

    // Khởi tạo mảng lọc trung bình
    for (int i = 0; i < numReadings; i++) {
        readings[i] = 0;
    }

    // KHAI BÁO LEDC CHUẨN 2.x (Tuyệt đối không dùng ledcAttach)
    ledcSetup(pwmChannel, pwmFreq, pwmResolution);
    ledcAttachPin(LED_PIN, pwmChannel);
}

void loop() {
    int rawValue = analogRead(POT_PIN);

    // Thuật toán lọc trung bình di động (Moving Average)
    total = total - readings[readIndex];
    readings[readIndex] = rawValue;
    total = total + readings[readIndex];
    readIndex = (readIndex + 1) % numReadings;
    average = total / numReadings;

    // Map giá trị ADC (0-4095) sang PWM (0-255)
    int pwmValue = map(average, 0, 4095, 0, 255);
    
    // ĐIỀU KHIỂN LED THEO API 2.x
    ledcWrite(pwmChannel, pwmValue);

    // In dữ liệu ra Teleplot (giãn cách 50ms để vẽ mượt)
    if (millis() - lastPrintTime > 50) {
        Serial.printf(">tho:%d\n", rawValue);
        Serial.printf(">loc:%d\n", average);
        lastPrintTime = millis();
    }
}
