/*
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
#include "quantum.h"
#include "print.h"
#include "images/ZodiarkPiLogoGC.qgf.c"
#include "images/ZodiarkPiLogo.qgf.c"
#include "images/anykey.qgf.c"

// #ifdef QUANTUM_PAINTER_ENABLE
// painter_device_t qp_st7789_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode);
// #endif

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
// Key Matrix to LED Index
  // Left Hand
  { 8, 6, 5, 3, 2, 0, NO_LED },
  { 9, 10, 11, 12, 13, 14, 15 },
  { 24, 22, 21, 19, 18, 17, 31 },
  { 25, 26, 27, 28, 29, 30, 32 },
  { 43, 41, 40, 38, 37, 35, 33 },
  // Right Hand
  { 52, 50, 49, 47, 46, 44, NO_LED },
  { 53, 54, 55, 56, 57, 58, 59 },
  { 68, 66, 65, 63, 62, 64, 75 },
  { 69, 70, 71, 72, 73, 74, 76 },
  { 87, 85, 84, 82, 81, 79, 77 },


},
{
{ 77, 4 }, //row0
{ 70, 5 },
{ 62, 3 },
{ 47, 1 },
{ 40, 2 },
{ 32, 3 },
{ 17, 8 },
{ 10, 9 },
{ 1, 8 },
{ 32, 15 },
{ 47, 13 },
{ 62, 15 },
{ 77, 16 },
{ 92, 34 }, //row2
{ 82, 30 },
{ 77, 28 },
{ 62, 27 },
{ 47, 25 },
{ 40, 26 },
{ 32, 26 },
{ 17, 31 },
{ 10, 33 },
{ 1, 31 },
{ 1, 43 }, //row3
{ 17, 43 },
{ 32, 38 },
{ 47, 36 },
{ 62, 38 },
{ 77, 39 },
{ 92, 47 },
{ 105, 53 },
{ 98, 63 }, //row4
{ 88, 59 },
{ 82, 56 },
{ 62, 50 },
{ 53, 48 },
{ 47, 48 },
{ 40, 49 },
{ 32, 50 },
{ 17, 55 },
{ 9, 55 },
{ 1, 55 },
{ 147, 4 }, //right row0qp_st7789
{ 154, 5 },
{ 162, 3 },
{ 177, 1 },
{ 184, 2 },
{ 192, 3 },
{ 207, 8 },
{ 215, 9 },
{ 222, 8 },
{ 222, 19 }, //row1
{ 207, 19 },
{ 192, 15 },
{ 177, 13 },
{ 162, 15 },
{ 147, 16 },
{ 132, 34 }, //row2
{ 143, 30 },
{ 147, 28 },
{ 162, 27 },
{ 177, 25 },
{ 185, 26 },
{ 192, 26 },
{ 207, 31 },
{ 215, 33 },
{ 222, 31 },
{ 222, 43 }, //row3
{ 207, 43 },
{ 192, 38 },
{ 177, 36 },
{ 162, 38 },
{ 147, 39 },
{ 132, 47 },
{ 119, 53 },
{ 126, 63 }, //row4
{ 136, 59 },
{ 142, 56 },
{ 155, 50 },
{ 162, 50 },
{ 177, 48 },
{ 184, 49 },
{ 192, 50 },
{ 207, 55 },
{ 214, 55 },
{ 222, 55 },
},
{
  // LED Index to Flag
 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
} };
#endif

static painter_device_t display;
static painter_image_handle_t image;

#ifdef ENCODER_ENABLE

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
      return false; /* Don't process further events if user function exists and returns false */
    }
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_MS_WH_UP);
        } else {
            tap_code(KC_MS_WH_DOWN);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    }
    return true;
}

#endif

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  debug_mouse=true;
}

uint32_t deferred_init(uint32_t trigger_time, void *cb_arg) {

    print("doing stuff\n");
    display = qp_gc9a01_make_spi_device(240, 240, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, LCD_SPI_DIVISOR, 0);
    qp_power(display, true);
    qp_init(display, QP_ROTATION_0);

    if (is_keyboard_left()) {
        image = qp_load_image_mem(gfx_ZodiarkPiLogoGC);
    } else {
        image = qp_load_image_mem(gfx_ZodiarkPiLogoGC);
    }

    if (image != NULL) {
        print("image was not null\n");
        if (is_keyboard_left()) {
            qp_drawimage(display, 0, 0, image);
        } else {
            qp_drawimage(display, 0, 0, image);
        }
    }
    return(0);
}

void keyboard_post_init_kb(void)
{
    debug_enable=true;
    defer_exec(3000, deferred_init, NULL);
}
