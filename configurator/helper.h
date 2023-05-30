#pragma once
#include <string>


inline bool stris(const char* cp, const std::string& str) {
	for (int i = 0; i < (int)str.length() && cp[i]; i++) {
		if (cp[i] != str[i]) {
			return false;
		}
	}
	return true;
}


inline bool stris(const char* cp, const char* other, int len) {
	for (int i = 0; i < len && cp[i]; i++) {
		if (cp[i] != other[i]) {
			return false;
		}
	}
	return true;
}


inline uint16_t crc16(const uint8_t* data, uint16_t length){
	uint8_t byte;
	unsigned short crc = 0xFFFF;

	for (uint16_t i = 0; i < length; i++) {
		byte = crc >> 8 ^ *(data + i);
		byte ^= byte >> 4;
		crc = (crc << 8) ^ ((uint8_t)(byte << 12)) ^ ((uint8_t)(byte <<5)) ^ ((uint8_t)byte);
	}
	return crc;
}
