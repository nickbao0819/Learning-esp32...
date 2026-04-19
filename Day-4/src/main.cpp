#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_SDA 11
#define OLED_SCL 12

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int pin = 14;
int pinButton = 13;
int buttonState = HIGH;
int lastReading = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;
int count = 0;
int lastCount = -1;

// 呼吸灯相关变量
unsigned long lastBreatheTime = 0;
int breatheDir = 1;
int breatheValue = 0;
const unsigned long breatheInterval = 10;

enum ledState_t {
  OFF,
  MID,
  MAX,
  BREATHE
};

const char* ledStateNames[] = {"OFF", "MID", "MAX", "BREATHE"};

void updateOLED(const char* modeName) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 8);
  display.println("LED Mode:");

  display.setTextSize(2);
  display.setCursor(0, 28);
  display.println(modeName);

  display.display();
}

void setup() {
  Serial.begin(115200);
  delay(500);

  Wire.begin(OLED_SDA, OLED_SCL);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED init failed");
    while (true);
  }

  pinMode(pinButton, INPUT_PULLUP);
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);

  ledcSetup(0, 5000, 8);
  ledcWrite(0, 0);
  ledcAttachPin(pin, 0);

  updateOLED(ledStateNames[count]);

  Serial.println("System Initialized - LED is OFF (0%)");
}

void readButton() {
  int reading = digitalRead(pinButton);

  if (reading != lastReading) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        if (count >= 3) {
          count = 0;
        } else {
          count++;
        }

        Serial.print("[ Button Pressed ] LED State Changed to: ");
        Serial.println(ledStateNames[count]);
      }
    }
  }

  lastReading = reading;
}

void breatheState() {
  if (millis() - lastBreatheTime >= breatheInterval) {
    lastBreatheTime = millis();
    breatheValue += breatheDir;

    if (breatheValue >= 255) {
      breatheValue = 255;
      breatheDir = -1;
    } else if (breatheValue <= 0) {
      breatheValue = 0;
      breatheDir = 1;
    }

    ledcWrite(0, breatheValue);
  }
}

void ledState() {
  if (count != lastCount) {
    lastCount = count;

    switch (count) {
      case 0:
        ledcWrite(0, 0);
        Serial.println("\n>>> LED State: OFF");
        Serial.println("    PWM Value: 0 (0%)");
        Serial.println("    Brightness: Off\n");
        break;

      case 1:
        ledcWrite(0, 128);
        Serial.println("\n>>> LED State: MID");
        Serial.println("    PWM Value: 128 (50%)");
        Serial.println("    Brightness: Medium\n");
        break;

      case 2:
        ledcWrite(0, 255);
        Serial.println("\n>>> LED State: MAX");
        Serial.println("    PWM Value: 255 (100%)");
        Serial.println("    Brightness: Maximum\n");
        break;

      case 3:
        breatheValue = 0;
        breatheDir = 1;
        lastBreatheTime = millis();
        Serial.println("\n>>> LED State: BREATHE");
        Serial.println("    Mode: Breathing effect");
        Serial.println("    PWM Value: Dynamic (0-255)\n");
        break;
    }

    updateOLED(ledStateNames[count]);
  }

  switch (count) {
    case 0:
      break;
    case 1:
      break;
    case 2:
      break;
    case 3:
      breatheState();
      break;
  }
}

void loop() {
  readButton();
  ledState();
}