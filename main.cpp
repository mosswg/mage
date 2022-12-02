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

#include <tusb.h>
#include <bsp/board.h>

#include "usb_descriptors.h"

#include "mcp23017.h"

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

static uint32_t blink_interval_ms = BLINK_NOT_MOUNTED;

void write_letter(char, uint8_t);
void write_string(char*, uint8_t);
void hid_task(uint8_t*);

/*------------- MAIN -------------*/
int main(void)
{
  board_init();
  tud_init(0);
  mcp23017::initialize();

  uint8_t pressed_keys[6];
  uint8_t num_pressed_keys;
  bool prev_was_empty = true;

  while (1)
  {
    tud_task(); // tinyusb device task

	num_pressed_keys = 0;
	for(int i = 0; i < 6; i++) {
		pressed_keys[i] = 0;
	}


    uint8_t bank_b = mcp23017::get_bank_b();


	if(bank_b) {
		if (bank_b & 0b1) {
			pressed_keys[num_pressed_keys++] = HID_KEY_A;
		}
		if (bank_b & 0b10) {
			pressed_keys[num_pressed_keys++] = HID_KEY_B;
		}
		if (bank_b & 0b10000) {
			pressed_keys[num_pressed_keys++] = HID_KEY_C;
		}
	}

	if (!prev_was_empty || num_pressed_keys != 0) {
			hid_task(pressed_keys);
			if (num_pressed_keys == 0) {
				prev_was_empty = true;
			} else {
				prev_was_empty = false;
			}
	}

	sleep_ms(5);
  }

  return 0;
}

//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void)
{
  blink_interval_ms = BLINK_MOUNTED;
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
  blink_interval_ms = BLINK_NOT_MOUNTED;
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
  (void) remote_wakeup_en;
  blink_interval_ms = BLINK_SUSPENDED;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
  blink_interval_ms = BLINK_MOUNTED;
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

void write_string(char* str, uint8_t str_mods) {
  // skip if hid is not ready yet
  if ( !tud_hid_ready() ) return;

  if ( tud_suspended() && str[0] )
  {
    // Wake up host if we are in suspend mode
    // and REMOTE_WAKEUP feature is enabled by host
    tud_remote_wakeup();
  }

  for (int i = 0; str[i] != 0; i++) {

    if (str[i] == '{') {
      int j;
      for (j = 0; str[i + j] == '}'; j++) {
        if (!str[i + j]) {
          return;
        }
      }

      char substr[j];
      for (int k = 0; k < j; k++) {
        substr[k] = str[i + k];
      }

      write_string(substr, str_mods); // | KEYBOARD_MODIFIER_LEFTCTRL);
      i += j;
      continue;
    }

    write_letter_raw(str[i], str_mods);
    sleep_ms(5);
    tud_task();
  }

  send_hid_report(0,0);
}

void write_letter(char c, uint8_t mods) {
  if ( tud_suspended() && c )
  {
    // Wake up host if we are in suspend mode
    // and REMOTE_WAKEUP feature is enabled by host
    tud_remote_wakeup();
  }


  if (ascii_to_key_table[c][0]) {
    mods |= KEYBOARD_MODIFIER_LEFTSHIFT;
  }

  send_hid_report(ascii_to_key_table[c][1], mods);
  sleep_ms(5);
  tud_task(); // tinyusb device task
  sleep_ms(5);
  send_hid_report(0, 0);
 }

// Every 1ms, we will sent a report
// tud_hid_report_complete_cb() is used to send the next report after previous one is complete
void hid_task(uint8_t* keys)
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
	  tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keys);
  }
}

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint8_t len)
{
  (void) instance;
  (void) len;

  uint8_t next_report_id = report[0] + 1;

  if (next_report_id < REPORT_ID_COUNT)
  {
    // send_hid_report(0);
  }
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
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
  (void) instance;

  if (report_type == HID_REPORT_TYPE_OUTPUT)
  {
    // Set keyboard LED e.g Capslock, Numlock etc...
    if (report_id == REPORT_ID_KEYBOARD)
    {
      // bufsize should be (at least) 1
      if ( bufsize < 1 ) return;

      uint8_t const kbd_leds = buffer[0];

      if (kbd_leds & KEYBOARD_LED_CAPSLOCK)
      {
        // Capslock On: disable blink, turn led on
        blink_interval_ms = 0;
        board_led_write(true);
      }else
      {
        // Caplocks Off: back to normal blink
        board_led_write(false);
        blink_interval_ms = BLINK_MOUNTED;
      }
    }
  }
}
