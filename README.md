# 8051 Microcontroller Laboratory & Learning Package ⚡

[![8051 Architecture](https://img.shields.io/badge/Architecture-8051%20%2F%20AT89S52-blue.svg)](docs/8051_Architecture_Guide.md)
[![Toolchain](https://img.shields.io/badge/IDE-Keil%20%C2%B5Vision-orange.svg)](docs/Keil_Proteus_Setup_Guide.md)
[![Simulation](https://img.shields.io/badge/Simulation-Proteus%20VSM-green.svg)](docs/Keil_Proteus_Setup_Guide.md)
[![Language](https://img.shields.io/badge/Language-Embedded%20C%20(C51)-yellow.svg)](experiments/)
[![License: MIT](https://img.shields.io/badge/License-MIT-purple.svg)](LICENSE)

A standardized, complete, and production-ready laboratory package designed for **Undergraduate (UG) Engineering Students** (ECE, EEE, CSE, Mechatronics, Instrumentation). 

This repository contains ready-to-run Embedded C source code, circuit connection mappings, theoretical principles, precompiled Intel HEX files, interactive learning apps, and a 50+ question viva-voce bank for university lab examinations.

---

## 📑 Table of Contents

- [Curriculum & Learning Objectives](#-curriculum--learning-objectives)
- [Repository Structure](#-repository-structure)
- [List of Laboratory Experiments](#-list-of-laboratory-experiments)
- [Hardware & Software Prerequisites](#-hardware--software-prerequisites)
- [Quick Start Guide](#-quick-start-guide)
- [Interactive Web Tutorial](#-interactive-web-tutorial)
- [Documentation & Exam Preparation](#-documentation--exam-preparation)
- [License & Contributions](#-license--contributions)

---

## 🎯 Curriculum & Learning Objectives

This lab package aligns with standard undergraduate university syllabi (AICTE / IEEE / ABET) for **Microprocessors and Microcontrollers Laboratory**:

1. **Digital I/O & Port Logic:** Understand quasi-bidirectional ports, open-drain Port 0 pull-ups, and read-modify-write instructions.
2. **Human-Machine Interfaces:** Control single-digit and multiplexed 7-segment displays, and alphanumeric 16×2 LCDs.
3. **Serial Communication:** Configure on-chip UART, calculate baud rates with Timer 1 Mode 2, and establish PC-microcontroller communication.
4. **Mixed-Signal Interfacing:** Interface SAR Analog-to-Digital Converters (ADC0809) and R-2R Digital-to-Analog Converters (DAC0808).
5. **Actuator & Motor Control:** Implement H-Bridge control for DC motors and step sequencing for unipolar stepper motors.
6. **Digital Sensor Protocols:** Decode single-wire proprietary timing protocols for environmental sensors (DHT11).

---

## 📂 Repository Structure

```
8051_learning/
├── README.md                           # Master laboratory syllabus and guide
├── LICENSE                             # MIT Open Source License
├── docs/                               # Theory guides, pinouts, and exam prep
│   ├── 8051_Architecture_Guide.md     # Architecture, memory map, SFRs, interrupts
│   ├── Keil_Proteus_Setup_Guide.md     # Keil compilation and Proteus simulation guide
│   ├── Pinout_Quick_Reference.md       # Pinout reference and circuit rules
│   └── Viva_Voce_Question_Bank.md      # 50+ solved viva and interview questions
├── tutorial-web-app/                   # Interactive 16-lesson browser study app
│   ├── index.html
│   ├── lesson.html
│   ├── lessons.js
│   └── styles.css
└── experiments/                        # Hands-on lab experiments
    ├── Exp-01-LED-Patterns/
    ├── Exp-02-Seven-Segment-Display/
    ├── Exp-03-LCD1602-Character-Display/
    ├── Exp-04-UART-Serial-Communication/
    ├── Exp-05-ADC0809-Analog-Interfacing/
    ├── Exp-06-DAC0808-Waveform-Generator/
    ├── Exp-07-DC-Motor-Control/
    ├── Exp-08-Stepper-Motor-Control/
    └── Exp-09-DHT11-Sensor/
```

---

## 🔬 List of Laboratory Experiments

| Exp # | Experiment Title | Peripheral / IC | Key Concepts Demonstrated | Direct Link |
|:---:|:---|:---|:---|:---:|
| **01** | **LED Pattern & Bit Manipulation** | Port 0 LEDs | Blinking, chaser, odd/even, bitwise shifts (`<<`, `>>`) | [Exp 01](experiments/Exp-01-LED-Patterns/) |
| **02** | **Seven Segment Displays** | Common Cathode 7-Seg | Single-digit decoding & 4-digit multiplexed POV counter | [Exp 02](experiments/Exp-02-Seven-Segment-Display/) |
| **03** | **16×2 Alphanumeric LCD** | HD44780 Controller | 8-bit command/data initialization, string routines, shifting | [Exp 03](experiments/Exp-03-LCD1602-Character-Display/) |
| **04** | **UART Serial Communication** | On-Chip UART (Rx/Tx) | Timer 1 Mode 2, 9600 baud generation, string echo loopback | [Exp 04](experiments/Exp-04-UART-Serial-Communication/) |
| **05** | **Analog-to-Digital Converter** | ADC0809 (8-Channel SAR) | Clock generation, SOC/EOC handshaking, LCD readout | [Exp 05](experiments/Exp-05-ADC0809-Analog-Interfacing/) |
| **06** | **DAC Waveform Generation** | DAC0808 / MC1408 | Ramp, triangular, square, and synthesized sine waves | [Exp 06](experiments/Exp-06-DAC0808-Waveform-Generator/) |
| **07** | **DC Motor Speed & Direction** | L293D Dual H-Bridge | Direction reversal, dead-time switching, relay/motor drivers | [Exp 07](experiments/Exp-07-DC-Motor-Control/) |
| **08** | **Stepper Motor Step Sequencing** | ULN2003 / 4-Phase Stepper | Wave drive, full-step sequence, clockwise/counter-clockwise | [Exp 08](experiments/Exp-08-Stepper-Motor-Control/) |
| **09** | **DHT11 Temperature & Humidity** | DHT11 Digital Sensor | Microsecond 1-wire timing, start signal, parity checksum | [Exp 09](experiments/Exp-09-DHT11-Sensor/) |

---

## 🛠 Hardware & Software Prerequisites

### Recommended Hardware
- **Microcontroller:** AT89S52 or AT89C51 (40-Pin DIP)
- **Clock Crystal:** 11.0592 MHz (essential for standard UART baud rates without fractional error)
- **Capacitors:** 2× 33 pF ceramic (crystal load), 1× 10 µF electrolytic (power-on reset)
- **Resistors:** 1× 10 kΩ (reset pull-down), 1× 1 kΩ × 8 SIL pull-up resistor network (for Port 0)
- **ISP Programmer:** USBASP (with ProgISP / avrdude) or 8051 Development Board with USB-UART

### Recommended Software
- **Compiler / IDE:** [Keil µVision C51](https://www.keil.com/c51/) (Version 4 or 5)
- **Circuit Simulator:** [Labcenter Proteus VSM](https://www.labcenter.com/)
- **Terminal Emulator:** PuTTY, Tera Term, or Arduino Serial Monitor (for 9600 baud experiments)

---

## 🚀 Quick Start Guide

### 1. Build an Experiment in Keil µVision
1. Open Keil µVision and select **Project > New µVision Project**.
2. Select target chip: **Microchip/Atmel > AT89S52** (or AT89C51). When prompted to copy `STARTUP.A51`, click **Yes**.
3. Right-click **Source Group 1**, select **Add Existing Files**, and choose `main.c` from the desired experiment folder.
4. Click **Project > Options for Target 'Target 1'** (`Alt + F7`):
   - In the **Target** tab, set **Xtal (MHz):** `11.0592`.
   - In the **Output** tab, check **Create HEX File**.
5. Click **Project > Build Target** (`F7`).
6. The compiled `.hex` file will be generated in your project folder.

### 2. Simulate in Proteus VSM
1. Place an `AT89C51` or `AT89S52` component on the Proteus schematic.
2. Double-click the microcontroller, set **Clock Frequency:** `11.0592MHz`.
3. In **Program File**, click the folder icon and select the `.hex` file.
4. Press the **Play** button at the bottom left to run the simulation.

---

## 💻 Interactive Web Tutorial

This package includes a standalone, zero-dependency 16-lesson interactive web course. 

To use it:
1. Open [`tutorial-web-app/index.html`](tutorial-web-app/index.html) in any modern web browser.
2. Review architecture topics, addressing modes, instruction sets, and take self-assessment quizzes.

---

## 📚 Documentation & Exam Preparation

- [8051 Architecture & Memory Map](docs/8051_Architecture_Guide.md)
- [Pinout & Hardware Interface Rules](docs/Pinout_Quick_Reference.md)
- [Keil & Proteus Setup Walkthrough](docs/Keil_Proteus_Setup_Guide.md)
- [50+ Solved Viva-Voce Questions](docs/Viva_Voce_Question_Bank.md)

---

## 📜 License & Citation

This repository is distributed under the **[MIT License](LICENSE)**. 

Maintained by **[ChipCraftLab](https://github.com/ChipCraftLab)**. Free for educational use in university classrooms, student laboratories, and self-study.
[![Buy Me A Coffee](https://img.buymeacoffee.com/button-api/?text=Buy%20me%20a%20coffee&emoji=☕&slug=chipcraftlab&button_colour=FFDD00&font_colour=000000&font_family=Cookie&outline_colour=000000&coffee_colour=ffffff)](https://www.buymeacoffee.com/chipcraftlab)
