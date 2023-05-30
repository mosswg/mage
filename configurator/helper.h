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
