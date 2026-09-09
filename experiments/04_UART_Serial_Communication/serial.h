#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <reg51.h>

/**
 * @brief Initialize 8051 hardware UART at specified baud rate using Timer 1 Mode 2.
 * @param br Desired baud rate (typically 9600 for 11.0592 MHz crystal).
 */
void init_serial(unsigned int br) {
    TMOD = (TMOD & 0x0F) | 0x20; // Timer 1, Mode 2 (8-bit auto-reload)
    SCON = 0x50;                 // Mode 1 (8-bit UART), Receiver Enabled (REN=1)
    TH1  = (unsigned char)(256 - (28800 / br)); // Auto-reload value (0xFD for 9600)
    TR1  = 1;                    // Start Timer 1
    TI   = 0;
    RI   = 0;
}

/**
 * @brief Transmit a single character byte over UART.
 * @param ch Byte to transmit.
 */
void trans_serial(unsigned char ch) {
    SBUF = ch;
    while (TI == 0); // Wait until byte transmission is complete
    TI = 0;          // Clear Transmit Interrupt flag
}

/**
 * @brief Block and receive a single character byte from UART.
 * @return Received ASCII character from SBUF.
 */
unsigned char rec_serial(void) {
    while (RI == 0); // Wait until a byte is received
    RI = 0;          // Clear Receive Interrupt flag
    return SBUF;
}

/**
 * @brief Transmit a null-terminated string over serial port.
 * @param str Pointer to string.
 */
void string_serial(const char *str) {
    while (*str != '\0') {
        trans_serial(*str);
        str++;
    }
}

#endif
