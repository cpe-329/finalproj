/*
 * main.c
 *
 * Danica Fujiwara & Spencer Shaw
 *
 * CPE 329-17/18 Spring 2019
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include "msp.h"

//#include "button.h"
#include "bno055.h"
#include "delay.h"
#include "i2c.h"
#include "led.h"
#include "my_msp.h"
#include "uart.h"

#define FREQ FREQ_48_MHZ

unsigned char str_enter_reg[] = "Enter register address: ";
unsigned char str_reg[] = "Reg address: ";
unsigned char str_enter_val[] = "Enter value: ";
unsigned char str_val[] = "Value: ";
unsigned char str_reading[] = "Reading value ";
unsigned char str_writing[] = "Writing value ";
unsigned char str_to_reg[] = " to reg ";
unsigned char str_from_reg[] = " from reg ";
unsigned char str_done[] = "Done!";

volatile unsigned char char_data = '7';
volatile uint8_t got_fresh_char = FALSE;

int main(void) {
       unsigned int reg = 0;
       unsigned int value = 0;
    // volatile uint32_t i = 0;

    init(FREQ);

    led_on();
    // Read or Write to I2C Memory
    bno_write(BNO_REG_MODE, BNO_MODE_NDOF);

    delay_ms(200, FREQ_48_MHZ);
    led_off();

    delay_ms(200, FREQ_48_MHZ);

    while (1) {
        uart_write_nl();

        // Enter reg address
        uart_write_str(str_enter_reg, sizeof(str_enter_reg));
        reg = uart_get_int();
        uart_write_nl();
        uart_write_str(str_reg, sizeof(str_reg));
        uart_write_int(reg);
        uart_write_nl();

        // Enter Value
        uart_write_str(str_enter_val, sizeof(str_enter_val));
        value = uart_get_int();
        uart_write_nl();
        uart_write_str(str_val, sizeof(str_val));
        uart_write_int(value);
        uart_write_nl();

        // Output data
        uart_write_str(str_writing, sizeof(str_writing));
        uart_write_int(value);
        uart_write_str(str_to_reg, sizeof(str_to_reg));
        uart_write_int(reg);
        uart_write_nl();

        led_on();
        // Read or Write to I2C Memory
        bno_write(reg, value);

        delay_ms(200, FREQ_48_MHZ);
        led_off();

        delay_ms(200, FREQ_48_MHZ);

        uart_write_str(str_done, sizeof(str_done));
        uart_write_nl();
        uart_write_nl();
        
    }
}

// UART interrupt service routine
void EUSCIA0_IRQHandler(void) {
    if (EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG) {
        if (has_new) {
            return;
        }
        // Check if the TX buffer is empty first
        while (!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG)) {
        }

        new_char = EUSCI_A0->RXBUF;
        has_new = TRUE;
        // Echo the received character back
        EUSCI_A0->TXBUF = new_char;
        // delay_ms(10, FREQ);
    }
}
