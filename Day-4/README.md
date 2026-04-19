# LED Multi-Mode Controller with OLED Display | LED多モード制御 OLED表示 | LED多模式控制器 OLED显示屏

---

## 📖 English | 日本語 | 中文

---

## English

### Overview
This is an ESP32-S3 based LED control system with OLED display that supports multiple LED brightness modes. Users can cycle through different LED states using a button, with real-time display feedback on an SSD1306 OLED screen.

### Features
- **Multi-Mode LED Control**: Four LED brightness modes (OFF, MID, MAX, BREATHE)
- **Button Input**: Debounced button input for mode switching
- **OLED Display**: Real-time mode display on 128×64 SSD1306 OLED screen
- **Breathing Effect**: Smooth PWM fade animation for breathing mode
- **Serial Feedback**: Detailed console output for debugging and monitoring
- **PWM Control**: 5kHz PWM frequency with 8-bit resolution

### Hardware Requirements
- **MCU**: ESP32-S3 DevKit-C 1
- **Display**: SSD1306 OLED (128×64), I2C interface
- **LED**: Connected to GPIO 14 (via current limiting resistor)
- **Button**: Momentary push button connected to GPIO 13 (pull-up)
- **I2C Interface**: 
  - SDA: GPIO 11
  - SCL: GPIO 12

### Software Requirements
- PlatformIO IDE
- Arduino Framework
- Adafruit GFX Library
- Adafruit SSD1306 Library

### Pin Configuration
| Component | GPIO Pin |
|-----------|----------|
| LED Output (PWM) | GPIO 14 |
| Push Button Input | GPIO 13 |
| OLED SDA (I2C) | GPIO 11 |
| OLED SCL (I2C) | GPIO 12 |

### LED Modes

| Mode | PWM Value | Brightness | Description |
|------|-----------|------------|-------------|
| OFF | 0 | 0% | LED is completely off |
| MID | 128 | 50% | LED at medium brightness |
| MAX | 255 | 100% | LED at maximum brightness |
| BREATHE | 0-255 | Dynamic | Smooth fade in/out effect |

### How It Works

1. **Setup Phase**:
   - Initializes serial communication (115200 baud)
   - Initializes I2C interface for OLED
   - Configures GPIO pins and PWM
   - Displays initial state on OLED

2. **Button Reading**:
   - Reads button state with debounce delay (50ms)
   - Cycles through modes: OFF → MID → MAX → BREATHE → OFF
   - Updates OLED display immediately on mode change

3. **LED Control**:
   - OFF mode: PWM value 0
   - MID mode: PWM value 128
   - MAX mode: PWM value 255
   - BREATHE mode: PWM value fades from 0-255 and back (10ms intervals)

4. **OLED Display**:
   - Shows current LED mode name
   - Updates whenever mode changes
   - 128×64 pixel display with I2C communication

### Serial Output Example
```
System Initialized - LED is OFF (0%)
[ Button Pressed ] LED State Changed to: MID

>>> LED State: MID
    PWM Value: 128 (50%)
    Brightness: Medium

[ Button Pressed ] LED State Changed to: MAX

>>> LED State: MAX
    PWM Value: 255 (100%)
    Brightness: Maximum

[ Button Pressed ] LED State Changed to: BREATHE

>>> LED State: BREATHE
    Mode: Breathing effect
    PWM Value: Dynamic (0-255)
```

### Building and Uploading
```bash
# Build the project
pio run -e esp32-s3-devkitc-1

# Upload to device
pio run -e esp32-s3-devkitc-1 -t upload

# Monitor serial output
pio device monitor
```

### Code Structure
- **setup()**: Hardware initialization
- **readButton()**: Debounced button input handling
- **breatheState()**: Breathing LED effect with smooth PWM fade
- **ledState()**: Main LED control logic and mode switching
- **updateOLED()**: OLED display update function
- **loop()**: Main program loop

### Future Enhancements
- Support for RGB LED control
- Adjustable breathing speed
- Custom brightness levels
- Memory to store last used mode
- Additional OLED animations

---

## 日本語

### 概要
これはESP32-S3ベースのLED制御システムで、OLEDディスプレイを備えています。複数のLED輝度モードをサポートしており、ユーザーはボタンを使用して異なるLED状態を切り替えることができます。SSD1306 OLEDスクリーンにリアルタイムで表示されます。

