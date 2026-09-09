#ifndef __LCD_H__
#define __LCD_H__

#include <reg51.h>
#include "delay.h"

#define LCD_DATA P0
sbit LCD_RS = P2^0;
sbit LCD_E  = P2^1;

void cmd_lcd(unsigned char cmd) {
    LCD_DATA = cmd;
    LCD_RS = 0;
    LCD_E = 1;
    delay(100);
    LCD_E = 0;
    delay(100);
}

void data_lcd(unsigned char dat) {
    LCD_DATA = dat;
    LCD_RS = 1;
    LCD_E = 1;
    delay(100);
    LCD_E = 0;
    delay(100);
}

void init_lcd(void) {
    cmd_lcd(0x38);
    delay(5000);
    cmd_lcd(0x0C);
    delay(1000);
    cmd_lcd(0x06);
    delay(1000);
    cmd_lcd(0x01);
    delay(5000);
}

void string_lcd(const char *str) {
    while (*str != '\0') {
        data_lcd(*str);
        str++;
    }
}

/**
 * @brief Display an integer number with specified number of digits.
 * @param num Integer value (0 - 255).
 * @param digits Number of digits to display (e.g. 3).
 */
void number_lcd(unsigned int num, unsigned char digits) {
    unsigned char d[5];
    char i;
    for (i = digits - 1; i >= 0; i--) {
        d[i] = (num % 10) + '0';
        num /= 10;
    }
    for (i = 0; i < digits; i++) {
        data_lcd(d[i]);
    }
}

#endif
