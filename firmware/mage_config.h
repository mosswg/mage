#pragma once
#include <tusb.h>
#include "pico/stdlib.h"
#include "hardware/flash.h"
#include <string>

namespace mage_config {

#define CONFIG_FLASH_OFFSET (32 * FLASH_SECTOR_SIZE)
	inline const int NUMBER_OF_KEYS_IN_ROW = 14;
	inline const int NUMBER_OF_KEYS_IN_COLUMN = 4;
	inline const int NUMBER_OF_KEYS_IN_PLANK = NUMBER_OF_KEYS_IN_ROW * NUMBER_OF_KEYS_IN_COLUMN;
	inline const int NUMBER_OF_KEYS_IN_CONTROL_GROUP = 4;
	inline const int CONFIG_SIZE = (NUMBER_OF_KEYS_IN_PLANK * 3) + (NUMBER_OF_KEYS_IN_CONTROL_GROUP * 2);
	inline const uint8_t *config_flash = (const uint8_t *) (XIP_BASE + CONFIG_FLASH_OFFSET);

	inline const uint8_t KEY_RAISE = 0xa5;
	inline const uint8_t KEY_LOWER = 0xa6;

	inline uint8_t config_memory[FLASH_PAGE_SIZE];


	/**
	inline const uint8_t default_config[CONFIG_SIZE] = {
		HID_KEY_ARROW_UP,    HID_KEY_GRAVE,        HID_KEY_F1,        HID_KEY_F2,    HID_KEY_F3,     HID_KEY_F4,    HID_KEY_F5,    HID_KEY_F6,        HID_KEY_F7,         HID_KEY_F8,       HID_KEY_F9,         HID_KEY_F10,         HID_KEY_BRACKET_LEFT,  HID_KEY_ESCAPE,
		HID_KEY_ARROW_LEFT,  HID_KEY_SPACE,        HID_KEY_1,         HID_KEY_2,     HID_KEY_3,      HID_KEY_4,     HID_KEY_5,     HID_KEY_6,         HID_KEY_7,          HID_KEY_8,        HID_KEY_9,          HID_KEY_0,           HID_KEY_BRACKET_RIGHT, HID_KEY_DELETE,
		HID_KEY_ARROW_RIGHT, HID_KEY_CONTROL_LEFT, HID_KEY_EQUAL,     HID_KEY_NONE,  HID_KEY_NONE,   HID_KEY_NONE,  HID_KEY_NONE,  HID_KEY_NONE,      HID_KEY_NONE,       HID_KEY_NONE,     HID_KEY_NONE,       HID_KEY_NONE,        HID_KEY_NONE,          HID_KEY_TAB,
		HID_KEY_ARROW_DOWN,  HID_KEY_SHIFT_LEFT,   HID_KEY_SEMICOLON, HID_KEY_NONE,  HID_KEY_NONE,   HID_KEY_NONE,  HID_KEY_NONE,  HID_KEY_NONE,      HID_KEY_NONE,       HID_KEY_NONE,     HID_KEY_NONE,       HID_KEY_NONE,        HID_KEY_EQUAL,         HID_KEY_SHIFT_RIGHT,

		HID_KEY_ARROW_UP,    HID_KEY_ESCAPE,       HID_KEY_1,         HID_KEY_2,     HID_KEY_3,      HID_KEY_4,     HID_KEY_5,     HID_KEY_6,         HID_KEY_7,          HID_KEY_8,        HID_KEY_9,          HID_KEY_0,           HID_KEY_BRACKET_RIGHT, HID_KEY_ESCAPE,
		HID_KEY_ARROW_LEFT,  HID_KEY_TAB,          HID_KEY_Q,         HID_KEY_W,     HID_KEY_E,      HID_KEY_R,     HID_KEY_T,     HID_KEY_Y,         HID_KEY_U,          HID_KEY_I,        HID_KEY_O,          HID_KEY_P,           HID_KEY_BRACKET_LEFT,  HID_KEY_DELETE,
		HID_KEY_ARROW_RIGHT, HID_KEY_CONTROL_LEFT, HID_KEY_A,         HID_KEY_S,     HID_KEY_D,      HID_KEY_F,     HID_KEY_G,     HID_KEY_H,         HID_KEY_J,          HID_KEY_K,        HID_KEY_L,          HID_KEY_SEMICOLON,   HID_KEY_APOSTROPHE,    HID_KEY_TAB,
		HID_KEY_ARROW_DOWN,  HID_KEY_SHIFT_LEFT,   HID_KEY_Z,         HID_KEY_X,     HID_KEY_C,      HID_KEY_V,     HID_KEY_B,     HID_KEY_N,         HID_KEY_M,          HID_KEY_COMMA,    HID_KEY_PERIOD,     HID_KEY_SLASH,       HID_KEY_MINUS,         HID_KEY_SHIFT_RIGHT,

		HID_KEY_ARROW_UP,    HID_KEY_GRAVE,        HID_KEY_NONE,      HID_KEY_NONE,  HID_KEY_NONE,  HID_KEY_NONE,  HID_KEY_NONE,   HID_KEY_NONE,      HID_KEY_NONE,       HID_KEY_NONE,     HID_KEY_NONE,       HID_KEY_NONE,        HID_KEY_NONE,          HID_KEY_GRAVE,
		HID_KEY_ARROW_LEFT,  HID_KEY_SPACE,        HID_KEY_F1,        HID_KEY_F2,    HID_KEY_F3,    HID_KEY_F4,    HID_KEY_F5,     HID_KEY_F6,        HID_KEY_F7,         HID_KEY_F8,       HID_KEY_F9,         HID_KEY_F10,         HID_KEY_F11,           HID_KEY_F12,
		HID_KEY_ARROW_RIGHT, HID_KEY_CONTROL_LEFT, HID_KEY_ESCAPE,    HID_KEY_NONE,  HID_KEY_NONE,  HID_KEY_NONE,  HID_KEY_NONE,   HID_KEY_BACKSPACE, HID_KEY_ARROW_LEFT, HID_KEY_ARROW_UP, HID_KEY_ARROW_DOWN, HID_KEY_ARROW_RIGHT, HID_KEY_NONE,          HID_KEY_TAB,
		HID_KEY_ARROW_DOWN,  HID_KEY_SHIFT_LEFT,   HID_KEY_NONE,      HID_KEY_NONE,  HID_KEY_NONE,  HID_KEY_NONE,  HID_KEY_NONE,   HID_KEY_NONE,      HID_KEY_NONE,       HID_KEY_NONE,     HID_KEY_NONE,       HID_KEY_NONE,        HID_KEY_NONE,          HID_KEY_NONE,

		mage_config::KEY_RAISE, HID_KEY_GUI_LEFT, HID_KEY_CONTROL_LEFT, HID_KEY_SPACE,
		mage_config::KEY_LOWER, HID_KEY_BACKSPACE, HID_KEY_CONTROL_RIGHT, HID_KEY_ENTER
	};
	*/


