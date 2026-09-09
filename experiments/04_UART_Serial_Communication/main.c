/**
 * ============================================================================
 * Experiment 04: UART Serial Communication (9600 Baud Loopback & Strings)
 * Microcontroller: AT89S52 / AT89C51
 * Oscillator Clock: 11.0592 MHz
 * Timer Used: Timer 1 Mode 2 (8-Bit Auto-Reload)
 * Maintainer: ChipCraftLab
 * ============================================================================
 */

#include <reg51.h>
#include "delay.h"
#include "serial.h"

void main(void) {
    unsigned char received_char;

    // Configure UART for 9600 Baud, 8 Data Bits, 1 Stop Bit, No Parity
    init_serial(9600);
    delay(10000);

    // Transmit welcoming banner message
    string_serial("\r\n=========================================\r\n");
    string_serial(" 8051 UART SERIAL COMMUNICATION LAB\r\n");
    string_serial(" ChipCraftLab - 9600 Baud, 8-N-1\r\n");
    string_serial(" Type any character to echo back:\r\n");
    string_serial("=========================================\r\n\r\n");

    while (1) {
        // Wait for incoming character, then echo it back to terminal
        received_char = rec_serial();
        trans_serial(received_char);

        // If user presses Enter (Carriage Return), append Line Feed
        if (received_char == '\r') {
            trans_serial('\n');
        }
    }
}
