#pragma once
#include "../include/mage_const.h"
#include <string>
#include <iostream>
#include "keycode.h"
#include "serial.h"
#include "config_file.h"
#include "helper.h"






// Helper functions

inline void init_tty(int SERIAL_USB, struct termios& tty) {
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

inline void print_usage() {
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
