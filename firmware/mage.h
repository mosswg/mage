#pragma once

#include "mcp23017.h"
#include "mage_config.h"

class mage {
	public:
	const uint8_t STATE_HIGH = 0;
	const uint8_t STATE_NORMAL = 1;
	const uint8_t STATE_LOW = 2;
	const uint8_t STATE_CONTROL = 3;

	mcp23017 io1;
	mcp23017 io2;
	mcp23017 io3;
	mcp23017 io4;
	uint8_t state;

	static constexpr uint8_t KEY_POSITIONS_BUFFER_SIZE = 32;
	uint16_t key_positions_buffer[KEY_POSITIONS_BUFFER_SIZE];

	mage() : io1(mcp23017(0x20)), io2(mcp23017(0x21)), io3(mcp23017(0x22)), io4(mcp23017(0x23)), state(STATE_NORMAL) {}

	int get_pressed_keys(uint8_t* buffer, int buffer_size, uint8_t& mods);

	bool append_io1_bank_a_to_keys(uint16_t* key_buffer, int& buffer_index, int key_buffer_size, uint8_t& mods);
	bool append_io1_bank_b_to_keys(uint16_t* key_buffer, int& buffer_index, int key_buffer_size, uint8_t& mods);
	bool append_io2_bank_a_to_keys(uint16_t* key_buffer, int& buffer_index, int key_buffer_size, uint8_t& mods);
	bool append_io2_bank_b_to_keys(uint16_t* key_buffer, int& buffer_index, int key_buffer_size, uint8_t& mods);
	bool append_io3_bank_a_to_keys(uint16_t* key_buffer, int& buffer_index, int key_buffer_size, uint8_t& mods);
	bool append_io3_bank_b_to_keys(uint16_t* key_buffer, int& buffer_index, int key_buffer_size, uint8_t& mods);
	bool append_io4_bank_a_to_keys(uint16_t* key_buffer, int& buffer_index, int key_buffer_size, uint8_t& mods);
	bool append_io4_bank_b_to_keys(uint16_t* key_buffer, int& buffer_index, int key_buffer_size, uint8_t& mods);

	void error_out_buffer(uint8_t* key_buffer, int key_buffer_size);

	uint8_t key_to_modifier(uint8_t key);


	uint8_t get_plank_key(uint8_t column, uint8_t row, uint8_t state);
	uint8_t get_control_group_key(uint8_t group, uint8_t index);


	void append_keys_from_postions_to_buffer(uint8_t* buffer, uint8_t buffer_size, uint8_t& mods);

	int append_plank_key(uint8_t* key_buffer, int buffer_index, uint8_t& mods, uint8_t column, uint8_t row);

	int append_control_group_key(uint8_t* key_buffer, int buffer_index, uint8_t& mods, uint8_t column, uint8_t row);
};
