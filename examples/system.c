/**
 * @file
 * @author Ceyhun Şen
 *
 * System control and reset module, example usage.
 */

// SPDX-FileCopyrightText: 2023 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#include "hal_system.h"
#include <avr/interrupt.h>

ISR(WDT_vect) {
    // MCU will enter this function, before reset.
}

int main() {
    uint8_t cause;
    struct system_watchdog_t config;

    cause = system_get_reset_status();

    if (cause == system_watchdog_reset) {
        // Reset caused by watchdog. Means code below worked before.
    } else {
        // Reset not caused by watchdog.
    }

    // Create an interrupt and reset MCU after 8 seconds.
    config.mode = system_watchdog_interrupt_and_reset_mode;
    config.cycles = system_watchdog_1024k_cycles;
    system_set_watchdog(config);

    // Reset watchdog counter, if needed.
    system_reset_watchdog();

    while (1)
        ;

    return 0;
}
