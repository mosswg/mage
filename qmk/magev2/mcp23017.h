#pragma once

#include <hal_i2c.h>
#include "i2c_master.h"


/// Constants
// Registers
const uint8_t REG_DEVID = 0x00;
const uint8_t REG_POWER_CTL = 0x2D;
const uint8_t REG_DATAX0 = 0x32;

// Other constants
const uint8_t DEVID = 0xE5;
const uint8_t IODIRA = 0x00;
const uint8_t IODIRB = 0x01;
const uint8_t IOCONA = 0x0a;
const uint8_t IOCONB = 0x0b;
const uint8_t GPIOA = 0x12;
const uint8_t GPIOB = 0x13;
const uint8_t GPPUA = 0xC;
const uint8_t GPPUB = 0xD;

const uint8_t IODIR_INPUT = 0x0;
const uint8_t PULL_DOWN = 0x00;
const uint8_t PULL_UP = 0xff;

#define MCP23017_I2C_TIMEOUT 1000
#define I2C_WRITE 0x00
#define I2C_READ 0x01

typedef struct {
	/// Member values
	uint8_t address;
	uint8_t address_write;
	uint8_t address_read;
	i2c_status_t current_status;
} mcp23017;


// Write the  bytes of buf to the specified register
i2c_status_t reg_write (mcp23017* io, uint8_t *buf, const uint8_t nbytes) {
	// Check to make sure caller is sending 1 or more bytes
	if (nbytes < 1) {
		return 0;
	}

	// Write data to register(s) over I2C
	io->current_status = i2c_start(io->address_write);
	io->current_status = i2c_transmit(io->address_write, buf, nbytes, MCP23017_I2C_TIMEOUT);
	i2c_stop();

	return io->current_status;
}


// Read byte(s) from specified register. If nbytes > 1, read from consecutive
// registers.
i2c_status_t reg_read(mcp23017* io, const uint8_t reg, uint8_t *buf, const uint8_t nbytes) {
	// Check to make sure caller is asking for 1 or more bytes
	if (nbytes < 1) {
		return 0;
	}

	// Read data from the register over I2C
	io->current_status = i2c_start(io->address_write);
	io->current_status = i2c_transmit(io->address_write, &reg, 1, MCP23017_I2C_TIMEOUT);
	io->current_status = i2c_start(io->address_read);
	io->current_status = i2c_receive(io->address_read, buf, nbytes, MCP23017_I2C_TIMEOUT);
	i2c_stop();

	return io->current_status;
}



mcp23017 make_mcp23017(uint8_t address) {
	mcp23017 out = {address,
					((address << 1) | I2C_WRITE),
					((address << 1) | I2C_READ),
					0
	};

	// Buffer to store raw reads
	uint8_t buffer[2];

	// Initalize chip
	buffer[0] = IODIRA;
	buffer[1] = IODIR_INPUT;
	reg_write(&out, buffer,
			  2);


	buffer[0] = IODIRB;
	buffer[1] = IODIR_INPUT;
	reg_write(&out, buffer,
			  2);

	//seems like A pull ups also needed
	buffer[0] = GPPUA;
	buffer[1] = PULL_UP;
	reg_write(&out, buffer,
			  2);
	//set B pull ups ON
	buffer[0] = GPPUB;
	buffer[1] = PULL_UP;
	reg_write(&out, buffer,
			  2);

	return out;
}

// get the values in bank a
uint8_t get_bank_a(mcp23017* io) {
	uint8_t data = 0;

	/// We don't care about the status (assume success)
	(void)reg_read(io, GPIOA,
				   &data,
				   1);

	return data;
}
// get the values in bank b
uint8_t get_bank_b(mcp23017* io) {
	uint8_t data;

	/// We don't care about the status (assume success)
	(void)reg_read(io, GPIOB,
				   &data,
				   1);

	return data;
}
