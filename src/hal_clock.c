/**
 * @file
 * @author Ceyhun Şen
 *
 * @brief Configures system input clock.
 * */

// SPDX-FileCopyrightText: 2025 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#include "hal_clock.h"

#include <avr/io.h>

/**
 * @brief Sets clock source of the system.
 * @param source Clock source to set.
 * */
void clock_set_source(enum clock_source source) {
    uint8_t value = source;
    CKSEL = 0;
}
