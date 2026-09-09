# Experiment 01: LED Interfacing & Bit Manipulation Patterns

## 🎯 Aim
To interface an array of 8 LEDs to Port 0 of the 8051 microcontroller and generate dynamic visual patterns (nibble flashing, alternating odd/even, chaser shift, and fill-rotation) using Embedded C bitwise operations.

---

## 🧰 Components Required
| S.No | Component | Specification | Quantity |
|:---:|:---|:---|:---:|
| 1 | Microcontroller | AT89S52 / AT89C51 | 1 |
| 2 | Crystal Oscillator | 11.0592 MHz | 1 |
| 3 | Ceramic Capacitors | 33 pF | 2 |
| 4 | Electrolytic Capacitor | 10 µF (Reset circuit) | 1 |
| 5 | Resistors | 10 kΩ (Reset pull-down) | 1 |
| 6 | Resistor Network (SIL) | 1 kΩ × 8 (Port 0 pull-ups) | 1 |
| 7 | LEDs | 5mm Red / Green | 8 |
| 8 | Current Limiting Resistors | 330 Ω | 8 |

---

## ⚡ Circuit Schematic & Pin Connections

```
     AT89S52 Microcontroller
    +-----------------------+
    |                       |
    |          P0.0 (Pin 39)+----[ 330R ]----|>|----+ (LED 0)
    |          P0.1 (Pin 38)+----[ 330R ]----|>|----+ (LED 1)
    |          P0.2 (Pin 37)+----[ 330R ]----|>|----+ (LED 2)
    |          P0.3 (Pin 36)+----[ 330R ]----|>|----+ (LED 3)
    |          P0.4 (Pin 35)+----[ 330R ]----|>|----+ (LED 4)
    |          P0.5 (Pin 34)+----[ 330R ]----|>|----+ (LED 5)
    |          P0.6 (Pin 33)+----[ 330R ]----|>|----+ (LED 6)
    |          P0.7 (Pin 32)+----[ 330R ]----|>|----+ (LED 7)
    |                       |                       |
    +-----------------------+                      === GND
```

> [!IMPORTANT]
> **Port 0 Pull-Up Requirement:** Because Port 0 has open-drain outputs, a 1 kΩ – 10 kΩ pull-up resistor network **must** be connected between Port 0 pins and $+5\text{V}$ (VCC) if operating in active-high configuration.

---

## 🧠 Theory & Logic
- **Bitwise Shifts:**
  - `LED = LED << 1;` shifts all bits one position left, moving the illuminated LED from pin `P0.0` towards `P0.7`.
  - `LED = LED >> 1;` shifts all bits right, moving the illuminated LED from `P0.7` towards `P0.0`.
- **Masking & Combining:**
  - `(LED << 1) | 0x01` shifts bits left while maintaining a logic `1` at LSB, creating a fill bar.

---

## 🚀 How to Build & Simulate
1. Open the project in Keil µVision using `AT89S52` target.
2. Compile and generate `Exp01_LED.hex`.
3. In Proteus, load `Exp01_LED.hex` into the microcontroller.
4. Press Run to observe the sequential LED patterns.

---

## 💬 Viva-Voce Questions
1. **Why do we need external pull-up resistors for Port 0?**
   *Answer:* Port 0 is an open-drain bidirectional port and has no internal pull-up transistors.
2. **What current limiting resistor is recommended for LEDs driven by 5V?**
   *Answer:* 220 Ω to 330 Ω (limiting forward current to ~10–15 mA).
3. **What is the difference between arithmetic shift and logical shift in C?**
   *Answer:* For `unsigned char`, `>>` performs a logical shift, filling MSB with zero. For signed types, it fills with the sign bit.
