/**
 * @file test_mock_up.h
 * @author Ceyhun Şen
 * @brief Mock-up register definitions for testing.
 */

// SPDX-FileCopyrightText: 2023 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef __TEST_MOCK_UP_H
#define __TEST_MOCK_UP_H

#include <stdint.h>

extern uint8_t __atmega328p_registers[0xFF];

void reset_registers();
void spawn_watcher_thread(void *(*handler)());

#endif // __TEST_MOCK_UP_H
