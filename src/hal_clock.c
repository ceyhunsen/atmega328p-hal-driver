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
        .range = (raw >> 7) & 1,
        .calibration_value = raw & ((1 << 7) - 1),
    };

    return calibration_val;
}

/**
 * @brief Changes calibration value of the internal
 * @param value New calibration range and value.
 */
void hal_clock_write_oscillator_calibration_value(
    struct hal_clock_oscillator_calibration value) {
    OSCCAL = (value.range << 7) | (value.calibration_value);
}
