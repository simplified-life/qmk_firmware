/*
Copyright 2024 SimplifiedLife https://github.com/simplified-life
Copyright 2024 QMK User Manual
Copyright 2023 Spencer Deven <splitlogicdesign@gmail.com>
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


/* LAYERS NAME DEFINITIONS */
enum layer_names {
    _BASE,          //BASE LAYER (QWERTY)
    _NUMPAD,        //NUMPAD LAYER
    _MOUSE,         //MOUSE LAYER
    _SETTINGS,      //SETTINGS LAYER
    _EXTRA          //UNUSED - SUGGESTED COLEMAK DH OR ALTERNATIVE
};

/* Custom Keycodes Particularly for Macros*/
//MACRO 1 SCR_SHOT = {KC_LCTL,KC_LALT,KC_TAB}
//MACRO 2 W_SWTCH = {KC_LGUI,KC_LSFT,KC_S}
enum custom_keycodes {
  DRAG_SCROLL = SAFE_RANGE,
  SCR_SHOT,
  W_SWTCH,
};

/* Variable for Drag Scroll in cirque*/
bool set_scrolling = false;

/*Processing of user input for handling alternate actions*/
bool process_record_user(uint16_t keycode, keyrecord_t * record) {
  switch (keycode) {
     case DRAG_SCROLL: // Toggle set_scrolling when DRAG_SCROLL key is pressed or released
         set_scrolling = record->event.pressed;
         break;
    case W_SWTCH:  // Windows function to take a screenshot
      if (record->event.pressed) {
        SEND_STRING("KC_LCTL,KC_LALT,KC_TAB");
      }
        break;
    case SCR_SHOT:  // Windows function to switch windows
      if (record->event.pressed) {
        SEND_STRING("KC_LGUI,KC_LSFT,KC_S");
      }
        break;
    default:
        break;
  }
  return true;
}

/* INCLUDE FILES for enabled devices (needs to be included after above definitions)*/
#ifdef OLED_ENABLE
	#include "oled.c"
#endif
#ifdef POINTING_DEVICE_ENABLE
    #include "cirque.c"
#endif

/* Layout Definitions for Different Layers */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//QWERTY / BASE
	[0] = LAYOUT(
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
      KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_MINS, KC_MUTE,  RGB_TOG, KC_EQL,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_GRV, KC_BSLS,   KC_EQL, TT(1),     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
      KC_LCTL, KC_LALT, KC_LBRC, KC_RBRC, KC_LGUI, KC_SPC,  LGUI(LSFT(KC_S)),  LCTL(LALT(KC_TAB)),KC_ENT,  KC_DEL,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),
//NUMPAD
	[1] = LAYOUT(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                         KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,
      _______, _______, KC_UP,   _______, _______, _______,                                       KC_PSLS, KC_P7,   KC_P8,   KC_P9,    KC_P0,   _______,
      _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_BTN1, KC_BTN2, _______, _______,  _______, _______,  KC_PMNS, KC_P4,   KC_P5,   KC_P6,    KC_PAST, KC_F12,
      _______, _______, _______, _______, KC_MPLY, KC_MUTE, KC_VOLD, KC_VOLU,  RGB_TOG, TT(0),    KC_PDOT, KC_P1,   KC_P2,   KC_P3,    _______, _______,
      _______, _______, KC_HOME, KC_END,  _______, _______, TO(2),             TO(3),             _______,  _______, _______, _______, _______, _______
      ),
//MOUSE
	[2] = LAYOUT(
      _______, KC_F1, KC_F2,   KC_F3,   KC_F4,     KC_F5,                                         KC_F6,   KC_F7,   KC_F8,  KC_F9,   KC_F10,  KC_F11,
      KC_PSLS, KC_P7, KC_P8,   KC_P9,   _______,   KC_NUM,                                        KC_BTN1, KC_BTN2, KC_NO,  KC_NO,   KC_NO,   _______,
      KC_CAPS, KC_P4, KC_P5,   KC_P6,   KC_LCTL,   KC_SCRL, _______, _______,  _______, _______,  TT(0),   KC_NO,   KC_NO,  KC_BTN3, KC_NO,   KC_F12,
      _______, KC_P1, KC_P2,   KC_P3,   _______,   _______, _______, _______,  _______,  TT(0),   _______, _______, KC_NO,  KC_NO,   KC_NO,   _______,
      _______, KC_P0, KC_PDOT, KC_PENT, _______,   _______, TO(3),             TO(1),             _______, _______, _______,_______, _______, _______
      ),
//SETTINGS
	[3] = LAYOUT(
      QK_BOOT, TO(0),   TO(1),   TO(2),   TO(3),   TO(4),                                         _______, _______, _______, _______, _______, QK_BOOT,
      _______, _______, _______, _______, _______, _______,                                       _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, TT(0),     RGB_TOG, RGB_MOD, RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI,
      _______, _______, _______, _______, _______, _______, TO(2),             TO(1),             _______, RGB_RMOD,RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD
      ),

//COLEMAK DH
    [4] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, _______,    KC_F,    KC_P,    KC_B,                                        KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, _______,
      _______, _______,    KC_R,    KC_S,    KC_T, _______, _______, _______, _______, _______,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O, _______,
      _______, _______, _______, _______,    KC_D, _______, _______, _______, _______, TT(0),      KC_K,    KC_H, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______,          _______,          _______, _______, _______, _______, _______, _______
      )

};

