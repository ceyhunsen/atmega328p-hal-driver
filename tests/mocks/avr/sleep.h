/**
 * @file sleep.h
 * @author Ceyhun Şen
 * @brief Mock-up header of macros for accessing AVR special function registers.
 * This header must overwrite avr/sleep.h for testing.
 */

// SPDX-FileCopyrightText: 2023 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef __SLEEP_H
#define __SLEEP_H

/// Callback function to check for things if there are things needed to be done
/// after the sleep instruction. Needs to be defined per test file.
void sleep_callback();
#define sleep_cpu() sleep_callback()

#endif // __SLEEP_H
