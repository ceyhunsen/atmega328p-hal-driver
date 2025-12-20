/**
 * @file
 * @author Ceyhun Şen
 *
 * @brief System control and reset module, main functionalities.
 * */

// SPDX-FileCopyrightText: 2025 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#include "hal_system.h"
#include "hal_internals.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>

/**
 * @brief Reset watchdog timer counter.
 * */
inline void hal_system_reset_watchdog() { wdt_reset(); }

/**
 * @brief Set watchdog timer with given settings.
 * @param config Configuration option for watchdog.
 * */
void hal_system_set_watchdog(struct hal_system_watchdog_t config) {
    uint8_t control_register;

    control_register = 0;

    // Save operating mode.
    switch (config.mode) {
    default:
    case hal_system_watchdog_disabled:
        break;
    case hal_system_watchdog_interrupt_mode:
        SET_BIT(control_register, WDIE);
        break;
    case hal_system_watchdog_reset_mode:
        SET_BIT(control_register, WDE);
        break;
    case hal_system_watchdog_interrupt_and_reset_mode:
        SET_BIT(control_register, WDIE);
        SET_BIT(control_register, WDE);
        break;
    }

    // If watchdog timer is not disabled, save cycles.
    if (config.mode != hal_system_watchdog_disabled) {
        control_register |= (config.cycles << WDP0);
    }

    // Disable interrupts and reset watchdog counter.
    cli();
    hal_system_reset_watchdog();

    // Clear watchdog status flag.
    CLEAR_BIT(MCUSR, WDRF);

    // Set change enable.
    WDTCSR |= BIT(WDCE) | BIT(WDE);

    // Write final value to register.
    WDTCSR = control_register;

    // Finally, enable interrupts.
    sei();
}

/**
 * @brief Get reset status register value and reset status register. Reset
 * statuses are defined in enum `hal_system_reset_status`.
 * @returns Reset status register value.
 * @see hal_system_reset_status
 * */
inline uint8_t hal_system_get_reset_status() {
    uint8_t tmp;

    tmp = MCUSR;
    MCUSR = 0;

    return tmp;
}
