#include "mage.h"


int mage::get_pressed_keys(uint8_t* keys_buffer, int keys_buffer_size, uint8_t& mods) {
	this->state = STATE_NORMAL;
	for (int i = 0; i < KEY_POSITIONS_BUFFER_SIZE; i++) {
		key_positions_buffer[i] = 0;
	}
	int buffer_index = 0;
	if (!append_io1_bank_a_to_keys(key_positions_buffer, buffer_index, KEY_POSITIONS_BUFFER_SIZE, mods)) {
		return 0;
	}
	if (!append_io1_bank_b_to_keys(key_positions_buffer, buffer_index, KEY_POSITIONS_BUFFER_SIZE, mods)) {
		return 0;
	}

	if (!append_io2_bank_a_to_keys(key_positions_buffer, buffer_index, KEY_POSITIONS_BUFFER_SIZE, mods)) {
		return 0;
	}
	if (!append_io2_bank_b_to_keys(key_positions_buffer, buffer_index, KEY_POSITIONS_BUFFER_SIZE, mods)) {
		return 0;
	}

	if (!append_io3_bank_a_to_keys(key_positions_buffer, buffer_index, KEY_POSITIONS_BUFFER_SIZE, mods)) {
		return 0;
	}
	if (!append_io3_bank_b_to_keys(key_positions_buffer, buffer_index, KEY_POSITIONS_BUFFER_SIZE, mods)) {
		return 0;
	}

	if (!append_io4_bank_a_to_keys(key_positions_buffer, buffer_index, KEY_POSITIONS_BUFFER_SIZE, mods)) {
		return 0;
	}
	if (!append_io4_bank_b_to_keys(key_positions_buffer, buffer_index, KEY_POSITIONS_BUFFER_SIZE, mods)) {
		return 0;
	}

	append_keys_from_postions_to_buffer(keys_buffer, keys_buffer_size, mods);

	return buffer_index;
}



bool mage::append_io1_bank_a_to_keys(uint16_t* key_buffer, int& buffer_index, int key_buffer_size, uint8_t& mods) {
	uint8_t bank = io1.get_bank_a();

	if (bank & 0b1) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (6 << 8) | (0);
	}

	if (bank & 0b10) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (6 << 8) | (1);
	}

	if (bank & 0b100) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (6 << 8) | (2);
	}

	if (bank & 0b1000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (6 << 8) | (3);
	}

	if (bank & 0b10000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (-1 << 8) | (2);
	}

	if (bank & 0b100000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (-1 << 8) | (3);
	}

	if (bank & 0b1000000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (-1 << 8) | (1);
	}

	if (bank & 0b10000000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (-1 << 8) | (0);
	}

	return true;
}

bool mage::append_io1_bank_b_to_keys(uint16_t* key_buffer, int& buffer_index, int key_buffer_size, uint8_t& mods) {
	uint8_t bank = io1.get_bank_b();

	if (bank & 0b1) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (4 << 8) | (0);
	}

	if (bank & 0b10) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (4 << 8) | (1);
	}

	if (bank & 0b100) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (4 << 8) | (2);
	}

	if (bank & 0b1000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (4 << 8) | (3);
	}

	if (bank & 0b10000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (5 << 8) | (3);
	}

	if (bank & 0b100000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (5 << 8) | (2);
	}

	if (bank & 0b1000000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (5 << 8) | (1);
	}

	if (bank & 0b10000000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (5 << 8) | (0);
	}

	return true;
}

bool mage::append_io2_bank_a_to_keys(uint16_t* key_buffer, int& buffer_index, int key_buffer_size, uint8_t& mods) {
	uint8_t bank = io2.get_bank_a();

	if (bank & 0b1) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (2 << 8) | (0);
	}

	if (bank & 0b10) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (2 << 8) | (1);
	}

	if (bank & 0b100) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (2 << 8) | (2);
	}

	if (bank & 0b1000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (2 << 8) | (3);
	}

	if (bank & 0b10000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (3 << 8) | (0);
	}

	if (bank & 0b100000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (3 << 8) | (1);
	}

	if (bank & 0b1000000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (3 << 8) | (2);
	}

	if (bank & 0b10000000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (3 << 8) | (3);
	}


	return true;
}
bool mage::append_io2_bank_b_to_keys(uint16_t* key_buffer, int& buffer_index, int key_buffer_size, uint8_t& mods) {
	uint8_t bank = io2.get_bank_b();

	if (bank & 0b1) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (1 << 8) | (3);
	}

	if (bank & 0b10) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (1 << 8) | (2);
	}

	if (bank & 0b100) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (1 << 8) | (1);
	}

	if (bank & 0b1000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (1 << 8) | (0);
	}

	if (bank & 0b10000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (0 << 8) | (3);
	}

	if (bank & 0b100000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (0 << 8) | (2);
	}

	if (bank & 0b1000000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (0 << 8) | (1);
	}

	if (bank & 0b10000000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (0 << 8) | (0);
	}

	return true;
}

