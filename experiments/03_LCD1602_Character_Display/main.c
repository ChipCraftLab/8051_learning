/**
 * ============================================================================
 * Experiment 03: 16x2 Character LCD Interfacing (HD44780 Controller)
 * Microcontroller: AT89S52 / AT89C51
 * Interface Mode: 8-Bit Parallel Interface
 * Maintainer: ChipCraftLab
 * ============================================================================
 */

#include <reg51.h>
#include "delay.h"
#include "lcd.h"

void main(void) {
    char i;

    // Initialize LCD screen (0x38, 0x0C, 0x06, 0x01)
    init_lcd();

    while (1) {
        // Line 1: Address 0x80
        cmd_lcd(0x80);
        string_lcd("  CHIPCRAFTLAB  ");

        // Line 2: Address 0xC0
        cmd_lcd(0xC0);
        string_lcd(" ** 8051 LAB ** ");
        delay(60000);

        // Display Shift Right Demonstration (Command 0x1C)
        for (i = 0; i < 4; i++) {
            cmd_lcd(0x1C);
            delay(30000);
        }

        // Display Shift Left Demonstration (Command 0x18)
        for (i = 0; i < 4; i++) {
            cmd_lcd(0x18);
            delay(30000);
        }

        delay(30000);
    }
}
