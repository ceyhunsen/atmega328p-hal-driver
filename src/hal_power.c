/**
 * @file
 * @author Ceyhun Şen
 *
 * @brief Power management and sleep modes module, main functionalities.
 * */

// SPDX-FileCopyrightText: 2025 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#include "hal_power.h"
#include "hal_internals.h"

#include <avr/io.h>
#include <avr/sleep.h>

/**
 * @brief Set sleep mode for ATmega328P.
 * @param mode Sleep mode to be set.
 */
int hal_power_set_sleep_mode(enum hal_power_sleep_modes mode) {
    // Check if only legal values are passed.
    switch (mode) {
    case hal_power_idle_mode:
    case hal_power_adc_noise_reduction_mode:
    case hal_power_power_down_mode:
    case hal_power_power_save_mode:
    case hal_power_standby_mode:
    case hal_power_external_standby_mode:
        break;
    default:
        return 1;
    }

    // Assign new mode. Other bits of the register should be 0.
    SMCR = mode << 1;

    // Set sleep enable bit and call sleep instruction.
    SET_BIT(SMCR, SE);
    sleep_cpu();

    // Clear sleep flag after sleep.
    CLEAR_BIT(SMCR, SE);

    return 0;
}

/**
 * @brief Set specified module's power on or off. If a module is turned off,
 * it might need reinitialization (refer to data-sheet).
 * @param module Module name.
 * @param state 1 (or any other positive number) for on, 0 for off.
 * */
int hal_power_set_module_power(enum hal_power_modules module, uint8_t state) {
    // Check for illegal values.
    if (module == 4 || module > power_twi) {
        return 1;
    }

    if (state)
        CLEAR_BIT(PRR, module);
    else
        SET_BIT(PRR, module);

    return 0;
}
