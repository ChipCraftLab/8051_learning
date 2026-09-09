/**
 * ============================================================================
 * Experiment 01: LED Interfacing & Bit Manipulation Patterns
 * Microcontroller: AT89S52 / AT89C51
 * Clock Frequency: 11.0592 MHz
 * Laboratory: Undergraduate Microcontroller Systems Lab
 * Maintainer: ChipCraftLab
 * ============================================================================
 * 
 * Objectives:
 * 1. Configure Port 0 as a digital output port with external pull-ups.
 * 2. Implement fundamental visual patterns:
 *    - Nibble alternate flashing (0x0F <-> 0xF0)
 *    - Odd / Even alternating LEDs (0xAA <-> 0x55)
 *    - Left & Right chaser shifts using bitwise shift operators (<<, >>)
 *    - Running fill and clear rotation patterns
 */

#include <reg51.h>
#include "delay.h"

// Define LED output port (Port 0 requires external 1k-10k pull-up resistor network)
#define LED P0

void main(void) {
    unsigned char i;

    // Initialize all LEDs to OFF (Active-low or active-high depending on wiring)
    LED = 0x00;
    delay(30000);

    while (1) {
        /* Pattern 1: Nibble Flashing (Lower 4 LEDs vs Upper 4 LEDs) */
        LED = 0x0F;
        delay(30000);
        LED = 0xF0;
        delay(30000);

        /* Pattern 2: Alternating Odd / Even LEDs */
        LED = 0xAA; // 1010 1010
        delay(30000);
        LED = 0x55; // 0101 0101
        delay(30000);

        /* Pattern 3: Single LED Left Shift Chaser (P0.0 -> P0.7) */
        LED = 0x01;
        delay(30000);
        for (i = 0; i < 7; i++) {
            LED = LED << 1;
            delay(30000);
        }

        /* Pattern 4: Single LED Right Shift Chaser (P0.7 -> P0.0) */
        LED = 0x80;
        delay(30000);
        for (i = 0; i < 7; i++) {
            LED = LED >> 1;
            delay(30000);
        }

        /* Pattern 5: Left Fill Rotate (Accumulating LEDs from right to left) */
        LED = 0x01;
        delay(30000);
        for (i = 0; i < 7; i++) {
            LED = (LED << 1) | 0x01;
            delay(30000);
        }

        /* Pattern 6: Right Fill Rotate (Accumulating LEDs from left to right) */
        LED = 0x80;
        delay(30000);
        for (i = 0; i < 7; i++) {
            LED = (LED >> 1) | 0x80;
            delay(30000);
        }
    }
}
