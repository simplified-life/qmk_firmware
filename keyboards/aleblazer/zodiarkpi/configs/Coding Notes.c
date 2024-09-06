
//Update keymap into keymap.c

//VOLUME SCROLL for cirque (See also DKAO if he ever gets back to me)
https://www.reddit.com/r/ploopy/comments/l32k9l/qmk_detect_direction_of_scroll_wheelmouse_movement/
https://blog.slinkyworks.net/running-custom-qmk-on-a-ploopy-mini-trackball/


//Set precision  mode for cirque? Toggle through DPI and turn off auto mouse on some layers
https://docs.qmk.fm/features/pointing_device#examples


///////////////////////////////////////////
//KEYMAPS
//////////////////////////////////////////
//WORK ON MEDIA KEYS AND OTHER SHORTCUTS
Web browsing Back/Forward, third mouse button
Move cursor position back and forward
Undo and Redo?
Highlight words, paragraphs + Other
Integrate with Windows Powertoys?
//TAP DANCE KEYS consider some tap dance keys (double tap for an alternative - could be good for brackets, caps lock or similar)
TAP_DANCE_ENABLE = yes




/////////////////////////////
//NOTES
/////////////////////////////
//Here's my keymap (haven't kept up-to-date with latest QMK): https://github.com/dkao/qmk_firmware/tree/dkao_20221222/keyboards/splitkb/kyria/keymaps/dkao
//I use mouse keys for click. These are on _FUNCTION layer activated by leftmost thumb key + keys near trackpad.
//With dual trackpads you could dedicate one side for scrolling if you'd prefer. If you want more reliable taps that's under relative mode, unfortunately relative vs absolute are mutually exclusive #ifdefs so need to build different images if you wanted relative on one half and absolute on the other.


// scrolling on one side https://docs.qmk.fm/features/pointing_device#combined-pointing-devices

// For clicking on touch, you need to enable absolute mode, and then the gestures will work https://docs.qmk.fm/features/pointing_device#absolute-mode-gestures


///////////////////////////////////////////
////OLED IDEAS
//////////////////////////////////////////
// POMODORO TIMER
// WPM COUNTER
// CAPS LOCK IMAGE
// LOCALISED IMAGES TO REDUCE PROCESSING


///////////////////////////////////////////
//LAYER LIGHTING
///////////////////////////////////////////
//For anybody wanting to use layer lighting with the underglow LEDs, here is what should go for the RGB Matrix Flags in zodiarkpi.c. This uses bitmask 2 for underglow rather than 4 for everything:
{ // LED Index to Flag
 /*Left Hand*/4, 2, 4, 4, 2, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 2, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 4, 2, 4, 4, 2, 4, 4, 2, 4, /*Right Hand*/4, 2, 4, 4, 2, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 2, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 4, 2, 4, 4, 2, 4, 4, 2, 4,
}


///////////////////////////////////////////
//ENCODER RELATED ZODIARK PI SPECIFIC STUFF
///////////////////////////////////////////

//Updated in rules.mk:
ENCODER_MAP_ENABLE = yes

