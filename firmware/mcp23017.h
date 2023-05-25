#pragma once

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

class mcp23017 {
	public:

	/// Constants
	// Registers
	static const uint8_t REG_DEVID = 0x00;
	static const uint8_t REG_POWER_CTL = 0x2D;
	static const uint8_t REG_DATAX0 = 0x32;

	// Other constants
	static const uint8_t DEVID = 0xE5;
	static const uint8_t IODIRA = 0x00;
	static const uint8_t IODIRB = 0x01;
	static const uint8_t IOCONA = 0x0a;
	static const uint8_t IOCONB = 0x0b;
	static const uint8_t GPIOA = 0x12;
	static const uint8_t GPIOB = 0x13;

	static const uint8_t IODIR_INPUT = 0x0;


	// i2c values
	static const uint SDA_PIN = 6;
	static const uint SCL_PIN = 7;
	static constexpr i2c_inst_t* I2C = i2c1;

	/// Member values
	uint8_t address;
	bool exists = true;

	mcp23017(const uint8_t address) : address(address) {

		// Buffer to store raw reads
		uint8_t buffer[2];

		//Initialize I2C port at 400 kHz
		i2c_init(I2C, 400 * 1000);

		// Initialize I2C pins
		gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
		gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);

		// Check if the chip exists
		uint8_t iodira = 0;
		reg_read(IODIRA, &iodira, 1);
		if (iodira != 0b11111111) {
			//exists = true;
			//return;
		}

		// Initalize chip
		buffer[0] = IODIRA;
		buffer[1] = IODIR_INPUT;
		reg_write(buffer,
				2);


		buffer[0] = IODIRB;
		buffer[1] = IODIR_INPUT;
		reg_write(buffer,
				2);
	}

	// Write the  bytes of buf to the specified register
	int reg_write (uint8_t *buf,
			const uint8_t nbytes);


	// Read byte(s) from specified register. If nbytes > 1, read from consecutive
	// registers.
	int reg_read(const uint8_t reg,
			uint8_t *buf,
			const uint8_t nbytes);


	// get the values in bank a
	uint8_t get_bank_a();
	// get the values in bank b
	uint8_t get_bank_b();
};
