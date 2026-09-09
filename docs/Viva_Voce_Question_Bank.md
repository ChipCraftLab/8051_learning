# 8051 Microcontroller Laboratory: Master Viva-Voce Question Bank

A comprehensive collection of 50+ high-frequency oral exam (viva-voce) questions and technical answers for undergraduate students.

---

## Category 1: 8051 Core Architecture & Features

#### Q1: What is the difference between a microprocessor and a microcontroller?
**Ans:** A microprocessor (e.g., 8085, 8086) contains only CPU blocks (ALU, registers) and requires external RAM, ROM, timers, and I/O chips. A microcontroller (e.g., 8051) integrates the CPU, RAM, ROM, timers/counters, serial port, and I/O ports onto a single IC package (System on a Chip).

#### Q2: What type of architecture does the 8051 employ?
**Ans:** Harvard architecture. It maintains separate physical address spaces and instruction buses for Program Memory (ROM) and Data Memory (RAM).

#### Q3: Why is 11.0592 MHz universally used as the crystal frequency for the 8051?
**Ans:** The standard 8051 divides the crystal frequency by 12 to generate machine cycles ($921.6\text{ kHz}$), and divides it further by 32 in Timer 1 Mode 2 to generate UART clocks. 11.0592 MHz divides cleanly without fractional remainder into standard baud rates (9600, 4800, 2400, 1200 baud), yielding exactly 0% timing error. A 12 MHz crystal creates ~7% baud rate error, resulting in corrupted serial data.

#### Q4: What is a machine cycle in the 8051?
**Ans:** One machine cycle consists of 12 oscillator clock periods (or 6 states, $S_1$ to $S_6$). For an 11.0592 MHz crystal, one machine cycle takes approximately $1.085\ \mu\text{s}$. For a 12 MHz crystal, it takes exactly $1.0\ \mu\text{s}$.

#### Q5: What is the function of the $\overline{\text{EA}}$ pin (Pin 31)?
**Ans:** $\overline{\text{EA}}$ stands for External Access. When tied to $+5\text{V}$ (logic high), the 8051 executes instructions from internal on-chip Flash ROM ($0x0000$ to $0x0FFF$ or $0x1FFF$) before fetching from external ROM. When tied to GND (logic low), the 8051 bypasses internal ROM and fetches all instructions exclusively from external ROM.

#### Q6: What is the function of the ALE pin (Pin 30)?
**Ans:** Address Latch Enable. Port 0 multiplexes low-order address lines ($A_0-A_7$) and data lines ($D_0-D_7$). ALE provides a pulse to an external latch (like 74HC373) to demultiplex and hold the address during memory read/write cycles.

#### Q7: What is the function of the $\overline{\text{PSEN}}$ pin (Pin 29)?
**Ans:** Program Store Enable. It is an active-low read strobe signal used exclusively to fetch code bytes from external Program ROM. It connects to the $\overline{\text{OE}}$ pin of the external EPROM/Flash.

#### Q8: What happens when the 8051 is reset?
**Ans:** The Program Counter (PC) is cleared to `0x0000`, the Stack Pointer (SP) is initialized to `0x07`, all I/O ports are initialized to `0xFF` (logic high), and Special Function Registers are reset to their default states.

---

## Category 2: Memory Organization & Registers

#### Q9: Describe the internal RAM structure of the 8051.
**Ans:** The lower 128 bytes of internal RAM are divided into:
1. Four Register Banks: `0x00 - 0x1F` (32 bytes, Banks 0 to 3, each having R0-R7).
2. Bit-Addressable RAM: `0x20 - 0x2F` (16 bytes = 128 individually addressable bits).
3. General Purpose Scratchpad RAM: `0x30 - 0x7F` (80 bytes).

#### Q10: How do you switch between Register Banks?
**Ans:** By modifying the RS1 and RS0 bits (Bits 4 and 3) in the Program Status Word (PSW) register:
- Bank 0: RS1 = 0, RS0 = 0 (`0x00 - 0x07`) [Default]
- Bank 1: RS1 = 0, RS0 = 1 (`0x08 - 0x0F`)
- Bank 2: RS1 = 1, RS0 = 0 (`0x10 - 0x17`)
- Bank 3: RS1 = 1, RS0 = 1 (`0x18 - 0x1F`)

#### Q11: What is the default location of the stack in the 8051?
**Ans:** At power-on reset, the Stack Pointer (SP) register holds `0x07`. When a `PUSH` or `CALL` instruction executes, SP is pre-incremented, so the first pushed byte is saved at RAM address `0x08` (which belongs to Register Bank 1).

#### Q12: What is the size of the DPTR register and what is its role?
**Ans:** DPTR (Data Pointer) is a 16-bit register composed of two 8-bit SFRs: DPH (`0x83`) and DPL (`0x82`). It is used to point to external data memory addresses (`MOVX @DPTR`) and lookup table addresses in code memory (`MOVC A, @A+DPTR`).

