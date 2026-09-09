# Experiment 07: DC Motor Control Using L293D H-Bridge

## 🎯 Aim
To interface a 5V–12V DC motor to the 8051 microcontroller using an L293D Dual H-Bridge motor driver IC, and demonstrate bidirectional rotation (Forward, Reverse, and Coast Stop) with software dead-time delays.

---

## 🧰 Components Required
- AT89S52 / AT89C51 Microcontroller
- L293D Motor Driver IC (16-pin DIP)
- 5V to 12V Small DC Geared Motor
- 1 kΩ Resistors (Port 0 pull-ups)
- Separate DC Power Supply (+12V $V_S$ for motor supply, +5V $V_{SS}$ for logic)

---

## ⚡ Circuit Schematic & Connections

```
      AT89S52 Microcontroller                      L293D Driver IC
    +-------------------------+                 +-------------------+
    |                         |                 |                   |
    |               P0.0 (39) +---------------->| Pin 2 (IN1)       |
    |               P0.1 (38) +---------------->| Pin 7 (IN2)       |
    |                         |                 | Pin 1 (EN1) ── +5V|
    |                         |                 | Pin 3 (OUT1) ──┐  |
    |                         |                 | Pin 6 (OUT2) ──┼──+───[ DC Motor ]
    |                         |                 | Pin 4,5,12,13 ─┴──+─── GND
    |                         |                 | Pin 8 (V_motor)───+─── +12V DC
    |                         |                 | Pin 16 (V_logic)──+─── +5V DC
    +-------------------------+                 +-------------------+
```

---

## 🧠 L293D Truth Table

| Enable 1 | Input 1 (IN1) | Input 2 (IN2) | Motor Output State |
|:---:|:---:|:---:|:---|
| **HIGH** | `1` | `0` | **Clockwise (Forward)** |
| **HIGH** | `0` | `1` | **Counter-Clockwise (Reverse)** |
| **HIGH** | `0` | `0` | **Stop (Coast / High-Z)** |
| **HIGH** | `1` | `1` | **Fast Motor Brake** |
| **LOW** | X | X | **Motor Disabled** |

> [!IMPORTANT]
> **Why Dead-Time is Essential:** When switching from Forward to Reverse, always insert a short stop delay (`IN1=0; IN2=0;`). Switching polarity instantly causes high inductive kickback currents that stress the H-bridge transistors.

---

## 💬 Viva-Voce Questions
1. **Why cannot a DC motor be connected directly to an 8051 I/O pin?**
   *Answer:* 8051 port pins can sink a maximum of ~10–20 mA, while even small DC motors draw 100 mA to 1 A during startup and under mechanical load. Directly connecting a motor will overload and burn the microcontroller pin.
2. **What is the function of internal clamp diodes in the L293D?**
   *Answer:* Motor windings are inductors ($V = L \frac{di}{dt}$). When power is suddenly disconnected, the magnetic field collapses and generates a high-voltage back-EMF spike. The diodes clamp these spikes safely to $V_{CC}$ and Ground, protecting the switching transistors.
3. **What is the difference between Pin 8 ($V_S$) and Pin 16 ($V_{SS}$) on the L293D?**
   *Answer:* Pin 16 ($V_{SS}$) powers the internal logic gates (+5V), while Pin 8 ($V_S$) provides higher voltage/current (+12V to +36V) directly to drive the motors.
