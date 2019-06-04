/*
 * bno055.c
 *
 * Danica Fujiwara & Spencer Shaw
 *
 * CPE 329-17/18 Spring 2019
 *
 */

#include "bno055.h"
#include <stdint.h>
#include "delay.h"
#include "i2c.h"

void bno_init() {}

void bno_write(uint8_t reg, uint8_t value) {
    i2c_set_txdata(reg, value, 0);
    i2c_write(BNO_ADDR, 2);
    delay_ms(1, FREQ_48_MHZ);
}

uint8_t bno_read(uint8_t reg) {
    uint8_t value = 0;

    i2c_set_txdata(reg, 0, 0);
    i2c_write(BNO_ADDR, 1);
    value = i2c_read_byte(BNO_ADDR);
    delay_ms(1, FREQ_48_MHZ);
    return value;
}

#define I2C_DELAY_MS (1)

void bno_read_angles(int16_t* x_out, int16_t* y_out) {
    uint16_t x_high = bno_read(BNO_REG_ROLL_MSB);  // & 0xEF;
    // NOP
    uint16_t x_low = bno_read(BNO_REG_ROLL_LSB);
    // delay_ms(I2C_DELAY_MS, FREQ_48_MHZ);
    // NOP
    uint16_t y_high = bno_read(BNO_REG_PITCH_MSB);
    // delay_ms(I2C_DELAY_MS, FREQ_48_MHZ);
    // NOP
    uint16_t y_low = bno_read(BNO_REG_PITCH_LSB);

    uint16_t x = ((x_high << 8) | x_low) >> 6;
    uint16_t y = ((y_high << 8) | y_low) >> 6;

    *x_out = x;
    *y_out = y;

    // return;

    if (x > 511) {
        // Negative X
        // x = x & 0b11;
        if (x == 1023){
            *x_out = -1;
        }
        else{
            *x_out = -2;
        }
    } else {
        // Positive X
        if (x > 1) {
            *x_out = 2;
        } else {
            *x_out = x;
        }
    }

    if (y > 511) {
        // Negative Y
        if (y == 1023) {
            *y_out = -1;
        } else {
            *y_out = -2;
        }
    } else {
        // Positive y
        if (y == 0){
            *y_out = 0;
        }
        else if (y == 1) {
            *y_out = 1;
        } else {
            *y_out = 2;
        }
    }
}
