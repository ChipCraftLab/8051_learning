/**
 * ============================================================================
 * Experiment 07: DC Motor Direction & Interface via L293D H-Bridge
 * Microcontroller: AT89S52 / AT89C51
 * Motor Driver: L293D Dual H-Bridge Driver IC
 * Maintainer: ChipCraftLab
 * ============================================================================
 * 
 * Operating Principle:
 * - IN1 = 1, IN2 = 0 -> Forward (Clockwise) Rotation
 * - IN1 = 0, IN2 = 1 -> Reverse (Counter-Clockwise) Rotation
 * - IN1 = 0, IN2 = 0 -> Motor Coast / Stop
 * - IN1 = 1, IN2 = 1 -> Active Braking
 */

#include <reg51.h>
#include "delay.h"

// L293D Input Control Pins (Port 0)
sbit MOTOR_IN1 = P0^0;
sbit MOTOR_IN2 = P0^1;

void main(void) {
    while (1) {
        /* 1. Rotate Clockwise (Forward) for ~3 seconds */
        MOTOR_IN1 = 1;
        MOTOR_IN2 = 0;
        delay(65000);
        delay(65000);

        /* 2. Dead-time Stop for ~1 second (Prevents H-Bridge shoot-through) */
        MOTOR_IN1 = 0;
        MOTOR_IN2 = 0;
        delay(30000);

        /* 3. Rotate Counter-Clockwise (Reverse) for ~3 seconds */
        MOTOR_IN1 = 0;
        MOTOR_IN2 = 1;
        delay(65000);
        delay(65000);

        /* 4. Dead-time Stop for ~1 second */
        MOTOR_IN1 = 0;
        MOTOR_IN2 = 0;
        delay(30000);
    }
}
