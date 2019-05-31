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
    i2c_write(BNO_ADDR, 2);

    value = i2c_read_byte(BNO_ADDR);
    return value;
}

void bno_read_angles(int16_t* x, int16_t* y) {
    unsigned int val;
    val = bno_read(BNO_REG_ROLL_MSB);
    *x = val << 8;
    *x |= bno_read(BNO_REG_ROLL_LSB);

    val = bno_read(BNO_REG_PITCH_MSB);
    *y = val << 8;
    *y |= bno_read(BNO_REG_PITCH_LSB);
}
