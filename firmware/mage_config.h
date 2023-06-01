#pragma once
#include <tusb.h>
#include "pico/stdlib.h"
#include "hardware/flash.h"
#include "../include/mage_const.h"
#include <string>

namespace mage_config {

	// This must be less than 16 for logic in the write funcions
const uint8_t number_of_configs = 16;
	// SECTOR SIZE = 4096
	// PAGE SIZE = 256
#define CONFIG_FLASH_OFFSET PICO_FLASH_SIZE_BYTES - (number_of_configs * FLASH_SECTOR_SIZE)

	inline const uint8_t *config_flash = (const uint8_t *) (XIP_BASE + CONFIG_FLASH_OFFSET);
	inline uint8_t config_memory[FLASH_PAGE_SIZE];
	inline uint8_t temp_config_memory[FLASH_PAGE_SIZE * number_of_configs];


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
	inline const uint16_t magev1_io_expander_column_row_mappings[mage_const::NUMBER_OF_KEYS_IN_IO_EXPANDER * mage_const::NUMBER_OF_IO_EXPANDERS] = {
		( 6 << 8) | (0), ( 6 << 8) | (1), ( 6 << 8) | (2), ( 6 << 8) | (3), (-1 << 8) | (2), (-1 << 8) | (3), (-1 << 8) | (1), (-1 << 8) | (0), ( 4 << 8) | (0), ( 4 << 8) | (1), ( 4 << 8) | (2), ( 4 << 8) | (3), ( 5 << 8) | (3), ( 5 << 8) | (2), ( 5 << 8) | (1), ( 5 << 8) | (0),
		( 2 << 8) | (0), ( 2 << 8) | (1), ( 2 << 8) | (2), ( 2 << 8) | (3), ( 3 << 8) | (0), ( 3 << 8) | (1), ( 3 << 8) | (2), ( 3 << 8) | (3), ( 1 << 8) | (3), ( 1 << 8) | (2), ( 1 << 8) | (1), ( 1 << 8) | (0), ( 0 << 8) | (3), ( 0 << 8) | (2), ( 0 << 8) | (1), ( 0 << 8) | (0),
		(11 << 8) | (0), (11 << 8) | (1), (11 << 8) | (2), (11 << 8) | (3), (10 << 8) | (0), (10 << 8) | (1), (10 << 8) | (2), (10 << 8) | (3), (13 << 8) | (0), (13 << 8) | (1), (13 << 8) | (2), (13 << 8) | (3), (12 << 8) | (0), (12 << 8) | (1), (12 << 8) | (2), (12 << 8) | (3),
		( 7 << 8) | (0), ( 7 << 8) | (1), ( 7 << 8) | (2), ( 7 << 8) | (3), (-2 << 8) | (2), (-2 << 8) | (3), (-2 << 8) | (1), (-2 << 8) | (0), ( 9 << 8) | (0), ( 9 << 8) | (1), ( 9 << 8) | (2), ( 9 << 8) | (3), ( 8 << 8) | (0), ( 8 << 8) | (1), ( 8 << 8) | (2), ( 8 << 8) | (3),
	};
	inline const uint16_t magev2_io_expander_column_row_mappings[mage_const::NUMBER_OF_KEYS_IN_IO_EXPANDER * mage_const::NUMBER_OF_IO_EXPANDERS] = {
		/* io0-a */ ( 2 << 8) | (0), ( 2 << 8) | (1), ( 2 << 8) | (2), ( 2 << 8) | (3), ( 3 << 8) | (0), ( 3 << 8) | (1), ( 3 << 8) | (2), ( 3 << 8) | (3), /* io0-b */ ( 0 << 8) | (0), ( 0 << 8) | (1), ( 0 << 8) | (2), ( 0 << 8) | (3), ( 1 << 8) | (0), ( 1 << 8) | (1), ( 1 << 8) | (2), ( 1 << 8) | (3),
		/* io1-a */ ( 6 << 8) | (0), ( 6 << 8) | (1), ( 6 << 8) | (2), ( 6 << 8) | (3), (-1 << 8) | (2), (-1 << 8) | (3), (-1 << 8) | (1), (-1 << 8) | (0), /* io1-b */ ( 4 << 8) | (0), ( 4 << 8) | (1), ( 4 << 8) | (2), ( 4 << 8) | (3), ( 5 << 8) | (0), ( 5 << 8) | (1), ( 5 << 8) | (2), ( 5 << 8) | (3),
		/* io2-a */ (11 << 8) | (0), (11 << 8) | (1), (11 << 8) | (2), (11 << 8) | (3), (10 << 8) | (0), (10 << 8) | (1), (10 << 8) | (2), (10 << 8) | (3), /* io2-b */ (13 << 8) | (0), (13 << 8) | (1), (13 << 8) | (2), (13 << 8) | (3), (12 << 8) | (0), (12 << 8) | (1), (12 << 8) | (2), (12 << 8) | (3),
		/* io3-a */ ( 7 << 8) | (0), ( 7 << 8) | (1), ( 7 << 8) | (2), ( 7 << 8) | (3), (-2 << 8) | (0), (-2 << 8) | (1), (-2 << 8) | (2), (-2 << 8) | (3), /* io3-b */ ( 9 << 8) | (0), ( 9 << 8) | (1), ( 9 << 8) | (2), ( 9 << 8) | (3), ( 8 << 8) | (0), ( 8 << 8) | (1), ( 8 << 8) | (2), ( 8 << 8) | (3),
	};
#pragma GCC diagnostic pop


#define MAGEV2
#ifdef MAGEV2
	inline const uint16_t* io_expander_column_row_mappings = magev2_io_expander_column_row_mappings;
#else
	inline const uint16_t* io_expander_column_row_mappings = magev1_io_expander_column_row_mappings;
#endif

