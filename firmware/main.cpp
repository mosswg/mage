/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <string>

#include <tusb.h>
#include <bsp/board.h>

#include "usb_descriptors.h"

#include "mage.h"

//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF PROTYPES
//--------------------------------------------------------------------+

/* Blink pattern
 * - 250 ms  : device not mounted
 * - 1000 ms : device mounted
 * - 2500 ms : device is suspended
 */
enum  {
  BLINK_NOT_MOUNTED = 250,
  BLINK_MOUNTED = 1000,
  BLINK_SUSPENDED = 2500,
};


uint8_t const ascii_to_key_table[128][2] =  { HID_ASCII_TO_KEYCODE };
uint8_t const key_to_ascii_table[128][2] =  { HID_KEYCODE_TO_ASCII };

static uint32_t blink_interval_ms = BLINK_NOT_MOUNTED;

void write_letter(char, uint8_t);
void write_string(char*, uint8_t);
void hid_task(uint8_t*, uint8_t);
void cdc_task(void);

/*------------- MAIN -------------*/
int main(void)
{
	board_init();
	tud_init(0);

	uint8_t pressed_keys[7];
	uint8_t mods;
	uint8_t num_pressed_keys;
	bool prev_was_empty = true;

	mage_config::read_config_from_flash();

	mage keyboard;

	while (1) {
		tud_task(); // tinyusb device task

		num_pressed_keys = 0;
		for(int i = 0; i < 6; i++) {
			pressed_keys[i] = 0;
		}
		mods = 0;

		num_pressed_keys = keyboard.get_pressed_keys(pressed_keys, 6, mods);

		// anti-spam
		if (!prev_was_empty || num_pressed_keys != 0) {
			hid_task(pressed_keys, mods);
			if (num_pressed_keys == 0) {
				prev_was_empty = true;
			} else {
				prev_was_empty = false;
			}
		}

		cdc_task();

		sleep_ms(5);
	}

	return 0;
}



bool buffer_starts_with(uint8_t* buffer, std::string str) {
	for (int i = 0; i < str.size(); i++) {
		if (buffer[i] != str[i]) {
			return false;
		}
	}
	return true;
}
//--------------------------------------------------------------------+
// USB CDC
//--------------------------------------------------------------------+
void cdc_task(void) {
	if ( tud_cdc_connected() ) {
		// connected and there are data available
		if ( tud_cdc_available() ) {
			uint8_t buf[2 * (FLASH_PAGE_SIZE + 4)];

			// read and echo back
			uint32_t count = tud_cdc_read(buf, 2 * (FLASH_PAGE_SIZE + 4));

			if (count >= 4) {
				if (buffer_starts_with(buf, "CFG")) {
					tud_cdc_write_str("CONF PARSING\r\n");
					mage_config::get_from_serial(buf + 4, count - 4, buf[3]);
				}
				else if (buffer_starts_with(buf, "CHNG")) {
					if (count != 8) {
						tud_cdc_write_str("ERROR: INVALID NUMBER OF BYTES IN CHANGE\r\n");
						tud_cdc_write_flush();
						return;
					}
					tud_cdc_write_str("CHANGING CONFIG\r\n");
					mage_config::change_from_serial(buf + 4);
				}
				else if (buffer_starts_with(buf, "SAVE")) {
					tud_cdc_write_str("SAVING CONFIG\r\n");
					mage_config::save_config();
				}
				else if (buffer_starts_with(buf, "FCH")) {
					if (count != 4) {
						tud_cdc_write_str("ERROR: FETCH MUST SPECIFY STATE\r\n");
					}
					mage_config::fetch_config(buf[3]);
				}
				else if (buffer_starts_with(buf, "RSTR")) {
					mage_config::read_config_from_flash();
				}
			}
			tud_cdc_write_flush();
		}
	}
}

// Invoked when cdc when line state changed e.g connected/disconnected
void tud_cdc_line_state_cb(uint8_t itf, bool dtr, bool rts) {
	(void) itf;

	// connected
	if ( dtr && rts )
		{
			// print initial message when connected
			//tud_cdc_write_str("\r\nTinyUSB CDC MSC device example\r\n");
		}
}

// Invoked when CDC interface received data from host
void tud_cdc_rx_cb(uint8_t itf) {
	(void) itf;
}




//--------------------------------------------------------------------+
// USB HID
//--------------------------------------------------------------------+

static void send_hid_report(char c, uint8_t mods)
{
  uint8_t keycode[6] = { c };

  if(keycode[0]) {
    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, mods, keycode);
  }
  // send empty key report if previously has key pressed
  else {
    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
  }
}


void write_letter_raw(char c, uint8_t mods) {
  if (ascii_to_key_table[c][0]) {
    mods |= KEYBOARD_MODIFIER_LEFTSHIFT;
  }

  send_hid_report(ascii_to_key_table[c][1], mods);
}

// Every 1ms, we will sent a report
// tud_hid_report_complete_cb() is used to send the next report after previous one is complete
void hid_task(uint8_t* keys, uint8_t mods)
{

  // skip if hid is not ready yet
  if ( !tud_hid_ready() ) return;

  // Remote wakeup
  if ( tud_suspended() && keys[0] )
  {
    // Wake up host if we are in suspend mode
    // and REMOTE_WAKEUP feature is enabled by host
    tud_remote_wakeup();
  } else {
    // Send the 1st of report chain, the rest will be sent by tud_hid_report_complete_cb()
	  tud_hid_keyboard_report(REPORT_ID_KEYBOARD, mods, keys);
  }
}

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint8_t len)
{
  (void) instance;
  (void) len;
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
  // TODO not Implemented
  (void) instance;
  (void) report_id;
  (void) report_type;
  (void) buffer;
  (void) reqlen;

  return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {}
