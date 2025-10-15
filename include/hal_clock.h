/**
 * @file
 * @author Ceyhun Şen
 * @brief Configure system clock.
 *
 * ## Capabilities
 *
 * - View and change oscillator calibration.
 * - View and change prescaler divisor for input clock.
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
 *
 * As stated in the datasheet, there are 2 available ranges for the calibration
 * value. But the important thing is these two ranges overlap. For example:
 * (range = 1, calibration_value = 0) < (range = 1, calibration_value =
 * 0b1111111). Please check datasheet for more information.
 */
struct hal_clock_oscillator_calibration {
    uint8_t range : 1;
    uint8_t calibration_value : 7;
};

struct hal_clock_oscillator_calibration hal_clock_read_oscillator_calibration();
void hal_clock_write_oscillator_calibration_value(
    struct hal_clock_oscillator_calibration value);

/**
 * @enum hal_clock_prescaler_division_rates
 * @brief Available divisors for clock prescaler. All available values are
 * powers of 2. Maximum division rate is 256 while minimum is 1.
 */
enum hal_clock_prescaler_division_rates {
    hal_clock_prescaler_1 = 0,
    hal_clock_prescaler_2,
    hal_clock_prescaler_4,
    hal_clock_prescaler_8,
    hal_clock_prescaler_16,
    hal_clock_prescaler_32,
    hal_clock_prescaler_64,
    hal_clock_prescaler_128,
    hal_clock_prescaler_256,
};

enum hal_clock_prescaler_division_rates hal_clock_get_clock_prescaler();
int hal_clock_change_clock_prescaler(
    enum hal_clock_prescaler_division_rates divisor);

#endif // __HAL_CLOCK_H
