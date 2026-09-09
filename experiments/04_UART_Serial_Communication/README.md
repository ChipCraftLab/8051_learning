# Experiment 04: UART Asynchronous Serial Communication

## 🎯 Aim
To configure the 8051 on-chip UART for 9600 baud rate communication using Timer 1 in Mode 2 (8-bit auto-reload), transmit formatted strings to a PC serial terminal, and implement full-duplex interactive character echo.

---

## 🧰 Components Required
- AT89S52 / AT89C51 Microcontroller
- 11.0592 MHz Crystal Oscillator with 2× 33 pF capacitors
- USB-to-UART TTL Converter Module (CP2102 / FTDI / CH340) OR MAX232 Level Shifter
- PC with Serial Terminal Software (PuTTY / Tera Term / Arduino Serial Monitor)

---

## ⚡ Circuit Schematic & Connections

```
     AT89S52 Microcontroller           USB-UART TTL Converter
    +-----------------------+          +---------------------+
    |                       |          |                     |
    |          P3.0 (RXD) 10|<---------| TXD                 |
    |          P3.1 (TXD) 11|--------->| RXD                 |
    |                    GND|----------| GND                 |
    +-----------------------+          +---------------------+
```

> [!NOTE]
> When connecting the 8051 to a USB-to-UART converter, remember that **TX connects to RX** and **RX connects to TX**, sharing a common Ground.

---

## 🧠 Baud Rate Derivation (11.0592 MHz)

1. Crystal Frequency: $f_{\text{osc}} = 11.0592\text{ MHz}$
2. Machine Cycle: $f_{\text{machine}} = \frac{11.0592\text{ MHz}}{12} = 921.6\text{ kHz}$
3. UART Prescaler: In Mode 1 with $\text{SMOD}=0$, the UART clock is $\frac{921.6\text{ kHz}}{32} = 28,800\text{ Hz}$.
4. Timer 1 Count for 9600 Baud:
   $$N = \frac{28,800}{9600} = 3$$
5. Reload Value:
   $$\text{TH1} = 256 - 3 = 253 = \text{0xFD}$$

---

## 🚀 Serial Terminal Configuration
- **Baud Rate:** 9600
- **Data Bits:** 8
- **Stop Bits:** 1
- **Parity:** None
- **Flow Control:** None

---

## 💬 Viva-Voce Questions
1. **Why is Timer 1 used in Mode 2 for serial baud rates rather than Mode 1?**
   *Answer:* Mode 2 is an 8-bit auto-reload mode. Once TH1 is loaded, the hardware automatically reloads TL1 upon overflow without generating an interrupt or requiring software reloading, preventing timing jitter.
2. **What is the purpose of SBUF register?**
   *Answer:* SBUF is the serial buffer register. It physically consists of two separate registers: a write-only transmit buffer and a read-only receive buffer.
3. **What happens to the TI and RI flags in SCON after a byte is sent or received?**
   *Answer:* They are set automatically by hardware, but they **must be cleared by software** (`TI = 0; RI = 0;`), otherwise the program will halt or falsely trigger interrupts.
