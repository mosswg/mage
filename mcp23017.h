#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

namespace mcp23017 {
	// I2C address
	static const uint8_t MCP_ADDR = 0x20;

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

	static const uint8_t INPUT = 0x0;

	void initialize();

	// Write the  bytes of buf to the specified register
	int reg_write (  i2c_inst_t *i2c,
			const uint addr,
			uint8_t *buf,
			const uint8_t nbytes);


	// Read byte(s) from specified register. If nbytes > 1, read from consecutive
	// registers.
	int reg_read(  i2c_inst_t *i2c,
			const uint addr,
			const uint8_t reg,
			uint8_t *buf,
			const uint8_t nbytes);


	// get the values in bank a
	uint8_t get_bank_a();
	// get the values in bank b
	uint8_t get_bank_b();
}
