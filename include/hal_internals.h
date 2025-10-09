/**
 * @file hal_internals.h
 * @author Ceyhun Şen
 * @brief Internal macros for ATmega328P HAL driver.
 * */

// SPDX-FileCopyrightText: 2023 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef __HAL_INTERNALS_H
#define __HAL_INTERNALS_H

#include <avr/io.h>

/**
 * Create a value with shifting 1 to the left, `bit` times.
 */
#define BIT(bit) (_BV(bit))

/**
 * Clear specified `bit` of `var`.
 * */
#define CLEAR_BIT(var, bit) ((var) &= ~(BIT(bit)))

/**
 * Set specified `bit` of `var`.
 * */
#define SET_BIT(var, bit) ((var) |= BIT(bit))

#endif // __HAL_INTERNALS_H
