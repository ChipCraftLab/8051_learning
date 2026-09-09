# Experiment 06: Digital-to-Analog Converter (DAC0808) Waveform Generation

## 🎯 Aim
To interface an 8-bit Digital-to-Analog Converter (DAC0808 / MC1408) with an LM741 operational amplifier current-to-voltage converter to Port 2 of the 8051, and generate standard periodic waveforms (Triangular, Sine, Square, and Sawtooth) observable on an oscilloscope.

---

## 🧰 Components Required
- AT89S52 / AT89C51 Microcontroller
- DAC0808 / MC1408 8-Bit DAC IC
- LM741 / TL081 Operational Amplifier
- Resistors: 5 kΩ (feedback resistor), 2.5 kΩ ($V_{\text{ref}}$ current resistor)
- Dual DC Power Supply ($\pm 12\text{V}$ for Op-Amp, $+5\text{V}$ for 8051)
- Cathode-Ray Oscilloscope (CRO) / Digital Storage Oscilloscope (DSO)

---

## ⚡ Circuit Schematic & Connections

```
      AT89S52                          DAC0808                      LM741 Op-Amp
    +---------+                      +----------+                  +------------+
    |         |                      |          |                  |            |
    |     P2.0+--------------------->| A8 (LSB) |                  |            |
    |     P2.1+--------------------->| A7       |                  |            |
    |     P2.2+--------------------->| A6       |   I_out (Pin 4)  |            |
    |     P2.3+--------------------->| A5       +----------------->|- In        |
    |     P2.4+--------------------->| A4       |                  |+ In        |
    |     P2.5+--------------------->| A3       |           GND───>|            |
    |     P2.6+--------------------->| A2       |                  |     V_out  |
    |     P2.7+--------------------->| A1 (MSB) |        ┌─────────+───o───────>| To Scope
    +---------+                      +----------+        │         │   (0-5V)   |
                                                         │       ┌─┴─┐          |
                                                         └───────┤5k ├──────────┘
                                                                 └───┘ Rf
```

---

## 🧠 Theory & Waveform Generation
The DAC0808 is an R-2R ladder multiplying DAC that outputs an analog current $I_{\text{out}}$ proportional to the 8-bit digital input byte:
$$I_{\text{out}} = I_{\text{ref}} \left( \frac{\text{Byte}}{256} \right)$$

The LM741 operational amplifier converts this current to an analog voltage:
$$V_{\text{out}} = I_{\text{out}} \times R_f$$

### Waveform Synthesis Algorithms:
1. **Triangular Wave:** Increment output linearly from `0` to `255`, then decrement linearly from `255` to `0`.
2. **Sawtooth Wave:** Increment linearly from `0` to `255`, then reset immediately back to `0`.
3. **Square Wave:** Output `0x00` for time $T/2$, then output `0xFF` for time $T/2$.
4. **Sine Wave:** Fetch values from a 36-point lookup table calculated as $V = 128 + 127 \sin(\theta)$ where $\theta$ steps by $10^\circ$.

---

## 💬 Viva-Voce Questions
1. **What is the settling time of DAC0808?**
   *Answer:* Approximately 150 ns, making it suitable for audio-frequency waveform generation.
2. **Why is an external operational amplifier required with DAC0808?**
   *Answer:* DAC0808 provides an analog current output ($I_{\text{out}}$), not an analog voltage. The operational amplifier configured as a transimpedance amplifier (current-to-voltage converter) transforms $I_{\text{out}}$ into an observable voltage signal.
3. **What determines the frequency of the generated sine wave?**
   *Answer:* The number of discrete sample points in the lookup table and the delay between consecutive lookup outputs ($f = \frac{1}{N \times T_{\text{sample}}}$).
