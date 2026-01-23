/*
    I2C Driver Implementation
    MCU: TM4C123GH6PM
*/

#include "i2c.h"
#include "tm4c123gh6pm.h"

struct i2c_handle_t {
    volatile uint32_t *I2C_BASE;
};

void decode_module_id(uint8_t module_id, 
                    volatile uint32_t **I2C_BASE,
                    uint8_t *RCGCI2C_BIT,
                    uint8_t *RCGCGPIO_BIT,
                    volatile uint32_t **GPIO_PORT_BASE,
                    uint8_t *GPIO_AFSEL_PINS,
                    uint32_t *GPIO_PCTL_PINS) {
    switch(module_id) {
        case(0):
            *I2C_BASE = (volatile uint32_t *)0x40020000;
            *RCGCI2C_BIT = 0x01;
            *RCGCGPIO_BIT = 0x02;
            *GPIO_PORT_BASE = (volatile uint32_t *)0x40005000;
            *GPIO_AFSEL_PINS = 0x0C;
            *GPIO_PCTL_PINS = (0x11 << 12) | (0x11 << 8);
                // pmc3
                // B2, B3
                // SCL, SDA
            break;
        case(1):
            *I2C_BASE = (volatile uint32_t *)0x40021000;
            *RCGCI2C_BIT = 0x02;
            *RCGCGPIO_BIT = 0x01;
            *GPIO_PORT_BASE = (volatile uint32_t *)0x40004000;
            *GPIO_AFSEL_PINS = 0xC0;
            *GPIO_PCTL_PINS = (0x11 << 28) | (0x11 << 24);
            // pmc3
            // A6, A7
            break;
        case(2):
            *I2C_BASE = (volatile uint32_t *)0x40022000;
            *RCGCI2C_BIT = 0x04;
            *RCGCGPIO_BIT = 0x10;
            *GPIO_PORT_BASE = (volatile uint32_t *)0x40024000;
            *GPIO_AFSEL_PINS = 0x30;
            *GPIO_PCTL_PINS = (0x11 << 20) | (0x11 << 16);
            // pmc3
            // E4, E5
            break;
        case(3):
            *I2C_BASE = (volatile uint32_t *)0x40023000;
            *RCGCI2C_BIT = 0x08;
            *RCGCGPIO_BIT = 0x08;
            *GPIO_PORT_BASE = (volatile uint32_t *)0x40007000;
            *GPIO_AFSEL_PINS = 0x03;
            *GPIO_PCTL_PINS = (0x11 << 4) | (0x11);
            // pmc3
            // D0, D1
            break;
        default:
            *I2C_BASE=0;
    }
}



void i2c_init(i2c_handle_t *out_handle, uint8_t module_id, uint32_t clock_speed_hz) {

    volatile uint8_t delay;
    uint8_t RCGCI2C_BIT;
    uint8_t RCGCGPIO_BIT;
    uint8_t GPIO_AFSEL_PINS;
    uint32_t GPIO_PCTL_PINS;
    volatile uint32_t *I2C_BASE, GPIO_PORT_BASE;
    decode_module_id(module_id, 
            &I2C_BASE, 
            &RCGCI2C_PIN, 
            &RCGCGPIO_BIT, 
            &GPIO_PORT_BASE,
            &GPIO_AFSEL_PINS,
            &GPIO_PCTL_PINS);
    // Enable i2c clock with RCGC12C
    SYSCTL_RCGCI2C_R |= RCGCI2C_BIT;

    // Enable GPIO Module Clock via RCGCGPIO
    SYSCTL_RCGCGPIO_R |= RCGCGPIO_BIT;
    delay = RCGCGPIO_BIT;

    // Enable appropriate GPIO pins via GPIOAFSEL
    *(GPIO_PORT_BASE + 0x420) |= GPIO_AFSEL_PINS;

    // Enable I2CSDA pin for open-drain operation
    *(GPIO_PORT_BASE + 0x50C) |= GPIO_AFSEL_PINS;

    // Config PMCn fields in GPIOPCTL register to assign I2C signals to appropriate pins
    *(GPIO_PORT_BASE + 0x52C) |= GPIO_PCTL_PINS;

    // Initialize I2C Master by writing I2CMCR register with 0x0000.0010
    *(I2C_BASE + 0x020) |= 0x00010000;

    // Set SCL clock speed of 100kbps
    *(I2C_BASE + 0x00C) |= 0x09;

    // return handle
    out_handle->I2C_BASE = I2C_BASE
}

void i2c_master_send(i2c_handle_t* handle, uint8_t slave_address, uint8_t *buf, size_t len) {
    // Write I2CMSA reg with address and write bit

    // place data in I2CMDR reg

    // Write I2CMCS for multiple byte transfer

    // Wait until transmission done by polling I2CMCS reg BUSBSY bit until it's cleared

    // Check ERROR bit in I2CMCS reg for ack

    // place data in i2CMDR reg

    // If i==len, transmit last bit and STOP
}

void i2c_master_receive(i2c_handle_t* handle, uint8_t slave_address, uint8_t *buf, size_t len);