#### Q13: What flags are present in the Program Status Word (PSW)?
**Ans:** 
- `CY` (Bit 7): Carry flag
- `AC` (Bit 6): Auxiliary carry (for BCD operations)
- `F0` (Bit 5): User-defined general-purpose flag 0
- `RS1, RS0` (Bits 4, 3): Register bank select bits
- `OV` (Bit 2): Two's complement signed arithmetic overflow flag
- `P` (Bit 0): Parity flag (set to 1 if Accumulator contains an odd number of 1s)

---

## Category 3: I/O Ports & Hardware Interfacing

#### Q14: Why does Port 0 require external pull-up resistors?
**Ans:** Port 0 is designed as an open-drain bidirectional port and lacks internal pull-up transistors. When configured as an output port, it can sink current (pull low) but cannot source current (pull high) without external 4.7 kΩ to 10 kΩ pull-up resistors connected to $+5\text{V}$.

#### Q15: Why must an 8051 port pin be written with `1` before reading it as an input?
**Ans:** The 8051 ports use quasi-bidirectional buffers. Writing `0` turns ON the internal pull-down FET, grounding the pin. Writing `1` turns OFF the pull-down FET and allows the weak internal pull-up (or external pull-up) to hold the line high, letting an external sensor or switch freely drive the line low or high.

#### Q16: What is a "Read-Modify-Write" instruction?
**Ans:** Instructions that read the state of the port latch rather than the actual physical voltage on the external pin, modify the value, and write it back. Examples include `ANL P1, A`, `ORL P1, A`, `CPL P1.0`, `DJNZ P1, label`, and `JBC bit, label`. This prevents a pin externally held low from accidentally overwriting other bits in the port latch.

---

## Category 4: Timers & Counters

#### Q17: What is the difference between Timer mode and Counter mode in 8051?
**Ans:** In Timer mode ($C/\overline{T} = 0$), the register increments once every machine cycle ($f_{\text{osc}} / 12$), serving as a time reference. In Counter mode ($C/\overline{T} = 1$), the register increments on negative (1-to-0) transitions on external pins T0 (P3.4) or T1 (P3.5).

#### Q18: Explain the 4 operational modes of Timer 0 and Timer 1.
**Ans:**
- **Mode 0:** 13-bit timer/counter (compatible with legacy 8048).
- **Mode 1:** 16-bit timer/counter (counts from `0x0000` to `0xFFFF`, overflows at 65,536).
- **Mode 2:** 8-bit auto-reload timer (counts from TH value up to `0xFF`; on overflow, TF is set and TL is automatically reloaded from TH).
- **Mode 3:** Split timer mode (Timer 0 splits into two independent 8-bit timers TL0 and TH0).

#### Q19: Which timer mode is used for UART baud rate generation and why?
**Ans:** Timer 1 in **Mode 2 (8-bit auto-reload)**. Because it automatically reloads the initial value into TL1 upon overflow without requiring software intervention in an ISR, ensuring jitter-free, constant baud clock generation.

#### Q20: How do you calculate the reload value for Timer 0 to generate a 1 ms delay with an 11.0592 MHz crystal?
**Ans:**
1. Machine cycle time = $\frac{12}{11.0592\text{ MHz}} = 1.08507\ \mu\text{s}$.
2. Required clock counts = $\frac{1000\ \mu\text{s}}{1.08507\ \mu\text{s}} \approx 922$ counts.
3. Reload value in Mode 1 (16-bit) = $65536 - 922 = 64614 = \text{0xFC66}$.
4. Therefore: `TH0 = 0xFC; TL0 = 0x66;`.

---

## Category 5: Serial Communication (UART)

#### Q21: What are SCON and SBUF registers?
**Ans:** 
- **SCON (Serial Control):** Configures UART mode (SM0, SM1), enables receiver (REN), and holds transmit (TI) and receive (RI) interrupt flags.
- **SBUF (Serial Buffer):** Physically two separate registers sharing the same address (`0x99`). Writing to SBUF sends a byte to the transmitter; reading from SBUF fetches a byte from the receiver buffer.

#### Q22: What are the TI and RI flags in SCON?
**Ans:** 
- **TI (Transmit Interrupt):** Automatically set by hardware when the stop bit of the transmitted byte is sent out. It must be cleared by software (`TI = 0;`).
- **RI (Receive Interrupt):** Automatically set by hardware when the stop bit of an incoming byte is received and valid in SBUF. It must be cleared by software (`RI = 0;`).

#### Q23: What does the SMOD bit in PCON register do?
**Ans:** SMOD is Bit 7 of PCON. When set to `1`, it doubles the UART baud rate for a given Timer 1 reload value. When `0` (default), standard baud rates apply.

---

## Category 6: Interrupts

