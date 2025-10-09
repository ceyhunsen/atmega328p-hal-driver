/**
 * @file
 * @author Ceyhun Şen
 *
 * @brief System control and reset module header file.
 * */

// SPDX-FileCopyrightText: 2023 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef __HAL_SYSTEM_H
#define __HAL_SYSTEM_H

#include <stdint.h>

/**
 * @enum system_watchdog_modes
 * @brief Trigger modes after watchdog timer expires.
 * */
enum system_watchdog_modes {
    system_watchdog_disabled = 0,            ///< Disable watchdog timer.
    system_watchdog_interrupt_mode,          ///< Trigger interrupt after
                                             ///< watchdog timer expires.
    system_watchdog_reset_mode,              ///< Reset MCU after watchdog
                                             ///< timer expires.
    system_watchdog_interrupt_and_reset_mode ///< Trigger interrupt and
                                             ///< reset MCU after watchdog
                                             ///< timer expires.
};

/**
 * @enum system_watchdog_cycles
 * @brief Watchdog oscillator cycles before a trigger.
 * */
enum system_watchdog_cycles {
    system_watchdog_2k_cycles = 0,   ///< 16 ms at 5.0 V.
    system_watchdog_4k_cycles = 1,   ///< 32 ms at 5.0 V.
    system_watchdog_8k_cycles = 2,   ///< 64 ms at 5.0 V.
    system_watchdog_16k_cycles = 3,  ///< 0.125 s at 5.0 V.
    system_watchdog_32k_cycles = 4,  ///< 0.25 s at 5.0 V.
    system_watchdog_64k_cycles = 5,  ///< 0.5 s at 5.0 V.
    system_watchdog_128k_cycles = 6, ///< 1 s at 5.0 V.
    system_watchdog_256k_cycles = 7, ///< 2 s at 5.0 V.
    system_watchdog_512k_cycles = 8, ///< 4 s at 5.0 V.
    system_watchdog_1024k_cycles = 9 ///< 8 s at 5.0 V.
};

/**
 * @struct system_watchdog_t
 * @brief Watchdog timer settings.
 * @param mode Watchdog timer trigger mode.
 * @param cycles Oscillator cycles before a watchdog trigger. Doesn't matter in
 * disabled mode.
 */
struct system_watchdog_t {
    enum system_watchdog_modes mode;
    enum system_watchdog_cycles cycles;
};

/**
 * @enum system_reset_status
 * @brief System reset causes.
 */
enum system_reset_status {
    system_power_on_reset = 0b0001, ///< System reset caused by power on
                                    ///< sequence.
    system_external_reset = 0b0010, ///< System reset caused by external
                                    ///< source.
    system_brownout_reset = 0b0100, ///< System reset caused by brownout
                                    ///< detector.
    system_watchdog_reset = 0b1000  ///< System reset caused by watchdog.
};

void system_set_watchdog(struct system_watchdog_t config);
void system_reset_watchdog();
uint8_t system_get_reset_status();

#endif // __HAL_SYSTEM_H
