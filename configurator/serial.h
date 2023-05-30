#pragma once

#include "keycode.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>

namespace mage {

	const int CONFIG_PLANK_SIZE = mage_const::NUMBER_OF_KEYS_IN_PLANK + 4;
	const int CONFIG_CONTROL_SIZE = (mage_const::NUMBER_OF_KEYS_IN_CONTROL_GROUP * 2) + 4;

	const uint8_t config_high[CONFIG_PLANK_SIZE] = {
		'C', 'F', 'G', mage_const::STATE_HIGH,
		HID_KEY_ARROW_UP,    HID_KEY_GRAVE,        HID_KEY_F1,        HID_KEY_F2,    HID_KEY_F3,     HID_KEY_F4,    HID_KEY_F5,    HID_KEY_F6,        HID_KEY_F7,         HID_KEY_F8,       HID_KEY_F9,         HID_KEY_F10,         HID_KEY_BRACKET_LEFT,  HID_KEY_ESCAPE,
		HID_KEY_ARROW_LEFT,  HID_KEY_SPACE,        HID_KEY_1,         HID_KEY_2,     HID_KEY_3,      HID_KEY_4,     HID_KEY_5,     HID_KEY_6,         HID_KEY_7,          HID_KEY_8,        HID_KEY_9,          HID_KEY_0,           HID_KEY_BRACKET_RIGHT, HID_KEY_DELETE,
		HID_KEY_ARROW_RIGHT, HID_KEY_CONTROL_LEFT, HID_KEY_EQUAL,     HID_KEY_NONE,  HID_KEY_NONE,   HID_KEY_NONE,  HID_KEY_NONE,  HID_KEY_NONE,      HID_KEY_NONE,       HID_KEY_NONE,     HID_KEY_NONE,       HID_KEY_NONE,        HID_KEY_NONE,          HID_KEY_TAB,
		HID_KEY_ARROW_DOWN,  HID_KEY_SHIFT_LEFT,   HID_KEY_SEMICOLON, HID_KEY_NONE,  HID_KEY_NONE,   HID_KEY_NONE,  HID_KEY_NONE,  HID_KEY_NONE,      HID_KEY_NONE,       HID_KEY_NONE,     HID_KEY_NONE,       HID_KEY_NONE,        HID_KEY_EQUAL,         HID_KEY_SHIFT_RIGHT,
	};


	const uint8_t config_normal[CONFIG_PLANK_SIZE] = {
		'C', 'F', 'G', mage_const::STATE_NORMAL,
		HID_KEY_ARROW_UP,    HID_KEY_ESCAPE,       HID_KEY_1,         HID_KEY_2,     HID_KEY_3,      HID_KEY_4,     HID_KEY_5,     HID_KEY_6,         HID_KEY_7,          HID_KEY_8,        HID_KEY_9,          HID_KEY_0,           HID_KEY_BRACKET_RIGHT, HID_KEY_ESCAPE,
		HID_KEY_ARROW_LEFT,  HID_KEY_TAB,          HID_KEY_Q,         HID_KEY_W,     HID_KEY_E,      HID_KEY_R,     HID_KEY_T,     HID_KEY_Y,         HID_KEY_U,          HID_KEY_I,        HID_KEY_O,          HID_KEY_P,           HID_KEY_BRACKET_LEFT,  HID_KEY_DELETE,
		HID_KEY_ARROW_RIGHT, HID_KEY_CONTROL_LEFT, HID_KEY_A,         HID_KEY_S,     HID_KEY_D,      HID_KEY_F,     HID_KEY_G,     HID_KEY_H,         HID_KEY_J,          HID_KEY_K,        HID_KEY_L,          HID_KEY_SEMICOLON,   HID_KEY_APOSTROPHE,    HID_KEY_TAB,
		HID_KEY_ARROW_DOWN,  HID_KEY_SHIFT_LEFT,   HID_KEY_Z,         HID_KEY_X,     HID_KEY_C,      HID_KEY_V,     HID_KEY_B,     HID_KEY_N,         HID_KEY_M,          HID_KEY_COMMA,    HID_KEY_PERIOD,     HID_KEY_SLASH,       HID_KEY_MINUS,         HID_KEY_SHIFT_RIGHT,
	};

