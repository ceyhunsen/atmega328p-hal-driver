/**
 * @file
 * @author Ceyhun Şen
 *
 * Power management and sleep modes module, example usage.
 */

// SPDX-FileCopyrightText: 2023 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#include "hal_power.h"

int main() {
    enum hal_power_sleep_modes sleep_mode;
    enum hal_power_modules module;

    // Setting general CPU power.
    sleep_mode = hal_power_idle_mode;
    hal_power_set_sleep_mode(sleep_mode);

    // Disabling ADC.
    module = hal_power_adc;
    hal_power_set_module_power(module, 0);

    // Disabling SPI.
    module = hal_power_spi;
    hal_power_set_module_power(module, 0);

    // Enabling SPI.
    module = hal_power_spi;
    hal_power_set_module_power(module, 1);

    return 0;
}
