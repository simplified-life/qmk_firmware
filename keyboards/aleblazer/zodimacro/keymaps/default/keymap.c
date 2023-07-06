/*
Copyright 2021 Spencer Deven <splitlogicdesign@gmail.com>
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


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(
      KC_ESC, C(KC_S), C(KC_C), C(KC_V), KC_F13, KC_DEL,
      KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20,  KC_F21,
      KC_F22, KC_F23,  KC_F24,    C(KC_F13),    C(KC_F14),    C(KC_F15), C(KC_F16),
      C(KC_F17), C(KC_F18),    C(KC_F19),    C(KC_F20),    C(KC_F21),    C(KC_F22),  C(KC_F23), KC_MUTE,
      S(KC_F13), S(KC_F14), S(KC_F15), S(KC_F16), S(KC_F17),  S(KC_F18),   KC_ENT
    ),

};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (clockwise) {
              tap_code(KC_PGUP);
        } else {
           tap_code(KC_PGDN);
        }
    }
    return true;
}
