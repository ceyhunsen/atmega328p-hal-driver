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
    // Check for reserved or illegal values.
    switch (module) {
    case hal_power_adc:
    case hal_power_usart0:
    case hal_power_spi:
    case hal_power_timer_1:
    case hal_power_timer0:
    case hal_power_timer_2:
    case hal_power_twi:
        break;
    default:
        return 1;
    }

    if (state)
        CLEAR_BIT(PRR, module);
    else
        SET_BIT(PRR, module);

    return 0;
}

/**
 * @brief Changes multiple module powers at one go, using given lists. Use
 * #hal_power_modules to generate power on and off lists.
 * @param power_off_list Modules to power off. Set specific bit to 1 to do that.
 * @param power_on_list Modules to power on. Set specific bit to 1 to do that.
 * @returns 0 if successful. 1 if there is a problem.
 */
enum hal_result_power hal_power_change_module_powers(uint8_t power_off_list,
                                                     uint8_t power_on_list) {
    // Check if the reserved bit is used.
    if (power_off_list == BIT(4) || power_on_list == BIT(4)) {
        return hal_result_power_bit_is_reserved;
    }

    // Check if power off and on lists has same bit set.
    if (!(power_off_list ^ power_on_list)) {
        return hal_result_power_same_bit_set_for_power_management;
    }

    uint8_t new_state = PRR;
    new_state |= power_off_list;

    int i;
    for (i = 0; i <= 8; i++) {
        if (power_on_list & BIT(i)) {
            CLEAR_BIT(new_state, i);
        }
    }

    PRR = new_state;

    return hal_result_power_ok;
}