#### Q24: How many interrupts are available on a standard 8051, and what are their vector addresses?
**Ans:** Standard 8051 has 5 interrupt sources:
1. **Reset:** `0x0000`
2. **External Interrupt 0 ($\overline{\text{INT0}}$):** `0x0003`
3. **Timer 0 Overflow (TF0):** `0x000B`
4. **External Interrupt 1 ($\overline{\text{INT1}}$):** `0x0013`
5. **Timer 1 Overflow (TF1):** `0x001B`
6. **Serial Port (TI / RI):** `0x0023`

#### Q25: How do you enable global and individual interrupts in C?
**Ans:** By configuring the **IE (Interrupt Enable)** register:
- `EA = 1;` enables global interrupts.
- `EX0 = 1;` enables External Interrupt 0.
- `ET0 = 1;` enables Timer 0 Interrupt.
- `ES = 1;` enables Serial Port Interrupt.

---

## Category 7: Peripheral Interfacing

#### Q26: What is the difference between Common Anode and Common Cathode 7-Segment Displays?
**Ans:**
- **Common Anode (CA):** All LED anodes are tied together to $+5\text{V}$. Segments light up when driven **LOW (0)**.
- **Common Cathode (CC):** All LED cathodes are tied together to GND. Segments light up when driven **HIGH (1)**.

#### Q27: How does multiplexing work in a 4-digit 7-segment display?
**Ans:** Multiplexing uses **Persistence of Vision (POV)** (human eye retains images for ~1/16th of a second). All segment data lines (A-G) are shared across all 4 displays. Only one digit control pin is enabled at any single moment, displaying its corresponding value for ~2–5 ms. By cycling through all 4 digits rapidly (>50 Hz), all displays appear continuously lit without flicker, saving 20 I/O pins.

#### Q28: What is the purpose of the RS and E pins on a 16x2 HD44780 LCD?
**Ans:**
- **RS (Register Select):** `RS = 0` selects the Instruction Command Register (for clearing display, cursor moves, initializing). `RS = 1` selects the Data Register (for displaying ASCII characters).
- **E (Enable):** Latches the byte on the LCD data bus on a High-to-Low transition ($1 \to 0$ pulse).

#### Q29: What is the standard 16x2 LCD initialization command sequence?
**Ans:**
1. `0x38`: 2 lines, 5x7 matrix character format, 8-bit data mode.
2. `0x0C`: Display ON, cursor OFF.
3. `0x06`: Auto-increment cursor position to the right.
4. `0x01`: Clear display screen and return cursor to home (`0x80`).

#### Q30: How does the ADC0809 handshaking mechanism operate?
**Ans:**
1. Set channel select lines (ADDA, ADDB, ADDC).
2. Pulse **ALE** (Address Latch Enable) and **SOC** (Start of Conversion) high to begin SAR sampling.
3. Monitor **EOC** (End of Conversion). EOC goes low during conversion and transitions high when conversion is complete.
4. Set **OE** (Output Enable) high to read the converted 8-bit digital value from the data pins.

#### Q31: How does an R-2R ladder DAC0808 generate analog voltages?
**Ans:** It converts an 8-bit digital binary input into an output current proportional to the digital value:
$$I_{\text{out}} = I_{\text{ref}} \left( \frac{D_7}{2} + \frac{D_6}{4} + \dots + \frac{D_0}{256} \right)$$
An external operational amplifier (e.g., LM741 / TL084) is used as an I-to-V converter to produce a $0\text{ to }5\text{V}$ or $-5\text{V to }+5\text{V}$ analog output waveform.

#### Q32: Why is an L293D or ULN2003 driver required to connect motors to an 8051?
**Ans:** An 8051 port pin can source only ~50–100 µA and sink ~10–20 mA at 5V, while DC motors and stepper coils require hundreds of milliamps to several amperes at higher voltages (9V–24V). Attempting to drive motors directly from 8051 pins would destroy the microcontroller. Additionally, motor drivers contain flyback clamp diodes to suppress inductive back-EMF spikes generated when motor coils de-energize.

#### Q33: Describe the 1-wire communication sequence used by the DHT11 sensor.
**Ans:**
1. **Start Signal:** 8051 pulls the data pin low for at least 18 ms, then pulls high for 20–40 µs.
2. **Response:** DHT11 pulls low for 80 µs, then high for 80 µs.
3. **Data Stream:** DHT11 transmits 40 bits (5 bytes: Integral RH, Decimal RH, Integral Temp, Decimal Temp, Checksum). A bit `0` has a 26–28 µs high pulse; a bit `1` has a 70 µs high pulse.
4. **Verification:** If $\text{RH}_{\text{int}} + \text{RH}_{\text{dec}} + \text{Temp}_{\text{int}} + \text{Temp}_{\text{dec}} == \text{Checksum}$, data is valid.
