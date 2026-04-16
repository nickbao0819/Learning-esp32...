# ESP32 呼吸灯控制系统

[English](README_en.md) | [日本語](README_ja.md)

## 项目概述

这是一个基于 ESP32 微控制器的 LED 呼吸灯控制系统，支持多种 LED 模式切换。通过按钮实现按钮按压计数，控制 LED 在多种状态之间循环切换。

## 功能特性

- **四种 LED 工作模式**：
  - OFF（关闭）
  - MID（中等亮度）
  - MAX（最大亮度）
  - BREATHE（呼吸效果）

- **智能消抖处理**：50ms 消抖延迟，确保按钮读取的稳定性

- **PWM 控制**：使用 LED PWM 控制器实现平滑的亮度调节

- **状态反馈**：通过串口实时输出 LED 状态和按压计数

## 硬件要求

| 组件 | 规格 | 数量 |
|------|------|------|
| ESP32 开发板 | 任意 ESP32 开发板 | 1 |
| LED | 任意颜色（推荐普通 LED） | 1 |
| 按钮 | 触碰按钮或机械按钮 | 1 |
| 电阻 | 220Ω～1kΩ（LED 限流） | 1 |
| 连接线 | 杜邦线 | 若干 |

## 接线图

```
ESP32 GPIO12 ----[220Ω]---- LED正极
ESP32 GND ---- LED负极

ESP32 GPIO13 ---- 按钮
按钮另一端 ---- GND
(GPIO13 使用内部上拉电阻)
```

## 软件要求

- **开发环境**：PlatformIO
- **框架**：Arduino
- **ESP32 核心**：最新版本

## 快速开始

### 1. 克隆项目
```bash
git clone https://github.com/yourusername/esp32-led-control.git
cd esp32-led-control
```

### 2. 打开项目
```bash
# 使用 VS Code + PlatformIO
code .
```

### 3. 上传代码
- 在 VS Code 中打开 PlatformIO 侧栏
- 选择目标环境（ESP32）
- 点击 "Upload" 上传代码到开发板

### 4. 监控串口
- PlatformIO → Project Tasks → ESP32 → Monitor
- 或者使用其他串口监控工具（波特率：9600）

## 使用说明

### 按钮交互

每按一次按钮：
- **按压 1 次**：LED 设置为 OFF（关闭，0%）
- **按压 2 次**：LED 设置为 MID（中等，50%）
- **按压 3 次**：LED 设置为 MAX（最大，100%）
- **按压 4 次**：LED 设置为 BREATHE（呼吸效果）
- **按压 5 次及以后**：循环回到 OFF

### 串口输出示例
```
System Initialized - LED is OFF (0%)
Button pressed 1 times - LED is MID (50%)
Button pressed 2 times - LED is MAX (100%)
Button pressed 3 times - LED is BREATHE (Breathing...)
```

## 代码结构

```
src/
├── main.cpp          # 主程序入口
├── 硬件配置         # GPIO 管脚定义
├── 按钮处理         # 消抖算法实现
└── LED 控制         # PWM 和呼吸灯效果
```

### 关键函数

- `readButton()`：读取按钮状态并进行消抖处理
- `updateLED()`：根据当前模式更新 LED 状态
- `breatheLED()`：实现 LED 呼吸效果

## 技术亮点

1. **消抖算法**：使用时间戳比较的软件消抖方法
2. **状态管理**：使用枚举类型管理 LED 工作模式
3. **PWM 控制**：通过 LED 控制器实现精确的亮度控制
4. **非阻塞设计**：主循环不使用 delay()，响应迅速

## 配置参数

编辑 `src/main.cpp` 中的以下参数来自定义项目：

```cpp
int pin = 12;                           // LED 引脚
int pinButton = 13;                     // 按钮引脚
const unsigned long debounceDelay = 50; // 消抖延迟（毫秒）
const unsigned long breatheInterval = 10; // 呼吸间隔（毫秒）
```

## 故障排除

| 问题 | 解决方案 |
|------|--------|
| LED 不亮 | 检查 GPIO 接线，确认是否连接正确 |
| 按钮无效 | 检查 GPIO13 内部上拉是否启用 |
| LED 闪烁 | 检查消抖延迟设置，可能需要调整 |
| 串口无输出 | 检查 USB 连接和波特率设置（9600） |

## 许可证

MIT License - 详见 [LICENSE](LICENSE) 文件

## 贡献

欢迎提交 Issue 和 Pull Request！

## 作者

Created with ❤️ for ESP32 enthusiasts

---

**其他语言版本**：[English](README_en.md) | [日本語](README_ja.md)
