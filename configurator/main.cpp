#include "main.h"
#include "tui/tui.h"


void init_tty(int, struct termios&);
void print_usage();
int main(int argc, char** argv) {
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
		run_tui(SERIAL_USB, config);
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
		mage::save_config(SERIAL_USB);
	}
	else if (stris(argv[1], "restore")) {
		mage::restore_config(SERIAL_USB);
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
	else if (stris(argv[1], "edit")) {
		if (argc < 3) {
			std::cout << "Too few arguments for edit\n";
			print_usage();
		}

		char* filename = argv[2];
		uint8_t config[mage_const::CONFIG_SIZE];
		mage::load_config_from_file(filename, config);
		run_tui(SERIAL_USB, config);
	}


	return 0;
}






// Helper functions

void init_tty(int SERIAL_USB, struct termios& tty) {
	struct termios tty_old;
	memset(&tty, 0, sizeof tty);

	/* Error Handling */
	if ( tcgetattr ( SERIAL_USB, &tty ) != 0 ) {
		std::cout << "Error " << errno << " from tcgetattr: " << strerror(errno) << std::endl;
		exit(2);
	}

	/* Save old tty parameters */
	tty_old = tty;

	/* Set Baud Rate */
	cfsetospeed (&tty, (speed_t)B115200);
	cfsetispeed (&tty, (speed_t)B115200);

	/* Setting other Port Stuff */
	tty.c_cflag     &=  ~PARENB;            // Make 8n1
	tty.c_cflag     &=  ~CSTOPB;
	tty.c_cflag     &=  ~CSIZE;
	tty.c_cflag     |=  CS8;

	tty.c_cflag     &=  ~CRTSCTS;           // no flow control
	tty.c_cc[VMIN]   =  1;                  // read doesn't block
	tty.c_cc[VTIME]  =  50;                  // 5.0 seconds read timeout
	tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

	/* Make raw */
	cfmakeraw(&tty);

	/* Flush Port, then applies attributes */
	tcflush( SERIAL_USB, TCIFLUSH );
	if ( tcsetattr ( SERIAL_USB, TCSANOW, &tty ) != 0) {
		std::cout << "Error " << errno << " from tcsetattr" << std::endl;
		exit(3);
	}
}

void print_usage() {
	auto& out = std::cout;
	out << "Usage: configurator [command] <arguments>\n";
	out << "\tCommands:\n";
	out << "\t\tchange:\n";
	out << "\t\t\tChange a key in the configuration\n";
	out << "\t\t\tArguments: State Column Row Key\n\n";
	out << "\t\tdefault:\n";
	out << "\t\t\tUpload the default configuration\n";
	out << "\t\t\tArguments: NONE\n\n";
	out << "\t\tsave:\n";
	out << "\t\t\tSave the current configuration to flash\n";
	out << "\t\t\tArguments: NONE\n\n";
	out << "\t\trestore:\n";
	out << "\t\t\tRestore the configuration from flash\n";
	out << "\t\t\tArguments: NONE\n\n";
	out << "\t\tfetch:\n";
	out << "\t\t\tGet the current configuration from the keyboard\n";
	out << "\t\t\tArguments: NONE\n\n";
}
