# ESP32 Breathing LED Control System

[中文](README.md) | [日本語](README_ja.md)

## Project Overview

This is an ESP32-based LED breathing light control system that supports multiple LED modes. Use a button to cycle through different LED states and control brightness using PWM.

## Features

- **Four LED Working Modes**:
  - OFF (turned off)
  - MID (medium brightness - 50%)
  - MAX (maximum brightness - 100%)
  - BREATHE (breathing effect)

- **Smart Debouncing**: 50ms debounce delay ensures stable button reading

- **PWM Control**: Smooth brightness adjustment using LED PWM controller

- **Serial Feedback**: Real-time status and button press count via UART

## Hardware Requirements

| Component | Specification | Quantity |
|-----------|---------------|----------|
| ESP32 Board | Any ESP32 development board | 1 |
| LED | Any color (regular LED recommended) | 1 |
| Button | Touch or mechanical button | 1 |
| Resistor | 220Ω～1kΩ (for LED current limiting) | 1 |
| Wires | Dupont jumper wires | Multiple |

## Wiring Diagram

```
ESP32 GPIO12 ----[220Ω]---- LED Positive
ESP32 GND ---- LED Negative

ESP32 GPIO13 ---- Button
Button Other End ---- GND
(GPIO13 uses internal pull-up resistor)
```

## Software Requirements

- **Development Environment**: PlatformIO
- **Framework**: Arduino
- **ESP32 Core**: Latest version

## Quick Start

### 1. Clone Repository
```bash
git clone https://github.com/yourusername/esp32-led-control.git
cd esp32-led-control
```

### 2. Open Project
```bash
# Using VS Code + PlatformIO
code .
```

### 3. Upload Code
- Open PlatformIO sidebar in VS Code
- Select target environment (ESP32)
- Click "Upload" to flash code to the board

### 4. Monitor Serial Output
- PlatformIO → Project Tasks → ESP32 → Monitor
- Or use other serial monitor tools (Baud rate: 9600)

## Usage Guide

### Button Interaction

Each button press cycles through modes:
- **Press 1 time**: LED OFF (0%)
- **Press 2 times**: LED MID (50%)
- **Press 3 times**: LED MAX (100%)
- **Press 4 times**: LED BREATHE (breathing effect)
- **Press 5+ times**: Cycles back to OFF

### Serial Output Example
```
System Initialized - LED is OFF (0%)
Button pressed 1 times - LED is MID (50%)
Button pressed 2 times - LED is MAX (100%)
Button pressed 3 times - LED is BREATHE (Breathing...)
```

## Code Structure

```
src/
├── main.cpp          # Main program entry
├── Hardware Config   # GPIO pin definitions
├── Button Handler    # Debounce algorithm
└── LED Control       # PWM and breathing effects
```

### Key Functions

- `readButton()`: Read button state with debouncing
- `updateLED()`: Update LED state based on current mode
- `breatheLED()`: Implement LED breathing effect

## Technical Highlights

1. **Debounce Algorithm**: Software debouncing using timestamp comparison
2. **State Management**: LED modes managed with enum types
3. **PWM Control**: Precise brightness control via LED controller
4. **Non-blocking Design**: Main loop avoids delay(), ensuring quick response

## Configuration Parameters

Edit the following parameters in `src/main.cpp` to customize:

```cpp
int pin = 12;                           // LED pin
int pinButton = 13;                     // Button pin
const unsigned long debounceDelay = 50; // Debounce delay (milliseconds)
const unsigned long breatheInterval = 10; // Breathing interval (milliseconds)
```

## Troubleshooting

| Issue | Solution |
|-------|----------|
| LED won't light up | Check GPIO wiring and connections |
| Button not responding | Verify GPIO13 pull-up is enabled |
| LED flickering | Adjust debounce delay settings |
| No serial output | Check USB connection and baud rate (9600) |

## License

MIT License - See [LICENSE](LICENSE) file for details

## Contributing

Issues and Pull Requests are welcome!

## Author

Created with ❤️ for ESP32 enthusiasts

---

**Other Languages**: [中文](README.md) | [日本語](README_ja.md)
