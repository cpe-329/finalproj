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
#include "i2c.h"

void bno_init() {}

void bno_write(uint8_t reg, uint8_t value) {
    i2c_set_txdata(reg, value, 0);
    i2c_write(BNO_ADDR, 2);
}

uint8_t bno_read(uint8_t reg) {
    uint8_t value = 0;

    i2c_set_txdata(reg, 0, 0);
    i2c_write(BNO_ADDR, 1);
    value = i2c_read_byte(BNO_ADDR);
    return value;
}

void bno_read_angles(int16_t* x, int16_t* y) {
    *x = bno_read(BNO_REG_ROLL_MSB) & -1;
    // int16_t x_low = bno_read(BNO_REG_ROLL_LSB);
    *y = bno_read(BNO_REG_PITCH_MSB);
    // int16_t y_low = bno_read(BNO_REG_PITCH_LSB);

    if (*x > 128) {
        *x = *x - 255;
    }
    if (*x > 2) {
        *x = 2;
    } else if (*x < -2) {
        *x = -2;
    }

    if (*y > 128) {
        *y = *y - 255;
    }
    *y = 0 - *y;

    if (*y > 2) {
        *y = 2;
    } else if (*y < -2) {
        *y = -2;
    }
}
