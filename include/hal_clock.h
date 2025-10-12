/**
 * @file
 * @author Ceyhun Şen
 * @brief Configure system clock.
 *
 *
 * */

// SPDX-FileCopyrightText: 2025 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef __HAL_CLOCK_H
#define __HAL_CLOCK_H

/**
 * @enum clock_source
 * @brief
 */
enum clock_source {
    clock_external_clock = 0,
    clock_calibrated_internal_rc_oscillator = 2,
    clock_low_power_crystal_oscillator = 0b1000,
};

#endif // __HAL_CLOCK_H
