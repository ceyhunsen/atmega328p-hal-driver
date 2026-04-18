/**
 * @file
 * @author Ceyhun Şen
 * @brief Configure timer.
 *
 * To use both timer modules, sleep modes need to be disabled. Use
 * #hal_power_set_module_power to disable sleep mode.
 *
 * \see hal_power_set_module_power
 * \see hal_power_modules
 * */

// SPDX-FileCopyrightText: 2026 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#include <stdint.h>

/// @brief Available return types for timer0 functions.
enum hal_result_timer0 {
    hal_result_timer0_ok = 0,                      ///< Operation was successful
    hal_result_timer0_invalid_output_compare_mode, ///< Invalid setting for
                                                   ///< either non-PWM, fast PWM
                                                   ///< or phase correct PWM
                                                   ///< modes
    hal_result_timer0_invalid_output_compare_register, ///< An invalid output
                                                       ///< compare register is
                                                       ///< specified
};

/// @brief Two of the output compare registers, that are available to timer0.
enum hal_timer0_output_compare_register {
    hal_timer0_output_compare_register_a = 0, ///< Output compare register A
    hal_timer0_output_compare_register_b = 1  ///< Output compare register B
};

/// @brief Define operation mode with output compare bit. Works for non-PWM,
/// fast PWM or phase correct modes.
enum hal_timer0_output_compare_mode {
    hal_timer0_compare_output_mode_normal =
        0, ///< Normal port operation, OC0A disconnected
    hal_timer0_compare_output_mode_toggle, ///< Toggle OC0A on compare match
    hal_timer0_compare_output_mode_clear,  ///< Clear OC0A on compare match
    hal_timer0_compare_output_mode_set     ///< Set OC0A on compare match
};

uint8_t hal_timer0_get_counter();
void hal_timer0_set_counter(uint8_t val);
enum hal_result_timer0
hal_timer0_set_output_compare_mode(enum hal_timer0_output_compare_register reg,
                                   enum hal_timer0_output_compare_mode mode);
