#ifndef __ADC_H__
#define __ADC_H__

#include <reg51.h>

// ADC Control and Handshaking Pin Definitions
#define ADC_DATA_BUS P3

sbit ADC_OE    = P1^0;  // Output Enable (Active High)
sbit ADC_SOC   = P1^1;  // Start Of Conversion (Active High pulse)
sbit ADC_ALE   = P1^2;  // Address Latch Enable (Active High pulse)
sbit ADC_EOC   = P1^3;  // End Of Conversion (Input from ADC)
sbit ADC_CLOCK = P1^4;  // Software Generated Clock for ADC0808/0809
sbit ADC_SET0  = P1^5;  // Channel Select Bit A
sbit ADC_SET1  = P1^6;  // Channel Select Bit B
sbit ADC_SET2  = P1^7;  // Channel Select Bit C

/**
 * @brief Generate clock pulses for ADC0809 internal SAR logic (~500 kHz).
 */
void adc_clock(void) {
    int a, b;
    for (b = 0; b <= 200; b++) {
        for (a = 0; a < 10; a++);
        ADC_CLOCK = ~ADC_CLOCK;
    }
}

/**
 * @brief Sample analog channel and read 8-bit digital value from ADC0809.
 * @param channel Analog channel number (0 to 7).
 * @return 8-bit converted digital value (0 to 255).
 */
unsigned char read_adc(unsigned char channel) {
    unsigned char dat;

    // Set 3-bit multiplexer address (A, B, C) with proper clearing
    ADC_SET0 = (channel & 0x01) ? 1 : 0;
    ADC_SET1 = (channel & 0x02) ? 1 : 0;
    ADC_SET2 = (channel & 0x04) ? 1 : 0;

    // Latch address and trigger Start of Conversion (SOC)
    ADC_ALE = 1;
    ADC_SOC = 1;
    adc_clock();
    ADC_ALE = 0;
    ADC_SOC = 0;
    adc_clock();

    // Wait until conversion completes (EOC goes HIGH)
    while (ADC_EOC == 0) {
        ADC_CLOCK = ~ADC_CLOCK; // Continue clocking SAR during conversion
    }

    // Enable tri-state outputs to read data bus
    ADC_OE = 1;
    dat = ADC_DATA_BUS;
    ADC_OE = 0; // Release data bus

    return dat;
}

#endif
