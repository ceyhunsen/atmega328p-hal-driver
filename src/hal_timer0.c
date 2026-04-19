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

/**
 * @brief Get current timer0 counter value.
 * @returns 8 bit value of the timer0 counter.
 */
uint8_t hal_timer0_get_counter() {
    volatile uint8_t val = TCNT0;
    return val;
}

/**
 * @brief Set new value to timer0 counter.
 */
void hal_timer0_set_counter(uint8_t val) { TCNT0 = val; }

/**
 * @brief Set timer0 operation mode
 * @param mode Operation mode to be set
 * @returns Error if mode is invalid
 */
enum hal_result_timer0
hal_timer0_set_operation_mode(enum hal_timer0_operation_modes mode) {
    volatile uint8_t tccr0a, tccr0b;

    tccr0a = TCCR0A;
    tccr0b = TCCR0B;

    switch (mode) {
    case hal_timer0_mode_normal:
        CLEAR_BIT(tccr0b, WGM02);
        CLEAR_BIT(tccr0a, WGM01);
        CLEAR_BIT(tccr0a, WGM00);
        break;
    case hal_timer0_mode_ctc:
        CLEAR_BIT(tccr0b, WGM02);
        SET_BIT(tccr0a, WGM01);
        CLEAR_BIT(tccr0a, WGM00);
        break;
    case hal_timer0_mode_fast_pwm:
        break;
    case hal_timer0_mode_phase_correct_pwm:
        break;

    default:
        return hal_result_timer0_invalid_operation_mode;
    }

    TCCR0A = tccr0a;
    TCCR0B = tccr0b;

    return hal_result_timer0_ok;
}

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
