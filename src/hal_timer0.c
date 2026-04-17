/**
 * @file
 * @author Ceyhun Şen
 *
 * @brief Timer module, main functionalities.
 * */

// SPDX-FileCopyrightText: 2026 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#include "hal_timer0.h"
#include "hal_internals.h"

#include <avr/io.h>
#include <stdint.h>

/**
 * @brief Set output compare pin behaviour.
 *
 * Behavior will change based on the compare output mode. Please refer to the
 * datasheet for more information.
 *
 * @param mode Output compare mode to set.
 * @return Error if given mode is invalid, ok if given mode is valid.
 *
 * \see hal_timer0_output_compare_mode
 * @todo Check if corresponding DDR bit is set.
 */
enum hal_result_timer0
hal_timer0_set_output_compare_mode(enum hal_timer0_output_compare_mode mode) {
    if (mode < hal_timer0_compare_output_mode_normal ||
        mode > hal_timer0_compare_output_mode_set) {
        return hal_result_timer0_invalid_output_compare_mode;
    }

    volatile uint8_t reg_val = TCCR0A;

    switch (mode) {
    default:
    case hal_timer0_compare_output_mode_normal:
        CLEAR_BIT(reg_val, COM0A1);
        CLEAR_BIT(reg_val, COM0A0);
        break;
    case hal_timer0_compare_output_mode_toggle:
        CLEAR_BIT(reg_val, COM0A1);
        SET_BIT(reg_val, COM0A0);
        break;
    case hal_timer0_compare_output_mode_clear:
        SET_BIT(reg_val, COM0A1);
        CLEAR_BIT(reg_val, COM0A0);
        break;
    case hal_timer0_compare_output_mode_set:
        SET_BIT(reg_val, COM0A1);
        SET_BIT(reg_val, COM0A0);
        break;
    }

    TCCR0A = reg_val;

    return hal_result_timer0_ok;
}
