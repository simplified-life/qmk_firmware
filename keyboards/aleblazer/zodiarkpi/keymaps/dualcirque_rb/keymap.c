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


enum custom_keycodes {          // See below in process_record_user for purpose of custom keycode
  DG_SCR = SAFE_RANGE,
  AM_Togl,
  DG_VOL,
  DG_PAN,
  DG_BRI,
  DG_HOR,
  DG_RWFF,
  MS_PREC,
};



/*Enable Auto Mouse */
void pointing_device_init_user(void) {
//  set_auto_mouse_layer(<mouse_layer>); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
//  cirque_pinnacle_configure_cursor_glide(5); //motion of cursor continues when flicked
}
/* Variable for Drag Scroll in cirque and global variable for passing keycode*/
bool set_scrolling = false;
static uint16_t current_keycode = KC_NO;
uint16_t get_current_keycode(void) {
    return current_keycode;
}
/* Variable to turn on/off Auto Mouse in cirque*/
bool auto_mouse_tg_off = false;
/* Precision Mode for Cirque Mouse */
bool cirque_precision_tg_off = false;
#define CIRQUE_DPI_DEFAULT 1500 //used for cirque as mouse
#define CIRQUE_DPI_PRECISION 400 //used for cirque to set in lower dpi in precision mode

//Tap Dance Declarations

enum td_keycodes {      // Tap dance enums
    TD_ALT,     //LALT Key when held or tapped. Shift up layer when ALT is tap tap held.
    TD_BSPC,    //BSPC Key when tapped, Ctrl+BSPC when held to delete whole words at a time
    TD_ESC,     //ESC Key when tapped, Ctrl+Alt+Delete when held
};
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Create a global instance of the tapdance state type
static td_state_t td_state;

// Declare your tapdance functions:

