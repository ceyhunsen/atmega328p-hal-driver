/**
 * @file
 * @author Ceyhun Şen
 * @brief Power management and sleep modes
 *
 * ## Capabilities
 *
 * - Set various sleep modes
 * - Enable/disable individual peripherals
 *
 * ## Sleep Modes
 *
 * There are a bunch of sleep modes, defined in #hal_power_sleep_modes. These
 * sleep modes can be selected with hal_power_set_sleep_mode() function.
 *
 * ## Module Enable/Disable
 *
 * Modules can be enabled or disabled individually using
 * hal_power_set_module_power() function. Possible candidates are listed in
 * #hal_power_modules.
 *
 * ## Extras
 *
 * ### Change Multiple Modules' Power States
 *
 * Apart from the hal_power_set_module_power(), hal_power_change_module_powers()
 * can be used to set multiple modules' power state. #hal_power_modules should
 * be used to construct power on and off bytes: Logic or multiple enum values to
 * construct the 2 parameters.
 * */

// SPDX-FileCopyrightText: 2025 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef __HAL_POWER_H
#define __HAL_POWER_H

#include <stdint.h>

/**
 * @brief Available sleep modes.
 *
 * Enum values matches register value for that setting.
 * */
enum hal_power_sleep_modes {
    hal_power_idle_mode = 0,
    hal_power_adc_noise_reduction_mode = 1,
    hal_power_power_down_mode = 2,
    hal_power_power_save_mode = 3,
    hal_power_standby_mode = 6,
    hal_power_external_standby_mode = 7
};

/// @brief Module specific errors for the power related stuff.
enum hal_result_power {
    ///< Operation successful.
    hal_result_power_ok = 0,
    ///< A reserved bit is used; No module has matched.
    hal_result_power_bit_is_reserved,
    ///< Same bit is set both to power on and off. Can't decide what to do  with
    ///< the power of that module.
    hal_result_power_same_bit_set_for_power_management,
};

/**
 * @brief Modules that's power state is configurable.
 *
 * Enum values matches register value for that setting.
 * */
enum hal_power_modules {
    hal_power_adc = 0,
    hal_power_usart0 = 1,
    hal_power_spi = 2,
    hal_power_timer_1 = 3,
    hal_power_timer0 = 5,
    hal_power_timer_2 = 6,
    hal_power_twi = 7
};

int hal_power_set_sleep_mode(enum hal_power_sleep_modes mode);
int hal_power_set_module_power(enum hal_power_modules module, uint8_t state);
enum hal_result_power hal_power_change_module_powers(uint8_t power_off_list,
                                                     uint8_t power_on_list);

#endif // __HAL_POWER_H