	// We should only need one of these so i think having this as global is ok. idk
	inline uint8_t current_config_index = 0;


	inline void fetch_config_index() {
		tud_cdc_write(&current_config_index, 1);
	}

	/**
		Retreave config from flash storage
	 */
	inline void read_config_from_flash(uint8_t config_index = current_config_index) {
		for (int i = 0; i < mage_const::CONFIG_SIZE; i++) {
			config_memory[i] = config_flash[(config_index * FLASH_PAGE_SIZE) + i];
		}
	}

	inline void set_config_index(uint8_t config_index) {
		if (config_index < 0 || config_index > number_of_configs) {
			tud_cdc_write_str(("ERROR: Index " + std::to_string(config_index) + " out of bounds\r\n").c_str());
			return;
		}
		current_config_index = config_index;
		read_config_from_flash(config_index);
	}

	inline uint16_t get_column_and_row_from_io_expander(uint8_t expander, bool bank_b, uint8_t index) {
		return io_expander_column_row_mappings[(mage_const::NUMBER_OF_KEYS_IN_IO_EXPANDER * expander) + (bank_b * 8) + index];
	}



	inline bool memory_and_flash_configs_are_equal() {
		for (int i = 0; i < FLASH_PAGE_SIZE; ++i) {
			if (config_memory[i] != config_flash[i]) {
				return false;
			}
		}
		return true;
	}

	/**
		@param config - the config to be written into the flash
		@return - true if success, false if failure.
	*/
	inline void write_config_to_flash(uint8_t* config, uint8_t config_index) {
		uint32_t address = CONFIG_FLASH_OFFSET;

		// Since we have to erase an entire page at one time, we need to:
		// 	1. save the current data
		uint8_t* current_data_ptr = (uint8_t*)(XIP_BASE + address);
		uint8_t current_data_copy[FLASH_SECTOR_SIZE];
		for (int i = 0; i < FLASH_SECTOR_SIZE / 4; i++) {
			((uint32_t*)current_data_copy)[i] = ((uint32_t*)current_data_ptr)[i];
		}

		// 	2. erase the flash
		uint32_t ints = save_and_disable_interrupts();
		flash_range_erase(address, FLASH_SECTOR_SIZE);
		restore_interrupts(ints);

		// 	3. modify the saved data
		for (int i = 0; i < FLASH_PAGE_SIZE; i++) {
			current_data_copy[(config_index * FLASH_PAGE_SIZE) + i] = config[i];
		}

		// 	4. reinsert the entire page
		flash_range_program(address, current_data_copy, FLASH_SECTOR_SIZE);

	}

	inline void set_config_memory(uint8_t state, uint8_t column, uint8_t row, uint8_t key) {
		if (state < mage_const::MIN_STATE || state > mage_const::MAX_STATE || column < 0 || column >= mage_const::NUMBER_OF_KEYS_IN_ROW || row < 0 || row >= mage_const::NUMBER_OF_KEYS_IN_COLUMN) {
			tud_cdc_write_str("ERROR: Change out of bounds\r\n");
			return;
		}
		mage_config::config_memory[mage_const::NUMBER_OF_KEYS_IN_PLANK * state + (row * mage_const::NUMBER_OF_KEYS_IN_ROW) + column] = key;
	}

	uint8_t const key_to_ascii_table[128][2] =  { HID_KEYCODE_TO_ASCII };

	inline void get_from_serial(uint8_t* serial_config, uint32_t size, uint8_t state) {
		if (state > mage_const::MAX_STATE || state < mage_const::MIN_STATE) {
			tud_cdc_write_str("ERROR: State ");
			tud_cdc_write_str(std::to_string(state).c_str());
			tud_cdc_write_str(" Out of bounds\r\n");
			return;
		}
		tud_cdc_write_str(("WRITING CONF FOR STATE: " + std::to_string(state) + "\r\n").c_str());


		for (int i = 0; i < size; i++) {
			config_memory[i + (state * mage_const::NUMBER_OF_KEYS_IN_PLANK)] = serial_config[i];
		}

	}

	inline void save_config() {
		write_config_to_flash(config_memory, current_config_index);
	}


	inline void save_config(uint8_t config_index) {
		write_config_to_flash(config_memory, config_index);
	}

	inline void change_from_serial(uint8_t* serial_data) {
		uint8_t state = serial_data[0];
		uint8_t column = serial_data[1];
		uint8_t row = serial_data[2];
		uint8_t key = serial_data[3];

		set_config_memory(state, column, row, key);
	}

	inline void fetch_config(uint8_t state) {
		if (state > mage_const::MAX_STATE || state < mage_const::MIN_STATE) {
			tud_cdc_write_str("ERROR: State ");
			tud_cdc_write_str(std::to_string(state).c_str());
			tud_cdc_write_str(" Out of bounds\r\n");
			return;
		}

		// Sleep to allow the receiver time to start reading
		sleep_ms(5);

		if (state == mage_const::STATE_CONTROL) {
			tud_cdc_write(config_memory + (mage_const::NUMBER_OF_KEYS_IN_PLANK * state), mage_const::NUMBER_OF_KEYS_IN_CONTROL_GROUP * 2);
		}
		else {
			tud_cdc_write(config_memory + (mage_const::NUMBER_OF_KEYS_IN_PLANK * state), mage_const::NUMBER_OF_KEYS_IN_PLANK);
		}
		tud_cdc_write_flush();
	}
}