### 機能
- **マルチモードLED制御**: 4つのLED輝度モード（OFF、MID、MAX、BREATHE）
- **ボタン入力**: チャタリング除去されたボタン入力でモード切り替え
- **OLEDディスプレイ**: 128×64 SSD1306 OLEDスクリーンにリアルタイム表示
- **呼吸効果**: 呼吸モード用のスムーズなPWMフェード アニメーション
- **シリアルフィードバック**: デバッグと監視用の詳細なコンソール出力
- **PWM制御**: 5kHz周波数、8ビット分解能

### ハードウェア要件
- **MCU**: ESP32-S3 DevKit-C 1
- **ディスプレイ**: SSD1306 OLED（128×64）、I2Cインターフェース
- **LED**: GPIO 14に接続（電流制限抵抗経由）
- **ボタン**: GPIO 13に接続されたモーメンタリー プッシュボタン（プルアップ）
- **I2Cインターフェース**: 
  - SDA: GPIO 11
  - SCL: GPIO 12

### ソフトウェア要件
- PlatformIO IDE
- Arduino Framework
- Adafruit GFX ライブラリ
- Adafruit SSD1306 ライブラリ

### ピン設定
| コンポーネント | GPIOピン |
|-----------|----------|
| LED出力（PWM） | GPIO 14 |
| プッシュボタン入力 | GPIO 13 |
| OLED SDA（I2C） | GPIO 11 |
| OLED SCL（I2C） | GPIO 12 |

### LEDモード

| モード | PWM値 | 輝度 | 説明 |
|------|-----------|------------|-------------|
| OFF | 0 | 0% | LEDは完全にオフ |
| MID | 128 | 50% | LEDは中程度の明るさ |
| MAX | 255 | 100% | LEDは最大輝度 |
| BREATHE | 0-255 | 動的 | スムーズなフェードイン/アウト効果 |

### 動作原理

1. **セットアップフェーズ**:
   - シリアル通信（115200ボー）を初期化
   - OLEDのI2Cインターフェースを初期化
   - GPIOピンとPWMを設定
   - OLEDに初期状態を表示

2. **ボタン読み込み**:
   - チャタリング除去遅延（50ms）でボタン状態を読み込み
   - モードをサイクル: OFF → MID → MAX → BREATHE → OFF
   - モード変更時にOLEDディスプレイを即座に更新

3. **LED制御**:
   - OFFモード: PWM値 0
   - MIDモード: PWM値 128
   - MAXモード: PWM値 255
   - BREATHEモード: PWM値は0-255にフェード（10ms間隔）

4. **OLEDディスプレイ**:
   - 現在のLEDモード名を表示
   - モード変更時に更新
   - 128×64ピクセル表示、I2C通信

### シリアル出力の例
```
System Initialized - LED is OFF (0%)
[ Button Pressed ] LED State Changed to: MID

>>> LED State: MID
    PWM Value: 128 (50%)
    Brightness: Medium

[ Button Pressed ] LED State Changed to: MAX

>>> LED State: MAX
    PWM Value: 255 (100%)
    Brightness: Maximum

[ Button Pressed ] LED State Changed to: BREATHE

>>> LED State: BREATHE
    Mode: Breathing effect
    PWM Value: Dynamic (0-255)
```

### ビルドとアップロード
```bash
# プロジェクトをビルド
pio run -e esp32-s3-devkitc-1

# デバイスにアップロード
pio run -e esp32-s3-devkitc-1 -t upload

# シリアル出力を監視
pio device monitor
```

### コード構成
- **setup()**: ハードウェア初期化
- **readButton()**: チャタリング除去されたボタン入力処理
- **breatheState()**: スムーズなPWMフェードを使用した呼吸LED効果
- **ledState()**: メインのLED制御ロジックとモード切り替え
- **updateOLED()**: OLEDディスプレイ更新関数
- **loop()**: メインプログラムループ

### 今後の拡張
- RGB LED制御のサポート
- 調整可能な呼吸速度
- カスタム輝度レベル
- 最後に使用したモードを記憶する機能
- 追加のOLEDアニメーション

