# 📡 TelemetryDash

**Ground Control Station - Serial Telemetry Dashboard**

[![C++](https://img.shields.io/badge/C++-17-00599C.svg)](https://isocpp.org/)
[![Qt](https://img.shields.io/badge/Qt-6.x-41CD52.svg)](https://www.qt.io/)
[![CMake](https://img.shields.io/badge/CMake-3.16+-064F8C.svg)](https://cmake.org/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

## 🎯 Overview

**TelemetryDash** is a desktop Ground Control Station (GCS) interface that receives, parses, and visualizes real-time telemetry data from UAVs or embedded systems via serial communication (UART/RS232).

### ⚡ Key Features

- **📡 Serial Communication**: QSerialPort for UART/RS232 connectivity
- **🔌 Port Management**: Auto-detect and list available COM ports
- **📊 Data Parsing**: String tokenization of telemetry packets (e.g., `ALT:150,BAT:85,SPD:20`)
- **🎨 Visual Displays**: Progress bars, LCD numbers, and real-time gauges
- **📜 Log Console**: Raw data logging in list format
- **⚡ Real-time Updates**: Sub-100ms UI refresh rate

## 🏗️ System Architecture

```
┌─────────────────┐         Serial/UART        ┌─────────────────┐
│  Embedded Sys   │      (QSerialPort)         │  TelemetryDash  │
│  (STM32/Sim)    │ ──────────────────────────>│   (Qt C++)      │
│                 │                             │                 │
│ • Sensors       │   "ALT:150,BAT:85,SPD:20"   │ • Port Manager  │
│ • UART TX       │                             │ • Data Parser   │
│ • 10-50 Hz      │                             │ • GUI Widgets   │
└─────────────────┘                             └─────────────────┘
```

**Data Flow:**
1. **Embedded System**: Sends formatted ASCII packets via UART
2. **QSerialPort**: Receives data on selected COM port (e.g., `/dev/ttyUSB0`, `COM3`)
3. **Parser**: Splits string by delimiter (`,`) and extracts key-value pairs
4. **GUI**: Updates widgets (QProgressBar for battery, QLCDNumber for altitude)

## 🛠️ Technology Stack

- **C++17** - Core application logic
- **Qt 6 Widgets** - GUI framework
- **QSerialPort** - Cross-platform serial I/O
- **CMake** - Build system
- **QSS** - Qt stylesheets for custom UI

## 📦 Project Structure

```
TelemetryDash/
│
├── src/
│   ├── main.cpp                  # Application entry point
│   ├── MainWindow.cpp            # Main window implementation
│   ├── MainWindow.h              # Main window header
│   ├── SerialManager.cpp         # Serial port handler
│   ├── SerialManager.h
│   ├── TelemetryParser.cpp       # Data parsing logic
│   └── TelemetryParser.h
│
├── ui/
│   ├── MainWindow.ui             # Qt Designer UI file
│   └── styles.qss                # Custom stylesheet
│
├── CMakeLists.txt                # Build configuration
├── README.md
├── LICENSE
└── .gitignore
```

## 🚀 Quick Start

### Prerequisites

```bash
# Ubuntu/Debian
sudo apt install qt6-base-dev qt6-serialport-dev cmake build-essential

# macOS
brew install qt cmake

# Windows
# Install Qt from qt.io (include Qt SerialPort module)
```

### Build & Run

```bash
# Clone repository
git clone https://github.com/nisa-s/TelemetryDash.git
cd TelemetryDash

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build
cmake --build . --config Release

# Run
./TelemetryDash          # Linux/macOS
# or
TelemetryDash.exe        # Windows
```

## 📊 Supported Telemetry Format

**Expected packet structure:**
```
ALT:150,BAT:85,SPD:20,HDG:180,ROLL:5,PITCH:-2
```

**Parameter definitions:**
- `ALT` - Altitude in meters (integer)
- `BAT` - Battery percentage 0-100 (integer)
- `SPD` - Speed in m/s (integer/float)
- `HDG` - Heading in degrees 0-360 (integer)
- `ROLL` - Roll angle in degrees ±180 (integer)
- `PITCH` - Pitch angle in degrees ±90 (integer)

**Custom formats** can be added in `TelemetryParser.cpp`

## 🎨 GUI Components

### Dashboard Widgets:
- **🔋 Battery Bar**: QProgressBar with color zones (green >50%, yellow 20-50%, red <20%)
- **📏 Altitude Display**: QLCDNumber with large digits + unit label
- **🚀 Speed Gauge**: QLCDNumber or custom QWidget
- **🧭 Heading Indicator**: Text label (future: circular compass widget)
- **📜 Data Log**: QListWidget showing timestamped raw packets
- **🔌 Connection Panel**: COM port dropdown + baud rate selector + Connect button

### UI Layout (Reusing To-Do List skeleton):
```
┌──────────────────────────────────────┐
│  [COM Port ▼] [115200 ▼] [Connect]  │  ← Was "Add Task" section
├──────────────────────────────────────┤
│  Battery: [████████░░] 85%          │
│  Altitude: [150] m                   │  ← Main display area
│  Speed: [20.5] m/s                   │
├──────────────────────────────────────┤
│  📜 Log Console:                     │
│  [18:51:23] ALT:150,BAT:85,SPD:20   │  ← Was task list
│  [18:51:24] ALT:151,BAT:85,SPD:21   │
└──────────────────────────────────────┘
```

## 🔧 Hardware Integration

### Example: STM32 UART Transmit

```c
// STM32 HAL example - UART2, 115200 baud
char telemetry[64];
uint16_t alt = 150, bat = 85, spd = 20;

sprintf(telemetry, "ALT:%d,BAT:%d,SPD:%d\r\n", alt, bat, spd);
HAL_UART_Transmit(&huart2, (uint8_t*)telemetry, strlen(telemetry), 100);
HAL_Delay(100); // 10 Hz update rate
```

### Arduino Example

```cpp
void loop() {
  int altitude = analogRead(A0);  // Simulated sensor
  int battery = map(analogRead(A1), 0, 1023, 0, 100);
  
  Serial.print("ALT:");
  Serial.print(altitude);
  Serial.print(",BAT:");
  Serial.println(battery);
  
  delay(100); // 10 Hz
}
```

## 🎓 Project Objectives

This project demonstrates key competencies for defense industry applications:

### ✅ **Serial Communication & Embedded Systems**
- Cross-platform serial I/O with QSerialPort
- UART protocol understanding
- Buffer management and asynchronous data handling

### ✅ **Data Processing & Visualization**
- String parsing and tokenization
- Real-time data pipeline
- GUI updates without blocking main thread

### ✅ **C++ & Qt Framework**
- Object-oriented design patterns
- Qt signal-slot mechanism
- Qt Designer for UI layout
- Custom styling with QSS


## 🎓 Academic Context

**Project Type:** Software Engineering Portfolio Project  
**Developer:** 3rd Year Software Engineering Student  
**Duration:** ~1 week (January 2025)  
**Base Code:** Refactored from To-Do List Qt project

### Learning Outcomes
- ✅ Qt Framework (Widgets, Signals/Slots, QSerialPort)
- ✅ Serial communication protocols
- ✅ Real-time data processing
- ✅ Code refactoring and reusability

### Related Courses
- **Embedded Systems** - UART communication
- **OOP** - C++ class design
- **Software Engineering** - Code reuse, version control

## 🤝 Related Projects

- **[EagleEye-Distributed-UAV-Vision](https://github.com/nisa-s/EagleEye-Distributed-UAV-Vision)** - ROS2 vision system (could integrate via ROSBridge)

## 📝 License

MIT License - see [LICENSE](LICENSE) file

## 👨‍💻 Author

**Nisanur Şen**  
3rd Year Software Engineering Student

📧 nisssn.03@gmail.com  
💼 [Nisanur Şen](https://linkedin.com/in/nisanur-şen)  

## 🙏 Acknowledgments

- **Inspiration:** Professional GCS software (Mission Planner, QGroundControl)
- **Purpose:** Internship application
- **Base Code:** Refactored from personal To-Do List project

---

<div align="center">

### ⭐ Star this repository if you find it interesting!

**Made with ❤️ for UAV Ground Control**

</div>

