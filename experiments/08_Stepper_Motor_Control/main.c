/**
 * ============================================================================
 * Experiment 08: Stepper Motor Control (4-Phase Unipolar via ULN2003)
 * Microcontroller: AT89S52 / AT89C51
 * Motor: 4-Phase Unipolar Stepper Motor (e.g. 28BYJ-48)
 * Maintainer: ChipCraftLab
 * ============================================================================
 * 
 * Stepping Sequence (Wave Drive / 4-Step):
 * Step 1: Coil A = 1, Coils B, C, D = 0
 * Step 2: Coil B = 1, Coils A, C, D = 0
 * Step 3: Coil C = 1, Coils A, B, D = 0
 * Step 4: Coil D = 1, Coils A, B, C = 0
 * 
 * Reversing the excitation sequence rotates the motor in the opposite direction.
 */

#include <reg51.h>
#include "delay.h"

// 4 Stepper Motor Coil Pins (Port 0)
sbit COIL_A = P0^0;
sbit COIL_B = P0^1;
sbit COIL_C = P0^2;
sbit COIL_D = P0^3;

/**
 * @brief Step motor one cycle clockwise.
 */
void step_clockwise(void) {
    COIL_A = 1; COIL_B = 0; COIL_C = 0; COIL_D = 0;
    delay(20000);
    COIL_A = 0; COIL_B = 1; COIL_C = 0; COIL_D = 0;
    delay(20000);
    COIL_A = 0; COIL_B = 0; COIL_C = 1; COIL_D = 0;
    delay(20000);
    COIL_A = 0; COIL_B = 0; COIL_C = 0; COIL_D = 1;
    delay(20000);
}

/**
 * @brief Step motor one cycle counter-clockwise.
 */
void step_counter_clockwise(void) {
    COIL_A = 0; COIL_B = 0; COIL_C = 0; COIL_D = 1;
    delay(20000);
    COIL_A = 0; COIL_B = 0; COIL_C = 1; COIL_D = 0;
    delay(20000);
    COIL_A = 0; COIL_B = 1; COIL_C = 0; COIL_D = 0;
    delay(20000);
    COIL_A = 1; COIL_B = 0; COIL_C = 0; COIL_D = 0;
    delay(20000);
}

void main(void) {
    char i;

    while (1) {
        // Rotate Clockwise for 24 sequences
        for (i = 0; i < 24; i++) {
            step_clockwise();
        }

        // Pause for 1 second
        delay(65000);

        // Rotate Counter-Clockwise for 24 sequences
        for (i = 0; i < 24; i++) {
            step_counter_clockwise();
        }

        // Pause for 1 second
        delay(65000);
    }
}
