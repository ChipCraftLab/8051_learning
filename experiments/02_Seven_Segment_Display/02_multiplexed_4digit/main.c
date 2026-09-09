/**
 * ============================================================================
 * Experiment 02B: 4-Digit Multiplexed 7-Segment Display (0000 - 9999 Counter)
 * Microcontroller: AT89S52 / AT89C51
 * Technique: Time-Division Multiplexing (Persistence of Vision)
 * Maintainer: ChipCraftLab
 * ============================================================================
 * 
 * Multiplexing Principle:
 * - Segment data bus (P0: a to g) is shared by all 4 display digits.
 * - Digit control lines (P2.0 to P2.3) enable one digit cathode at a time.
 * - By cycling through all 4 digits at > 50 Hz (~2 ms per digit), the human
 *   eye perceives all 4 digits as continuously and simultaneously illuminated.
 */

#include <reg51.h>
#include "delay.h"

#define SEG_DATA P0  // Segment Data bus (a-g, dp)
#define SEG_CTRL P2  // Digit select lines (D1, D2, D3, D4)

/* Common Cathode Segment Lookup Table (0-9) */
unsigned char code sev_seg[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

void main(void) {
    unsigned char thousands, hundreds, tens, units, refresh;

    while (1) {
        for (thousands = 0; thousands < 10; thousands++) {
            for (hundreds = 0; hundreds < 10; hundreds++) {
                for (tens = 0; tens < 10; tens++) {
                    for (units = 0; units < 10; units++) {

                        /* Multiplexing refresh loop (~50 cycles = ~100 ms hold per number) */
                        for (refresh = 0; refresh < 30; refresh++) {
                            // Digit 1: Units (P2.0 active)
                            SEG_CTRL = 0x01;
                            SEG_DATA = sev_seg[units];
                            delay(200);
                            SEG_CTRL = 0x00; // Ghosting prevention blanking

                            // Digit 2: Tens (P2.1 active)
                            SEG_CTRL = 0x02;
                            SEG_DATA = sev_seg[tens];
                            delay(200);
                            SEG_CTRL = 0x00;

                            // Digit 3: Hundreds (P2.2 active)
                            SEG_CTRL = 0x04;
                            SEG_DATA = sev_seg[hundreds];
                            delay(200);
                            SEG_CTRL = 0x00;

                            // Digit 4: Thousands (P2.3 active)
                            SEG_CTRL = 0x08;
                            SEG_DATA = sev_seg[thousands];
                            delay(200);
                            SEG_CTRL = 0x00;
                        }

                    }
                }
            }
        }
    }
}
