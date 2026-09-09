/**
 * ============================================================================
 * Experiment 06: DAC0808 / MC1408 Waveform Generator
 * Microcontroller: AT89S52 / AT89C51
 * DAC Data Bus: Port 2 (P2.0 - P2.7)
 * Output Waveforms: Square, Triangular, Sawtooth, and Sine Wave
 * Maintainer: ChipCraftLab
 * ============================================================================
 */

#include <reg51.h>
#include "delay.h"

#define DAC_PORT P2

/* 36-Point Precalculated Sine Wave Table (0 to 360 degrees, centered at 128) */
/* Formula: V = 128 + 127 * sin(theta) */
unsigned char code sine_table[36] = {
    128, 150, 172, 192, 210, 226, 238, 247, 252, 253, 
    250, 243, 232, 218, 201, 182, 161, 139, 117,  95, 
     74,  55,  38,  24,  14,   7,   4,   5,  10,  19, 
     31,  47,  65,  85, 106, 128
};

/**
 * @brief Generate continuous triangular waveform.
 */
void generate_triangular(void) {
    int i, j;
    // Ramp Up (0 to 255)
    for (i = 0; i <= 255; i++) {
        DAC_PORT = i;
        for (j = 0; j < 2; j++);
    }
    // Ramp Down (255 to 0)
    for (i = 255; i >= 0; i--) {
        DAC_PORT = i;
        for (j = 0; j < 2; j++);
    }
}

/**
 * @brief Generate continuous sine wave using 36-point lookup table.
 */
void generate_sine(void) {
    unsigned char i;
    for (i = 0; i < 36; i++) {
        DAC_PORT = sine_table[i];
    }
}

/**
 * @brief Generate square wave (50% duty cycle).
 */
void generate_square(void) {
    DAC_PORT = 0x00;
    delay(500);
    DAC_PORT = 0xFF;
    delay(500);
}

/**
 * @brief Generate sawtooth (ramp up, instantaneous drop).
 */
void generate_sawtooth(void) {
    unsigned char i;
    for (i = 0; i < 255; i++) {
        DAC_PORT = i;
    }
}

void main(void) {
    while (1) {
        // Default output: Triangular wave
        generate_triangular();
    }
}
