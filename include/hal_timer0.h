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

enum hal_result_timer0 {
    hal_result_timer0_ok = 0,                     ///< Operation was successful
    hal_result_timer0_invalid_compare_output_mode ///< Invalid setting for
                                                  ///< either non-PWM, fast PWM
                                                  ///< or phase correct PWM
                                                  ///< modes
};

/// @brief Define operation mode with output compare bit. Works for non-PWM,
/// fast PWM or phase correct modes.
enum hal_timer0_compare_output_mode {
    hal_timer0_compare_output_mode_normal =
        0, ///< Normal port operation, OC0A disconnected
    hal_timer0_compare_output_mode_toggle, ///< Toggle OC0A on compare match
    hal_timer0_compare_output_mode_clear,  ///< Clear OC0A on compare match
    hal_timer0_compare_output_mode_set     ///< Set OC0A on compare match
};
