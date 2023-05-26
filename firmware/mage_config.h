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
	inline const int NUMBER_OF_KEYS_IN_IO_EXPANDER = 16;
	inline const int NUMBER_OF_IO_EXPANDERS = 4;
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


// Remove annoynig "narrowing" warning just for these few lines
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnarrowing"
	inline const uint16_t io_expander_column_row_mappings[NUMBER_OF_KEYS_IN_IO_EXPANDER * NUMBER_OF_IO_EXPANDERS] = {
		( 6 << 8) | (0), ( 6 << 8) | (1), ( 6 << 8) | (2), ( 6 << 8) | (3), (-1 << 8) | (2), (-1 << 8) | (3), (-1 << 8) | (1), (-1 << 8) | (0), ( 4 << 8) | (0), ( 4 << 8) | (1), ( 4 << 8) | (2), ( 4 << 8) | (3), ( 5 << 8) | (3), ( 5 << 8) | (2), ( 5 << 8) | (1), ( 5 << 8) | (0),
		( 2 << 8) | (0), ( 2 << 8) | (1), ( 2 << 8) | (2), ( 2 << 8) | (3), ( 3 << 8) | (0), ( 3 << 8) | (1), ( 3 << 8) | (2), ( 3 << 8) | (3), ( 1 << 8) | (3), ( 1 << 8) | (2), ( 1 << 8) | (1), ( 1 << 8) | (0), ( 0 << 8) | (3), ( 0 << 8) | (2), ( 0 << 8) | (1), ( 0 << 8) | (0),
		(11 << 8) | (0), (11 << 8) | (1), (11 << 8) | (2), (11 << 8) | (3), (10 << 8) | (0), (10 << 8) | (1), (10 << 8) | (2), (10 << 8) | (3), (13 << 8) | (0), (13 << 8) | (1), (13 << 8) | (2), (13 << 8) | (3), (12 << 8) | (0), (12 << 8) | (1), (12 << 8) | (2), (12 << 8) | (3),
		( 7 << 8) | (0), ( 7 << 8) | (1), ( 7 << 8) | (2), ( 7 << 8) | (3), (-2 << 8) | (2), (-2 << 8) | (3), (-2 << 8) | (1), (-2 << 8) | (0), ( 9 << 8) | (0), ( 9 << 8) | (1), ( 9 << 8) | (2), ( 9 << 8) | (3), ( 8 << 8) | (0), ( 8 << 8) | (1), ( 8 << 8) | (2), ( 8 << 8) | (3),
	};
#pragma GCC diagnostic pop

	inline uint16_t get_column_and_row_from_io_expander(uint8_t expander, bool bank_b, uint8_t index) {
		return io_expander_column_row_mappings[(NUMBER_OF_KEYS_IN_IO_EXPANDER * expander) + (bank_b * 8) + index];
	}


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
