#include <Arduino.h>

int analogValue;
int mappedValue;

int ledPin = 0;
int adcPin = 9;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  ledcSetup(0, 5000, 8);
  ledcAttachPin(ledPin, 0);
}

void message(){
  Serial.print("analogValue: ");
  Serial.println(analogValue);

  Serial.print("mappedValue: ");
  Serial.println(mappedValue);
}

void calculateBrightness(){
  // 这里可以添加一些算法来调整亮度，例如非线性映射、曲线调整等
  // 目前我们直接使用mappedValue作为PWM值
  analogValue = analogRead(adcPin);

  mappedValue = map(analogValue, 0, 4095, 0, 255);
}

void controlLED(){
  // 直接将mappedValue写入PWM控制LED亮度
  ledcWrite(0, mappedValue);
}

void loop() {

  calculateBrightness();

  message();

  controlLED();
  delay(20); // 小延迟，避免过于频繁地读取和控制

}