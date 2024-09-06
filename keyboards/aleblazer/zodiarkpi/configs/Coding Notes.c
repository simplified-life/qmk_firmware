//Update Github

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


