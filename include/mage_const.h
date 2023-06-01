#pragma once
#include <stdint.h>

namespace mage_const {
	const uint8_t STATE_HIGH = 0;
	const uint8_t STATE_NORMAL = 1;
	const uint8_t STATE_LOW = 2;
	const uint8_t STATE_CONTROL = 3;


	const int NUMBER_OF_KEYS_IN_ROW = 14;
	const int NUMBER_OF_KEYS_IN_COLUMN = 4;
	const int NUMBER_OF_KEYS_IN_PLANK = NUMBER_OF_KEYS_IN_ROW * NUMBER_OF_KEYS_IN_COLUMN;
	const int NUMBER_OF_KEYS_IN_CONTROL_GROUP = 4;
	const int NUMBER_OF_KEYS_IN_IO_EXPANDER = 16;
	const int NUMBER_OF_IO_EXPANDERS = 4;
	const int CONFIG_SIZE = (NUMBER_OF_KEYS_IN_PLANK * 3) + (NUMBER_OF_KEYS_IN_CONTROL_GROUP * 2);

	const int MAX_STATE = STATE_CONTROL;
	const int MIN_STATE = STATE_HIGH;

	const uint8_t KEY_RAISE = 0xa5;
	const uint8_t KEY_LOWER = 0xa6;
	const uint8_t CONFIG0 = 0xa7;
	const uint8_t CONFIG1 = 0xa8;
	const uint8_t CONFIG2 = 0xa9;
	const uint8_t CONFIG3 = 0xaa;
	const uint8_t CONFIG4 = 0xab;
	const uint8_t CONFIG5 = 0xac;
	const uint8_t CONFIG6 = 0xad;
	const uint8_t CONFIG7 = 0xae;
	const uint8_t CONFIG8 = 0xaf;
	const uint8_t CONFIG9 = 0xb0;
};
