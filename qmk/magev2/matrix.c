/*
  Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>
  2020 Pierre Chevalier <pierrechevalier83@gmail.com>
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * This code was heavily inspired by the ergodox_ez keymap, and modernized
 * to take advantage of the quantum.h microcontroller agnostics gpio control
 * abstractions and use the macros defined in config.h for the wiring as opposed
 * to repeating that information all over the place.
 */

#include QMK_KEYBOARD_H
#include "print.h"
#include "debug.h"
#include "mcp23017.h"
#include "mage_const.h"

// For a better understanding of the i2c protocol, this is a good read:
// https://www.robot-electronics.co.uk/i2c-tutorial

bool i2c_initialized = 0;
mcp23017 io1;
mcp23017 io2;
mcp23017 io3;
mcp23017 io4;
mcp23017* io_expanders[4] = { &io1, &io2, &io3, &io4 };

/// This is a small optimization to allow for a 1d array rather than a 2d array.
/// COMBINED_POS = ROW << 8 | COLUMN
///
/// ROW = (COMBINED_POS >> 8) & 0xff
/// COLUMN = COMBINED_POS & 0xff
///
 // * Group indexs are:
 // * [ 0 ] [ 1 ] [ 2 ]
 // *     [   3   ]
const uint16_t io_expander_column_row_mappings[mage_const_NUMBER_OF_KEYS_IN_IO_EXPANDER * mage_const_NUMBER_OF_IO_EXPANDERS] = {
	/* io0-a */ ( 2 << 8) | (0), ( 2 << 8) | (1), ( 2 << 8) | (2), ( 2 << 8) | (3), ( 3 << 8) | (0), ( 3 << 8) | (1), ( 3 << 8) | (2), ( 3 << 8) | (3), /* io0-b */ ( 0 << 8) | (0), ( 0 << 8) | (1), ( 0 << 8) | (2), ( 0 << 8) | (3), ( 1 << 8) | (0), ( 1 << 8) | (1), ( 1 << 8) | (2), ( 1 << 8) | (3),
	/* io1-a */ ( 6 << 8) | (0), ( 6 << 8) | (1), ( 6 << 8) | (2), ( 6 << 8) | (3), ( 6 << 8) | (4), ( 5 << 8) | (5), ( 5 << 8) | (4), ( 4 << 8) | (4), /* io1-b */ ( 4 << 8) | (0), ( 4 << 8) | (1), ( 4 << 8) | (2), ( 4 << 8) | (3), ( 5 << 8) | (0), ( 5 << 8) | (1), ( 5 << 8) | (2), ( 5 << 8) | (3),
	/* io2-a */ (11 << 8) | (0), (11 << 8) | (1), (11 << 8) | (2), (11 << 8) | (3), (10 << 8) | (0), (10 << 8) | (1), (10 << 8) | (2), (10 << 8) | (3), /* io2-b */ (13 << 8) | (0), (13 << 8) | (1), (13 << 8) | (2), (13 << 8) | (3), (12 << 8) | (0), (12 << 8) | (1), (12 << 8) | (2), (12 << 8) | (3),
	/* io3-a */ ( 7 << 8) | (0), ( 7 << 8) | (1), ( 7 << 8) | (2), ( 7 << 8) | (3), ( 7 << 8) | (4), ( 8 << 8) | (5), ( 8 << 8) | (4), ( 9 << 8) | (4), /* io3-b */ ( 9 << 8) | (0), ( 9 << 8) | (1), ( 9 << 8) | (2), ( 9 << 8) | (3), ( 8 << 8) | (0), ( 8 << 8) | (1), ( 8 << 8) | (2), ( 8 << 8) | (3),
};


uint8_t init_mcp23017(void) {
	print("init mcp23017\n");

	// I2C subsystem
	if (i2c_initialized == 0) {
		i2c_init();  // on pins D(1,0)
		i2c_initialized = true;
		wait_ms(MCP23017_I2C_TIMEOUT);
	}


	io1 = make_mcp23017(0x20);
	io2 = make_mcp23017(0x21);
	io3 = make_mcp23017(0x22);
	io4 = make_mcp23017(0x23);

	print("mcp23017 init complete\n");

	return io1.current_status | io2.current_status | io3.current_status | io4.current_status;
}


void matrix_init(void) {
	debug_enable = true;
	print("matrix_init_custom\n");

	init_mcp23017();
}

uint16_t get_column_and_row_from_io_expander(uint8_t expander, bool bank_b, uint8_t index) {
	return io_expander_column_row_mappings[(mage_const_NUMBER_OF_KEYS_IN_IO_EXPANDER * expander) + (bank_b * 8) + index];
}

void print_row(uint8_t row, matrix_row_t key_row) {
	print_hex8(row);
	print(": ");
	print_bin_reverse16(key_row);
	print("\n");
}

void print_bank(uint8_t bank) {
	print_bin_reverse8(bank);
	print("\n");
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
	bool changed = false;
	for (int io_expander = 0; io_expander < mage_const_NUMBER_OF_IO_EXPANDERS; io_expander++) {
		uint8_t bank = get_bank_a(io_expanders[io_expander]);
		uint8_t bank_b = get_bank_b(io_expanders[io_expander]);

		/// Go through each value in each bank
		for (int b = 0; b < 2; b++) {
			for (int bank_index = 0; bank_index < 8; bank_index++) {
				uint16_t position = get_column_and_row_from_io_expander(io_expander, b, bank_index);
				uint8_t column = position & 0xff;
				uint8_t row = (position >> 8) & 0xff;
				matrix_row_t key_row = current_matrix[column];
				matrix_row_t new_key_row;
				bool adding = false;
				if (bank & (0b1 << bank_index)) {
					new_key_row = key_row | (0b1 << row);
					adding = true;
				}
				else {
					new_key_row = key_row & (~(0b1 << row));
				}
				if (key_row == new_key_row) {
					// Ignore if no change
					continue;
				}
				if (adding) {
					print("Adding key: ");
				}
				else {
					print("Removing key: ");
				}

				uprintf("col: %2u, row: %2u\n", column, row);
				changed = true;
				current_matrix[column] = new_key_row;
			}
			/// Swap to second bank
			bank = bank_b;
		}
	}

	return changed;
}
