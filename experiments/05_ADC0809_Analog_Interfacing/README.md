# Experiment 05: Analog-to-Digital Converter (ADC0809) Interfacing

## 🎯 Aim
To interface an 8-bit, 8-channel Successive Approximation Register (SAR) Analog-to-Digital Converter (ADC0809/ADC0808) to the 8051 microcontroller, generate necessary clock/control signals, sample analog voltages, and display both the raw digital count and computed millivolts on a 16×2 LCD.

---

## 🧰 Components Required
- AT89S52 / AT89C51 Microcontroller
- ADC0809 or ADC0808 8-Bit Converter IC
- 16×2 Character LCD (HD44780)
- 10 kΩ Potentiometer (analog voltage source $0\text{V} - 5\text{V}$)
- 1 kΩ × 8 Resistor Pack (Port 0 pull-ups)

---

## ⚡ Interfacing & Handshaking Table

| ADC0809 Pin | 8051 Pin | Direction | Function |
|:---:|:---:|:---:|:---|
| **START (SOC)** | `P1.1` | Output to ADC | Starts internal successive approximation conversion |
| **ALE** | `P1.2` | Output to ADC | Latches 3-bit multiplexer channel address |
| **EOC** | `P1.3` | Input to 8051 | End Of Conversion: Goes LOW during conversion, HIGH when ready |
| **OE** | `P1.0` | Output to ADC | Output Enable: Activates tri-state data outputs |
| **CLK** | `P1.4` | Output to ADC | Clock input for internal SAR logic (~10 kHz to 1280 kHz) |
| **ADDA, B, C** | `P1.5, P1.6, P1.7`| Output to ADC | 3-Bit Channel Multiplexer Address Lines ($IN_0 - IN_7$) |
| **$D_0 - D_7$** | `P3.0 - P3.7` | Input to 8051 | 8-bit digital output data bus |

---

## 🧠 Conversion Mathematics
For an 8-bit ADC with $V_{\text{ref}} = 5.0\text{ V}$:
$$\text{Resolution (Step Size)} = \frac{V_{\text{ref}}}{2^8 - 1} = \frac{5.0\text{ V}}{255} \approx 19.6\text{ mV/step}$$

$$\text{Analog Voltage } V_{\text{in}} = \frac{\text{Digital Output} \times 5000\text{ mV}}{255}$$

---

## 💬 Viva-Voce Questions
1. **What type of ADC architecture is used in the ADC0809?**
   *Answer:* Successive Approximation Register (SAR). It compares the analog input against internal DAC voltages bit-by-bit from MSB to LSB.
2. **What is the typical conversion time of the ADC0809?**
   *Answer:* Approximately 100 µs when clocked at 640 kHz (requiring ~64 clock cycles per conversion).
3. **What is the function of the ALE pin on the ADC0809?**
   *Answer:* Address Latch Enable. It latches the 3-bit address on lines A, B, and C to select one of the 8 analog input channels ($IN_0$ through $IN_7$).