---

## 中文

### 项目简介
这是一个基于ESP32-S3的LED控制系统，配备OLED显示屏。它支持多个LED亮度模式，用户可以使用按钮在不同的LED状态之间切换，实时反馈显示在SSD1306 OLED屏幕上。

### 主要功能
- **多模式LED控制**: 四种LED亮度模式（关闭、中等、最大、呼吸）
- **按钮输入**: 具有防抖的按钮输入，用于模式切换
- **OLED显示屏**: 128×64 SSD1306 OLED屏幕的实时模式显示
- **呼吸效果**: 呼吸模式的平滑PWM淡入淡出动画
- **串行反馈**: 详细的控制台输出用于调试和监测
- **PWM控制**: 5kHz PWM频率，8位分辨率

### 硬件要求
- **MCU**: ESP32-S3 DevKit-C 1
- **显示屏**: SSD1306 OLED（128×64），I2C接口
- **LED**: 连接到GPIO 14（通过限流电阻）
- **按钮**: 瞬时按钮连接到GPIO 13（上拉）
- **I2C接口**: 
  - SDA: GPIO 11
  - SCL: GPIO 12

### 软件要求
- PlatformIO IDE
- Arduino Framework
- Adafruit GFX 库
- Adafruit SSD1306 库

### 引脚配置
| 组件 | GPIO引脚 |
|-----------|----------|
| LED输出（PWM） | GPIO 14 |
| 按钮输入 | GPIO 13 |
| OLED SDA（I2C） | GPIO 11 |
| OLED SCL（I2C） | GPIO 12 |

### LED模式

| 模式 | PWM值 | 亮度 | 描述 |
|------|-----------|------------|-------------|
| 关闭 | 0 | 0% | LED完全熄灭 |
| 中等 | 128 | 50% | LED中等亮度 |
| 最大 | 255 | 100% | LED最大亮度 |
| 呼吸 | 0-255 | 动态 | 平滑淡入淡出效果 |

### 工作原理

1. **初始化阶段**:
   - 初始化串行通信（115200波特率）
   - 初始化OLED的I2C接口
   - 配置GPIO引脚和PWM
   - 在OLED上显示初始状态

2. **按钮读取**:
   - 使用防抖延迟（50ms）读取按钮状态
   - 在模式间循环切换：关闭 → 中等 → 最大 → 呼吸 → 关闭
   - 模式改变时立即更新OLED显示

3. **LED控制**:
   - 关闭模式：PWM值 0
   - 中等模式：PWM值 128
   - 最大模式：PWM值 255
   - 呼吸模式：PWM值从0-255淡入淡出（10ms间隔）

4. **OLED显示屏**:
   - 显示当前LED模式名称
   - 模式改变时更新
   - 128×64像素显示，I2C通信

### 串行输出示例
```
System Initialized - LED is OFF (0%)
[ Button Pressed ] LED State Changed to: MID

>>> LED State: MID
    PWM Value: 128 (50%)
    Brightness: Medium

[ Button Pressed ] LED State Changed to: MAX

>>> LED State: MAX
    PWM Value: 255 (100%)
    Brightness: Maximum

[ Button Pressed ] LED State Changed to: BREATHE

>>> LED State: BREATHE
    Mode: Breathing effect
    PWM Value: Dynamic (0-255)
```

### 编译和上传
```bash
# 编译项目
pio run -e esp32-s3-devkitc-1

# 上传到设备
pio run -e esp32-s3-devkitc-1 -t upload

# 监控串行输出
pio device monitor
```

### 代码结构
- **setup()**: 硬件初始化
- **readButton()**: 防抖按钮输入处理
- **breatheState()**: 平滑PWM淡入淡出的呼吸LED效果
- **ledState()**: 主LED控制逻辑和模式切换
- **updateOLED()**: OLED显示屏更新函数
- **loop()**: 主程序循环

### 未来增强方向
- RGB LED控制支持
- 可调节的呼吸速度
- 自定义亮度级别
- 保存最后使用模式的内存功能
- 额外的OLED动画

---

## 📄 License
MIT License

## 👨‍💻 Author
Created with PlatformIO

---

**[English](#english) | [日本語](#日本語) | [中文](#中文)**
