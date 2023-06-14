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
#include "zodiarm.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
// Key Matrix to LED Index
  // Left Hand
  { 8, 6, 5, 3, 2, 0, 15 },
  { 9, 10, 11, 12, 13, 14, 16 },
  { 25, 23, 22, 20, 19, 18, 32 },
  { 26, 27, 28, 29, 30, 31, 34 },
  { 44, 42, 41, 39, 38, 37, 35},
  // Right Hand
  { 53, 51, 50, 48, 47, 45, 60 },
  { 54, 55, 56, 57, 58, 59, 61 },
  { 70, 68, 67, 65, 64, 63, 77 },
  { 71, 72, 73, 74, 75, 76, 79 },
  { 89, 87, 86, 84, 83, 82, 80 },

  
}, {
{ 77, 4 }, 
{ 70, 5 }, 
{ 62, 3 }, 
{ 47, 1 }, 
{ 40, 2 }, 
{ 32, 3 }, 
{ 17, 8 }, 
{ 10, 9 }, 
{ 1, 8 }, 
{ 1, 19 }, 
{ 17, 19 }, 
{ 32, 15 }, 
{ 47, 13 }, 
{ 62, 15 }, 
{ 77, 16 }, 
{ 92, 21 }, 
{ 92, 34 }, 
{ 82, 30 }, 
{ 77, 28 }, 
{ 62, 27 }, 
{ 47, 25 }, 
{ 40, 26 }, 
{ 32, 26 }, 
{ 17, 31 }, 
{ 10, 33 }, 
{ 1, 31 }, 
{ 1, 43 }, 
{ 17, 43 }, 
{ 32, 38 }, 
{ 47, 36 }, 
{ 62, 38 }, 
{ 77, 39 }, 
{ 92, 47 }, 
{ 98, 49 }, 
{ 105, 53 }, 
{ 98, 63 }, 
{ 88, 59 }, 
{ 82, 56 }, 
{ 62, 50 }, 
{ 47, 48 }, 
{ 40, 49 }, 
{ 32, 50 }, 
{ 17, 55 }, 
{ 9, 55 }, 
{ 1, 55 }, 
{ 147, 4 }, 
{ 154, 5 }, 
{ 162, 3 }, 
{ 177, 1 }, 
{ 184, 2 }, 
{ 192, 3 }, 
{ 207, 8 }, 
{ 215, 9 }, 
{ 222, 8 }, 
{ 222, 19 }, 
{ 207, 19 }, 
{ 192, 15 }, 
{ 177, 13 }, 
{ 162, 15 }, 
{ 147, 16 }, 
{ 132, 21 }, 
{ 132, 34 }, 
{ 143, 30 }, 
{ 147, 28 }, 
{ 162, 27 }, 
{ 177, 25 }, 
{ 185, 26 }, 
{ 192, 26 }, 
{ 207, 31 }, 
{ 215, 33 }, 
{ 222, 31 }, 
{ 222, 43 }, 
{ 207, 43 }, 
{ 192, 38 }, 
{ 177, 36 }, 
{ 162, 38 }, 
{ 147, 39 }, 
{ 132, 47 }, 
{ 125, 49 }, 
{ 119, 53 }, 
{ 126, 63 }, 
{ 136, 59 }, 
{ 142, 56 }, 
{ 162, 50 }, 
{ 177, 48 }, 
{ 184, 49 }, 
{ 192, 50 }, 
{ 207, 55 }, 
{ 214, 55 }, 
{ 222, 55 }, 
}, {
  // LED Index to Flag
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
} };
#endif
