# LED Brightness Controller | LED輝度制御 | LED亮度控制

---

## 📖 English | 日本語 | 中文

---

## English

### Overview
This is an ESP32-S3 based project that reads analog input signals and controls LED brightness through PWM (Pulse Width Modulation). The analog input value is mapped to a PWM duty cycle to achieve smooth brightness adjustment.

### Features
- **Analog Input Reading**: Reads ADC (Analog-to-Digital Converter) signals from GPIO 9
- **PWM Control**: Uses PWM on GPIO 0 to control LED brightness
- **Real-time Feedback**: Outputs analog and mapped values via serial communication for monitoring
- **Smooth Operation**: 20ms delay ensures stable signal reading and control

### Hardware Requirements
- **MCU**: ESP32-S3 DevKit-C 1
- **LED**: Connected to GPIO 0 (via current limiting resistor)
- **Analog Sensor**: Connected to GPIO 9
- **USB Cable**: For programming and serial communication

### Software Requirements
- PlatformIO IDE
- Arduino Framework

### Pin Configuration
| Component | GPIO Pin |
|-----------|----------|
| LED Output (PWM) | GPIO 0 |
| Analog Input (ADC) | GPIO 9 |

### How It Works
1. **Setup Phase**: Initializes serial communication, GPIO modes, and PWM configuration (5kHz frequency, 8-bit resolution)
2. **Loop Phase**: 
   - Reads analog input value (0-4095)
   - Maps value to PWM range (0-255)
   - Outputs diagnostic values via serial
   - Adjusts LED brightness via PWM
   - Waits 20ms before repeating

### Serial Output
```
analogValue: [0-4095]
mappedValue: [0-255]
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

### Future Enhancements
- Non-linear brightness mapping (e.g., gamma correction)
- Curve adjustment algorithms
- Multiple LED control
- Sensor calibration

---

## 日本語

### 概要
これはESP32-S3ベースのプロジェクトで、アナログ入力信号を読み取り、PWM（パルス幅変調）を使用してLED輝度を制御します。アナログ入力値はPWMデューティサイクルにマップされて、スムーズな輝度調整を実現します。

### 機能
- **アナログ入力読み込み**: GPIO 9からADC（アナログ-デジタルコンバーター）信号を読み取ります
- **PWM制御**: GPIO 0のPWMを使用してLED輝度を制御します
- **リアルタイムフィードバック**: シリアル通信を介してアナログおよびマップ値を出力して監視します
- **スムーズ動作**: 20ms遅延により安定した信号読み取りと制御を保証します

### ハードウェア要件
- **MCU**: ESP32-S3 DevKit-C 1
- **LED**: GPIO 0に接続（電流制限抵抗経由）
- **アナログセンサー**: GPIO 9に接続
- **USBケーブル**: プログラミングおよびシリアル通信用

### ソフトウェア要件
- PlatformIO IDE
- Arduino Framework

### ピン設定
| コンポーネント | GPIOピン |
|-----------|----------|
| LED出力（PWM） | GPIO 0 |
| アナログ入力（ADC） | GPIO 9 |

### 動作原理
1. **セットアップフェーズ**: シリアル通信、GPIO モード、PWM設定（5kHz周波数、8ビット解像度）を初期化します
2. **ループフェーズ**: 
   - アナログ入力値を読み取ります（0-4095）
   - 値をPWM範囲にマップします（0-255）
   - 診断値をシリアル経由で出力します
   - PWM経由でLED輝度を調整します
   - 20ms待機してから繰り返します

### シリアル出力
```
analogValue: [0-4095]
mappedValue: [0-255]
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

### 今後の拡張
- 非線形輝度マッピング（ガンマ補正など）
- 曲線調整アルゴリズム
- 複数のLED制御
- センサーキャリブレーション

---

## 中文

### 项目简介
这是一个基于ESP32-S3的项目，它读取模拟输入信号，通过PWM（脉宽调制）控制LED的亮度。模拟输入值被映射到PWM占空比范围内，实现平滑的亮度调节。

### 主要功能
- **模拟输入读取**: 从GPIO 9读取ADC（模数转换器）信号
- **PWM控制**: 使用GPIO 0上的PWM控制LED亮度
- **实时反馈**: 通过串行通信输出模拟值和映射值以进行监测
- **平稳运行**: 20ms的延迟确保信号读取和控制的稳定性

### 硬件要求
- **MCU**: ESP32-S3 DevKit-C 1
- **LED**: 连接到GPIO 0（通过限流电阻）
- **模拟传感器**: 连接到GPIO 9
- **USB数据线**: 用于编程和串行通信

### 软件要求
- PlatformIO IDE
- Arduino Framework

### 引脚配置
| 组件 | GPIO引脚 |
|-----------|----------|
| LED输出（PWM） | GPIO 0 |
| 模拟输入（ADC） | GPIO 9 |

### 工作原理
1. **初始化阶段**: 初始化串行通信、GPIO模式和PWM配置（5kHz频率，8位分辨率）
2. **循环阶段**: 
   - 读取模拟输入值（0-4095）
   - 将值映射到PWM范围（0-255）
   - 通过串行输出诊断值
   - 通过PWM调整LED亮度
   - 延迟20ms后重复

### 串行输出
```
analogValue: [0-4095]
mappedValue: [0-255]
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

### 未来增强方向
- 非线性亮度映射（如伽玛校正）
- 曲线调整算法
- 多个LED控制
- 传感器校准

---

## 📄 License
MIT License

## 👨‍💻 Author
Created with PlatformIO

---

**[English](#english) | [日本語](#日本語) | [中文](#中文)**
