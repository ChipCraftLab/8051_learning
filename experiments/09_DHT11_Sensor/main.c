/**
 * ============================================================================
 * Experiment 09: DHT11 Digital Temperature & Humidity Sensor Interfacing
 * Microcontroller: AT89S52 / AT89C51
 * Crystal Clock: 11.0592 MHz
 * Protocol: Single-Wire Bidirectional Time-Division Protocol
 * Output: Serial UART (9600 Baud)
 * Maintainer: ChipCraftLab
 * ============================================================================
 * 
 * Data Packet Structure (40 Bits / 5 Bytes):
 * Byte 1: Relative Humidity Integral part (0 - 100 %)
 * Byte 2: Relative Humidity Decimal part (always 0 on standard DHT11)
 * Byte 3: Temperature Integral part (0 - 50 °C)
 * Byte 4: Temperature Decimal part
 * Byte 5: Checksum = (Byte 1 + Byte 2 + Byte 3 + Byte 4) & 0xFF
 */

#include <reg51.h>

sbit DHT11_PIN = P1^0; // Single-wire data communication line

/**
 * @brief Software microsecond delay for 11.0592 MHz crystal.
 * @note Each loop iteration takes ~3-4 machine cycles (~3.5 us).
 */
void delay_us(unsigned int us) {
    while (us--) {
        ;;;;;
    }
}

/**
 * @brief Millisecond delay.
 */
void delay_ms(unsigned int ms) {
    while (ms--) {
        delay_us(250);
    }
}

/**
 * @brief Configure UART for 9600 baud serial output.
 */
void uart_init(void) {
    TMOD = (TMOD & 0x0F) | 0x20; // Timer 1 Mode 2 (8-bit auto reload)
    SCON = 0x50;                 // Mode 1 (8-bit UART), REN=1
    TH1  = 0xFD;                 // 9600 Baud at 11.0592 MHz
    TR1  = 1;
    TI   = 0;
}

/**
 * @brief Transmit byte over UART.
 */
void uart_tx(unsigned char ch) {
    SBUF = ch;
    while (!TI);
    TI = 0;
}

/**
 * @brief Transmit string over UART.
 */
void uart_print(const char *str) {
    while (*str != '\0') {
        uart_tx(*str);
        str++;
    }
}

/**
 * @brief Transmit 2-digit integer as ASCII text.
 */
void uart_print_num(unsigned char num) {
    uart_tx((num / 10) + '0');
    uart_tx((num % 10) + '0');
}

/**
 * @brief Issue Master Start Signal to wake DHT11 sensor.
 */
void dht11_start(void) {
    DHT11_PIN = 0;   // Pull data line LOW
    delay_ms(20);    // Hold LOW for at least 18ms
    DHT11_PIN = 1;   // Release data line HIGH
    delay_us(30);    // Wait for sensor response (20-40us)
}

/**
 * @brief Read one 8-bit byte from DHT11 bit stream.
 */
unsigned char dht11_read_byte(void) {
    unsigned char dat = 0;
    char i;

    for (i = 0; i < 8; i++) {
        // Wait for pin to transition HIGH (start of bit pulse)
        while (!DHT11_PIN);

        // Pulse duration distinguishes logic '0' (26-28us) from logic '1' (70us)
        delay_us(30);

        if (DHT11_PIN == 0) {
            dat = (dat << 1);        // Bit is '0'
        } else {
            dat = (dat << 1) | 0x01; // Bit is '1'
            while (DHT11_PIN);       // Wait until pulse finishes going LOW
        }
    }
    return dat;
}

void main(void) {
    unsigned char rh_int, rh_dec, temp_int, temp_dec, checksum;

    uart_init();
    delay_ms(1000); // Allow sensor to stabilize after power on

    uart_print("\r\n=========================================\r\n");
    uart_print(" DHT11 TEMPERATURE & HUMIDITY MONITOR\r\n");
    uart_print("=========================================\r\n\r\n");

    while (1) {
        dht11_start();

        // Check sensor response: DHT11 pulls line LOW (80us) then HIGH (80us)
        if (DHT11_PIN == 0) {
            while (DHT11_PIN == 0); // Wait for response LOW to end
            while (DHT11_PIN == 1); // Wait for response HIGH to end

            // Read 5 bytes (40 bits)
            rh_int   = dht11_read_byte();
            rh_dec   = dht11_read_byte();
            temp_int = dht11_read_byte();
            temp_dec = dht11_read_byte();
            checksum = dht11_read_byte();

            // Verify parity checksum
            if ((rh_int + rh_dec + temp_int + temp_dec) == checksum) {
                uart_print("Humidity: ");
                uart_print_num(rh_int);
                uart_print(" %RH  |  Temperature: ");
                uart_print_num(temp_int);
                uart_print(" *C\r\n");
            } else {
                uart_print("[WARN] Checksum error: data packet corrupted.\r\n");
            }
        } else {
            uart_print("[ERROR] DHT11 sensor not responding.\r\n");
        }

        // Sampling interval must be >= 1-2 seconds
        delay_ms(2000);
    }
}
