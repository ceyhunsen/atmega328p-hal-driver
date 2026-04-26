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
#include "hal_io.h"

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
 * @brief Set the top value of the timer0 counter. This value will be the top
 * for the timer0 if the correct #hal_timer0_operation_modes is set.
 */
void hal_timer0_set_top(uint8_t val) { OCR0A = val; }

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
        CLEAR_BIT(tccr0b, WGM02);
        SET_BIT(tccr0a, WGM01);
        SET_BIT(tccr0a, WGM00);
        break;
    case hal_timer0_mode_phase_correct_pwm:
        CLEAR_BIT(tccr0b, WGM02);
        CLEAR_BIT(tccr0a, WGM01);
        SET_BIT(tccr0a, WGM00);
        break;
    case hal_timer0_mode_phase_correct_pwm_to_top:
        SET_BIT(tccr0b, WGM02);
        CLEAR_BIT(tccr0a, WGM01);
        SET_BIT(tccr0a, WGM00);
        break;
    case hal_timer0_mode_fast_pwm_to_top:
        SET_BIT(tccr0b, WGM02);
        SET_BIT(tccr0a, WGM01);
        SET_BIT(tccr0a, WGM00);
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
 * @warning This call will make corresponding pin's direction to output, using
 * \ref hal_io_configure.
 *
 * @param reg Output compare register to set.
 * @param mode Output compare mode to set.
 *
 * @return Error if given mode or register is invalid, ok if everything is
 * valid.
 *
 * \see hal_timer0_output_compare_mode
 */
enum hal_result_timer0
hal_timer0_set_output_compare_mode(enum hal_timer0_output_compare_register reg,
                                   enum hal_timer0_output_compare_mode mode) {
    volatile uint8_t reg_val;
    uint8_t reg1, reg0;

    struct hal_io_pin io = {.port = hal_io_port_d};
    struct hal_io_pin_configuration configuration = {
        .direction = hal_io_direction_output,
    };

    // Set bits.
    switch (reg) {
    case hal_timer0_output_compare_register_a:
        reg1 = COM0A1;
        reg0 = COM0A0;

        io.pin = 6;
        if (hal_io_configure(io, configuration) != hal_result_io_ok) {
            return hal_result_timer0_cant_set_output_compare_io_pin;
        };
        break;
    case hal_timer0_output_compare_register_b:
        reg1 = COM0B1;
        reg0 = COM0B0;

        io.pin = 5;
        if (hal_io_configure(io, configuration) != hal_result_io_ok) {
            return hal_result_timer0_cant_set_output_compare_io_pin;
        };
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

    TCCR0A = reg_val;

    return hal_result_timer0_ok;
}

/**
 * @brief Set timer0's clock source
 */
enum hal_result_timer0
hal_timer0_set_clock_source(enum hal_timer0_clock_source source) {
    volatile uint8_t reg = TCCR0B;

    switch (source) {
    case hal_timer0_stop:
        CLEAR_BIT(reg, CS02);
        CLEAR_BIT(reg, CS01);
        CLEAR_BIT(reg, CS00);
        break;
    case hal_timer0_prescaler_1:
        CLEAR_BIT(reg, CS02);
        CLEAR_BIT(reg, CS01);
        SET_BIT(reg, CS00);
        break;
    case hal_timer0_prescaler_8:
        CLEAR_BIT(reg, CS02);
        SET_BIT(reg, CS01);
        CLEAR_BIT(reg, CS00);
        break;
    case hal_timer0_prescaler_64:
        CLEAR_BIT(reg, CS02);
        SET_BIT(reg, CS01);
        SET_BIT(reg, CS00);
        break;
    case hal_timer0_prescaler_256:
        SET_BIT(reg, CS02);
        CLEAR_BIT(reg, CS01);
        CLEAR_BIT(reg, CS00);
        break;
    case hal_timer0_prescaler_1024:
        SET_BIT(reg, CS02);
        CLEAR_BIT(reg, CS01);
        SET_BIT(reg, CS00);
        break;
    case hal_timer0_external_falling_edge:
        SET_BIT(reg, CS02);
        SET_BIT(reg, CS01);
        CLEAR_BIT(reg, CS00);
        break;
    case hal_timer0_external_rising_edge:
        SET_BIT(reg, CS02);
        SET_BIT(reg, CS01);
        SET_BIT(reg, CS00);
        break;

    default:
        return hal_result_timer0_invalid_clock_source;
        break;
    }

    TCCR0B = reg;

    return hal_result_timer0_ok;
}
