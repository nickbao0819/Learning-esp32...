#include <Arduino.h>

int pin = 12;
int pinButton = 13;
int buttonState = HIGH;       // 稳定的按钮状态
int lastReading = HIGH;       // 上一次读取值
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;  // 消抖延迟50ms
int count = 0;
int lastCount = -1;  // 用于追踪状态变化，防止重复输出

// 呼吸灯相关变量
unsigned long lastBreatheTime = 0;
int breatheDir = 1;  // 1: 亮起, -1: 熄灭
int breatheValue = 0;
const unsigned long breatheInterval = 10;  // 每10ms更新一次

enum ledState_t {
  OFF,
  MID,
  MAX,
  BREATHE
};

const char* ledStateNames[] = {"OFF", "MID", "MAX", "BREATHE"};

void setup() {
  Serial.begin(9600);
  delay(500);
  
  pinMode(pinButton, INPUT_PULLUP);
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);  // 立即拉低GPIO，防止上电时高电平点亮LED
  ledcSetup(0, 5000, 8);
  ledcWrite(0, 0);  // 先设置PWM值为0
  ledcAttachPin(pin, 0);  // 再附加GPIO
  
  Serial.println("System Initialized - LED is OFF (0%)");
}

void readButton(){
  int reading = digitalRead(pinButton);
  
  // 只要读取值变了，就重新计时
  if (reading != lastReading) {
    lastDebounceTime = millis();
  }
  
  // 超过消抖时间后，再确认这次状态变化是否有效
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      
      // 只在按下时触发一次
      if (buttonState == LOW) {
        if(count >= 3) {
          count = 0;
        } else {
          count++;
        }
        
        // 输出按钮按下事件和新的LED状态
        Serial.print("[ Button Pressed ] LED State Changed to: ");
        Serial.println(ledStateNames[count]);
      }
    }
  }
  
  lastReading = reading;
}

void breatheState(){
  if (millis() - lastBreatheTime >= breatheInterval) {
    lastBreatheTime = millis();
    breatheValue += breatheDir;  // 每次增加或减少1
    
    if (breatheValue >= 255) {
      breatheValue = 255;
      breatheDir = -1;  // 转向熄灭
    } else if (breatheValue <= 0) {
      breatheValue = 0;
      breatheDir = 1;   // 转向亮起
    }
    
    ledcWrite(0, breatheValue);
  }
}

void ledState(){
  // 状态发生改变时输出详细信息
  if(count != lastCount) {
    lastCount = count;
    
    switch (count){
      case 0:  // OFF
        ledcWrite(0, 0);
        Serial.println("\n>>> LED State: OFF");
        Serial.println("    PWM Value: 0 (0%)");
        Serial.println("    Brightness: Off\n");
        break;
        
      case 1:  // MID
        ledcWrite(0, 128);
        Serial.println("\n>>> LED State: MID");
        Serial.println("    PWM Value: 128 (50%)");
        Serial.println("    Brightness: Medium\n");
        break;
        
      case 2:  // MAX
        ledcWrite(0, 255);
        Serial.println("\n>>> LED State: MAX");
        Serial.println("    PWM Value: 255 (100%)");
        Serial.println("    Brightness: Maximum\n");
        break;
        
      case 3:  // BREATHE
        Serial.println("\n>>> LED State: BREATHE");
        Serial.println("    Mode: Breathing effect");
        Serial.println("    PWM Value: Dynamic (0-255)\n");
        break;
    }
  }
  
  // 执行对应的LED控制
  switch (count){
    case 0:
      // 已在上面处理
      break;
    case 1:
      // 已在上面处理
      break;
    case 2:
      // 已在上面处理
      break;
    case 3:
      breatheState();
      break;
  }
}

void loop() {
  readButton();
  ledState();
  delay(5);  // 小延迟，优化性能
}