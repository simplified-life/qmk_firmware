//VOLUME SCROLL for cirque (See also DKAO if he ever gets back to me)
https://www.reddit.com/r/ploopy/comments/l32k9l/qmk_detect_direction_of_scroll_wheelmouse_movement/
https://blog.slinkyworks.net/running-custom-qmk-on-a-ploopy-mini-trackball/
https://github.com/shaleh/qmk_firmware/tree/my-ploopy-adept/keyboards/ploopyco/common

//Set precision  mode for cirque? Toggle through DPI and turn off auto mouse on some layers
https://docs.qmk.fm/features/pointing_device#examples

//Have an array of precision modes for precision scrolling
https://blog.slinkyworks.net/running-custom-qmk-on-a-ploopy-mini-trackball/


///////////////////////////////////////////
//KEYMAPS - make sure to check out examples and consider adding a colemak layer
//////////////////////////////////////////
//WORK ON MEDIA KEYS AND OTHER SHORTCUTS
Web browsing Back/Forward, third mouse button
Move cursor position back and forward
Undo and Redo?
Highlight words, paragraphs + Other
Integrate with Windows Powertoys?
//TAP DANCE KEYS consider some tap dance keys (double tap for an alternative - could be good for brackets, caps lock or similar)
TAP_DANCE_ENABLE = yes
TAB through windows from a double tap.... caps lock hold for a double tap shift to caps a word or similar?
//consider the ability to record custom macros using the settings layer or something so that when doing repetitive tasks the tasks can be automated
Example: select word nearest to cursor, highlight, paste clipboard over



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

/*
////FUNCTIONS
is_auto_mouse_active(void)	Returns the active state of the auto mouse layer (eg if the layer has been triggered)		bool
auto_mouse_keyevent(bool pressed)	Auto mouse mouse key event (true: key down, false: key up)	void(None)
get_auto_mouse_toggle(void)	Return value of toggling state variable	bool

keyboard_config_t keyboard_config;
uint16_t          dpi_array[] = CIRQUE_DPI_OPTIONS;
#define DPI_OPTION_SIZE ARRAY_SIZE(dpi_array)

uint16_t lastScroll        = 0; // Previous confirmed wheel event
uint16_t lastMidClick      = 0; // Stops scrollwheel from being read if it was pressed
*/

/* LOGIC FLOW
DEFINE MOUSE KEYS AND FUNCTIONS
KC_VOLU / KC_VOLD //volume
KC_MS_WH_UP / KC_MS_WH_DOWN //vertical scrolling
KC_BRIU / KC_BRID //screen brightness
KC_MS_WH_LEFT / KC_MS_WH_RIGHT //horizontal scrolling
KC_MRWD / KC_MFFD //fast foward / rewind media (horizontal movement)
PRECISION  - reduce DPI for RIGHT mouse

SCROLLING_KEYCODE

DRAG_VOLUME
DRAG_VERTICAL
DRAG_BRIGHTNESS
DRAG_HORIZONTAL
DRAG_RWFF
MOUSE_PRECISION


PROCESS MOUSE REPORT
SCALE FOR TASK
TRANSLATE to KEY PRESSES WHILE MOUSE KEY IS PRESSED



*/



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




DYNAMIC MACROS

Back to TopSee full docs
Record and play back sequences of keystrokes. Note: macros are not kept in memory after the keyboard is unplugged.

Step 1: Setup
in keymap.c:
enum planck_keycodes {
    QWERTY = SAFE_RANGE,
    COLEMAK,
    DVORAK,
    PLOVER,
    LOWER,
    RAISE,
    BACKLIT,
    EXT_PLV,
    DYNAMIC_MACRO_RANGE,
};

// this is called when dynamic macro buffer is full
void backlight_toggle(void) {
    // INSERT CODE HERE: for example, call function to turn on indicator LED.
}

#include "dynamic_macro.h"`
in keymap.c, in `process_record_user` function (create function if it doesn't exist):
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_dynamic_macro(keycode, record)) {
        return false;
    }
    return true;
}

Step 2: Use
in keymap.c, in your KEYMAP():
Keycode
to be added to your call to KEYMAP()
Description
DYN_REC_START1
Start recording Macro 1
DYN_REC_START2
Start recording Macro 2
DYN_REC_STOP
Stop recording current Macro
DYN_MACRO_PLAY1
Replay Macro 1
DYN_MACRO_PLAY2
Replay Macro 2


TAP DANCE
Back to TopSee full docs
Send different key codes depending on how many times key is tapped. Tap key once does one thing, tap twice does another thing, etc.

Step 1: Setup
in rules.mk:
TAP_DANCE_ENABLE = yes
in config.h:
#define TAPPING_TERM 200
Step 2: Declare
Create an entry for each tap dance in an enum. Replace YOUR_TAPDANCE_1, YOUR_TAPDANCE_2, etc., with the names of your tap dances.

in keymap.c, before KEYMAP():
// Tap Dance Declarations
enum {
    YOUR_TAPDANCE_1 = 0,
    YOUR_TAPDANCE_2,
    // ..., the rest of your tap dances
};
Step 3: Define
in keymap.c, before KEYMAP():
// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // simple tap dance
    [YOUR_TAPDANCE_1] = ACTION_TAP_DANCE_DOUBLE(KC_XXXX, KC_YYYY), // replace with your keycodes. BASIC codes only, no custom codes.

    // complex tap dance function (to specify what happens when key is pressed 3+ times, for example). See full docs for how to define
    [YOUR_TAPDANCE_2] = ACTION_TAP_DANCE_FN(your_function_name),
};
Step 4: Use
in keymap.c, in your KEYMAP():
TD(YOUR_TAPDANCE_1)
