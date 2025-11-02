/**
 * @file
 * @author Ceyhun Şen
 *
 * @brief Extra power management and sleep modes functionalities.
 * */

// SPDX-FileCopyrightText: 2025 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#include "hal_internals.h"
#include "hal_power.h"

#include <avr/io.h>

/**
 * @brief Changes multiple module powers with a single register write. Use
 * #hal_power_modules to generate power on and off bytes.
 *
 * @param power_off_list Modules to power off. Set specific bit to 1 to do that.
 * @param power_on_list Modules to power on. Set specific bit to 1 to do that.
 *
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
