/*
   I2C Driver API
   Implements basic I2C functionality as a portable API
*/


// TODO: Will add ifdef clauses for MCU specific I2C features, if they include them


#ifndef I2C_H
#define I2C_H

#include <stdint.h>;


// Forward opaque declaration for handle
typedef struct i2c_handle_t i2c_handle_t;

// Initialization
// Input 1: Address of statically allocated handle for output
// Input 2: Module ID - HAL will map integers to matching MCU I2C modules
void i2c_init(i2c_handle_t *out_handle, uint8_t module_id, uint32_t clock_speed_hz);

// Master Send
// Input: Handle Pointer, Slave Address, data pointer, len of data to send in bytes
// 7-bit Slave Address should NOT be shifted left - give input with MSB = 0
void i2c_master_send(i2c_handle_t* handle, uint8_t slave_address, uint8_t *buf, size_t len);

// Master Receive
// Input: Handle Pointer Slave Address, pointer to 8-bit data buffer, len of data to read in bytes
void i2c_master_receive(i2c_handle_t* handle, uint8_t slave_address, uint8_t *buf, size_t len);

#endif
