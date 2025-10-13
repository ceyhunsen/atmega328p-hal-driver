/**
 * @file
 * @author Ceyhun Şen
 *
 * @brief Configures system input clock.
 * */

// SPDX-FileCopyrightText: 2025 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#include "hal_clock.h"

#include <avr/io.h>

/**
 * @brief Returns current oscillator calibration value.
 * @returns Parsed calibration value with range.
 */
struct hal_clock_oscillator_calibration
hal_clock_read_oscillator_calibration() {
    uint8_t raw = OSCCAL;

    struct hal_clock_oscillator_calibration calibration_val = {
        .range = raw & (1 << 8),
        .calibration_value = raw & ((1 << 8) - 1),
    };

    return calibration_val;
}
