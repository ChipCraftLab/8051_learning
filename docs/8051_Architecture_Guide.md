# 8051 Microcontroller Architecture & Reference Guide

## 1. Overview
The Intel 8051 (and derivatives like Atmel AT89C51/AT89S52) is an 8-bit CISC Harvard-architecture microcontroller. It provides separate physical memory spaces for program code (ROM) and runtime data (RAM).

```
+-------------------------------------------------------------+
|                      8051 Core CPU                          |
|  +--------------+  +--------------+  +-------------------+  |
|  | Accumulator  |  |  B Register  |  | Program Status    |  |
|  |     (A)      |  |     (B)      |  |   Word (PSW)      |  |
|  +--------------+  +--------------+  +-------------------+  |
|  +--------------------+   +------------------------------+  |
|  | Data Pointer (DPTR)|   |     Program Counter (PC)     |  |
|  |   DPH   |   DPL    |   |           16-Bit             |  |
|  +--------------------+   +------------------------------+  |
+-------------------------------------------------------------+
               |                            |
  [ 4 KB / 8 KB Flash ROM ]     [ 128 / 256 Bytes Internal RAM ]
        (MOVC @A+DPTR)                    (MOV @Ri, direct)
```

---

## 2. Key Specifications

| Parameter | 8051 Standard | AT89S52 Extension |
|:---|:---|:---|
| **Data Bus Width** | 8 bits | 8 bits |
| **Address Bus Width** | 16 bits (accesses up to 64 KB) | 16 bits |
| **Internal On-Chip ROM** | 4 KB (EPROM/ROM) | 8 KB In-System Programmable (ISP) Flash |
| **Internal RAM** | 128 bytes | 256 bytes |
| **16-Bit Timers/Counters** | 2 (Timer 0, Timer 1) | 3 (Timer 0, Timer 1, Timer 2) |
| **Parallel I/O Ports** | 4 (P0, P1, P2, P3: 32 pins) | 4 (32 pins) |
| **Full Duplex UART** | 1 Channel | 1 Channel |
| **Interrupt Sources** | 5 vectors (2 external, 3 internal)| 8 vectors |

---

## 3. Internal RAM Memory Organization (128 Bytes)

The lower 128 bytes of internal RAM (`0x00` to `0x7F`) are divided into three distinct operational regions:

```
Address Range   Usage
+-------------+-------------------------------------------------------------+
| 0x30 - 0x7F | General Purpose Scratchpad RAM (80 bytes)                   |
|             | Used for local variables and user stack operations.         |
+-------------+-------------------------------------------------------------+
| 0x20 - 0x2F | Bit-Addressable RAM (16 bytes = 128 individual bits)        |
|             | Bit addresses: 0x00 to 0x7F. Accessed via SETB, CLR, JB.    |
+-------------+-------------------------------------------------------------+
| 0x18 - 0x1F | Register Bank 3 (R0 - R7)                                   |
| 0x10 - 0x17 | Register Bank 2 (R0 - R7)                                   |
| 0x08 - 0x0F | Register Bank 1 (R0 - R7)                                   |
| 0x00 - 0x07 | Register Bank 0 (R0 - R7) [Default at power-on reset]       |
+-------------+-------------------------------------------------------------+
```

---

## 4. Special Function Registers (SFRs: 0x80 - 0xFF)

Only registers with addresses divisible by 8 (e.g., `0x80`, `0x88`, `0x90`, `0x98`, `0xA0`, `0xA8`, `0xB0`, `0xB8`, `0xD0`, `0xE0`, `0xF0`) are **bit-addressable**.

| SFR Name | Hex Address | Bit-Addressable? | Description |
|:---|:---:|:---:|:---|
| **ACC (A)** | `0xE0` | Yes | Accumulator (arithmetic and logic results) |
| **B** | `0xF0` | Yes | Auxiliary register for multiplication and division (`MUL AB`, `DIV AB`) |
| **PSW** | `0xD0` | Yes | Program Status Word (flags: CY, AC, F0, RS1, RS0, OV, -, P) |
| **SP** | `0x81` | No | Stack Pointer (initialized to `0x07`, points to top of stack) |
| **DPL / DPH** | `0x82` / `0x83` | No | Data Pointer Low and High bytes (form 16-bit DPTR) |
| **P0, P1, P2, P3** | `0x80`, `0x90`, `0xA0`, `0xB0` | Yes | Parallel I/O Ports 0, 1, 2, and 3 |
| **IP** | `0xB8` | Yes | Interrupt Priority register |
| **IE** | `0xA8` | Yes | Interrupt Enable register (`EA` bit controls global interrupt) |
| **TMOD** | `0x89` | No | Timer/Counter Mode register (Timer 0 & Timer 1) |
| **TCON** | `0x88` | Yes | Timer Control register (Run and Overflow flags: TR0, TF0, TR1, TF1) |
| **TH0 / TL0** | `0x8C` / `0x8A` | No | Timer 0 High and Low byte counters |
| **TH1 / TL1** | `0x8D` / `0x8B` | No | Timer 1 High and Low byte counters |
| **SCON** | `0x98` | Yes | Serial Control register (SM0, SM1, SM2, REN, TB8, RB8, TI, RI) |
| **SBUF** | `0x99` | No | Serial Data Buffer (separate physical Tx and Rx registers) |
| **PCON** | `0x87` | No | Power Control register (contains SMOD baud rate doubler bit) |

---

## 5. Clock and Machine Cycle Calculations

In the standard 8051 core:
- **1 Machine Cycle = 12 Oscillator Clock Cycles**
- For a standard **$11.0592\text{ MHz}$** crystal:
  $$\text{Machine Cycle Frequency } f_{\text{machine}} = \frac{11.0592\text{ MHz}}{12} = 921.6\text{ kHz}$$
  $$\text{Machine Cycle Period } T_{\text{machine}} = \frac{1}{921.6\text{ kHz}} \approx 1.085\ \mu\text{s}$$

- For a **$12.000\text{ MHz}$** crystal:
  $$\text{Machine Cycle Period } = \frac{12}{12\text{ MHz}} = 1.000\ \mu\text{s}$$

---

## 6. UART Baud Rate Generation (Timer 1 Mode 2)

Timer 1 is placed in **Mode 2 (8-bit auto-reload)** to clock the serial port:
$$\text{Baud Rate} = \frac{2^{\text{SMOD}}}{32} \times \frac{f_{\text{osc}}}{12 \times (256 - \text{TH1})}$$

When $\text{SMOD} = 0$ and $f_{\text{osc}} = 11.0592\text{ MHz}$:
$$\text{TH1} = 256 - \frac{28800}{\text{Baud Rate}}$$

### Baud Rate Reload Table ($f_{\text{osc}} = 11.0592\text{ MHz}$):

| Desired Baud Rate | TH1 (Decimal) | TH1 (Hex) | Percent Error |
|:---:|:---:|:---:|:---:|
| **9600** | $256 - 3 = 253$ | `0xFD` | **0.0%** |
| **4800** | $256 - 6 = 250$ | `0xFA` | **0.0%** |
| **2400** | $256 - 12 = 244$ | `0xF4` | **0.0%** |
| **1200** | $256 - 24 = 232$ | `0xE8` | **0.0%** |

*(Notice why 11.0592 MHz is universally chosen for 8051 over 12 MHz: it yields exact integer reload values with 0% timing error).*
