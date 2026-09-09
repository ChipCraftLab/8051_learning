# Experiment 02: Seven Segment Display Interfacing

## 🎯 Aim
1. **Part A:** Interface a single-digit Common Cathode 7-segment display to Port 0 and display a 0–9 decade counter.
2. **Part B:** Interface a 4-digit 7-segment display module using time-division multiplexing to count from `0000` to `9999`.

---

## 🧰 Components Required
- 8051 Microcontroller (AT89S52 / AT89C51)
- 11.0592 MHz Crystal Oscillator with 33 pF capacitors
- 1× Common Cathode 7-Segment Display (Part A)
- 1× 4-Digit Common Cathode Multiplexed Display or 4 individual displays (Part B)
- 4× BC547 NPN Transistors (or direct port drive for low-current displays)
- 1× 1 kΩ × 8 SIL Resistor Pack (Port 0 pull-ups)
- 8× 330 Ω Resistors (Segment current limiters)

---

## ⚡ Pin Mapping Table

| 8051 Port Pin | 7-Segment Pin | Segment Function |
|:---:|:---:|:---|
| `P0.0` | Pin a | Top horizontal segment |
| `P0.1` | Pin b | Top-right vertical segment |
| `P0.2` | Pin c | Bottom-right vertical segment |
| `P0.3` | Pin d | Bottom horizontal segment |
| `P0.4` | Pin e | Bottom-left vertical segment |
| `P0.5` | Pin f | Top-left vertical segment |
| `P0.6` | Pin g | Middle horizontal segment |
| `P0.7` | Pin dp | Decimal point |
| `P2.0` | Common Cathode 1 | Digit 1 (Units) Enable |
| `P2.1` | Common Cathode 2 | Digit 2 (Tens) Enable |
| `P2.2` | Common Cathode 3 | Digit 3 (Hundreds) Enable |
| `P2.3` | Common Cathode 4 | Digit 4 (Thousands) Enable |

---

## 🧠 Theory of Multiplexing (Persistence of Vision)
When driving multiple 7-segment displays without multiplexing, four 8-segment displays would require $4 \times 8 = 32$ separate I/O pins, consuming the entire microcontroller.

By using **Time-Division Multiplexing**:
1. All segment pins (a through g) are connected in parallel to Port 0.
2. Only the cathode/anode of the desired digit is energized at any instant.
3. The display scans across all digits rapidly (> 50 Hz, or < 20 ms per full frame).
4. Because of human Persistence of Vision (POV), the user perceives all 4 digits as continuously illuminated.

---

## 💬 Viva-Voce Questions
1. **What is the difference between Common Anode and Common Cathode displays?**
   *Answer:* Common Anode displays have all positive terminals connected together (+5V) and turn ON with a logic LOW (0). Common Cathode displays connect all negative terminals to GND and turn ON with a logic HIGH (1).
2. **What is display ghosting and how do we prevent it?**
   *Answer:* Ghosting occurs when segment data from the previous digit lingers on the data bus while switching to the next digit cathode. It is prevented by briefly blanking the display (`SEG_CTRL = 0x00;`) before loading new segment data.
3. **What minimum refresh rate is needed to avoid visible flicker in multiplexed displays?**
   *Answer:* At least 50 Hz to 60 Hz overall refresh rate (~2 ms to 5 ms per digit).
