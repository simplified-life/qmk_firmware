/////////
//KEYMAPS
/////////
//WORK ON SHORTCUTS
/*
//TAP DANCE KEYS consider some tap dance keys
TAB through windows from a double tap.... caps lock hold for a double tap shift to caps a word or similar?
//consider the ability to record custom macros using the settings layer or something so that when doing repetitive tasks the tasks can be automated
ACTION_TAP_DANCE_DOUBLE(kc1, kc2)

OSL(X) // switch to layer X for one keypress

//TAP DANCE

//Tap Dance Declarations
enum {
    TD_ALT = 0,
    TD_TAB = 0
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Alt, twice for layer switch
  [TD_ALT]  = ACTION_TAP_DANCE_DOUBLE(KC_LALT, OSL(1)),
  [TD_TAB]  = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_LALT(TAB))
};
*/


///////////////////////////////////////////
//VOLUME SCROLL for cirque (references)
//////////////////////////////////////////
//https://www.reddit.com/r/ploopy/comments/l32k9l/qmk_detect_direction_of_scroll_wheelmouse_movement/
//https://blog.slinkyworks.net/running-custom-qmk-on-a-ploopy-mini-trackball/
//https://github.com/shaleh/qmk_firmware/blob/my-ploopy-adept/keyboards/ploopyco/ploopyco.c
//https://github.com/qmk/qmk_firmware/blob/master/docs/features/pointing_device.md
//Set precision  mode for cirque? Toggle through DPI and turn off auto mouse on some layers?? https://docs.qmk.fm/features/pointing_device#examples




///////////////////////////////////////////
////OLED IDEAS
//////////////////////////////////////////
// LOCALISED IMAGES TO REDUCE PROCESSING

///////////////////////////////////////////
//LAYER LIGHTING
///////////////////////////////////////////

//  For anybody wanting to use layer lighting with the underglow LEDs, here is what should go for the RGB Matrix Flags in zodiarkpi.c. This uses bitmask 2 for underglow rather than 4 for everything:
//  { // LED Index to Flag
//   /*Left Hand*/4, 2, 4, 4, 2, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 2, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 4, 2, 4, 4, 2, 4, 4, 2, 4, /*Right Hand*/4, 2, 4, 4, 2, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 2, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 4, 2, 4, 4, 2, 4, 4, 2, 4,
//  }

///////////////////////////////////////////
//ENCODER RELATED ZODIARK PI SPECIFIC STUFF
///////////////////////////////////////////

/*
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
      return false; // Don't process further events if user function exists and returns false
...
*/


// FEATURES NOT IMPLEMENTED

// The following example will work with either POINTING_DEVICE_LEFT or POINTING_DEVICE_RIGHT and
// enables scrolling mode while on a particular layer.
/*
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


*/
