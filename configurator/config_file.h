#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "../include/mage_const.h"
#include "helper.h"

namespace mage {
	const uint8_t config_magic_size = 8;
	const uint8_t crc_size = 2;
	const int config_file_size = mage_const::CONFIG_SIZE + config_magic_size + crc_size;
	const char config_magic[config_magic_size] = {'M', 'A', 'G', 'E', 'C', 'F', 'G', 'A'};

	inline void load_config_from_file(const std::string& filename, uint8_t* config_output) {
		std::ifstream file(filename, std::ios_base::in | std::ios_base::binary);

		if (!file.is_open()) {
			std::cerr << "Error: Invalid file \"" << filename << "\"" << std::endl;
			return;
		}

		char magic[config_magic_size];

		file.get(magic, config_magic_size + 1);


		if (!stris(magic, config_magic, config_magic_size)) {
			std::cerr << "Error: Incorrect magic for config file\n";
			return;
		}


		// Get the length of the file
		file.seekg(0, file.end);
		int length = file.tellg();
		file.seekg(config_magic_size, file.beg);

		// Using CONFIG_SIZE as we have already skipped the magic by reading it.
		if (length < config_file_size) {
			std::cerr << "Error: Config file too short; Must be at least " << config_file_size << "b long\n";
			return;
		}
		else if (length > config_file_size) {
			std::cout << "Warning: Config file larger than required; Extra data will be ignored\n";
			std::cout << "file is " << length << " should be " << mage_const::CONFIG_SIZE << "\n";
		}

		file.read((char*)config_output, mage_const::CONFIG_SIZE);

		if (!file) {
			std::cerr << "Error: Could not read all bytes of config file\n";
		}

		uint16_t file_crc;
		file.get((char*)&file_crc, crc_size + 1);



		uint16_t computed_crc = crc16(config_output, mage_const::CONFIG_SIZE);

		if (file_crc != computed_crc) {
			std::cout << "Error: Data does not match CRC; Expected " << file_crc << " computed " << computed_crc << " May be corrupted or invalid\n";
		}

		file.close();
	}



	inline void save_config_to_file(const std::string& filename, uint8_t* config) {
		std::ofstream file(filename, std::ios_base::out | std::ios_base::binary);

		if (!file.is_open()) {
			std::cerr << "Error: Invalid file \"" << filename << "\"" << std::endl;
			return;
		}

		uint16_t crc = crc16(config, mage_const::CONFIG_SIZE);

		file.write(config_magic, config_magic_size);

		file.write((char*)config, mage_const::CONFIG_SIZE);

		file.write((char*)(&crc), crc_size);

		if (!file) {
			std::cerr << "Error: Could not write all bytes of config file\n";
		}

		file.close();
	}
}
