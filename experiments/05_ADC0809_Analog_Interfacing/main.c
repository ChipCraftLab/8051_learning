/**
 * ============================================================================
 * Experiment 05: ADC0809 8-Channel SAR Analog-to-Digital Converter
 * Microcontroller: AT89S52 / AT89C51
 * Display: 16x2 Character LCD (Port 0)
 * ADC Interface: Port 1 (Control) + Port 3 (Data Bus)
 * Maintainer: ChipCraftLab
 * ============================================================================
 */

#include <reg51.h>
#include "delay.h"
#include "lcd.h"
#include "adc.h"

void main(void) {
    unsigned char adc_raw;
    unsigned int voltage_mv;

    // Initialize LCD screen
    init_lcd();
    cmd_lcd(0x80);
    string_lcd("ADC0809 LAB TEST");
    delay(35000);

    while (1) {
        // Read Channel 7 (Potentiometer / Analog Input)
        adc_raw = read_adc(7);

        // Calculate voltage in millivolts: V = (raw * 5000) / 255
        voltage_mv = (unsigned int)(((unsigned long)adc_raw * 5000) / 255);

        // Line 1: Raw 8-Bit Digital Value (0 - 255)
        cmd_lcd(0x80);
        string_lcd("Raw Val: ");
        number_lcd(adc_raw, 3);
        string_lcd(" / 255 ");

        // Line 2: Calculated Voltage (e.g. "V: 3500 mV")
        cmd_lcd(0xC0);
        string_lcd("Volt: ");
        number_lcd(voltage_mv, 4);
        string_lcd(" mV   ");

        delay(15000);
    }
}