	const uint8_t config_low[CONFIG_PLANK_SIZE] = {
		'C', 'F', 'G', mage_const::STATE_LOW,
		HID_KEY_ARROW_UP,    HID_KEY_GRAVE,        HID_KEY_NONE,      HID_KEY_NONE,  HID_KEY_NONE,  HID_KEY_NONE,  HID_KEY_NONE,   HID_KEY_NONE,      HID_KEY_NONE,       HID_KEY_NONE,     HID_KEY_NONE,       HID_KEY_NONE,        HID_KEY_NONE,          HID_KEY_GRAVE,
		HID_KEY_ARROW_LEFT,  HID_KEY_SPACE,        HID_KEY_F1,        HID_KEY_F2,    HID_KEY_F3,    HID_KEY_F4,    HID_KEY_F5,     HID_KEY_F6,        HID_KEY_F7,         HID_KEY_F8,       HID_KEY_F9,         HID_KEY_F10,         HID_KEY_F11,           HID_KEY_F12,
		HID_KEY_ARROW_RIGHT, HID_KEY_CONTROL_LEFT, HID_KEY_ESCAPE,    HID_KEY_NONE,  HID_KEY_NONE,  HID_KEY_NONE,  HID_KEY_NONE,   HID_KEY_BACKSPACE, HID_KEY_ARROW_LEFT, HID_KEY_ARROW_UP, HID_KEY_ARROW_DOWN, HID_KEY_ARROW_RIGHT, HID_KEY_NONE,          HID_KEY_TAB,
		HID_KEY_ARROW_DOWN,  HID_KEY_SHIFT_LEFT,   HID_KEY_NONE,      HID_KEY_NONE,  HID_KEY_NONE,  HID_KEY_NONE,  HID_KEY_NONE,   HID_KEY_NONE,      HID_KEY_NONE,       HID_KEY_NONE,     HID_KEY_NONE,       HID_KEY_NONE,        HID_KEY_NONE,          HID_KEY_NONE,
	};

	const uint8_t config_control[CONFIG_CONTROL_SIZE] = {
		'C', 'F', 'G', mage_const::STATE_CONTROL,
		MAGE_KEY_RAISE, HID_KEY_GUI_LEFT, HID_KEY_CONTROL_LEFT, HID_KEY_SPACE,
		MAGE_KEY_LOWER, HID_KEY_BACKSPACE, HID_KEY_CONTROL_RIGHT, HID_KEY_ENTER,
	};



	const uint8_t save_seq[4] = {'S', 'A', 'V', 'E'};

	const uint8_t fetch_high_seq[4] = {'F', 'C', 'H', mage_const::STATE_HIGH};
	const uint8_t fetch_normal_seq[4] = {'F', 'C', 'H', mage_const::STATE_NORMAL};
	const uint8_t fetch_low_seq[4] = {'F', 'C', 'H', mage_const::STATE_LOW};
	const uint8_t fetch_control_seq[4] = {'F', 'C', 'H', mage_const::STATE_CONTROL};


	const uint8_t restore_seq[4] = {'R', 'S', 'T', 'R'};

	inline void save_config(int SERIAL_USB) {
		write( SERIAL_USB, save_seq, 4);
	}

	inline void restore_config(int SERIAL_USB) {
		write( SERIAL_USB, restore_seq, 4);
	}

	inline void write_default_config(int SERIAL_USB) {
		write( SERIAL_USB, config_high, CONFIG_PLANK_SIZE);
		write( SERIAL_USB, config_normal, CONFIG_PLANK_SIZE);
		write( SERIAL_USB, config_low, CONFIG_PLANK_SIZE);
		write( SERIAL_USB, config_control, CONFIG_CONTROL_SIZE);

		tcflush(SERIAL_USB, TCIOFLUSH);
	}


