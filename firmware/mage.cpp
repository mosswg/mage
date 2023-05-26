#include "mage.h"


int mage::get_pressed_keys(uint8_t* keys_buffer, int keys_buffer_size, uint8_t& mods) {
	this->state = STATE_NORMAL;
	for (int i = 0; i < KEY_POSITIONS_BUFFER_SIZE; i++) {
		key_positions_buffer[i] = -1;
	}
	int buffer_index = 0;


	for (int io_expander = 0; io_expander < mage_const::NUMBER_OF_IO_EXPANDERS; io_expander++) {
		uint8_t bank = io_expanders[io_expander].get_bank_a();
		uint8_t bank_b = io_expanders[io_expander].get_bank_b();

		/// Go through each value in each bank
		for (int b = 0; b < 2; b++) {
			for (int bank_index = 0; bank_index < 8; bank_index++) {
				if (bank & (0b1 << bank_index)) {
					if (buffer_index + 1 >= keys_buffer_size) {
						return 0;
					}
					key_positions_buffer[buffer_index++] = mage_config::get_column_and_row_from_io_expander(io_expander, b, bank_index);
					#if 0
					tud_cdc_write_str("Adding key at: ");
					tud_cdc_write_str(std::to_string(io_expander * mage_const::NUMBER_OF_KEYS_IN_IO_EXPANDER + b * 8 + bank_index).c_str());
					tud_cdc_write_str(": ");
					tud_cdc_write_str(std::to_string(key_positions_buffer[buffer_index - 1] >> 8).c_str());
					tud_cdc_write_str(", ");
					tud_cdc_write_str(std::to_string(key_positions_buffer[buffer_index - 1] & 0xff).c_str());
					tud_cdc_write_str("\r\n");
					#endif
				}
			}
			/// Swap to second bank
			bank = bank_b;
		}
	}

	append_keys_from_postions_to_buffer(keys_buffer, keys_buffer_size, mods);

	return buffer_index;
}



void mage::error_out_buffer(uint8_t* key_buffer, int key_buffer_size) {
	for (int i = 0; i < key_buffer_size; i++) {
		/// TODO: Make sure that this should be 0 and not something else.
		key_buffer[i] = 0;
	}
}



uint8_t mage::key_to_modifier(uint8_t key) {
	switch (key) {
		case HID_KEY_CONTROL_LEFT:
			return KEYBOARD_MODIFIER_LEFTCTRL;
		case HID_KEY_SHIFT_LEFT:
			return KEYBOARD_MODIFIER_LEFTSHIFT;
		case HID_KEY_ALT_LEFT:
			return KEYBOARD_MODIFIER_LEFTALT;
		case HID_KEY_GUI_LEFT:
			return KEYBOARD_MODIFIER_LEFTGUI;
		case HID_KEY_CONTROL_RIGHT:
			return KEYBOARD_MODIFIER_RIGHTCTRL;
		case HID_KEY_SHIFT_RIGHT:
			return KEYBOARD_MODIFIER_RIGHTSHIFT;
		case HID_KEY_ALT_RIGHT:
			return KEYBOARD_MODIFIER_RIGHTALT;
		case HID_KEY_GUI_RIGHT:
			return KEYBOARD_MODIFIER_RIGHTGUI;
		default:
			return 0;
	}
}

/**
 * The left side is columns 0-6 and the right side is 7-13
 *
 * Appends the key in the grid to the buffer or mods.
 */
int mage::append_plank_key(uint8_t* key_buffer, int buffer_index, uint8_t& mods, uint8_t column, uint8_t row) {
	if (column >= 14 || row >= 4) {
		return 0;
	}

	uint8_t key = get_plank_key(column, row, state);

	if (key == mage_const::KEY_RAISE || key == mage_const::KEY_LOWER) {
		return 0;
	}

	// Modifier keys
	if (key >= 0xe0 && key <= 0xe7) {
		mods |= key_to_modifier(key);
		return 0;
	}

	key_buffer[buffer_index] = key;

	return 1;
}



/**
 * Group indexs are:
 * [ 0 ] [ 1 ] [ 2 ]
 *     [   3   ]
 *
 * Appends the key in the group to the buffer or mods.
 */
int mage::append_control_group_key(uint8_t* key_buffer, int buffer_index, uint8_t& mods, uint8_t group, uint8_t index) {
	if (group >= 2 || index >= 4) {
		return 0;
	}


	uint8_t key = get_control_group_key(group, index);

	if (key == mage_const::KEY_RAISE || key == mage_const::KEY_LOWER) {
		return 0;
	}

	// Modifier keys
	if (key >= 0xe0 && key <= 0xe7) {
		mods |= key_to_modifier(key);
		return 0;
	}

	key_buffer[buffer_index] = key;

	return 1;
}


uint8_t mage::get_plank_key(uint8_t column, uint8_t row, uint8_t state) {
	return mage_config::config_memory[mage_const::NUMBER_OF_KEYS_IN_PLANK * state + (row * mage_const::NUMBER_OF_KEYS_IN_ROW) + column];
}

uint8_t mage::get_control_group_key(uint8_t group, uint8_t index) {
	return mage_config::config_memory[mage_const::NUMBER_OF_KEYS_IN_PLANK * STATE_CONTROL + (mage_const::NUMBER_OF_KEYS_IN_CONTROL_GROUP * group) + index];
}



void mage::append_keys_from_postions_to_buffer(uint8_t* buffer, uint8_t buffer_size, uint8_t& mods) {
	int buffer_index = 0;

	// Check for state keys pressed
	for (int i = 0; i < KEY_POSITIONS_BUFFER_SIZE; i++) {
		if (key_positions_buffer[i] == -1) {
			break;
		}


		uint16_t key_position = key_positions_buffer[i];
		int8_t column = (int8_t)(key_position >> 8);
		uint8_t row = (uint8_t)(key_position & 0xff);

		uint8_t key = 0;
		if (column < 0) {
			key = this->get_control_group_key(~column, row);
		}
		else {
			key = this->get_plank_key(column, row, STATE_NORMAL);
		}

		if (key == mage_const::KEY_RAISE) {
			if (this->state == STATE_LOW) {
				this->state = STATE_NORMAL;
			}
			else {
				this->state = STATE_HIGH;
			}
		}
		else if (key == mage_const::KEY_LOWER) {
			if (this->state == STATE_HIGH) {
				this->state = STATE_NORMAL;
			}
			else {
				this->state = STATE_LOW;
			}
		}
	}

	// Get the rest of the keys with the modified state
	for (int i = 0; i < KEY_POSITIONS_BUFFER_SIZE; i++) {
		if (key_positions_buffer[i] == -1) {
			break;
		}

		uint16_t key_position = key_positions_buffer[i];
		int8_t column = (int8_t)(key_position >> 8);
		uint8_t row = (uint8_t)(key_position & 0xff);

		if (column < 0) {
			buffer_index += append_control_group_key(buffer, buffer_index, mods, ~column, row);
		}
		else {
			buffer_index += append_plank_key(buffer, buffer_index, mods, column, row);
		}
	}
}
