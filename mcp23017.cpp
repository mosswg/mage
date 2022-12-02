#include "mcp23017.h"

/*******************************************************************************
 * Function Definitions
 */

namespace mcp23017 {
	i2c_inst_t *i2c = i2c0;

	// Write 1 byte to the specified register
	int reg_write(  i2c_inst_t *i2c,
			const uint addr,
			uint8_t *buf,
			const uint8_t nbytes) {

		int num_bytes_read = 0;

		// Check to make sure caller is sending 1 or more bytes
		if (nbytes < 1) {
			return 0;
		}

		// Write data to register(s) over I2C
		num_bytes_read = i2c_write_blocking(i2c, addr, buf, nbytes, false);

		printf("nb: %02x\n", num_bytes_read);

		return num_bytes_read;
	}

	// Read byte(s) from specified register. If nbytes > 1, read from consecutive
	// registers.
	int reg_read(  i2c_inst_t *i2c,
			const uint addr,
			const uint8_t reg,
			uint8_t *buf,
			const uint8_t nbytes) {

		int num_bytes_read = 0;

		// Check to make sure caller is asking for 1 or more bytes
		if (nbytes < 1) {
			return 0;
		}

		// Read data from register(s) over I2C
		i2c_write_blocking(i2c, addr, &reg, 1, true);
		num_bytes_read = i2c_read_blocking(i2c, addr, buf, nbytes, false);

		return num_bytes_read;
	}

	void initialize() {

		// Pins
		const uint sda_pin = 24;
		const uint scl_pin = 25;

		// Buffer to store raw reads
		uint8_t buffer[2];

		//Initialize I2C port at 400 kHz
		i2c_init(i2c, 400 * 1000);

		// Initialize I2C pins
		gpio_set_function(sda_pin, GPIO_FUNC_I2C);
		gpio_set_function(scl_pin, GPIO_FUNC_I2C);

		// Initalize chip
		buffer[0] = IODIRA;
		buffer[1] = INPUT;
		reg_write(  i2c,
				MCP_ADDR,
				buffer,
				2);


		buffer[0] = IODIRB;
		buffer[1] = INPUT;
		reg_write(  i2c,
				MCP_ADDR,
				buffer,
				2);
	}

	uint8_t get_bank_a() {
		uint8_t data;

		reg_read(  i2c,
				MCP_ADDR,
				GPIOA,
				&data,
				1);

		return data;
	}

	uint8_t get_bank_b() {
		uint8_t data;

		reg_read(  i2c,
				MCP_ADDR,
				GPIOB,
				&data,
				1);

		return data;
	}
}
