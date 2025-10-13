/**
 * @file
 * @author Ceyhun Şen
 * @brief Configure system clock.
 *
 * ## Capabilities
 *
 * - View and change oscillator calibration.
 *
 * ## Setting Clock Source
 *
 * Clock source must be set at compile time. Please visit
 * https://www.nongnu.org/avr-libc/user-manual/group__avr__fuse.html for more
 * details and set it according to the ATmega328P datasheet.
 * */

// SPDX-FileCopyrightText: 2025 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef __HAL_CLOCK_H
#define __HAL_CLOCK_H

#include <stdint.h>

/**
 * @struct hal_clock_oscillator_calibration
 * @brief Oscillator calibration value with it's range specified.
 */
struct hal_clock_oscillator_calibration {
    uint8_t range : 1;
    uint8_t calibration_value : 7;
};

struct hal_clock_oscillator_calibration hal_clock_read_oscillator_calibration();

#endif // __HAL_CLOCK_H
