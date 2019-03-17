/*
Copyright 2017 Balz Guenat

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "fc660c.h"

#ifdef ACTUATION_DEPTH_ADJUSTMENT
#include "actuation_point.h"
#endif

#ifdef AUDIO_ENABLE
  #include "audio.h"
  float  caps_on[][2]  = SONG( CAPS_LOCK_ON_SOUND );
  float  caps_off[][2]  = SONG( CAPS_LOCK_OFF_SOUND );
#endif

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up

#ifdef ACTUATION_DEPTH_ADJUSTMENT
    adjust_actuation_point(ACTUATION_DEPTH_ADJUSTMENT);
#endif
wait_ms( 1000 );
	matrix_init_user();
}

void matrix_scan_kb(void) {
	// put your looping keyboard code here
	// runs every cycle (a lot)

	matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	// put your per-action keyboard code here
	// runs for every action, just before processing by the firmware

	return process_record_user(keycode, record);
}

void led_set_kb(uint8_t usb_led) {
    static uint8_t old_usb_led = 0;
    if ( (usb_led & (1 << USB_LED_CAPS_LOCK) ) && !(old_usb_led & (1 << USB_LED_CAPS_LOCK) ) )  {
        PORTB &= ~(1<<6);
        #ifdef AUDIO_ENABLE
          PLAY_SONG( caps_on );
        #endif
     }else if ( !(usb_led & (1 << USB_LED_CAPS_LOCK) ) && (old_usb_led & (1 << USB_LED_CAPS_LOCK) ) )  {
        PORTB |=  (1<<6);
        #ifdef AUDIO_ENABLE
          PLAY_SONG( caps_off );
        #endif
    }
    old_usb_led = usb_led;

	led_set_user(usb_led);
}
