# 🚀 ESP32 UART Communication with STM32 - LED Control via Serial Messages

Welcome to the **ESP32 UART Communication with STM32** project! This project enables the **ESP32** to communicate with the **STM32 microcontroller** via **UART**. You can send **ON/OFF commands** from the ESP32 to control an LED connected to the STM32 board. This demonstrates **real-time communication** between two microcontrollers and shows how serial messaging can be used effectively.

---

## 📋 Table of Contents
- [📖 Introduction](#-introduction)
- [✨ Features](#-features)
- [⚙️ How It Works](#️-how-it-works)
- [📊 Specifications](#-specifications)
- [🔧 Hardware Requirements](#-hardware-requirements)
- [💻 Software Requirements](#-software-requirements)
- [🔌 Wiring Diagram](#-wiring-diagram)
- [⚡ Installation and Setup](#-installation-and-setup)
- [📑 ESP32 Code Overview](#-esp32-code-overview)
- [📐 Usage](#-usage)
- [🛠️ Future Improvements](#-future-improvements)
- [🤝 Contributing](#-contributing)
- [📄 License](#-license)
- [🎉 Acknowledgments](#-acknowledgments)

---

## 📖 Introduction
This project showcases the use of **UART communication** between two popular microcontrollers: the **ESP32** and **STM32**. The ESP32 sends **"ON"** or **"OFF"** messages over UART to the STM32, which then toggles an LED on its GPIO pin. This is a great example of:
- Inter-microcontroller communication
- Real-time serial messaging
- Hardware control using software protocols

---

## ✨ Features
- 🌐 **UART Communication** between ESP32 and STM32
- 🟢 **Control LED ON/OFF** remotely from ESP32
- ⚡ **Real-time updates** with minimal latency
- 🔄 **Bidirectional communication** capability (future extension)
- 🛠️ **Easy to modify and extend**

---

## ⚙️ How It Works
1. The ESP32 sends **"ON"** or **"OFF"** messages via UART.
2. The STM32 listens on UART and toggles the **LED** connected to **PB3** based on the received message.
3. A small **debounce delay** ensures reliable button presses on the ESP32 side.

---

## 📊 Specifications
- **ESP32** running on 115200 baud rate for UART communication.
- **STM32** microcontroller listening on **USART2 RX** at 115200 baud.
- LED connected to **PB3** pin on STM32.
- Messages: 
  - `"ON"` to turn the LED ON.
  - `"OFF"` to turn the LED OFF.

---

## 🔧 Hardware Requirements
- 🛠 **ESP32 Development Board**
- 🛠 **STM32 Microcontroller (e.g., STM32F103 or STM32F401)**
- 🟢 **LED** (connected to PB3 pin of STM32)
- ⚡ **Breadboard and Jumpers** for wiring
- 🌀 **USB-to-Serial Converter** (for debugging if needed)

---

## 💻 Software Requirements
- **Arduino IDE** (for ESP32 code)
- **STM32CubeMX** (for STM32 configuration)
- **PlatformIO** (optional alternative)
- **USB drivers** for ESP32 and STM32
- **Serial monitor** (e.g., PuTTY or Arduino Serial Monitor)

---

## 🔌 Wiring Diagram
```plaintext
ESP32 TX (GPIO 17) --> STM32 RX (USART2)
ESP32 RX (GPIO 16) <-- STM32 TX (Optional for debugging)
ESP32 GND ---------> STM32 GND
LED + --> STM32 PB3

---

---

## ⚡ Installation and Setup

**Open the Arduino IDE and install the following:**

- **ESP32 Board Manager**: Tools → Board → Boards Manager  
- Install **ESP32 libraries** if not installed.

**Upload the ESP32 Code:**

1. Select **ESP32 Dev Module** in Arduino IDE.  
2. Open `esp32_code.ino` and upload it to your ESP32 board.

**STM32 Configuration:**

1. Use **STM32CubeMX** to configure **USART2** and GPIOs.  
2. Upload the STM32 firmware using **STM32CubeProgrammer**.
## 📐 Usage

1. Connect the ESP32 and STM32 as per the wiring diagram.
2. Upload the ESP32 and STM32 code to their respective boards.
3. Open the Serial Monitor on the ESP32 (baud rate: 115200).
4. Press the button connected to GPIO 13 on the ESP32:
   - **"ON"** message: LED on STM32 will turn ON.
   - **"OFF"** message: LED on STM32 will turn OFF.
5. Debug using STM32 USART1 if needed.

---

## 🛠️ Future Improvements

- Add **bi-directional communication** to get status feedback from the STM32.
- Implement **Wi-Fi integration** with the ESP32 for remote control over the network.
- Add **OTA updates** for the ESP32 to simplify code deployment.

---

## 🤝 Contributing

Feel free to **fork this repository** and submit a **pull request**. If you encounter any issues, open an **issue** on GitHub. Contributions are welcome!

---

## 📄 License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

---

## 🎉 Acknowledgments

Special thanks to the **open-source community** for providing great tools and libraries that make projects like this possible.

---

Enjoy building with **ESP32** and **STM32**! 🎊