//Used in keymap.c:
#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_PGDN, KC_PGUP)  },
    [1] =   { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [2] =   { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [3] =   { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  }
};
#endif

//Updated in zodiarkpi.json:
[{"y":-0.83,"x":6,"c":"#aaaaaa"},"0,6\n\n\n\n\n\n\n\n\ne0",{"x":5},"5,6\n\n\n\n\n\n\n\n\ne2"],

//This replaces/overrides the custom code you have in zodiarkpi.c that is not in the keymaps:
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
      return false; /* Don't process further events if user function exists and returns false *
...



// FEATURES NOT IMPLEMENTED

// The following example will work with either POINTING_DEVICE_LEFT or POINTING_DEVICE_RIGHT and
// enables scrolling mode while on a particular layer.

static bool scrolling_mode = false;

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _RAISE:  // If we're on the _RAISE layer enable scrolling mode
            scrolling_mode = true;
            pointing_device_set_cpi(2000);
            break;
        default:
            if (scrolling_mode) {  // check if we were scrolling before and set disable if so
                scrolling_mode = false;
                pointing_device_set_cpi(8000);
            }
            break;
    }
    return state;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (scrolling_mode) {
        mouse_report.h = mouse_report.x;
        mouse_report.v = mouse_report.y;
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}




/////////////////////////////////////
// SUPER BASIC HELLO WORLD
// Draw to OLED
bool oled_task_user() {
    // Set cursor position
    oled_set_cursor(5, 5);

    // Write text to OLED
    oled_write("Hello World!", false);

    return false;
}
// END OF SUPER BASIC TEST
/////////////////////////////////////





#include QMK_KEYBOARD_H


#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2
#define _LAYER3 3

enum custom_keycodes {
    LAYER0 = SAFE_RANGE,
    LAYER1,
    LAYER2,
    LAYER3,
};

 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_LAYER0] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_MUTE, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_NO, KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_GRV, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_BSLS, KC_LCTL, KC_LALT, KC_LBRC, KC_RBRC, KC_LGUI, KC_SPC, MACRO(1), KC_MINS, KC_0, KC_9, KC_8, KC_7, KC_6, RGB_TOG, KC_BSPC, KC_P, KC_O, KC_I, KC_U, KC_Y, KC_NO, KC_QUOT, KC_SCLN, KC_L, KC_K, KC_J, KC_H, TT(1), KC_RSFT, KC_SLSH, KC_DOT, KC_COMM, KC_M, KC_N, KC_EQL, KC_RGHT, KC_UP, KC_DOWN, KC_LEFT, KC_DEL, KC_ENT, MACRO(0)),

[_LAYER1] = LAYOUT(_______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, _______, _______, _______, KC_UP, _______, _______, _______, KC_END, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_MS_BTN1, KC_MS_BTN2, KC_VOLD, _______, _______, _______, _______, KC_MPLY, KC_MUTE, KC_VOLU, _______, _______, KC_HOME, KC_END, _______, _______, TO(2), KC_F11, KC_F10, KC_F9, KC_F8, KC_F7, KC_F6, _______, KC_BSPC, KC_P0, KC_P9, KC_P8, KC_P7, KC_PPLS, _______, KC_F12, KC_PAST, KC_P6, KC_P5, KC_P4, KC_PMNS, TO(0), _______, _______, KC_P3, KC_P2, KC_P1, KC_PDOT, RGB_TOG, _______, _______, _______, _______, _______, _______, TO(3)),

[_LAYER2] = LAYOUT(_______, KC_F1, KC_F2, KC_F3, KC_F4, KC_WWW_REFRESH, _______, KC_PSLS, KC_P7, KC_P8, KC_P9, _______, KC_NLCK, _______, KC_CAPS, KC_P4, KC_P5, KC_P6, KC_LCTL, KC_SLCK, _______, _______, KC_P1, KC_P2, KC_P3, _______, _______, _______, _______, KC_P0, KC_PDOT, KC_PENT, _______, _______, _______, KC_F11, KC_F10, KC_F9, KC_F8, KC_F7, KC_F6, _______, KC_F12, KC_NO, KC_NO, KC_NO, KC_MS_BTN2, KC_MS_BTN1, _______, _______, KC_NO, KC_NO, KC_MS_BTN3, KC_NO, TO(0), _______, _______, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, _______, _______, _______, _______, _______, _______, _______, _______),

[_LAYER3] = LAYOUT(RESET, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_F11, KC_F10, KC_F9, KC_F8, KC_F7, KC_F6, _______, KC_F12, RESET, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, _______, _______, RGB_VAI, RGB_SAI, RGB_HUI, RGB_SPI, RGB_MOD, _______, _______, RGB_VAD, RGB_SAD, RGB_HUD, RGB_SPD, RGB_RMOD, _______, _______)

};
