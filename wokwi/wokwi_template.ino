#define BUTTON_PIN 4
#define LED_PIN 2

volatile bool buttonPressed = false;
unsigned long lastInterruptTime = 0;

void IRAM_ATTR isr() {
  buttonPressed = true;
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), isr, FALLING);
}

void loop() {
  if (buttonPressed) {
    buttonPressed = false;
    
    unsigned long interruptTime = millis();
    // Lọc nhiễu: Bỏ qua các tín hiệu ngắt xuất hiện trong vòng 200ms
    if (interruptTime - lastInterruptTime > 200) {
      digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // Lệnh đảo trạng thái LED
      Serial.println("Button toggled successfully!");
    }
    lastInterruptTime = interruptTime;
  }
}