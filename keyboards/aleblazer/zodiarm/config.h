/* Copyright 2023 Spencer Deven
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

/* Matrix Config */
#define MATRIX_ROWS 10 // Rows are Doubled Up on Splits
#define MATRIX_COLS 7
#define MATRIX_COL_PINS { C13, A0, B5, B4, B3, A15, A8 }
#define MATRIX_ROW_PINS { A10, B15, B10, B12, B14 }
#define MATRIX_COL_PINS_RIGHT { C13, A0, B5, B4, B3, A15, A8 }
#define MATRIX_ROW_PINS_RIGHT  { A10, B15, B10, B12, B14 }
#define DIODE_DIRECTION COL2ROW
#define MATRIX_IO_DELAY 5

/* Encoder Config */
#define ENCODERS_PAD_A { B6, B1, A7 }
#define ENCODERS_PAD_B { B7, B0, A6 }
#define ENCODERS_PAD_A_RIGHT { B6, B1, A7 }
#define ENCODERS_PAD_B_RIGHT { B7, B0, A6 }
#define ENCODER_RESOLUTION 2

#define SPLIT_HAND_PIN  C14  // high = left, low = right

/* serial.c configuration for split keyboard (Half-Duplex mode required for Blue Beta Boards, otherwise select your mode by bridging the labeled jumpers on the right side of the ZodiARM) */
#define SERIAL_USART_DRIVER SD2
#define SERIAL_USART_SPEED 921600
/* Half-Duplex single pin config, comment out for Full-Duplex mode */
//#define SOFT_SERIAL_PIN A3
/* Full-Duplex config, comment out for Half-Duplex mode*/
#define SERIAL_USART_FULL_DUPLEX // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN A2
#define SERIAL_USART_RX_PIN A3
#define SERIAL_USART_TX_PAL_MODE 7 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_RX_PAL_MODE 7 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_TIMEOUT 100   // USART driver timeout. default 100

/* i2c config for oleds */
#define I2C_DRIVER        I2CD1
#define I2C1_SCL_PIN      B8
#define I2C1_SDA_PIN      B9
#define I2C1_SCL_PAL_MODE 4
#define I2C1_SDA_PAL_MODE 4
/* For Legacy Compatibility: */
#define I2C1_SCL 8
#define I2C1_SDA 9

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Bootmagic config for flashing */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
#define BOOTMAGIC_LITE_ROW_RIGHT 5
#define BOOTMAGIC_LITE_COLUMN_RIGHT 6
