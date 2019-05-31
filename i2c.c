/*
 * i2c.c
 *
 * Danica Fujiwara & Spencer Shaw
 *
 * CPE 329-17/18 Spring 2019
 *
 */

#include "i2c.h"
#include <stdint.h>
#include "delay.h"
#include "led.h"
#include "msp.h"

volatile uint8_t TXData[I2C_TX_DATA_MAX_SIZE] = {0};
// volatile uint8_t TXDataPointer = 0;
volatile uint8_t TXDataSize = 0;

volatile uint8_t RXData = 0;

uint8_t data_written = FALSE;
uint8_t data_read = FALSE;

void i2c_init(uint8_t slave_addr) {
    rgb_set(RGB_RED);

    P1->SEL0 |= I2C_PINS;  // Set I2C pins of eUSCI_B0
    // Enable eUSCIB0 interrupt in NVIC module
    NVIC->ISER[0] = 1 << ((EUSCIB0_IRQn)&31);
    // Configure USCI_B0 for I2C mode
    EUSCI_B0->CTLW0 |= EUSCI_A_CTLW0_SWRST;       // Software reset enabled
    EUSCI_B0->CTLW0 = EUSCI_A_CTLW0_SWRST |       // Remain eUSCI in reset mode
                      EUSCI_B_CTLW0_MODE_3 |      // I2C mode
                      EUSCI_B_CTLW0_MST |         // Master mode
                      EUSCI_B_CTLW0_SYNC |        // Sync mode
                      EUSCI_B_CTLW0_SSEL__SMCLK;  // SMCLK
    EUSCI_B0->BRW = 30;                       // baudrate = SMCLK / 30 = 100kHz
    EUSCI_B0->I2CSA = slave_addr;             // Slave address
    EUSCI_B0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;  // Release eUSCI from reset
    EUSCI_B0->IE |= EUSCI_A_IE_RXIE |         // Enable receive interrupt
                    EUSCI_A_IE_TXIE;

    delay_ms(500, FREQ_48_MHZ);
    rgb_clear(RGB_RED);
}

void i2c_set_txdata(uint8_t d1, uint8_t d2, uint8_t d3) {
    TXData[0] = d1;
    TXData[1] = d2;
    TXData[2] = d3;
}

void i2c_write(uint8_t addr, unsigned int data_size) {
    uint8_t i = 0;
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TR;     // Set transmit mode (write)
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TXSTT;  // I2C start condition

    for (i = 0; i < TXDataSize; i++) {
        while (!data_written)
            ;  // Wait for EEPROM address to transmit
        data_written = FALSE;
        EUSCI_B0->TXBUF =
            TXData[i];  // Send the high byte of the memory address
    }

    while (!data_written)
        ;  // Wait for the transmit to complete
    data_written = 0;

    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TXSTP;  // I2C stop condition
}

uint8_t i2c_read_byte(uint8_t addr) {
    uint8_t ReceiveByte;

    EUSCI_B0->CTLW0 &= ~EUSCI_B_CTLW0_TR;    // Set receive mode (read)
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TXSTT;  // I2C start condition (restart)
    // Wait for start to be transmitted
    while ((EUSCI_B0->CTLW0 & EUSCI_B_CTLW0_TXSTT))
        ;
    // set stop bit to trigger after first byte
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TXSTP;
    while (!data_read)
        ;  // Wait to receive a byte
    data_read = 0;
    ReceiveByte = EUSCI_B0->RXBUF;  // Read byte from the buffer
    return ReceiveByte;
}

// I2C Interrupt Service Routine
void EUSCIB0_IRQHandler(void) {
    if (EUSCI_B0->IFG & EUSCI_B_IFG_TXIFG0)  // Check if transmit complete
    {
        EUSCI_B0->IFG &= ~EUSCI_B_IFG_TXIFG0;  // Clear interrupt flag
        data_written = TRUE;                   // Set global flag
    }
    if (EUSCI_B0->IFG & EUSCI_B_IFG_RXIFG0)  // Check if receive complete
    {
        EUSCI_B0->IFG &= ~EUSCI_B_IFG_RXIFG0;  // Clear interrupt flag
        data_read = TRUE;                      // Set global flag
    }
}
