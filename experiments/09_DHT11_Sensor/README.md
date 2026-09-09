# Experiment 09: DHT11 Digital Temperature & Humidity Sensor

## 🎯 Aim
To interface the DHT11 digital environmental sensor with an 8051 microcontroller using a bidirectional single-wire timing protocol, extract 40-bit data frames, calculate parity checksums, and stream real-time temperature (°C) and relative humidity (%RH) readings over serial UART.

---

## 🧰 Components Required
- AT89S52 / AT89C51 Microcontroller
- DHT11 Digital Temperature & Humidity Sensor Module
- 4.7 kΩ to 10 kΩ Pull-up Resistor (between DATA pin and +5V)
- USB-to-UART Serial Module (CP2102 / CH340)
- 11.0592 MHz Crystal Oscillator with 33 pF capacitors

---

## ⚡ Circuit Schematic & Connections

```
     AT89S52 Microcontroller                      DHT11 Sensor
    +-----------------------+                 +-------------------+
    |                       |                 |                   |
    |             P1.0 (1)  +---------------->| Pin 2 (DATA)      |
    |                       |         │       | Pin 1 (VCC) ── +5V|
    |                       |       ┌─┴─┐     | Pin 4 (GND) ── GND|
    |                       |   10k │   │     | Pin 3 (NC)        |
    |                       |       └─┬─┘     +-------------------+
    |                       |         │
    |                       |        +5V
    |            P3.1 (TXD) +----------------> To PC USB-UART RX
    +-----------------------+
```

---

## 🧠 Single-Wire Protocol Timing

```
8051 (Master)                           DHT11 (Slave)
Pulls LOW for >18ms   Releases (20-40µs)  Pulls LOW (80µs)   Pulls HIGH (80µs)  Sends 40 Data Bits
─────┐                   ┌───────────────┐                  ┌───────────────────┐  ┌───
     │                   │               │                  │                   └──┘
     └───────────────────┘               └──────────────────┘
```

### Bit Encoding Scheme:
- Every bit starts with a **50 µs LOW** pulse from DHT11.
- **Logic '0':** High pulse lasting **26–28 µs**.
- **Logic '1':** High pulse lasting **~70 µs**.
- By sampling the pin after ~30–35 µs, the microcontroller directly distinguishes between a `0` and a `1`.

---

## 💬 Viva-Voce Questions
1. **What type of sensing elements are inside the DHT11?**
   *Answer:* A capacitive humidity sensing element and a Negative Temperature Coefficient (NTC) thermistor, read by an internal 8-bit OTP microcontroller.
2. **What is the measurement range and accuracy of DHT11?**
   *Answer:* Humidity range: 20% to 90% RH ($\pm 5\%$ accuracy). Temperature range: 0°C to 50°C ($\pm 2^\circ\text{C}$ accuracy).
3. **Why is a minimum 1 to 2 second delay required between consecutive DHT11 readings?**
   *Answer:* The sensor's thermal mass and capacitive chamber require at least 1–2 seconds to stabilize between sampling cycles. Polling faster causes self-heating errors or failed communications.
