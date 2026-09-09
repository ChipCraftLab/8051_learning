/**
 * ============================================================================
 * Experiment 02A: Single-Digit 7-Segment Display (0-9 Decade Counter)
 * Microcontroller: AT89S52 / AT89C51
 * Display Type: Common Cathode (Active High Segment Signals)
 * Maintainer: ChipCraftLab
 * ============================================================================
 */

#include <reg51.h>
#include "delay.h"

#define SEG_DATA P0  // Segment Data lines (a, b, c, d, e, f, g, dp)
#define SEG_CTRL P2  // Digit Common Control lines

/* Common Cathode Segment Lookup Table for Digits 0 to 9 */
/* Bit Mapping: P0.7=dp, P0.6=g, P0.5=f, P0.4=e, P0.3=d, P0.2=c, P0.1=b, P0.0=a */
unsigned char code sev_seg[10] = {
    0x3F, // 0: a,b,c,d,e,f
    0x06, // 1: b,c
    0x5B, // 2: a,b,d,e,g
    0x4F, // 3: a,b,c,d,g
    0x66, // 4: b,c,f,g
    0x6D, // 5: a,c,d,f,g
    0x7D, // 6: a,c,d,e,f,g
    0x07, // 7: a,b,c
    0x7F, // 8: a,b,c,d,e,f,g
    0x6F  // 9: a,b,c,d,f,g
};

void main(void) {
    unsigned char j;

    // Enable first digit position (Common Cathode grounded via transistor or driven low/high)
    SEG_CTRL = 0x00; 

    while (1) {
        for (j = 0; j < 10; j++) {
            SEG_DATA = sev_seg[j];
            delay(35000); // Hold each digit visible for ~350ms
        }
    }
}
