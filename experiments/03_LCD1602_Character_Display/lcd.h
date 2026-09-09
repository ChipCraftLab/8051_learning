#ifndef __LCD_H__
#define __LCD_H__

#include <reg51.h>
#include "delay.h"

// Define LCD Control and Data Lines
#define LCD_DATA P0
sbit LCD_RS = P2^0;
sbit LCD_E  = P2^1;

/**
 * @brief Send an 8-bit instruction command to the LCD.
 * @param cmd Hex command byte (e.g. 0x01 for clear, 0x80 for Line 1).
 */
void cmd_lcd(unsigned char cmd) {
    LCD_DATA = cmd;
    LCD_RS = 0;   // RS = 0 selects Command Register
    LCD_E = 1;    // Generate High-to-Low pulse on Enable pin
    delay(100);
    LCD_E = 0;
    delay(100);
}

/**
 * @brief Send an ASCII character byte to display on the LCD.
 * @param dat ASCII character (e.g. 'A', '8').
 */
void data_lcd(unsigned char dat) {
    LCD_DATA = dat;
    LCD_RS = 1;   // RS = 1 selects Data Register
    LCD_E = 1;    // Generate High-to-Low pulse on Enable pin
    delay(100);
    LCD_E = 0;
    delay(100);
}

/**
 * @brief Initialize 16x2 LCD in 8-bit mode.
 */
void init_lcd(void) {
    cmd_lcd(0x38); // 8-bit mode, 2 display lines, 5x7 font matrix
    delay(5000);
    cmd_lcd(0x0C); // Display ON, Cursor OFF
    delay(1000);
    cmd_lcd(0x06); // Auto-increment cursor to the right
    delay(1000);
    cmd_lcd(0x01); // Clear display screen
    delay(5000);
}

/**
 * @brief Print a null-terminated string to the LCD.
 * @param str Pointer to char array / string constant.
 */
void string_lcd(const char *str) {
    while (*str != '\0') {
        data_lcd(*str);
        str++;
    }
}

#endif
