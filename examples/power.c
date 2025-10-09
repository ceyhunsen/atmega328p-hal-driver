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
    enum power_sleep_modes sleep_mode;
    enum power_modules module;

    // Setting general CPU power.
    sleep_mode = power_idle_mode;
    power_set_sleep_mode(sleep_mode);

    // Disabling ADC.
    module = power_adc;
    power_set_module_power(module, 0);

    // Disabling SPI.
    module = power_spi;
    power_set_module_power(module, 0);

    // Enabling SPI.
    module = power_spi;
    power_set_module_power(module, 1);

    return 0;
}
