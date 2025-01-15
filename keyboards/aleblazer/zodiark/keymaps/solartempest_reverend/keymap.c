/*
Copyright 2021 Spencer Deven <splitlogicdesign@gmail.com>
Copyright 2021 solartempest
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#ifdef OLED_ENABLE
	//#include "oled.c"
	#include "image_minimal.c"
#endif

#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)
	extern rgblight_config_t rgblight_config; // To pull layer status for RGBLIGHT
#endif

//Variables for custom keycodes


//#ifndef VIA_ENABLE //This will bypass the layout when VIA is enabled to save space. Requires loading layout in VIA otherwise random keys may be occur.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  KC_LBRC,                       KC_RBRC,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
      MO(3),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,  KC_MINS,                        KC_EQL,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  KC_GRV, KC_MUTE,      RGB_TOG, KC_DEL,KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
      KC_LCTL, KC_LALT, KC_LGUI, KC_APP, MO(1),       KC_SPC,   KC_ENT,           KC_ENT,   KC_SPC,  MO(2),    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

	[1] = LAYOUT(
      _______, KC_F1, KC_F2, KC_F3, KC_F4,   KC_F5,                                KC_F6,   KC_F7,   KC_F8, KC_F9, KC_F10, KC_F11,
      KC_PSLS, KC_P7, KC_P8, KC_P9, KC_NUM,  _______, _______,                   _______, _______, KC_PSLS, KC_P7, KC_P8, KC_P9, KC_F12,
      KC_CAPS, KC_P4, KC_P5, KC_P6, KC_NUM,  _______, _______,                   _______, _______, _______, KC_P4, KC_P5, KC_P6, KC_NUM,
      _______, KC_P1, KC_P2, KC_P3, _______, _______, _______, _______,  _______, _______, _______, _______, KC_P1, KC_P2, KC_P3, _______,
      _______, KC_P0, KC_PDOT, KC_PENT, _______,     _______,  _______,   _______,    _______,   _______, KC_P0, KC_PDOT, KC_PENT, _______
      ),

	[2] = LAYOUT(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
      _______, _______, _______, _______, _______, _______, _______,                   _______, _______, EE_CLR,  _______, _______, _______, KC_F12,
      _______, _______, _______, _______, _______, _______, _______,                   _______, _______, RGB_TOG, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD, RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI,
      _______, _______, _______, _______, _______,      _______,     _______, _______,     _______,      RGB_RMOD, RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD
      ),

	[3] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______,      _______,     _______, _______,     _______,      _______, _______, _______, _______, _______
      ),

	[4] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______,      _______,     _______, _______,     _______,      _______, _______, _______, _______, _______
      )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_PGDN, KC_PGUP)  },
    [1] =   { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [2] =   { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [3] =   { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [4] =   { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  }
};
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	#if defined(KEYBOARD_PET) || defined(OLED_LOGO)
		if (record->event.pressed) { //OLED timeout code
			oled_timer = timer_read32();
		}
	#endif
    	return true;
			}

void keyboard_post_init_user(void)
{
	#ifdef RGBLIGHT_ENABLE
		//rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT+8); //Set to static gradient 9
		//rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING); //Set to breathing
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT); //set to static colour

	#endif
	layer_move(0); 						//Start on layer0 by default to set LED colours. Can remove to save a very small amount of space.
}
