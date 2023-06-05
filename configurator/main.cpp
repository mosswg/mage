#include "main.h"
#include "tui/tui.h"


int main(int argc, char** argv) {
	/// Allow for help to be printed without the mage
	if (argc > 1 && stris(argv[1], "help")) {
		print_usage();
		return 0;
	}

	// Allow edit without keyboard plugged in
	if (argc > 1 && stris(argv[1], "edit")) {
		if (argc < 3) {
			std::cout << "Too few arguments for edit\n";
			print_usage();
		}

		char* filename = argv[2];
		uint8_t config[mage_const::CONFIG_SIZE];
		mage::load_config_from_file(filename, config);
		run_tui(config);
		mage::save_config_to_file(filename, config);
		return 0;
	}

	int SERIAL_USB = open( "/dev/ttyACM0", O_RDWR| O_NOCTTY );

	if (SERIAL_USB < 0) {
		perror("Error while opening device");
		exit(1);
	}

	struct termios tty;

	init_tty(SERIAL_USB, tty);

	if (argc < 2) {
		uint8_t config[mage_const::CONFIG_SIZE];
		memset(config, 0, mage_const::CONFIG_SIZE);
		mage::fetch_config(SERIAL_USB, config);
		run_tui(config);
		mage::write_config(SERIAL_USB, config);
		return 0;
	}

	if (stris(argv[1], "change")) {
		if (argc < 6) {
			std::cout << "Too few arguments for change\n";
			print_usage();
		}
		uint8_t state = mage::string_to_state(argv[2]);
		uint8_t column = std::stoi(argv[3]);
		uint8_t row = std::stoi(argv[4]);
		uint8_t key = mage::name_to_keycode(argv[5]);
		if (state == -1) {
			std::cerr << "ERROR: Unknown state " << state << "\n";
			return 1;
		}
		if (key == -1) {
			std::cerr << "ERROR: Unknown key " << key << "\n";
			return 1;
		}
		if (column < 1 || column > mage_const::NUMBER_OF_KEYS_IN_ROW) {
			std::cerr << "ERROR: Column out of bounds\n";
			return 1;
		}
		if (row < 1 || row > mage_const::NUMBER_OF_KEYS_IN_COLUMN) {
			std::cerr << "ERROR: Row out of bounds\n";
			return 1;
		}

		// Change from indexing from 1 to 0
		mage::write_change(SERIAL_USB, state, column - 1, row - 1, key);
	}
	else if (stris(argv[1], "default")) {
		mage::write_default_config(SERIAL_USB);
	}
	else if (stris(argv[1], "save")) {
		if (argc > 2) {
			uint8_t config_index = std::stoi(argv[2]);
			mage::save_config(SERIAL_USB, config_index);
		}
		else {
			mage::save_config(SERIAL_USB);
		}
	}
	else if (stris(argv[1], "restore")) {
		if (argc > 2) {
			uint8_t config_index = std::stoi(argv[2]);
			mage::restore_config(SERIAL_USB, config_index);
		}
		else {
			mage::restore_config(SERIAL_USB);
		}
	}
	else if (stris(argv[1], "fetch")) {
		uint8_t config[mage_const::CONFIG_SIZE];
		memset(config, 0, mage_const::CONFIG_SIZE);
		mage::fetch_config(SERIAL_USB, config);
		mage::print_config(config);
	}
	else if (stris(argv[1], "upload")) {
		if (argc < 3) {
			std::cout << "Too few arguments for upload\n";
			print_usage();
		}

		char* filename = argv[2];
		uint8_t config[mage_const::CONFIG_SIZE];
		mage::load_config_from_file(filename, config);
		mage::write_config(SERIAL_USB, config);
	}
	else if (stris(argv[1], "download")) {
		if (argc < 3) {
			std::cout << "Too few arguments for download\n";
			print_usage();
		}

		char* filename = argv[2];
		uint8_t config[mage_const::CONFIG_SIZE];
		mage::fetch_config(SERIAL_USB, config);
		mage::save_config_to_file(filename, config);
	}
	else if (stris(argv[1], "index")) {
		if (argc < 3) {
			std::cout << (int)mage::fetch_config_index(SERIAL_USB) << "\n";
			return 0;
		}
		uint8_t index = std::stoi(argv[2]);
		mage::change_config_index(SERIAL_USB, index);
	}


	return 0;
}
