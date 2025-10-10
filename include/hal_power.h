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
 * There are a bunch of sleep modes, defined in #power_sleep_modes. These
 * sleep modes can be selected with power_set_sleep_mode() function.
 *
 * ## Module Enable/Disable
 *
 * Modules can be enabled or disabled individually using
 * power_set_module_power() function. Possible candidates are listed in
 * #power_modules.
 * */

// SPDX-FileCopyrightText: 2023 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef __HAL_POWER_H
#define __HAL_POWER_H

#include <stdint.h>

/**
 * Sleep modes for ATmega328P. Value for every mode is the same as the bit
 * number in target register.
 * */
enum power_sleep_modes {
    power_idle_mode = 0,
    power_adc_noise_reduction_mode = 1,
    power_power_down_mode = 2,
    power_power_save_mode = 3,
    power_standby_mode = 6,
    power_external_standby_mode = 7
};

/**
 * Modules that have configurable power mode. Value for every module is the same
 * as the bit number in target register.
 * */
enum power_modules {
    power_adc = 0,
    power_usart0 = 1,
    power_spi = 2,
    power_timer_1 = 3,
    power_timer0 = 5,
    power_timer_2 = 6,
    power_twi = 7
};

void power_set_sleep_mode(enum power_sleep_modes mode);
void power_set_module_power(enum power_modules module, uint8_t state);

#endif // __HAL_POWER_H
