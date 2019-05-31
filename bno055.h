/*
 * bno055.h
 *
 * Danica Fujiwara & Spencer Shaw
 *
 * CPE 329-17/18 Spring 2019
 *
 */
#ifndef __BNO055_H__
#define __BNO055_H__

#include <stdint.h>

#define BNO_ADDR (0x28)

#define BNO_REG_MODE (0x3D)

#define BNO_MODE_IMU  (0b1000)
#define BNO_MODE_NDOF (0b1100)

#define BNO_REG_PITCH_MSB (0x1F)
#define BNO_REG_PITCH_LSB (0x1E)
#define BNO_REG_ROLL_MSB (0x1D)
#define BNO_REG_ROLL_LSB (0x1C)

void bno_init();

void bno_write(uint8_t reg, uint8_t value);
uint8_t bno_read(uint8_t reg);

void bno_read_angles(int16_t *x, int16_t *y);

#endif
