# 8051 Pinout & Hardware Design Reference

## 1. 40-Pin DIP Pinout Diagram

```
                 +-----------v-----------+
        (P1.0)   1 | P1.0           VCC | 40  (+5V Power)
        (P1.1)   2 | P1.1      (AD0) P0.0 | 39  (Open-Drain Bus)
        (P1.2)   3 | P1.2      (AD1) P0.1 | 38
        (P1.3)   4 | P1.3      (AD2) P0.2 | 37
        (P1.4)   5 | P1.4      (AD3) P0.3 | 36
  (MOSI/P1.5)   6 | P1.5      (AD4) P0.4 | 35
  (MISO/P1.6)   7 | P1.6      (AD5) P0.5 | 34
   (SCK/P1.7)   8 | P1.7      (AD6) P0.6 | 33
 (Active High)   9 | RST        (AD7) P0.7 | 32
   (RXD/P3.0)  10 | P3.0         EA/VPP | 31  (Tie to VCC for internal ROM)
   (TXD/P3.1)  11 | P3.1           ALE  | 30  (Address Latch Enable)
  (INT0/P3.2)  12 | P3.2           PSEN | 29  (Program Strobe Enable)
  (INT1/P3.3)  13 | P3.3       (A15) P2.7 | 28  (High Address Byte)
    (T0/P3.4)  14 | P3.4       (A14) P2.6 | 27
    (T1/P3.5)  15 | P3.5       (A13) P2.5 | 26
    (WR/P3.6)  16 | P3.6       (A12) P2.4 | 25
    (RD/P3.7)  17 | P3.7       (A11) P2.3 | 24
     (Crystal)  18 | XTAL2      (A10) P2.2 | 23
     (Crystal)  19 | XTAL1       (A9) P2.1 | 22
      (Ground)  20 | GND         (A8) P2.0 | 21
                 +-----------------------+
```

---

## 2. Port Hardware Differences & Rules

### Port 0 (Pins 32 - 39)
- **Circuit Design:** True **Open-Drain Bidirectional Port** without internal pull-up resistors.
- **Rule:** When using Port 0 as general-purpose I/O, you **MUST attach an external 4.7 kΩ – 10 kΩ pull-up resistor network** (e.g., 9-pin SIL resistor pack) connected to $+5\text{V}$. Without pull-ups, logic high output will float in high-impedance state!
- **Dual Function:** Serves as multiplexed low-order address byte ($A_0 - A_7$) and 8-bit data bus ($D_0 - D_7$) during external memory access.

### Port 1 (Pins 1 - 8)
- **Circuit Design:** Quasi-bidirectional with internal pull-up resistors.
- **Usage:** Purely general-purpose I/O.
- **Note for AT89S52:** Pins P1.5 (MOSI), P1.6 (MISO), and P1.7 (SCK) are used for SPI In-System Programming (ISP).

### Port 2 (Pins 21 - 28)
- **Circuit Design:** Quasi-bidirectional with internal pull-up resistors.
- **Dual Function:** Outputs high-order address byte ($A_8 - A_{15}$) during external memory access.

### Port 3 (Pins 10 - 17)
- **Circuit Design:** Quasi-bidirectional with internal pull-up resistors.
- **Alternate Multifunction Pins:**
  - `P3.0` (**RXD**): Serial data input
  - `P3.1` (**TXD**): Serial data output
  - `P3.2` (**INT0**): External hardware interrupt 0 (Active low)
  - `P3.3` (**INT1**): External hardware interrupt 1 (Active low)
  - `P3.4` (**T0**): Timer 0 external event counter input
  - `P3.5` (**T1**): Timer 1 external event counter input
  - `P3.6` (**WR**): External data memory write strobe (Active low)
  - `P3.7` (**RD**): External data memory read strobe (Active low)

---

## 3. Essential Minimum System Circuit

To make an AT89S52 or AT89C51 boot reliably on a breadboard or PCB, the following 4 connections are strictly required:

```
        +5V ────────────┬───────────────────────────── Pin 40 (VCC)
                        │
                        ├───────────────────────────── Pin 31 (EA/VPP)  [CRITICAL: Must be HIGH]
                        │
                      ┌─┴─┐
                 10µF │ + │
             Electr. └──┬──┘
                        ├───────────────────────────── Pin 9 (RST)
                        │
                      ┌─┴─┐
                  10k │   │ Resistor
                      └─┬─┘
                        │
        GND ────────────┴───────────────────────────── Pin 20 (GND)
                        │
               ┌────────┴────────┐
               │                 │
             ┌─┴─┐             ┌─┴─┐
        33pF │   │        33pF │   │
             └─┬─┘             └─┬─┘
               │                 │
     Pin 19 ───┴───[ 11.0592MHz ]───┴─── Pin 18
     (XTAL1)          Crystal           (XTAL2)
```

> [!WARNING]
> **Common Student Mistake:** If **Pin 31 ($\overline{\text{EA}}$)** is left floating or tied to GND, the 8051 will ignore on-chip Flash ROM and attempt to fetch program code from external memory, causing the CPU to hang!
