#pragma once
#include <stdint.h>

const uint8_t mage_const_STATE_HIGH = 0;
const uint8_t mage_const_STATE_NORMAL = 1;
const uint8_t mage_const_STATE_LOW = 2;
const uint8_t mage_const_STATE_CONTROL = 3;


const int mage_const_NUMBER_OF_KEYS_IN_ROW = 14;
const int mage_const_NUMBER_OF_KEYS_IN_COLUMN = 4;
const int mage_const_NUMBER_OF_KEYS_IN_PLANK = mage_const_NUMBER_OF_KEYS_IN_ROW * mage_const_NUMBER_OF_KEYS_IN_COLUMN;
const int mage_const_NUMBER_OF_KEYS_IN_CONTROL_GROUP = 4;
#define mage_const_NUMBER_OF_KEYS_IN_IO_EXPANDER 16
#define mage_const_NUMBER_OF_IO_EXPANDERS 4
const int mage_const_CONFIG_SIZE = (mage_const_NUMBER_OF_KEYS_IN_PLANK * 3) + (mage_const_NUMBER_OF_KEYS_IN_CONTROL_GROUP * 2);

const int mage_const_MAX_STATE = mage_const_STATE_CONTROL;
const int mage_const_MIN_STATE = mage_const_STATE_HIGH;

const uint8_t mage_const_KEY_RAISE = 0xa5;
const uint8_t mage_const_KEY_LOWER = 0xa6;
const uint8_t mage_const_CONFIG0 = 0xa7;
const uint8_t mage_const_CONFIG1 = 0xa8;
const uint8_t mage_const_CONFIG2 = 0xa9;
const uint8_t mage_const_CONFIG3 = 0xaa;
const uint8_t mage_const_CONFIG4 = 0xab;
const uint8_t mage_const_CONFIG5 = 0xac;
const uint8_t mage_const_CONFIG6 = 0xad;
const uint8_t mage_const_CONFIG7 = 0xae;
const uint8_t mage_const_CONFIG8 = 0xaf;
const uint8_t mage_const_CONFIG9 = 0xb0;
