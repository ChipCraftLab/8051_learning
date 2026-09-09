# Experiment 03: 16×2 Alphanumeric LCD Interfacing

## 🎯 Aim
To interface an industry-standard 16×2 alphanumeric LCD module (Hitachi HD44780 controller) to an 8051 microcontroller in 8-bit mode, initialize the display, print strings on both lines, and demonstrate display shifting commands.

---

## 🧰 Components Required
- AT89S52 / AT89C51 Microcontroller
- 16×2 Character LCD (HD44780 or equivalent)
- 10 kΩ Preset Potentiometer (for LCD contrast adjustment - Pin 3 $V_{EE}$)
- 1 kΩ × 8 SIL Resistor Pack (Port 0 pull-ups)
- 11.0592 MHz Crystal Oscillator with 33 pF capacitors

---

## ⚡ Pin Connections

| LCD Pin # | Pin Symbol | Connected To | Description |
|:---:|:---:|:---:|:---|
| 1 | VSS | GND | Ground (0V) |
| 2 | VDD | +5V | Logic Power Supply |
| 3 | VEE / V0 | Pot wiper | Contrast Adjustment |
| 4 | RS | `P2.0` | Register Select: 0=Command, 1=Data |
| 5 | R/W | GND | Read/Write: Tied to GND for Write-Only |
| 6 | E | `P2.1` | Enable strobe (High-to-Low active pulse) |
| 7–14 | D0 – D7 | `P0.0 – P0.7` | 8-Bit Bidirectional Data Bus |
| 15 | LED+ (A) | +5V (via 220Ω) | Backlight Anode |
| 16 | LED- (K) | GND | Backlight Cathode |

---

## 🧠 LCD Command Reference

| Hex Code | Command Function |
|:---:|:---|
| `0x38` | Configure 2 display lines, 5×7 character font, 8-bit bus mode |
| `0x0C` | Display ON, Cursor OFF |
| `0x0E` | Display ON, Cursor Blinking |
| `0x06` | Entry Mode: Auto-increment cursor to the right |
| `0x01` | Clear entire display and return cursor to home position |
| `0x80` | Force cursor to beginning of Line 1 |
| `0xC0` | Force cursor to beginning of Line 2 |
| `0x1C` | Shift entire display right by one position |
| `0x18` | Shift entire display left by one position |

---

## 💬 Viva-Voce Questions
1. **What is the function of the RS pin on an LCD?**
   *Answer:* Register Select. When RS is 0, the byte sent to the data lines is executed as an instruction command. When RS is 1, the byte is stored in DDRAM as an ASCII character to be displayed.
2. **Why is the R/W pin frequently tied directly to GND in student experiments?**
   *Answer:* Grounding R/W configures the LCD permanently in Write mode, saving one microcontroller pin when the busy flag does not need to be polled (using simple software delays instead).
3. **What is the address of the first character on Line 2 of a 16x2 LCD?**
   *Answer:* `0xC0` (since DDRAM address for line 2 starts at $0x40$, and command format is $0x80 + 0x40 = 0xC0$).
