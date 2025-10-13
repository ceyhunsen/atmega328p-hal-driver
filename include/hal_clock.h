/**
 * @file
 * @author Ceyhun Şen
 * @brief Configure system clock.
 *
 * ## Setting Clock Source
 *
 * Clock source can be set
 *
 * */

// SPDX-FileCopyrightText: 2025 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef __HAL_CLOCK_H
#define __HAL_CLOCK_H

/**
 * @enum clock_source
 * @brief Possible clock sources.
 */
enum clock_source {
    clock_external_clock = 0b0000,
    clock_calibrated_internal_rc_oscillator = 0b0010,
    clock_internal_128khz_rc_oscillator = 0b0011,
    clock_low_frequency_crystal_oscillator = 0b0100,
    clock_full_swing_crystal_oscillator = 0b0110,
    clock_low_power_crystal_oscillator = 0b1000,
};

void clock_set_source(enum clock_source source);

#endif // __HAL_CLOCK_H