// Function to determine the current tapdance state
td_state_t cur_dance(tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void td_alt_finished(tap_dance_state_t *state, void *user_data);
void td_alt_reset(tap_dance_state_t *state, void *user_data);

/*Processing of user input for handling alternate actions*/
bool process_record_user(uint16_t keycode, keyrecord_t * record) {
  switch (keycode) {
     case DG_SCR:           // Activate mouse DRAG_SCROLL while pressed
     case DG_VOL:           // Activate cirque DRAG_VOLUME
     case DG_PAN:           // Activate cirque DRAG_PAN (horizontal and vertical scroll)
     case DG_BRI:           // Activate cirque DRAG_BRIGHTNESS
     case DG_HOR:           // Activate cirque DRAG_HORIZONTAL
     case DG_RWFF:          // Activate cirque DRAG_RWFF rewind/fast forward (not working well, uses horizontal motion)
         if(record->event.pressed) { // key down
         set_scrolling = record->event.pressed;
         current_keycode = keycode;
         } else {
            // Clear the global variable when the key is releasec
            if (current_keycode == keycode) {
            current_keycode = KC_NO;
            }
         }
         break;
     case MS_PREC: //update DPI values for Cirque and toggle for more precision
            if(record->event.pressed) { // key down
                if(cirque_precision_tg_off) {
                pointing_device_set_cpi_on_side(false, CIRQUE_DPI_DEFAULT); //Set cpi on right side to a default value for mousing.
                cirque_precision_tg_off = !cirque_precision_tg_off;
                } else{
                pointing_device_set_cpi_on_side(false, CIRQUE_DPI_PRECISION); //Set cpi on right side to a precision value for mousing.
                cirque_precision_tg_off = !cirque_precision_tg_off;
                }
            } // do nothing on key up
        break;
     case AM_Togl:      // toggle auto mouse enable key
            if(record->event.pressed) { // key down
                auto_mouse_layer_off(); // disable target layer if needed
                set_auto_mouse_enable((AUTO_MOUSE_ENABLED) ^ 1);
                auto_mouse_tg_off = !get_auto_mouse_enable();
            } // do nothing on key up
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
#ifdef TAP_DANCE_ENABLE
    #include "tapdance.c"
#endif

/* Layout Definitions for Different Layers */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//QWERTY / BASE
	[0] = LAYOUT(
      TD(TD_ESC), KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
      KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    TD(TD_BSPC),
      KC_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_MINS, KC_MUTE,  RGB_TOG, KC_EQL,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      SC_SENT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,LT(1,KC_GRV), KC_BSLS,  KC_EQL,  TT(1),    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
      KC_LCTL,TD(TD_ALT),  KC_LBRC, KC_RBRC, KC_LGUI, KC_SPC,          LSG(KC_S),  LCA(KC_TAB),       KC_ENT,  KC_DEL,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),
//NUMPAD
	[1] = LAYOUT(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                         KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,
      _______, _______, KC_UP,   _______, KC_BSPC, KC_NUM,                                        KC_PSLS, KC_P7,   KC_P8,   KC_P9,    KC_P0,   _______,
      _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL,  KC_SCRL, _______, _______,  _______, _______,  KC_PMNS, KC_P4,   KC_P5,   KC_P6,    KC_PAST, KC_F12,
      _______, _______, _______, _______, KC_MPLY, KC_MUTE, KC_VOLD, KC_VOLU,  RGB_TOG, TT(0),    KC_PDOT, KC_P1,   KC_P2,   KC_P3,    _______, _______,
      _______, _______, KC_HOME, KC_END,  _______, _______,            TO(2),  TO(3),             _______,  _______, _______, _______, _______, _______
      ),
//MOUSE
	[2] = LAYOUT(
      _______, DM_REC1, DM_REC2, DM_PLY1, DM_PLY2, DM_RSTP,                                      _______,      _______,      _______, _______,_______, _______,
      _______, _______, _______, _______, KC_BTN3, KC_BTN1,                                      KC_BTN1,      KC_BTN2,      KC_NO,   KC_NO,  MS_PREC, _______,
      _______, _______,  DG_SCR, _______, KC_LCTL, KC_BTN2, _______, _______,   _______, _______,LALT(KC_LEFT),LALT(KC_RGHT),KC_NO,   KC_BTN3,KC_NO,   _______,
      _______, _______, _______, _______, _______, DG_BRI,   DG_VOL, DG_RWFF,   RGB_TOG,  TT(0),   KC_F5,      _______,      KC_NO,   KC_NO,  KC_NO,   _______,
      _______, _______, _______, _______, _______, DG_PAN,   DG_HOR,            TO(1),           _______,      _______,      _______, _______,_______, _______
      ),
//SETTINGS
	[3] = LAYOUT(
      QK_BOOT,   TO(0),   TO(1),   TO(2),   TO(3),   TO(4),                                       _______, _______, _______, _______, _______, QK_BOOT,
      AM_Togl,   DF(0),   DF(1),   DF(2),   DF(3),   DF(4),                                       _______, _______, _______, _______, _______, _______,
      EE_CLR,  _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, TT(0),     RGB_TOG, RGB_MOD, RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI,
      _______, _______, _______, _______, _______, _______,            TO(2),  TO(1),             _______, RGB_RMOD,RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD
      ),

//COLEMAK DH
    [4] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, _______,    KC_F,    KC_P,    KC_B,                                        KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, _______,
      _______, _______,    KC_R,    KC_S,    KC_T, _______, _______, _______, _______, _______,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O, _______,
      _______, _______, _______, _______,    KC_D, _______, _______, _______, _______, TT(0),      KC_K,    KC_H, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______, _______
      )

};

/* REFERENCE (not programming guide) Custom Keycodes Particularly for Macros*/
//MACRO 1 SCREEN_SHOT = {KC_LCTL,KC_LALT,KC_TAB}
//MACRO 2 WINDOW_SWITCH = {KC_LGUI,KC_LSFT,KC_S}