bool mage::append_io3_bank_a_to_keys(uint16_t* key_buffer, int& buffer_index, int key_buffer_size, uint8_t& mods) {
	uint8_t bank = io3.get_bank_a();

	if (bank & 0b1) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (11 << 8) | (0);
	}

	if (bank & 0b10) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (11 << 8) | (1);
	}

	if (bank & 0b100) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (11 << 8) | (2);
	}

	if (bank & 0b1000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (11 << 8) | (3);
	}

	if (bank & 0b10000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (10 << 8) | (0);
	}

	if (bank & 0b100000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (10 << 8) | (1);
	}

	if (bank & 0b1000000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (10 << 8) | (2);
	}

	if (bank & 0b10000000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (10 << 8) | (3);
	}

	return true;
}

bool mage::append_io3_bank_b_to_keys(uint16_t* key_buffer, int& buffer_index, int key_buffer_size, uint8_t& mods) {
	uint8_t bank = io3.get_bank_b();

	if (bank & 0b1) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (13 << 8) | (0);
	}

	if (bank & 0b10) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (13 << 8) | (1);
	}

	if (bank & 0b100) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (13 << 8) | (2);
	}

	if (bank & 0b1000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (13 << 8) | (3);
	}

	if (bank & 0b10000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (12 << 8) | (0);
	}

	if (bank & 0b100000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (12 << 8) | (1);
	}

	if (bank & 0b1000000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (12 << 8) | (2);
	}

	if (bank & 0b10000000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (12 << 8) | (3);
	}

	return true;
}

bool mage::append_io4_bank_a_to_keys(uint16_t* key_buffer, int& buffer_index, int key_buffer_size, uint8_t& mods) {
	uint8_t bank = io4.get_bank_a();

	if (bank & 0b1) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (7 << 8) | (0);
	}

	if (bank & 0b10) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (7 << 8) | (1);
	}

	if (bank & 0b100) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (7 << 8) | (2);
	}

	if (bank & 0b1000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (7 << 8) | (3);
	}

	if (bank & 0b10000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (-2 << 8) | (2);
	}

	if (bank & 0b100000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (-2 << 8) | (3);
	}

	if (bank & 0b1000000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (-2 << 8) | (1);
	}

	if (bank & 0b10000000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (-2 << 8) | (0);
	}

	return true;
}

bool mage::append_io4_bank_b_to_keys(uint16_t* key_buffer, int& buffer_index, int key_buffer_size, uint8_t& mods) {
	uint8_t bank = io4.get_bank_b();

	if (bank & 0b1) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (9 << 8) | (0);
	}

	if (bank & 0b10) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (9 << 8) | (1);
	}

	if (bank & 0b100) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (9 << 8) | (2);
	}

	if (bank & 0b1000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (9 << 8) | (3);
	}

	if (bank & 0b10000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (8 << 8) | (0);
	}

	if (bank & 0b100000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (8 << 8) | (1);
	}

	if (bank & 0b1000000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (8 << 8) | (2);
	}

	if (bank & 0b10000000) {
		if (buffer_index + 1 >= key_buffer_size) {
			return false;
		}
		key_buffer[buffer_index++] = (8 << 8) | (3);
	}

	return true;
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

	if (key == mage_config::KEY_RAISE || key == mage_config::KEY_LOWER) {
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

	if (key == mage_config::KEY_RAISE || key == mage_config::KEY_LOWER) {
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
	return mage_config::config_memory[mage_config::NUMBER_OF_KEYS_IN_PLANK * state + (row * mage_config::NUMBER_OF_KEYS_IN_ROW) + column];
}

uint8_t mage::get_control_group_key(uint8_t group, uint8_t index) {
	return mage_config::config_memory[mage_config::NUMBER_OF_KEYS_IN_PLANK * STATE_CONTROL + (mage_config::NUMBER_OF_KEYS_IN_CONTROL_GROUP * group) + index];
}



void mage::append_keys_from_postions_to_buffer(uint8_t* buffer, uint8_t buffer_size, uint8_t& mods) {
	int buffer_index = 0;

	// Check for state keys pressed
	for (int i = 0; i < KEY_POSITIONS_BUFFER_SIZE; i++) {
		if (key_positions_buffer[i] == 0) {
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

		if (key == mage_config::KEY_RAISE) {
			if (this->state == STATE_LOW) {
				this->state = STATE_NORMAL;
			}
			else {
				this->state = STATE_HIGH;
			}
		}
		else if (key == mage_config::KEY_LOWER) {
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
		if (key_positions_buffer[i] == 0) {
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
