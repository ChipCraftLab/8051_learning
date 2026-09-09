# Experiment 08: Stepper Motor Interfacing & Step Sequencing

## 🎯 Aim
To interface a 4-phase unipolar stepper motor to Port 0 of the 8051 microcontroller using a ULN2003 Darlington transistor array driver, and demonstrate precise angular rotation in both Clockwise (CW) and Counter-Clockwise (CCW) directions using 4-step wave excitation.

---

## 🧰 Components Required
- AT89S52 / AT89C51 Microcontroller
- 4-Phase Unipolar Stepper Motor (e.g. 5V 28BYJ-48 or 12V motor)
- ULN2003 Darlington Transistor Driver IC (or ULN2003 breakout module)
- External +5V to +12V DC power source for motor coils
- 1 kΩ Resistor Pack (Port 0 pull-ups)

---

## ⚡ Circuit Schematic & Connections

```
      AT89S52 Microcontroller                      ULN2003 Driver IC
    +-------------------------+                 +-------------------+
    |                         |                 |                   |
    |               P0.0 (39) +---------------->| Pin 1 (1B) -> 1C (16) -- Coil A (Blue)
    |               P0.1 (38) +---------------->| Pin 2 (2B) -> 2C (15) -- Coil B (Pink)
    |               P0.2 (37) +---------------->| Pin 3 (3B) -> 3C (14) -- Coil C (Yellow)
    |               P0.3 (36) +---------------->| Pin 4 (4B) -> 4C (13) -- Coil D (Orange)
    |                         |                 | Pin 8 (GND) ── GND
    |                         |                 | Pin 9 (COM) ── +5V/12V (Flyback clamp)
    +-------------------------+                 +-------------------+
                                                          |
                                                    Motor Common Wire (Red) ── +5V/12V
```

---

## 🧠 Stepper Excitation Table (Wave Drive)

| Step # | Coil A (`P0.0`) | Coil B (`P0.1`) | Coil C (`P0.2`) | Coil D (`P0.3`) | Hex Value |
|:---:|:---:|:---:|:---:|:---:|:---:|
| **1** | `1` | `0` | `0` | `0` | `0x01` |
| **2** | `0` | `1` | `0` | `0` | `0x02` |
| **3** | `0` | `0` | `1` | `0` | `0x04` |
| **4** | `0` | `0` | `0` | `1` | `0x08` |

- **Clockwise (CW) Direction:** Step 1 $\to$ Step 2 $\to$ Step 3 $\to$ Step 4
- **Counter-Clockwise (CCW) Direction:** Step 4 $\to$ Step 3 $\to$ Step 2 $\to$ Step 1

---

## 💬 Viva-Voce Questions
1. **What is the Step Angle of a stepper motor?**
   *Answer:* The angle through which the motor shaft rotates per single electrical step pulse. Formula: $\text{Step Angle} = \frac{360^\circ}{\text{Number of Steps per Revolution}}$. For example, 200 steps/rev yields a $1.8^\circ$ step angle.
2. **What is the difference between Wave Drive, Full-Step, and Half-Step drive modes?**
   *Answer:* Wave Drive energizes one phase at a time (least torque, lowest current). Full-Step energizes two phases simultaneously (maximum torque). Half-Step alternates between one and two phases, doubling the angular resolution.
3. **What is the purpose of the ULN2003 IC?**
   *Answer:* The ULN2003 is an array of 7 high-voltage, high-current NPN Darlington pairs capable of sinking up to 500 mA per channel, with built-in inductive suppression clamp diodes connected to the COM pin.
