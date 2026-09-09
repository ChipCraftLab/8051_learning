#ifndef __DELAY_H__
#define __DELAY_H__

/**
 * @brief Simple software delay loop for 8051.
 * @param d Iteration count for loop execution.
 * @note At 11.0592 MHz, d = 30000 provides approximately 250-300 ms delay.
 */
void delay(unsigned int d) {
    unsigned int i;
    for (i = 0; i < d; i++);
}

#endif