	/**
		@param config - the config to be written into the flash
		@return - true if success, false if failure.
	*/
	inline bool write_config_to_flash(uint8_t* config) {
		uint32_t ints = save_and_disable_interrupts();
		flash_range_erase(CONFIG_FLASH_OFFSET, FLASH_SECTOR_SIZE);
		restore_interrupts (ints);

		flash_range_program(CONFIG_FLASH_OFFSET, config, FLASH_PAGE_SIZE);

		for (int i = 0; i < FLASH_PAGE_SIZE; ++i) {
			if (config[i] != config_flash[i]) {
				return false;
			}
		}
		return true;
	}

	/**
		Retreave config from flash storage
	 */
	inline void read_config_from_flash() {
		for (int i = 0; i < CONFIG_SIZE; i++) {
			config_memory[i] = config_flash[i];
		}
	}

	uint8_t const key_to_ascii_table[128][2] =  { HID_KEYCODE_TO_ASCII };

	inline void get_from_serial(uint8_t* serial_config, uint32_t size, uint8_t state) {
		tud_cdc_write_str(("WRITING CONF FOR STATE: " + std::to_string(state) + "\r\n").c_str());


		for (int i = 0; i < size; i++) {
			config_memory[i + (state * NUMBER_OF_KEYS_IN_PLANK)] = serial_config[i];
		}

		write_config_to_flash(config_memory);
	}

}
