#include "main.h"


const int CONFIG_PLANK_SIZE = mage_const::NUMBER_OF_KEYS_IN_PLANK + 4;
const int CONFIG_CONTROL_SIZE = (mage_const::NUMBER_OF_KEYS_IN_CONTROL_GROUP * 2) + 4;

const uint8_t config_high[CONFIG_PLANK_SIZE] = {
	'C', 'F', 'G', mage_const::STATE_HIGH,
	HID_KEY_ARROW_UP,    HID_KEY_GRAVE,        HID_KEY_F1,        HID_KEY_F2,    HID_KEY_F3,     HID_KEY_F4,    HID_KEY_F5,    HID_KEY_F6,        HID_KEY_F7,         HID_KEY_F8,       HID_KEY_F9,         HID_KEY_F10,         HID_KEY_BRACKET_LEFT,  HID_KEY_ESCAPE,
	HID_KEY_ARROW_LEFT,  HID_KEY_SPACE,        HID_KEY_1,         HID_KEY_2,     HID_KEY_3,      HID_KEY_4,     HID_KEY_5,     HID_KEY_6,         HID_KEY_7,          HID_KEY_8,        HID_KEY_9,          HID_KEY_0,           HID_KEY_BRACKET_RIGHT, HID_KEY_DELETE,
	HID_KEY_ARROW_RIGHT, HID_KEY_CONTROL_LEFT, HID_KEY_EQUAL,     HID_KEY_NONE,  HID_KEY_NONE,   HID_KEY_NONE,  HID_KEY_NONE,  HID_KEY_NONE,      HID_KEY_NONE,       HID_KEY_NONE,     HID_KEY_NONE,       HID_KEY_NONE,        HID_KEY_NONE,          HID_KEY_TAB,
	HID_KEY_ARROW_DOWN,  HID_KEY_SHIFT_LEFT,   HID_KEY_SEMICOLON, HID_KEY_NONE,  HID_KEY_NONE,   HID_KEY_NONE,  HID_KEY_NONE,  HID_KEY_NONE,      HID_KEY_NONE,       HID_KEY_NONE,     HID_KEY_NONE,       HID_KEY_NONE,        HID_KEY_EQUAL,         HID_KEY_SHIFT_RIGHT,
};


const uint8_t config_normal[CONFIG_PLANK_SIZE] = {
	'C', 'F', 'G', mage_const::STATE_NORMAL,
	HID_KEY_ARROW_UP,    HID_KEY_ESCAPE,       HID_KEY_1,         HID_KEY_2,     HID_KEY_3,      HID_KEY_4,     HID_KEY_5,     HID_KEY_6,         HID_KEY_7,          HID_KEY_8,        HID_KEY_9,          HID_KEY_0,           HID_KEY_BRACKET_RIGHT, HID_KEY_ESCAPE,
	HID_KEY_ARROW_LEFT,  HID_KEY_TAB,          HID_KEY_Q,         HID_KEY_W,     HID_KEY_E,      HID_KEY_R,     HID_KEY_T,     HID_KEY_Y,         HID_KEY_U,          HID_KEY_I,        HID_KEY_O,          HID_KEY_P,           HID_KEY_BRACKET_LEFT,  HID_KEY_DELETE,
	HID_KEY_ARROW_RIGHT, HID_KEY_CONTROL_LEFT, HID_KEY_A,         HID_KEY_S,     HID_KEY_D,      HID_KEY_F,     HID_KEY_G,     HID_KEY_H,         HID_KEY_J,          HID_KEY_K,        HID_KEY_L,          HID_KEY_SEMICOLON,   HID_KEY_APOSTROPHE,    HID_KEY_TAB,
	HID_KEY_ARROW_DOWN,  HID_KEY_SHIFT_LEFT,   HID_KEY_Z,         HID_KEY_X,     HID_KEY_C,      HID_KEY_V,     HID_KEY_B,     HID_KEY_N,         HID_KEY_M,          HID_KEY_COMMA,    HID_KEY_PERIOD,     HID_KEY_SLASH,       HID_KEY_MINUS,         HID_KEY_SHIFT_RIGHT,
};

