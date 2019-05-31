/*
 * i2c.h
 *
 * Danica Fujiwara & Spencer Shaw
 *
 * CPE 329-17/18 Spring 2019
 *
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>
#include "my_msp.h"

#define I2C_SCL_PIN P1_7
#define I2C_SDA_PIN P1_6
#define I2C_PINS (I2C_SCL_PIN | I2C_SDA_PIN)

#define I2C_TX_DATA_MAX_SIZE (3)

void i2c_init(uint8_t slave_addr);
void i2c_set_txdata(uint8_t d1, uint8_t d2, uint8_t d3);
void i2c_write(uint8_t addr, unsigned int data_size);
uint8_t i2c_read_byte(uint8_t addr);

#endif /* I2C_H_ */
