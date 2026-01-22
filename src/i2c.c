/*
    I2C Driver Implementation
    MCU: TM4C123GH6PM
*/

#include "i2c.h"
#include "TM4C123GH6PM.h"

struct i2c_handle_t {
};

void i2c_init(i2c_handle_t *out_handle, uint8_t module_id, uint32_t clock_speed_hz);

void i2c_master_send(i2c_handle_t* handle, uint8_t slave_address, uint8_t *buf, size_t len);

void i2c_master_receive(i2c_handle_t* handle, uint8_t slave_address, uint8_t *buf, size_t len);