const uint8_t config_low[CONFIG_PLANK_SIZE] = {
	'C', 'F', 'G', mage_const::STATE_LOW,
	HID_KEY_ARROW_UP,    HID_KEY_GRAVE,        HID_KEY_NONE,      HID_KEY_NONE,  HID_KEY_NONE,  HID_KEY_NONE,  HID_KEY_NONE,   HID_KEY_NONE,      HID_KEY_NONE,       HID_KEY_NONE,     HID_KEY_NONE,       HID_KEY_NONE,        HID_KEY_NONE,          HID_KEY_GRAVE,
	HID_KEY_ARROW_LEFT,  HID_KEY_SPACE,        HID_KEY_F1,        HID_KEY_F2,    HID_KEY_F3,    HID_KEY_F4,    HID_KEY_F5,     HID_KEY_F6,        HID_KEY_F7,         HID_KEY_F8,       HID_KEY_F9,         HID_KEY_F10,         HID_KEY_F11,           HID_KEY_F12,
	HID_KEY_ARROW_RIGHT, HID_KEY_CONTROL_LEFT, HID_KEY_ESCAPE,    HID_KEY_NONE,  HID_KEY_NONE,  HID_KEY_NONE,  HID_KEY_NONE,   HID_KEY_BACKSPACE, HID_KEY_ARROW_LEFT, HID_KEY_ARROW_UP, HID_KEY_ARROW_DOWN, HID_KEY_ARROW_RIGHT, HID_KEY_NONE,          HID_KEY_TAB,
	HID_KEY_ARROW_DOWN,  HID_KEY_SHIFT_LEFT,   HID_KEY_NONE,      HID_KEY_NONE,  HID_KEY_NONE,  HID_KEY_NONE,  HID_KEY_NONE,   HID_KEY_NONE,      HID_KEY_NONE,       HID_KEY_NONE,     HID_KEY_NONE,       HID_KEY_NONE,        HID_KEY_NONE,          HID_KEY_NONE,
};

const uint8_t config_control[CONFIG_CONTROL_SIZE] = {
	'C', 'F', 'G', mage_const::STATE_CONTROL,
	MAGE_KEY_RAISE, HID_KEY_GUI_LEFT, HID_KEY_CONTROL_LEFT, HID_KEY_SPACE,
	MAGE_KEY_LOWER, HID_KEY_BACKSPACE, HID_KEY_CONTROL_RIGHT, HID_KEY_ENTER,
};

const uint8_t save_seq[4] = {'S', 'A', 'V', 'E'};

const uint8_t fetch_high_seq[4] = {'F', 'C', 'H', mage_const::STATE_HIGH};
const uint8_t fetch_normal_seq[4] = {'F', 'C', 'H', mage_const::STATE_NORMAL};
const uint8_t fetch_low_seq[4] = {'F', 'C', 'H', mage_const::STATE_LOW};
const uint8_t fetch_control_seq[4] = {'F', 'C', 'H', mage_const::STATE_CONTROL};

void save_config(int SERIAL_USB) {
	write( SERIAL_USB, save_seq, 4);
}

void write_default_config(int SERIAL_USB) {
	int n_written = write( SERIAL_USB, config_high, CONFIG_PLANK_SIZE);
	n_written = write( SERIAL_USB, config_normal, CONFIG_PLANK_SIZE);
	n_written = write( SERIAL_USB, config_low, CONFIG_PLANK_SIZE);
	n_written = write( SERIAL_USB, config_control, CONFIG_CONTROL_SIZE);
	save_config(SERIAL_USB);

	tcflush(SERIAL_USB, TCIOFLUSH);
}

void write_change(int SERIAL_USB, uint8_t state, uint8_t column, uint8_t row, uint8_t key) {
	uint8_t data[8] = {
		'C', 'H', 'N', 'G',
		state, column, row, key,
	};
	write(SERIAL_USB, data, 8);
}

