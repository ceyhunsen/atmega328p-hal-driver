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
 * @param reg Output compare register to set.
 * @param mode Output compare mode to set.
 *
 * @return Error if given mode or register is invalid, ok if everything is
 * valid.
 *
 * \see hal_timer0_output_compare_mode
 * @todo Check if corresponding DDR bit is set.
 */
enum hal_result_timer0
hal_timer0_set_output_compare_mode(enum hal_timer0_output_compare_register reg,
                                   enum hal_timer0_output_compare_mode mode) {
    volatile uint8_t reg_val;
    uint8_t reg1, reg0;

    // Set bits.
    switch (reg) {
    case hal_timer0_output_compare_register_a:
        reg1 = COM0A1;
        reg0 = COM0A0;
        break;
    case hal_timer0_output_compare_register_b:
        reg1 = COM0B1;
        reg0 = COM0B0;
        break;

    default:
        return hal_result_timer0_invalid_output_compare_register;
    }

    // Change the register.
    reg_val = TCCR0A;
    switch (mode) {
    case hal_timer0_compare_output_mode_normal:
        CLEAR_BIT(reg_val, reg1);
        CLEAR_BIT(reg_val, reg0);
        break;
    case hal_timer0_compare_output_mode_toggle:
        CLEAR_BIT(reg_val, reg1);
        SET_BIT(reg_val, reg0);
        break;
    case hal_timer0_compare_output_mode_clear:
        SET_BIT(reg_val, reg1);
        CLEAR_BIT(reg_val, reg0);
        break;
    case hal_timer0_compare_output_mode_set:
        SET_BIT(reg_val, reg1);
        SET_BIT(reg_val, reg0);
        break;

    default:
        return hal_result_timer0_invalid_output_compare_mode;
    }

    // Write new value to register.
    TCCR0A = reg_val;

    return hal_result_timer0_ok;
}
