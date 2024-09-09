/*
Copyright 2024 SimplifiedLife https://github.com/simplified-life
Copyright 2024 QMK User Manual
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

/////////////////////////////////
/* CIRQUE SETUP FILE */
/////////////////////////////////
// Key Features:
//      + Auto Mouse Layer for activation of mouse keys
//      + Drag Scrolling of Cirque with modifier buttons for what is being scrolled (window, volume, etc)
//      + Combined pointing devices with one always scroll and one for mouse function
//      + Different DPI Settings for each cirque


//////////////////////////////////////////////////////////////
// AUTO MOUSE this allows auto mouse keys when the mouse is used
//////////////////////////////////////////////////////////////

void pointing_device_init_user(void) {
//  set_auto_mouse_layer(<mouse_layer>); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
    cirque_pinnacle_configure_cursor_glide(5); //motion of cursor continues when flicked
}

#define SCR_VOL  SM_TG(SM_VOL)

//////////////////////////////////////////////////////////////
// DRAG SCROLL This allows you to toggle between scrolling and cursor movement by pressing the DRAG_SCROLL key.
// What is the drag scroll key? this does not apply to split cirque
//////////////////////////////////////////////////////////////

/*  //Needs to be defined in keymap.c otherwise here
    enum custom_keycodes {
        DRAG_SCROLL = SAFE_RANGE,
    };
 bool set_scrolling = false;
 */

// Modify these values to adjust the scrolling speed
#define SCROLL_DIVISOR_H 8.0
#define SCROLL_DIVISOR_V 8.0

// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

// Function to handle mouse reports and perform drag scrolling
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // Check if drag scrolling is active
    if (set_scrolling) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)mouse_report.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        mouse_report.h = (int8_t)scroll_accumulated_h;
        mouse_report.v = (int8_t)scroll_accumulated_v;

        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        // Clear the X and Y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}

// Function to handle key events and enable/disable drag scrolling
// defined here if not defined in keymap.c
/*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DRAG_SCROLL:
            // Toggle set_scrolling when DRAG_SCROLL key is pressed or released
            set_scrolling = record->event.pressed;
            break;
        default:
            break;
    }
    return true;
}
*/

// Function to handle layer changes and disable drag scrolling when not in AUTO_MOUSE_DEFAULT_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    // Disable set_scrolling if the current layer is not the AUTO_MOUSE_DEFAULT_LAYER
    if (get_highest_layer(state) != AUTO_MOUSE_DEFAULT_LAYER) {
        set_scrolling = false;
    }
    return state;
}

/////////////////////////////////
/* COMBINED POINTING FUNCTIONS */
/////////////////////////////////
//  The following example requires POINTING_DEVICE_COMBINED to be defined
// and sets the left side pointing device to scroll only while the right retains mouse.

void keyboard_post_init_user(void) {
    pointing_device_set_cpi_on_side(true, 100); //Set cpi on left side to a low value for slower scrolling.
    pointing_device_set_cpi_on_side(false, 2000); //Set cpi on right side to a reasonable value for mousing.
}

report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
    left_report.h = left_report.x;
    left_report.v = left_report.y;
    left_report.x = 0;
    left_report.y = 0;
    return pointing_device_combine_reports(left_report, right_report);
}
//////////////////////////////////////////






