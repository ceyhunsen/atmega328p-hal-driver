/**
 * @file
 * @author Ceyhun Şen
 *
 * @brief System control and reset module, main functionalities.
 * */

/*
 * MIT License
 *
 * Copyright (c) 2023 Ceyhun Şen
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * */

#include "hal_system.h"
#include "hal_internals.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>

/**
 * @brief Set watchdog timer with given settings.
 * @param config Configuration option for watchdog.
 * */
void system_set_watchdog(struct system_watchdog_t config) {
    uint8_t control_register;

    control_register = 0;

    // Save operating mode.
    switch (config.mode) {
    default:
    case system_watchdog_disabled:
        break;
    case system_watchdog_interrupt_mode:
        SET_BIT(control_register, WDIE);
        break;
    case system_watchdog_reset_mode:
        SET_BIT(control_register, WDE);
        break;
    case system_watchdog_interrupt_and_reset_mode:
        SET_BIT(control_register, WDIE);
        SET_BIT(control_register, WDE);
        break;
    }

    // If watchdog timer is not disabled, save cycles.
    if (config.mode != system_watchdog_disabled) {
        control_register |= (config.cycles << WDP0);
    }

    // Disable interrupts and reset watchdog counter.
    cli();
    system_reset_watchdog();

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
 * @brief Reset watchdog timer counter.
 * */
inline void system_reset_watchdog() { wdt_reset(); }

/**
 * @brief Get reset status register value and reset status register. Reset
 * statuses are defined in enum `system_reset_status`.
 * @returns Reset status register value.
 * @see system_reset_status
 * */
inline uint8_t system_get_reset_status() {
    uint8_t tmp;

    tmp = MCUSR;
    MCUSR = 0;

    return tmp;
}
