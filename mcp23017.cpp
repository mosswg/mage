#include "mcp23017.h"

/*******************************************************************************
 * Function Definitions
 */

// Write the contents of buffer to the mcp23017.
// The first value in buf is the register
int mcp23017::reg_write(uint8_t *buf,
		const uint8_t nbytes) {
	if (!this->exists) {
		return 0;
	}

	int num_bytes_read = 0;

	// Check to make sure caller is sending 1 or more bytes
	if (nbytes < 1) {
		return 0;
	}

	// Write data to register(s) over I2C
	num_bytes_read = i2c_write_blocking(I2C, this->address, buf, nbytes, false);

	printf("nb: %02x\n", num_bytes_read);

	return num_bytes_read;
}

// Read byte(s) from specified register. If nbytes > 1, read from consecutive
// registers.
int mcp23017::reg_read(const uint8_t reg,
		uint8_t *buf,
		const uint8_t nbytes) {
	if (!this->exists) {
		return 0;
	}

	int num_bytes_read = 0;

	// Check to make sure caller is asking for 1 or more bytes
	if (nbytes < 1) {
		return 0;
	}

	// Read data from the register over I2C
	i2c_write_blocking(I2C, this->address, &reg, 1, true);
	num_bytes_read = i2c_read_blocking(I2C, this->address, buf, nbytes, false);

	return num_bytes_read;
}

uint8_t mcp23017::get_bank_a() {
	if (!this->exists) {
		return 0;
	}
	uint8_t data;

	reg_read(GPIOA,
			&data,
			1);

	return data;
}

uint8_t mcp23017::get_bank_b() {
	if (!this->exists) {
		return 0;
	}
	uint8_t data;

	reg_read(GPIOB,
			&data,
			1);

	return data;
}