	inline void write_config(int SERIAL_USB, uint8_t* config) {
		uint8_t config_high[CONFIG_PLANK_SIZE] = {'C', 'F', 'G', mage_const::STATE_HIGH};
		uint8_t config_normal[CONFIG_PLANK_SIZE] = {'C', 'F', 'G', mage_const::STATE_NORMAL};
		uint8_t config_low[CONFIG_PLANK_SIZE] = {'C', 'F', 'G', mage_const::STATE_LOW};
		uint8_t config_control[CONFIG_CONTROL_SIZE] = {'C', 'F', 'G', mage_const::STATE_CONTROL};


		memcpy(config_high + 4, config, mage_const::NUMBER_OF_KEYS_IN_PLANK);
		memcpy(config_normal + 4, config + mage_const::NUMBER_OF_KEYS_IN_PLANK, mage_const::NUMBER_OF_KEYS_IN_PLANK);
		memcpy(config_low + 4, config + (2 * mage_const::NUMBER_OF_KEYS_IN_PLANK), mage_const::NUMBER_OF_KEYS_IN_PLANK);
		memcpy(config_control + 4, config + (3 * mage_const::NUMBER_OF_KEYS_IN_PLANK), mage_const::NUMBER_OF_KEYS_IN_CONTROL_GROUP * 2);

		write( SERIAL_USB, config_high, CONFIG_PLANK_SIZE);
		write( SERIAL_USB, config_normal, CONFIG_PLANK_SIZE);
		write( SERIAL_USB, config_low, CONFIG_PLANK_SIZE);
		write( SERIAL_USB, config_control, CONFIG_CONTROL_SIZE);

		tcflush(SERIAL_USB, TCIOFLUSH);
	}


	inline void write_change(int SERIAL_USB, uint8_t state, uint8_t column, uint8_t row, uint8_t key) {
		uint8_t data[8] = {
			'C', 'H', 'N', 'G',
			state, column, row, key,
		};
		write(SERIAL_USB, data, 8);
	}

	inline void fetch_config(int SERIAL_USB, uint8_t* out) {
		write(SERIAL_USB, fetch_high_seq, 4);
		read(SERIAL_USB, out, mage_const::NUMBER_OF_KEYS_IN_PLANK);

		write(SERIAL_USB, fetch_normal_seq, 4);
		read(SERIAL_USB, out + mage_const::NUMBER_OF_KEYS_IN_PLANK, mage_const::NUMBER_OF_KEYS_IN_PLANK);

		write(SERIAL_USB, fetch_low_seq, 4);
		read(SERIAL_USB, out + (mage_const::NUMBER_OF_KEYS_IN_PLANK * 2), mage_const::NUMBER_OF_KEYS_IN_PLANK);

		write(SERIAL_USB, fetch_control_seq, 4);
		read(SERIAL_USB, out + (mage_const::NUMBER_OF_KEYS_IN_PLANK * 3), mage_const::NUMBER_OF_KEYS_IN_CONTROL_GROUP * 2);

	}

	inline void print_config(uint8_t* config) {
		for (int i = 0; i < mage_const::CONFIG_SIZE; i++) {
			if (!(i % mage_const::NUMBER_OF_KEYS_IN_ROW)) {
				std::cout << "\n";
			}
			if (!(i % mage_const::NUMBER_OF_KEYS_IN_PLANK)) {
				std::cout << "\n";
			}
			std::cout << keycode_names[config[i]] << "\t";
		}
		std::cout << std::endl;
	}

	inline uint8_t name_to_keycode(std::string name) {
		for (char& c : name) {
			c = toupper(c);
		}
		return get_from_map(name_to_key, name);
	}

	inline uint8_t string_to_state(std::string name) {
		for (char& c : name) {
			c = toupper(c);
		}

		return get_from_map(name_to_state, name);


		return -1;
	}

}