void fetch_config(int SERIAL_USB, uint8_t* out) {
	write(SERIAL_USB, fetch_high_seq, 4);
	read(SERIAL_USB, out, mage_const::NUMBER_OF_KEYS_IN_PLANK);

	write(SERIAL_USB, fetch_normal_seq, 4);
	read(SERIAL_USB, out + mage_const::NUMBER_OF_KEYS_IN_PLANK, mage_const::NUMBER_OF_KEYS_IN_PLANK);

	write(SERIAL_USB, fetch_low_seq, 4);
	read(SERIAL_USB, out + (mage_const::NUMBER_OF_KEYS_IN_PLANK * 2), mage_const::NUMBER_OF_KEYS_IN_PLANK);

	write(SERIAL_USB, fetch_control_seq, 4);
	read(SERIAL_USB, out + (mage_const::NUMBER_OF_KEYS_IN_PLANK * 3), mage_const::NUMBER_OF_KEYS_IN_CONTROL_GROUP * 2);

	for (int i = 0; i < mage_const::CONFIG_SIZE; i++) {
		if (!(i % mage_const::NUMBER_OF_KEYS_IN_ROW)) {
			std::cout << "\n";
		}
		if (!(i % mage_const::NUMBER_OF_KEYS_IN_PLANK)) {
			std::cout << "\n";
		}
		std::cout << keycode_names[out[i]] << "\t";
	}
	std::cout << std::dec << "\n";
}

uint8_t name_to_keycode(std::string name) {
	for (char& c : name) {
		c = toupper(c);
	}
	// Should probably change this to a hashmap
	for (int i = 0; i < MAX_KEYCODE; i++) {
		if (keycode_names[i] == name) {
			return i;
		}
	}
	std::cerr << "ERROR: Unknown key " << name << "\n";
	return -1;
}

uint8_t string_to_state(std::string str) {
	for (char& c : str) {
		c = toupper(c);
	}

	for (int i = 0; i < mage_const::MAX_STATE; i++) {
		if (str == state_names[i] || str == std::to_string(i)) {
			return i;
		}
	}

	std::cerr << "ERROR: Unknown state " << str << "\n";

	return -1;
}

void init_tty(int, struct termios&);
void print_usage();
bool stris(char*, std::string);

int main(int argc, char** argv) {
	int SERIAL_USB = open( "/dev/ttyACM0", O_RDWR| O_NOCTTY );

	if (SERIAL_USB < 0) {
		perror("Error while opening device: ");
		exit(1);
	}

	struct termios tty;

	init_tty(SERIAL_USB, tty);

	if (argc < 2) {
		print_usage();
		return 1;
	}

	if (stris(argv[1], "change")) {
		if (argc < 6) {
			std::cout << "Too few arguments for change\n";
			print_usage();
		}
		uint8_t state = string_to_state(argv[2]);
		uint8_t column = std::stoi(argv[3]);
		uint8_t row = std::stoi(argv[4]);
		uint8_t key = name_to_keycode(argv[5]);
		if (state == -1 || key == -1) {
			return 1;
		}
		if (column < 0 || column >= mage_const::NUMBER_OF_KEYS_IN_ROW) {
			std::cerr << "ERROR: Column out of bounds\n";
			return 1;
		}
		if (row < 0 || row >= mage_const::NUMBER_OF_KEYS_IN_COLUMN) {
			std::cerr << "ERROR: Row out of bounds\n";
			return 1;
		}

		write_change(SERIAL_USB, state, column, row, key);
	}
	else if (stris(argv[1], "default")) {
		write_default_config(SERIAL_USB);
	}
	else if (stris(argv[1], "save")) {
		save_config(SERIAL_USB);
	}
	else if (stris(argv[1], "fetch")) {
		uint8_t config[mage_const::CONFIG_SIZE];
		memset(config, 0, mage_const::CONFIG_SIZE);
		fetch_config(SERIAL_USB, config);
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
	out << "\t\tfetch:\n";
	out << "\t\t\tGet the current configuration from the keyboard\n";
	out << "\t\t\tArguments: NONE\n\n";
}


bool stris(char* cp, std::string str) {
	for (int i = 0; i < str.length() && cp[i]; i++) {
		if (cp[i] != str[i]) {
			return false;
		}
	}
	return true;
}
